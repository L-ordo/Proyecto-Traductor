#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>

using namespace std;

// Definimos la estructura de datos para almacenar las traducciones
struct WordTranslations {
    string spanish;
    string italian;
    string french;
    string german;
    string english;
};

// creamos la Función para cargar los datos desde un archivo
map<string, WordTranslations> loadTranslationsFromFile(const string& filename) {
    map<string, WordTranslations> translations;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        return translations;
    }

    string line;
    while (getline(file, line)) {
        WordTranslations word;
        
        stringstream ss(line);
        ss >> word.spanish >> word.italian >> word.french >> word.german >> word.english;
        translations[word.spanish] = word;
    }

    file.close();
    return translations;
}

// Se creo la funcion para mostrar las traducciones cargadas
void showTranslations(const map<string, WordTranslations>& translations) {
    for (const auto& pair : translations) {
        cout << "Palabra: " << pair.first << endl;
        cout << "  Italiano: " << pair.second.italian << endl;
        cout << "  Frances: " << pair.second.french << endl;
        cout << "  Aleman: " << pair.second.german << endl;
        cout << "  Ingles: " << pair.second.english << endl;
    }
}

// Función para agregar una nueva traducción al archivo
void addTranslationToFile(const string& filename, const WordTranslations& newTranslation) {
    ofstream file(filename, ios::app); // Abre el archivo en modo de agregar (append)
    if (file.is_open()) {
        file << newTranslation.spanish << " " << newTranslation.italian << " " << newTranslation.french << " " << newTranslation.german << " " << newTranslation.english << endl;
        cout << "Traducción agregada al archivo correctamente." << endl;
        file.close();
    } else {
        cerr << "Error al abrir el archivo " << filename << " para agregar una nueva traducción." << endl;
    }
}

// Función para encriptar una palabra según las condiciones dadas
string encryptWord(const string& word) {
    string encryptedWord = word; // Inicialmente, la palabra encriptada es igual a la palabra original
    
    // Definimos las sustituciones según las condiciones dadas
    map<char, string> substitutions = {
        {'b', "m1"}, {'c', "m2"}, {'d', "m3"}, {'f', "m4"}, {'g', "m5"}, {'h', "m6"},
        {'j', "m7"}, {'k', "m8"}, {'l', "m9"}, {'m', "m10"}, {'n', "m11"}, {'ñ', "m12"},
        {'p', "m13"}, {'q', "m14"}, {'r', "m15"}, {'s', "m16"}, {'t', "m17"}, {'v', "m18"},
        {'w', "m19"}, {'x', "m20"}, {'y', "m21"}, {'z', "m22"}, {'B', "g1"}, {'C', "g2"},
        {'D', "g3"}, {'F', "g4"}, {'G', "g5"}, {'H', "g6"}, {'J', "g7"}, {'K', "g8"},
        {'L', "g9"}, {'M', "g10"}, {'N', "g11"}, {'Ñ', "g12"}, {'P', "g13"}, {'Q', "g14"},
        {'R', "g15"}, {'S', "g16"}, {'T', "g17"}, {'V', "g18"}, {'W', "g19"}, {'X', "g20"},
        {'Y', "g21"}, {'Z', "g22"}
    };

    // Iteramos sobre cada caracter de la palabra y aplicamos la sustitución si está definida
    for (char& c : encryptedWord) {
        auto it = substitutions.find(c);
        if (it != substitutions.end()) {
            c = it->second[0]; // Reemplazamos el caracter por el primer caracter de la sustitución
            encryptedWord.insert(encryptedWord.find(c) + 1, it->second.substr(1)); // Insertamos el resto de la sustitución después del caracter
        }
    }

    return encryptedWord;
}

// Método para buscar la palabra en el archivo y encriptar sus traducciones
void encryptTranslations(const map<string, WordTranslations>& translations, const string& word) {
    auto it = translations.find(word);
    if (it != translations.end()) {
        WordTranslations encryptedTranslations = it->second;

        // Encriptar las traducciones
        encryptedTranslations.italian = encryptWord(it->second.italian);
        encryptedTranslations.french = encryptWord(it->second.french);
        encryptedTranslations.german = encryptWord(it->second.german);
        encryptedTranslations.english = encryptWord(it->second.english);

        // Mostrar las traducciones encriptadas en consola
        cout << "Palabra Encontrada: " << word << endl;
        cout << "  Italiano (Encriptado): " << encryptedTranslations.italian << endl;
        cout << "  Frances (Encriptado): " << encryptedTranslations.french << endl;
        cout << "  Aleman (Encriptado): " << encryptedTranslations.german << endl;
        cout << "  Ingles (Encriptado): " << encryptedTranslations.english << endl;

        // Guardar las traducciones encriptadas en un nuevo archivo
        ofstream outFile("encriptacion.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "Palabra: " << word << endl;
            outFile << "  Italiano (Encriptado): " << encryptedTranslations.italian << endl;
            outFile << "  FrancEs (Encriptado): " << encryptedTranslations.french << endl;
            outFile << "  Aleman (Encriptado): " << encryptedTranslations.german << endl;
            outFile << "  Ingls (Encriptado): " << encryptedTranslations.english << endl;
            outFile << endl;
            outFile.close();
            cout << "Traducciones encriptadas guardadas en el archivo 'encriptacion.txt'." << endl;
        } else {
            cerr << "Error al abrir el archivo 'encriptacion.txt' para guardar las traducciones encriptadas." << endl;
        }
    } else {
        cout << "La palabra \"" << word << "\" no fue encontrada en las traducciones." << endl;
    }
}

// Función para guardar las traducciones en un nuevo archivo
//void saveTranslationsToFile(const string& filename, const map<string, WordTranslations>& translations) {
//    ofstream file(filename);
//    if (file.is_open()) {
//        for (const auto& pair : translations) {
//            file << pair.second.spanish << " " << pair.second.italian << " " << pair.second.french << " " << pair.second.german << " " << pair.second.english << endl;
//        }
//        cout << "Traducciones guardadas en el nuevo archivo correctamente." << endl;
//        file.close();
//    } else {
//        cerr << "Error al crear el archivo " << filename << " para guardar las traducciones." << endl;
//    }
//}

//Metodo para buscar palabras
void searchWord(const map<string, WordTranslations>& translations, const string& word) {
    auto it = translations.find(word);
    if (it != translations.end()) {
        cout << "Traducciones de \"" << word << "\":\n";
        cout << "  Italiano: " << it->second.italian << endl;
        cout << "  Frances: " << it->second.french << endl;
        cout << "  Aleman: " << it->second.german << endl;
        cout << "  Ingles: " << it->second.english << endl;
    } else {
        cout << "La palabra \"" << word << "\" no fue encontrada en las traducciones." << endl;
    }
}

int main() {
    // ruta del archivo de entrada
    string filename = "C:\\Users\\ordol\\OneDrive\\Documents\\Universidad\\05 Quinto semestre\\Progra 3\\Proyecto traductor\\words.txt";

    // Cargamos las traducciones desde el archivo
    map<string, WordTranslations> translations = loadTranslationsFromFile(filename);

    int op;
    do {
        // Mostrar el menú
        cout << "\nMenu:\n";
        cout << "1. Mostrar traducciones\n";
        cout << "2. Agregar palabras\n";
        cout << "3. Buscar Palabras\n";
        cout << "4. Encriptar palabras\n";
        cout << "5. Desencriptar palabras\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch (op) {
            case 1:
                // Opción para mostrar las traducciones
                showTranslations(translations);
                break;
            case 2: {
                // Opción para agregar traducción
                WordTranslations newTranslation;
                cout << "Ingrese la palabra en espanol: ";
                cin >> newTranslation.spanish;
                cout << "Ingrese la traduccion en italiano: ";
                cin >> newTranslation.italian;
                cout << "Ingrese la traduccion en frances: ";
                cin >> newTranslation.french;
                cout << "Ingrese la traduccion en aleman: ";
                cin >> newTranslation.german;
                cout << "Ingrese la traduccion en ingles: ";
                cin >> newTranslation.english;
                addTranslationToFile(filename, newTranslation);
                break;
            }
            case 3:{
                 // Opción para buscar palabras             
                    string wordToSearch;
                    cout << "Ingrese la palabra a buscar: ";
                    cin >> wordToSearch;
                    searchWord(translations, wordToSearch);
                break;
            }
            case 4:{
                // Opción para encriptar palabras
                string wordToEncrypt;
                cout << "Ingrese la palabra a encriptar: ";
                cin >> wordToEncrypt;
                encryptTranslations(translations, wordToEncrypt);
                break;
            }
            case 6:
                // Opción para salir
                cout << "Saliendo del programa.\n";
                break;
            default:
                // Opción inválida
                cout << "Opción inválida. Por favor, seleccione una opción válida.\n";
                break;
        }
    } while (op != 6);

    return 0;
}

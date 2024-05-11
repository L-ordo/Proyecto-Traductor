#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

// Definimos la estructura de datos para almacenar las traducciones
struct WordTranslations {
    string spanish;
    string italian;
    string french;
    string german;
    string english;
};

// Definimos la estructura de un nodo de árbol AVL
struct Node {
    string key;
    WordTranslations translations;
    Node* left;
    Node* right;
    int height;
};

// Mapa para el encriptado de las palabras
map<char, string> encryptionMap = {
    {'b', "m1"}, {'c', "m2"}, {'d', "m3"}, {'f', "m4"}, {'g', "m5"}, {'h', "m6"},
    {'j', "m7"}, {'k', "m8"}, {'l', "m9"}, {'m', "m10"}, {'n', "m11"}, {'ñ', "m12"},
    {'p', "m13"}, {'q', "m14"}, {'r', "m15"}, {'s', "m16"}, {'t', "m17"}, {'v', "m18"},
    {'w', "m19"}, {'x', "m20"}, {'y', "m21"}, {'z', "m22"},
    {'B', "g1"}, {'C', "g2"}, {'D', "g3"}, {'F', "g4"}, {'G', "g5"}, {'H', "g6"},
    {'J', "g7"}, {'K', "g8"}, {'L', "g9"}, {'M', "g10"}, {'N', "g11"}, {'Ñ', "g12"},
    {'P', "g13"}, {'Q', "g14"}, {'R', "g15"}, {'S', "g16"}, {'T', "g17"}, {'V', "g18"},
    {'W', "g19"}, {'X', "g20"}, {'Y', "g21"}, {'Z', "g22"}
};

// Función para encriptar una palabra según el mapa de encriptación
string encryptWord(const string& word) {
    string encryptedWord;
    for (char c : word) {
        if (encryptionMap.find(c) != encryptionMap.end()) {
            encryptedWord += encryptionMap[c];
        } else {
            encryptedWord += c;
        }
    }
    return encryptedWord;
}

// Función para obtener la altura de un nodo
int height(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Función para obtener el máximo de dos enteros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Función para crear un nuevo nodo
Node* newNode(const string& key, const WordTranslations& translations) {
    Node* node = new Node();
    node->key = key;
    node->translations = translations;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

// Función para rotar a la derecha
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realizar rotación
    x->right = y;
    y->left = T2;

    // Actualizar alturas
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Función para rotar a la izquierda
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realizar rotación
    y->left = x;
    x->right = T2;

    // Actualizar alturas
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Función para obtener el balance de un nodo
int getBalance(Node* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Función para insertar un nodo en el árbol AVL
Node* insert(Node* node, const string& key, const WordTranslations& translations) {
    // Paso 1: Insertar nodo como en un árbol de búsqueda binaria estándar
    if (node == nullptr) return newNode(key, translations);

    if (key < node->key)
        node->left = insert(node->left, key, translations);
    else if (key > node->key)
        node->right = insert(node->right, key, translations);
    else // Claves iguales no se permiten en el árbol AVL
        return node;

    // Paso 2: Actualizar la altura del nodo actual
    node->height = 1 + max(height(node->left), height(node->right));

    // Paso 3: Obtener el balance del nodo para verificar si se ha desequilibrado
    int balance = getBalance(node);

    // Si el nodo se ha desequilibrado, hay 4 casos a considerar:

    // Caso izquierda-izquierda
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso derecha-derecha
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso izquierda-derecha
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Caso derecha-izquierda
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Si el nodo está balanceado, simplemente devuelve el nodo
    return node;
}

// Función para buscar una palabra en el árbol AVL
void searchWord(Node* root, const string& word) {
    if (root == nullptr) {
        cout << "La palabra \"" << word << "\" no fue encontrada en las traducciones." << endl;
        return;
    }
    if (word == root->key) {
        cout << "Traducciones de \"" << word << "\":\n";
        cout << "  Italiano: " << root->translations.italian << endl;
        cout << "  Francés: " << root->translations.french << endl;
        cout << "  Alemán: " << root->translations.german << endl;
        cout << "  Inglés: " << root->translations.english << endl;
    } else if (word < root->key) {
        searchWord(root->left, word);
    } else {
        searchWord(root->right, word);
    }
}

// Función para encriptar una palabra y sus traducciones y guardarlas en un nuevo archivo
void encryptAndSaveTranslations(const string& word, Node* root, const map<char, string>& encryptionMap) {
    // Verificar si la palabra existe en las traducciones
    searchWord(root, word);

    // Aquí podrías implementar la lógica para guardar las traducciones encriptadas en un archivo
    // Utiliza el mapa de encriptación para encriptar las palabras
    
}

int main() {
    // Ruta del archivo de entrada
    string filename = "words.txt";

    // Cargamos las traducciones desde el archivo y construimos el árbol AVL
    Node* root = nullptr;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            WordTranslations word;
            stringstream ss(line);
            ss >> word.spanish >> word.italian >> word.french >> word.german >> word.english;
            root = insert(root, word.spanish, word);
        }
        file.close();
    } else {
        cerr << "Error al abrir el archivo " << filename << endl;
        return 1;
    }

    int op;
    do {
        // Mostrar el menú
        cout << "\nMenu:\n";
        cout << "1. Mostrar traducciones\n";
        cout << "2. Agregar palabras\n";
        cout << "3. Buscar Palabras\n";
        cout << "4. Encriptar palabras\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch (op) {
            case 1:
                // Opción para mostrar las traducciones
                // Implementación pendiente
                break;
            case 2: {
                // Opción para agregar traducción
                // Implementación pendiente
                break;
            }
            case 3:{
                // Opción para buscar palabras
                string wordToSearch;
                cout << "Ingrese la palabra a buscar: ";
                cin >> wordToSearch;
                searchWord(root, wordToSearch);
                break;
            }
            case 4:{
                // Opción para encriptar palabra y guardar en archivo
                string wordToEncrypt;
                cout << "Ingrese la palabra que desea encriptar: ";
                cin >> wordToEncrypt;
                encryptAndSaveTranslations(wordToEncrypt, root, encryptionMap);
                break;
            }
            case 5:
                // Opción para salir
                cout << "Saliendo del programa.\n";
                break;
            default:
                // Opción inválida
                cout << "Opción inválida. Por favor, seleccione una opción válida.\n";
                break;
        }
    } while (op != 5);

    return 0;
}

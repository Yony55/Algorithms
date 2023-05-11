//
//A01424138 / Antonio Jaime Lopez
//A01424137 / Jonathan Maya
//A00829598 / Juan Pablo Yanez Gonzalez
//Programa que realiza el ordenamiento de un archivo .txt, ordenándolo por ip de forma ascendente
//Ademas, se almacenan los datos en un BST y se muestran las 5 ip mas altas
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
using namespace std;
//vector que guarda las ip ordenadas de forma ascendente
vector <string> finalVector;
//vector auxiliar para la impresión del árbol en level by level
vector <int> auxPrint;

// Se declara una estructura de tipo nodo, incluyendo "data" como valor entero
// y los respectivos apuntadores a sus hijos "left" y "right"
struct node
{
    int data;
    node* left;
    node* right;
};

// Función que crea un nodo u hoja para el BST recibiendo un dato entero
// Es de orden O(1), ya que solo se ejecuta una vez cuando es llamada
node* newNode(int data) {
    node* temp = new node();
    temp->data = data;
    temp->right = temp->left = NULL;
    return temp;
}

// Función que recibe el apuntador a la raíz del BST e imprime en pantalla
// los valores de forma "Level by level"
// Es de orden O(n), ya que depende de la cantidad de nodos en el BST
void lvlOrder(node* root) {
    if (root == NULL) {                       // Comprueba que no reciba una raiz vacia
        return;
    }
    queue <node*> Queue;                    // Se crea un objeto de tipo queue (FIFO) que almacena apuntadores a "node"
    Queue.push(root);
    while (!Queue.empty()) {
        node* currNode = Queue.front();     // Se crea otro apuntador tipo "node" que almacena el valor que se encuntra al frente
        //cout << currNode->data << " ";
        auxPrint.push_back(currNode->data);
        if (currNode->left != NULL) {       // Condiciones para seguir recorriendo el arbol
            Queue.push(currNode->left);
        }
        if (currNode->right != NULL) {
            Queue.push(currNode->right);
        }
        Queue.pop();                        // Se elimina el valor de enfrente de la cola (queue)
    }
}

// Funcion que inserta nodos u hojas dentro del BST
// es de orden O(n), ya que la busqueda de insercion depende
// de la cantidad de nodos en el arbol
void insertNode(node*& root, int data) {
    if (root == NULL) {
        root = newNode(data);
    }
    else if (root->data > data) {
        insertNode(root->left, data);
    }
    else {
        insertNode(root->right, data);
    }
}

//Funcion que ordena la tercera parte de la ip recibiendo un vector de direcciones
//Es de orden O(n^2), ya que contiene ciclos anidados
void ord3Digit2(vector <string> array) {
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(22, 1) == to_string(i) && array[j].substr(23, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 10; i < 100; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(22, 2) == to_string(i) && array[j].substr(24, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(22, 3) == to_string(i) && array[j].substr(25, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(23, 1) == to_string(i) && array[j].substr(24, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 10; i < 100; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(23, 2) == to_string(i) && array[j].substr(25, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(23, 3) == to_string(i) && array[j].substr(26, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }
}

//Funcion que ordena la segunda parte de la ip recibiendo un vector de direcciones
//Es de orden O(n^2), ya que contiene ciclos anidados
void ord3Digit(vector <string> array) {
    for (int i = 1; i < 10; i++) {
        vector <string> ipOrd;
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(20, 1) == to_string(i) && array[j].substr(21, 1) == ".") {
                ipOrd.push_back(array[j]);
            }
        }
        ord3Digit2(ipOrd);
    }

    for (int i = 10; i < 100; i++) {
        vector <string> ipOrd;
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(20, 2) == to_string(i) && array[j].substr(22, 1) == ".") {
                ipOrd.push_back(array[j]);
            }
        }
        ord3Digit2(ipOrd);
    }
}

//Funcion que ordena la tercera parte de la ip recibiendo un vector de direcciones
//Es de orden O(n^2), ya que contiene ciclos anidados
void ord2Digit2(vector <string> array) {
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(21, 1) == to_string(i) && array[j].substr(22, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 10; i < 100; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(21, 2) == to_string(i) && array[j].substr(23, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(21, 3) == to_string(i) && array[j].substr(24, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(22, 1) == to_string(i) && array[j].substr(23, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 10; i < 100; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(22, 2) == to_string(i) && array[j].substr(24, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(22, 3) == to_string(i) && array[j].substr(25, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }
    //
    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(22, 3) == to_string(i) && array[j].substr(25, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }
}

//Funcion que ordena la segunda parte de la ip recibiendo un vector de direcciones
//Es de orden O(n^2), ya que contiene ciclos anidados
void ord2Digit(vector <string> array) {
    for (int i = 1; i < 10; i++) {
        vector <string> ipOrd;
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(19, 1) == to_string(i) && array[j].substr(20, 1) == ".") {
                ipOrd.push_back(array[j]);
            }
        }
        ord2Digit2(ipOrd);
    }

    for (int i = 10; i < 100; i++) {
        vector <string> ipOrd;
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(19, 2) == to_string(i) && array[j].substr(21, 1) == ".") {
                ipOrd.push_back(array[j]);
            }
        }
        ord2Digit2(ipOrd);
    }
}

//Funcion que ordena la tercera parte de la ip recibiendo un vector de direcciones
//Es de orden O(n^2), ya que contiene ciclos anidados
void ord1Digit2(vector <string> array) {
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(20, 1) == to_string(i) && array[j].substr(21, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 10; i < 100; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(20, 2) == to_string(i) && array[j].substr(22, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(20, 3) == to_string(i) && array[j].substr(23, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(21, 1) == to_string(i) && array[j].substr(22, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 10; i < 100; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(21, 2) == to_string(i) && array[j].substr(23, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }

    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(21, 3) == to_string(i) && array[j].substr(24, 1) == ".") {
                finalVector.push_back(array[j]);
                array.erase(array.begin() + j);
            }
        }
    }
}

//Funcion que ordena la segunda parte de la ip recibiendo un vector de direcciones
//Es de orden O(n^2), ya que contiene ciclos anidados
void ord1Digit(vector <string> array) {
    for (int i = 1; i < 10; i++) {
        vector <string> ipOrd;
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(18, 1) == to_string(i) && array[j].substr(19, 1) == ".") {
                ipOrd.push_back(array[j]);
            }
        }
        ord1Digit2(ipOrd);
    }

    for (int i = 10; i < 100; i++) {
        vector <string> ipOrd;
        for (int j = 0; j < array.size(); j++) {
            if (array[j].substr(18, 2) == to_string(i) && array[j].substr(20, 1) == ".") {
                ipOrd.push_back(array[j]);
            }
        }
        ord1Digit2(ipOrd);
    }
}

int main() {
    //Declaramos variables 
    ifstream archivo;
    string linea;
    vector <string> vectorTemp;
    vector <string> ipOrd;
    node* root = NULL;


    ////////////Archivo///////////////
    //Se abre el archivo bitacora.txt
    archivo.open("bitacora.txt", ios::in);

    //se imprime un mensaje de error si es que no se pudo acceder al archivo
    if (archivo.fail()) {
        std::cout << "No se encontró el archivo" << endl;
        exit(1);
    }

    //Se meten las lineas del archivo un vector temporal
    while (!archivo.eof()) {
        getline(archivo, linea);
        vectorTemp.push_back(linea);
    }

    //Ciclo que ordena las ip que tienen un digito en la primera parte
    //Es de orden O(n), ya que contiene ciclos anidados
    for (int i = 1; i < 10; i++) {
        for (int j = 0; j < vectorTemp.size(); j++) {
            if (vectorTemp[j].substr(16, 1) == to_string(i) && vectorTemp[j].substr(17, 1) == ".") {
                ipOrd.push_back(vectorTemp[j]);
            }
        }
    }

    //Ciclo que ordena las ip que tienen dos digitos en la primera parte
    //Es de orden O(n), ya que contiene ciclos anidados
    for (int i = 10; i < 100; i++) {
        for (int j = 0; j < vectorTemp.size(); j++) {
            if (vectorTemp[j].substr(16, 2) == to_string(i) && vectorTemp[j].substr(18, 1) == ".") {
                ipOrd.push_back(vectorTemp[j]);
            }
        }
    }

    //Ciclo que ordena las ip que tienen tres digitos en la primera parte
    //Es de orden O(n), ya que contiene ciclos anidados
    for (int i = 100; i < 1000; i++) {
        for (int j = 0; j < vectorTemp.size(); j++) {
            if (vectorTemp[j].substr(16, 3) == to_string(i) && vectorTemp[j].substr(19, 1) == ".") {
                ipOrd.push_back(vectorTemp[j]);
            }
        }
    }

    //Ciclo que ordena las ip que tienen un digito en la primera parte
    //Y manda el vector a una funcion de ordenamiento
    //Es de orden O(n), ya que contiene ciclos anidados
    for (int i = 1; i < 10; i++) {
        vector <string> tempVector;
        for (int j = 0; j < ipOrd.size(); j++) {
            if (ipOrd[j].substr(16, 1) == to_string(i) && ipOrd[j].substr(17, 1) == ".") {
                tempVector.push_back(ipOrd[j]);
            }
        }
        ord1Digit(tempVector);
    }

    //Ciclo que ordena las ip que tienen dos digitos en la primera parte
    //Y manda el vector a una funcion de ordenamiento
    //Es de orden O(n), ya que contiene ciclos anidados
    for (int i = 10; i < 100; i++) {
        vector <string> tempVector;
        for (int j = 0; j < ipOrd.size(); j++) {
            if (ipOrd[j].substr(16, 2) == to_string(i) && ipOrd[j].substr(18, 1) == ".") {
                tempVector.push_back(ipOrd[j]);
            }
        }
        ord2Digit(tempVector);
    }

    //Ciclo que ordena las ip que tienen dos digitos en la primera parte
    //Y manda el vector a una funcion de ordenamiento
    //Es de orden O(n), ya que contiene ciclos anidados
    for (int i = 100; i < 1000; i++) {
        vector <string> tempVector;
        for (int j = 0; j < ipOrd.size(); j++) {
            if (ipOrd[j].substr(16, 3) == to_string(i) && ipOrd[j].substr(19, 1) == ".") {
                tempVector.push_back(ipOrd[j]);
            }
        }
        ord3Digit(tempVector);
    }

    //Ciclo que imprime los 5 valores mas grandes de bitacora.txt
    //Es de orden O(n), ya que el ciclo depende de la cantidad de datos
    for (int i = finalVector.size(); i > (finalVector.size() - 6); i--) {
        cout << finalVector[i] << endl;
    }

    //Ciclo para insertar bitacora en un BST
    //Es de orden O(n^2), ya que hay ciclos anidados
    for (int i = 0; i < finalVector.size(); i++) {
        for (int j = 0; j < finalVector.size(); j++) {
            if (vectorTemp[i] == finalVector[j]) {
                insertNode(root, j);
            }
        }
    }

    //Utilizamos esta parte del código para probar el funcionamiento del BST
    /*
    lvlOrder(root);

    for (int i = 0; i < auxPrint.size(); i++) {
        cout << finalVector[auxPrint[i]] << endl;
    }
    */

    return 0;
}
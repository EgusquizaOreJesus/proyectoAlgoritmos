// Deletion operation on a B+ tree in C++

#include <iostream>
#include "stack"
using namespace std;
int MAX_SIZE = 3;

class BPTree;
class Node {
    bool IS_LEAF{};
    int *key, size{};
    Node **ptr;
    friend class BPTree;

public:
    Node();
};
class BPTree {
    Node *root;
    void insertInternal(int, Node *, Node *);
    void removeInternal(int, Node *, Node *);
    Node *findParent(Node *, Node *);

public:
    BPTree();
    void search_value(int);
    void insert_value(int);
    void remove_value(int);
    static void print_BPTree(Node *);
    void print_BPTree();
};

Node::Node() {
    IS_LEAF = false;
    key = new int[MAX_SIZE];
    ptr = new Node *[MAX_SIZE + 1];
}
BPTree::BPTree() {
    root = nullptr;
}


void BPTree::search_value(int value) {
    if (root == nullptr) {
        cout << "El arbol esta vacio\n";
    } else {
        Node *temp = root;
        while (!temp->IS_LEAF) {
            for (int i = 0; i < temp->size; i++) {
                if (value < temp->key[i]) {
                    temp = temp->ptr[i];
                    break;
                }
                if (i == temp->size - 1) {
                    temp = temp->ptr[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < temp->size; i++) {
            if (temp->key[i] == value) {
                cout << "Valor encontrado\n";
                return;
            }
        }
        cout << "Valor no encontrado\n";
    }
}

void BPTree::insert_value(int value) {
    if (root == nullptr) {
        root = new Node;
        root->key[0] = value;
        root->IS_LEAF = true;
        root->size = 1;
    } else {
        Node *cursor = root;
        Node *parent;
        ///se busca llegar a la posicion para insertar
        while (!cursor->IS_LEAF) {
            parent = cursor;                        // se guarda el puntero previo
            for (int i = 0; i < cursor->size; i++) {
                if (value < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        ///caso donde aun queda espacio para insertar
        if (cursor->size < MAX_SIZE) {
            int i = 0;
            //busqueda de posicion
            while (value > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            //insersion del valor
            cursor->key[i] = value;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = nullptr;
        } else {    /// caso donde el nodo esta lleno
            ///se crea un nodo temporal para poder hacer la division
            Node *newLeaf = new Node;
            int virtualNode[MAX_SIZE + 1];
            for (int i = 0; i < MAX_SIZE; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (value > virtualNode[i] && i < MAX_SIZE)
                i++;
            for (int k = MAX_SIZE + 1; k > i; k--) {
                virtualNode[k] = virtualNode[k - 1];
            }
            virtualNode[i] = value;
            ///construccion de la nueva hoja
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX_SIZE + 1) / 2;                   /////!!!!!!!!!! declaracion de pesos
            newLeaf->size = MAX_SIZE + 1 - (MAX_SIZE + 1)/2;     ////// en este caso se deja con menor numero de datos al de la izquierda y con mayor a la derecha
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX_SIZE]; /// duda dudosa
            cursor->ptr[MAX_SIZE] = nullptr;

            ///asignacion de los valores a los nodos reales
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }

            ///si existe un padre se le asigna los nuevos punteros
            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];  // se asigna el menor valor del nuevo hijo
                newRoot->ptr[0] = cursor;           // puntero al hijo de la izquierda
                newRoot->ptr[1] = newLeaf;          // puntero al hijo de la derecha
                newRoot->IS_LEAF = false;           // se declara que no es hoja
                newRoot->size = 1;                  //asignacion de tamanio
                root = newRoot;                     //se asigna como el nuevo root
            } else { /// en caso exista un padre se realiza recursion
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

void BPTree::insertInternal(int value, Node *cursor, Node *child) {
    if (cursor->size < MAX_SIZE) {
        int i = 0;
        //busqueda de posicion a insertar el valor
        while (value > cursor->key[i] && i < cursor->size)
            i++;
        //movemos los valores a la derecha
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        //movemos los valores de los punteros a la derecha
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = value;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    } else {
        Node *newInternal = new Node;
        int virtualKey[MAX_SIZE + 1];
        Node *virtualPtr[MAX_SIZE + 2];
        //copia de los valores de los punteros del nodo
        for (int i = 0; i < MAX_SIZE; i++) {
            virtualKey[i] = cursor->key[i];
        }
        //copia de los valores de los punteros
        for (int i = 0; i < MAX_SIZE + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        //se busca la posicion del valor en el nodo
        while (value > virtualKey[i] && i < MAX_SIZE)
            i++;
        //se realiza el desplazamiento de los valores del nodo
        for (int k = MAX_SIZE + 1; k > i; k--) {
            virtualKey[k] = virtualKey[k - 1];
        }
        virtualKey[i] = value;
        //se realiza el deplazamiento de los punteros del nodo
        for (int k = MAX_SIZE + 2; k > i + 1; k--) {
            virtualPtr[k] = virtualPtr[k - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX_SIZE + 1) / 2; /// division de los tamanios ¸
        newInternal->size = MAX_SIZE - (MAX_SIZE + 1) / 2; /// division de los tamanios ¸
        //inserta los valores de la mitad correspondiente al nuevo nodo
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        //inserta los punteros de la mitad correspondiente al nuevo nodo
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            Node *newRoot = new Node;
            newRoot->key[0] = cursor->key[cursor->size];    ///guarda el valor mas alto a la izquierda
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        } else {
            insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
        }
    }
}

///funcion que nos permite conocer el nodo padre
Node *BPTree::findParent(Node *temp, Node *child) {
    Node *parent;
    if (temp->IS_LEAF || (temp->ptr[0])->IS_LEAF) { //si el nodo es hoja  o su primer hijo es hoja se retorna nullptr
        return nullptr;
    }
    for (int i = 0; i < temp->size + 1; i++) { // busca en todos sus punteros al hijo
        if (temp->ptr[i] == child) {
            parent = temp;
            return parent;  // si lo encuentra lo retorna
        } else {
            parent = findParent(temp->ptr[i], child);   // caso contrario sigue buscando
            if (parent != nullptr)
                return parent;
        }
    }
    return parent;
}

void BPTree::remove_value(int value) {
    if (root == nullptr) {
        cout << "Tree empty\n";
    } else {
        Node *temp = root;    //nodo actual
        Node *parent;           //se guarda el padre
        int leftSibling, rightSibling;
        while (!temp->IS_LEAF) {
            for (int i = 0; i < temp->size; i++) {
                parent = temp;
                leftSibling = i - 1;    // se guarda el valor del puntero izquierda
                rightSibling = i + 1;   // se guarda el valor del puntero derecha
                if (value < temp->key[i]) {
                    temp = temp->ptr[i];
                    break;
                }
                if (i == temp->size - 1) {//caso donde se llega al ultimo valor
                    leftSibling = i;
                    rightSibling = i + 2;
                    temp = temp->ptr[i + 1];
                    break;
                }
            }
        }
        bool found = false; //condicion de encontrado
        int pos;
        for (pos = 0; pos < temp->size; pos++) {  //se busca el valor
            if (temp->key[pos] == value) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Not found\n";
            return;
        }
        for (int i = pos; i < temp->size; i++) {
            temp->key[i] = temp->key[i + 1];
        }
        temp->size--;
        //caso donde solo se tiene el 1 nodo
        if (temp == root) {
            for (int i = 0; i < MAX_SIZE + 1; i++) {
                temp->ptr[i] = nullptr;
            }
            if (temp->size == 0) {// caso donde solo se tenie un elemento y se destruye el arbol
                cout << "Tree died\n";
                delete[] temp->key;
                delete[] temp->ptr;
                delete temp;
                root = nullptr;
            }
            return;
        }
        temp->ptr[temp->size] = temp->ptr[temp->size + 1];  // se disminuye el valor del puntero y se guarda el valor
        temp->ptr[temp->size + 1] = nullptr;    // el valor eleminado se vuele nullptr
        if (temp->size >= (MAX_SIZE + 1) / 2) {    // si el tamano del nodo eliminado es mayor a la condicion se acaba el delete
            return;
        }   // caso contrario se tiene que preguntar si el hermano del costado nos puede prestar
        if (leftSibling >= 0) {
            Node *leftNode = parent->ptr[leftSibling];
            if (leftNode->size >= (MAX_SIZE + 1) / 2 + 1) { // se realiza el prestamo de valores y actualizaciion de los punteros y valores en el nodo padre
                for (int i = temp->size; i > 0; i--) {
                    temp->key[i] = temp->key[i - 1];
                }
                temp->size++;
                temp->ptr[temp->size] = temp->ptr[temp->size - 1];
                temp->ptr[temp->size - 1] = nullptr;
                temp->key[0] = leftNode->key[leftNode->size - 1];
                leftNode->size--;
                leftNode->ptr[leftNode->size] = temp;
                leftNode->ptr[leftNode->size + 1] = nullptr;
                parent->key[leftSibling] = temp->key[0];
                return;
            }
        }   // caso donde el de la izquierda no nos puede prestar
        if (rightSibling <= parent->size) {
            Node *rightNode = parent->ptr[rightSibling];
            if (rightNode->size >= (MAX_SIZE + 1) / 2 + 1) { // se realiza el prestamo de valores y actualizaciion de los punteros y valores en el nodo padre
                temp->size++;
                temp->ptr[temp->size] = temp->ptr[temp->size - 1];
                temp->ptr[temp->size - 1] = nullptr;
                temp->key[temp->size - 1] = rightNode->key[0];
                rightNode->size--;
                rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size + 1];
                rightNode->ptr[rightNode->size + 1] = nullptr;
                for (int i = 0; i < rightNode->size; i++) {
                    rightNode->key[i] = rightNode->key[i + 1];
                }
                parent->key[rightSibling - 1] = rightNode->key[0];
                return;
            }
        }
        if (leftSibling >= 0) { //casos donde se elimina y se tiene que perder el valor
            Node *leftNode = parent->ptr[leftSibling];
            for (int i = leftNode->size, j = 0; j < temp->size; i++, j++) {
                leftNode->key[i] = temp->key[j];
            }
            leftNode->ptr[leftNode->size] = nullptr;
            leftNode->size += temp->size;
            leftNode->ptr[leftNode->size] = temp->ptr[temp->size];
            removeInternal(parent->key[leftSibling], parent, temp);
            delete[] temp->key;
            delete[] temp->ptr;
            delete temp;
        } else if (rightSibling <= parent->size) {
            Node *rightNode = parent->ptr[rightSibling];
            for (int i = temp->size, j = 0; j < rightNode->size; i++, j++) {
                temp->key[i] = rightNode->key[j];
            }
            temp->ptr[temp->size] = nullptr;
            temp->size += rightNode->size;
            temp->ptr[temp->size] = rightNode->ptr[rightNode->size];
            cout << "Merging two leaf nodes\n";
            removeInternal(parent->key[rightSibling - 1], parent, rightNode);
            delete[] rightNode->key;
            delete[] rightNode->ptr;
            delete rightNode;
        }
    }
}

void BPTree::removeInternal(int value, Node *temp, Node *child) {
    if (temp == root) {
        // Caso donde ya no se puede prestar de los hermanos y se tiene que eliminar el nodo si o si;
        if (temp->size == 1) {
            if (temp->ptr[1] == child) {
                delete[] child->key;
                delete[] child->ptr;
                delete child;
                root = temp->ptr[0];
                delete[] temp->key;
                delete[] temp->ptr;
                delete temp;
                cout << "Changed root node\n";
                return;
            } else if (temp->ptr[0] == child) {
                delete[] child->key;
                delete[] child->ptr;
                delete child;
                root = temp->ptr[1];
                delete[] temp->key;
                delete[] temp->ptr;
                delete temp;
                cout << "Changed root node\n";
                return;
            }
        }
    }
    int pos;
    for (pos = 0; pos < temp->size; pos++) {
        if (temp->key[pos] == value) {
            break;
        }
    }
    /// Elimina la clave 'value' del nodo 'temp'
    for (int i = pos; i < temp->size; i++) {
        temp->key[i] = temp->key[i + 1];
    }
    /// Elimina el puntero 'child' del nodo 'temp'
    for (pos = 0; pos < temp->size + 1; pos++) {
        if (temp->ptr[pos] == child) {
            break;
        }
    }
    for (int i = pos; i < temp->size + 1; i++) {
        temp->ptr[i] = temp->ptr[i + 1];
    }
    temp->size--;

    /// Si el tamaño del nodo 'temp' es mayor o igual a la mitad de la capacidad permitida, se termina la eliminación
    if (temp->size >= (MAX_SIZE + 1) / 2 - 1) {
        return;
    }
    if (temp == root)
        return;

    /// Se busca el padre del nodo 'temp'
    Node *parent = findParent(root, temp);
    int leftSibling = 0, rightSibling;
    for (pos = 0; pos < parent->size + 1; pos++) {
        if (parent->ptr[pos] == temp) {
            leftSibling = pos - 1;
            rightSibling = pos + 1;
            break;
        }
    }

    /// Si el hermano izquierdo puede prestar valores
    if (leftSibling >= 0) {
        Node *leftNode = parent->ptr[leftSibling];
        if (leftNode->size >= (MAX_SIZE + 1) / 2) {
            /// Realiza el préstamo de valores y actualización de punteros y valores en el nodo padre
            for (int i = temp->size; i > 0; i--) {
                temp->key[i] = temp->key[i - 1];
            }
            temp->key[0] = parent->key[leftSibling];
            parent->key[leftSibling] = leftNode->key[leftNode->size - 1];
            for (int i = temp->size + 1; i > 0; i--) {
                temp->ptr[i] = temp->ptr[i - 1];
            }
            temp->ptr[0] = leftNode->ptr[leftNode->size];
            temp->size++;
            leftNode->size--;
            return;
        }
    }

    /// Si el hermano derecho puede prestar valores
    if (rightSibling <= parent->size) {
        Node *rightNode = parent->ptr[rightSibling];
        if (rightNode->size >= (MAX_SIZE + 1) / 2) {
            // Realiza el préstamo de valores y actualización de punteros y valores en el nodo padre
            temp->key[temp->size] = parent->key[pos];
            parent->key[pos] = rightNode->key[0];
            for (int i = 0; i < rightNode->size - 1; i++) {
                rightNode->key[i] = rightNode->key[i + 1];
            }
            temp->ptr[temp->size + 1] = rightNode->ptr[0];
            for (int i = 0; i < rightNode->size; ++i) {
                rightNode->ptr[i] = rightNode->ptr[i + 1];
            }
            temp->size++;
            rightNode->size--;
            return;
        }
    }

    /// Fusiona con el hermano izquierdo si no puede prestar valores
    if (leftSibling >= 0) {
        Node *leftNode = parent->ptr[leftSibling];
        leftNode->key[leftNode->size] = parent->key[leftSibling];
        for (int i = leftNode->size + 1, j = 0; j < temp->size; j++) {
            leftNode->key[i] = temp->key[j];
        }
        for (int i = leftNode->size + 1, j = 0; j < temp->size + 1; j++) {
            leftNode->ptr[i] = temp->ptr[j];
            temp->ptr[j] = nullptr;
        }
        leftNode->size += temp->size + 1;
        temp->size = 0;
        removeInternal(parent->key[leftSibling], parent, temp);
    }
    /// Fusiona con el hermano derecho si no puede prestar valores
    else if (rightSibling <= parent->size) {
        Node *rightNode = parent->ptr[rightSibling];
        temp->key[temp->size] = parent->key[rightSibling - 1];
        for (int i = temp->size + 1, j = 0; j < rightNode->size; j++) {
            temp->key[i] = rightNode->key[j];
        }
        for (int i = temp->size + 1, j = 0; j < rightNode->size + 1; j++) {
            temp->ptr[i] = rightNode->ptr[j];
            rightNode->ptr[j] = nullptr;
        }
        temp->size += rightNode->size + 1;
        rightNode->size = 0;
        removeInternal(parent->key[rightSibling - 1], parent, rightNode);
    }
}

void BPTree::print_BPTree(Node *root) {
    stack<Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        for (int i = 0; i < currentNode->size; i++) {
            cout << currentNode->key[i] << " ";
        }
        cout << "\n";

        if (!currentNode->IS_LEAF) {
            for (int i = 0; i < currentNode->size + 1; i++) {
                nodeStack.push(currentNode->ptr[i]);
            }
        }
    }
}

void BPTree::print_BPTree() {
    print_BPTree(root);
}


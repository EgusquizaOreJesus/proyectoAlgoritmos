// Deletion operation on a B+ tree in C++

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
int MAX = 3;

class BPTree;
class Node {
    bool IS_LEAF;
    int *key, size;
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
    void search(int);
    void insert(int);
    void remove(int);
    void display(Node *);
    Node *getRoot();
    void show_BPTree();
};
Node::Node() {
    key = new int[MAX];
    ptr = new Node *[MAX + 1];
}
BPTree::BPTree() {
    root = nullptr;
}
void BPTree::insert(int x) {
    if (root == NULL) {
        root = new Node;
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    } else {
        Node *cursor = root;
        Node *parent;
        //se busca llegar a la posicion para insertar
        while (!cursor->IS_LEAF) {
            parent = cursor; // se guarda el puntero previo
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        //caso donde aun queda espacio para insertar
        if (cursor->size < MAX) {
            int i = 0;
            //busqueda de posicion
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            //insersion del valor
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = NULL;
        } else {    // caso donde el nodo esta lleno
            //se crea un nodo temporal para poder hacer la division
            Node *newLeaf = new Node;
            int virtualNode[MAX + 1];
            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (x > virtualNode[i] && i < MAX)
                i++;
            for (int j = MAX + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = x;
            //construccion de la nueva hoja
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX + 1) / 2; ///////////!!!!!!!!!! declaracion de pesos
            newLeaf->size = MAX + 1 - (MAX + 1) /
                                      2; ////// en este caso se deja con menor numero de datos al de la izquierda y con mayor a la derecha
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX]; /// duda dudosa
            cursor->ptr[MAX] = nullptr;

            //asignacion de los valores a los nodos reales
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }

            //si existe un padre se le asigna los nuevos punteros
            if (cursor == root) {
                Node *newRoot = new Node;
                newRoot->key[0] = newLeaf->key[0];  // se asigna el menor valor del nuevo hijo
                newRoot->ptr[0] = cursor;   // puntero al hijo de la izquierda
                newRoot->ptr[1] = newLeaf;  // puntero al hijo de la derecha
                newRoot->IS_LEAF = false;   // se declara que no es hoja
                newRoot->size = 1;          //asignacion de tamanio
                root = newRoot;             //se asigna como el nuevo root
            } else {    // en caso exista un padre se realiza recursion
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

void BPTree::insertInternal(int x, Node *cursor, Node *child) {
    if (cursor->size < MAX) {
        int i = 0;
        //busqueda de posicion a insertar el valor
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        //movemos los valores a la derecha
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        //movemos los valores de los punteros a la derecha
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    } else {
        Node *newInternal = new Node;
        int virtualKey[MAX + 1];
        Node *virtualPtr[MAX + 2];
        //copia de los valores de los punteros del nodo
        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
        }
        //copia de los valores de los punteros
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        //se busca la posicion del valor en el nodo
        while (x > virtualKey[i] && i < MAX)
            i++;
        //se realiza el desplazamiento de los valores del nodo
        for (int j = MAX + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        //se realiza el deplazamiento de los punteros del nodo
        for (int j = MAX + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX + 1) / 2; /// division de los tamanios ¸
        newInternal->size = MAX - (MAX + 1) / 2; /// division de los tamanios ¸
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

//funcion que nos permite conocer el nodo padre
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
void BPTree::remove(int value) {
    if (root == nullptr) {
        cout << "Tree empty\n";
    } else {
        Node *cursor = root;    //nodo actual
        Node *parent;           //se guarda el padre
        int leftSibling, rightSibling;
        while (!cursor->IS_LEAF) {
            for (int i = 0; i < cursor->size; i++) {
                parent = cursor;
                leftSibling = i - 1;    // se guarda el valor del puntero izquierda
                rightSibling = i + 1;   // se guarda el valor del puntero derecha
                if (value < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {//caso donde se llega al ultimo valor
                    leftSibling = i;
                    rightSibling = i + 2;
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        bool found = false; //condicion de encontrado
        int pos;
        for (pos = 0; pos < cursor->size; pos++) {  //se busca el valor
            if (cursor->key[pos] == value) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Not found\n";
            return;
        }
        for (int i = pos; i < cursor->size; i++) {
            cursor->key[i] = cursor->key[i + 1];
        }
        cursor->size--;
        //caso donde solo se tiene el 1 nodo
        if (cursor == root) {
            for (int i = 0; i < MAX + 1; i++) {
                cursor->ptr[i] = nullptr;
            }
            if (cursor->size == 0) {// caso donde solo se tenie un elemento y se destruye el arbol
                cout << "Tree died\n";
                delete[] cursor->key;
                delete[] cursor->ptr;
                delete cursor;
                root = nullptr;
            }
            return;
        }
        cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1];  // se disminuye el valor del puntero y se guarda el valor
        cursor->ptr[cursor->size + 1] = nullptr;    // el valor eleminado se vuele nullptr
        if (cursor->size >= (MAX + 1) / 2) {    // si el tamano del nodo eliminado es mayor a la condicion se acaba el delete
            return;
        }   // caso contrario se tiene que preguntar si el hermano del costado nos puede prestar
        if (leftSibling >= 0) {
            Node *leftNode = parent->ptr[leftSibling];
            if (leftNode->size >= (MAX + 1) / 2 + 1) { // se realiza el prestamo de valores y actualizaciion de los punteros y valores en el nodo padre
                for (int i = cursor->size; i > 0; i--) {
                    cursor->key[i] = cursor->key[i - 1];
                }
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = nullptr;
                cursor->key[0] = leftNode->key[leftNode->size - 1];
                leftNode->size--;
                leftNode->ptr[leftNode->size] = cursor;
                leftNode->ptr[leftNode->size + 1] = nullptr;
                parent->key[leftSibling] = cursor->key[0];
                return;
            }
        }   // caso donde el de la izquierda no nos puede prestar
        if (rightSibling <= parent->size) {
            Node *rightNode = parent->ptr[rightSibling];
            if (rightNode->size >= (MAX + 1) / 2 + 1) { // se realiza el prestamo de valores y actualizaciion de los punteros y valores en el nodo padre
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = nullptr;
                cursor->key[cursor->size - 1] = rightNode->key[0];
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
            for (int i = leftNode->size, j = 0; j < cursor->size; i++, j++) {
                leftNode->key[i] = cursor->key[j];
            }
            leftNode->ptr[leftNode->size] = nullptr;
            leftNode->size += cursor->size;
            leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
            removeInternal(parent->key[leftSibling], parent, cursor);
            delete[] cursor->key;
            delete[] cursor->ptr;
            delete cursor;
        } else if (rightSibling <= parent->size) {
            Node *rightNode = parent->ptr[rightSibling];
            for (int i = cursor->size, j = 0; j < rightNode->size; i++, j++) {
                cursor->key[i] = rightNode->key[j];
            }
            cursor->ptr[cursor->size] = nullptr;
            cursor->size += rightNode->size;
            cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
            cout << "Merging two leaf nodes\n";
            removeInternal(parent->key[rightSibling - 1], parent, rightNode);
            delete[] rightNode->key;
            delete[] rightNode->ptr;
            delete rightNode;
        }
    }
}


void BPTree::removeInternal(int x, Node *cursor, Node *child) {
    if (cursor == root) {
        //caso donde ya no se puede prestar del los hermanos y se tiene que eliminar el nodo si o si;
        if (cursor->size == 1) {
            if (cursor->ptr[1] == child) {
                delete[] child->key;
                delete[] child->ptr;
                delete child;
                root = cursor->ptr[0];
                delete[] cursor->key;
                delete[] cursor->ptr;
                delete cursor;
                cout << "Changed root node\n";
                return;
            } else if (cursor->ptr[0] == child) {
                delete[] child->key;
                delete[] child->ptr;
                delete child;
                root = cursor->ptr[1];
                delete[] cursor->key;
                delete[] cursor->ptr;
                delete cursor;
                cout << "Changed root node\n";
                return;
            }
        }
    }
    int pos;
    for (pos = 0; pos < cursor->size; pos++) {
        if (cursor->key[pos] == x) {
            break;
        }
    }
    for (int i = pos; i < cursor->size; i++) {
        cursor->key[i] = cursor->key[i + 1];
    }
    for (pos = 0; pos < cursor->size + 1; pos++) {
        if (cursor->ptr[pos] == child) {
            break;
        }
    }
    for (int i = pos; i < cursor->size + 1; i++) {
        cursor->ptr[i] = cursor->ptr[i + 1];
    }
    cursor->size--;
    if (cursor->size >= (MAX + 1) / 2 - 1) {
        return;
    }
    if (cursor == root)
        return;
    Node *parent = findParent(root, cursor);
    int leftSibling, rightSibling;
    for (pos = 0; pos < parent->size + 1; pos++) {
        if (parent->ptr[pos] == cursor) {
            leftSibling = pos - 1;
            rightSibling = pos + 1;
            break;
        }
    }
    if (leftSibling >= 0) {
        Node *leftNode = parent->ptr[leftSibling];
        if (leftNode->size >= (MAX + 1) / 2) {
            for (int i = cursor->size; i > 0; i--) {
                cursor->key[i] = cursor->key[i - 1];
            }
            cursor->key[0] = parent->key[leftSibling];
            parent->key[leftSibling] = leftNode->key[leftNode->size - 1];
            for (int i = cursor->size + 1; i > 0; i--) {
                cursor->ptr[i] = cursor->ptr[i - 1];
            }
            cursor->ptr[0] = leftNode->ptr[leftNode->size];
            cursor->size++;
            leftNode->size--;
            return;
        }
    }
    if (rightSibling <= parent->size) {
        Node *rightNode = parent->ptr[rightSibling];
        if (rightNode->size >= (MAX + 1) / 2) {
            cursor->key[cursor->size] = parent->key[pos];
            parent->key[pos] = rightNode->key[0];
            for (int i = 0; i < rightNode->size - 1; i++) {
                rightNode->key[i] = rightNode->key[i + 1];
            }
            cursor->ptr[cursor->size + 1] = rightNode->ptr[0];
            for (int i = 0; i < rightNode->size; ++i) {
                rightNode->ptr[i] = rightNode->ptr[i + 1];
            }
            cursor->size++;
            rightNode->size--;
            return;
        }
    }
    if (leftSibling >= 0) {
        Node *leftNode = parent->ptr[leftSibling];
        leftNode->key[leftNode->size] = parent->key[leftSibling];
        for (int i = leftNode->size + 1, j = 0; j < cursor->size; j++) {
            leftNode->key[i] = cursor->key[j];
        }
        for (int i = leftNode->size + 1, j = 0; j < cursor->size + 1; j++) {
            leftNode->ptr[i] = cursor->ptr[j];
            cursor->ptr[j] = nullptr;
        }
        leftNode->size += cursor->size + 1;
        cursor->size = 0;
        removeInternal(parent->key[leftSibling], parent, cursor);
    } else if (rightSibling <= parent->size) {
        Node *rightNode = parent->ptr[rightSibling];
        cursor->key[cursor->size] = parent->key[rightSibling - 1];
        for (int i = cursor->size + 1, j = 0; j < rightNode->size; j++) {
            cursor->key[i] = rightNode->key[j];
        }
        for (int i = cursor->size + 1, j = 0; j < rightNode->size + 1; j++) {
            cursor->ptr[i] = rightNode->ptr[j];
            rightNode->ptr[j] = nullptr;
        }
        cursor->size += rightNode->size + 1;
        rightNode->size = 0;
        removeInternal(parent->key[rightSibling - 1], parent, rightNode);
    }
}
void BPTree::display(Node *cursor) {
    if (cursor != nullptr) {
        for (int i = 0; i < cursor->size; i++) {
            cout << cursor->key[i] << " ";
        }
        cout << "\n";
        if (!cursor->IS_LEAF) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}
Node *BPTree::getRoot() {
    return root;
}

void BPTree::show_BPTree() {
    display(root);
}


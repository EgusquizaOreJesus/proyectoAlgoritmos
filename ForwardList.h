//
// Created by USER on 5/24/2023.
//

#ifndef PROYECTO_FORWARDLIST_H
#define PROYECTO_FORWARDLIST_H
template<typename T>
class ForwardList {
private:
    struct Node {
        T data;
        Node* next;

        Node(){
            next = nullptr;
            // TODO
        }

        explicit Node(T value){
            data = value;
            next = nullptr;
            // TODO
        }

        [[maybe_unused]]void killSelf(){
            delete this;
        }
    };

public:

    class FIterator
    {
    public:
        using reference = T&;
    private:
        Node* current;
        ForwardList<T>* array;

    public:
        FIterator(){
            current= new Node();
            current->next= nullptr;
        }

        explicit FIterator(Node* pos, ForwardList<T> *array = nullptr){
            current = pos;
            this->array = array;
        }

        bool operator != (const FIterator &other){
            return current != other.current;
        }

        FIterator& operator++(){
            this->current=current->next;
            return *this;
        }
        reference operator*(){
            return current->data;
        }
    };
    typedef FIterator iterator;
private:
    Node* head;
    int nodes;

public:
    ForwardList()  {
        head = nullptr;
        nodes = 0;
    }

    ~ForwardList(){
        delete head;
        // TODO
    }
    iterator begin(){

        return iterator(head, this);
    }
    iterator end(){
        return iterator(nullptr, this);
    }
    T front(){
        return head->data;
//            throw ("sin definir");
    }

    T back(){
        Node* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        return temp->data;
//            throw ("sin definir");
    }

    void push_front(T data){
        Node* nodo = new Node(data);
        if (is_empty()){
            head = nodo;
            head->next = nullptr;
        }
        else{
            nodo->next = head;
            head = nodo;
        }
        nodes++;
//            throw ("sin definir");
    }

    void push_back(T data){
        Node* nodo = new Node(data);
        if (head == nullptr){
            head = nodo;
            head->next = nullptr;
        }
        else{
            Node* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = nodo;
        }
        nodo->next = nullptr;
        nodes++;
//            throw ("sin definir");
    }

    T pop_front(){
        if (head == nullptr){
            return 0;
        }
        else{
            T val = head->data;
            Node* temp = head;
            head = head->next;
            delete temp;
            nodes--;
            return val;
        }
//            throw ("sin definir");
    }

    T pop_back(){
        if (head == nullptr){
            return 0;
        }
        else if (head->next == nullptr){
            T val = head->data;
            delete head;
            head = nullptr;
            nodes--;
            return val;
        }
        else{
            Node* temp = head;
            while (temp->next->next != nullptr){
                temp = temp->next;
            }
            T val = temp->next->data;
            delete temp->next;
            temp->next = nullptr;
            nodes--;
            return val;
        }
//            throw ("sin definir");
    }

    T insert(T data, int pos){
        if (is_empty() || pos>size()){
            push_back(data);
        }
        else if (pos == 1){
            push_front(data);
        }
        else{
            Node* nodo = new Node();
            nodo->data = data;
            Node* temp  = head;
            int i = 1;
            while (i++<pos-1){
                temp = temp->next;
            }
            nodo->next = temp->next;
            temp->next = nodo;
            nodes++;
        }
        return data;
//            throw ("sin definir");
    }

    bool remove(int pos){
        if (pos>nodes){
            return false;
        }
        else if (pos == 1){
            pop_front();
            nodes--;
            return true;
        }
        else{
            Node* temp  = head;
            int i = 1;
            while (i++<pos-1){
                temp = temp->next;
            }
            temp->next = temp->next->next;
            nodes--;
            return true;
        }
//            throw ("sin definir");
    }

    T& operator[](int pos){
        if (pos == 1){
            return head->data;
        }
        else{
            Node* temp  = head;
            int i = 1;
            while (i++<pos-1){
                temp = temp->next;
            }
            return temp->next->data;
        }
//            throw ("sin definir");
    }

    bool is_empty(){
        return head == nullptr;
//            throw ("sin definir");
    }

    int size(){
        return nodes;
//            throw ("sin definir");
    }

    void clear(){
        while (head != nullptr){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
//            throw ("sin definir");
    }

};

#endif //PROYECTO_FORWARDLIST_H

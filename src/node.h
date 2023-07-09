//
// Created by USER on 5/29/2023.
//

#ifndef PROYECTOALGORITMOS_NODE_H
#define PROYECTOALGORITMOS_NODE_H
#include <iostream>
#include "transaccion.h"
#include "vector"
using namespace std;

template <typename TK>
struct Node {
    // array de keys
    TK* keys;
    // array de punteros a hijos
    Node** children;
    // cantidad de keys
    int count;
    // indicador de nodo hoja
    bool leaf;

    Node() : keys(nullptr), children(nullptr), count(0), leaf(true) {}
    Node(int M, bool _leaf = true) {
        this->keys = new TK[M-1];
        this->children = new Node<TK>*[M];
        for(int i=0; i < M; i++){
            this->children[i] = nullptr;
        }
        this->count = 0;
        this->leaf = _leaf;
    }
    template<typename T>
    void range_2(T start, T end, vector<TK>& result) {
        int i = 0;
        while (i < count && comparador::isMenor(start,keys[i]))
            ++i;
        if (leaf) {
            while (i < count && comparador::isMenorIgual(end,keys[i])) {
                result.push_back(keys[i]);
                ++i;
            }
        } else {
            while (i < count && comparador::isMenorIgual(end,keys[i])) {
                children[i]->range_2(start, end, result);
                result.push_back(keys[i]);
                ++i;
            }
            children[i]->range_2(start, end, result);
        }
    }
    vector<TK> range_search(string begin, string end) {
        vector<TK> result;
        range_2(begin, end, result);

        return result;
    }

    vector<TK> range_search(double begin, double end) {
        vector<TK> result;
        range_2(begin, end, result);

        return result;
    }

    int insert(TK value) {
        int i = this->count - 1;
        for(; i >= 0; i--){
            if(comparador::isMenor(this->keys[i],value)){
                break;
            }else{
                this->keys[i+1] = this->keys[i];
            }
        }
        this->keys[i + 1] = value;
        (this->count)++;
        return i+1;
    }

    int insert(Node<TK>* node, int M, Node<TK>* cmp) {
        int i = M - 1;
        for(; i >= 0; i--){
            if(children[i] == cmp){
                break;
            }else{
                this->children[i+1] = this->children[i];
            }
        }
        this->children[i + 1] = node;
        return i+1;
    }

    void print(){
        for(int i = 0; i < this->count; i++){
            cout<<this->keys[i]<<" ";
        }
        cout<<endl;
    }

    void killSelf() {
        for(int i = 0; i<= this->count; i++){
            if(this->children[i] != nullptr){
                this->children[i]->killSelf();
            }
        }
        if(this->keys != nullptr) delete[] this->keys;
        if(this->children[0] == nullptr) delete[] this->children;
        delete this;
    }

    void display(const string& sep = ",") {
        int i;
        for(i = 0; i < count; i++){
            if(children[i] != nullptr){
                children[i]->display();
            }
            cout<<keys[i]<<sep;
        }
        if(children[i] != nullptr){
            children[i]->display();
        }
    }

    void toString(string& result, const string& sep = ",") {
        int i;
        for(i = 0; i < count; i++){
            if(children[i] != nullptr){
                children[i]->toString(result, sep);
            }
            result += std::to_string(keys[i]) + sep;
        }
        if(children[i] != nullptr){
            children[i]->toString(result, sep);
        }
    }

    void display_keys(const string& sep = ",") {
        int i;
        for(i = 0; i < count; i++){
            cout<<keys[i]<<sep;
        }
    }


    void remove(int idx){
        for (;idx<count-1; idx++){
            this->keys[idx] = this->keys[idx+1];
        }
        this->count = this->count-1;
    }

    void remove(int idx, int M){
        for (;idx<=count; idx++){
            this->children[idx] = this->children[idx+1];
        }
        for (int i = this->count + 1; i < M; i++){
            this->children[i] = nullptr;
        }
    }
};
#endif //PROYECTOALGORITMOS_NODE_H

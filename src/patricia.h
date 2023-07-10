//
// Created by USER on 7/7/2023.
//

#ifndef PRUEBA_PATRICIA_H
#define PRUEBA_PATRICIA_H
#include <iostream>
#include "boyer.h"
using namespace std;
const unsigned ALPHA_SIZE = 27;
class TriePatricia {
private:
    struct TrieNode{
        string  suffix;
        TrieNode** children;
        bool end_of_word;
        int position;

        TrieNode():  end_of_word(false)
        { children= new TrieNode * [ALPHA_SIZE];

            for (int i = 0; i < ALPHA_SIZE; ++i) {
                children[i]= nullptr;
            }
        }
        explicit TrieNode(string nueva ): suffix(std::move(nueva)), end_of_word(false)
        { children= new TrieNode * [ALPHA_SIZE];
            for (int i = 0; i < ALPHA_SIZE; ++i) {
                children[i]= nullptr;
            }
        }
    };
    TrieNode* root;
public:

    TriePatricia(){
        root = new TrieNode();
    }
    void insert( const string& new_word  ) {

        int idx= get_index(new_word);
        cout << idx << endl;
        cout << "insert block" << endl;
        insert(new_word,0,root->children[idx]);
    }

    void insert(string new_word , int posF , TrieNode* &current){
        if(current== nullptr)
        {
            current= new TrieNode(new_word);
            current->end_of_word= true;
        } else {
            int i=posF;
            int m=int(new_word.size()); // tam de la nueva palabra
            while (i<m or i<current->suffix.size())
            {
                if(new_word[i]!=current->suffix[i])
                    break;
                i++;
            }
            posF=i;
            string new_excess , old_excess , coincidence;
            coincidence=current->suffix.substr(0,posF);
            new_excess=new_word.substr(posF,m);
            old_excess=current->suffix.substr(posF,current->suffix.size());

            current->suffix=coincidence;
            if (!old_excess.empty()) {
                auto* new_node = new TrieNode(old_excess);
                new_node->end_of_word = current->end_of_word;
                current->end_of_word = false;

                for (int j = 0; j < ALPHA_SIZE; ++j) {
                    if (current->children[j] != nullptr) {
                        new_node->children[j] = current->children[j];
                        current->children[j] = nullptr;
                    }
                }

                current->children[get_index(old_excess)] = new_node;

            }
            if(!new_excess.empty())
            {
                insert(new_excess,0,current->children[get_index(new_excess)]);
            }
            if (new_excess.empty())
                current->end_of_word = true;
        }
    }
    bool search(string key) {
        return search(std::move(key) , root);
    }

    vector<string> contains(const string pattern ){


        string palabras=toString("-");
        vector<int> posi= BoyerMoore(palabras,pattern);
        vector<string> nombres;
        for(auto p: posi) {
            int start = p;
            int end = p;

            // Encuentra el inicio de la palabra.
            while(start >= 0 && palabras[start] != '-') {
                start--;
            }

            // Encuentra el final de la palabra.
            while(end < palabras.size() && palabras[end] != '-') {
                end++;
            }

            // Extrae la palabra completa.
            string word = palabras.substr(start+1, end-start-1);
            nombres.push_back(word);
        }
        return nombres;

    }


    vector<string>search_start_with(const string & empieza){
        bool  to_erase_later= false;
        if(!search(empieza))
        {
            insert(empieza);
            to_erase_later= true;
        }

        auto * guia = new TrieNode;

        search_support(empieza,root , guia);
        vector<string > coincidences;
        string parent= empieza.substr(0,empieza.size()-guia->suffix.size());
        toString_support("", guia, parent , coincidences);

        if(to_erase_later)
        {
            remove(empieza);
            coincidences.erase(coincidences.begin());
            return coincidences;
        }else{
            return coincidences;
        }

    }

    void search_support(string key , TrieNode* current , TrieNode* & guia ) {

        if (current == nullptr)
            return;
        else {
            int i = 0;
            int m = int(key.size()); // tam de la palabra a buscar
            int n = int(current->suffix.size());
            while (i < m or i < current->suffix.size()) {
                if (key[i] != current->suffix[i])
                    break;
                i++;
            }
            string to_find_excess = key.substr(i, m);
            string to_find_old_excess = current->suffix.substr(i, n);

            if (to_find_excess.empty() and to_find_old_excess.empty()) {
                guia=current;
            } else if (!to_find_excess.empty() and to_find_old_excess.empty())
                search_support(to_find_excess, current->children[get_index(to_find_excess)],guia);

            return;
        }
    }
    void toString_support(const string& sep, TrieNode* current, const string& parent , vector<string>& cosas) {
        string new_word;
        if (current->end_of_word) {
            new_word += parent + current->suffix+sep;

            cosas.push_back(new_word);
        }
        for (int i = 0; i < ALPHA_SIZE; ++i) {
            if (current->children[i] != nullptr) {

                toString_support(sep, current->children[i], parent + current->suffix,cosas);
            }
        }


    }
    bool search(string key , TrieNode* current ){

        if(current== nullptr)
            return false;
        else{
            int i=0;
            int m=int(key.size()); // tam de la palabra a buscar
            int n=int(current->suffix.size());
            while (i<m or i<current->suffix.size())
            {
                if(key[i]!=current->suffix[i])
                    break;
                i++;
            }
            string to_find_excess=key.substr(i,m);
            string to_find_old_excess=current->suffix.substr(i,n);

            if(to_find_excess.empty() and to_find_old_excess.empty())
            {
                return current->end_of_word ;
            }
            else if(!to_find_excess.empty() and to_find_old_excess.empty()) return search(to_find_excess , current->children[get_index(to_find_excess)]);

            return false;
        }
    }

    void remove(string key) {
        remove(std::move(key) , root);
    }
    void remove(string key , TrieNode* & current){
        if(current== nullptr)
            return ;
        else{
            int i=0;
            int m=int(key.size()); // tam de la palabra a buscar
            while (i<m or i<current->suffix.size())
            {
                if(key[i]!=current->suffix[i])
                    break;
                i++;
            }
            string to_remove_excess=key.substr(i,m);
//            cout<<"ENTRO  "<<to_remove_excess<<"  "<<current->suffix<<endl;
            if(to_remove_excess.empty())
            {

                int cont=0;
                for (int j = 0; j < ALPHA_SIZE; ++j) if(current->children[j] != nullptr)cont++;
                if(cont==0)
                {
                    current->end_of_word= false;
                    current= nullptr;
                }else current->end_of_word= false;
            }
            else remove(to_remove_excess , current->children[get_index(to_remove_excess)]);

            //En el regreso de la recursion se compacta si es necesario

            if(current!= nullptr)
            {
                int cont=0;
                int pos=-1;

                for (int j = 0; j < ALPHA_SIZE; ++j)
                {
                    if(current->children[j] != nullptr)
                    {
                        cont++;
                        pos=j;
                    }
                }
                if(cont==1 and !current->end_of_word)
                {

                    current->suffix+=current->children[pos]->suffix;
                    for (int k = 0; k < ALPHA_SIZE; ++k) {
                        if(current->children[pos]->children[k] != nullptr)
                            current->children[k]=current->children[pos]->children[i];
                    }
                    current->end_of_word= true;
                    current->children[pos]->end_of_word= false;
                    current->children[pos]= nullptr;
                }
            }
        }
    }
    string toString(const string& sep) {
        return toString(sep,root,"");
    }
    string toString(const string& sep, TrieNode* current, const string& parent) {
        string new_word;
        if (current->end_of_word) {
            new_word += parent + current->suffix+sep;

        }
        for (int i = 0; i < ALPHA_SIZE; ++i) {
            if (current->children[i] != nullptr) {

                new_word +=  toString(sep, current->children[i], parent + current->suffix);
            }
        }

        return new_word;
    }

private:

    static bool is_upper(char c){
        return c>='A' and c <='[';
    }
    static bool is_lower(char c){
        return c>='a' and c <='{';
    }

    static int get_index(string word)
    {
        if(is_upper(word[0]))
            return word[0]-'A';

        if(is_lower(word[0]))
            return word[0]-'a';


        return -1;
    }
};
#endif //PRUEBA_PATRICIA_H
//
// Created by USER on 5/29/2023.
//

#ifndef PROYECTOALGORITMOS_BLOCKCHAIN_H
#define PROYECTOALGORITMOS_BLOCKCHAIN_H
#include <utility>
#include "hash.h"
#include "ForwardList.h"
#include "ChainHash.h"
#include "transaccion.h"

int mine( int nonce, const string& data , string challenge)
{
    string hashcode= sha256(data +to_string(nonce));
    int size = challenge.size();
    while (true)
    {
        hashcode= sha256(data +to_string(nonce));
        nonce++;
        if(hashcode.substr(0, size)==challenge)
            break;

    }
    //cout<<hashcode<<endl;
    return nonce;

}

struct block{
    int id;
    string data;
    vector<transaccion> data2;
    string  prev_hash;
    string  current_hash;
    int nonce;
    string signature_string="0000";
    block(){}
    explicit block(int previd , const vector<transaccion>& datos, const string& previo){
        string algo=string (64, '0');
        prev_hash=(previd==0)?(algo):(previo);
        id=++previd;
        for(const auto& e:datos){
            data += e.emisor +","+ e.receptor +","+ to_string(e.monto) +","+ to_string(e.fechatransaccion.dia) +","+  to_string(e.fechatransaccion.mes) + ","+ to_string(e.fechatransaccion.anio) + "\n";
        }
        data2=datos;
        nonce= mine(0,data+prev_hash,signature_string)-1;
        current_hash= sha256(data+prev_hash+ to_string(nonce));

    }
    block(const block& copy)
    {
        this->id=copy.id;
        data=copy.data;
        for (auto v:copy.data2) {
            this->data2.push_back(v);
        }
        prev_hash=copy.prev_hash;
        current_hash=copy.current_hash;
        nonce=copy.nonce;
    }
    void re_data(){
        data.clear();
        for(const auto& e:data2){
            data += e.emisor +","+ e.receptor +","+ to_string(e.monto) +","+ to_string(e.fechatransaccion.dia) +","+  to_string(e.fechatransaccion.mes) + ","+ to_string(e.fechatransaccion.anio) + "\n";
        }
    }
    void self_hash()
    {
        nonce= mine(0,data+prev_hash,signature_string)-1;
        current_hash= sha256(data+prev_hash+ to_string(nonce));
    }

    void setPrevHash(const string &prevHash) {
        prev_hash = prevHash;
    }

    template<typename T>
    void edit_transaction(int index,const T& edit,bool emisor= false){
        if constexpr(is_same_v<double,T>){
            data2[index-1].monto = edit;
            re_data();
        }
        else{
            if (emisor){
                data2[index-1].emisor = edit;
                re_data();
            }
            else{
                data2[index-1].receptor = edit;
                re_data();
            }
        }
    }

    void printblock(){
        cout<<"ID :"<<id<<endl;
        cout<<"NONCE :"<<nonce<<endl;
        cout<<endl;
        cout<<data<<endl;
        cout<<endl;
        cout<<"PREV_HASH :"<<prev_hash<<endl;
        cout<<"CURRENT_HASH :"<<current_hash<<endl;
        cout<<endl;
    }


};
class blockchain{
private:
    //ForwardList<block*> blockchain_;
    int id;
    ChainHash<int,block*> block_references;

public:
    blockchain(const vector<transaccion>& data){
        id=1;
        auto* new_block= new block(0,data,"");
        block_references.insert(make_pair(new_block->id,new_block));
    }
    blockchain(const blockchain& other) {
        // cout<<"USANDO CONSTRUCT COPIA"<<endl;
        id = other.id;

        for (int i = 1; i <= id; ++i) {
            auto nuevo= other.block_references[i];
            auto* block_copy = new block(*nuevo);
            block_references.insert(make_pair(block_copy->id, block_copy));
        }
    }
    void insert_block_with_transaction(const vector<transaccion>& data){
        //block * current_block = blockchain_.front();
        block * current_block=block_references[id++];
        auto * new_block =new block(current_block->id ,data , current_block->current_hash);
        block_references.insert(make_pair(new_block->id,new_block));
        //blockchain_.push_front(new_block);
    }
    void insert_block(block * new_block2){
        //block * current_block = blockchain_.front();
        block * current_block=block_references[id++];
        new_block2 =new block(current_block->id ,current_block->data2 , current_block->current_hash);
        block_references.insert(make_pair(id,new_block2));



    }

    void view_blockChain(){
        for (int i = 1; i <= id; ++i)
            block_references[i]->printblock();
    }

    template<typename T>
    void edit_block(int index_b , int index_t ,const T& dato ,bool emisor = false){
        block_references[index_b]->edit_transaction(index_t,dato,emisor);
//        block_references[index_b]=std::move(dato);
        block_references[index_b]->self_hash();
        string current_hash = block_references[index_b]->current_hash;
        for (int i = index_b+1; i <= id ; ++i) {
            block_references[i]->prev_hash = current_hash;
            block_references[i]->self_hash();
            current_hash = block_references[i]->current_hash;
        }
    }
    string last_hash_code()
    {
        return block_references[id]->current_hash;
    }
    auto find_block(int index){

        if(!block_references.contains(index))
        {
            cout<<"Block not found ...";

        } else {

            block_references[index]->printblock();
            return block_references[index];
        }

    }
    void etc(){
        cout << block_references.getsize();
    }
    bool isblock(int index){
        if(!block_references.contains(index))
        {
            return false;
        }
        return true;
    }

    vector<transaccion> search(const string& data,eleccion a){
        vector<transaccion> result;
        for (int i = 1; i <= this->block_references.getsize(); ++i) {
            for (const auto& trans: block_references[i]->data2) {
                if (a == receptor){
                    if (data == trans.receptor){
                        result.push_back(trans);
                    }
                }
                else if (a == emisor){
                    if (data == trans.emisor){
                        result.push_back(trans);
                    }
                }

                else if (a == fechaX){
                    if (comparador::igualdad(data,trans)){
                        result.push_back(trans);
                    }
                }
            }
        }
        return result;

    }

    vector<transaccion> search(double data){
        vector<transaccion> result;
        for (int i = 1; i <= this->block_references.getsize(); ++i) {
            for (const auto& trans: block_references[i]->data2) {
                if (trans.monto == data){
                    result.push_back(trans);
                }
            }
        }
        return result;

    }

    vector<transaccion> search(double data,int index){
        vector<transaccion> result;
        if (isblock(index)){
            for (const auto& trans: block_references[index]->data2) {
                if (trans.monto == data){
                    result.push_back(trans);
                }
            }
        }
        return result;
    }
    int getLastBlockId(){
        return id;
    }

};
#endif //PROYECTOALGORITMOS_BLOCKCHAIN_H

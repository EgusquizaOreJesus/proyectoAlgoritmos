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
struct block{
    int id;
    string data;
    vector<transaccion> data2;
    string  prev_hash;
    string  current_hash;
    int nonce;
    block(){}
    block(int previd , const vector<transaccion>& datos, const string& previo){
        string algo=string (64, '0');
        prev_hash=(previd==0)?(algo):(previo);
        id=++previd;
        for(const auto& e:datos){
            data += e.emisor +","+ e.receptor +","+ to_string(e.monto) +","+ to_string(e.fechatransaccion.dia) +","+  to_string(e.fechatransaccion.mes) + ","+ to_string(e.fechatransaccion.anio) + "\n";
        }
        data2=datos;
        nonce= mine(0,data+prev_hash)-1;
        current_hash= sha256(data+prev_hash+ to_string(nonce));

    }
    void re_data(){
        data.clear();
        for(const auto& e:data2){
            data += e.emisor +","+ e.receptor +","+ to_string(e.monto) +","+ to_string(e.fechatransaccion.dia) +","+  to_string(e.fechatransaccion.mes) + ","+ to_string(e.fechatransaccion.anio) + "\n";
        }
    }
    void self_hash()
    {
        nonce= mine(0,data+prev_hash)-1;
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
    int mine( int nonce, const string& data )
    {
        string hashcode= sha256(data +to_string(nonce));
        while (true)
        {
            hashcode= sha256(data +to_string(nonce));
            nonce++;
            if(hashcode.substr(0, 3)=="000")
                break;

        }
        //cout<<hashcode<<endl;
        return nonce;

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
    explicit blockchain(const vector<transaccion>& data){
        id=1;
        auto* new_block= new block(0,data,"");
        block_references.insert(make_pair(new_block->id,new_block));
    }

    void insert_block(const vector<transaccion>& data){
        //block * current_block = blockchain_.front();
        block * current_block=block_references[id++];
        auto * new_block =new block(current_block->id ,data , current_block->current_hash);
        block_references.insert(make_pair(new_block->id,new_block));
        //blockchain_.push_front(new_block);
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
    void find_block(int index){

        if(!block_references.contains(index))
        {
            cout<<"Block not found ...";
        } else {

            block_references[index]->printblock();
        }

    }


};
#endif //PROYECTOALGORITMOS_BLOCKCHAIN_H

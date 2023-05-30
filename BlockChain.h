//
// Created by USER on 5/29/2023.
//

#ifndef PROYECTOALGORITMOS_BLOCKCHAIN_H
#define PROYECTOALGORITMOS_BLOCKCHAIN_H
#include <utility>
#include "hash.h"
#include "ForwardList.h"
#include "ChainHash.h"
struct block{
    int id;
    string data;
    string  prev_hash;
    string  current_hash;
    int nonce;

    block(int previd , string datos, string previo){
        string algo=string (64, '0');
        prev_hash=(previd==0)?(algo):(previo);
        id=++previd;
        data=datos;
        nonce= mine(0,datos+prev_hash)-1;
        current_hash= sha256(datos+prev_hash+ to_string(nonce));

    }

    void self_hash()
    {
        nonce= mine(0,data+prev_hash)-1;
        current_hash= sha256(data+prev_hash+ to_string(nonce));
    }

    void setPrevHash(const string &prevHash) {
        prev_hash = prevHash;
    }

    int mine( int nonce, const string& data )
    {
        string hashcode= sha256(data +to_string(nonce));
        while (true)
        {
            hashcode= sha256(data +to_string(nonce));
            nonce++;
            if(hashcode.substr(0, 4)=="0000")
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
    explicit blockchain(string data){
        id=1;
        auto* new_block= new block(0,std::move(data),"");
        block_references.insert(make_pair(new_block->id,new_block));
        // blockchain_.push_front(new_block);
    }

    void insert_block(string data){
        //block * current_block = blockchain_.front();
        block * current_block=block_references[id++];
        auto * new_block =new block(current_block->id ,std::move(data) , current_block->current_hash);
        block_references.insert(make_pair(new_block->id,new_block));
        //blockchain_.push_front(new_block);
    }
    void view_blockChain(){
        for (int i = 1; i <= id; ++i)
            block_references[i]->printblock();
    }

    void edit_block(int index_b , int index_t ,string dato ){

        block_references[index_b]->data=std::move(dato);
        block_references[index_b]->self_hash();
        for (int i = index_b+1; i < id ; ++i) {

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

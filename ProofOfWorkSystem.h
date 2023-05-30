//
// Created by USER on 5/30/2023.
//

#ifndef PROYECTOALGORITMOS_PROOFOFWORKSYSTEM_H
#define PROYECTOALGORITMOS_PROOFOFWORKSYSTEM_H
#include<string>
#include "BlockChain.h"
using namespace  std;
class peers{

private:
    blockchain  block_chain_copy;
public:
    const blockchain &getBlockChainCopy() const {
        return block_chain_copy;
    }

    explicit peers(const blockchain new_block ): block_chain_copy(new_block){

    }
    void display_blocks()
    {
        block_chain_copy.view_blockChain();
    }

    void find_block(int index)
    {
        block_chain_copy.find_block(index);
    }
    template<typename T>
    void change_own_blockchain(int block_index ,int transacction_index,T new_transaccion , bool emisor= false)
    {
        block_chain_copy.edit_block(block_index ,transacction_index , new_transaccion , emisor);
    }

    string final_block_hash()
    {
        return block_chain_copy.last_hash_code();
    }
};

class User_net{

private:
    blockchain shared_block_chain;
    string signature_hash_code;
    vector<peers*> users;
    int user_number;

public:
    User_net(const blockchain &sharedBlockChain,  int userNumber) : shared_block_chain(
            sharedBlockChain), user_number(userNumber) {
        signature_hash_code=shared_block_chain.last_hash_code();
        for (int i = 0; i < user_number; ++i) {
            users.push_back(new peers(shared_block_chain));
        }
    }

    void performProofOfWork(block* new_block) {
        string data = new_block->data + new_block->prev_hash;
        int nonce = 0;
        nonce = mine(nonce, data,"00000");
        string current_hash = sha256(data + to_string(nonce));
        cout<<"with a proof of work with signature 00000 and after "<<nonce<<" tries new block was accepted ..."<<endl;
    }

    void addBlock(const vector<transaccion>& data) {
        block* new_block = new block(shared_block_chain.getLastBlockId() ,data ,shared_block_chain.last_hash_code());
        performProofOfWork(new_block);
        shared_block_chain.insert_block(new_block);
    }
    template<typename T>
    void alter_transaction(int user_id,int block_index ,int transacction_index,T new_transaccion , bool emisor= false ){

        users[user_id]->change_own_blockchain(block_index,transacction_index,new_transaccion , emisor );
    }

    bool is_change_valid(int user_id){
        int half_plus_one=0;
        int actual_signature=0;
        string current_user_hash=users[user_id]->final_block_hash();
        for (int i = 0; i < user_number; ++i) {
            if(users[i]->final_block_hash()==current_user_hash)
                half_plus_one++;
            if(users[i]->final_block_hash()==signature_hash_code)
                actual_signature++;
        }
        cout<<half_plus_one<<endl;

        if(half_plus_one>=(user_number/2)+1 and half_plus_one>actual_signature)
        {
            signature_hash_code=current_user_hash;
            shared_block_chain=users[user_id]->getBlockChainCopy();
            return true;
        }else return false;
    }
    void view_shared_block()
    {
        shared_block_chain.view_blockChain();
    }
    void view_block_chain_by_id(int user_id)
    {
        users[user_id]->display_blocks();
    }

    void view_codes(){
        for (int i = 0; i < user_number; ++i) {
            cout<<"ID:"<<i+1<<users[i]->final_block_hash()<<endl;
        }
    }
};

#endif //PROYECTOALGORITMOS_PROOFOFWORKSYSTEM_H

#include <iostream>
#include "BlockChain.h"
#include "Btree.h"

using namespace std;

class peers{

private:
    blockchain  block_chain_copy;
public:

    explicit peers(const blockchain& new_block ): block_chain_copy(new_block){

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
    void change_own_blockchain(int block_index ,int transacction_index,T new_transaccion )
    {
        block_chain_copy.edit_block(block_index ,transacction_index , new_transaccion);
    }

    string final_block_hash()
    {
        return block_chain_copy.last_hash_code();
    }
};



int main() {
   // blockchain alfa("transaccion 1");
//    alfa.insert_block("transaccion 2");
//    alfa.insert_block("transaccion 3");
//    alfa.insert_block("transaccion 4");
//    alfa.insert_block("transaccion 5");
//    alfa.insert_block("transaccion 6");
//    alfa.insert_block("transaccion 7");
//    alfa.insert_block("transaccion 7");
//    alfa.insert_block("transaccion 7");
//    alfa.insert_block("transaccion 7");
//    alfa.insert_block("transaccion 7");
//    alfa.insert_block("transaccion 7");
//    alfa.insert_block("transaccion 7");
//    alfa.view_blockChain();
////        cout<<"LA BUSQUEDA ES"<<endl;
////    alfa.find_block(12);
//    peers user1(alfa);
//    cout<<"ULTIMO HASH DEL USER ES :"<<user1.final_block_hash()<<endl;
//    user1.change_own_blockchain(11,0,"EDITADO BY LOLI");
//    cout<<"ULTIMO HASH DEL USER ES again:"<<user1.final_block_hash();



    return 0;
}
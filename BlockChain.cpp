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
    vector<transaccion> total;
    transaccion a(100,"Jesus","Chavez",20,10,2022);
    transaccion b(200,"Jesus","Chavez",21,10,2022);
    transaccion c(200,"Jesus","Chavez",22,10,2022);
    transaccion d(200,"Jesus","Chavez",23,10,2022);
    transaccion e(200,"Jesus","Chavez",24,10,2022);
    transaccion f(200,"Jesus","Chavez",25,10,2022);
    transaccion g(200,"Jesus","Chavez",26,10,2022);

    total.push_back(a);
    total.push_back(b);
    total.push_back(c);
    total.push_back(d);
    total.push_back(e);
    total.push_back(f);
    vector<transaccion> trans2{a,c,f};
    vector<transaccion> trans3{a,b,c};
    vector<transaccion> trans4{a,b,c,g};

    blockchain alfa(total);
    alfa.insert_block(trans2);
    alfa.insert_block(trans3);
    alfa.view_blockChain();
    alfa.edit_block(1,6,500.0);
    alfa.view_blockChain();
    alfa.insert_block(trans4);
    alfa.view_blockChain();
    alfa.edit_block(2,2,"Pedro", true);
    alfa.view_blockChain();

    //    alfa.insert_block(total);
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
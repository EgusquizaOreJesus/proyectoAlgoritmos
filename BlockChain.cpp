#include <iostream>
#include "BlockChain.h"
#include "Btree.h"

#include "ProofOfWorkSystem.h"
using namespace std;




int main() {
    vector<transaccion> total;
    transaccion a(100,"Jesus","Chavez",20,10,2022);
    transaccion b(200,"Chambilla","Chavez",21,10,2022);
    transaccion c(300,"Mai ","Hermes",22,10,2022);
    transaccion  d(400,"Miguel","Chavez",30,10,2022);
    transaccion e(500,"Pedro","Chavez",24,10,2022);
    transaccion f(150,"Benjamin","Chavez",25,10,2022);
    transaccion g(700,"Joaquin","Chavez",26,10,2022);

    total.push_back(a);
    total.push_back(b);
    total.push_back(c);
    total.push_back(d);
    total.push_back(e);
    total.push_back(f);
    vector<transaccion> trans2{a,c,f};
    vector<transaccion> trans3{a,b,c};
    vector<transaccion> trans4{a,b,c,g};
    vector<transaccion> transM{c,d,e};





    blockchain alfa(total);
    alfa.insert_block_with_transaction(trans2);
    alfa.insert_block_with_transaction(trans3);
    alfa.insert_block_with_transaction(trans4);


//    User_net peers(alfa,4);
//    alfa.view_blockChain();
//    peers.view_shared_block();
//    cout<<"------------------------------USER BLOCK CHAIN ORIGINAL------------------------------"<<endl;
//        alfa.view_blockChain();
//    peers.alter_transaction(2,2,1,"Yashajin_Ai",true);
//    cout<<"------------------------------USER BLOCK CHAIN ALTERED-------------------------------"<<endl;
//    peers.view_block_chain_by_id(2);
//    peers.view_codes();
//    cout<<boolalpha<<peers.is_change_valid(2)<<endl;
//    cout<<"------------------------------PROOF OF WORK TO ADD BLOCK------------------------------"<<endl;
//    peers.addBlock(transM);
//    peers.view_shared_block();
    BTree<transaccion> alfa2(3);
    alfa2.insert(a);
    alfa2.insert(b);
    alfa2.insert(c);
    alfa2.insert(d);
    alfa2.insert(e);
    alfa2.insert(f);
    alfa2.insert(g);

auto v = alfa2.range_searching("22/10/2022","30/10/2022");


    cout << "tamano: "<< v.size() << endl;
    for(const auto& x:v){
        cout << "emisor: " <<x.emisor << endl;
    }

//    auto v = alfa.search("21/10/2022" ,fechaX);
//    for(const auto& x:v){
//        x.display();
//        cout << endl;
//    }
    return 0;
}
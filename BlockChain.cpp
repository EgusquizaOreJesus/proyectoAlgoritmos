#include <iostream>
#include "transaccion.h"
#include "BlockChain.h"
#include "Btree.h"
//#include "BPPtree.h"
#include "patricia.h"
#include "boyer.h"
using namespace std;



int main() {
    vector<transaccion> total;
    transaccion a(100,"jesus","chavez",20,10,2022);
    transaccion b(200,"chambilla","chavez",21,10,2022);
    transaccion c(300,"mai","hermes",22,10,2022);
    transaccion  d(400,"miguel","chavez",30,10,2022);
    transaccion e(500,"pedro","chavez",24,10,2022);
    transaccion f(150,"chanchumaru","heider",25,10,2022);
    transaccion g(700,"joaquin","hitler",26,10,2022);

    total.push_back(a);
    total.push_back(b);
    total.push_back(c);

    total.push_back(e);
    total.push_back(f);
    total.push_back(g);
    vector<transaccion> trans2{a,c,f};
    vector<transaccion> trans3{a,b,c,d};
    vector<transaccion> trans4{a,b,c,g};
    vector<transaccion> transM{c,d,e,g,g,g,g,g,g,g};



        blockchain alfa(total);
        alfa.insert_block_with_transaction(trans2);
        alfa.insert_block_with_transaction(trans3);
        alfa.insert_block_with_transaction(trans4);

      alfa.view_blockChain();
        auto pera = alfa.getUsuarios();

//    BPTree<Monto> montos;
//    for(auto v:total )
//    {
//        Monto nuevo;
//        nuevo.monto=v.monto;
//        nuevo.index_bloque=1;
//        montos.insert(nuevo);
//    }
//
//    auto maxi=montos.found_max();
//    cout<<maxi.monto;






//    block alfa(0,transM,"");
//    alfa.printblock();
//    alfa.edit_transaction(4,"Yashajin_Ai",true);
//    alfa.self_hash_invalido();
//    alfa.printblock();
//    alfa.self_hash();
//    alfa.printblock();

    ////
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
//    BTree<transaccion> alfa2(3);
//    alfa2.insert(a);
//    alfa2.insert(b);
//    alfa2.insert(c);
//    alfa2.insert(d);
//    alfa2.insert(e);
//    alfa2.insert(f);
//    alfa2.insert(g);
//
////    vector<transaccion> asdf = alfa2.range_searching(100,500)
////    for(auto a: asdf){
////        cout << a <<  " ";
////    }
//auto v = alfa2.range_searching(100,400);
//
//
//
//
//    cout << "tamano: "<< v.size() << endl;
//    for(const auto& x:v){
//        cout << "emisor: " <<x.emisor << endl;
//    }

//    auto v = alfa.search("21/10/2022" ,fechaX);
//    for(const auto& x:v){
//        x.display();
//        cout << endl;
//    }
//
//    string cosa = "{jose{carlos{joaquin{";
    // Position of suffixes in word
    // a (5)
    // na (4)
    // ana (3)
    // nana (2)
    // anana(1)
    // banana (0)
//
//    TriePatricia alfa;
//    alfa.insert("chambilla");
//    alfa.insert("chavez");
//    alfa.insert("miguel");
//    alfa.insert("jesus");
//    alfa.insert("joaquin");
//    alfa.insert("pedro");
//    alfa.insert("mai");
//    alfa.insert("hermes");
//    alfa.insert("loligoth");
//    alfa.insert("loliyami");
//    alfa.insert("lolipregnant");
//    alfa.insert("lolisegs");
//    alfa.insert("lolicoito");
//    auto coincidences=alfa.search_start_with("loli");
//    for(auto palabras :coincidences)
//        cout<<palabras<<endl;

//   cout<<alfa.toString("-");
//
//    string palabras=alfa.toString("-");
//   vector<int> posi= BoyerMoore(palabras,"ier");
//   cout<<endl;
//   cout<<endl;
//    vector<string> nombres;
//    for(auto p: posi) {
//        int start = p;
//        int end = p;
//
//        // Encuentra el inicio de la palabra.
//        while(start >= 0 && palabras[start] != '-') {
//            start--;
//        }
//
//        // Encuentra el final de la palabra.
//        while(end < palabras.size() && palabras[end] != '-') {
//            end++;
//        }
//
//        // Extrae la palabra completa.
//        string word = palabras.substr(start+1, end-start-1);
//        nombres.push_back(word);
//    }
//
//
//    for(auto v:nombres)
//   {
//       cout<<v<<endl;
//   }
    return 0;
}
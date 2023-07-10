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
#include "BPPtree.h"
#include "Btree.h"
#include "patricia.h"

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
struct Monto{
    double monto;
    int index_bloque;

    // Sobrecarga de los operadores de comparación.
    bool operator<(const Monto& other) const {
        return monto < other.monto;
    }

    bool operator>(const Monto& other) const {
        return monto > other.monto;
    }

    bool operator<=(const Monto& other) const {
        return monto <= other.monto;
    }

    bool operator>=(const Monto& other) const {
        return monto >= other.monto;
    }

    bool operator==(const Monto& other) const {
        return monto == other.monto;
    }

    bool operator!=(const Monto& other) const {
        return monto != other.monto;
    }
};
struct block{
    int id;
    string data;
    vector<transaccion> data2;
    string  prev_hash;
    string  current_hash;
    int nonce;
    string signature_string="0000";
    bool valido;
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



    void self_hash_invalido() {

        current_hash = sha256(data + prev_hash);
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
    bool getValido()
    {

        valido =current_hash.substr(0,4)=="0000";
        return valido;
    }
    void printblock(){
        cout<<"ID :"<<id<<endl;
        cout<<"NONCE :"<<nonce<<endl;
        cout<<endl;
        cout<<data<<endl;
        cout<<endl;
        cout<<"PREV_HASH :"<<prev_hash<<endl;
        cout<<"CURRENT_HASH :"<<current_hash<<endl;
        cout<<"VALIDO "<<boolalpha<<getValido()<<endl;
        cout<<endl;
    }
    [[nodiscard]] vector<transaccion> getTransaccion() const{
        return data2;
    }


};
class blockchain{
private:
    //ForwardList<block*> blockchain_;
    int id;
    int id_last_edited;
    BPTree<Monto> index_on_monto;
    BTree<transaccion>* index_on_transaction = new BTree<transaccion>(3);
    ChainHash<int,block*> block_references;
    TriePatricia index_on_names;
    ChainHash <string , Usuario*> usuarios;
    vector<int> filtrados;

public:
    blockchain(const blockchain& other) {
        // cout<<"USANDO CONSTRUCT COPIA"<<endl;
        id = other.id;

        for (int i = 1; i <= id; ++i) {
            auto nuevo= other.block_references[i];
            auto* block_copy = new block(*nuevo);
            block_references.insert(make_pair(block_copy->id, block_copy));
        }
    }
    blockchain( vector<transaccion>& data){
        id=1;
        for(auto& particular_transaction : data)
        {    auto instance_user1 = new Usuario(particular_transaction.emisor);
            auto instance_user2 = new Usuario(particular_transaction.receptor);
            if(!usuarios.contains(particular_transaction.emisor))
            {

                instance_user1->nueva_operacion(id);
                usuarios.insert(make_pair(instance_user1->getNombre(),instance_user1));
            }else usuarios[particular_transaction.emisor]->nueva_operacion(id);

            if(!usuarios.contains(particular_transaction.receptor))
            {

                instance_user2->nueva_operacion(id);
                usuarios.insert(make_pair(instance_user2->getNombre(),instance_user2));
            }else usuarios[particular_transaction.receptor]->nueva_operacion(id);


            if(usuarios.contains(particular_transaction.emisor) and usuarios.contains(particular_transaction.receptor))
            {
                usuarios[particular_transaction.emisor]->increment((-1.0)*particular_transaction.monto);
                usuarios[particular_transaction.receptor]->increment(particular_transaction.monto);
            }

            particular_transaction.setIdBloque(id);
            id_last_edited = 1;
            index_on_transaction->insert(particular_transaction);
            Monto prov{};
            prov.monto=particular_transaction.monto;
            prov.index_bloque=id;
            index_on_monto.insert(prov);
            index_on_names.insert(particular_transaction.emisor);
            index_on_names.insert(particular_transaction.receptor);
        }
        auto* new_block= new block(0,data,"");
        block_references.insert(make_pair(new_block->id,new_block));
    }
    void insert_transaction(int index,transaccion& data){

        block_references[index]->data2.push_back(data);
        block_references[index]->re_data();
        block_references[index]->self_hash_invalido();
        string current_hash = block_references[index]->current_hash;
        auto instance_user1 = new Usuario(data.emisor);
        auto instance_user2 = new Usuario(data.receptor);
        if(!usuarios.contains(data.emisor))
        {

            instance_user1->nueva_operacion(index);
            usuarios.insert(make_pair(instance_user1->getNombre(),instance_user1));
        }else usuarios[data.emisor]->nueva_operacion(index);

        if(!usuarios.contains(data.receptor))
        {

            instance_user2->nueva_operacion(index);
            usuarios.insert(make_pair(instance_user2->getNombre(),instance_user2));
        }else usuarios[data.receptor]->nueva_operacion(index);


        if(usuarios.contains(data.emisor) and usuarios.contains(data.receptor))
        {
            usuarios[data.emisor]->increment((-1.0)*data.monto);
            usuarios[data.receptor]->increment(data.monto);
        }
        if (!index_on_names.search(data.emisor)){
            cout << "hola" << endl;
            index_on_names.insert(data.emisor);
        }
        if (!index_on_names.search(data.receptor)){
            index_on_names.insert(data.receptor);
        }
        data.setIdBloque(index);
        id_last_edited = 1;
        index_on_transaction->insert(data);
        Monto prov{};
        prov.monto=data.monto;
        prov.index_bloque=index;
        index_on_monto.insert(prov);
        index_on_names.insert(data.emisor);
        index_on_names.insert(data.receptor);
        for (int i = index+1; i <= id ; ++i) {
            block_references[i]->prev_hash = current_hash;
            block_references[i]->self_hash_invalido();
            current_hash = block_references[i]->current_hash;
        }
    }
    void insert_block_with_transaction( vector<transaccion>& data){
        //block * current_block = blockchain_.front();

        for(auto& particular_transaction : data)
        {    auto instance_user1 = new Usuario(particular_transaction.emisor);
            auto instance_user2 = new Usuario(particular_transaction.receptor);
            if(!usuarios.contains(particular_transaction.emisor))
            {

                instance_user1->nueva_operacion(id+1);
                usuarios.insert(make_pair(instance_user1->getNombre(),instance_user1));
            }else usuarios[particular_transaction.emisor]->nueva_operacion(id+1);

            if(!usuarios.contains(particular_transaction.receptor))
            {

                instance_user2->nueva_operacion(id+1);
                usuarios.insert(make_pair(instance_user2->getNombre(),instance_user2));
            }else usuarios[particular_transaction.receptor]->nueva_operacion(id+1);


            if(usuarios.contains(particular_transaction.emisor) and usuarios.contains(particular_transaction.receptor))
            {
                usuarios[particular_transaction.emisor]->increment((-1.0)*particular_transaction.monto);
                usuarios[particular_transaction.receptor]->increment(particular_transaction.monto);
            }

            particular_transaction.setIdBloque(id+1);

            index_on_transaction->insert(particular_transaction);
            Monto prov;
            prov.monto=particular_transaction.monto;
            prov.index_bloque=id;
            index_on_monto.insert(prov);
            index_on_names.insert(particular_transaction.emisor);
            index_on_names.insert(particular_transaction.receptor);
        }

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


    const TriePatricia &getIndexOnNames() const {
        return index_on_names;
    }
    const ChainHash<string, Usuario *> &getUsuarios() const {
        return usuarios;
    }
    void view_blockChain(){
        for (int i = 1; i <= id; ++i)
            block_references[i]->printblock();
    }
    [[nodiscard]] int get_id() const{
        return id;
    }
    template<typename T>
    void edit_block(int index_b , int index_t ,const T& dato ,bool emisor = false){
        block_references[index_b]->edit_transaction(index_t,dato,emisor);
//        block_references[index_b]=std::move(dato);
        block_references[index_b]->self_hash_invalido();
        string current_hash = block_references[index_b]->current_hash;
        for (int i = index_b+1; i <= id ; ++i) {
            block_references[i]->prev_hash = current_hash;
            block_references[i]->self_hash_invalido();
            current_hash = block_references[i]->current_hash;
        }
        id_last_edited=index_b;
    }
    void mine_invalid_blocks(){
        block_references[id_last_edited]->self_hash();
        string current_hash = block_references[id_last_edited]->current_hash;
        for (int i = id_last_edited+1; i <= id ; ++i) {
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

//CRITERIOS DE BUSQUEDA -->Igual a X
    //IGUAL A X Devuelve transacciones que tengan un valor atomico como fecha o nombre de usuario(emisor , receptor)
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
//IGUAL A X Devuelve transacciones que tengan un valor atomico como monto
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
//IGUAL A X Devuelve transacciones que tengan un valor atomico como monto en un bloque especifico
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
//CRITERIOS DE BUSQUEDA Igual -->Entre X y Y
    //Obtener montos en un rango inicia; y final (USO DE B+)
    vector<Monto> monto_range_search_monto(double  ini , double  end)
    {   Monto inicial , final;
        inicial.monto=ini;
        inicial.index_bloque=-1;
        final.monto=end;
        final.index_bloque=-1;
        return index_on_monto.range_search(inicial , final );
    }
    //Obtener transacciones  en un rango inicia; y final (fechas , montos )
    vector<transaccion> transaction_range_search_fecha(string fecha_ini , string fecha_fin){
        return index_on_transaction->range_searching(fecha_ini,fecha_fin);
    }
    vector<transaccion> transaction_range_search_monto( double monto_ini, double monto_final){
        return index_on_transaction->range_searching(monto_ini,monto_final);
    }
//    vector<transaccion> transaction_range_search_transaction( const transaccion& t_ini, const transaccion& t_final){
//        return index_on_transaction.range_searching(t_ini,t_final);
//    }
//CRITERIOS DE BUSQUEDA Igual -->Inicia con
    vector<string> start_with(const string & start)
    {
        return index_on_names.search_start_with(start);
    }
    //CRITERIOS DE BUSQUEDA Igual -->Esta contenido en
    vector<string > contains(const string& pattern)
    {
        auto v = index_on_names.contains(pattern);
        auto t = this->get_block_id_from_user(v);
        return index_on_names.contains(pattern);
    }
    //Obtener transacciones ocurridas entre ciertas fechas

//CRITERIOS DE BUSQUEDA  -->Máximo valor de
    Monto max_value(){
        return index_on_monto.found_max();
    }
    Monto min_value(){
        return index_on_monto.found_min();
    }
    enum CriterioBusqueda {
        IgualA_X_String = 1,
        IgualA_X_Double,
        IgualA_X_Double_Bloque,
        RangoMonto,
        RangoFechaTransaccion,
        RangoMontoTransaccion,
        IniciaCon,
        ContenidoEn,
        MaximoValor,
        MinimoValor,
        // agregar otros criterios según sea necesario...
    };

    static vector<int> get_block_id_from_transaction(const vector<transaccion>& filtrados)
    {  vector<int> ids;
        for(auto t:filtrados){
            auto iter = std::find(ids.begin(), ids.end(), t.getIdBloque());
            if (iter == ids.end()){
                ids.push_back(t.getIdBloque());
            }

        }
        return ids;
    }
    static vector<int> get_block_id_from_monto(const vector<Monto>& filtrados)
    {  vector<int> ids;
        for(auto t:filtrados)
            ids.push_back(t.index_bloque);
        return ids;
    }

    vector<int> get_block_id_from_user(const vector<string>& filtros)
    {
        vector<int> ids;
        vector<bool> vistos(id, false);
        cout<<id<<endl;
        for(auto t:filtros)
        {
            cout<<usuarios[t]->getNombre()<<endl;
            for(auto ide:usuarios[t]->getBloqueId())
            {
                cout<<"ide:"<<ide<<endl;
                if(!vistos[ide-1])
                {  //cout<<ide<<endl;
                    ids.push_back(ide);
                    vistos[ide-1]= true;
                }


            }

        }

        return ids;
    }

    vector<int> getFiltrados(CriterioBusqueda criterio, const string& str_data = "", double dbl_data = 0, eleccion elec = emisor, double ini = 0, double end = 0, int index = -1)  {
        vector<int> ids;  // vector para guardar los ids de los bloques

        switch (criterio) {
            case CriterioBusqueda::IgualA_X_String:
            {
                auto result = search(str_data, elec);
                ids= get_block_id_from_transaction(result);
            }
                break;
            case CriterioBusqueda::IgualA_X_Double:
            {
                auto result = search(dbl_data);
                ids= get_block_id_from_transaction(result);
            }
                break;
            case CriterioBusqueda::IgualA_X_Double_Bloque:
            {
                auto result = search(dbl_data, index);
                ids= get_block_id_from_transaction(result);
            }
                break;
            case CriterioBusqueda::RangoMonto:
            {
                auto result = monto_range_search_monto(ini, end);
                ids=get_block_id_from_monto(result);
            }
                break;
            case CriterioBusqueda::RangoFechaTransaccion:
            {
                auto result = transaction_range_search_fecha(str_data, str_data);
                ids= get_block_id_from_transaction(result);
            }
                break;
            case CriterioBusqueda::RangoMontoTransaccion:
            {
                auto result = transaction_range_search_monto(ini, end);
                ids= get_block_id_from_transaction(result);
            }
                break;
            case CriterioBusqueda::IniciaCon:
            {
                auto result = start_with(str_data);
                ids= get_block_id_from_user(result);
            }
                break;
            case CriterioBusqueda::ContenidoEn:
            {
                auto result = contains(str_data);
                ids= get_block_id_from_user(result);
            }
                break;
            case CriterioBusqueda::MaximoValor:
            {
                auto result = max_value();
                ids.push_back(result.index_bloque);
            }
                break;
            case CriterioBusqueda::MinimoValor:
            {
                auto result = min_value();
                ids.push_back(result.index_bloque);
            }
                break;

            default:

                break;
        }


        return ids;
    }



};
#endif //PROYECTOALGORITMOS_BLOCKCHAIN_H
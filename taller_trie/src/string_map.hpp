#include "string_map.h"

template <typename T>

string_map<T>::string_map(){
    this->raiz = new Nodo();
    this->_size = 0;
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &val) {
    Nodo * n1 = this->raiz;
    for(int i = 0; i < val.first.length(); i++){
        if(!n1->siguientes[val.first[i]]){
            Nodo * siguiente = new Nodo();
            n1->siguientes[val.first[i]] = siguiente;
            n1 = siguiente;
        }else{
            n1 = n1->siguientes[val.first[i]];
        }
    }
    T * a = new T(val.second);
    if(n1->definicion == nullptr){
        this->_claves.push_back(val.first);
        this->_size++;
    }else{
        delete n1->definicion;
    }
    n1->definicion = a;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    raiz = new Nodo;
    _size = 0;
    for(string c : d._claves){
        insert(make_pair(c,d.at(c)));
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    for(string clave : this->_claves)
        this->erase(clave);
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // COMPLETAR
}


template <typename T>
int string_map<T>::count(const string& clave) const{
    if(this->_size == 0){
        return 0;
    }else{
        if(this->at(clave)){
            return 1;
        }else{
            return 0;
        }
    }
}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    Nodo * crawler = this->raiz;
    for(int i = 0; i < clave.length() && crawler != nullptr; i++){
        crawler = crawler->siguientes[clave[i]];
    }
    if(crawler != nullptr && crawler->definicion != nullptr){
        return *crawler->definicion;
    }else{
        return NULL;
    }
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    Nodo * crawler = this->raiz;
    for(int i = 0; i < clave.length(); i++){
        crawler = crawler->siguientes[clave[i]];
    }
    return *crawler->definicion;
}

template<typename T>
bool string_map<T>::hasChild(string_map::Nodo *node) {
    for(Nodo *n : node->siguientes){
        if(n != nullptr) return true;
    }
    return false;
}

template<typename T>
int string_map<T>::nChildren(string_map::Nodo *node) {
    int children = 0;
    for(Nodo *n : node->siguientes){
        if (n != nullptr) children++;
    }
    return children;
}

template <typename T>
void string_map<T>::erase(const string& clave) { // PRE : La clave esta en el TRIE.
    Nodo * actual = this->raiz;
    Nodo * ultimo = this->raiz;
    int j = 0;

    for(int i = 0; i < clave.length(); i++){
        if((nChildren(actual) > 1 || actual->definicion) && i < clave.length() - 1){
            ultimo = actual;
            j = i;
        }
        actual = actual->siguientes[clave[i]];
    }
    if(!hasChild(actual)){
        while(j < clave.length()){
            Nodo * siguiente = ultimo->siguientes[clave[j]];
            ultimo->siguientes[clave[j++]] = nullptr;
            delete ultimo->siguientes[clave[j]];
            ultimo = siguiente;
        }
    }

    for(int i = 0; i < this->_claves.size(); i++){
        if(this->_claves[i] == clave){
            this->_claves.erase(this->_claves.begin()+i);
        }
    }
    actual->definicion = nullptr;
    delete actual->definicion;
    this->_size--;
}

template <typename T>
int string_map<T>::size() const{
    return this->_size;
}

template <typename T>
bool string_map<T>::empty() const{
    return this->_size == 0;
}

template<typename T>
vector<string> &string_map<T>::claves() {
    return &this->_claves;
}







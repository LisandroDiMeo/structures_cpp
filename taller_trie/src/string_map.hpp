#include "string_map.h"

template <typename T>

string_map<T>::string_map(){
    this->raiz = new Nodo();
    this->_size = 0;
}

template<typename T>
void string_map<T>::insert(const pair<string, T> &val) {
    Nodo* actual = raiz;
    for (int i = 0; i < val.first.size() - 1; i++){
        if (actual->siguientes[val.first[i]] == nullptr)
            actual->siguientes[val.first[i]] = new Nodo;

        actual = actual->siguientes[val.first[i]];
    }

    if (actual->siguientes[val.first[val.first.size()-1]] != nullptr){
        T* sigAnterior = actual->siguientes[val.first[val.first.size()-1]]->definicion;
        actual->siguientes[val.first[val.first.size()-1]]->definicion = new T(val.second);
        delete sigAnterior;
    }else{
        actual->siguientes[val.first[val.first.size()-1]] = new Nodo(new T(val.second));
        _size++;
        _claves.push_back(val.first);
    }
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; } // Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {
    for(string c : d._claves){
        insert(make_pair(c,d.at(c)));
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    Nodo* actual = raiz;
    destructorHelper(actual);
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
const T string_map<T>::at(const string& clave) const {
    Nodo * crawler = this->raiz;
    for(int i = 0; i < clave.length() && crawler != nullptr; i++){
        crawler = crawler->siguientes[clave[i]];
    }
//    return *crawler->definicion;
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

template<typename T>
bool string_map<T>::esNodoValido(string_map::Nodo *nodo) {
    return nodo->definicion != nullptr || nChildren(nodo) > 1;
}

template<typename T>
typename string_map<T>::Nodo *string_map<T>::obtenerHijoValido(string_map::Nodo *nodo) {
    vector<Nodo*> hijos = nodo->siguientes;
    int i = 0;
    while (i < hijos.size() && hijos[i] == nullptr) {
        i++;
    }
    return hijos[i];
}

template <typename T>
void string_map<T>::erase(const string& clave) { // PRE : La clave esta en el TRIE.
    Nodo* actNodo = raiz;
    Nodo* ultNodo = raiz;
    int ultIndice = -1;

    for (int i = 0; i < clave.size(); ++i) {
        actNodo = actNodo->siguientes[clave[i]];
        if (esNodoValido(actNodo) && i != clave.size()-1){
            ultNodo = actNodo;
            ultIndice = i;
        }
    }

    T* def = actNodo->definicion;
    actNodo->definicion = nullptr;
    delete def;

    if (nChildren(actNodo) == 0){

        Nodo* aux = ultNodo->siguientes[clave[ultIndice+1]];
        ultNodo->siguientes[clave[ultIndice+1]] = nullptr;
        ultNodo = aux;

        while (ultNodo != actNodo){
            Nodo* borrar = ultNodo;
            ultNodo = obtenerHijoValido(ultNodo);
            delete borrar;
        }
        delete actNodo;
    }

    _size--;
    vector<string> clavesAux;
    for (string c : _claves){
        if (c != clave)
            clavesAux.push_back(c);
    }
    _claves = clavesAux;
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


template<typename T>
void string_map<T>::destructorHelper(string_map::Nodo *nodo) {
    T* def = nodo->definicion;
    nodo->definicion = nullptr;
    delete def;

    //Limpio el vector de siguientes
    for (int i = 0; i < nodo->siguientes.size(); i++){
        if (nodo->siguientes[i] != nullptr){
            Nodo* n = nodo->siguientes[i];
            nodo->siguientes[i] = nullptr;
            destructorHelper(n);
        }
    }
    delete nodo;
}




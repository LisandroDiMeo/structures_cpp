
#include "Conjunto.h"

template <class T>
Conjunto<T>::Conjunto() {
    this->_raiz = nullptr;
}

template<class T>
Nodo<T> *Conjunto<T>::vaciarArbol(Nodo<T> *nodo) {
    if(nodo != nullptr){
        vaciarArbol(nodo->der);
        vaciarArbol(nodo->izq);
        delete nodo;
    }
    return nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() { 
    this->_raiz = this->vaciarArbol(this->_raiz);
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool res = false;
    if(this->buscar(this->_raiz, clave) != nullptr){
        res = true;
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if(! this->pertenece(clave)){
        this->_raiz = this->insert(this->_raiz, clave);
        this->_cardinal++;
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if(this->pertenece(clave)){
        this->_raiz = this->borrar(this->_raiz, clave);
        this->_cardinal--;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo<T>* actual = this->_raiz;
    while (actual->valor != clave){
        if (actual->valor > clave)
            actual = actual->izq;
        else
            actual = actual->der;
    }
    Nodo<T>* sucesor = obtenerSucesor(actual);
    return sucesor->valor;
}

template<class T>
Nodo<T> *Conjunto<T>::obtenerSucesor(Nodo<T> *nodo) {
    if(nodo->der == nullptr){
        Nodo<T>* padre = obtenerPadre(nodo);
        return (padre != nullptr && padre->valor > nodo->valor) ? padre : nullptr;
    }else {
        Nodo<T>* sucesor = nodo->der;
        while (sucesor->izq != nullptr){
            sucesor = sucesor->izq;
        }
        return sucesor;
    }
}

template<class T>
Nodo<T> *Conjunto<T>::obtenerPadre(Nodo<T> *nodo) {
    Nodo<T> * padre = this->_raiz;
    while(padre != nullptr && padre->izq != nodo && padre->der != nodo){
        if (padre->valor > nodo->valor){
            padre = padre->izq;
        }else{
            padre = padre->der;
        }
    }
    return padre;
}


template <class T>
const T& Conjunto<T>::minimo() const {
    return this->_minimo;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    return this->_maximo;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return this->_cardinal;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}

template<class T>
Nodo<T> *Conjunto<T>::insert(Nodo<T> *nodo, const T &elem) {
    if(nodo == nullptr){
        nodo = new Nodo<T>(elem);
        if(this->_cardinal == 0){
            this->_minimo = elem;
            this->_maximo = elem;
        }else if(this->_minimo > elem){
            this->_minimo = elem;
        }else if(this->_maximo < elem){
            this->_maximo = elem;
        }
    }else{
        if(nodo->valor > elem){
            nodo->izq = insert(nodo->izq, elem);
        }else if(nodo->valor < elem){
            nodo->der = insert(nodo->der, elem);
        }else{
            return nodo;
        }
    }
    return nodo;
}

template<class T>
Nodo<T> *Conjunto<T>::buscar(Nodo<T> *nodo, const T &elem) const{
    if(nodo == nullptr){
        return nullptr;
    }else{
        if(nodo->valor < elem){
            return buscar(nodo->der, elem);
        }else if(nodo->valor > elem){
            return buscar(nodo->izq, elem);
        }else{
            return nodo;
        }
    }
}

template<class T>
Nodo<T> *Conjunto<T>::encontrarMinimo(Nodo<T> *nodo) {
    Nodo<T>* current = nodo;
    while (current && current->izq != nullptr)
        current = current->izq;

    return current;
}

template<class T>
Nodo<T> *Conjunto<T>::borrar(Nodo<T> *nodo, const T &elem) {
    // Caso base
    if(nodo == nullptr) return nodo;
    if(nodo->valor > elem)
        nodo->izq = borrar(nodo->izq, elem);
    else if(nodo->valor < elem)
        nodo->der = borrar(nodo->der, elem);
    else{ // elem == nodo->valor
        if(nodo->izq == nullptr){
            Nodo<T> * temp = nodo->der;
            nodo->izq = nullptr;
            nodo->der = nullptr;
            delete nodo;
            return temp;
        }else if(nodo->der == nullptr){
            Nodo<T> * temp = nodo->izq;
            nodo->izq = nullptr;
            nodo->der = nullptr;
            delete nodo;
            return temp;
        }
        Nodo<T> * temp = encontrarMinimo(nodo->der);
        nodo->valor = temp->valor;
        nodo->der = borrar(nodo->der, temp->valor);
    }
    return nodo;
}

template<class T>
std::vector<T> Conjunto<T>::_inorder(Nodo<T> *nodo) {
    std::vector<T> res;
    if(nodo->der == nullptr && nodo->izq == nullptr){
        res.push_back(nodo->valor);
    }else{
        llenarVector(res, nodo);
    }
    return res;
}

template<class T>
void Conjunto<T>::llenarVector(std::vector<T> &v, Nodo<T> *nodo){
    if(nodo == nullptr){
        return;
    }
    else if(nodo->der == nullptr && nodo->izq == nullptr){
        v.push_back(nodo->valor);
    } else{
        llenarVector(v, nodo->izq);
        v.push_back(nodo->valor);
        llenarVector(v, nodo->der);
    }
}

template<class T>
void Conjunto<T>::mostrarEnOrden() {
    std::vector<T> v = this->_inorder(this->_raiz);
    for(T t : v){
        std::cout << t << " ";
    }
    std::cout << std::endl;
}

template<class T>
int contieneOrdenada(vector<T> &s, const T &x) {
    if (s.size()==0 ) {
        return -1;
    }else if(s.size() == 1){
        if(s[0] == x){
            return 0;
        }else{
            return -1;
        }
    }else if (x < s[0]) {
        return -1;
    }else if(x >= s[s.size()-1]){
        if(x == s[s.size()-1]){
            return s.size()-1;
        }else{
            return -1;
        }
    }else{
        int low = 0;
        int high = s.size() - 1;
        while(low+1 < high){
            int mid = (low + high) / 2;
            if(s[mid] <= x){
                low = mid;
            }else{
                high = mid;
            }
        }
        return s[low] == x ? low : -1;
    }
}

//template<class T>
//const T &Conjunto<T>::next(Nodo<T> *nodo,const T& elem) { // PRE: EL ELEMENTO SIEMPRE TIENE SIGUIENTE
//    std::vector<T> v = _inorder(nodo);
//    int indice = contieneOrdenada(v, elem);
//    indice++;
//    return v[indice];
//}




#include "Lista.h"

template <typename T>
Lista<T>::Lista() {
    this->_prim = nullptr;
    this->_ult = nullptr;
    this->cantElementos = 0;
}

template <typename T>
Lista<T>::Lista(const Lista<T>& l) : Lista() {
    //Inicializa una lista vacía y luego utiliza operator= para no duplicar el código de la copia de una lista.
    *this = l;
}

template <typename T>
Lista<T>::~Lista() {
    this->destruirNodos();
}

template <typename T>
void Lista<T>::destruirNodos(){
    Nodo *actual = this->_prim;
    while (actual != nullptr){
        Nodo *siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    this->_prim = nullptr;
    this->_ult = nullptr;
}

template <typename T>
Lista<T>& Lista<T>::operator=(const Lista<T>& aCopiar) {
    destruirNodos();
    copiarNodos(aCopiar);
    this->cantElementos = aCopiar.longitud();
    return *this;
}

template <typename T>
void Lista<T>::copiarNodos(const Lista<T> &aCopiar){
    Nodo *actual = aCopiar._prim;
    while(actual != nullptr){
        agregarAtras(actual->valor);
        actual = actual->siguiente;
    }
}

template <typename T>
void Lista<T>::agregarAdelante(const T& elem) {
    Nodo *nuevo = new Nodo(this->_prim,nullptr,elem);
    if(this->cantElementos == 0){
        this->_prim = nuevo;
        this->_ult = nuevo;
    }else{
        this->_prim->anterior = nuevo;
        this->_prim = nuevo;
    }
    this->cantElementos = 1 + this->cantElementos;
}

template <typename T>
void Lista<T>::agregarAtras(const T& elem) {
    Nodo* nuevo = new Nodo(nullptr,this->_ult,elem);
    if(this->cantElementos == 0){
        this->_prim = nuevo;
        this->_ult = nuevo;
    }else{
        this->_ult->siguiente = nuevo;
        this->_ult = nuevo;
    }
    this->cantElementos = 1 + this->cantElementos;
}

template <typename T>
void Lista<T>::eliminar(Nat i) {
    Nodo *actual = this->_prim;
    int j = 0;
    if(this->longitud() == 1){
        delete actual;
        this->_prim = nullptr;
        this->_ult = nullptr;
    }else{
        if(i == 0){
            Nodo *siguiente = actual->siguiente;
            delete actual;
            this->_prim = siguiente;
            this->_prim->anterior = nullptr;
        }else if(i == this->longitud() - 1){
            actual = this->_ult;
            Nodo *anterior = actual->anterior;
            delete actual;
            this->_ult = anterior;
            this->_ult->siguiente = nullptr;
        }else{
            while(j < i){
                actual = actual->siguiente;
                j++;
            }
            Nodo *anterior = actual->anterior;
            Nodo *siguiente = actual->siguiente;
            delete actual;
            anterior->siguiente = siguiente;
            siguiente->anterior = anterior;
        }

    }
    this->cantElementos--;
}

template <typename T>
int Lista<T>::longitud() const {
    return this->cantElementos;
}

template <typename T>
const T& Lista<T>::iesimo(Nat i) const {
    Nodo *actual = this->_prim;
    if(actual == nullptr){
        actual = this->_ult;
    }
    for(int j = 0;j < i;j++){
        actual = actual->siguiente;
    }
    return actual->valor;
}

template <typename T>
T& Lista<T>::iesimo(Nat i) {
    Nodo *actual = this->_prim;
    if(actual == nullptr){
        actual = this->_ult;
    }
    for(int j = 0;j < i;j++){
        actual = actual->siguiente;
    }
    return actual->valor;
}

template <typename T>
void Lista<T>::mostrar(ostream& o) {
    // Completar
}
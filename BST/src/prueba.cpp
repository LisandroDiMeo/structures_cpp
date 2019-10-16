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
Nodo<T> *Conjunto<T>::encontrarMinimo(Nodo<T> *nodo) {
    if(nodo == nullptr){
        return nullptr;
    }else if(nodo->izq == nullptr){
        return nodo;
    }else{
        return encontrarMinimo(nodo->izq);
    }
}

template<class T>
Nodo<T> *Conjunto<T>::borrar(Nodo<T> *nodo, const T &elem) {
    Nodo<T> * temp;
    if(nodo == nullptr){
        return nodo;
    }else if(nodo->valor > elem){
        // Si el proximo es el que voy a borrar, reasigno el minimo (Si hace falta)
        if (nodo->izq != nullptr && nodo->izq->valor == this->_minimo) this->_minimo = nodo->izq->valor;
        return borrar(nodo->izq, elem);
    }else if(nodo->valor < elem){
        // Si el proximo es el que voy a borrar, reasigno el maximo (Si hace falta)
        if (nodo->der != nullptr && nodo->der->valor == this->_maximo) this->_maximo = nodo->izq->valor;
        return borrar(nodo->der, elem);
    }else{
        if(nodo->izq != nullptr && nodo->der != nullptr){
            temp = encontrarMinimo(nodo->der);
            nodo->valor = temp->valor;
            nodo->der = borrar(nodo->der, nodo->valor);
        }else{
            temp = nodo;
            if(nodo->izq == nullptr){
                nodo = nodo->der;
            }else{
                nodo = nodo->izq;
            }
            delete temp;
        }
    }
    return nodo;
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
#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
struct Nodo
{
    // El elemento al que representa el nodo.
    T valor;
    // Puntero a la raíz del subárbol izquierdo.
    Nodo* izq;
    // Puntero a la raíz del subárbol derecho.
    Nodo* der;

    Nodo(const T& nuevo) :
            valor(nuevo), izq(nullptr), der(nullptr) {
    }
};

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto de manera ordenada.
        void mostrarEnOrden();

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:
        Nodo<T> * _raiz;
        Nodo<T> * insert(Nodo<T> * nodo, const T& elem);
        Nodo<T> * buscar(Nodo<T> * nodo, const T& elem) const;
        Nodo<T> * encontrarMinimo(Nodo<T> * nodo);
        Nodo<T> * borrar(Nodo<T> * nodo, const T& elem);
        std::vector<T> _inorder(Nodo<T> * nodo);
        void llenarVector(std::vector<T> &v, Nodo<T> * nodo);
        const T& next(Nodo<T> * nodo,const T& elem);
        Nodo<T> * vaciarArbol(Nodo<T> * nodo);
        Nodo<T> * obtenerSucesor(Nodo<T> * nodo);
        Nodo<T> * obtenerPadre(Nodo<T> * nodo);
        int _cardinal = 0;
        int _minimo;
        int _maximo;
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

template<class T>
int contieneOrdenada(vector<T> &s, const T &x);

#include "Conjunto.hpp"

#endif // CONJUNTO_H_

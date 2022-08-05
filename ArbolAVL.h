#ifndef __ARBOLAVL__H__
#define __ARBOLAVL__H__

#include <iostream>
#include "NodoBinarioAVL.h"
#include <list>
#include <utility>

template< class T >
class ArbolAVL {
  protected:
    NodoBinarioAVL<T> *raiz;
  public:
    //constructores
    ArbolAVL();
    ArbolAVL(T& val);
    //destructor
    ~ArbolAVL();
    //manipuladores del arbol
    bool esVacio();
    T& datoRaiz();
    void fijarRaiz(NodoBinarioAVL<T> *n_raiz);
    NodoBinarioAVL<T>* obtenerRaiz();
    //operaciones del arbol
    void preOrden();
    void inOrden();
    void inordenEnLista(std::list<T>& lista);
    void posOrden();
    void nivelOrden();
    bool buscar(T& val);
    bool insert(T& val);
    bool insertar(T& val);
    bool erase(T& val);
    bool eliminar(T& val);
    T& minimo();
    T& maximo();
    int tamano();
    int altura();
};

#include "ArbolAVL.hxx"

#endif // __ARBOLAVL__H__

// eof - ArbolAVL.h


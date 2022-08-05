#ifndef __NODOBINARIOAVL__H__
#define __NODOBINARIOAVL__H__

#include <iostream>
#include <list>
#include <utility>

template< class T >
class NodoBinarioAVL {
  protected:
    T dato;
    NodoBinarioAVL<T> *hijoIzq;
    NodoBinarioAVL<T> *hijoDer;
    int altura;
  public:
    //constructores
    NodoBinarioAVL();
    NodoBinarioAVL(T& val);
    NodoBinarioAVL(T& val, NodoBinarioAVL<T> *izq, NodoBinarioAVL<T> *der);
    //destructor
    ~NodoBinarioAVL();
    //manipuladores del nodo
    bool esHoja();
    T& obtenerDato();
    NodoBinarioAVL<T>* obtenerHijoIzq();
    NodoBinarioAVL<T>* obtenerHijoDer();
    int obtenerAltura();
    void fijarDato(T& val);
    void fijarHijoIzq(NodoBinarioAVL<T> *izq);
    void fijarHijoDer(NodoBinarioAVL<T> *der);
    void fijarAltura(int& h);
    //operaciones del arbol
    void preOrden();
    void inOrden();
    void inordenEnLista(std::list<T>& lista);
    void posOrden();
    void nivelOrden();
    bool buscar(T& val);
    bool insertar(T& val, NodoBinarioAVL<T> **nraiz);
    bool eliminar(T& val, NodoBinarioAVL<T> **nraiz);
    T& minimo();
    T& maximo();
    int tamano();
    void actualizarAlturas();
    NodoBinarioAVL<T>* balanceoArbol ();
  private:
    NodoBinarioAVL<T>* rotDerecha();
    NodoBinarioAVL<T>* rotIzquierda();
    NodoBinarioAVL<T>* rotIzquierdaDerecha();
    NodoBinarioAVL<T>* rotDerechaIzquierda();
};
    
#include "NodoBinarioAVL.hxx"

#endif // __NODOBINARIOAVL__H__

// eof - NodoBinarioAVL.h


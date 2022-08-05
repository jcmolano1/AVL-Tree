#include "ArbolAVL.h"
#include <iostream>

// ------------------------------------------------------------------------
template< class T >
ArbolAVL<T>::ArbolAVL() {
  this->raiz = NULL;
}

// ------------------------------------------------------------------------
template< class T >
ArbolAVL<T>::ArbolAVL(T& val) {
  this->raiz = new NodoBinarioAVL<T>(val);
}

// ------------------------------------------------------------------------
template< class T >
ArbolAVL<T>::~ArbolAVL() {
  if (this->raiz != NULL) {
    delete this->raiz;
    this->raiz = NULL;
  }
}

// ------------------------------------------------------------------------
template< class T >
bool ArbolAVL<T>::esVacio() {
  return (this->raiz == NULL);
}

// ------------------------------------------------------------------------
template< class T >
T& ArbolAVL<T>::datoRaiz() {
  return (this->raiz)->obtenerDato();
}

// ------------------------------------------------------------------------
template< class T >
void ArbolAVL<T>::fijarRaiz(NodoBinarioAVL<T> *n_raiz) {
  this->raiz = n_raiz;
}

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>* ArbolAVL<T>::obtenerRaiz() {
  return this->raiz;
}

// ------------------------------------------------------------------------
template< class T >
void ArbolAVL<T>::preOrden() {
  if (this->raiz != NULL)
    this->raiz->preOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
template< class T >
void ArbolAVL<T>::inOrden() {
  if (this->raiz != NULL)
    this->raiz->inOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
template< class T >
void ArbolAVL<T>::inordenEnLista(std::list<T>& lista) {
  if (this->raiz != NULL)
    this->raiz->inordenEnLista(lista);
}

// ------------------------------------------------------------------------
template< class T >
void ArbolAVL<T>::posOrden() {
  if (this->raiz != NULL)
    this->raiz->posOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
template< class T >
void ArbolAVL<T>::nivelOrden() {
  if (this->raiz != NULL)
    this->raiz->nivelOrden();
  std::cout << std::endl;
}

// ------------------------------------------------------------------------
template< class T >
bool ArbolAVL<T>::buscar(T& val) {
  bool res;
  if (this->raiz == NULL)
    res = false;
  else
    res = this->raiz->buscar(val);
    
  return res;
}

// ------------------------------------------------------------------------
template< class T >
bool ArbolAVL<T>::insert(T& val) {
  return this->insertar(val);
}

// ------------------------------------------------------------------------
template< class T >
bool ArbolAVL<T>::insertar(T& val) {
  bool res;
  
  if (this->raiz == NULL) {
    this->raiz = new NodoBinarioAVL<T>(val);
    res = true;
  } else {
    NodoBinarioAVL<T> *nraiz = this->raiz;
    res = this->raiz->insertar(val,&nraiz);
    this->raiz = nraiz;
  }
  
  return res;
}

// ------------------------------------------------------------------------
template< class T >
bool ArbolAVL<T>::erase(T& val) {
  return this->eliminar(val);
}

// ------------------------------------------------------------------------
template< class T >
bool ArbolAVL<T>::eliminar(T& val) {
  bool res;
  
  if (this->raiz == NULL)
    res = false;
  else if (this->raiz->esHoja() && this->raiz->obtenerDato() == val) {
    delete this->raiz;
    this->raiz = NULL;
    res = true;
  } else {
    NodoBinarioAVL<T> *nraiz = this->raiz;
    res = this->raiz->eliminar(val,&nraiz);
    this->raiz = nraiz;
  }
  
  return res;
}

// ------------------------------------------------------------------------
template< class T >
T& ArbolAVL<T>::minimo() {
  if (this->raiz != NULL)
    return this->raiz->minimo();
}

// ------------------------------------------------------------------------
template< class T >
T& ArbolAVL<T>::maximo() {
  if (this->raiz != NULL)
    return this->raiz->maximo();
}

// ------------------------------------------------------------------------
template< class T >
int ArbolAVL<T>::tamano() {
  int val;
  if (this->raiz == NULL)
    val = 0;
  else
    val = this->raiz->tamano();
  
  return val;
}

// ------------------------------------------------------------------------
template< class T >
int ArbolAVL<T>::altura() {
  int val;
  if (this->raiz == NULL)
    val = -1;
  else
    val = this->raiz->obtenerAltura();
    
  return val;
}

// eof - ArbolAVL.hxx


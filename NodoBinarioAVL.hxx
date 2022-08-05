#include <queue>
#include <iostream>

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>::NodoBinarioAVL() {
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
  this->altura = -1;
}

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>::NodoBinarioAVL(T& val){
  this->dato = val;
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
  this->altura = 0;
}

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>::NodoBinarioAVL(T& val, NodoBinarioAVL<T> *izq, NodoBinarioAVL<T> *der) {
  this->dato = val;
  this->hijoIzq = izq;
  this->hijoDer = der;
  if (izq->altura > der->altura)
    this->altura = izq->altura + 1;
  else
    this->altura = der->altura + 1;
}

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>::~NodoBinarioAVL() {
  if (this->hijoIzq != NULL) {
    delete this->hijoIzq;
    this->hijoIzq = NULL;
  }
  if (this->hijoDer != NULL) {
    delete this->hijoDer;
    this->hijoDer = NULL;
  }
}

// ------------------------------------------------------------------------
template< class T >
bool NodoBinarioAVL<T>::esHoja() {
  return (this->hijoIzq == NULL && this->hijoDer == NULL);
}

// ------------------------------------------------------------------------
template< class T >
T& NodoBinarioAVL<T>::obtenerDato() {
  return this->dato;
}

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>* NodoBinarioAVL<T>::obtenerHijoIzq() {
  return this->hijoIzq;
}

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>* NodoBinarioAVL<T>::obtenerHijoDer() {
  return this->hijoDer;
}

// ------------------------------------------------------------------------
template< class T>
int NodoBinarioAVL<T>::obtenerAltura() {
  return this->altura;
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::fijarDato(T& val) {
  this->dato = val;
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::fijarHijoIzq(NodoBinarioAVL<T> *izq) {
  this->hijoIzq = izq;
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::fijarHijoDer(NodoBinarioAVL<T> *der) {
  this->hijoDer = der;
}

// ------------------------------------------------------------------------
template< class T>
void NodoBinarioAVL<T>::fijarAltura(int& h) {
  this->altura = h;
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::preOrden() {
  std::cout << this->dato << "\t";
  if (this->hijoIzq != NULL)
    this->hijoIzq->preOrden();
  if (this->hijoDer != NULL)
    this->hijoDer->preOrden();
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::inOrden() {
  if (this->hijoIzq != NULL)
    this->hijoIzq->inOrden();
  std::cout << this->dato << "\t";
  if (this->hijoDer != NULL)
    this->hijoDer->inOrden();
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::inordenEnLista(std::list<T>& lista) {
  if (this->hijoIzq != NULL)
    this->hijoIzq->inordenEnLista(lista);
  lista.push_back(this->dato);
  if (this->hijoDer != NULL)
    this->hijoDer->inordenEnLista(lista);
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::posOrden() {
  if (this->hijoIzq != NULL)
    this->hijoIzq->posOrden();
  if (this->hijoDer != NULL)
    this->hijoDer->posOrden();
  std::cout << this->dato << "\t";
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::nivelOrden() {
  std::queue< NodoBinarioAVL<T>* > q;
  NodoBinarioAVL<T> *t = this;
  while (t != NULL) {
    std::cout << t->dato << "\t";
    if (t->hijoIzq != NULL)
      q.push(t->hijoIzq);
    if (t->hijoDer != NULL)
      q.push(t->hijoDer);
    if (!q.empty()) {
      t = q.front();
      q.pop();
    } else
      t = NULL;
  }
}

// ------------------------------------------------------------------------
template< class T >
bool NodoBinarioAVL<T>::buscar(T& val) {
  NodoBinarioAVL<T> *p = this;
  bool encontrado = false;
  while (p != NULL && !encontrado) {
    if (val < p->dato)
      p = p->hijoIzq;
    else if (val > p->dato)
      p = p->hijoDer;
    else
      encontrado = true;
  }
  return encontrado;
}

// ------------------------------------------------------------------------
template< class T >
bool NodoBinarioAVL<T>::insertar(T& val, NodoBinarioAVL<T> **nraiz) {
  NodoBinarioAVL<T> *p = this;
  NodoBinarioAVL<T> *pp = this;
  bool insertado = false;
  bool duplicado = false;
  while (p != NULL) {
    pp = p;
    if (val < p->dato)
      p = p->hijoIzq;
    else if (val > p->dato)
      p = p->hijoDer;
    else {
      duplicado = true;
      break;
    }
  }
  if (!duplicado) {
    NodoBinarioAVL<T> *n = new NodoBinarioAVL<T>(val);
    if (n != NULL) {
      if (val < pp->dato)
        pp->fijarHijoIzq(n);
      else
        pp->fijarHijoDer(n);
    }
    
    this->actualizarAlturas();
    *nraiz = this->balanceoArbol();
    
    insertado = true;
  }
  
  return insertado;
}

// ------------------------------------------------------------------------
template< class T >
bool NodoBinarioAVL<T>::eliminar(T& val, NodoBinarioAVL<T> **nraiz) {
  NodoBinarioAVL<T> *p = this;
  NodoBinarioAVL<T> *pp = this;
  bool eliminado = false;
  while (p != NULL && p->dato != val){
    pp = p;
    if (val < p->dato)
      p = p->hijoIzq;
    else if (val > p->dato)
      p = p->hijoDer;
  }
  if (p != NULL) {
    if (p->hijoIzq != NULL && p->hijoDer != NULL) {
      NodoBinarioAVL<T> *s = p->hijoIzq;
      NodoBinarioAVL<T> *ps = p;
      while (s->hijoDer != NULL) {
        ps = s;
        s = s->hijoDer;
      }
      p->dato = s->dato;
      if (ps == p)
        ps->hijoIzq = s->hijoIzq;
      else
        ps->hijoDer = s->hijoIzq;
    } else {
      NodoBinarioAVL<T> *c = NULL;
      if (p->hijoIzq != NULL)
        c = p->hijoIzq;
      else if (p->hijoDer != NULL)
        c = p->hijoDer;
      if (p == this) {
        this->dato = c->dato;
        this->hijoIzq = c->hijoIzq;
        this->hijoDer = c->hijoDer;
        delete c;
        c = NULL;
      } else {
        if (p == pp->hijoIzq)
          pp->hijoIzq = c;
        else if (p == pp->hijoDer)
          pp->hijoDer = c;
      }
    }

    this->actualizarAlturas();
    *nraiz = this->balanceoArbol();
  
    eliminado = true;
  }
  
  return eliminado;
}

// ------------------------------------------------------------------------
template< class T >
T& NodoBinarioAVL<T>::minimo() {
  NodoBinarioAVL<T> *p = this;
  while (p->hijoIzq != NULL) {
    p = p->hijoIzq;
  }
  return p->dato;
}

// ------------------------------------------------------------------------
template< class T >
T& NodoBinarioAVL<T>::maximo() {
  NodoBinarioAVL<T> *p = this;
  while (p->hijoDer != NULL) {
    p = p->hijoDer;
  }
  return p->dato;
}

// ------------------------------------------------------------------------
template< class T >
int NodoBinarioAVL<T>::tamano() {
  int vtam = 0;
  if (this->hijoIzq != NULL)
    vtam += this->hijoIzq->tamano();
  if (this->hijoDer != NULL)
    vtam += this->hijoDer->tamano();
  return (vtam+1);
}

// ------------------------------------------------------------------------
template< class T >
void NodoBinarioAVL<T>::actualizarAlturas() {
  int ai = -1;
  int ad = -1;
  if (this->hijoIzq == NULL && this->hijoDer == NULL)
    this->altura = 0;
  if (this->hijoIzq != NULL) {
    this->hijoIzq->actualizarAlturas();
    ai = this->hijoIzq->altura;
  }
  if (this->hijoDer != NULL) {
    this->hijoDer->actualizarAlturas();
    ad = this->hijoDer->altura;
  }
  if (ai > ad)
    this->altura = ai+1;
  else
    this->altura = ad+1;
}

// ------------------------------------------------------------------------
template< class T >
NodoBinarioAVL<T>* NodoBinarioAVL<T>::balanceoArbol() {
  int ai, ad, dif, hai, had, hdif;
  NodoBinarioAVL<T> *temp;
  NodoBinarioAVL<T> *nres = this;
  NodoBinarioAVL<T> *ntemp1, *ntemp2;

  if (this->hijoIzq != NULL) {
    ntemp1 = this->hijoIzq->balanceoArbol();
    this->fijarHijoIzq(ntemp1);
    ai = this->hijoIzq->altura;
  } else
    ai = -1;

  if (this->hijoDer != NULL) {
    ntemp2 = this->hijoDer->balanceoArbol();
    this->fijarHijoDer(ntemp2);
    ad = this->hijoDer->altura;
  } else
    ad = -1;
  dif = ai - ad;
  
  if (dif == 2) {
    //subarbol izquierdo mas alto que subarbol derecho
    temp = this->hijoIzq;
    
    if (temp->hijoIzq != NULL)
      hai = temp->hijoIzq->altura;
    else
      hai = -1;
    
    if (temp->hijoDer != NULL)
      had = temp->hijoDer->altura;
    else
      had = -1;
    hdif = hai - had;
    
    if (hdif >= 0) {
      //subarbol izquierdo más alto que subarbol derecho en el hijo izquierdo
      nres = this->rotDerecha();
      nres->actualizarAlturas();
    } else if (hdif < 0) {
      //subarbol derecho más alto que subarbol izquierdo en el hijo izquierdo
      nres = this->rotIzquierdaDerecha();
      nres->actualizarAlturas();
    }
      
  } else if (dif == -2) {
    //subarbol derecho mas alto que subarbol izquierdo
    temp = this->hijoDer;
    
    if (temp->hijoIzq != NULL)
      hai = temp->hijoIzq->altura;
    else
      hai = -1;
    
    if (temp->hijoDer != NULL)
      had = temp->hijoDer->altura;
    else
      had = -1;
    hdif = hai - had;
    
    if (hdif <= 0) {
      //subarbol derecho más alto que subarbol izquierdo en el hijo derecho
      nres = this->rotIzquierda();
      nres->actualizarAlturas();
    } else if (hdif > 0) {
      //subarbol izquierdo más alto que subarbol derecho en el hijo derecho
      nres = this->rotDerechaIzquierda();
      nres->actualizarAlturas();
    }
  }
  
  return nres;
}

// ------------------------------------------------------------------------
template< class T>
NodoBinarioAVL<T>* NodoBinarioAVL<T>::rotDerecha() {
  NodoBinarioAVL<T> *n_padre = this->hijoIzq;
  this->fijarHijoIzq(n_padre->hijoDer);
  n_padre->fijarHijoDer(this);
  
  return n_padre;
} 

// ------------------------------------------------------------------------
template< class T>
NodoBinarioAVL<T>* NodoBinarioAVL<T>::rotIzquierda() {
  NodoBinarioAVL<T> *n_padre = this->hijoDer;
  this->fijarHijoDer(n_padre->hijoIzq);
  n_padre->fijarHijoIzq(this);
  
  return n_padre;
}

// ------------------------------------------------------------------------
template< class T>
NodoBinarioAVL<T>* NodoBinarioAVL<T>::rotIzquierdaDerecha() {
  this->fijarHijoIzq(this->hijoIzq->rotIzquierda());
  return this->rotDerecha();
}

// ------------------------------------------------------------------------
template< class T>
NodoBinarioAVL<T>* NodoBinarioAVL<T>::rotDerechaIzquierda() {
  this->fijarHijoDer(this->hijoDer->rotDerecha());
  return this->rotIzquierda();
} 

// eof - NodoBinarioAVL.hxx



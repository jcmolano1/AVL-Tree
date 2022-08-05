#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

#include <list>
#include <set>
#include "ArbolAVL.h"

typedef std::list< std::string > TList;
typedef std::set< std::string >  TSet;
typedef std::vector< std::string > TVector;
typedef ArbolAVL< std::string > TAVL;

template< class TArbol >
bool LeerArbol( TArbol& arbol, const std::string& nomArch )
{
  std::ifstream entrada( nomArch.c_str( ) );
  if( !entrada )
    return( false );
  while( !entrada.eof( ) )
  {
    std::string codigo, valor;
    entrada >> codigo >> valor;
    if( codigo == "A" )
      arbol.insert( valor );
    else if( codigo == "E" )
      arbol.erase( valor );

  }
  entrada.close( );
  return( true );
}

int main( int argc, char* argv[] )
{
  if( argc < 2 )
  {
    std::cerr << "Uso: " << argv[ 0 ] << " archivo_entrada" << std::endl;
    return( -1 );

  }

  TSet miArbolRN; // arbol rojinegro
  TAVL miArbolAVL; // arbol AVL

  // Llenar arbol rojinegro y calcular el tiempo empleado
  std::clock_t inicioLecturaRN = std::clock( );
  bool lecturaRN = LeerArbol( miArbolRN, argv[ 1 ] );
  std::clock_t finLecturaRN = std::clock( );
  double tiempoLecturaRN = ( finLecturaRN - inicioLecturaRN ) / double( CLOCKS_PER_SEC );
  if( lecturaRN )
    std::cout << "Tiempo de llenado arbol RN = " << tiempoLecturaRN << "segs." << std::endl;
  else
    std::cout << "Error al leer \"" << argv[ 1 ] << "\" para llenar el arbol RN." << std::endl;
  
  // Llenar arbol AVL y calcular el tiempo empleado
  std::clock_t inicioLecturaAVL = std::clock( );
  bool lecturaAVL = LeerArbol( miArbolAVL, argv[ 1 ] );
  std::clock_t finLecturaAVL = std::clock( );
  double tiempoLecturaAVL = ( finLecturaAVL - inicioLecturaAVL ) / double( CLOCKS_PER_SEC );
  if( lecturaAVL )
    std::cout << "Tiempo de llenado arbol AVL = " << tiempoLecturaAVL << "segs." << std::endl;
  else
    std::cout << "Error al leer \"" << argv[ 1 ] << "\" para llenar el arbol AVL." << std::endl;
  
  // Obtener recorrido en inorden del arbol AVL
  TList inordenAVL;
  miArbolAVL.inordenEnLista( inordenAVL );

  std::cout << "Cantidad de datos en arbol AVL: " << inordenAVL.size( ) << std::endl;
  std::cout << "Cantidad de datos en arbol RN: " << miArbolRN.size( ) << std::endl;

  if( inordenAVL.size( ) != miArbolRN.size( ) )
  {
    std::cout << "Cantidad de elementos en los arboles no coinciden." << std::endl;
    return( -1 );

  }

  // Comparar los datos en los arboles
  TSet::const_iterator rnIt = miArbolRN.begin( );
  TList::const_iterator avlIt = inordenAVL.begin( );
  bool iguales = true;
  for( ; rnIt != miArbolRN.end( ); rnIt++, avlIt++ ) {
    iguales &= ( *rnIt == *avlIt );
  }

  // Informar si los arboles coinciden o no
  std::cout << "Los arboles ";
  if( !iguales )
    std::cout << "no ";
  std::cout << "coinciden." << std::endl;
  
  return( 0 );
}

// eof - taller_3_ordenamiento_busqueda.cxx

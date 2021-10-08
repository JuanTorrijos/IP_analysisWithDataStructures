#include <iostream>
#include "ListasDL.hpp"
#include <fstream>

int main() {
  //Lectura de archivo separada
    ifstream datos;
    datos.open("bitacoraPrincipal.txt");
    string mes, dia,hora,ipp,falla;
    ListaDL<Bitacora *> * lista1=new ListaDL<Bitacora *>();
    while(datos.good()){
        getline(datos,mes,' ');
        getline(datos,dia,' ');
        getline(datos,hora,' ');
        getline(datos,ipp,' ');
        getline(datos,falla);
        lista1->agregaFinal(new Bitacora(mes,dia,hora,ipp,falla));
    }
    datos.close();
    //lista1->imprimirLista();

    ListaCDL<Falla *> * lista2=new ListaCDL<Falla *>();
    NodoDL<Bitacora *> * nodo=lista1->getHead();
    while(nodo){
      Falla * comp = new Falla(nodo->getValor()->getFalla(), 1, nodo->getValor()->mesANumero());
      if(lista2->buscar(comp)){
        lista2->buscar(comp)->getValor()->sumarOcurrencia(nodo->getValor()->mesANumero());
      }else{ 
        lista2->agregarFinal(comp);
      }
        nodo=nodo->getSiguiente();
    }
    
    //lista2->imprimirListaSobrecarga();

    string fallaTipo;
    cout<<"Introduce el tipo de falla: ";
    getline(cin, fallaTipo);//(no poner cin)
    Falla * fallaB = new Falla(fallaTipo, 0, "1");
    //Escritura de archivo
    ofstream miArchivo("Lista.txt"); //Escribir un archivo
    if(!lista2->buscar(fallaB)){
      cout<<"No se encuentra"<<endl;
      miArchivo<<"No se encuentra"<<endl;
    }else{
      cout<< * lista2->buscar(fallaB)->getValor();
      miArchivo<< * lista2->buscar(fallaB)->getValor();
    }
    miArchivo.close();

    string hrs;
    cout<<"Ponga la hora que desea buscar: (formato de 24 hrs) "<<endl;
    cin>>hrs;

    ofstream miArchivo2("Lista2.txt");
      cout<<lista1->buscarHora(hrs);
      miArchivo2<<lista1->buscarHora(hrs);
    miArchivo2.close();
    return 0;
}

    

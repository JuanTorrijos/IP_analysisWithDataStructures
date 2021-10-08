#include "grafo.hpp"
#include <fstream>

int main(){
    Grafo<string> * ejemploGrafo=new Grafo<string>();
    ifstream datos;
    datos.open("bitacoraTest1.txt");
    string aux,ip1,ip2;
    
    //1.-Construcción del grafo
    while(datos.good()){
        getline(datos,aux,' ');
        getline(datos,aux,' ');
        getline(datos,aux,' ');
        getline(datos,ip1,' ');
        getline(datos,ip2,' ');
        getline(datos,aux);
        //Agregar ips de origen y destino si es que no existen
        if(!ejemploGrafo->buscarNodo(ip1))
            ejemploGrafo->insertarNodoGrafo(ip1);
        if(!ejemploGrafo->buscarNodo(ip2))
            ejemploGrafo->insertarNodoGrafo(ip2);
        //Agregar el arco
        Arco<string> * arcoNuevo= ejemploGrafo->buscarArco(ip1, ip2);
        if(arcoNuevo)
            arcoNuevo->setPeso(arcoNuevo->getPeso()+1);//Ya existe el arco entonces solo actualizo el peso
        else
            ejemploGrafo->agregarArco(ip1,ip2,1);        
    }

    ejemploGrafo->imprimirGrafo();

    //Solucion punto 4
    Lista<string> * listaIP;
    int max_peso=0;
    //Recorer la lista de nodosGrafo
    Nodo<NodoGrafo<string> *> * actual = ejemploGrafo->getNodos()->getHead();
    while(actual){
        //Recorer la lista de los arcos del nodoGrafo actual
        int suma_peso=0;
        Nodo<Arco<string>*> * nodoArco = actual->getValor()->getArcos()->getHead();
        //Sumar los pesos asociados a cada arco
        while(nodoArco){
            suma_peso=suma_peso + nodoArco->getValor()->getPeso();
            nodoArco=nodoArco->getSiguiente();
        }
        //Buscar el nodoGrafo o nodosGrafo que tenga la suma de pesos mayor
        if(suma_peso==max_peso){
            listaIP->agregarInicio(actual->getValor()->getValor());
        }else if(suma_peso>max_peso){
            max_peso=suma_peso;
            delete listaIP; //Liberar el espacio de memoria de la lista anterior
            listaIP = new Lista<string>();
            listaIP->agregarInicio(actual->getValor()->getValor());
        }
        actual=actual->getSiguiente();
    }

    cout<<"¿Cual o cuales son las direcciones IP que generan mas fallas?"<<endl;
    listaIP->imprimirLista();
    cout<<"Numero de fallas: "<<max_peso<<endl;

    //Solucion al punto 3
    listaIP=new Lista<string>();
    max_peso=0;
    //Recorrer la lista de nodoGrafo
    actual = ejemploGrafo->getNodos()->getHead();
    int suma_peso=0;
    while (actual){
        Nodo<NodoGrafo<string>*> * destino=actual;
        Nodo<NodoGrafo<string>*> * origen=ejemploGrafo->getNodos()->getHead();
        //Sumar por cada nodoGrafo la veces que tenga como nodoGrafo destino
        while(origen){
            Arco<string> * arco = ejemploGrafo->buscarArco(origen->getValor()->getValor(), destino->getValor()->getValor());
            if(arco){
                suma_peso=suma_peso + arco->getPeso();
            }
            origen=origen->getSiguiente();   
        }

        if(suma_peso==max_peso){
            listaIP->agregarInicio(destino->getValor()->getValor());
        }else if(suma_peso>max_peso){
            max_peso=suma_peso;
            delete listaIP; //Liberar el espacio de memoria de la lista anterior
            listaIP = new Lista<string>();
            listaIP->agregarInicio(destino->getValor()->getValor());
        }
        actual = actual->getSiguiente();
    }

    cout<<"¿Cual o cuales son las direcciones IP que reciben mas fallas?"<<endl;
    listaIP->imprimirLista();
    cout<<"Numero de fallas: "<<max_peso<<endl;

    datos.close();
    return 0;    
}
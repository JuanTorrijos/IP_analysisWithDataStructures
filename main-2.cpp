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

    //Solución punto 4
    Lista<string> * listaIP=new Lista<string>();
    int max_peso=0;
    //Recorrer la lista de nodosGrafo
    Nodo<NodoGrafo<string>*> * actual = ejemploGrafo->getNodos()->getHead();
    while(actual){
        //Recorrer la lista de los arcos del nodoGrafo actual
        int suma_peso=0;
        Nodo<Arco<string> *> * nodoarco = actual->getValor()->getArcos()->getHead();
        //Sumar los pesos asociados a cada arco
        while(nodoarco){
            suma_peso=suma_peso+nodoarco->getValor()->getPeso();
            nodoarco=nodoarco->getSiguiente();
        }
        //Buscar el nodoGrafo o nodosGrafo que tenga la suma de pesos mayor
        if(suma_peso==max_peso)
            listaIP->agregarInicio(actual->getValor()->getValor());
        else if(suma_peso>max_peso){
            max_peso=suma_peso;
            delete listaIP; //Liberar el espacio de memoria de la lista anterior
            listaIP= new Lista<string>();
            listaIP->agregarInicio(actual->getValor()->getValor());
        }
        actual=actual->getSiguiente();
    }

    cout<<"¿Cual o cuales son las direcciones IPs que generan más fallas?"<<endl;
    listaIP->imprimirLista();
    cout<<"Numero de fallas:"<< max_peso<<endl;

    //Solución al punto 3
    listaIP=new Lista<string>();
    max_peso=0;
    //Recorrer la lista de nodosGrafo
    actual = ejemploGrafo->getNodos()->getHead();
    while(actual){
        Nodo<NodoGrafo<string>*> * destino=actual;
        Nodo<NodoGrafo<string>*> * origen = ejemploGrafo->getNodos()->getHead();
        int suma_peso=0;
        //Sumar por cada nodoGrafo las veces que tengan como nodoGrafo destino
        while(origen){
            Arco<string> * arco = ejemploGrafo->buscarArco(origen->getValor()->getValor(), destino->getValor()->getValor());
            if(arco)
                suma_peso=suma_peso+arco->getPeso();
            origen=origen->getSiguiente();
        }

        if(suma_peso==max_peso)
            listaIP->agregarInicio(destino->getValor()->getValor());
        else if(suma_peso>max_peso){
            max_peso=suma_peso;
            delete listaIP; //Liberar el espacio de memoria de la lista anterior
            listaIP= new Lista<string>();
            listaIP->agregarInicio(destino->getValor()->getValor());
        }
        actual=actual->getSiguiente();
    }

    cout<<"¿Cuál o cuales son las direcciones IPs que reciben más fallas?"<<endl;
    listaIP->imprimirLista();
    cout<<"Numero de fallas:"<< max_peso<<endl;
    cout<<endl;

    Grafo<string> * ejemGrafo=new Grafo<string>();

    cout<<"Depth First: "<<endl;

    ejemploGrafo->DeepthFirst(5);
    cout<<endl;
    
    ofstream miArchivo2("Lista2.txt");

    datos.close();
    return 0;    
}
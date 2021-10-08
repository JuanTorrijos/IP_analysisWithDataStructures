#include <iostream>
#include "bst.hpp"
#include <fstream>

void buscarAccesoArbol(BST<Acceso *> * arbol, int accesos){
    if(arbol->buscarNodo(new Acceso("***", accesos))){
        cout<<"Las Ip con "<<accesos<<" accesos son: "<<endl;
        arbol->buscarNodo(new Acceso("***", accesos))->getValor()->imprimirVec();
    }else 
        cout<<"Ese numero de accesos no se encuentra en el arbol";
    cout<<endl;
}

int main(){
    BST<Acceso *> * arbol=new BST<Acceso *>();
    //Lectura de archivo separada
    ifstream datos;
    datos.open("bitacoraCompleta.txt");
    string aux,ipp;
    ListaDL<Acceso *> * lista1=new ListaDL<Acceso *>();
    while(datos.good()){
        getline(datos,aux,' ');
        getline(datos,aux,' ');
        getline(datos,aux,' ');
        getline(datos,ipp,':');
        getline(datos,aux);
        if(lista1->buscarListaDL(ipp)){
            Acceso * ippAcceso = lista1->buscarListaDL(ipp)->getValor();
            ippAcceso->setAccesos(ippAcceso->getAccesos()+1);
        }else{
            lista1->agregaFinal(new Acceso(ipp, 1));
        }

    }
    datos.close();

    //Escritura de archivo
    ofstream listaS("ListaAccesos.txt"); //Escribir un archivo
    //Agregar los elementos de la lista al arbol y tambien al archivo
    NodoDL<Acceso *> * nodo=lista1->getHead();
            while(nodo){
                arbol->agregaNodoIterativo(nodo->getValor());
                listaS<<* nodo->getValor();
                nodo=nodo->getSiguiente();
            }
    listaS.close();
    
    //lista1->imprimirLista();
    int opcion = 0;
    int num=0;
    while(opcion!=4){
        cout<<"Seleccione una opción (1-4) "<<endl;
        cout<<"Opción 1-Imprimir lista simple"<<endl;
        cout<<"Opción 2-Imprimir en Order y Preorder "<<endl;
        cout<<"Opción 3-Imprimir ip con acceso repetido "<<endl;
        cout<<"Opción 4-Salir "<<endl;
        cin>>opcion;
        if (opcion==1){
            lista1->imprimirLista();
        }
        else if (opcion==2){
            cout<<"inorder: "<<endl;
            arbol->imprimirArbolInOrder();

            cout<<"Preorder: "<<endl;
            arbol->imprimirArbolPreOrder();
        }
        else if (opcion==3){
            cout<<"Ponga el numero de alguno de los accesos repetidos: ";
            cin>>num;
            cout<<endl;
            buscarAccesoArbol(arbol, num);
        }
        else if(opcion == 4){
            cout<<"Camara *despedida chola*"<<endl;
        }else{
            cout<<"Opcion Invalida"<<endl;  
        }
    } 
    return 0;
}


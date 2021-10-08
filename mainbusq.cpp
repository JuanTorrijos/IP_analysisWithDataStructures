#include "bitacora.hpp"
#include <vector>
#include <fstream> //Biblioteca para lectura y escritura de archivos

int particion(vector<Bitacora *> &vec, int inicio, int fin){
    int pivote = vec[inicio]->getClave();
    int i = (inicio + 1); 
    for (int j=i;j<=fin;j++){ 
        if (vec[j]->getClave()<pivote){  
            swap(vec[i], vec[j]);
            i++;
        }
    }
    swap(vec[inicio], vec[i-1]);  
    return (i - 1); //posicion del pivote
}

//Funcion para integrar los arreglos o vectores usando recursion y la funcion anterior
//**********Big O de la función: O(n^2)*************
void quicksort(vector<Bitacora *> &vec, int inicio, int fin){
    if(inicio<fin){
        int pivote = particion(vec, inicio, fin);
        quicksort(vec, inicio, pivote-1);
        quicksort(vec, pivote+1, fin);
    }
}

template <class T>
//**********Big o de log(n)***************
int busqBinaria(vector<T> &vec, int valor){  
    int inicio = 0, fin = vec.size()-1, mitad, valorMitad;
    while (inicio<=fin){
        mitad = (fin+inicio)/2;
        valorMitad = vec[mitad]->getClave();

        if (valor==valorMitad)
            return mitad;

        else if (valor<valorMitad)
            fin = mitad-1;

        else
            inicio = mitad+1;
    }
    return inicio;
}

int main(){
    //Lectura de archivo separada
    ifstream datos;
    datos.open("bitacoraPrincipal.txt");
    string mes, dia, hora, ipp, falla;
    vector<Bitacora *> log; //vector con objetos dentro del heap

    while(datos.good()){
        getline(datos,mes,' ');
        getline(datos,dia,' ');
        getline(datos,hora,' ');
        getline(datos,ipp,' ');
        getline(datos,falla);
        log.push_back(new Bitacora(mes, dia, hora, ipp, falla));
    }
    datos.close();
    for(Bitacora * entry:log)
        entry->imprimirRegistro();

    cout<<"============Ordenados==========="<<endl;
    
    quicksort(log, 0, log.size()-1);
    for(Bitacora * entry:log)
        entry->imprimirRegistro();
    ofstream miArchivo("Ordenamiento.txt"); //Escribir un archivo
    for(int i=0;i<log.size();i++){
        miArchivo<<log[i]->getMes()<<" ";
        miArchivo<<log[i]->getDia()<<" ";
        miArchivo<<log[i]->getHora()<<" ";
        miArchivo<<log[i]->getIpp()<<" ";
        miArchivo<<log[i]->getFalla()<<"\n";
    }
    miArchivo.close();

    //Busquedas
    cout<<"=========Busquedas=========="<<endl;
    string mesIn, diaIn;
    string mesFin, diaFin;
    cout<<"Inserte fecha de inicio para buscar:"<<"\n"<<"Mes: ";
    cin>>mesIn;
    cout<<"\n"<<"Dia: ";
    cin>>diaIn;
    Bitacora busqIn(mesIn, diaIn, "***", "***", "***");

    cout<<"Inserte fecha de fin para buscar:"<<"\n"<<"Mes: ";
    cin>>mesFin;
    cout<<"\n"<<"Dia: ";
    cin>>diaFin;
    Bitacora busqFin(mesFin, diaFin, "***", "***", "***");

    cout<<"****Registros****"<<endl;
    int in=busqBinaria(log,busqIn.getClave());
    int finp=busqBinaria(log,busqFin.getClave());

    ofstream busqArchivo("Busqueda.txt"); //Escribir un archivo
    for (int i = in; i <= finp; i++){
        if (log[i]->getClave()<=busqFin.getClave()){
            log[i]->imprimirRegistro();
            busqArchivo<<log[i]->getMes()<<" ";
            busqArchivo<<log[i]->getDia()<<" ";
            busqArchivo<<log[i]->getHora()<<" ";
            busqArchivo<<log[i]->getIpp()<<" ";
            busqArchivo<<log[i]->getFalla()<<"\n";
        }
    }
    busqArchivo.close();
    return 0;
} 

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

template <typename T>
class NodoArbolBinario{
    T valor;
    NodoArbolBinario<T> * izq;
    NodoArbolBinario<T> * der;
    NodoArbolBinario<T> * padre;
    public:
        //Métodos get
        T getValor(){return this->valor;}
        NodoArbolBinario<T> * getIzq(){return this->izq;}
        NodoArbolBinario<T> * getDer(){return this->der;}
        NodoArbolBinario<T> * getPadre(){return this->padre;}
        //Métodos set
        void setValor(T valor){this->valor=valor;}
        void setIzq(NodoArbolBinario<T> * izq){this->izq=izq;}
        void setDer(NodoArbolBinario<T> * der){this->der=der;}
        void setPadre(NodoArbolBinario<T> * padre){this->padre=padre;}

        //Constructor
        NodoArbolBinario(NodoArbolBinario<T> * padre, T valor){
            this->valor=valor;
            this->izq=nullptr;
            this->der=nullptr;
            this->padre=padre;
        }

        //Destructor (delete)
        ~NodoArbolBinario(){
            //delete this->valor;
            cout<<"Ejecute el destructor"<<endl;
        } 

        //*******Complejidad: O(n)*********
        static void imprimirInOrder(NodoArbolBinario<T> * actual){
            if(!actual)
                return;
            else{
                imprimirInOrder(actual->izq);
                cout<<actual->valor->getAccesos()<<" ";
                imprimirInOrder(actual->der);
            }
        } 
    
        //*******Complejidad: O(n)*********
        static void preOrden(NodoArbolBinario<T> * actual){
            if(actual!=NULL){
            cout <<actual->valor->getAccesos() <<" ";
            preOrden(actual->izq);
            preOrden(actual->der);
            }
        }
        //*******Complejidad: O(n)*********
        static void postOrden(NodoArbolBinario<T> * actual){
            if(actual!=NULL){
                postOrden(actual->izq);
                postOrden(actual->der);
                cout <<* actual->valor << " ";
            }
        }
};

template <typename T>
class BST{
    NodoArbolBinario<T> * root;
    public:
        //Métodos get
        NodoArbolBinario<T> * getRoot(){return this->root;}
        //Métodos set
        void setRoot(NodoArbolBinario<T> * root){this->root=root;}
        //Método constructor
        BST(){
            this->root=nullptr;
        }

        ~BST(){

        }
        //*******Complejidad: O(1)*********
        void agregaNodoIterativo(T valor){
            NodoArbolBinario<T> * actual= this->root;
            NodoArbolBinario<T> * padre;
            //Arbol vacío
            if(!this->root){
                this->root= new NodoArbolBinario<T>(nullptr,valor);
                return;
            }
            if(!this->buscarNodo(valor)){
                //Árbol con valores
                //Encontrar al nodo padre
                while(actual){
                    padre=actual;
                    if(valor->getAccesos()<actual->getValor()->getAccesos()) //Determina la relación de orden
                        actual=actual->getIzq();
                    else
                        actual=actual->getDer();
                }
                if(valor->getAccesos()<padre->getValor()->getAccesos())//El elemento es menor que el padre 
                    padre->setIzq(new NodoArbolBinario<T>(padre,valor));
                else
                    padre->setDer(new NodoArbolBinario<T>(padre,valor));
            }else
                //cout<<"Valor repetido"<<endl;
                this->buscarNodo(valor)->getValor()->agregaIp(valor->getIp());          
        }

        //*******Complejidad: O(n)*********
        NodoArbolBinario<T> * buscarNodo(T valor){
            NodoArbolBinario<T> * actual=this->root;
            while(actual){
                if(actual->getValor()->getAccesos()==valor->getAccesos())
                    return actual;
                else    
                    actual=(actual->getValor()->getAccesos())>valor->getAccesos()?actual->getIzq():actual->getDer();
            }
            return nullptr;
        }
        //*******Complejidad: O(n)*********
        void imprimirArbolInOrder(){
            NodoArbolBinario<T>::imprimirInOrder(this->root);
            cout<<endl;
        }
        //*******Complejidad: O(n)*********
        void imprimirArbolPreOrder(){
            NodoArbolBinario<T>::preOrden(this->root);
            cout<<endl;
        }

};

template<typename T>
class NodoDL{
    T valor;
    NodoDL<T> * siguiente;
    NodoDL<T> * anterior;
    public:
    //Metodos
    T getValor(){return this->valor;}
    void setValor(T valor){this->valor=valor;}
    NodoDL<T> * getSiguiente(){return this->siguiente;}
    void setSiguiente(NodoDL<T> * siguiente){this->siguiente=siguiente;}
    NodoDL<T> * getAnterior(){return this->anterior;}
    void setAnterior(NodoDL<T> * anterior){this->anterior=anterior;}
    
    //Constructores
    NodoDL(T valor,NodoDL<T> * siguiente, NodoDL<T> * anterior){
        this->valor=valor;
        this->siguiente=siguiente;
        this->anterior=anterior;
    }
};

template<typename T>
class ListaDL{
    NodoDL<T> * head;
    int tam;
    public:
        int getTam(){return this->tam;}
        void setTam(int tam){this->tam=tam;}
        NodoDL<T> * getHead(){return this->head;}
        void setHead(NodoDL<T> * head){this->head=head;}
        

        ListaDL(){
            this->head=nullptr;
            this->tam=0;
        }
        //Funcion para agregar un elemento al inicio de la lista
        //*******Complejidad: O(n)*********
        string buscarHora(string hora){
            NodoDL<T> *nodo = head;
            stringstream aux; 
            bool a=0;
            while (nodo) {
                if ( nodo->getValor()->getHoraIndividual() == hora ){
                    aux << *nodo->getValor() << endl;
                    a=1;
                }
                nodo = nodo->getSiguiente();  
            }
            if(!a)
                return "No se encontro\n";
            return aux.str(); 
        }
        
        //Funcion para agregar un elemento al inicio de la lista
        //*******Complejidad: O(1)*********
        void agregarInicio(T valor){
            NodoDL<T> * nuevo=new NodoDL<T>(valor,this->head,nullptr); //Crear nuevo nodo
            if(this->head) //Lista con elementos
                this->head->setAnterior(nuevo);
            this->head=nuevo;//Actualizar el head de listaDL
            this->tam++; //Actualizar el tamaño            
        }
        //Funcion para agregar un elemento al inicio de la lista
        //*******Complejidad: O(1)*********
        void agregaFinal(T valor){
            NodoDL<T> * nuevo=new NodoDL<T>(valor,nullptr,nullptr);
            if(this->head){
                //Encontrar el ultimo nodo
                NodoDL<T> * nodo=this->head;
                while(nodo->getSiguiente()){
                    nodo=nodo->getSiguiente();
                }
                nodo->setSiguiente(nuevo);
                nuevo->setAnterior(nodo);
            }else
                this->head=nuevo;
            this->tam++;                      
        }
        //Funcion para agregar un elemento al inicio de la lista
        //*******Complejidad: O(n)*********
        void imprimirLista(){
            NodoDL<T> * nodo=this->head;
            while(nodo){
                cout<<* nodo->getValor();
                //nodo->getValor()->imprimirRegistro();
                //cout<<endl;
                nodo=nodo->getSiguiente();
            }
            cout<<endl;
        }
        //Funcion para agregar un elemento al inicio de la lista
        //*******Complejidad: O(n)*********
        NodoDL<T> * buscarListaDL(string valor){ 
            if(tam>0){
                NodoDL<T> * elem=this->head;
                int bandera = 0;
                do{
                    if (elem->getValor()->getIp()==valor){
                        bandera = 1;
                        return elem;
                    }
                    elem=elem->getSiguiente();
                }while(elem);
                if (bandera == 0)
                    return nullptr;
            }
            return nullptr;
        }

    
};

//template<typename T>
class Acceso{
    string ip;
    int accesos;
    vector<string> ips;

    public:
        //Getters
        int getAccesos(){return this->accesos;}
        string getIp(){return this->ip;}
        //Setters
        void setAccesos(int accesos){this->accesos=accesos;}
        void setIp(string ip){this->ip=ip;}
        //Constructores
        Acceso (string ip, int accesos){
            this->ip=ip;
            this->accesos=accesos;
            agregaIp(ip);
        }
        Acceso(){
            this->ip="***";
            this->accesos=0;
            agregaIp(ip);
        }

        friend ostream& operator<<(ostream& salida, const Acceso& objeto){
            salida<<objeto.ip<<" "<<objeto.accesos<<endl;

            return salida;
        }
        //*******Complejidad: O(1)*********
        void agregaIp(string ip){
            ips.push_back(ip);
        }
        //*******Complejidad: O(n)*********
        void imprimirVec(){
            for(int i=0; i<this->ips.size();i++){
                cout<<this->ips[i];
                cout<<endl;
            }
            
        }
};
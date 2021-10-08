#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;
class Bitacora{
    //Atributos
    private:
        string mes;
        string dia;
        string hora;
        string ipp;
        string falla;
        int clave;
    //Métodos
    public:
        string getMes(){return this->mes;}
        void setMes(string mes){this->mes=mes;}
        string getDia(){return this->dia;}
        void setDia(string dia){this->dia=dia;}
        string getHora(){return this->hora;}
        void setHora(string hora){this->hora=hora;}
        string getIpp(){return this->ipp;}
        void setIpp(string ipp){this->ipp=ipp;}
        string getFalla(){return this->falla;}
        void setFalla(string falla){this->falla=falla;}
        int getClave(){return this->clave;}
        void setClave(int clave){this->clave=clave;}
        string getHoraIndividual(){return this->hora.substr(0,2); }

        Bitacora(string mes, string dia, string hora, string ipp, string falla){
            this->mes=mes;
            this->dia=dia;
            this->hora=hora;
            this->ipp=ipp;
            this->falla=falla;
            //Llamar al metodo asignar clave
            this->asignarClave();
        }

        string mesANumero(){
            if(!this->mes.compare("Jun")) // ! not
                return "6";
            else if(!this->mes.compare("Jul"))
                return "7";
            else if(!this->mes.compare("Aug"))
                return "8";
            else if(!this->mes.compare("Sep"))
                return "9";
            else if(!this->mes.compare("Oct"))
                return "10";
            else if(!this->mes.compare("Nov"))
                return "11";
            else if(!this->mes.compare("Dec"))
                return "12";
            else
                return "0";
        }

        void asignarClave(){
            string id=this->mesANumero()+this->dia; //Concatenar el mes con el dia para crear la clave
            stringstream string2int(id);
            string2int>>this->clave; //Conversion de string a int        
        }

        void imprimirRegistro(){
            cout<<this->clave<<" "<<this->mes<<" "<<this->dia<<" "<<this->hora<<" "<<this->ipp<<" "<<this->falla<<"\n";
        }

        friend ostream& operator<<(ostream& salida, const Bitacora& objeto){
        salida<<objeto.mes<<" "<<objeto.dia<<" "<<objeto.hora<<" "<<objeto.ipp<<" "<<objeto.falla<<"\n";

        return salida;
        
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
                //cout<<nodo->getValor()<<" ";
                nodo->getValor()->imprimirRegistro();
                //cout<<endl;
                nodo=nodo->getSiguiente();
            }
            cout<<endl;
        }
        //Funcion para agregar un elemento al inicio de la lista
        //*******Complejidad: O(n)*********
        NodoDL<T> * buscarListaDL(string valor){ 
            cout<<"Entre a buscarListaDL"<<endl;
            cout<<*this->head->getValor()<<endl;
            if(tam>0){
                cout<<"entre al if 1";
                NodoDL<T> * elem=this->head;
                int bandera = 0;
                do{
                    if (elem->getValor()->getHora()==valor){
                        cout<<"entre al if 2xd";
                        bandera = 1;
                        return elem;
                    }
                    elem=elem->getSiguiente();
                }while(elem!=this->head);//revisar
                cout<<"entre al while";
                if (bandera == 0)
                    return nullptr;
            }
            cout<<"Voy a devolver el nullptr"<<endl;
            return nullptr;
        }

    
};

template <typename T>
class ListaCDL{
    NodoDL<T> * head;
    int tam;
    public:
        int getTam(){return this->tam;}
        void setTam(int tam){this->tam=tam;}
        NodoDL<T> * getHead(){return this->head;}
        void setHead(NodoDL<T> * head){this->head=head;}

        ListaCDL(){
            this->head=nullptr;
            this->tam=0;
        }

        void agregarVacio(T valor){
            NodoDL<T> * nuevo= new NodoDL<T>(valor,nullptr,nullptr);
            nuevo->setSiguiente(nuevo);
            nuevo->setAnterior(nuevo);
            this->head=nuevo;
        }
        
        //Funcion para agregar un elemento al inicio de la lista
        //Complejidad: O(n)
        void agregarInicio(T valor){
            if(this->head){ //Lista con nodos
                NodoDL<T> * nuevo=new NodoDL<T>(valor,this->head,this->head->getAnterior());
                this->head->getAnterior()->setSiguiente(nuevo);
                this->head->setAnterior(nuevo);
                this->head=nuevo;                
            }else //Lista sin nodos
                this->agregarVacio(valor);
            this->tam++;
        }

        //Funcion para agregar un elemento al final de la lista
        //Complejidad: O(n)
        void agregarFinal(T valor){
            if(this->head){ //Lista con nodos
                NodoDL<T> * nuevo=new NodoDL<T>(valor,this->head,this->head->getAnterior());
                this->head->getAnterior()->setSiguiente(nuevo);
                this->head->setAnterior(nuevo);                             
            }else //Lista sin nodos
                this->agregarVacio(valor);
            this->tam++;
        }

        //Funcion para imprimir los elementos de la lista
        //Complejidad: O(1)
        void imprimirLista(){
            if(this->head){
                NodoDL<T> * elemento=this->head;
                do{
                    cout<<elemento->getValor()->getFalla()<<endl;
                    cout<<"Ocurrencias: "<<elemento->getValor()->getOcurrencia()<<endl;
                    elemento=elemento->getSiguiente();
                }while(elemento!=this->head);
                cout<<endl;
            }else{
                cout<<"Lista vacía"<<endl;
            }   
        }

        //Funcion para imprimir los elementos de la lista usando la sobrecarga del operador
        //Complejidad: O(1)
        void imprimirListaSobrecarga(){
            if(this->head){
                NodoDL<T> * elemento=this->head;
                do{
                    cout<<* elemento->getValor()<<endl;
                    elemento=elemento->getSiguiente();
                }while(elemento!=this->head);
                cout<<endl;
            }else{
                cout<<"Lista vacía"<<endl;
            }   
        }

        //Funcion para leer (buscar) un elemento en la lista
        //Complejidad: O(n)
        NodoDL<T> * buscar(T valor){
            if(this->head){
                NodoDL<T> * elem=this->head;
                int bandera = 0;
                do{
                    if (elem->getValor()->getFalla()==valor->getFalla()){
                        bandera = 1;
                        return elem;
                    }
                    elem=elem->getSiguiente();
                }while(elem!=this->head);
                if (bandera == 0)
                    return nullptr;
            }
            return nullptr;
        }

};

class Falla{
  string falla;
  int ocurrencia;
  vector<int> mesOcurrencias;

  public:
    //Getters
    string getFalla(){return this->falla;}
    int getOcurrencia(){return this-> ocurrencia;}
    //Setters
    void setFalla(string falla){this->falla=falla;}
    void setOcurrencia(int ocurrencia){this->ocurrencia=ocurrencia;}

    //Constructores
    Falla(string falla, int ocurrencia, string mes){

      this->falla=falla;
      this->ocurrencia=ocurrencia;
      this->mesOcurrencias= vector<int>(12);
      stringstream geek(mes);//string to int(geekfgeeks)
      int x=0;
      geek>>x;
      this->mesOcurrencias[x-1]++;
    }
    
    void sumarOcurrencia(string mes){
        this->ocurrencia=this->ocurrencia+1;
        stringstream geek(mes);//string to int(geekfgeeks)
        int x=0;
        geek>>x;
        this->mesOcurrencias[x-1]++;
    }

    friend ostream& operator<<(ostream& salida, const Falla& objeto){
            salida<<objeto.falla<<endl
            <<"Ocurrencias Totales: "<<objeto.ocurrencia<<endl
            <<"Enero: "<<objeto.mesOcurrencias[0]<<endl
            <<"Febrero: "<<objeto.mesOcurrencias[1]<<endl
            <<"Marzo: "<<objeto.mesOcurrencias[2]<<endl
            <<"Abril: "<<objeto.mesOcurrencias[3]<<endl
            <<"Mayo: "<<objeto.mesOcurrencias[4]<<endl
            <<"Junio: "<<objeto.mesOcurrencias[5]<<endl
            <<"Juio: "<<objeto.mesOcurrencias[6]<<endl
            <<"Agosto: "<<objeto.mesOcurrencias[7]<<endl
            <<"Septiembre: "<<objeto.mesOcurrencias[8]<<endl
            <<"Octubre: "<<objeto.mesOcurrencias[9]<<endl
            <<"Noviembre: "<<objeto.mesOcurrencias[10]<<endl
            <<"Diciembre: "<<objeto.mesOcurrencias[11]<<endl;

            return salida;
    }

};
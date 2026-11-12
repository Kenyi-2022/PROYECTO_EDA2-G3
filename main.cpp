#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// ESTRUCTURA BASE
struct Pedido {
    string idPedido;
    string dniCliente;
    string tipoEnvio;
    int nivelPrioridad;
    double montoDolares;
    string fecha;
    string hora;
    string estado;
    
    Pedido(string id, string dni, string tipo, int prio, double monto, string f, string h, string est)
        : idPedido(id), dniCliente(dni), tipoEnvio(tipo), nivelPrioridad(prio), montoDolares(monto), fecha(f), hora(h), estado(est) {}
};

struct NodoHash {
    Pedido* pedido;
    NodoHash* siguiente;
    NodoHash(Pedido* p) : pedido(p), siguiente(nullptr) {}
};

struct NodoAVL {
    Pedido* pedido;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;
    NodoAVL(Pedido* p) : pedido(p), izq(nullptr), der(nullptr), altura(1) {}
};

//--------------------------------------INTEGRANTE 1---------------------------------------------------
class TablaHash{
private:
    NodoHash** tabla;
    int numBuckets;
    int cantidadElementos;

    int funcionHash(string llave) {
        int suma = 0;
        for (char c : llave) {
            suma += c; 
        }
        return suma % numBuckets; 
    }

public:
    TablaHash(int tamano) {
        numBuckets = tamano;
        cantidadElementos = 0;
        tabla = new NodoHash*[numBuckets];
        for(int i = 0; i < numBuckets; i++) {
            tabla[i] = nullptr;
        }
    }

    void insertarHash(Pedido* nuevoPedido) {
        int indice = funcionHash(nuevoPedido->idPedido);
        NodoHash* nuevoNodo = new NodoHash(nuevoPedido);
        nuevoNodo->siguiente = tabla[indice];
        tabla[indice] = nuevoNodo;
        cantidadElementos++;
    }

    Pedido* buscarHash(string idBuscado) {
        int indice = funcionHash(idBuscado);
        NodoHash* actual = tabla[indice];
        
        while (actual != nullptr) {
            if (actual->pedido->idPedido == idBuscado) {
                return actual->pedido;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    bool eliminarHash(string idEliminar) {
        int indice = funcionHash(idEliminar);
        NodoHash* actual = tabla[indice];
        NodoHash* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->pedido->idPedido == idEliminar) {
                if (anterior == nullptr) {
                    tabla[indice] = actual->siguiente;
                } else {
                    anterior->siguiente = actual->siguiente; 
                }
                delete actual; 
                cantidadElementos--;
                return true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }
        return false;
    }

    ~TablaHash() {
        for(int i = 0; i < numBuckets; i++) {
            NodoHash* actual = tabla[i];
            while(actual != nullptr) {
                NodoHash* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
        delete[] tabla;
    }
};

//--------------------------------------INTEGRANTE 2--------------------------------------------------
class ArbolAVL{

};
//--------------------------------------INTEGRANTE 3---------------------------------------------------
class MinHeap{

};


class SistemaLogistica {
private:
    TablaHash* KHash;

    // -----------INTEGRANTE 2---------------
    // ArbolAVL* *INICIAL DEL INTEGRANTE*Arbol; 
    
    // -----------INTEGRANTE 3----------------
    // MinHeap* *INICIAL DEL INTEGRANTE*Heap;

public:
    SistemaLogistica(int capHash) {
        KHash=new TablaHash(capHash);

        // *INICIAL DEL INTEGRANTE*Arbol = new ArbolAVL();
        
        // *INICIAL DEL INTEGRANTE*Heap = new MinHeap();
    }

    void registrarPedido(string id, string dni, string tipo, int prio, double monto, string f, string h, string est) {
        if(KHash->buscarHash(id) != nullptr){
            return;
        }

        Pedido* nuevoPedido = new Pedido(id, dni, tipo, prio, monto, f, h, est);

        KHash->insertarHash(nuevoPedido);
        
        // *INICIAL DEL INTEGRANTE*Arbol->insertarAVL(raizAVL, nuevoPedido); 

        // *INICIAL DEL INTEGRANTE*Heap->insertarHeap(nuevoPedido); 
    }

    Pedido* buscarPedidoPorID(string id){
        return KHash->buscarHash(id);
    }
    
    // DESTRUCTOR
    ~SistemaLogistica() {
        delete KHash;

        // delete *INICIAL DEL INTEGRANTE*Arbol;

        // delete *INICIAL DEL INTEGRANTE*Heap;

        // ------------- AQUI INSERTAN LA LOGICA ITERATIVA PARA EL DELETE DE CADA PEDIDO------------------
    }
};

// CARGA DE ARCHIVOS CSV 
void cargarCSV(string pedidos_masivos_G3, SistemaLogistica& sistema){
// void cargarCSV(string pedidos_pequenos_G3, SistemaLogistica& sistema){
    ifstream archivo(pedidos_masivos_G3);
    // ifstream archivo(pedidos_pequenos_G3);
    string linea;

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << pedidos_masivos_G3 << endl;
        // cout << "Error: No se pudo abrir el archivo " << pedidos_pequenos_G3 << endl;
        return;
    }

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string id, dni, tipo, prioStr, montoStr, fecha, hora, estado;

        getline(ss, id, ',');
        getline(ss, dni, ',');
        getline(ss, tipo, ',');
        getline(ss, prioStr, ',');
        getline(ss, montoStr, ',');
        getline(ss, fecha, ',');
        getline(ss, hora, ',');
        getline(ss, estado, ',');

        if (!id.empty()) {
            sistema.registrarPedido(id, dni, tipo, stoi(prioStr), stod(montoStr), fecha, hora, estado);
        }
    }
    archivo.close();
    cout << "Carga masiva completada exitosamente desde: " << pedidos_masivos_G3 << endl;
    // cout << "Carga pequena completada exitosamente desde: " << pedidos_pequenos_G3 << endl;
}

int main() {
    SistemaLogistica sistema(15000); // MINIMO DE PEDIDOS PARA LA PRUEBA: 10000 (los 15000 son de referencia nomas)
    cargarCSV("pedidos_pequenos.csv", sistema);

    return 0;
}
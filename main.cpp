#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

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

    void liberarPedidos() {
        for (int i = 0; i < numBuckets; i++) {
            NodoHash* actual = tabla[i];
            while (actual != nullptr) {
                delete actual->pedido;
                actual->pedido = nullptr;
                actual = actual->siguiente;
            }
        }
    }

    void mostrarEstadisticas() {
        int bucketsUsados = 0;
        int colisiones = 0;
        for (int i = 0; i < numBuckets; i++) {
            if (tabla[i] != nullptr) {
                bucketsUsados++;
                int count = 0;
                NodoHash* aux = tabla[i];
                while (aux != nullptr) {
                    count++;
                    aux = aux->siguiente;
                }
                if (count > 1) colisiones += (count - 1);
            }
        }
        cout << "Total elementos en Hash: " << cantidadElementos << endl;
        cout << "Buckets utilizados: " << bucketsUsados << " / " << numBuckets << endl;
        cout << "Colisiones resueltas por encadenamiento: " << colisiones << endl;
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

    bool actualizarEstadoPedido(string id, string nuevoEstado) {
        Pedido* p = KHash->buscarHash(id);
        if (p != nullptr) {
            p->estado = nuevoEstado;
            return true;
        }
        return false;
    }

    bool eliminarPedido(string id) {
        Pedido* p = KHash->buscarHash(id);
        if (p == nullptr) return false;

        KHash->eliminarHash(id);
        // *INICIAL DEL INTEGRANTE*Arbol->eliminarAVL(id);
        // *INICIAL DEL INTEGRANTE*Heap->cancelarPedido(id);

        delete p;
        return true;
    }

    void verMetricasHash() {
        KHash->mostrarEstadisticas();
    }
    
    // DESTRUCTOR
    ~SistemaLogistica() {
        KHash->liberarPedidos();
        delete KHash;

        // delete *INICIAL DEL INTEGRANTE*Arbol;

        // delete *INICIAL DEL INTEGRANTE*Heap;

        // ------------- AQUI INSERTAN LA LOGICA ITERATIVA PARA EL DELETE DE CADA PEDIDO------------------
    }
};

// CARGA DE ARCHIVOS CSV 
void cargarCSV(string nombreArchivo, SistemaLogistica& sistema){
    ifstream archivo(nombreArchivo);
    string linea;

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
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
    cout << "Carga masiva completada exitosamente desde: " << nombreArchivo << endl;
}

int main() {
    SistemaLogistica sistema(15000); // MINIMO DE PEDIDOS PARA LA PRUEBA: 10000 (los 15000 son de referencia nomas)
    cargarCSV("pedidos_masivos_G3.csv", sistema);
    // cargarCSV("pedidos_pequenos_G3.csv", sistema);
    
    return 0;
}
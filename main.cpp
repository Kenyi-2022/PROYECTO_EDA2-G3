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
        Pedido* nuevoPedido = new Pedido(id, dni, tipo, prio, monto, f, h, est);

        
        KHash->insertarHash(nuevoPedido);
        
        // *INICIAL DEL INTEGRANTE*Arbol->insertarAVL(raizAVL, nuevoPedido); 

        // *INICIAL DEL INTEGRANTE*Heap->insertarHeap(nuevoPedido); 
    }
    
    
    // DESTRUCTOR
    ~SistemaLogistica() {
        delete KHash;

        // delete *INICIAL DEL INTEGRANTE*Arbol;

        // delete *INICIAL DEL INTEGRANTE*Heap;

        // ------------- AQUI INSERTAN LA LOGICA ITERATIVA PARA EL DELETE DE CADA PEDIDO------------------
    }
};

// CARGA DE ARCHIVOS CSV (aun no se q nombre de archivo ponerle xd)
void cargarCSV(string *NombredeArchivo*, SistemaLogistica& sistema){

}

int main() {
    SistemaLogistica sistema(15000); // MINIMO DE PEDIDOS PARA LA PRUEBA: 10000 (los 15000 son de referencia nomas)
    return 0;
}
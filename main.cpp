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


//--------------------------------------INTEGRANTE 3---------------------------------------------------
class MinHeap{

};

//--------------------------------------ARBOL AVL--------------------------------------------------
class ArbolAVL {
private:
    NodoAVL* raiz;

    int mayor(int a, int b) {
        return a > b ? a : b;
    }

    int obtenerAltura(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    int obtenerBalance(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
    }

    NodoAVL* rotarDerecha(NodoAVL* y) {
        NodoAVL* x = y->izq;
        NodoAVL* T2 = x->der;

        x->der = y;
        y->izq = T2;

        y->altura = 1 + mayor(obtenerAltura(y->izq),
                              obtenerAltura(y->der));

        x->altura = 1 + mayor(obtenerAltura(x->izq),
                              obtenerAltura(x->der));

        return x;
    }

    NodoAVL* rotarIzquierda(NodoAVL* x) {
        NodoAVL* y = x->der;
        NodoAVL* T2 = y->izq;

        y->izq = x;
        x->der = T2;

        x->altura = 1 + mayor(obtenerAltura(x->izq),
                              obtenerAltura(x->der));

        y->altura = 1 + mayor(obtenerAltura(y->izq),
                              obtenerAltura(y->der));

        return y;
    }

    NodoAVL* insertarAVL(NodoAVL* nodo, Pedido* pedidoNuevo) {
        if (nodo == nullptr) {
            return new NodoAVL(pedidoNuevo);
        }

        if (pedidoNuevo->fecha < nodo->pedido->fecha) {
            nodo->izq = insertarAVL(nodo->izq, pedidoNuevo);
        }
        else if (pedidoNuevo->fecha > nodo->pedido->fecha) {
            nodo->der = insertarAVL(nodo->der, pedidoNuevo);
        }
        else if (pedidoNuevo->hora < nodo->pedido->hora) {
            nodo->izq = insertarAVL(nodo->izq, pedidoNuevo);
        }
        else if (pedidoNuevo->hora > nodo->pedido->hora) {
            nodo->der = insertarAVL(nodo->der, pedidoNuevo);
        }
        else if (pedidoNuevo->idPedido < nodo->pedido->idPedido) {
            nodo->izq = insertarAVL(nodo->izq, pedidoNuevo);
        }
        else if (pedidoNuevo->idPedido > nodo->pedido->idPedido) {
            nodo->der = insertarAVL(nodo->der, pedidoNuevo);
        }
        else {
            return nodo;
        }

        nodo->altura = 1 + mayor(obtenerAltura(nodo->izq),
                                 obtenerAltura(nodo->der));

        int balance = obtenerBalance(nodo);

        // Caso LL
        if (balance > 1 &&
            pedidoNuevo->fecha < nodo->izq->pedido->fecha) {
            return rotarDerecha(nodo);
        }

        if (balance > 1 &&
            pedidoNuevo->fecha == nodo->izq->pedido->fecha &&
            pedidoNuevo->hora < nodo->izq->pedido->hora) {
            return rotarDerecha(nodo);
        }

        if (balance > 1 &&
            pedidoNuevo->fecha == nodo->izq->pedido->fecha &&
            pedidoNuevo->hora == nodo->izq->pedido->hora &&
            pedidoNuevo->idPedido < nodo->izq->pedido->idPedido) {
            return rotarDerecha(nodo);
        }

        // Caso RR
        if (balance < -1 &&
            pedidoNuevo->fecha > nodo->der->pedido->fecha) {
            return rotarIzquierda(nodo);
        }

        if (balance < -1 &&
            pedidoNuevo->fecha == nodo->der->pedido->fecha &&
            pedidoNuevo->hora > nodo->der->pedido->hora) {
            return rotarIzquierda(nodo);
        }

        if (balance < -1 &&
            pedidoNuevo->fecha == nodo->der->pedido->fecha &&
            pedidoNuevo->hora == nodo->der->pedido->hora &&
            pedidoNuevo->idPedido > nodo->der->pedido->idPedido) {
            return rotarIzquierda(nodo);
        }

        // Caso LR
        if (balance > 1 &&
            pedidoNuevo->fecha > nodo->izq->pedido->fecha) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }

        if (balance > 1 &&
            pedidoNuevo->fecha == nodo->izq->pedido->fecha &&
            pedidoNuevo->hora > nodo->izq->pedido->hora) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }

        if (balance > 1 &&
            pedidoNuevo->fecha == nodo->izq->pedido->fecha &&
            pedidoNuevo->hora == nodo->izq->pedido->hora &&
            pedidoNuevo->idPedido > nodo->izq->pedido->idPedido) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }

        // Caso RL
        if (balance < -1 &&
            pedidoNuevo->fecha < nodo->der->pedido->fecha) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }

        if (balance < -1 &&
            pedidoNuevo->fecha == nodo->der->pedido->fecha &&
            pedidoNuevo->hora < nodo->der->pedido->hora) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }

        if (balance < -1 &&
            pedidoNuevo->fecha == nodo->der->pedido->fecha &&
            pedidoNuevo->hora == nodo->der->pedido->hora &&
            pedidoNuevo->idPedido < nodo->der->pedido->idPedido) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

public:
    ArbolAVL() : raiz(nullptr) {}

    void insertar(Pedido* pedidoNuevo) {
        raiz = insertarAVL(raiz, pedidoNuevo);
    }
};
class SistemaLogistica {
private:
    TablaHash* KHash;

    // -----------INTEGRANTE 2---------------
    // MinHeap* Heap;

    // -----------INTEGRANTE 3---------------
    ArbolAVL* DArbol;

public:
    SistemaLogistica(int capHash) {
        // KHash = new TablaHash(capHash);

        DArbol = new ArbolAVL();

        // Heap = new MinHeap();
    }

    void registrarPedido(string id, string dni, string tipo, int prio,
                         double monto, string f, string h, string est) {
        Pedido* nuevoPedido = new Pedido(
            id, dni, tipo, prio, monto, f, h, est
        );

        // KHash->insertarHash(nuevoPedido);

        DArbol->insertar(nuevoPedido);

        // Heap->insertarHeap(nuevoPedido);
    }

    ~SistemaLogistica() {
        // delete KHash;

        delete DArbol;

        // delete Heap;
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

    cargarCSV("pedidos_masivos_G3.csv", sistema);

    return 0;
}
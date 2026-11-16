#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
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
        if (balance > 1 && obtenerBalance(nodo->izq) >= 0) {
            return rotarDerecha(nodo);
        }

        // Caso RR
        if (balance < -1 && obtenerBalance(nodo->der) <= 0) {
            return rotarIzquierda(nodo);
        }

        // Caso LR
        if (balance > 1 && obtenerBalance(nodo->izq) < 0) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }

        // Caso RL
        if (balance < -1 && obtenerBalance(nodo->der) > 0) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    NodoAVL* eliminarAVL(NodoAVL* nodo,
                         string fecha,
                         string hora,
                         string idPedido) {
        if (nodo == nullptr) {
            return nullptr;
        }

        if (fecha < nodo->pedido->fecha ||
            (fecha == nodo->pedido->fecha &&
             hora < nodo->pedido->hora) ||
            (fecha == nodo->pedido->fecha &&
             hora == nodo->pedido->hora &&
             idPedido < nodo->pedido->idPedido)) {
            nodo->izq = eliminarAVL(nodo->izq, fecha, hora, idPedido);
        }
        else if (fecha > nodo->pedido->fecha ||
                 (fecha == nodo->pedido->fecha &&
                  hora > nodo->pedido->hora) ||
                 (fecha == nodo->pedido->fecha &&
                  hora == nodo->pedido->hora &&
                  idPedido > nodo->pedido->idPedido)) {
            nodo->der = eliminarAVL(nodo->der, fecha, hora, idPedido);
        }
        else {
            if (nodo->izq == nullptr || nodo->der == nullptr) {
                NodoAVL* hijo = nodo->izq != nullptr ? nodo->izq : nodo->der;
                delete nodo->pedido;
                delete nodo;
                return hijo;
            }

            NodoAVL* sucesor = nodo->der;
            while (sucesor->izq != nullptr) {
                sucesor = sucesor->izq;
            }

            Pedido* pedidoOriginal = nodo->pedido;
            nodo->pedido = sucesor->pedido;
            sucesor->pedido = pedidoOriginal;

            nodo->der = eliminarAVL(
                nodo->der,
                pedidoOriginal->fecha,
                pedidoOriginal->hora,
                pedidoOriginal->idPedido
            );
        }

        nodo->altura = 1 + mayor(obtenerAltura(nodo->izq),
                                 obtenerAltura(nodo->der));

        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izq) >= 0) {
            return rotarDerecha(nodo);
        }

        if (balance > 1 && obtenerBalance(nodo->izq) < 0) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }

        if (balance < -1 && obtenerBalance(nodo->der) <= 0) {
            return rotarIzquierda(nodo);
        }

        if (balance < -1 && obtenerBalance(nodo->der) > 0) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    void vaciarArbol(NodoAVL* nodo) {
        if (nodo == nullptr) {
            return;
        }

        vaciarArbol(nodo->izq);
        vaciarArbol(nodo->der);

        delete nodo->pedido;
        delete nodo;
    }

    void inOrderLimitado(NodoAVL* nodo, int& contador) {
    if (nodo == nullptr || contador >= 30) {
        return;
    }

    inOrderLimitado(nodo->izq, contador);

    if (contador >= 30) {
        return;
    }

        cout << left
            << setw(18) << nodo->pedido->idPedido
            << setw(14) << nodo->pedido->fecha
            << setw(10) << nodo->pedido->hora
            << setw(15) << nodo->pedido->estado
            << endl;

    contador++;

    if (contador >= 30) {
        return;
    }

    inOrderLimitado(nodo->der, contador);
}

public:
    ArbolAVL() : raiz(nullptr) {}

    ~ArbolAVL() {
        vaciarArbol(raiz);
    }

    void insertar(Pedido* pedidoNuevo) {
        raiz = insertarAVL(raiz, pedidoNuevo);
    }

    void eliminar(string fecha, string hora, string idPedido) {
        raiz = eliminarAVL(raiz, fecha, hora, idPedido);
    }
    
    void imprimirPrimeros30() {
    int contador = 0;

    cout << "\n--- Primeros 30 pedidos ordenados ---\n";

    inOrderLimitado(raiz, contador);
    }


private:
    void consultarPorRangoAVL(NodoAVL* nodo,
                              string fechaInicio,
                              string fechaFin,
                              int& cantidad,
                              double& montoTotal) {
        if (nodo == nullptr) {
            return;
        }

        if (nodo->pedido->fecha > fechaFin) {
            consultarPorRangoAVL(
                nodo->izq, fechaInicio, fechaFin, cantidad, montoTotal
            );
        }
        else if (nodo->pedido->fecha < fechaInicio) {
            consultarPorRangoAVL(
                nodo->der, fechaInicio, fechaFin, cantidad, montoTotal
            );
        }
        else {
            cantidad++;
            montoTotal += nodo->pedido->montoDolares;

            consultarPorRangoAVL(
                nodo->izq, fechaInicio, fechaFin, cantidad, montoTotal
            );

            consultarPorRangoAVL(
                nodo->der, fechaInicio, fechaFin, cantidad, montoTotal
            );
        }
    }

public:
    void consultarPorRango(string fechaInicio, string fechaFin) {
        int cantidad = 0;
        double montoTotal = 0.0;

        consultarPorRangoAVL(
            raiz, fechaInicio, fechaFin, cantidad, montoTotal
        );

        cout << "\n--- Auditoria por rango de fechas ---\n";
        cout << "Cantidad de pedidos: " << cantidad << endl;
        cout << "Monto total: $" << montoTotal << endl;
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
        KHash = new TablaHash(capHash);

        DArbol = new ArbolAVL();

        // Heap = new MinHeap();
    }

    void registrarPedido(string id, string dni, string tipo, int prio,
                         double monto, string f, string h, string est) {
        if (KHash->buscarHash(id) != nullptr) {
            return;
        }

        Pedido* nuevoPedido = new Pedido(
            id, dni, tipo, prio, monto, f, h, est
        );

        KHash->insertarHash(nuevoPedido);

        DArbol->insertar(nuevoPedido);

        // Heap->insertarHeap(nuevoPedido);
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
        DArbol->eliminar(p->fecha, p->hora, p->idPedido);
        return true;
    }

    void verMetricasHash() {
        KHash->mostrarEstadisticas();
    }
    
    ~SistemaLogistica() {
        delete DArbol;
        delete KHash;

        // delete Heap;
    }

void consultarRango(string fechaInicio, string fechaFin) {
    DArbol->consultarPorRango(fechaInicio, fechaFin);
}
void mostrarPedidosOrdenados() {
    DArbol->imprimirPrimeros30();
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
    cout << "Carga completada exitosamente desde: " << nombreArchivo << endl;
}

int main() {
    SistemaLogistica sistema(15000);

    string archivoCSV;
    int opcionCSV;

    cout << "\n========== SELECCION DE ARCHIVO CSV ==========" << endl;
    cout << "1. Pedidos Masivos" << endl;
    cout << "2. Pedidos Pequenos" << endl;
    cout << "Seleccione el archivo que desea cargar: ";
    cin >> opcionCSV;

    if (opcionCSV == 1) {
        archivoCSV = "PedidosCSV/pedidos_masivos_G3.csv";
    }
    else if (opcionCSV == 2) {
        archivoCSV = "PedidosCSV/pedidos_pequenos_G3.csv";
    }
    else {
        cout << "Opcion invalida. Se cargaran los pedidos masivos." << endl;
        archivoCSV = "PedidosCSV/pedidos_masivos_G3.csv";
    }

    auto inicioCarga = chrono::high_resolution_clock::now();
    cargarCSV(archivoCSV, sistema);
    auto finCarga = chrono::high_resolution_clock::now();
    double msCarga = chrono::duration<double, milli>(
        finCarga - inicioCarga
    ).count();

    cout << "Tiempo de carga: " << msCarga << " ms" << endl;

    int opcion;

    while (true) {
        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "1. Busqueda por ID (Hash)\n";
        cout << "2. Despacho de Pedidos Urgentes (Heap - Pendiente Integrante 2)\n";
        cout << "3. Consulta ordenada por fecha y hora (In-Order AVL)\n";
        cout << "4. Consulta por rango de fechas (Arbol AVL)\n";
        cout << "5. Ver metricas del Hash\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
        {
            string id;
            cout << "Ingrese el ID del pedido: ";
            cin >> id;

            Pedido* pedido = sistema.buscarPedidoPorID(id);
            if (pedido == nullptr) {
                cout << "Busqueda ID inexistente ('PD-888888').\n";
            }
            else {
                cout << "ID: " << pedido->idPedido
                     << " | Fecha: " << pedido->fecha
                     << " | Hora: " << pedido->hora
                     << " | Estado: " << pedido->estado
                     << endl;
            }
            break;
        }

        case 2:
            cout << "Despacho de pedidos urgentes pendiente de implementacion.\n";
            break;

        case 3:
            sistema.mostrarPedidosOrdenados();
            break;

        case 4: {
            string fechaInicio;
            string fechaFin;

            cout << "Ingrese la fecha inicial: ";
            cin >> fechaInicio;

            cout << "Ingrese la fecha final: ";
            cin >> fechaFin;

            sistema.consultarRango(fechaInicio, fechaFin);
            break;
        }

        case 5:
            sistema.verMetricasHash();
            break;

        case 6:
            cout << "Saliendo del programa...\n";
            return 0;

        default:
            cout << "Opcion invalida.\n";
        }
    }

    return 0;
}
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
    cout << "Carga completada exitosamente desde: " << nombreArchivo << endl;
}

int main() {
    SistemaLogistica sistema(15000); // MINIMO DE PEDIDOS PARA LA PRUEBA: 10000 (los 15000 son de referencia nomas)
    // 1. CARGA DE ARCHIVO CSV (Cambiar comentario segun prueba (PEQUENOS O MASIVOS))
    auto t1 = chrono::high_resolution_clock::now();
    cargarCSV("pedidos_masivos_G3.csv", sistema);
    // cargarCSV("pedidos_pequenos_G3.csv", sistema);
    auto t2 = chrono::high_resolution_clock::now();
    double msCarga = chrono::duration<double, milli>(t2 - t1).count();

    // BUSQUEDA POR ID EN TABLA HASH
    auto t3 = chrono::high_resolution_clock::now();
    Pedido* encontrado = sistema.buscarPedidoPorID("PD-000025");
    auto t4 = chrono::high_resolution_clock::now();
    double msBusqueda = chrono::duration<double, milli>(t4 - t3).count();

    // INSERCION INDIVIDUAL DE PEDIDO
    auto t5 = chrono::high_resolution_clock::now();
    sistema.registrarPedido("PD-099999", "74859612", "Express", 1, 320.50, "2026-11-15", "14:30:00", "Pendiente");
    auto t6 = chrono::high_resolution_clock::now();
    double msInsercion = chrono::duration<double, milli>(t6 - t5).count();

    // ACTUALIZACION DE ESTADO 
    auto t7 = chrono::high_resolution_clock::now();
    for (int i = 1; i <= 10; i++) {
        string id = (i < 10) ? "PD-00000" + to_string(i) : "PD-000010";
        sistema.actualizarEstadoPedido(id, "Entregado");
    }
    auto t8 = chrono::high_resolution_clock::now();
    double msActualizacion = chrono::duration<double, milli>(t8 - t7).count();

    // ELIMINACION DE PEDIDOS 
    auto t9 = chrono::high_resolution_clock::now();
    for (int i = 11; i <= 20; i++) {
        sistema.eliminarPedido("PD-0000" + to_string(i));
    }
    auto t10 = chrono::high_resolution_clock::now();
    double msEliminacion = chrono::duration<double, milli>(t10 - t9).count();

    // ----------- INTEGRANTE 2 (ARBOL AVL: Consulta ordenada y por rango) ------------
    // auto t11 = chrono::high_resolution_clock::now();
    // sistema.consultarOrdenadoAVL();
    // auto t12 = chrono::high_resolution_clock::now();

    // ----------- INTEGRANTE 3 (MIN-HEAP: Despacho de 100 pedidos urgentes) ----------- 
    // auto t13 = chrono::high_resolution_clock::now();
    // sistema.despacharUrgentesHeap(100);
    // auto t14 = chrono::high_resolution_clock::now();

    cout << "\n RESULTADOS DE TIEMPO" << endl;
    cout << "1. Carga masiva:               " << msCarga << " ms" << endl;
    cout << "2. Busqueda por ID (Hash):     " << msBusqueda << " ms" << endl;
    cout << "3. Insercion individual:       " << msInsercion << " ms" << endl;
    cout << "4. Actualizacion (10 pedidos): " << msActualizacion << " ms" << endl;
    cout << "5. Eliminacion (10 pedidos):   " << msEliminacion << " ms" << endl;

    cout << "\nVERIFICACION Y METRICAS HASH" << endl;
    if (encontrado != nullptr) {
        cout << "Pedido encontrado: " << encontrado->idPedido
             << " | DNI: " << encontrado->dniCliente
             << " | Monto: $" << encontrado->montoDolares << endl;
    }
    Pedido* noExiste = sistema.buscarPedidoPorID("PD-888888");
    cout << "Busqueda ID inexistente ('PD-888888'): "
         << (noExiste == nullptr ? "Retorno puntero vacio correctamente" : "Error") << endl;

    sistema.verMetricasHash();

    return 0;
}
#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#include <iostream>
#include <string>

// Nota: Asume que struct Pedido ya está definido en el main o en un archivo compartido.
class MinHeap {
private:
    Pedido** arreglo;    // Arreglo dinámico de PUNTEROS a Pedido
    int capacidad;
    int tamanio;

    void redimensionar() {
        capacidad *= 2;
        Pedido** nuevoArreglo = new Pedido*[capacidad];
        for (int i = 0; i < tamanio; i++) {
            nuevoArreglo[i] = arreglo[i];
        }
        delete[] arreglo;
        arreglo = nuevoArreglo;
    }

    void flotar(int indice) {
        while (indice > 0) {
            int padre = (indice - 1) / 2;
            if (arreglo[indice]->nivelPrioridad < arreglo[padre]->nivelPrioridad) {
                Pedido* temp = arreglo[indice];
                arreglo[indice] = arreglo[padre];
                arreglo[padre] = temp;
                indice = padre;
            } else {
                break;
            }
        }
    }

    void hundir(int indice) {
        int menor = indice;
        int izquierda = 2 * indice + 1;
        int derecha = 2 * indice + 2;

        if (izquierda < tamanio && arreglo[izquierda]->nivelPrioridad < arreglo[menor]->nivelPrioridad) {
            menor = izquierda;
        }

        if (derecha < tamanio && arreglo[derecha]->nivelPrioridad < arreglo[menor]->nivelPrioridad) {
            menor = derecha;
        }

        if (menor != indice) {
            Pedido* temp = arreglo[indice];
            arreglo[indice] = arreglo[menor];
            arreglo[menor] = temp;
            hundir(menor);
        }
    }

public:
    MinHeap(int capacidadInicial = 15000) {
        capacidad = capacidadInicial;
        tamanio = 0;
        arreglo = new Pedido*[capacidad];
    }

    ~MinHeap() {
        delete[] arreglo;
    }

    void insertarHeap(Pedido* pedido) {
        if (tamanio >= capacidad) {
            redimensionar();
        }
        arreglo[tamanio] = pedido;
        flotar(tamanio);
        tamanio++;
    }

    bool extraerMin(Pedido*& resultado) {
        if (tamanio == 0) return false;
        resultado = arreglo[0];
        arreglo[0] = arreglo[tamanio - 1];
        tamanio--;
        hundir(0);
        return true;
    }

    int obtenerTamanio() const {
        return tamanio;
    }

    bool estaVacio() const {
        return tamanio == 0;
    }
};

#endif
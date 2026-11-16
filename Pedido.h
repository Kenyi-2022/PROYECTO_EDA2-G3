#ifndef PEDIDO_H
#define PEDIDO_H

#include <string>

struct Pedido {
    std::string idPedido;       // Ej: PD-000001
    std::string dniCliente;     // Ej: 45879123
    std::string tipoEnvio;      // Normal, Express, SameDay
    int nivelPrioridad;         // Nivel de urgencia
    double montoDolares;        // Monto en dólares
    std::string fecha;          // YYYY-MM-DD
    std::string hora;           // HH:MM:SS
    std::string estado;         // Pendiente, EnTransito, Cancelado, etc.
    
    // Constructor con los 8 parámetros requerido por el main y la carga CSV
    Pedido(std::string id, std::string dni, std::string tipo, int prio, double monto, std::string f, std::string h, std::string est)
        : idPedido(id), dniCliente(dni), tipoEnvio(tipo), nivelPrioridad(prio), montoDolares(monto), fecha(f), hora(h), estado(est) {}
};

#endif
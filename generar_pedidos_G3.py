import csv
import random

tipos_envio = ["Normal", "Express", "SameDay"]
estados = ["Pendiente"]

with open('pedidos_masivos_G3.csv', mode='w', newline='') as file:
# with open('pedidos_pequenos_G3.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["idPedido", "dniCliente", "tipoEnvio", "nivelPrioridad", "montoDolares", "fecha", "hora", "estado"])
    # for i in range(1, 15001):
    for i in range(1, 31):
        id_pedido = f"PD-{str(i).zfill(6)}"
        dni = str(random.randint(10000000, 99999999))
        tipo = random.choice(tipos_envio)
        prioridad = random.randint(1, 10)
        monto = round(random.uniform(10.0, 1000.0), 2)
        dia = str(random.randint(1, 30)).zfill(2)
        fecha = f"2026-06-{dia}"
        hora = f"{str(random.randint(0, 23)).zfill(2)}:{str(random.randint(0, 59)).zfill(2)}:{str(random.randint(0, 59)).zfill(2)}"
        estado = "Pendiente"
        
        writer.writerow([id_pedido, dni, tipo, prioridad, monto, fecha, hora, estado])

print("Archivo generado con éxito.")
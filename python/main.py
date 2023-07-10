import random
from datetime import datetime, timedelta

# Constantes
NUM_TRANSACCIONES = 20
NOMBRES = ["fabricio", "jesus", "chambilla", "heider", "maria", "chino", "shinobu", "ximena", "carlos", "carla", "carlota", "hinatsu", "kimika", "makoto", "hitori", "bocchi", "chinatsu", "kyouko", "saya", "sayon", "samanta"]
FECHA_INICIO = datetime.now()
MIN_MONTO = 1
MAX_MONTO = 1000
MONTO_MINIMO_UNICO = 10
MONTO_MAXIMO_UNICO = 999

# Inicializa las variables
fecha_actual = FECHA_INICIO
monto_minimo_usado = False
monto_maximo_usado = False

with open("transacciones.txt", "w") as f:
    for i in range(NUM_TRANSACCIONES):
        # Garantiza que los montos mínimo y máximo únicos se utilicen
        if i == NUM_TRANSACCIONES - 2 and not monto_minimo_usado:
            monto = MONTO_MINIMO_UNICO
            monto_minimo_usado = True
        elif i == NUM_TRANSACCIONES - 1 and not monto_maximo_usado:
            monto = MONTO_MAXIMO_UNICO
            monto_maximo_usado = True
        else:
            monto = random.randint(MIN_MONTO, MAX_MONTO)

        # Asegura que el emisor y el receptor sean diferentes
        emisor, receptor = random.sample(NOMBRES, 2)

        # Asegura que la fecha de la transacción es posterior a la anterior
        fecha_actual += timedelta(days=random.randint(1, 3))

        # Escribe la transacción al archivo
        f.write(f"{monto} {emisor} {receptor} {fecha_actual.day} {fecha_actual.month} {fecha_actual.year}\n")

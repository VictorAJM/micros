import serial
import random
ser = serial.Serial('COM5',baudrate=4800,timeout=1)

def leer_desde_com1():
    try:
        # Lee datos desde el puerto COM1
        datos = ser.read()
        datos2 = int.from_bytes(datos)
        # Decodifica los datos a una cadena
        # Devuelve los datos decodificados
        return datos2
    except serial.SerialException as e:
        print(f"Error al leer desde COM1: {e}")

# Usa la función para leer datos y muéstralos
while 1:
  if random.randint(0,2) == 1:
    datos_recibidos = leer_desde_com1()
    g = (datos_recibidos/255.0*5.0)
    print(f"Datos recibidos desde COM1: {g:.2f} V", end='\r')


import serial
import tkinter as tk
import threading
import time


colores_notas = ['red', 'orange', 'yellow', 'green', 'blue', 'purple', 'pink', 'white']

ser = serial.Serial('COM6', 9600, bytesize=8, stopbits=2, timeout=5)

notas = [
    238,  # Do (C4)
    212,  # Re (D4)
    189,  # Mi (E4)
    178,  # Fa (F4)
    159,  # Sol (G4)
    142,  # La (A4)
    127,  # Si (B4)
    119   # Do (C5)
]

martinillo = [0, 1, 2, 0, 2, 3, 4, 2, 3, 4, 0, 1, 2, 0, 2, 3, 4, 2, 3, 4, 3, 2, 1, 0]
cero = 0
uno = 1 

def conv(x):
    return int.from_bytes(x, byteorder='big')

def enviar_valor_ocr0(valor):
    ser.write(valor.to_bytes(1, byteorder='big'))

def mostrar_nota(color, nota):
    label.config(text="Color: " + color + "\nNota a tocar: " + str(nota), fg=color)
    color_box.config(bg=color, width=20, height=10)

def mostrar_resultados(errores, duracion):
    resultados_label.config(text=f"Número de errores: {errores}\nTiempo total de ejecución: {duracion:.2f} segundos", fg='black')

def resetear_interfaz():
    label.config(text="Presione el boton blanco para comenzar...")
    color_box.config(bg='white')
    resultados_label.after(5000, lambda: resultados_label.config(text=""))

def ejecutar_interfaz():
    root = tk.Tk()
    root.title("Interfaz de Martinillo")
    root.geometry("300x300") 

    global label
    label = tk.Label(root, text="Presione el boton blanco para comenzar...", font=("Arial", 12))
    label.pack()

    global color_box
    color_box = tk.Label(root, text="", font=("Arial", 12))
    color_box.pack()

    global resultados_label
    resultados_label = tk.Label(root, text="", font=("Arial", 12))
    resultados_label.pack()

    root.mainloop()

def ejecutar_cancion():
    errores = 0
    inicio = time.time()

    print("Iniciando la canción...")
    for nota_codigo in martinillo:
        color = colores_notas[nota_codigo]
        mostrar_nota(color, nota_codigo+1)
        while True:
            if ser.in_waiting > 0:
                comando_recibido = conv(ser.read())
                if int(comando_recibido) == nota_codigo:
                    print("Nota correcta")
                    enviar_valor_ocr0(notas[nota_codigo])
                    break
                else:
                    print("Nota incorrecta")
                    ser.write(uno.to_bytes(1, byteorder='big'))
                    errores += 1
                    continue
                    
    fin = time.time()
    duracion = fin - inicio
    mostrar_resultados(errores, duracion)
    resetear_interfaz()
    print("cancion terminada")
    while True:
        if ser.in_waiting > 0:
            comando_recibido = conv(ser.read())
            if comando_recibido == 6:
                ser.write(cero.to_bytes(1, byteorder='big')) 
                print("Canción iniciada\n")
                break
            else:
                ser.write(uno.to_bytes(1, byteorder='big'))
                print("letra incorrecta\n")
                print(comando_recibido)
    ejecutar_cancion()         


interfaz_thread = threading.Thread(target=ejecutar_interfaz)
interfaz_thread.start()

print("Presione el boton blanco para comenzar...")
while True:
    if ser.in_waiting > 0:
        comando_recibido = conv(ser.read())
        if comando_recibido == 10: 
            print("Canción iniciada\n")
            ejecutar_cancion()
            break

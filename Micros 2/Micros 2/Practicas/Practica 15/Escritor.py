import serial
import keyboard
import time

ser = serial.Serial('COM5', 4800,bytesize=8, stopbits=2, timeout=10)

try:
    while True:
        key = keyboard.read_event()
        
        if key.event_type == keyboard.KEY_DOWN:
            if key.name == "space":
                character = " "
            elif key.name == "backspace":
                character = "/"
            else:
                character = key.name

            ser.write(character.encode())
            time.sleep(0.1)

except KeyboardInterrupt
    ser.close()


import serial
import time
import matplotlib.pyplot as plt
from collections import deque
import numpy as np
from matplotlib.colors import LinearSegmentedColormap
from scipy.interpolate import interp1d
from matplotlib.widgets import Button
import mplcursors


ser= serial.Serial('COM2',9600, bytesize=8 , stopbits=2 , timeout=5)

def update_bar(i):
    def eve(event):
        ser.write(i.to_bytes(1, byteorder='big'))
        time.sleep(0.1)
        tipo = ser.read()
        tipo = int.from_bytes(tipo, byteorder='big')
        value1 = ser.read()
        value1 = int.from_bytes(value1, byteorder='big')
        value2 = ser.read()
        value2 = int.from_bytes(value2, byteorder='big')
        
        if not tipo:
            value=value1-value2
        else:
            value=value1
            
        bars[i].set_height(value)
        for txt in ax.texts:
            if txt.get_position()[0] == bars[i].get_x() + bars[i].get_width() / 2:
                txt.remove()
        ax.annotate(f'{value:.1f}', (bars[i].get_x() + bars[i].get_width() / 2, bars[i].get_height()),
                    ha='center', va='bottom', fontsize=8, color='white')
        plt.draw()
    return eve

fig, ax = plt.subplots()
ax.set_ylim(-60, 160.0)
ax.set_xlim(-1, 1)
ax.set_title('Temperatura', color='lightgray', fontsize=14, fontweight='bold')
values = np.array([0])
labels = ['Temp']
colors = ['blue']
bars = ax.bar(labels, values, color=colors)

button_width = 0.2
button_height = 0.05
button = ['']

for i, label in enumerate(labels):
    button_ax = plt.axes([0.42 + i * 0.2, 0.01, button_width, button_height])
    button[i] = Button(button_ax, f'Update {label}')
    button[i].on_clicked(update_bar(i))

#ax.grid(color='white', linestyle='--', linewidth=0.5)
ax.set_facecolor('#121212')
ax.xaxis.label.set_color('white')  
ax.yaxis.label.set_color('white')
ax.spines['bottom'].set_color('white')  
ax.spines['left'].set_color('white')
ax.tick_params(axis='x', colors='white')
ax.tick_params(axis='y', colors='white')
ax.set_ylabel('Valor', color='lightgray', fontsize=12, fontweight='bold')
fig.patch.set_facecolor('#121212')

plt.show()


ser.close()



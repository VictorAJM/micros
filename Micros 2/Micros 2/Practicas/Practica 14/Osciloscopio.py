import serial
import time
import matplotlib.pyplot as plt
from collections import deque
import numpy as np
from matplotlib.colors import LinearSegmentedColormap
from scipy.interpolate import interp1d


ser= serial.Serial('COM4', 9600, bytesize=8 , stopbits=2 , timeout=5)

plt.ion()
fig, ax = plt.subplots()
ax.set_ylim(0, 5.0)
ax.set_xlim(0, 100)
line, = ax.plot([], [], color='blue', linewidth=2.5)
values = deque(maxlen=100)

plt.style.use('seaborn-darkgrid')
ax.grid(color='gray', linestyle='--', linewidth=0.5)
ax.set_facecolor('#121212')

ax.set_xlabel('Tiempo', color='lightgray', fontsize=12, fontweight='bold')
ax.set_ylabel('Amplitud', color='lightgray', fontsize=12, fontweight='bold')
ax.set_title('Osciloscopio', color='lightgray', fontsize=14, fontweight='bold')

ax.tick_params(axis='both', colors='lightgray')
for spine in ax.spines.values():
    spine.set_edgecolor('lightgray')

fig.patch.set_facecolor('#121212')

def update(data):
    x = np.arange(len(data))
    f = interp1d(x, data, kind='linear')
    x_smooth = np.linspace(0, len(data) - 1, 1000)
    line.set_xdata(x_smooth)
    line.set_ydata(f(x_smooth))
    ax.relim()
    ax.autoscale_view()
    plt.draw()
    plt.pause(0.001)
    

while(True):
    val=ser.read()
    valu=int.from_bytes(val, byteorder='big')/10
    values.append(valu)
    update(values)
    


ser.close()


import serial
import time
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
arduino=serial.Serial('COM2',9600)
try: 
    
    time.sleep(1)
    while True: 
        dato=arduino.readline().decode('utf-8')
        print(dato)
except:
    print("error")
arduino.close()


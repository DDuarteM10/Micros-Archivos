import serial
import time
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
arduino=serial.Serial('COM2',9600)
time.sleep(2)
dato=arduino.readline()
print(dato)
arduino.close()


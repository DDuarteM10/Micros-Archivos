import serial
import time 
import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation



arduino=serial.Serial('COM7',9600)
Menu=eval(input("1:Recibe datos 2: enviar datos "))


if Menu==1:
    try: 
        while True:

            if (arduino.inWaiting()>0):
                 datos = arduino.readline().decode('utf-8')
                 print(datos)
                 
            
    except:
        print("error")
    arduino.close()

if Menu==2:
    Num=str(input("Digite datos a enviar "))
    lista=list(Num)
    for n in lista:
        arduino.write(str(n).encode('utf-8')) 
        time.sleep(0.2)
        
    arduino.close()



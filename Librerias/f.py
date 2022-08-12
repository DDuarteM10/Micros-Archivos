import serial
import time 
import matplotlib.pyplot as plt

import matplotlib.animation as animation



arduino=serial.Serial('COM2',9600)
Menu=eval(input("1:Graficar 2: enviar numero 2bits "))
if Menu==1:
    try: 
        fig = plt.figure()
        ax = fig.add_subplot(1,1,1)
        xdatos, ydatos = [], []


        while True:

            if (arduino.inWaiting()>0):
                def animate(i,xdatos,ydatos):
                    datos = arduino.readline().decode()
                    datos = float(datos)
                    xdatos.append(i)
                    ydatos.append(datos)
                    ax.clear()
                    ax.plot(xdatos,ydatos)
                ani = animation.FuncAnimation(fig,animate, fargs=(xdatos,ydatos))
                plt.show()


    except:
        print("error")
    arduino.close()

if Menu==2:
    Num=int(input("Digite numero de dos bits "))
    arduino.write(str(Num).encode()) 
    time.sleep(1)
    arduino.close()



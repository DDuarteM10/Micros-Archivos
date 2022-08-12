import serial 
import matplotlib.pyplot as plt
fig1 = plt.figure("Graficas")
fig1.subplots_adjust(hspace=0.5, wspace=0.5)
Stm=serial.Serial('COM2',9600)
x1datos, y1datos = [], []
x2datos, y2datos = [], []
x3datos, y3datos = [], []
Condicion=True
Condicion1=True
Condicion2=True
Condicion3=True
Contador1=0
Contador2=0
Contador3=0
SumaDistancia=0
SumTemp=0
SumLux=0

solid=2

try:
    while Condicion:
        print("Distancia")
        P1 = fig1.add_subplot(2, 2, 1)
        while Condicion1:
            
            if (Stm.inWaiting()>0):
                Contador1=Contador1+1
                datos1 = Stm.readline().decode("utf-8")
                print(str(datos1))
                x1datos.append(Contador1)
                SumaDistancia=SumaDistancia+float(datos1)
                y1datos.append(datos1)
                P1.plot(x1datos,y1datos,"b")
                P1.set_xlabel("Tiempo")
                P1.set_ylabel("Distancia")
                P1.set_title("Distancia")
                P1.grid(color='gray', linestyle='dashed', linewidth=1, alpha=0.4)
                # Pintar los ejes pasando por (0,0)
                P1.axhline(0, color='black', linewidth=0.5)
                
               # Condicion=False
            if Contador1==10:
                Condicion1=False
        
        print("LM35")
        P2 = fig1.add_subplot(2, 2, 2)
        while Condicion2:
            if (Stm.inWaiting()>0):
                Contador2=Contador2+1
                datos2 = Stm.readline().decode("utf-8")
                print(str(datos2))
                x2datos.append(Contador2)
                SumTemp=SumTemp+float(datos2)
                y2datos.append(datos1)
                P2.plot(x2datos,y2datos,"r")
                P2.set_xlabel("Tiempo")
                P2.set_ylabel("Temperatura")
                P2.set_title("Temperatura")
                P2.grid(color='gray', linestyle='dashed', linewidth=1, alpha=0.4)
                # Pintar los ejes pasando por (0,0)
                P2.axhline(0, color='black', linewidth=0.5)
            if Contador2==10:
                Condicion2=False    
               # Condicion=False
        Promediotemp=(SumTemp/10)       
        P3 = fig1.add_subplot(2, 2, 3)
        print("Lumens")
        while Condicion3:
            if (Stm.inWaiting()>0):
                Contador3=Contador3+1
                datos3 = Stm.readline().decode("utf-8")
                print(str(datos3))
                x3datos.append(Contador3)
                SumLux=SumLux+float(datos3)
                y3datos.append(datos3)
                P3.plot(x3datos,y3datos,"g")
                P3.set_xlabel("Tiempo")
                P3.set_ylabel("Temperatura")
                P3.set_title("Temperatura")
                P3.grid(color='gray', linestyle='dashed', linewidth=1, alpha=0.4)
                # Pintar los ejes pasando por (0,0)
                P3.axhline(0, color='black', linewidth=0.5)
            
            if Contador3==10:
                Condicion3=False
                Condicion=False
    PromedioDistancia=(SumaDistancia/10)
    print("Promedio Distancia:"+str(PromedioDistancia))
    print("Promedio Temperatura:"+str(Promediotemp))
    Promediotlumens=(SumLux/10)
    print("Promedio Lumens:"+str(Promediotlumens))
    plt.show()
except:
    print("Terminado")
    arduino.close()


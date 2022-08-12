import random
import matplotlib.pyplot as plt



p = list(range(14))
q = [random.randint(0, 20) for _ in range(14)]


def filtro(p, q):
    q = [random.randint(0, 20) for _ in range(14)]
    return p, q


fig1 = plt.figure("Filtro")
fig1.subplots_adjust(hspace=0.5, wspace=0.5)

for i in range(1, 4):
    p, q = filtro(p, q)

    ax = fig1.add_subplot(2, 2, i)
    ax.plot(p,q,"g--")
    ax.set_xlabel("z")
    ax.set_ylabel("w")
    ax.set_title("cordenadas xy")
    ax.grid(color='gray', linestyle='dashed', linewidth=1, alpha=0.4)
    # Pintar los ejes pasando por (0,0)
    ax.axhline(0, color='black', linewidth=0.5)



def npotencia(array, exp):
    return [n ** exp for n in array]



plt.show()

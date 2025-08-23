import matplotlib
matplotlib.use('TkAgg')
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

filename = "Gaussian_Solution.txt"
data = np.loadtxt(filename)

N = data.shape[1]
L = 1.0  
x = np.linspace(0, L, N)

fig, ax = plt.subplots()
line, = ax.plot(x, data[0])
ax.set_ylim(np.min(data), np.max(data))
ax.set_xlabel("L")
ax.set_ylabel("Temperatura")
ax.set_title("Evolucion de la temperatura en 1D")

def update(frame):
    line.set_ydata(data[frame])
    return line,

ani = animation.FuncAnimation(fig, update, frames=len(data), interval=50, blit=True)
plt.show()

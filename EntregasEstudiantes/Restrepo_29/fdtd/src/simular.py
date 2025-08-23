import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Leer datos
data = pd.read_csv("campos.csv")

tmax = data["t"].max() + 1
xmax = data["pos"].max() + 1

# Reorganizar en matrices
E = data["E"].values.reshape((tmax, xmax))
H = data["H"].values.reshape((tmax, xmax))

x = np.arange(xmax)

# Crear figura con dos paneles
fig, axs = plt.subplots(2, 1, figsize=(8, 6), sharex=True)

# --- Campo eléctrico ---
lineE, = axs[0].plot([], [], color="blue")
axs[0].set_xlim(0, xmax)
axs[0].set_ylim(E.min()*1.2, E.max()*1.2)
axs[0].set_ylabel("E(x,t)")
axs[0].set_title("Campo eléctrico E")

# --- Campo magnético ---
lineH, = axs[1].plot([], [], color="red")
axs[1].set_xlim(0, xmax)
axs[1].set_ylim(H.min()*1.2, H.max()*1.2)
axs[1].set_xlabel("Posición x")
axs[1].set_ylabel("H(x,t)")
axs[1].set_title("Campo magnético H")

# Inicializar
def init():
    lineE.set_data([], [])
    lineH.set_data([], [])
    return lineE, lineH

# Función de animación
def update(n):
    lineE.set_data(x, E[n])
    lineH.set_data(x, H[n])
    return lineE, lineH

# Crear animación
ani = animation.FuncAnimation(fig, update, frames=tmax,
                              init_func=init, blit=True, interval=50)

plt.tight_layout()
plt.show()






import os
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import griddata

import matplotlib.animation as animation



#base_dir = os.path.dirname(os.path.abspath(__file__))
#ruta_entrada = os.path.join(base_dir, "..", "resultados_2D", "TDSE","evolucion_completa.txt")
#ruta_salida_gif = os.path.join(base_dir, "..", "resultados_2D", "evolucion_3D.gif")



# --- Leer datos ---
file_path = "../resultados_2D/TDSE/evolucion_completa.txt"  # Cambia a tu ruta
data = np.loadtxt(file_path)

# Columnas: t, x, y, valor (puede ser ψ o |ψ|²)
t = data[:, 0]
x = data[:, 1]
y = data[:, 2]
psi = data[:, 3]

# --- Encontrar tiempos únicos ---
times = np.unique(t)

# --- Crear malla para graficar ---
Nx = len(np.unique(x))
Ny = len(np.unique(y))

# --- Función para extraer datos de un tiempo ---
def get_frame_data(t_val):
    mask = t == t_val
    X = x[mask].reshape(Nx, Ny)
    Y = y[mask].reshape(Nx, Ny)
    Z = psi[mask].reshape(Nx, Ny)  # Usa |psi|² si corresponde
    return X, Y, Z

# --- Configuración de la figura ---
fig = plt.figure(figsize=(7, 5))
ax = fig.add_subplot(111, projection='3d')

X, Y, Z = get_frame_data(times[0])
surf = [ax.plot_surface(X, Y, Z, cmap="viridis")]

ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('|ψ|²')
ax.set_title(f"Evolución temporal - t={times[0]}")

# --- Función de actualización para la animación ---
def update(frame):
    ax.clear()
    X, Y, Z = get_frame_data(times[frame])
    ax.plot_surface(X, Y, Z, cmap="viridis")
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('|ψ|²')
    ax.set_title(f"Evolución temporal - t={times[frame]:.3f}")
    return ax,

# --- Crear animación ---
ani = animation.FuncAnimation(fig, update, frames=len(times), blit=False)

# Guardar como GIF (necesitas instalar ImageMagick o Pillow)
ani.save("evolucion_TDSE.gif", writer='pillow', fps=3)

plt.show()
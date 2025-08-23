# --- Librerías ---
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # necesario para superficies 3D
from matplotlib.animation import FuncAnimation
from matplotlib.animation import FuncAnimation, PillowWriter
from mpl_toolkits.mplot3d import Axes3D


# --- Leer archivo ---
# Ajusta la ruta si tu archivo no está en la carpeta actual
data = np.loadtxt("docs/datos.txt", comments="#")

# Columnas: t, k, Ex, Hy
t = data[:,0]
k = data[:,1].astype(int)
Ex = data[:,2]
Hy = data[:,3]

# --- Reorganizar en forma de matrices (tiempo x espacio) ---
nt = len(np.unique(t))
nx = len(np.unique(k))

T = np.unique(t)
K = np.unique(k)

Ex_grid = Ex.reshape((nt, nx))
Hy_grid = Hy.reshape((nt, nx))

# ============================
# 1) Gráfica 3D de Ex
# ============================
fig = plt.figure(figsize=(10,6))
ax = fig.add_subplot(111, projection='3d')

Tmesh, Kmesh = np.meshgrid(T, K, indexing="ij")
ax.plot_surface(Tmesh, Kmesh, Ex_grid, cmap="viridis")

ax.set_xlabel("Tiempo t")
ax.set_ylabel("Posición k")
ax.set_zlabel("Ex")
ax.set_title("Evolución espacio-temporal de Ex")
plt.show()

# ============================
# 2) Gráfica 3D de Hy
# ============================
fig = plt.figure(figsize=(10,6))
ax = fig.add_subplot(111, projection='3d')

ax.plot_surface(Tmesh, Kmesh, Hy_grid, cmap="plasma")

ax.set_xlabel("Tiempo t")
ax.set_ylabel("Posición k")
ax.set_zlabel("Hy")
ax.set_title("Evolución espacio-temporal de Hy")
plt.show()

# ============================
# 3) Gráficas 2D para instantes seleccionados
# ============================

# Columnas: t, k, Ex, Hy
t = data[:,0]
k = data[:,1].astype(int)
Ex = data[:,2]
Hy = data[:,3]

# --- Reorganizar en forma de matrices (tiempo x espacio) ---
nt = len(np.unique(t))
nx = len(np.unique(k))

T = np.unique(t)
K = np.unique(k)

Ex_grid = Ex.reshape((nt, nx))
Hy_grid = Hy.reshape((nt, nx))

pos_idx = nx // 2   # punto en el medio del espacio
plt.figure(figsize=(10,6))
plt.plot(T, Ex_grid[:,pos_idx], label="Ex")
plt.plot(T, Hy_grid[:,pos_idx], label="Hy")
plt.xlabel("Tiempo t")
plt.ylabel("Amplitud")
plt.title(f"Evolución temporal en k={K[pos_idx]}")
plt.legend()
plt.grid()
plt.show()

# ============================
# 4) Gráfica Ex y Hy vs Espacio (para un tiempo fijo)
# ============================
time_idx = nt // 2  # instante intermedio
plt.figure(figsize=(10,6))
plt.plot(K, Ex_grid[time_idx,:], label="Ex")
plt.plot(K, Hy_grid[time_idx,:], label="Hy")
plt.xlabel("Posición k")
plt.ylabel("Amplitud")
plt.title(f"Distribución espacial en t={T[time_idx]:.2f}")
plt.legend()
plt.grid()
plt.show()


# --- Elegimos un instante de tiempo ---
time_idx = nt // 2   # instante intermedio
t0 = T[time_idx]

Ex_t0 = Ex_grid[time_idx, :]
Hy_t0 = Hy_grid[time_idx, :]

# --- Gráfico estilo propagación ---
fig = plt.figure(figsize=(10,7))
ax = fig.add_subplot(111, projection='3d')

# Campo eléctrico Ex (eje Y)
ax.plot(K, Ex_t0, np.zeros_like(K), label="Ex", color="blue")

# Campo magnético H (eje Z)
ax.plot(K, np.zeros_like(K), Hy_t0, label="Hy", color="red")

# --- Agregar ejes centrales ---
# Línea eje propagación (k)
ax.plot([K.min(), K.max()], [0,0], [0,0], color="black", linestyle="--")

# Línea eje Ex (vertical en k=K[0])
ax.plot([0,0], [Ex_t0.min(), Ex_t0.max()], [0,0], color="blue", linestyle="--")

# Línea eje Hy (profundidad en k=K[0])
ax.plot([0,0], [0,0], [Hy_t0.min(), Hy_t0.max()], color="red", linestyle="--")

# Ajustes visuales
ax.set_xlabel("Dirección de propagación (k)")
ax.set_ylabel("Campo eléctrico Ex")
ax.set_zlabel("Campo magnético Hy")
ax.set_title(f"Frente de onda EM en t = {t0:.2f}")
ax.legend()

plt.show()

# ============================
# 5) Gráfica Ex y Hy vs tiempo (para un posición espacial k fija)
# ============================

# --- Elegimos una posición espacial ---
pos_idx = nx // 2   # punto intermedio en el espacio
k0 = K[pos_idx]

Ex_k0 = Ex_grid[:, pos_idx]
Hy_k0 = Hy_grid[:, pos_idx]

# --- Gráfico estilo propagación temporal ---
fig = plt.figure(figsize=(10,7))
ax = fig.add_subplot(111, projection='3d')

# Campo eléctrico Ex (eje Y)
ax.plot(T, Ex_k0, np.zeros_like(T), label="Ex", color="blue")

# Campo magnético Hy (eje Z)
ax.plot(T, np.zeros_like(T), Hy_k0, label="Hy", color="red")

# --- Agregar ejes centrales ---
# Línea eje temporal (t)
ax.plot([T.min(), T.max()], [0,0], [0,0], color="black", linestyle="--")

# Línea eje Ex
ax.plot([0,0], [Ex_k0.min(), Ex_k0.max()], [0,0], color="blue", linestyle="--")

# Línea eje Hy
ax.plot([0,0], [0,0], [Hy_k0.min(), Hy_k0.max()], color="red", linestyle="--")

# Ajustes visuales
ax.set_xlabel("Tiempo (t)")
ax.set_ylabel("Campo eléctrico Ex")
ax.set_zlabel("Campo magnético Hy")
ax.set_title(f"Frente de onda EM en k = {k0}")
ax.legend()

plt.show()


# ============================
# 6) Evolución temporal  de los campos Ex, Hy 
# ============================


# === 1. Leer archivo ===
# Reemplaza 'datos.txt' por el nombre real de tu archivo
data = np.loadtxt("docs/datos.txt", skiprows=1)  # salta la cabecera

t = data[:,0]
k = data[:,1].astype(int)
Ex = data[:,2]
Hy = data[:,3]

# === 2. Reorganizar datos ===
# Encontrar número de tiempos y número de posiciones
nt = len(np.unique(t))
nk = len(np.unique(k))

t_vals = np.unique(t)
k_vals = np.unique(k)

# Reorganizar en matrices [tiempo, espacio]
Ex = Ex.reshape(nt, nk)
Hy = Hy.reshape(nt, nk)

# === 3. Crear animación ===
fig, ax = plt.subplots()
line1, = ax.plot([], [], lw=2, label="Ex")
line2, = ax.plot([], [], lw=2, label="Hy")

ax.set_xlim(k_vals.min(), k_vals.max())
ax.set_ylim(min(Ex.min(), Hy.min()), max(Ex.max(), Hy.max()))
ax.set_xlabel("Posición k")
ax.set_ylabel("Campo")
ax.legend()

def init():
    line1.set_data([], [])
    line2.set_data([], [])
    return line1, line2

def update(frame):
    line1.set_data(k_vals, Ex[frame,:])
    line2.set_data(k_vals, Hy[frame,:])
    ax.set_title(f"Tiempo t = {t_vals[frame]:.2f}")
    return line1, line2

ani = FuncAnimation(fig, update, frames=nt,
                    init_func=init, blit=True, interval=100)

# === 4. Guardar en GIF o MP4 (opcional) ===
ani.save("python/ondaCF.gif", writer="pillow")
plt.show()

# ============================
# 7) Evolución temporal  de los campos Ex, Hy  (para un posición espacial k fija)
# ============================


# === 1. Cargar datos ===
data = np.loadtxt("docs/datos.txt", skiprows=1)

t = data[:,0]
k = data[:,1].astype(int)
Ex = data[:,2]
Hy = data[:,3]

# Filtrar para k = 100
k0 = 100
mask = (k == k0)
t_vals = t[mask]
Ex_vals = Ex[mask]
Hy_vals = Hy[mask]

# === 2. Crear figura 3D ===
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Límites fijos en ±0.1
ax.set_xlim(t_vals.min(), t_vals.max())
ax.set_ylim(-0.1, 0.1)
ax.set_zlim(-0.1, 0.1)

ax.set_xlabel("Tiempo (t)")
ax.set_ylabel("Campo eléctrico Ex")
ax.set_zlabel("Campo magnético Hy")
ax.set_title(f"Frente de onda EM en k = {k0}")

# === Ejes axiales centrados (manuales) ===
ax.plot([t_vals.min(), t_vals.max()], [0,0], [0,0], 'k--')   # eje t
ax.plot([0,0], [-0.1,0.1], [0,0], 'k--')                     # eje Ex
ax.plot([0,0], [0,0], [-0.1,0.1], 'k--')                     # eje Hy

# === 3. Líneas de las ondas ===
line_ex, = ax.plot([], [], [], color="blue", label="Ex")
line_hy, = ax.plot([], [], [], color="red", label="Hy")
ax.legend()

# === 4. Animación ===
def init():
    line_ex.set_data([], [])
    line_ex.set_3d_properties([])
    line_hy.set_data([], [])
    line_hy.set_3d_properties([])
    return line_ex, line_hy

def update(frame):
    # Ex (azul) sobre eje Y
    line_ex.set_data(t_vals[:frame], Ex_vals[:frame])
    line_ex.set_3d_properties(np.zeros_like(Ex_vals[:frame]))
    # Hy (rojo) sobre eje Z
    line_hy.set_data(t_vals[:frame], np.zeros_like(Hy_vals[:frame]))
    line_hy.set_3d_properties(Hy_vals[:frame])
    return line_ex, line_hy

ani = FuncAnimation(fig, update, frames=len(t_vals),
                    init_func=init, blit=True, interval=50)

# === Guardar como GIF ===
ani.save("python/onda_emtCF.gif", writer=PillowWriter(fps=20))

# === Mostrar animación en ventana ===
plt.show()



# ============================
# 7) Evolución espacial de los campos Ex, Hy  (para un tiempo t fijo)
# ============================

# === 1. Cargar datos ===
data = np.loadtxt("docs/datos.txt", skiprows=1)

t = data[:,0]
k = data[:,1].astype(int)
Ex = data[:,2]
Hy = data[:,3]

# === Fijamos un tiempo t0 ===
t0 = 100
mask = (t == t0)
k_vals = k[mask]
Ex_vals = Ex[mask]
Hy_vals = Hy[mask]

# === 2. Crear figura 3D ===
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Límites
ax.set_xlim(k_vals.min(), k_vals.max())
ax.set_ylim(-0.1, 0.1)
ax.set_zlim(-0.1, 0.1)

ax.set_xlabel("Número de onda (k)")
ax.set_ylabel("Campo eléctrico Ex")
ax.set_zlabel("Campo magnético Hy")
ax.set_title(f"Frente de onda EM en t = {t0}")

# === Ejes axiales centrados (manuales) ===
ax.plot([k_vals.min(), k_vals.max()], [0,0], [0,0], 'k--')   # eje k
ax.plot([0,0], [-0.1,0.1], [0,0], 'k--')                     # eje Ex
ax.plot([0,0], [0,0], [-0.1,0.1], 'k--')                     # eje Hy

# === 3. Líneas de las ondas ===
line_ex, = ax.plot([], [], [], color="blue", label="Ex")
line_hy, = ax.plot([], [], [], color="red", label="Hy")
ax.legend()

# === 4. Animación ===
def init():
    line_ex.set_data([], [])
    line_ex.set_3d_properties([])
    line_hy.set_data([], [])
    line_hy.set_3d_properties([])
    return line_ex, line_hy

def update(frame):
    # Ex (azul) sobre eje Y
    line_ex.set_data(k_vals[:frame], Ex_vals[:frame])
    line_ex.set_3d_properties(np.zeros_like(Ex_vals[:frame]))
    # Hy (rojo) sobre eje Z
    line_hy.set_data(k_vals[:frame], np.zeros_like(Hy_vals[:frame]))
    line_hy.set_3d_properties(Hy_vals[:frame])
    return line_ex, line_hy

ani = FuncAnimation(fig, update, frames=len(k_vals),
                    init_func=init, blit=True, interval=50)

# === Guardar como GIF ===
ani.save("python/onda_emkCF.gif", writer=PillowWriter(fps=20))

# === Mostrar animación en ventana ===
plt.show()
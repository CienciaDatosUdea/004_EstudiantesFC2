import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation
import gc
import os

def animate_fdtd_simulation(csv_path, title, save_gif=False, gif_name=None, stride=2, max_frames=200):
    """
    Animación 3D de una simulación FDTD a partir de un archivo CSV
    
    Parámetros:
    -----------
    csv_path : str
        Ruta al archivo CSV con los datos de la simulación
    title : str
        Título de la animación
    save_gif : bool, opcional
        Si es True, guarda la animación como GIF (por defecto False)
    gif_name : str, opcional
        Nombre del archivo GIF (por defecto usa el nombre del CSV)
    stride : int, opcional
        Submuestreo de nodos (por defecto 2)
    max_frames : int, opcional
        Número máximo de frames a animar (por defecto 200)
    """
    
    # Lectura
    try:
        df_raw = pd.read_csv(csv_path, sep=',', header=0, low_memory=False)
        for col in df_raw.columns:
            df_raw[col] = pd.to_numeric(df_raw[col], errors='coerce')

        df = df_raw.dropna()
        if df.empty:
            raise ValueError("El archivo CSV no contiene datos numéricos válidos después de la limpieza")
            
    except Exception as e:
        print(f"Error al leer el archivo: {e}")
        try:
            df = pd.read_csv(csv_path, sep=',', header=0, dtype={
                'step': int, 't': float, 'k': int, 'x': float, 'E': float, 'H': float
            })
        except:
            raise ValueError("No se pudo leer el archivo CSV")

    # Verificar que las columnas necesarias existen
    required_columns = ['step', 't', 'k', 'x', 'E', 'H']
    for col in required_columns:
        if col not in df.columns:
            raise ValueError(f"Falta la columna requerida: {col}")

    # Inferir tamaños
    num_nodes = int(df["k"].max()) + 1
    num_steps = int(df["step"].max()) + 1

    print(f"Datos cargados: {len(df)} filas, {num_nodes} nodos, {num_steps} pasos de tiempo")

    # Limitar el número de frames si es demasiado grande
    if num_steps > max_frames:
        print(f"Advertencia: Demasiados frames ({num_steps}). Limitando a {max_frames}.")
        num_steps = max_frames

    # Eje de propagación
    z_all = df[df["step"] == 0]["x"].to_numpy()
    zmin, zmax = z_all.min(), z_all.max()
    zrange = zmax - zmin

    # Calcular valores máximos de campos para escalado
    Emax = max(df["E"].abs().max(), 1e-12)
    Hmax = max(df["H"].abs().max(), 1e-12)

    # Figura con tamaño ajustado
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')

    # Submuestreo de nodos
    k_idx = np.arange(num_nodes)[::stride]

    # Posiciones anclaje (todas sobre el eje z)
    X0 = np.zeros_like(k_idx, dtype=float)
    Y0 = np.zeros_like(k_idx, dtype=float)
    Z0 = z_all[k_idx]

    # Escalado relativo al rango Z para una mejor visualización
    scale_factor = 0.1
    E_scale = scale_factor * zrange / Emax if Emax > 0 else 1
    H_scale = scale_factor * zrange / Hmax if Hmax > 0 else 1

    # Límites de ejes proporcionales
    max_arrow_size = max(Emax * E_scale, Hmax * H_scale)
    ax.set_xlim(-max_arrow_size, max_arrow_size)
    ax.set_ylim(-max_arrow_size, max_arrow_size)
    ax.set_zlim(zmin, zmax)

    # Etiquetas y título
    ax.set_xlabel("Campo E (X)")
    ax.set_ylabel("Campo H (Y)")
    ax.set_zlabel("Posición Z")
    ax.set_title(title)

    # Configurar relación de aspecto
    try:
        ax.set_box_aspect([2*max_arrow_size/zrange, 2*max_arrow_size/zrange, 1])
    except Exception as e:
        print(f"No se pudo establecer la relación de aspecto: {e}")

    # Añadir cuadrícula
    ax.grid(True, linestyle='--', alpha=0.3)

    # Inicializar quivers
    d0 = df[df["step"] == 0]
    E0 = (d0["E"].to_numpy()[k_idx]) * E_scale
    H0 = (d0["H"].to_numpy()[k_idx]) * H_scale

    # Colores diferentes para E y H
    qE = ax.quiver(X0, Y0, Z0, E0, np.zeros_like(E0), np.zeros_like(E0), 
                   color='red', length=1.0, normalize=False, label='Campo E')
    qH = ax.quiver(X0, Y0, Z0, np.zeros_like(H0), H0, np.zeros_like(H0), 
                   color='blue', length=1.0, normalize=False, label='Campo H')

    # Añadir leyenda
    ax.legend()

    # Para mostrar el tiempo en el título
    t_vals = df.groupby("step")["t"].first().to_numpy()

    # Precalcular todos los datos para mejorar rendimiento
    print("Precalculando datos...")
    E_data = []
    H_data = []
    for frame in range(num_steps):
        d = df[df["step"] == frame]
        E_data.append((d["E"].to_numpy()[k_idx]) * E_scale)
        H_data.append((d["H"].to_numpy()[k_idx]) * H_scale)

    # Función de actualización optimizada
    def update(frame):
        nonlocal qE, qH
        
        # Obtener datos precalculados
        E = E_data[frame]
        H = H_data[frame]
        
        # Eliminar quivers anteriores 
        if qE in ax.collections:
            qE.remove()
        if qH in ax.collections:
            qH.remove()
        
        # Crear nuevos quivers
        qE = ax.quiver(X0, Y0, Z0, E, np.zeros_like(E), np.zeros_like(E), 
                       color='red', length=1.0, normalize=False)
        qH = ax.quiver(X0, Y0, Z0, np.zeros_like(H), H, np.zeros_like(H), 
                       color='blue', length=1.0, normalize=False)

        ax.set_title(f"{title} - Paso {frame}  t={t_vals[frame]:.6f}")
        
        # Liberar memoria periódicamente
        if frame % 20 == 0:
            gc.collect()
        
        return qE, qH

    # Ajustar el ángulo de visión inicial
    ax.view_init(elev=20, azim=45)
    
    ax.set_xticks([])
    ax.set_yticks([])

    print("Iniciando animación...")
    ani = FuncAnimation(fig, update, frames=num_steps, interval=100, blit=False, repeat=False)
    
    # Guardar como GIF si se solicita
    if save_gif:
        if gif_name is None:
            # Generar nombre automático a partir del CSV
            base_name = os.path.splitext(os.path.basename(csv_path))[0]
            gif_name = f"{base_name}_animation.gif"
        
        print(f"Guardando animación como {gif_name}...")
        ani.save(gif_name, writer='pillow', fps=15, dpi=80)
        print("Animación guardada exitosamente.")
    
    plt.show()
    
    return ani


# Función principal para ejecutar múltiples animaciones
def main():
    """
    Ejemplo de uso de la función animate_fdtd_simulation
    """
    # Crear una carpeta para las animaciones si no existe
    if not os.path.exists("animaciones"):
        os.makedirs("animaciones")
    
    # Lista de simulaciones a animar
    simulations = [
        {
            "csv_path": "../main1.txt",
            "title": "Simulación 1 - Condiciones iniciales sinusoidales periodicas",
            "gif_name": "animaciones/simulacion1.gif"
        },
        {
            "csv_path": "../main2.txt", 
            "title": "Simulación 2 - Condiciones iniciales uniformes que se anulan en los extremos",
            "gif_name": "animaciones/simulacion2.gif"
        },
        {
            "csv_path": "../main3.txt",
            "title": "Parámetros que no cumplen la condición de Courant",
            "gif_name": "animaciones/simulacion3.gif"
        }
    ]
    
    # Animamos cada simulación
    for sim in simulations:
        print(f"\nProcesando {sim['csv_path']}...")
        try:
            animate_fdtd_simulation(
                csv_path=sim["csv_path"],
                title=sim["title"],
                save_gif=True,
                gif_name=sim["gif_name"],
                stride=2,
                max_frames=400
            )
        except Exception as e:
            print(f"Error al procesar {sim['csv_path']}: {e}")
    
    print("\nProcesamiento completado.")


# Ejecutar el programa principal si este script es el principal
if __name__ == "__main__":
    # Si quieres ejecutar solo una animación, puedes hacerlo así:
    # animate_fdtd_simulation("../main1.txt", "Mi simulación FDTD", save_gif=True)
    
    # O ejecutar todas las animaciones definidas en main()
    main()


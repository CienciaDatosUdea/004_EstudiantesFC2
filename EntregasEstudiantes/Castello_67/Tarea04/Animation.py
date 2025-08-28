import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import glob
import os
import re

def leer_archivo_de_datos(filename):
    """
    Lee un archivo de datos, lo limpia de valores inválidos (inf, NaN)
    y devuelve los datos listos para graficar.
    """
    try:
        with open(filename, 'r') as f:
            lines = f.readlines()
            linea_dims = lines[2].strip()
            dims = re.findall(r'\d+', linea_dims)
            if len(dims) < 2:
                print(f"Advertencia: No se pudieron encontrar dimensiones en {filename}. Saltando archivo.")
                return None, None, None, None, None
            nx, ny = int(dims[-2]), int(dims[-1])

        data = np.loadtxt(filename, skiprows=4)

        if not np.all(np.isfinite(data)):
            print(f"Advertencia: Se encontraron valores no finitos (NaN o Inf) en {filename}.")
            data = np.nan_to_num(data, nan=0.0, posinf=0.0, neginf=0.0)

        shape = (nx, ny)
        X = data[:, 2].reshape(shape).T
        Y = data[:, 3].reshape(shape).T
        U = data[:, 4].reshape(shape).T
        V = data[:, 5].reshape(shape).T
        P = data[:, 6].reshape(shape).T

        return X, Y, U, V, P
        
    except Exception as e:
        print(f"Error crítico leyendo el archivo {filename}: {e}")
        return None, None, None, None, None

def main():
    """
    Función principal para encontrar archivos, crear y guardar la animación.
    """
    ruta_busqueda = os.path.join('data', 'canal_flow_*.txt')
    
    def extraer_numero(f):
        s = re.search(r'_(\d+)\.txt', f)
        return int(s.group(1)) if s else -1

    lista_archivos = sorted(glob.glob(ruta_busqueda), key=extraer_numero)

    if not lista_archivos:
        print(f"Error: No se encontraron archivos 'canal_flow_*.txt' en la carpeta '{os.path.join(os.getcwd(), 'data')}'")
        return

    print(f"Se encontraron {len(lista_archivos)} archivos de datos para la animación.")

    fig, ax = plt.subplots(figsize=(12, 6))

    primer_valido = False
    for i, f in enumerate(lista_archivos):
        X, Y, U, V, P = leer_archivo_de_datos(f)
        if X is not None:
            primer_valido = True
            break
    
    if not primer_valido:
        print("Error: No se pudo leer ningún archivo de datos correctamente. Abortando.")
        return

    print("Calculando rango de presión global para una escala de colores consistente...")
    p_min_global, p_max_global = P.min(), P.max()
    for f in lista_archivos[i+1:]:
        _, _, _, _, p_actual = leer_archivo_de_datos(f)
        if p_actual is not None:
            p_min_global = min(p_min_global, p_actual.min())
            p_max_global = max(p_max_global, p_actual.max())
    
    if p_min_global == p_max_global:
        p_min_global -= 1
        p_max_global += 1

    mapa_presion = ax.pcolormesh(X, Y, P, cmap='viridis', shading='auto', vmin=p_min_global, vmax=p_max_global)
    fig.colorbar(mapa_presion, ax=ax, label='Presión (p)')

    skip = 4
    escala_flechas = 40.0 
    campo_velocidad = ax.quiver(
        X[::skip, ::skip], Y[::skip, ::skip],
        U[::skip, ::skip], V[::skip, ::skip],
        color='white',
        scale_units='width', # CAMBIO 1
        scale=escala_flechas  # CAMBIO 2
    )
    
    ax.quiverkey(campo_velocidad, X=0.85, Y=1.05, U=0.5,
                 label='0.5 m/s', labelpos='E', coordinates='axes')

    ax.set_xlabel('Posición X')
    ax.set_ylabel('Posición Y')
    ax.set_aspect('equal', adjustable='box')

    def actualizar(frame):
        archivo = lista_archivos[frame]
        _, _, U, V, P = leer_archivo_de_datos(archivo)
        
        if P is None: 
            return mapa_presion, campo_velocidad

        mapa_presion.set_array(P.flatten())
        
        # IMPORTANTE: Actualizamos los componentes U y V del campo de vectores.
        campo_velocidad.set_UVC(U[::skip, ::skip], V[::skip, ::skip])

        titulo = os.path.basename(archivo).replace('.txt', '')
        ax.set_title(f'Simulación de Flujo en Canal - Tiempo: {titulo.split("_")[-1]}', fontsize=14)
        print(f"Procesando cuadro {frame + 1}/{len(lista_archivos)}: {archivo}")
        
        return mapa_presion, campo_velocidad

    print("\nCreando animación... Esto puede tardar varios minutos.")
    ani = animation.FuncAnimation(fig, actualizar, frames=len(lista_archivos), blit=False, interval=100)

    try:
        nombre_salida = 'dinamica_de_fluidos.gif'
        ani.save(nombre_salida, writer='pillow', fps=10)
        print(f"\n¡Éxito! Animación guardada como: {nombre_salida}")
    except Exception as e:
        print(f"\nError al guardar la animación: {e}")
        print("Asegúrate de tener la librería 'Pillow' instalada (`pip install Pillow`).")

if __name__ == '__main__':
    main()
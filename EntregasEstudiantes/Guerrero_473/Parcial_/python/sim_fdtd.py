import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D
import os


def cargar_datos(filename):
    """
    Carga los datos de los campos desde el archivo
    """
    try:
        with open(filename, 'r') as f:
            contenido = f.read()
        
        # Dividir en secciones de E y H
        secciones = contenido.split('---')
        
        # Cargar campo eléctrico
        datos_E = []
        for linea in secciones[0].strip().split('\n'):
            if linea.strip() and not linea.startswith('Campo'):
                datos_E.append([float(x) for x in linea.split()])
        
        # Cargar campo magnético
        datos_H = []
        for linea in secciones[1].strip().split('\n'):
            if linea.strip() and not linea.startswith('Campo'):
                datos_H.append([float(x) for x in linea.split()])
        
        E = np.array(datos_E)
        H = np.array(datos_H)
        
        return E, H
        
    except Exception as e:
        print(f"Error cargando {filename}: {e}")
        return None, None

def crear_animacion_3d(filename, output_gif="onda_electromagnetica_3d.gif"):
    """
    Crea una animación 3D de la evolución de la onda EM sin rotación
    """
    E, H = cargar_datos(filename)
    if E is None:
        return
    
    # Configurar figura 3D
    fig = plt.figure(figsize=(12, 8))
    ax = fig.add_subplot(111, projection='3d')
    
    # Crear ejes
    z = np.arange(E.shape[1])  # Eje espacial
    x = np.zeros_like(z)       # Eje x para E
    y = np.zeros_like(z)       # Eje y para H
    
    # Normalizar campos para visualización
    E_norm = E / np.max(np.abs(E)) if np.max(np.abs(E)) > 0 else E
    H_norm = H / np.max(np.abs(H)) if np.max(np.abs(H)) > 0 else H
    
    # Crear líneas iniciales
    line_E, = ax.plot(z, E_norm[0, :], x, 'r-', linewidth=3, label='Campo Eléctrico (E)')
    line_H, = ax.plot(z, y, H_norm[0, :], 'b-', linewidth=3, label='Campo Magnético (H)')
    
    # Configurar el gráfico 3D
    ax.set_xlim(0, len(z))
    ax.set_ylim(-1.2, 1.2)
    ax.set_zlim(-1.2, 1.2)
    
    ax.set_xlabel('Posición (z)')
    ax.set_ylabel('Campo Eléctrico (E)')
    ax.set_zlabel('Campo Magnético (H)')
    ax.set_title('Evolución 3D de Onda Electromagnética')
    
    # Vista fija (sin rotación)
    ax.view_init(elev=20, azim=30)  # Ángulo fijo
    
    ax.legend()
    ax.grid(True)
    
    # Texto del tiempo
    time_text = ax.text2D(0.05, 0.95, '', transform=ax.transAxes)
    
    # Función de actualización
    def update(frame):
        # Actualizar campo eléctrico (en plano XZ)
        line_E.set_data(z, E_norm[frame, :])
        line_E.set_3d_properties(x)
        
        # Actualizar campo magnético (en plano YZ)
        line_H.set_data(z, y)
        line_H.set_3d_properties(H_norm[frame, :])
        
        # Actualizar texto
        time_text.set_text(f'Tiempo: {frame}')
        
        return line_E, line_H, time_text
    
    # Crear animación
    frames = range(0, E.shape[0], max(1, E.shape[0] // 100))
    anim = FuncAnimation(fig, update, frames=frames, interval=50, blit=True)
    
    # Guardar GIF
    anim.save(output_gif, writer='pillow', fps=20, dpi=100)
    print(f"GIF 3D guardado como: {output_gif}")
    
    plt.show()
    
    return anim

# Función principal simple
if __name__ == "__main__":
    # Elige el archivo que quieres visualizar
    archivo = "resultados_abiertas.txt"  # Cambiar para el archivo 
    

    
    if os.path.exists(archivo):
        print(f"Creando animación 3D para: {archivo}")
        crear_animacion_3d(archivo, "PulsoGaussiano_CF_Abiertas.gif")
    else:
        print(f"Archivo no encontrado: {archivo}")
        print("Archivos disponibles:")
        for f in os.listdir('.'):
            if f.startswith('resultados_') and f.endswith('.txt'):
                print(f"  - {f}")
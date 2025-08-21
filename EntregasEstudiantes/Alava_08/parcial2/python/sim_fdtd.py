# Archivo: sim_fdtd.py
# Contiene la función mejorada para generar las animaciones de la simulación.

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os

def generar_animacion_onda(ruta_datos, titulo, nombre_salida_gif=None):
    """
    Crea, muestra y opcionalmente guarda una animación de la propagación 
    de una onda a partir de un archivo de datos.

    Args:
        ruta_datos (str): Ruta al archivo .txt con los datos de la simulación.
        titulo (str): Título que se mostrará en el gráfico.
        nombre_salida_gif (str, optional): Nombre del archivo .gif para guardar.
    """
    if not os.path.exists(ruta_datos):
        print(f"Error: No se encontró el archivo de datos '{ruta_datos}'.")
        print("Asegúrate de haber ejecutado el programa en C++ para generarlo.")
        return

    datos_simulacion = np.loadtxt(ruta_datos)
    pasos_temporales, num_nodos = datos_simulacion.shape

    plt.style.use('seaborn-v0_8-darkgrid')
    figura, ejes = plt.subplots(figsize=(10, 5))

    y_min = datos_simulacion.min() * 1.2
    y_max = datos_simulacion.max() * 1.2
    ejes.set_ylim(y_min if y_min < -0.15 else -0.2, y_max if y_max > 0.15 else 0.2)
    ejes.set_xlim(0, num_nodos - 1)

    ejes.set_title(titulo, fontsize=16, weight='bold')
    ejes.set_xlabel("Posición en la Malla Espacial", fontsize=12)
    ejes.set_ylabel("Amplitud del Campo Eléctrico (Ex)", fontsize=12)

    linea_onda, = ejes.plot([], [], lw=2.5, color="#FF5733")
    texto_paso = ejes.text(0.03, 0.90, '', transform=ejes.transAxes, 
                           bbox=dict(boxstyle='round,pad=0.4', fc='aliceblue', alpha=0.8))

    def inicializar_lienzo():
        linea_onda.set_data([], [])
        texto_paso.set_text('')
        return linea_onda, texto_paso

    def actualizar_cuadro(n_cuadro):
        amplitudes = datos_simulacion[n_cuadro, :]
        linea_onda.set_data(np.arange(num_nodos), amplitudes)
        tiempo_sim = n_cuadro * (10 if "Inestable" not in titulo else 5)
        texto_paso.set_text(f'Tiempo Simulado: {tiempo_sim}')
        return linea_onda, texto_paso

    animacion = FuncAnimation(figura, actualizar_cuadro, init_func=inicializar_lienzo,
                              frames=pasos_temporales, interval=50, blit=True)

    if nombre_salida_gif:
        print(f"Guardando animación en '{nombre_salida_gif}'...")
        animacion.save(nombre_salida_gif, writer='pillow', fps=25)
        print(f"Animación guardada con éxito.")

    plt.show()

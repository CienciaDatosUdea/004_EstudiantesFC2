import matplotlib.pyplot as plt
import numpy as np
from ipywidgets import FloatSlider, VBox, Layout, IntProgress, Output
from IPython.display import display, clear_output
import os
import time

class VisualizadorAnimado:
    """
    Clase para visualizar la evolución temporal de la simulación de difusión de calor 1D
    utilizando un widget interactivo.
    """
    def __init__(self, carpeta_datos, t_max, dt):
        """
        Constructor.
        :param carpeta_datos: Ruta a la carpeta que contiene los archivos de datos por paso de tiempo.
        :param t_max: Tiempo máximo de la simulaci+on.
        :param dt: Paso de tiempo.
        """
        self.carpeta_datos = carpeta_datos
        self.t_max = t_max
        self.dt = dt
        self.x_data = []
        self.u_data_series = []
        # El código de C++ guarda cada 0.1 segundos
        self.num_pasos = int(self.t_max / 0.1)

    def cargar_datos(self):
        """
        Carga todos los perfiles de temperatura de los archivos de datos.
        """
        self.u_data_series = [] # Limpiar la lista antes de cargar
        
        # ProgressBar
        progress_bar = IntProgress(min=0, max=self.num_pasos, description='Cargando datos:')
        display(progress_bar)

        for i in range(self.num_pasos + 1):
            file_path = os.path.join(self.carpeta_datos, f"datos_paso_{i}.txt")
            try:
                data = np.loadtxt(file_path, skiprows=1)
                if i == 0:
                    self.x_data = data[:, 0]
                self.u_data_series.append(data[:, 1])
            except FileNotFoundError:
                print(f"Error: El archivo '{file_path}' no fue encontrado. Asegúrese de haber ejecutado 'make run' primero.")
                progress_bar.close()
                return False
            progress_bar.value += 1
        progress_bar.close()
        return True

    def display_interactive_plot(self):
        """
        Genera una gráfica interactiva utilizando ipywidgets y matplotlib.
        """
        if len(self.x_data) == 0 or len(self.u_data_series) == 0:
            print("No hay datos para graficar. Asegúrese de haber cargado los datos correctamente.")
            return
        
        # Crear un widget de salida dedicado para la gráfica
        plot_output = Output()

        # Función de actualización que SOLO modifica los datos de la línea
        def update_plot(change):
            # 'change' es un diccionario que contiene los detalles del evento
            t_paso = change['new']
            step_index = int(t_paso / 0.1) # Utiliza el intervalo de 0.1 segundos
            if step_index > self.num_pasos:
                step_index = self.num_pasos
            
            # Limpiar la salida anterior y dibujar la nueva gráfica
            with plot_output:
                clear_output(wait=True)
                fig, ax = plt.subplots(figsize=(6, 6))
                ax.set_ylim(np.min(self.u_data_series) - 0.1, np.max(self.u_data_series) + 0.1)
                ax.set_xlabel("Posición (x)")
                ax.set_ylabel("Temperatura (u)")
                ax.plot(self.x_data, self.u_data_series[step_index], lw=2)
                ax.set_title(f"Evolución de la Temperatura con el Tiempo (t = {t_paso:.2f})")
                plt.grid()
                plt.show()

        # Crea el control deslizante
        slider = FloatSlider(
            value=0,
            min=0,
            max=self.t_max,
            step=0.1,  # Paso del slider de 0.1 segundos para que coincida con los archivos
            description='Tiempo (t):',
            readout_format='.2f',
            layout=Layout(width='80%')
        )
        
        # Conecta el slider a la función de trazado
        slider.observe(update_plot, names='value')

        # Mostrar el slider y la salida de la gráfica
        display(VBox([slider, plot_output]))

        # Llamar a la función para mostrar la gráfica inicial
        update_plot({'new': slider.value})

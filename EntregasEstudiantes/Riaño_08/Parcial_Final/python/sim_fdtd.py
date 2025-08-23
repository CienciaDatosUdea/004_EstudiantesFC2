import numpy as np
import matplotlib.pyplot as plt
from ipywidgets import interactive, IntSlider, Dropdown
from IPython.display import display

def load_data(filename):
    """
    @brief Carga datos de un archivo de texto.
    @param filename El nombre del archivo a cargar.
    @return Un array de NumPy con los datos cargados o None si el archivo no se encuentra.
    """
    try:
        data = np.loadtxt(filename)
        # Si los datos tienen solo una fila, los convertimos a una lista de listas
        if data.ndim == 1:
            return np.array([data])
        return data
    except FileNotFoundError:
        print(f"Error: El archivo {filename} no se encontró. Por favor, asegúrate de que el programa C++ haya sido ejecutado y haya generado los archivos.")
        return None

def plot_fields(t, E_data, H_data):
    """
    @brief Genera la gráfica de los campos E y H para un paso de tiempo dado.
    @param t El paso de tiempo a graficar.
    @param E_data El historial de datos del campo eléctrico.
    @param H_data El historial de datos del campo magnético.
    """
    if E_data is None or H_data is None:
        return

    if t >= len(E_data):
        print(f"El paso de tiempo (t={t}) excede los datos disponibles (máximo t={len(E_data) - 1}).")
        return

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
    fig.suptitle(f'Simulación FDTD en t = {t}', fontsize=16)

    # Gráfica del Campo Eléctrico
    ax1.plot(E_data[t], label=f't={t}')
    ax1.set_title('Campo Eléctrico')
    ax1.set_xlabel('Posición (z)')
    ax1.set_ylabel('Campo E')
    ax1.grid(True)
    ax1.legend()

    # Gráfica del Campo Magnético
    ax2.plot(H_data[t], label=f't={t}')
    ax2.set_title('Campo Magnético')
    ax2.set_xlabel('Posición (z)')
    ax2.set_ylabel('Campo H')
    ax2.grid(True)
    ax2.legend()

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.show()

def create_interactive_plot(E_data, H_data, max_time_step):
    """
    @brief Crea y muestra el widget interactivo para la visualización de la simulación.
    @param E_data El historial de datos del campo eléctrico.
    @param H_data El historial de datos del campo magnético.
    @param max_time_step El número máximo de pasos de tiempo.
    """
    t_slider = IntSlider(min=0, max=max_time_step, step=1, value=0, description='Tiempo (t)')
    interactive_plot = interactive(lambda t: plot_fields(t, E_data, H_data), t=t_slider)
    display(interactive_plot)


def plot_final_fields_beta_explorer(dz, dt):
    """
    @brief Genera la gráfica de los campos E y H para los valores de dz y dt dados.
    Los datos provienen de los archivos generados por el simulador C++.
    @param dz El paso espacial (delta z) de la simulación.
    @param dt El paso de tiempo (delta t) de la simulación.
    """
    filename_E = f'E_fixed_dz_{dz}_dt_{dt}.txt'
    filename_H = f'H_fixed_dz_{dz}_dt_{dt}.txt'

    E_data = load_data(filename_E)
    H_data = load_data(filename_H)

    if E_data is None or H_data is None:
        return

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))
    beta_value = dt / dz
    fig.suptitle(f'Simulación con dz={dz}, dt={dt} (beta={beta_value:.2f})', fontsize=16)

    # Gráfica del Campo Eléctrico
    ax1.plot(E_data[0], label=f'beta={beta_value:.2f}')
    ax1.set_title('Campo Eléctrico (Paso final)')
    ax1.set_xlabel('Posición (z)')
    ax1.set_ylabel('Campo E')
    ax1.grid(True)
    ax1.legend()

    # Gráfica del Campo Magnético
    ax2.plot(H_data[0], label=f'beta={beta_value:.2f}')
    ax2.set_title('Campo Magnético (Paso final)')
    ax2.set_xlabel('Posición (z)')
    ax2.set_ylabel('Campo H')
    ax2.grid(True)
    ax2.legend()

    plt.tight_layout(rect=[0, 0.03, 1, 0.95])
    plt.show()

def create_beta_explorer_widget():
    """
    @brief Crea y muestra el widget interactivo para la visualización de las simulaciones.
    Permite al usuario seleccionar una combinación de dz y dt para ver los resultados.
    """
    dz_options = [0.01, 0.02, 0.03]
    dt_options = [0.004, 0.01, 0.02]

    dz_dropdown = Dropdown(options=dz_options, value=dz_options[0], description='Δz:')
    dt_dropdown = Dropdown(options=dt_options, value=dt_options[0], description='Δt:')
    
    interactive_plot = interactive(plot_final_fields_beta_explorer, dz=dz_dropdown, dt=dt_dropdown)
    display(interactive_plot)

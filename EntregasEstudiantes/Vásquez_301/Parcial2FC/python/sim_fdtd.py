import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def create_fdtd_animation(data_filepath, title, output_filename=None):
    """
    Crea y muestra una animación de una simulación FDTD desde un archivo de datos.
    """
    data = np.loadtxt(data_filepath)
    timesteps, num_nodes = data.shape

    fig, ax = plt.subplots()
    ax.set_xlim(0, num_nodes)
    ax.set_ylim(-0.2, 0.2) 
    ax.set_title(title)
    ax.set_xlabel("Posición en la red (k)")
    ax.set_ylabel("Amplitud del Campo Eléctrico Ex")
    ax.grid(True)
    
    line, = ax.plot([], [], lw=2)
    time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)

    def init():
        line.set_data([], [])
        time_text.set_text('')
        return line, time_text

    def animate(frame):
        y = data[frame, :]
        line.set_data(np.arange(num_nodes), y)
        time_text.set_text(f'Time Step: {frame * 10}')
        return line, time_text

    anim = FuncAnimation(fig, animate, init_func=init,
                           frames=timesteps, interval=100, blit=True)

    if output_filename:
        anim.save(output_filename, writer='pillow', fps=30)
        print(f"Animación guardada en {output_filename}")

    plt.show()
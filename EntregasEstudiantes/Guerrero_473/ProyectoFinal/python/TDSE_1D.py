import numpy as np
import matplotlib.pyplot as plt
import imageio
import os

#  Ruta de entrada y salida
input_file = "../resultados_1D/TDSE/evolucion_completa.txt"
output_folder = "../resultados_1D/TDSE/animaciones"
output_gif = os.path.join(output_folder, "evolucion_paquete_gaussiano.gif")

#  Crear carpeta de salida si no existe
os.makedirs(output_folder, exist_ok=True)

#  Cargar datos desde archivo .txt
data = np.loadtxt(input_file, delimiter="\t", skiprows=1)
x = data[:, 0]
psi_evolutions = data[:, 1:]

#  Transponer para tener psi[t][x]
psi_evolutions = psi_evolutions.T

# Crear frames
frames = []
for t_index, psi_t in enumerate(psi_evolutions):
    fig, ax = plt.subplots(figsize=(6, 4))
    ax.plot(x, psi_t, color='darkred')
    ax.set_title(f"Evolución temporal – paso {t_index}")
    ax.set_xlabel("x")
    ax.set_ylabel(r"$|\psi(x,t)|^2$")
    ax.set_ylim(0, np.max(psi_evolutions)*1.1)
    ax.grid(True)

    # Convertir figura a imagen
    fig.canvas.draw()
    image = np.frombuffer(fig.canvas.tostring_rgb(), dtype='uint8')
    image = image.reshape(fig.canvas.get_width_height()[::-1] + (3,))
    frames.append(image)
    plt.close()

#  Guardar GIF
imageio.mimsave(output_gif, frames, fps=10)
print(f"GIF guardado en: {output_gif}")

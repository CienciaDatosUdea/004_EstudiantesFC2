'''
Define funciones para la lectura de datos entregados por main y su graficado
'''
import sys

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation



def read_em_wave(filename):
    ''' 
    Lee el archivo filename con los datos entregados por main
    filename: nombre del archivo, e.g: data.txt.
    '''
    frames = []
    z_vals, E_vals, H_vals = [], [], []

    with open(filename) as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            if line.startswith("#t"):
                # new block
                if z_vals:  # save previous block
                    frames.append((np.array(z_vals), np.array(E_vals), np.array(H_vals)))
                    z_vals, E_vals, H_vals = [], [], []
                continue
            if line.startswith("#"):
                continue
            try:
                z, E, H = map(float, line.split())
            except ValueError:
                print(f"Error parsing line: {line}")
                exit(1)
            z_vals.append(z)
            E_vals.append(E)
            H_vals.append(H)

    if z_vals:  # save last block
        frames.append((np.array(z_vals), np.array(E_vals), np.array(H_vals)))

    return frames

def make_animation(frames, params, skip = 10):
    '''
    Retorna un objeto de animación de matplotlib  que se puede plotear o guardar en archivo
    frames: cada frame con los datos z, E, H. Lo entrega read_em_wave()
    params: lista de parámetros [dz, dt, K, N, C]
    skip: número de frames a omitir en la animación
    '''
    dz = params[0]
    dt = params[1]
    K = params[2]
    fig = plt.figure()
    ax = fig.add_subplot(111, projection="3d")

    # Lines for E and H
    lineE, = ax.plot([], [], [], 'r-', label="E field")
    lineH, = ax.plot([], [], [], 'b-', label="H field")
    ax.set_xlabel("z")
    ax.set_ylabel("E (x)")
    ax.set_zlabel("H (y)")
    ax.set_xlim(0, dz*K)
    ax.set_ylim(-0.2, 0.2)
    ax.set_zlim(-0.2, 0.2)

    def init():
        lineE.set_data([], [])
        lineE.set_3d_properties([])
        lineH.set_data([], [])
        lineH.set_3d_properties([])
        return lineE, lineH

    def animate(i):
        z, E, H = frames[i*skip]

        ax.set_title(f"t = {dt*i*skip:.2f}")
        # Update line positions
        lineE.set_data(z, E)
        lineE.set_3d_properties(0*z)   # E in xz-plane
        lineH.set_data(z, 0*z)
        lineH.set_3d_properties(H)                  # H in yz-plane

        return lineE, lineH

    ani = FuncAnimation(fig, animate, frames=int(len(frames)/skip),
                        init_func = init, interval=100, blit=False)
    return ani

#read and plot results
if __name__ == "__main__":
    output_filename = sys.argv[1]
    params = list(map(float,sys.argv[2:]))

    frames = read_em_wave(output_filename)
    anim = make_animation(frames, params)
    anim.save("EMWave.gif")

"""
Animate the CSV output produced by the C++ FDTD solver.

Usage:
    python sim_fdtd.py fdtd_output.csv
"""
import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def main(path):
    df = pd.read_csv(path)
    t_values = sorted(df['t_index'].unique())
    z = df[df['t_index']==t_values[0]]['z'].to_numpy()

    fig, ax = plt.subplots()
    ax.set_title("1D FDTD: Ex and Hy")
    ax.set_xlabel("z")
    ax.set_ylabel("Field amplitude")

    line_E, = ax.plot([], [], label="Ex")
    line_H, = ax.plot([], [], label="Hy")
    ax.legend(loc="best")
    ax.set_xlim(z.min(), z.max())

    def init():
        line_E.set_data([], [])
        line_H.set_data([], [])
        return line_E, line_H

    def update(frame_idx):
        t = t_values[frame_idx]
        sub = df[df['t_index']==t]
        Ex = sub['Ex'].to_numpy()
        Hy = sub['Hy'].to_numpy()
        line_E.set_data(z, Ex)
        line_H.set_data(z, Hy)
        ymax = max(np.max(np.abs(Ex)), np.max(np.abs(Hy)), 0.1)
        ax.set_ylim(-1.2*ymax, 1.2*ymax)
        ax.set_title(f"1D FDTD: Ex and Hy  (t_index={t})")
        return line_E, line_H

    ani = FuncAnimation(fig, update, frames=len(t_values),
                        init_func=init, blit=False, interval=40)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(0)
    main(sys.argv[1])

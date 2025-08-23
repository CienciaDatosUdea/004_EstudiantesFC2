import sys
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def main(path):
    df = pd.read_csv(path)
    t_values = sorted(df['t_index'].unique())
    z = df[df['t_index'] == t_values[0]]['z'].to_numpy()

    fig, (axE, axH) = plt.subplots(2, 1, figsize=(8, 6), sharex=True)

    # Setup Ex subplot
    axE.set_title("1D FDTD: Ex field")
    axE.set_ylabel("Ex amplitude")
    line_E, = axE.plot([], [], color="blue")
    axE.set_xlim(z.min(), z.max())

    # Setup Hy subplot
    axH.set_title("1D FDTD: Hy field")
    axH.set_xlabel("z")
    axH.set_ylabel("Hy amplitude")
    line_H, = axH.plot([], [], color="red")
    axH.set_xlim(z.min(), z.max())

    def init():
        line_E.set_data([], [])
        line_H.set_data([], [])
        return line_E, line_H

    def update(frame_idx):
        t = t_values[frame_idx]
        sub = df[df['t_index'] == t]
        Ex = sub['Ex'].to_numpy()
        Hy = sub['Hy'].to_numpy()

        # Update Ex
        line_E.set_data(z, Ex)
        ymaxE = max(np.max(np.abs(Ex)), 0.1)
        axE.set_ylim(-1.2 * ymaxE, 1.2 * ymaxE)
        axE.set_title(f"1D FDTD: Ex field (t_index={t})")

        # Update Hy
        line_H.set_data(z, Hy)
        ymaxH = max(np.max(np.abs(Hy)), 0.1)
        axH.set_ylim(-1.2 * ymaxH, 1.2 * ymaxH)
        axH.set_title(f"1D FDTD: Hy field (t_index={t})")

        return line_E, line_H

    ani = FuncAnimation(fig, update, frames=len(t_values),
                        init_func=init, blit=False, interval=40)
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script.py data.csv")
        sys.exit(0)
    main(sys.argv[1])

"""
3D animation for 1D FDTD results.

Shows E and H as orthogonal components:
- E along x (curve: x = Ex(z,t), y = 0, z = z)
- H along y (curve: x = 0, y = Hy(z,t), z = z)
Propagation axis is z.

Usage:
    python sim_fdtd_3d.py fdtd_output.csv  [--stride 2]
"""
import sys, argparse
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 (needed for 3D)

def main(path, stride):
    df = pd.read_csv(path)
    t_values = sorted(df['t_index'].unique())
    z_all = df[df['t_index']==t_values[0]]['z'].to_numpy()
    # optionally subsample to keep animation smooth
    idx = np.arange(0, len(z_all), stride, dtype=int)
    z = z_all[idx]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_title("3D Animation: E ⟂ H, propagation along z")
    ax.set_xlabel("x (E)")
    ax.set_ylabel("y (H)")
    ax.set_zlabel("z")

    # Lines for E and H
    line_E, = ax.plot([], [], [], label="E (x)", lw=1.5)
    line_H, = ax.plot([], [], [], label="H (y)", lw=1.5)
    ax.legend(loc="upper left")

    # Axis limits (will adjust dynamically initially)
    zmin, zmax = z.min(), z.max()
    ax.set_zlim(zmin, zmax)

    def init():
        line_E.set_data_3d([], [], [])
        line_H.set_data_3d([], [], [])
        return line_E, line_H

    def update(frame_idx):
        t = t_values[frame_idx]
        sub = df[df['t_index']==t]
        Ex = sub['Ex'].to_numpy()[idx]
        Hy = sub['Hy'].to_numpy()[idx]
        # 3D curves
        xE, yE, zE = Ex, np.zeros_like(Ex), z
        xH, yH, zH = np.zeros_like(Hy), Hy, z

        line_E.set_data_3d(xE, yE, zE)
        line_H.set_data_3d(xH, yH, zH)

        # dynamic symmetric x/y limits to keep orthogonality visible
        span = max(np.max(np.abs(Ex)), np.max(np.abs(Hy)), 0.2)
        ax.set_xlim(-1.2*span, 1.2*span)
        ax.set_ylim(-1.2*span, 1.2*span)
        ax.set_zlim(zmin, zmax)
        ax.view_init(elev=25.0, azim=80.0)
        ax.set_title(f"3D Animation: E, H (t_index={t})")
        return line_E, line_H

    ani = FuncAnimation(fig, update, frames=len(t_values),
                        init_func=init, blit=False, interval=40)
    plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("csv", help="fdtd_output.csv")
    parser.add_argument("--stride", type=int, default=2, help="subsample z points for speed (>=1)")
    args = parser.parse_args()
    main(args.csv, max(1, args.stride))

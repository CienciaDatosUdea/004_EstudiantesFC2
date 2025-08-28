import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

def read_output(filename):
    """Reads output.dat file with blocks of x T separated by blank lines."""
    with open(filename) as f:
        lines = f.readlines()

    frames, xs, Ts = [], [], []
    x, T = [], []
    for line in lines:
        if line.startswith("#"):  # skip comments
            continue
        if line.strip() == "":
            if x and T:
                xs.append(np.array(x))
                Ts.append(np.array(T))
                x, T = [], []
            continue
        vals = line.split()
        x.append(float(vals[0]))
        T.append(float(vals[1]))

    if x and T:  # last frame
        xs.append(np.array(x))
        Ts.append(np.array(T))

    return xs, Ts

def make_gif(filename="output.dat", gifname="diffusion.gif"):
    xs, Ts = read_output(filename)

    fig, ax = plt.subplots()
    line, = ax.plot(xs[0], Ts[0], color="red")
    ax.set_ylim(0, 1.1*np.max(Ts[0]))
    ax.set_xlim(xs[0][0], xs[0][-1])
    ax.set_xlabel("x")
    ax.set_ylabel("Temperature")

    def update(frame):
        line.set_ydata(Ts[frame])
        ax.set_title(f"Step {frame}")
        return line,

    ani = animation.FuncAnimation(fig, update, frames=len(Ts), blit=True, interval=50)
    ani.save(gifname, writer="pillow")
    print(f"Saved {gifname}")

if __name__ == "__main__":
    make_gif()

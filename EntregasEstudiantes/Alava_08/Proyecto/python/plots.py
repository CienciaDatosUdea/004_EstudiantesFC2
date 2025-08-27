import numpy as np
import matplotlib.pyplot as plt
from scipy.fft import fft, fftfreq

plt.style.use('seaborn-v0_8-whitegrid')

def plot_camelback(filename="../data/camelback.txt"):
    """Lee y grafica los datos del potencial camelback."""
    data = np.loadtxt(filename)
    la_ratios = np.unique(data[:, 2])

    plt.figure(figsize=(10, 6))
    for ratio in sorted(la_ratios, reverse=True):
        subset = data[data[:, 2] == ratio]
        plt.plot(subset[:, 0], subset[:, 1], label=f'L/a = {int(ratio)}')

    plt.xlabel('z / L (Posición Normalizada)', fontsize=12)
    plt.ylabel("U'_M (J/m³)", fontsize=12)
    plt.title("Potencial 'Camelback'", fontsize=14)
    plt.xlim(-0.6, 0.6)
    plt.ylim(0, 14)
    plt.legend()
    plt.grid(True)
    plt.show()

def plot_param_sweep(filename="../data/paramsweep.txt"):
    """Lee y grafica los datos del barrido de parámetros."""
    data = np.loadtxt(filename)
    la_ratios = data[:, 0]
    barrier_heights = data[:, 1]
    spring_constants = data[:, 2]

    fig, ax = plt.subplots(2, 1, figsize=(10, 10))

    # Gráfica para la Altura de la Barrera
    ax[0].plot(la_ratios, barrier_heights, 'o-')
    ax[0].set_xlabel('L / a', fontsize=12)
    ax[0].set_ylabel("ΔU'_M (J/m³)", fontsize=12)
    ax[0].set_title("Altura de la Barrera vs. L/a", fontsize=14)
    ax[0].grid(True)

    # Gráfica para la Constante de Resorte
    ax[1].plot(la_ratios, spring_constants, 'o-')
    ax[1].set_yscale('log')
    ax[1].set_xlabel('L / a', fontsize=12)
    ax[1].set_ylabel("k'_z (N/m⁴)", fontsize=12)
    ax[1].set_title("Constante de Resorte vs. L/a", fontsize=14)
    ax[1].grid(True)

    plt.tight_layout()
    plt.show()

def plot_oscillation(filename="../data/oscillation.txt"):
    """Lee y grafica la oscilación de la varilla."""
    data = np.loadtxt(filename)
    time = data[:, 0]
    position_mm = data[:, 1]
    
    plt.figure(figsize=(12, 6))
    plt.plot(time, position_mm)
    plt.axhline(0, color='black', linestyle='--')
    plt.xlabel("Tiempo (s)", fontsize=12)
    plt.ylabel("Posición z (mm)", fontsize=12)
    plt.title("Simulación de la Oscilación Amortiguada", fontsize=14)
    plt.grid(True)
    plt.show()

def plot_fft_spectrum(filename="../data/oscillation.txt"):
    """Calcula y grafica el espectro de frecuencia y devuelve el período."""
    data = np.loadtxt(filename)
    t = data[:, 0]
    z_t = data[:, 1]
    
    N = len(t)
    T_s = t[1] - t[0]
    yf = fft(z_t)
    xf = fftfreq(N, T_s)
    
    positive_mask = xf > 0
    xf_pos = xf[positive_mask]
    yf_pos = np.abs(yf[positive_mask])
    
    peak_freq_index = np.argmax(yf_pos)
    dominant_freq = xf_pos[peak_freq_index]
    T_z_measured = 1 / dominant_freq
    
    print(f"La frecuencia dominante de la oscilación es: {dominant_freq:.4f} Hz")
    print(f"El período 'medido' de la simulación es: T_z = {T_z_measured:.4f} s")
    
    plt.figure(figsize=(10, 5))
    plt.plot(xf_pos, yf_pos)
    plt.title("Espectro de Frecuencia de la Oscilación (FFT)")
    plt.xlabel("Frecuencia (Hz)")
    plt.ylabel("Amplitud")
    plt.xlim(0, 2)
    plt.axvline(dominant_freq, color='red', linestyle='--', label=f'Pico en {dominant_freq:.3f} Hz')
    plt.legend()
    plt.grid(True)
    plt.show()
    
    return T_z_measured

def plot_validation_curves(validation_filename, simulation_results):
    """Grafica las curvas teóricas y superpone el resultado de la simulación."""
    val_data = np.loadtxt(validation_filename)
    la_ratios = np.unique(val_data[:, 0])
    
    fig, ax = plt.subplots(1, 2, figsize=(16, 6))
    
    for ratio in la_ratios:
        subset = val_data[val_data[:, 0] == ratio]
        y_norm = subset[:, 1]
        T_z = subset[:, 2]
        chi = subset[:, 3]
        
        ax[0].plot(y_norm, T_z, lw=2, label=f'Teoría L/a = {int(ratio)}')
        ax[1].plot(T_z, np.abs(chi), lw=2, label=f'Teoría L/a = {int(ratio)}')
        
    # Superponer el punto de la simulación
    y0_norm_sim = simulation_results["y0"] / simulation_results["a"]
    Tz_sim = simulation_results["T_z"]
    chi_sim = np.abs(simulation_results["chi"])
    
    ax[0].plot(y0_norm_sim, Tz_sim, 'r*', markersize=15, label='Medición Virtual (L/a=8)')
    ax[1].plot(Tz_sim, chi_sim, 'r*', markersize=15, label='Medición Virtual (L/a=8)')
    
    ax[0].set_xlabel("Altura de Equilibrio y₀ / a", fontsize=12)
    ax[0].set_ylabel("Período de Oscilación T_z (s)", fontsize=12)
    ax[0].set_title("Verificación del Modelo: Tz vs y₀/a", fontsize=14)
    ax[0].legend()
    ax[0].grid(True)
    ax[0].set_ylim(0.5, 2.0)

    ax[1].set_xlabel("Período de Oscilación T_z (s)", fontsize=12)
    ax[1].set_ylabel("|χ| (Adimensional)", fontsize=12)
    ax[1].set_title("Verificación del Modelo: |χ| vs Tz", fontsize=14)
    ax[1].set_yscale('log')
    ax[1].legend()
    ax[1].grid(True)
    
    plt.tight_layout()
    plt.show()

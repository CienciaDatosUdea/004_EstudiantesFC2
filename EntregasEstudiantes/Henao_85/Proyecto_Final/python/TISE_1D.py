
import numpy as np
import matplotlib.pyplot as plt
import os

#  Rutas de entrada
eigenvalues_file = "../resultados_1D/TISE/estacionarias.txt"
eigenfunctions_file = "../resultados_1D/TISE/funciones_onda.txt"

#  Cargar datos
energias = np.loadtxt(eigenvalues_file)
data = np.loadtxt(eigenfunctions_file, delimiter="\t", skiprows=1)
x = data[:, 0]
psi_n = data[:, 1:]  # Cada columna es una función de onda

#  Normalización
psi_n_norm = psi_n / np.sqrt(np.trapz(psi_n**2, x, axis=0))

# Visualización
plt.figure(figsize=(10, 6))
for i in range(min(5, psi_n_norm.shape[1])):  # Mostrar hasta 5 estados
    plt.plot(x, psi_n_norm[:, i], label=f"$n={i}$, $E={energias[i]:.3f}$")

plt.title("Funciones de onda estacionarias – TISE 1D")
plt.xlabel("x")
plt.ylabel(r"$\psi_n(x)$ normalizada")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()

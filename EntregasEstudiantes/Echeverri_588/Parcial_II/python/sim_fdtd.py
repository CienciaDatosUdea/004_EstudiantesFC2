import numpy as np
import matplotlib.pyplot as plt
import os
import argparse

plt.rcParams['figure.figsize'] = (12, 8)
plt.rcParams['font.size'] = 12
plt.rcParams['lines.linewidth'] = 2
plt.style.use('seaborn-v0_8' if 'seaborn-v0_8' in plt.style.available else 'default')

output_dir = "../plots"
os.makedirs(output_dir, exist_ok=True)

results_dir = "../results"  # Directorio relativo donde están los datos

class FDTDVisualizer:
    """Clase para visualizar resultados de simulación FDTD"""
    
    def __init__(self):
        """Inicializar el visualizador"""
        self.data = {}
        self.z_positions = None
        
    def load_data(self, filename):
        """
        Cargar datos desde archivo generado por simulación C++
        
        Parameters:
        filename (str): Nombre del archivo de datos (solo nombre, sin path)
        """
        full_path = os.path.join(results_dir, filename)  # Ruta relativa results/
        
        try:
            if not os.path.exists(full_path):
                print(f"Error: Archivo {full_path} no encontrado")
                return None
                
            # Leer datos
            data = np.loadtxt(full_path, comments='#')
            
            if data.size == 0:
                print(f"Error: Archivo {full_path} está vacío")
                return None
                
            self.z_positions = data[:, 0]
            ex_data = data[:, 1]
            hy_data = data[:, 2]
            
            return {'z': self.z_positions, 'Ex': ex_data, 'Hy': hy_data}
            
        except Exception as e:
            print(f"Error cargando {full_path}: {str(e)}")
            return None
    
    def plot_single_snapshot(self, data, title="Campos Electromagnéticos", save_fig=None):
        """
        Graficar los campos
        
        Parameters:
        data (dict): Diccionario con datos {'z', 'Ex', 'Hy'}
        title (str): Título del gráfico
        save_fig (str): Nombre del archivo para guardar
        """
        if data is None:
            print("No hay datos para graficar")
            return
            
        fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 8))
        
        # Campo eléctrico
        ax1.plot(data['z'], data['Ex'], 'b-', label='Ex', linewidth=2)
        ax1.set_ylabel('Campo Eléctrico Ex')
        ax1.set_title(f'{title} - Campo Eléctrico')
        ax1.grid(True, alpha=0.3)
        ax1.legend()
        
        # Campo magnético
        ax2.plot(data['z'], data['Hy'], 'r-', label='Hy', linewidth=2)
        ax2.set_xlabel('Posición z')
        ax2.set_ylabel('Campo Magnético Hy')
        ax2.set_title(f'{title} - Campo Magnético')
        ax2.grid(True, alpha=0.3)
        ax2.legend()
        
        plt.tight_layout()
                
        if save_fig:
            save_path = os.path.join(output_dir, save_fig)
            plt.savefig(save_path, dpi=300, bbox_inches='tight')
            print(f"✓ Gráfico guardado: {save_path}")
        
        plt.show()
    
    def compare_conditions(self, data_periodic, data_zero):
        """
        Comparar resultados con diferentes condiciones de frontera
        
        Parameters:
        data_periodic (dict): Datos con condiciones periódicas
        data_zero (dict): Datos con condiciones de frontera cero
        """
        if data_periodic is None or data_zero is None:
            print("Faltan datos para comparación")
            return
            
        fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(15, 10))
        
        # Ex - Condiciones periódicas
        ax1.plot(data_periodic['z'], data_periodic['Ex'], 'b-', linewidth=2)
        ax1.set_title('Ex - Condiciones Periódicas')
        ax1.set_ylabel('Campo Ex')
        ax1.grid(True, alpha=0.3)
        
        # Ex - Condiciones cero
        ax2.plot(data_zero['z'], data_zero['Ex'], 'b-', linewidth=2)
        ax2.set_title('Ex - Condiciones Frontera Cero')
        ax2.set_ylabel('Campo Ex')
        ax2.grid(True, alpha=0.3)
        
        # Hy - Condiciones periódicas
        ax3.plot(data_periodic['z'], data_periodic['Hy'], 'r-', linewidth=2)
        ax3.set_title('Hy - Condiciones Periódicas')
        ax3.set_xlabel('Posición z')
        ax3.set_ylabel('Campo Hy')
        ax3.grid(True, alpha=0.3)
        
        # Hy - Condiciones cero
        ax4.plot(data_zero['z'], data_zero['Hy'], 'r-', linewidth=2)
        ax4.set_title('Hy - Condiciones Frontera Cero')
        ax4.set_xlabel('Posición z')
        ax4.set_ylabel('Campo Hy')
        ax4.grid(True, alpha=0.3)
        
        # Resaltar fronteras
        for ax in [ax2, ax4]:
            ax.axvline(x=0, color='k', linestyle='--', alpha=0.5, label='Frontera')
            ax.axvline(x=data_zero['z'][-1], color='k', linestyle='--', alpha=0.5)
        
        plt.tight_layout()
        compare_path = os.path.join(output_dir, 'comparacion_condiciones_frontera.png')
        plt.savefig(compare_path, dpi=300, bbox_inches='tight')
        print(f"✓ Gráfico guardado en: {compare_path}")
        plt.show()
    
    def create_summary_report(self):
        """Crear reporte resumen con todas las visualizaciones"""
        
        # Cargar todos los archivos disponibles
        files_to_check = [
            ('initial_conditions.dat', 'Condiciones Iniciales'),
            ('final_periodic.dat', 'Resultado Final - Periódico'),
            ('final_zero_boundary.dat', 'Resultado Final - Frontera Cero')
        ]
        
        available_data = {}
        for filename, description in files_to_check:
            data = self.load_data(filename)
            if data is not None:
                available_data[filename] = {'data': data, 'desc': description}
        
        if not available_data:
            print("No se encontraron archivos de datos")
            return
        
        # 1. Condiciones iniciales
        if 'initial_conditions.dat' in available_data:
            print("\n1. CONDICIONES INICIALES")
            print("-" * 30)
            initial_data = available_data['initial_conditions.dat']['data']
            self.plot_single_snapshot(initial_data, "Condiciones Iniciales", 
                                     "condiciones_iniciales.png")
        
        # 2. Comparación de condiciones de frontera
        if ('final_periodic.dat' in available_data and 
            'final_zero_boundary.dat' in available_data):
            print("\n2. COMPARACIÓN DE CONDICIONES DE FRONTERA")
            print("-" * 45)
            self.compare_conditions(
                available_data['final_periodic.dat']['data'],
                available_data['final_zero_boundary.dat']['data']
            )     
       
        print("\n" + "="*60)
        print("Archivos generados:")
        print("  • condiciones_iniciales.png")
        print("  • comparacion_condiciones_frontera.png") 

        print("="*60)

def main():
    """Función principal"""
    parser = argparse.ArgumentParser(description='Visualización FDTD')
    parser.add_argument('--file', '-f', help='Archivo específico a visualizar')
    parser.add_argument('--report', '-r', action='store_true', 
                       help='Generar reporte completo')
    parser.add_argument('--compare', '-c', action='store_true',
                       help='Comparar condiciones de frontera')
    
    args = parser.parse_args()
    
    visualizer = FDTDVisualizer()
    
    if args.file:
        # Visualizar archivo específico
        data = visualizer.load_data(args.file)
        if data:
            visualizer.plot_single_snapshot(data, f"Datos de {args.file}")
    
    elif args.compare:
        # Comparar condiciones de frontera
        data_periodic = visualizer.load_data('final_periodic.dat')
        data_zero = visualizer.load_data('final_zero_boundary.dat')
        visualizer.compare_conditions(data_periodic, data_zero)
    
    elif args.report:
        # Generar reporte completo
        visualizer.create_summary_report()
    
    else:
        # Por defecto, generar reporte completo
        print("Generando reporte completo...")
        print("Uso: python sim_fdtd.py [--file archivo.dat] [--report] [--compare]")
        visualizer.create_summary_report()

if __name__ == "__main__":
    main()
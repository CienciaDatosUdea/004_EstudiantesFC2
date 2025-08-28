import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def parse_md_data(filename):
    """Parse molecular dynamics data with energy information"""
    time_steps = []
    current_time = None
    current_data = []
    current_energy = None
    current_temp = None
    box_size = 54
    
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if not line:
                continue
                
            if line.startswith('#L = '):
                try:
                    box_size = float(line.split('=')[1].strip())
                except:
                    box_size = 54
            if line.startswith('#t ='):
                if current_data:
                    time_steps.append({
                        'time': current_time,
                        'positions': np.array(current_data),
                        'energy': current_energy,
                        'temp': current_temp
                    })
                    current_data = []
                    current_energy = None
                
                try:
                    current_time = float(line.split('=')[1].strip())
                except:
                    current_time = len(time_steps) * 0.001
                    
            elif line.startswith('#E ='):
                try:
                    current_energy = float(line.split('=')[1].strip())
                except:
                    current_energy = None
            elif line.startswith('#T ='):
                try:
                    current_temp = float(line.split('=')[1].strip())
                except:
                    current_temp = None
                    
            elif line.startswith('#'):
                continue
                
            else:
                try:
                    parts = line.split()
                    if len(parts) == 2:
                        x, y = map(float, parts)
                        current_data.append([x, y])
                except:
                    continue
    
    if current_data:
        time_steps.append({
            'time': current_time,
            'positions': np.array(current_data),
            'energy': current_energy,
            'temp': current_temp,
        })
    
    return time_steps, box_size

def create_animation_with_energy(time_steps,box_size ,output_gif='simulation.gif', fps=20):
    """Create animation with energy plot underneath"""
    fig = plt.figure(figsize=(15, 8))
    # Simulation plot
    gs = fig.add_gridspec(2,3, width_ratios = [2,1,1],height_ratios = [1,1])
    ax_sim = fig.add_subplot(gs[:,0:2])
    ax_energy = fig.add_subplot(gs[0,2])
    ax_temp = fig.add_subplot(gs[1,2])

    ax_sim.set_xlim(0, box_size)
    ax_sim.set_ylim(0, box_size)
    ax_sim.set_xlabel('X Position')
    ax_sim.set_ylabel('Y Position')
    ax_sim.set_title('Molecular Dynamics Simulation')
    ax_sim.grid(True, alpha=0.3)
    
    # Energy plot (static ranges)
    ax_energy.set_xlim(0, max(step['time'] for step in time_steps if step['time'] is not None))
    ax_energy.set_ylim(min(step['energy'] for step in time_steps if step['energy'] is not None),
                max(step['energy'] for step in time_steps if step['energy'] is not None))
                # 1e6)
    ax_energy.set_xlabel('Time')
    ax_energy.set_ylabel('Energy')
    ax_energy.grid(True, alpha=0.3)
    
    ax_temp.set_xlim(0, max(step['time'] for step in time_steps if step['time'] is not None))
    ax_temp.set_ylim(min(step['temp'] for step in time_steps if step['temp'] is not None),
                max(step['temp'] for step in time_steps if step['temp'] is not None))
                # 1e6)
    ax_temp.set_xlabel('Time')
    ax_temp.set_ylabel('Temp')
    ax_temp.grid(True, alpha=0.3)
    # Create scatter plot for particles
    scatter = ax_sim.scatter([], [], s=200, c='blue', alpha=0.7, edgecolors='none')
    
    # Create energy line plot
    energy_line, = ax_energy.plot([], [], 'r-', linewidth=2)
    current_energy_point, = ax_energy.plot([], [], 'ro', markersize=6)

    temp_line, = ax_temp.plot([], [], 'c-', linewidth=2)
    current_temp_point, = ax_temp.plot([], [], 'co', markersize=6)
    
    # Time and energy text
    time_text = ax_sim.text(0.02, 0.95, '', transform=ax_sim.transAxes, fontsize=10,
                        bbox=dict(boxstyle="round,pad=0.2", facecolor="white", alpha=0.8))
    
    def init():
        scatter.set_offsets(np.empty((0, 2)))
        energy_line.set_data([], [])
        temp_line.set_data([],[])
        current_energy_point.set_data([], [])
        current_temp_point.set_data([],[])
        time_text.set_text('')
        return scatter, energy_line, current_energy_point, temp_line, current_temp_point,time_text
    
    def update(i):
        frame = i*150
        data = time_steps[frame]
        positions = data['positions']
        time_val = data['time']
        energy_val = data['energy']
        temp_val = data['temp']
        
        # Update simulation
        scatter.set_offsets(positions)
        time_text.set_text(f'Time: {time_val:.3f}')
        
        # Update energy plot
        if energy_val is not None:
            # Get all previous times and energies
            times = [step['time'] for step in time_steps[:frame+1] if step['energy'] is not None]
            energies = [step['energy'] for step in time_steps[:frame+1] if step['energy'] is not None]
            
            energy_line.set_data(times, energies)
            current_energy_point.set_data([time_val], [energy_val])
        
        if temp_val is not None:
            times = [step['time'] for step in time_steps[:frame+1] if step['temp'] is not None]
            temps = [step['temp'] for step in time_steps[:frame+1] if step['temp'] is not None]

            temp_line.set_data(times, temps)
            current_temp_point.set_data([time_val], [temp_val])

        return scatter, energy_line, current_energy_point, temp_line, current_temp_point, time_text
    
    ani = FuncAnimation(fig, update, frames=int(len(time_steps)/150),
                       init_func=init, blit=True, interval=1/fps)
    
    plt.tight_layout()
    ani.save(output_gif, fps=fps)
    plt.close(fig)
    
    return ani

if __name__ == "__main__":
    # Parse and animate
    time_steps, box_size = parse_md_data('data.txt')
    create_animation_with_energy(time_steps,box_size ,fps=60)
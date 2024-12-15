import os
import re
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

# Path to directory containing the .dat files
data_dir = r'D:/UNO/CSCI 6454 Parallel and Scientific Computing/Assignments/Padam_Assignment/easyFunction/best_states_steps/'

# Lists to hold the extracted x, y coordinates and energy values
x_coords = []
y_coords = []
energies = []

# Regular expressions to capture coordinate and energy lines
coord_pattern = r'xyCoord == \((-?\d+\.\d+),(-?\d+\.\d+)\)'
energy_pattern = r'energy: (\d+\.\d+)'  # Adjusted to match only positive energy values

# Loop over all .dat files in the specified directory
for filename in os.listdir(data_dir):
    if filename.startswith('best_state') and filename.endswith('.txt'):
        filepath = os.path.join(data_dir, filename)
        with open(filepath, 'r') as file:
            content = file.read()
            coord_matches = re.findall(coord_pattern, content)
            energy_matches = re.findall(energy_pattern, content)
            
            # Ensure equal number of coordinates and energy values before processing
            min_length = min(len(coord_matches), len(energy_matches))
            
            for i in range(min_length):
                x_coords.append(float(coord_matches[i][0]))
                y_coords.append(float(coord_matches[i][1]))
                energies.append(float(energy_matches[i]))

# Convert lists to numpy arrays for further processing
x_coords = np.array(x_coords)
y_coords = np.array(y_coords)
energies = np.array(energies)

# Generate scatter plot if the lengths of x, y coordinates and energies match
if len(x_coords) == len(y_coords) == len(energies):
    # Apply a custom style with a dark background theme
    plt.style.use('dark_background')
    
    # Create figure and axis with customized background colors
    fig, ax = plt.subplots(figsize=(12, 10), facecolor='#00008B')  # Dark blue background for figure
    ax.set_facecolor('#F0F8FF')  # AliceBlue background for axes
    
    # Set color range based on the energy values (only positive energies)
    vmin = min(energies)
    vmax = max(energies)
    
    # Create a custom colormap using 'plasma' for positive values
    colors = plt.cm.plasma(np.linspace(0, 1, 256))
    colors = mcolors.LinearSegmentedColormap.from_list('custom_cmap', colors)
    colors.set_bad('gray')
    
    # Plot scatter points with the custom colormap based on energy values
    scatter = ax.scatter(x_coords, y_coords, c=energies, cmap=colors,
                         vmin=vmin, vmax=vmax, s=50, alpha=0.8)

    # Add a colorbar to represent the energy scale visually
    cbar = plt.colorbar(scatter)
    cbar.set_label('Energy', rotation=270, labelpad=15, color='white')
    cbar.ax.yaxis.set_tick_params(color='white')
    plt.setp(plt.getp(cbar.ax.axes, 'yticklabels'), color='white')

    # Set axis labels and plot title with white text color
    ax.set_xlabel('X Coordinate', color='white')
    ax.set_ylabel('Y Coordinate', color='white')
    ax.set_title('Energy Values in X-Y Coordinates', color='white')

    # Customize tick colors to match the dark theme
    ax.tick_params(colors='white')
    
    # Customize axis borders (spines) to be white-colored
    for spine in ax.spines.values():
        spine.set_edgecolor('white')

    # Display min and max energy values in exponential format on the plot
    ax.text(0.02, 0.98, f'Min Energy: {vmin:.2f}', transform=ax.transAxes,
            verticalalignment='top', color='black')
    ax.text(0.02, 0.95, f'Max Energy: {vmax:.2f}', transform=ax.transAxes,
            verticalalignment='top', color='black')

    # Save the generated plot as a PNG image file
    plt.tight_layout()
    plt.savefig('plot_figure.png')

    # Display the plot on screen
    plt.show()
else:
    print("Error: Mismatch in data lengths")
    print(f"x: {len(x_coords)}, y: {len(y_coords)}, energies: {len(energies)}")

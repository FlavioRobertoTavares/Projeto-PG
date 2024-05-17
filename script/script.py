import tkinter as tk
import json
import os
import subprocess

def compile_and_run():
    # Compile main.cpp into an executable named "render"
    compile_process = subprocess.run(["g++", "main.cpp", "-o", "render"], capture_output=True, text=True)

    run_process = subprocess.run(["./render"], stdin=open("input.txt", "r"), stdout=open("output.ppm", "w"))

# Function to write data to files
def write_to_file():
    data = {
        "origin": origin_entry.get(),
        "target": target_entry.get(),
        "up": up_entry.get(),
        "cor": cor_entry.get(),
        "height": height_entry.get(),
        "double length": double_length_entry.get(),
        "center": center_entry.get(),
        "radius": radius_entry.get(),
        "sp_color": sp_color_entry.get(),
        "center2": center2_entry.get(),
        "radius2": radius2_entry.get(),
        "sp_color2": sp_color2_entry.get(),
        "plane_origin": plane_origin_entry.get(),
        "plane_normal": plane_normal_entry.get(),
        "plane_cor": plane_cor_entry.get()  # Add plane_cor entry
    }
    
    # Write to JSON file for persistence
    with open("data.json", "w") as file:
        json.dump(data, file)
    
    # Write to output.txt for immediate viewing (data only)
    with open("input.txt", "w") as file:
        for value in data.values():
            file.write(f"{value}\n")
    
    compile_and_run()

# Function to save data when closing the window
def on_closing():
    #write_to_file()
    root.destroy()

# Function to load data from file
def load_data():
    if os.path.exists("data.json"):
        with open("data.json", "r") as file:
            data = json.load(file)
            return data
    return {}

# Create the main window
root = tk.Tk()
root.title("Data Writer")

# Define the labels and their respective columns
camera_labels = ["origin", "target", "up", "cor", "height", "double length"]
sphere_labels = ["center", "radius", "sp_color"]
sphere2_labels = ["center2", "radius2", "sp_color2"]
plane_labels = ["plane_origin", "plane_normal", "plane_cor"]  # Add plane_cor label

# Function to create labeled entries in a specific column
def create_labeled_entries(labels, start_row, col, data):
    entries = {}
    for i, label in enumerate(labels):
        lbl = tk.Label(root, text=label)
        lbl.grid(row=start_row + i, column=col, padx=5, pady=5, sticky='w')
        
        entry = tk.Entry(root)
        entry.grid(row=start_row + i, column=col + 1, padx=5, pady=5, sticky='we')
        entry.insert(0, data.get(label, ""))
        
        entries[label] = entry
    return entries

# Load existing data
data = load_data()

# Create category labels
tk.Label(root, text="Camera", font=('Helvetica', 12, 'bold')).grid(row=0, column=0, columnspan=2, pady=10)
tk.Label(root, text="Sphere 1", font=('Helvetica', 12, 'bold')).grid(row=0, column=2, columnspan=2, pady=10)
tk.Label(root, text="Sphere 2", font=('Helvetica', 12, 'bold')).grid(row=5, column=2, columnspan=2, pady=10)
tk.Label(root, text="Plane", font=('Helvetica', 12, 'bold')).grid(row=0, column=4, columnspan=2, pady=10)

# Create labeled entries for each column
camera_entries = create_labeled_entries(camera_labels, 1, 0, data)
sphere_entries = create_labeled_entries(sphere_labels, 1, 2, data)
sphere2_entries = create_labeled_entries(sphere2_labels, 6, 2, data)
plane_entries = create_labeled_entries(plane_labels, 1, 4, data)

# Assign entries to specific variables for clarity
origin_entry = camera_entries["origin"]
target_entry = camera_entries["target"]
up_entry = camera_entries["up"]
cor_entry = camera_entries["cor"]
height_entry = camera_entries["height"]
double_length_entry = camera_entries["double length"]
center_entry = sphere_entries["center"]
radius_entry = sphere_entries["radius"]
sp_color_entry = sphere_entries["sp_color"]
center2_entry = sphere2_entries["center2"]
radius2_entry = sphere2_entries["radius2"]
sp_color2_entry = sphere2_entries["sp_color2"]
plane_origin_entry = plane_entries["plane_origin"]
plane_normal_entry = plane_entries["plane_normal"]
plane_cor_entry = plane_entries["plane_cor"]  # Add plane_cor entry

# Create a save button
save_button = tk.Button(root, text="Save to File", command=write_to_file)
save_button.grid(row=10, columnspan=6, pady=20)

# Configure column weights
root.columnconfigure(1, weight=1)
root.columnconfigure(3, weight=1)
root.columnconfigure(5, weight=1)

# Bind the closing event to save data
root.protocol("WM_DELETE_WINDOW", on_closing)

# Start the main event loop
root.mainloop()






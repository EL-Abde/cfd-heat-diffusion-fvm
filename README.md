# 2D Heat Diffusion Simulation - Finite Volume Method (C++)

## Description
This project simulates the 2D heat diffusion equation on a metal plate using the Finite Volume Method (FVM) in C++.

- Physics: A 10x10 mm plate, initially cold (300 K), with a hot disk (700 K) in the center.
- Method: Explicit Finite Volume Method (flux-based, energy conservative).
- Output: Generates CSV files containing the temperature field at different time steps.

This repository is designed specifically for students learning Scientific Computing / CFD. The code is heavily commented to explain the transition from the physical equation to the numerical algorithm.

## Requirements
- C++ Compiler: `g++` (version 6.0 or higher) or Clang.
- Build Tool: `make` (or simply run the `g++` commands manually).
- Python (Optional): `numpy` and `matplotlib` for visualizing the results.

## Compilation & Execution

### 1. Compile the code
Open a terminal in the project root and run:
```bash
make

Project structure:
                ├── include/          # Header files (.hpp)
                │   ├── params.hpp    # All physical & numerical parameters (edit these!)
                │   ├── solver.hpp    # Declaration of the FVM solver
                │   └── io.hpp        # Declaration of the save_grid function
                ├── src/              # Source files (.cpp)
                │   ├── main.cpp      # Main loop
                │   ├── solver.cpp    # The FVM Engine (flux calculations)
                │   └── io.cpp        # CSV file writing
                ├── Makefile          # Build automation
                └── visualize.py      # Python plotting script

To Customize:

Open include/params.hpp and modify the constants:

D : Change the thermal diffusivity (e.g., 1.0 for glass, 10.0 for copper).

DX, DY : Increase to 0.2 for a coarser grid (faster simulation) or decrease to 0.05 for higher accuracy.

T_HOT : Change the initial hot spot temperature.

After modifying, simply re-run make and make run.
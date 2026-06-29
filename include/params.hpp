#ifndef PARAMS_HPP
#define PARAMS_HPP

/**
 * PHYSICAL AND NUMERICAL PARAMETERS
 * Alls quantities are in SI units (mm, K, s)
 */

// ---------- Plate goemtry (mm) ----------
constexpr double WIDTH = 10.0;  // Plate width (X-axis)
constexpr double HEIGHT = 10.0; // Plate height (Y-axis)

// ---------- Spatial discretization ----------
constexpr double DX = 0.1;  // Spatial step in X (mm)
constexpr double DY = 0.1;  // Spatial step in Y (mm)

// ---------- Material properties ----------
constexpr double D = 4.0; // Diffusivity of the solid material (mm2/s)

// ---------- Initial and boundary conditions ----------
constexpr double T_COLD = 300.0; // Cold temperature and the boundaries and initial state
constexpr double T_HOT = 700.0; // Hot temperature at the central disk

// ---------- Grid dimensions ----------
constexpr int NX = static_cast<int>(WIDTH / DX);
constexpr int NY = static_cast<int>(HEIGHT / DY);

/**
 * TIME STEP CALCULATION (DT)
 * For the explicit scheme to remain STABLE, DT cannot be too large.
 * The CFL stability condition for the 2D heat equation is:
 * DT <= (DX² * DY²) / (2 * D * (DX² + DY²))
 * 
 * We take the maximum allowed value to speed up the simulation.
 */

constexpr double DT = (DX*DX * DY*DY) / (2.0 * D * (DX*DX + DY*DY));

// ---------- Time lopp parameters ----------
constexpr int NUM_STEPS = 301; // time step from 0 to 100

// ---------- Time lopp parameters ----------
constexpr int SAVE_STEPS[] = {0, 50, 100, 300}; // Time of snapshots
constexpr int NUM_SAVES = 4; // Number of saves

#endif // PARAMS_HPP
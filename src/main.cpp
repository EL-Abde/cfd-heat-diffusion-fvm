#include "params.hpp"
#include "solver.hpp"
#include "io.hpp"
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>

/**
 * INITIALIZE THE TEMPERATURE FIELD
 * Creates a hot disc (T_HOT) at the center, cold elsewhere (T_COLD).
 */
void initialize(std::vector<double>& T0, std::vector<double>& T) {
    const double r  = 2.0;    // Radius of the hot disc (mm)
    const double cx = 5.0;    // Center of the disc in X
    const double cy = 5.0;    // Center of the disc in Y

    for (int i = 0; i < NX; ++i) {
        for (int j = 0; j < NY; ++j) {
            double x = i * DX;
            double y = j * DY;
            double dist2 = (x - cx) * (x - cx) + (y - cy) * (y - cy);
            double val = (dist2 < r * r) ? T_HOT : T_COLD;
            T0[i * NY + j] = val;
            T[i * NY + j]  = val;
        }
    }
}

int main() {
    // --- Display simulation info ---
    std::cout << "==========================================" << std::endl;
    std::cout << "HEAT DIFFUSION SIMULATION - FINITE VOLUMES" << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << "Grid : " << NX << " x " << NY << " cells" << std::endl;
    std::cout << "Time step (DT) : " << DT << " s" << std::endl;
    std::cout << "Total simulated time : " << DT * (NUM_STEPS - 1) << " s" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    // --- Allocate memory ---
    std::vector<double> T0(NX * NY);
    std::vector<double> T (NX * NY);

    // --- Initialize ---
    initialize(T0, T);

    // --- Save initial state ---
    save_grid(T0, 0);

    // --- Start timer ---
    auto start = std::chrono::high_resolution_clock::now();

    // --- Main time loop ---
    for (int n = 1; n < NUM_STEPS; ++n) {
        // Compute new field
        advance_timestep(T0, T);

        // Copy T into T0 for the next iteration
        std::copy(T.begin(), T.end(), T0.begin());

        // Save at specific steps
        for (int s = 0; s < NUM_SAVES; ++s) {
            if (n == SAVE_STEPS[s]) {
                save_grid(T, n);
                break;
            }
        }

        // Progress indicator every 10 steps
        if (n % 10 == 0) {
            std::cout << "Progress : " << n << " / " << NUM_STEPS-1 << " steps" << std::endl;
        }
    }

    // --- Stop timer ---
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // --- Final summary ---
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Simulation complete!" << std::endl;
    std::cout << "Execution time : " << elapsed.count() << " seconds." << std::endl;
    std::cout << "Run 'python visualize.py' to see the graphs." << std::endl;

    return 0;
}
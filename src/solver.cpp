#include "solver.hpp"
#include "params.hpp"

/**
 * ============================================================
 * TIME STEP USING THE FINITE VOLUME METHOD (FVM)
 * ============================================================
 * 
 * PHYSICAL PRINCIPLE:
 * Consider a small cell (control volume) centered at P.
 * The temperature changes over time if heat flows through its walls.
 * 
 * BALANCE EQUATION (over the volume V = DX * DY) :
 * 
 *    ∫∫∫ (∂T/∂t) dV = D * ∮ (∇T · n) dS
 * 
 * In discrete form (centered differences on faces) :
 * 
 *    T_P^{n+1} = T_P^n + (DT / (DX*DY)) * [ q_E + q_W + q_N + q_S ]
 * 
 * where q_E is the heat flux entering through the East (right) face :
 *    q_E = D * (T_E - T_P) / DX * DY
 * 
 * This is exactly what the function below calculates.
 * ============================================================
 */

void advance_timestep(const std::vector<double>& T0, std::vector<double>& T) {
    
    // Loop over interior cells only (boundaries remain at T_COLD)
    for (int i = 1; i < NX - 1; ++i) {
        for (int j = 1; j < NY - 1; ++j) {
            
            // Index of the current cell in the 1D array
            int idx_P = i * NY + j;
            
            // Indices of the four neighbors
            int idx_E = i * NY + (j + 1);   // East
            int idx_W = i * NY + (j - 1);   // West
            int idx_N = (i + 1) * NY + j;   // North
            int idx_S = (i - 1) * NY + j;   // South

            // Heat fluxes through the faces
            double flux_E = D * (T0[idx_E] - T0[idx_P]) / DX * DY;
            double flux_W = D * (T0[idx_W] - T0[idx_P]) / DX * DY;
            double flux_N = D * (T0[idx_N] - T0[idx_P]) / DY * DX;
            double flux_S = D * (T0[idx_S] - T0[idx_P]) / DY * DX;

            // Update temperature - explicit Euler
            T[idx_P] = T0[idx_P] + (DT / (DX * DY)) * (flux_E + flux_W + flux_N + flux_S);
        }
    }
}
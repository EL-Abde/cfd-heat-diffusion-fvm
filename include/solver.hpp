#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>

/**
 * Advance one time step
 * @param T0 Temperature field at the current time step
 * @param T Temperature field at next time
 */
void advance_timestep(const std::vector<double>& T0, std::vector<double>& T);

#endif // SOVLER_HPP
#ifndef IO_HPP
#define IO_HPP

#include <vector>

/**
 * SAVE THE 2D GRID TO A CSV FILE
 *
 * The grid is stored row by row. The file name is output_XXX.csv
 * where XXX is the zero-padded step number.
 *
 * @param T     Temperature field to save
 * @param step  Current time step index
 */
void save_grid(const std::vector<double>& T, int step);

#endif // IO_HPP
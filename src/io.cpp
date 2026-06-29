#include "io.hpp"
#include "params.hpp"
#include <fstream>
#include <iostream>
#include <cstdio>

void save_grid(const std::vector<double>& T, int step) {
    // Build filename with zero-padded step number
    char filename[50];
    std::sprintf(filename, "output_%03d.csv", step);
    
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "ERROR: Could not open file " << filename << std::endl;
        return;
    }

    // Write the grid row by row
    for (int i = 0; i < NX; ++i) {
        for (int j = 0; j < NY; ++j) {
            file << T[i * NY + j];
            if (j < NY - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
    std::cout << "Saved : " << filename << std::endl;
}
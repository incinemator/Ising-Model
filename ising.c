#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Constants
#define N 20 // Lattice size
#define J 1.0 // Coupling constant
#define bK 1.0 // Boltzmann consant
#define T 2.0 // Temperature

int lattice[N][N];

// Initialize the lattice with random spins
void initialize() 
{
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            lattice[i][j] = (rand() % 2) * 2 - 1; // Randomly assigns spin up or down
        }
    }
}

// Calculate the energy of the lattice
double calculateEnergy() 
{
    double energy = 0.0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            energy += -J * lattice[i][j] * (lattice[(i + 1) % N][j] + lattice[i][(j + 1) % N]);
        }
    }
    return energy;
}

// Flip a spin and calculate the change in energy
double flipSpin(int i, int j) {
    int oldSpin = lattice[i][j];
    int newSpin = -oldSpin;
    double deltaE = 2 * J * oldSpin * (lattice[(i + 1) % N][j] + lattice[i][(j + 1) % N]);
    return deltaE;
}

// The Metropolis algorithm
void metropolis() {
    for (int k = 0; k < N * N; k++) {
        int i = rand() % N;
        int j = rand() % N;
        double deltaE = flipSpin(i, j);
        if (deltaE <= 0 || ((double)rand() / RAND_MAX) < exp(-deltaE / (kB * T))) {
            lattice[i][j] *= -1; // Flip the spin
        }
    }
}
#include <iostream>
#include "Simulador.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso correto: ./tp2.out <arquivo.wkl>\n";
        return 1;
    }

    Simulador sim;
    sim.lerEntrada(argv[1]);
    sim.rodarSimulacao();

    return 0;
}

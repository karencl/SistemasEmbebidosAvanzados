// =================================================================
//
// File: exercise04.cpp
// Author(s): Karen Cebreros López - A01704254
// 			  Andrea González Arredondo - A01351820
// Description: This file implements the PI approximation using the
//				series proposed by Euler.
//				pi = sqrt ( 6 * sumatoria(i = 1-N) (1 / i^2) )
//				The time this implementation takes will be used as
//				the basis to calculate the improvement obtained with
//				parallel technologies.
//
// Copyright (c) 2022 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include "utils.h"

const int LIMIT = 1000000; //1e6

using namespace std;

int main(int argc, char* argv[]) {
	double ms = 0;
    long double result;

	cout << "Starting..." << endl;

	for (int i = 0; i < N; i++) {
		start_timer();

        result = 0;

        // Obtenemos pi a través de la serie de Euler. (La fórmula está dada arriba)
		for (long j = 1; j < LIMIT; j++) {
            // Primero hacemos la sumatoria
            result += 1.0 / (j * j);
        }
        // Luego hacemos la raíz de la sumatoria, multiplicada por 6
        result = sqrt(6 * result);

		ms += stop_timer();
	}
	cout << "result = " << setprecision(5) << result << "\n";
	cout << "avg time = " << setprecision(5) << (ms / N) << " ms" << endl;

	return 0;
}
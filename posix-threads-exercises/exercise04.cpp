// =================================================================
//
// File: exercise04.cpp
// Author(s): Karen Cebreros López - A01704254
// 			  Andrea González Arredondo - A01351820
// Description: This file implements the PI approximation using the
//				series proposed by Euler using using pthreads.
//				pi = sqrt ( 6 * sumatoria(i = 1-N) (1 / i^2) )
//              To compile: g++ exercise04.cpp -lpthread
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <omp.h>
#include "utils.h"
#include <pthread.h>
#include <omp.h>

const int LIMIT = 1000000; //1e6
const int THREADS = 1;

using namespace std;

typedef struct {
  int start, end; // [start, end)
} Block;

// Obtenemos pi a través de la serie de Euler
void* PI(void* param) {
    long double *acum, i;
    Block *block;

    block = (Block *) param;
    acum =  new long double;
    (*acum) = 0;
    for (i = block->start; i < block->end; i++) {
		// La sumatoria
        (*acum) += 1.0 / (i * i);
    }

    return ( (void**) acum );
}

int main(int argc, char* argv[]) {
	int block_size;
	long double *acum, result = 0;
	double ms = 0;

	Block blocks[THREADS];
    pthread_t tids[THREADS];

	block_size = LIMIT / THREADS;
	for (int i = 0; i < THREADS; i++) {

		// Empezamos en 1
        blocks[i].start = i * block_size + 1;

        if (i != (THREADS - 1)) {
            blocks[i].end = (i + 1) * block_size;
        } else {
            blocks[i].end = LIMIT;
        }
	}

	cout << "Starting..." << endl;
	for (int j = 0; j < N; j++) {
		start_timer();

		result = 0;
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, PI, (void*) &blocks[i]);
        }
        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], (void**) &acum);
            result += (*acum);
            delete acum;
        }

		// Raíz de la sumatoria, multiplicada por 6
		result = sqrt(6.0*result);

		ms += stop_timer();
	}
	cout << "result = " << fixed <<  setprecision(10) << result << "\n";
	cout << "avg time = " << setprecision(5) << (ms / N) << " ms" << endl;

	return 0;
}
// =================================================================
//
// File: exercise02.cpp
// Author(s): Karen Cebreros López - A01704254
// 			  Andrea González Arredondo - A01351820
// Description: This file contains the code that performs the sum of
//				all prime numbers less than or equal to MAXIMUM using 
//				pthreads.
//              To compile: g++ exercise02.cpp -lpthread
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <pthread.h>
#include <omp.h>
#include "utils.h"

#define MAXIMUM 1000000 //1e6

using namespace std;

const int THREADS = 4;

typedef long long int ill;

typedef struct {
  int start, end; // [start, end)
  int *arr;
} Block;

void* sumPrimeNumbers(void *param) {
    ill *acum;
    Block *block;
    
    block = (Block *) param;
    acum = new ill;
    (*acum) = 0;

    int i, j;
    for (i = block->start; i < block->end; i++) {

        // Usamos el método de la Criba de Eratóstenes. Ambos for loops empiezan en 2, porque sabemos que 1 y 0 NO son primos
        for (j = 2; j <= (int)sqrt(i); j++) {
            if (i % j == 0)
                break;
        }

        if (j > (int)sqrt(i))
            (*acum) += i;
    }

    return ( (void**) acum );
}

int main(int argc, char* argv[]) {
	int block_size;
	double ms = 0;
    ill *acum, result = 0;

    Block blocks[THREADS];
    pthread_t tids[THREADS];

    block_size = MAXIMUM / THREADS;
    for (int i = 0; i < THREADS; i++) {
        // Empezar en 2
        blocks[i].start = i * block_size + 2;
        if (i != (THREADS - 1)) {
            blocks[i].end = (i + 1) * block_size;
        } else {
            blocks[i].end = MAXIMUM;
        }
    }

	cout << "Starting..." << endl;
	for (int j = 0; j < N; j++) {
		start_timer();

		result = 0;
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, sumPrimeNumbers, (void*) &blocks[i]);
        }
        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], (void**) &acum);
            result += (*acum);
            delete acum;
        }

		ms += stop_timer();
	}
	cout << "result = " << fixed << setprecision(0) << result << "\n";
	cout << "avg time = " << fixed <<  setprecision(5) << (ms / N) << " ms" << endl;

	return 0;
}
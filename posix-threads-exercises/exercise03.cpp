// =================================================================
//
// File: exercise03.cpp
// Author(s): Karen Cebreros López - A01704254
// 			  Andrea González Arredondo - A01351820
// Description: This file contains the code that implements the
//				enumeration sort algorithm using pthreads.
//              To compile: g++ exercise03.cpp -lpthread
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <pthread.h>
#include <omp.h>
#include "utils.h"

const int SIZE = 10000; //1e4
const int THREADS = 1;

using namespace std;

typedef struct {
    int start, end; // [start, end)
    int *arr, *sorted_arr; // arreglo desordenado y arreglo ordenado
} Block;

void* eSort(void* param) {
    int max;
    Block *block;

    block = (Block *) param;
    for (int i = block->start; i < block->end; i++) {
        max = SIZE - 1;

        // Se busca el elemento con menor valor con las condiciones dadas en el doc de GitHub
        for (int j = 0; j < SIZE; j++) {
            if ((block->arr[i] < block->arr[j]) || (block->arr[i] == block->arr[j] && i < j))
                max--;
        }

        // Se agrega valor al arreglo ordenado, dependiendo de la posición dada por "max"
        block->sorted_arr[max] = block->arr[i];
    }

    return ( (void**) block->sorted_arr );
}

int main(int argc, char* argv[]) {
	int *a, *b, block_size;
	double ms = 0;

    Block blocks[THREADS];
    pthread_t tids[THREADS];

	a = new int[SIZE];
    b = new int[SIZE];
	random_array(a, SIZE);
	display_array("before", a);

    block_size = SIZE / THREADS;
    for (int i = 0; i < THREADS; i++) {

		blocks[i].arr = a;
        blocks[i].sorted_arr = b;
        blocks[i].start = i * block_size;
        if (i != (THREADS - 1)) {
            blocks[i].end = (i + 1) * block_size;
        } else {
            blocks[i].end = SIZE;
        }
	}

	cout << "Starting..." << endl;
	for (int j = 0; j < N; j++) {
		start_timer();

        b = new int[SIZE];

        for (int i = 0; i < THREADS; i++) 
            pthread_create(&tids[i], NULL, eSort, (void*) &blocks[i]);
        
        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], (void**) &b);
        }

		ms += stop_timer();

		if (j != N - 1) 
			delete [] b;
	}

	display_array("after", b);
	cout << "avg time = " << fixed <<  setprecision(5) << (ms / N) << " ms" << endl;

	delete [] a;
	delete [] b;
	return 0;
}
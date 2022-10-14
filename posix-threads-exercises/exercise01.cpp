// =================================================================
//
// File: exercise01.cpp
// Author(s): Karen Cebreros López - A01704254
// 			  Andrea González Arredondo - A01351820
// Description: This file contains the code to count the number of
//				even numbers within an array using pthreads.
//              To compile: g++ exercise01.cpp -lpthread
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <omp.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 1000000000; //1e9
const int THREADS = 4;

using namespace std;

typedef struct {
  int start, end; // [start, end)
  int *arr;
} Block;

void* evenNumbersCount(void* param) {
    int *acum, i;
    Block *block;

    block = (Block *) param;
    acum =  new int;
    (*acum) = 0;
    for (i = block->start; i < block->end; i++) {
        if (block->arr[i] % 2 == 0)
            (*acum)++;
    }

    return ( (void**) acum );
}

int main(int argc, char* argv[]) {
	int *a, *acum, block_size, result = 0;
	double ms = 0;

    Block blocks[THREADS];
    pthread_t tids[THREADS];

	a = new int[SIZE];
	fill_array(a, SIZE);
	display_array("a", a);

    block_size = SIZE / THREADS;
	for (int i = 0; i < THREADS; i++) {

		blocks[i].arr = a;
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

        result = 0;
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, evenNumbersCount, (void*) &blocks[i]);
        }
        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], (void**) &acum);
            result += (*acum);
            delete acum;
        }

        ms += stop_timer();
    }
	cout << "result = " << fixed << setprecision(0) << result << "\n";
	cout << "avg time = " <<  fixed << setprecision(5) << (ms / N) << " ms" << endl;

	delete [] a;
	return 0;
}
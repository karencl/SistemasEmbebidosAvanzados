// =================================================================
//
// File: exercise03.cpp
// Author(s): Karen Cebreros López - A01704254
// 			  Andrea González Arredondo - A01351820
// Description: This file contains the code that implements the
//				enumeration sort algorithm. The time this implementation
//				takes ill be used as the basis to calculate the
//				improvement obtained with parallel technologies.
//
// Copyright (c) 2022 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include "utils.h"

const int SIZE = 10000; //1e4

using namespace std;

int main(int argc, char* argv[]) {
	int *a, *b, max;
	double ms = 0;

	a = new int[SIZE];
    b = new int[SIZE];

	random_array(a, SIZE);
	display_array("before", a);

	cout << "Starting..." << endl;

	for (int i = 0; i < N; i++) {
		start_timer();

		for (int j = 0; j < SIZE; j++) {
            max = SIZE - 1;

            // Se busca el elemento con menor valor
            for (int k = 0; k < SIZE; k++) {
                if ((a[j] < a[k]) || (a[j] == a[k] && j < k))
                    max--; 
            } 

            // Se agrega valor al nuevo arreglo, dependiendo de la posición dada por "max"
            b[max] = a[j];
        }

		ms += stop_timer();
	}
	display_array("after", b);
	cout << "avg time = " << setprecision(5) << (ms / N) << " ms" << endl;

	delete [] a;
    delete [] b;
	return 0;
}
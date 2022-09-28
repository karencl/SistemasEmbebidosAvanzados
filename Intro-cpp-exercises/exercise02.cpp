// =================================================================
//
// File: exercise02.cpp
// Author(s): Karen Cebreros López - A01704254
// 			  Andrea González Arredondo - A01351820
// Description: This file contains the code that performs the sum of
//				all prime numbers less than or equal to MAXIMUM. The 
//				time this implementation takes will be used as the 
//				basis to calculate the improvement obtained with 
//				parallel technologies.
//
// Copyright (c) 2022 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "utils.h"

#define MAXIMUM 1000000 //1e6

using namespace std;

int main(int argc, char* argv[]) {
	int i;
	double ms = 0;
    long long result = 0;
    bool num_primo;

	cout << "Starting..." << endl;

	for (int i = 0; i < N; i++) {
        start_timer();

        // Usamos el método de la Criba de Eratóstenes. Ambos for loops empiezan en 2, porque sabemos que 1 y 0 NO son primos
        for (int i = 2; i < MAXIMUM; i++) {

            num_primo = true;
		    for (int j = 2; j < sqrt(i); j++) {
                if (i % j == 0) {
                    num_primo = false;
                    break;
                }
            
                if (num_primo)
                    result += i;
            }
	    }

        ms += stop_timer();
    }

	cout << "result = " << setprecision(5) << result << "\n";
	cout << "avg time = " << setprecision(5) << (ms / N) << " ms" << endl;

	return 0;
}
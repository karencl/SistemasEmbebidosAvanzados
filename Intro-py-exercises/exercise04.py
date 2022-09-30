## =================================================================
##
## File: exercise04.py
## Author(s): Andrea Gonzalez Arredondo A01351820 Karen Cebreros Lopez A01704254
## Description: This file implements the PI approximation using the
##				series proposed by Euler.
##				pi = sqrt ( 6 * sumatoria(i = 1-N) (1 / i^2) )
##				The time this implementation takes will be used as
##				the basis to calculate the improvement obtained with
##				parallel technologies.
##
## Copyright (c) 2022 by Tecnologico de Monterrey.
## All Rights Reserved. May be reproduced for any non-commercial
## purpose.
##
## =================================================================

from cmath import sqrt
import utils
import time

SIZE = 1000000 ##1e6

## Place your code here

if __name__ == "__main__":

    print("Starting...")
    startTime = endTime = ms = 0
    result = 0.0
    j = 1

    for i in range(utils.N):
        startTime = time.time() * 1000
        result = 0

        # Obtenemos pi a través de la serie de Euler. (La fórmula está dada arriba)
        for j in range(1, SIZE+1):
            # Primero hacemos la sumatoria
            result += 1.0 / (j * j)

        # Luego hacemos la raíz de la sumatoria, multiplicada por 6
        result = sqrt(6 * result)

        endTime = time.time() * 1000
        ms = ms + (endTime - startTime)

    print("result = ", result)
    print("avg time = ", (ms / utils.N), " ms")
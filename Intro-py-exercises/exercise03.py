## =================================================================
##
## File: exercise03.py
## Author(s): Andrea Gonzalez Arredondo A01351820 Karen Cebreros Lopez A01704254
## Description: This file contains the code that implements the
##				enumeration sort algorithm. The time this implementation
##				takes ill be used as the basis to calculate the
##				improvement obtained with parallel technologies.
##
## Copyright (c) 2022 by Tecnologico de Monterrey.
## All Rights Reserved. May be reproduced for any non-commercial
## purpose.
##
## =================================================================

import utils
import time

SIZE = 10000 ##1e5

if __name__ == "__main__":
    array1 = [0] * SIZE
    array2 = [0] * SIZE

    utils.randomArray(array1)
    utils.displayArray("before", array1)

    print("Starting...")
    startTime = endTime = ms = result = 0

    for i in range(utils.N):
        startTime = time.time() * 1000

        for j in range(SIZE):
            max = SIZE - 1
            for k in range(SIZE):
                if ((array1[j] < array1[k]) or (array1[j] == array1[k] and j < k)):
                    max -= 1
            array2[max] = array1[j];

        endTime = time.time() * 1000

        ms = ms + (endTime - startTime)

    utils.displayArray("after", array2)
    print("avg time = ", (ms / utils.N), " ms")
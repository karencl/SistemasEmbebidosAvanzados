## =================================================================
##
## File: exercise01.py
## Author(s): Andrea Gonzalez Arredondo A01351820 Karen Cebreros Lopez A01704254
## Description: This file contains the code to count the number of
##				even numbers within an array using processes in 
##              Python.
##
## Copyright (c) 2022 by Tecnologico de Monterrey.
## All Rights Reserved. May be reproduced for any non-commercial
## purpose.
##
## =================================================================

import utils
import time
import multiprocessing as mp
import threading

# CORES = mp.cpu_count() 
CORES = 4
SIZE = 100000000 ##1e8

def evenNumbersCount(start, end, array, queue):
    acum = 0;
    for i in range(start, end):
        if (array[i] % 2 == 0):
            acum += 1

    queue.put(acum)    

if __name__ == "__main__":
    array = [0] * SIZE

    utils.fillArray(array)
    utils.displayArray("array", array)
    
    blockSize = SIZE // CORES

    print("Starting...")
    startTime = endTime = ms = 0
    result = 0
    for i in range(utils.N):
        startTime = time.time() * 1000

        queue = mp.SimpleQueue()
        processes = list()
        for i in range(CORES):
            start = i * blockSize
            if i != (CORES - 1):
                end = (i + 1) * blockSize
            else:
                end = SIZE
            process = mp.Process(target=evenNumbersCount, args=(start, end, array, queue,))            
            processes.append(process)
            process.start()
        
        result = 0
        for i in range(CORES):
            result += queue.get()

        endTime = time.time() * 1000

        ms = ms + (endTime - startTime)

    print("sum = ", result)
    print("avg time = ", (ms / utils.N), " ms")
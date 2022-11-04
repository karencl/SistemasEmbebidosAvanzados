## =================================================================
##
## File: exercise03.py
## Author(s): Andrea Gonzalez Arredondo A01351820 Karen Cebreros Lopez A01704254
## Description: This file contains the code that implements the
##				enumeration sort algorithm using processes in Python.
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
SIZE = 10000 ##1e5

def eSort(start, end, array, queue_new_pos):
    for i in range(start, end):
        pos = SIZE - 1
        for j in range (SIZE):
            if ((array[i] < array[j]) | (array[i] == array[j] & i < j)):
                pos -= 1
        pos_and_value = [pos, array[i]]
        queue_new_pos.put(pos_and_value)

if __name__ == "__main__":
    array = [0] * SIZE

    utils.randomArray(array)
    utils.displayArray("before", array)
    
    blockSize = SIZE // CORES

    print("Starting...")
    startTime = endTime = ms = 0
    for i in range(utils.N):
        startTime = time.time() * 1000

        queue_new_pos = mp.SimpleQueue()
        processes = list()
        for i in range(CORES):
            start = i * blockSize
            if i != (CORES - 1):
                end = (i + 1) * blockSize
            else:
                end = SIZE
            process = mp.Process(target=eSort, args=(start, end, array, queue_new_pos,))            
            processes.append(process)
            process.start()
        for process in processes:
            process.join()
            
        while not queue_new_pos.empty:
            elem = queue_new_pos.get()
            pos = elem[0]
            value = elem[1]
            array[pos] = value

        endTime = time.time() * 1000

        ms = ms + (endTime - startTime)

    utils.displayArray("after", array)
    print("avg time = ", (ms / utils.N), " ms")
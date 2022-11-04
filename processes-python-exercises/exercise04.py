## =================================================================
##
## File: exercise04.py
## Author(s): Andrea Gonzalez Arredondo A01351820 Karen Cebreros Lopez A01704254
## Description: This file implements the PI approximation using the
##				series proposed by Euler.
##				pi = sqrt ( 6 * sumatoria(i = 1-N) (1 / i^2) )
##				using processes in Python.
##
## Copyright (c) 2022 by Tecnologico de Monterrey.
## All Rights Reserved. May be reproduced for any non-commercial
## purpose.
##
## =================================================================

import utils
import time
from cmath import sqrt
import multiprocessing as mp
import threading

# CORES = mp.cpu_count() 
CORES = 1
SIZE = 1000000 ##1e6

# Obtenemos pi a través de la serie de Euler
def PI(start, end, queue):
    acum = 0
    for i in range(start, end):
        # La sumatoria
        acum += 1.0 / (i * i)
        
    queue.put(acum)
        

if __name__ == "__main__":
    
    blockSize = SIZE // CORES

    print("Starting...")
    startTime = endTime = ms = 0
    result = 0
    for i in range(utils.N):
        startTime = time.time() * 1000

        queue = mp.SimpleQueue()
        processes = list()
        for i in range(CORES):
            # Empezamos en 1
            start = i * blockSize + 1
            
            if i != (CORES - 1):
                end = (i + 1) * blockSize
            else:
                end = SIZE
            process = mp.Process(target=PI, args=(start, end, queue,))            
            processes.append(process)
            process.start()
        
        result = 0
        for i in range(CORES):
            result += queue.get()
        
        # Raíz de la sumatoria, multiplicada por 6
        result = sqrt(6.0 * result)

        endTime = time.time() * 1000
        ms = ms + (endTime - startTime)

    print("result = ", result)
    print("avg time = ", (ms / utils.N), " ms")
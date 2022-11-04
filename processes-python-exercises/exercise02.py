## =================================================================
##
## File: exercise02.py
## Author(s): Andrea Gonzalez Arredondo A01351820 Karen Cebreros Lopez A01704254 Aranza Leal Aguirre A01751706
## Description: This file contains the code that performs the sum of 
##				all prime numbers less than or equal to MAXIMUM 
##              using processes in Python.
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
MAXIMUM = 1000000 ##1e6

def sumPrimeNumbers(start, end, queue):
    acum = 0;
    
    # Usamos el método de la Criba de Eratóstenes. Ambos for loops empiezan en 2, porque sabemos que 1 y 0 NO son primos
    for i in range(start, end):
        isPrime = True
        for j in range(2,int(i**(1/2))+1):
            if (i % j == 0):
                isPrime = False
                break
        
        if isPrime:
            acum += i

    queue.put(acum) 

if __name__ == "__main__":
    blockSize = MAXIMUM // CORES

    print("Starting...")
    startTime = endTime = ms = 0
    result = 0
    for i in range(utils.N):
        startTime = time.time() * 1000

        queue = mp.SimpleQueue()
        processes = list()
        for i in range(CORES):
            start = i * blockSize + 2
            if i != (CORES - 1):
                end = (i + 1) * blockSize
            else:
                end = MAXIMUM
            process = mp.Process(target=sumPrimeNumbers, args=(start, end, queue,))            
            processes.append(process)
            process.start()
        
        result = 0
        for i in range(CORES):
            result += queue.get()

        endTime = time.time() * 1000

        ms = ms + (endTime - startTime)

    print("sum = ", result)
    print("avg time = ", (ms / utils.N), " ms")

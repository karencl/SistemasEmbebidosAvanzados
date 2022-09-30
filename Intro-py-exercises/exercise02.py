# =================================================================
# 
#  File: exercise02.py
#  Author(s): Andrea Gonzalez Arredondo A01351820 Karen Cebreros Lopez A01704254
#  Description: This file contains the code to count the number of
# 				even numbers within an array. The time this implementation
# 				takes will be used as the basis to calculate the
# 				improvement obtained with parallel technologies.
# 
#  Copyright (c) 2022 by Tecnologico de Monterrey.
#  All Rights Reserved. May be reproduced for any non-commercial
#  purpose.
# 
#  =================================================================

import utils
import time

maximo = 100000  

if __name__ == "__main__":
    print("Starting...")
    startTime = endTime = ms = 0
  
    for i in range(utils.N):
        resultado = 0
        startTime = time.time() * 1000
    # Suma todos los números primos menores o iguales al maximo
        for num in range(2, maximo + 1):
            isPrime = True
    # Comprueba todos los números del 2 a la raíz cuadrada del número actual
            for div in range(2, int(num**(1/2))+1):
    # Si num es divisible por div, no es primo
                if num % div == 0:
                    isPrime = False
                    break
    # Si el número es primo sumarlo al resultado
            if isPrime:
                resultado += num

        endTime = time.time() * 1000
        ms = ms + (endTime - startTime)
    print("sum = ", resultado)
    print("avg time = ", (ms / utils.N), " ms")
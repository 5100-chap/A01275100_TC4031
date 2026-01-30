#include <iostream>
#include <cstdlib>   
#include <ctime>
#include <omp.h>
#include <sstream>
#include <limits>

#define UPPERLIMIT 1000000
#define LOWLIMITRAND 1
#define HIGHLIMITRAND 100

int randomNumber(){
    return int(LOWLIMITRAND + (rand() % (HIGHLIMITRAND - LOWLIMITRAND + 1)));
}

void randomFill(int* arr, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arr[i] = randomNumber();
    }
}

void printArray(int* arr, int n) {
    std::ostringstream buffer;
    buffer << "\n[";
    for (int i = 0; i < n; i++) {
        buffer << arr[i];
        if (i < n - 1) buffer << ", ";
    }
    buffer << "]\n";
    std::cout << buffer.str();
}

void parallelSum(int* arrA, int* arrB, int* arrRes, int n) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        arrRes[i] = arrA[i] + arrB[i];
    }
}


int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    int temp;
    int len;
    std::cout << "Tarea 1. Programación de una solución paralela\n";
    std::cout << "Diego Alberto Baños Lopez - A01275100\n";
    std::cout << "Favor de establecer el tamaño del array, el valor debe de estar del rango del 2-" << UPPERLIMIT << "\n";
    std::cout << "Opción 1: Introducir un valor propio\n";
    std::cout << "Opción 2: Introducir un valor aleatorio\n";
    std::cout << "Opción 3: Introducir el valor máximo permitido (" << UPPERLIMIT << ")\n";
    while (!(std::cin >> temp) || temp < 1 || temp > 3) {
        std::cout << "Valor invalido, favor de ingresar una opción: ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    switch(temp) {
        case 1:
            std::cout << "Favor de introducir un valor propio\n";
            while (!(std::cin >> len) || len < 2 || len > UPPERLIMIT) {
                std::cout << "Valor invalido, debe de esta entre el 2-" << UPPERLIMIT << ": ";
                std::cin.clear(); 
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            break;
        case 2: 
            std::cout << "Generando un tamaño aleatorio\n";
            len = randomNumber();
            std::cout << "El tamaño es de " << len << " elementos. \n";
            break;
        default:
            std::cout << "Estableciendo el tamaño máximo\n";
            len = UPPERLIMIT;
    }

    int* arrayA = new int[len];
    int* arrayB = new int[len];
    int* resArray = new int[len];
    
    randomFill(arrayA, len); 
    randomFill(arrayB, len);  
    std::cout << "\nElementos del primer array:\n";
    printArray(arrayA, len);
    std::cout << "\nElementos del segundo array:\n";
    printArray(arrayB, len);
    std::cout << "\nRealizando suma en paralelo:\n";
    parallelSum(arrayA, arrayB, resArray, len);
    std::cout << "\nResultado suma en paralelo:\n";
    printArray(resArray, len);
    delete[] arrayA;
    delete[] arrayB;
    delete[] resArray;
    
    return 0;
}
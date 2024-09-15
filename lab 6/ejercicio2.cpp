#include <pthread.h>
#include <iostream>
#include <cmath>

using namespace std;

struct ThreadParameters {
    int number; //n
    double result; //resultado
};

void* Calc(void* args) { //subrutina para calcular el resultado
    ThreadParameters* parameters = static_cast<ThreadParameters*>(args); //convierte de void* a ThreadParameters*
    parameters->result = 3.0 / pow(2.0, parameters->number);
    pthread_exit(nullptr);
}

int main() {
    int NTHREADS; //número de threads a usar, que es igual a la n ingresada por el usuario

    cout << "Ingresa el valor de n que desea calcular: ";
    cin >> NTHREADS;

    pthread_t* threads = new pthread_t[NTHREADS]; //array threads
    ThreadParameters* threadParameters = new ThreadParameters[NTHREADS]; //array parámetros

    for (int i = 0; i < NTHREADS; ++i) { //número para el thread
        threadParameters[i].number = i;
        threadParameters[i].result = 0.0;
        pthread_create(&threads[i], nullptr, Calc, &threadParameters[i]); //crear thread
    }

    double totalSum = 0.0;
    for (int i = 0; i < NTHREADS; ++i) {
        pthread_join(threads[i], nullptr); //unir threads
        totalSum += threadParameters[i].result; //sumar resultado de cada thread
    }

    cout << "La suma total de la serie es: " << totalSum << endl;

    delete[] threads; // liberar memoria
    delete[] threadParameters; // liberar memoria

    pthread_exit(nullptr);
    return 0;
}
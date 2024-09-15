#include <pthread.h>
#include <iostream>
#include <cmath>

using namespace std;

struct ThreadParameters {
    int start; //inicio del rango
    int end; //final del rango
    int sum; //suma del rango
};

bool Primo(int number) { //función para verificar si es primo o no
    if (number <= 1) { //los números menores o iguales a 1 no son primos
        return false;
    }
    for (int i = 2; i * i <= number; i++) { //verifica si el número es divisible entre todos los números desde el dos hasta la raíz cuadrada del número
        if (number % i == 0) { //si el residuo es 0, no es primo
            return false;
        }
    }
    return true; //en cualquier otro resultado, es primo
}

void* Find(void* args) { //subrutina para sumar si es primo
    ThreadParameters* parameters = static_cast<ThreadParameters*>(args); //convierte de void* a ThreadParameters*
    parameters->sum = 0; //iniciar suma en 0

    for (int i = parameters->start; i <= parameters->end; i++) { //para los números desde el inicio hasta el final en los parámetros del thread
        if (Primo(i)) { //si es primo
            parameters->sum += i; //suma el número
        }
    }

    //Indicar que termina la subrutina
    pthread_exit(nullptr);
}

int main() {
    int totalSum = 0; //suma de todas las sumas de los threads
    int MAX; //número máximo hasta donde se encuentran los primos
    int NTHREADS; //número de threads a usar

    cout << "Ingresa el valor máximo: ";
    cin >> MAX;
    cout << "Ingresa el número de threads para trabajar: ";
    cin >> NTHREADS;

    if (NTHREADS <= 0) { //comprobar que no se solicita trabajar con 0 threads
        cout << "El número de threads debe ser mayor a 0" << endl;
        return 1;
    }

    pthread_t* threads = new pthread_t[NTHREADS]; //array threads
    ThreadParameters* threadParameters = new ThreadParameters[NTHREADS]; //array parámetros

    int elementos = MAX / NTHREADS; //identificar la cantidad de elementos que procesa cada hilo
    int residuo = MAX % NTHREADS; //identificar el residuo

    for (int i = 0; i < NTHREADS; ++i) { //rango de números para el thread
        threadParameters[i].start = i * elementos + 1;
        threadParameters[i].end = (i + 1) * elementos;

        if (i == NTHREADS - 1) { //si es el último thread, asignarle el resto del trabajo, si hay residuo
            threadParameters[i].end += residuo;
        }

        pthread_create(&threads[i], nullptr, Find, &threadParameters[i]); //crear thread
    }

    for (int i = 0; i < NTHREADS; ++i) {
        pthread_join(threads[i], nullptr); //unir todos los threads
        totalSum += threadParameters[i].sum; //sumar los resultados de cada thread
    }

    cout << "La suma total de los números primos es: " << totalSum << endl;

    delete[] threads; //liberar memoria
    delete[] threadParameters; //liberar memoria

    pthread_exit(nullptr);
    return 0;
}

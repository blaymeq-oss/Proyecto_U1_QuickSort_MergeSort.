#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>

using namespace std;

// ==========================================
// 1. MERGESORT CON ARREGLOS NATIVOS Y MÉTRICAS
// ==========================================
void merge(int arr[], int izq, int medio, int der, long long& comp, long long& inter) {
    int n1 = medio - izq + 1;
    int n2 = der - medio;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[izq + i];
    for (int j = 0; j < n2; j++) R[j] = arr[medio + 1 + j];

    int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2) {
        comp++; // Conteo de comparación
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        inter++; // Conteo de movimiento en el arreglo
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        inter++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        inter++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSortHelper(int arr[], int izq, int der, long long& comp, long long& inter, int prof, int& prof_max) {
    if (izq < der) {
        prof++;
        if (prof > prof_max) prof_max = prof;

        int medio = izq + (der - izq) / 2;
        mergeSortHelper(arr, izq, medio, comp, inter, prof, prof_max);
        mergeSortHelper(arr, medio + 1, der, comp, inter, prof, prof_max);
        merge(arr, izq, medio, der, comp, inter);
    }
}

void ejecutarMergeSort(int arr[], int n, long long& comp, long long& inter, int& prof_max) {
    comp = 0;
    inter = 0;
    prof_max = 0;
    if (n <= 1) return;
    mergeSortHelper(arr, 0, n - 1, comp, inter, 0, prof_max);
}

// ==========================================
// 2. QUICKSORT CON ARREGLOS NATIVOS Y MÉTRICAS
// ==========================================
int particion(int arr[], int bajo, int alto, long long& comp, long long& inter) {
    int pivote = arr[alto];
    int i = (bajo - 1);

    for (int j = bajo; j <= alto - 1; j++) {
        comp++;
        if (arr[j] <= pivote) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            inter++;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = temp;
    inter++;

    return (i + 1);
}

void quickSortHelper(int arr[], int bajo, int alto, long long& comp, long long& inter, int prof, int& prof_max) {
    if (bajo < alto) {
        prof++;
        if (prof > prof_max) prof_max = prof;

        int pi = particion(arr, bajo, alto, comp, inter);
        quickSortHelper(arr, bajo, pi - 1, comp, inter, prof, prof_max);
        quickSortHelper(arr, pi + 1, alto, comp, inter, prof, prof_max);
    }
}

void ejecutarQuickSort(int arr[], int n, long long& comp, long long& inter, int& prof_max) {
    comp = 0;
    inter = 0;
    prof_max = 0;
    if (n <= 1) return;
    quickSortHelper(arr, 0, n - 1, comp, inter, 0, prof_max);
}

// ==========================================
// 3. GENERADORES DE PATRONES CON ARREGLOS NATIVOS
// ==========================================
void generarDatos(int arr[], int n, string patron, mt19937& rng) {
    if (patron == "aleatorio") {
        uniform_int_distribution<int> dist(1, n * 10);
        for (int i = 0; i < n; i++) arr[i] = dist(rng);
    } 
    else if (patron == "ascendente") {
        for (int i = 0; i < n; i++) arr[i] = i;
    } 
    else if (patron == "descendente") {
        for (int i = 0; i < n; i++) arr[i] = n - i;
    } 
    else if (patron == "casi_ordenado") {
        for (int i = 0; i < n; i++) arr[i] = i;
        int permutas = max(1, (int)(n * 0.05)); // 5% permutados
        uniform_int_distribution<int> dist(0, n - 1);
        for (int p = 0; p < permutas; p++) {
            int idx1 = dist(rng);
            int idx2 = dist(rng);
            int temp = arr[idx1];
            arr[idx1] = arr[idx2];
            arr[idx2] = temp;
        }
    } 
    else if (patron == "duplicados") {
        uniform_int_distribution<int> dist(1, 20);
        for (int i = 0; i < n; i++) arr[i] = dist(rng);
    }
}

// Función auxiliar para copiar arreglos dinámicos
void copiarArreglo(int origen[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

// ==========================================
// 4. CONTROL EXPERIMENTAL (MAIN)
// ==========================================
int main() {
    int tamanios[] = {1000, 10000, 100000};
    int num_tamanios = 3;
    
    string patrones[] = {"aleatorio", "ascendente", "descendente", "casi_ordenado", "duplicados"};
    int num_patrones = 5;
    
    int repeticiones = 30;
    unsigned int semilla_base = 42;

    ofstream archivo("results/resultados_experimentales.csv");
    archivo << "algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,intercambios,profundidad_recursion,semilla\n";

    mt19937 rng(semilla_base);

    for (int t = 0; t < num_tamanios; t++) {
        int n = tamanios[t];
        
        // Reservar memoria para los arreglos base de este tamaño
        int* original = new int[n];
        int* arr_merge = new int[n];
        int* arr_quick = new int[n];

        for (int p = 0; p < num_patrones; p++) {
            string patron = patrones[p];

            for (int rep = 1; rep <= repeticiones; rep++) {
                unsigned int semilla_actual = semilla_base + rep + n;
                mt19937 rng_copia(semilla_actual);
                
                // Generar datos originales
                generarDatos(original, n, patron, rng_copia);

                // --- Probar Mergesort ---
                copiarArreglo(original, arr_merge, n);
                long long comp_m = 0, inter_m = 0;
                int prof_m = 0;

                auto inicio_m = chrono::steady_clock::now();
                ejecutarMergeSort(arr_merge, n, comp_m, inter_m, prof_m);
                auto fin_m = chrono::steady_clock::now();
                double tiempo_m = chrono::duration<double, milli>(fin_m - inicio_m).count();

                archivo << "Mergesort," << n << "," << patron << "," << rep << "," 
                        << tiempo_m << "," << comp_m << "," << inter_m << "," << prof_m << "," << semilla_actual << "\n";

                // --- Probar Quicksort ---
                copiarArreglo(original, arr_quick, n);
                long long comp_q = 0, inter_q = 0;
                int prof_q = 0;

                auto inicio_q = chrono::steady_clock::now();
                ejecutarQuickSort(arr_quick, n, comp_q, inter_q, prof_q);
                auto fin_q = chrono::steady_clock::now();
                double tiempo_q = chrono::duration<double, milli>(fin_q - inicio_q).count();

                archivo << "Quicksort," << n << "," << patron << "," << rep << "," 
                        << tiempo_q << "," << comp_q << "," << inter_q << "," << prof_q << "," << semilla_actual << "\n";
            }
            
        }

        // Liberar memoria de los arreglos de este tamaño
        delete[] original;
        delete[] arr_merge;
        delete[] arr_quick;

        cout << "Completado para n = " << n << endl;
    }

    archivo.close();
    cout << "Experimento finalizado con exito. Datos guardados en results/resultados_experimentales.csv" << endl;
    return 0;
}
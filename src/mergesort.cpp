#include <iostream>
using namespace std;

void mezcla(long long arr[], int izquierda, int medio, int derecha, long long& comparaciones);

void mergeSort(long long arr[], int izquierda, int derecha, long long& comparaciones);

int main() {
    int n;
    cout << "=== MERGE SORT (Entrada Manual) ===" << endl;
    cout << "Ingrese la cantidad de numeros que desea ordenar: ";
    cin >> n;

    long long* arr = new long long[n];
    cout << "Ingrese los " << n << " numeros (separados por espacio o enter):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    long long comparaciones = 0;
    mergeSort(arr, 0, n - 1, comparaciones);

    cout << "\n--- RESULTADO MERGE SORT ---" << endl;
    cout << "Numeros ordenados: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\nTotal de comparaciones realizadas: " << comparaciones << endl;

    delete[] arr;
    return 0;
}

void mezcla(long long arr[], int izquierda, int medio, int derecha, long long& comparaciones) {
    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;
    
    long long* L = new long long[n1];
    long long* R = new long long[n2];
    
    for (int i = 0; i < n1; i++) L[i] = arr[izquierda + i];
    for (int j = 0; j < n2; j++) R[j] = arr[medio + 1 + j];
    
    int i = 0, j = 0, k = izquierda;
    while (i < n1 && j < n2) {
        comparaciones++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    
    delete[] L;
    delete[] R;
}

void mergeSort(long long arr[], int izquierda, int derecha, long long& comparaciones) {
    if (izquierda < derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;
        mergeSort(arr, izquierda, medio, comparaciones);
        mergeSort(arr, medio + 1, derecha, comparaciones);
        mezcla(arr, izquierda, medio, derecha, comparaciones);
    }
}
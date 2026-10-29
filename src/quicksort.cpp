#include <iostream>

using namespace std;

// 1. Primero colocas la función particion
int particion(long long arr[], int bajo, int alto, long long& comparaciones);

// 2. Luego colocas la función quickSort
void quickSort(long long arr[], int bajo, int alto, long long& comparaciones);

// 3. Finalmente va el int main() al final
int main() {
    int n;
    cout << "=== QUICK SORT (Entrada Manual) ===" << endl;
    cout << "Ingrese la cantidad de numeros que desea ordenar: ";
    cin >> n;

    long long* arr = new long long[n];
    cout << "Ingrese los " << n << " numeros (separados por espacio o enter):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    long long comparaciones = 0;
    quickSort(arr, 0, n - 1, comparaciones);

    cout << "\n--- RESULTADO QUICK SORT ---" << endl;
    cout << "Numeros ordenados: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\nTotal de comparaciones realizadas: " << comparaciones << endl;

    delete[] arr;
    return 0;
}

int particion(long long arr[], int bajo, int alto, long long& comparaciones) {
    int medio = bajo + (alto - bajo) / 2;
    long long pivote = arr[medio];
    
    long long temp = arr[medio];
    arr[medio] = arr[alto];
    arr[alto] = temp;
    
    int i = bajo - 1;
    for (int j = bajo; j <= alto - 1; j++) {
        comparaciones++;
        if (arr[j] <= pivote) {
            i++;
            long long t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    long long t = arr[i + 1];
    arr[i + 1] = arr[alto];
    arr[alto] = t;
    
    return i + 1;
}

// 2. Luego colocas la función quickSort
void quickSort(long long arr[], int bajo, int alto, long long& comparaciones) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto, comparaciones);
        quickSort(arr, bajo, pi - 1, comparaciones);
        quickSort(arr, pi + 1, alto, comparaciones);
    }
}

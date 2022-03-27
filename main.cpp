#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

ifstream f("data.in");

void citire(int v[], int &n) {
    f >> n;
    for (int i = 0; i < n; i++)
        f >> v[i];
}

int maxim(int v[], int n) {
    int maxx = v[0];
    for (int i = 1; i < n; i++)
        if (maxx < v[i])
            maxx = v[i];
    return maxx;
}

void countingsort(int v[], int n, int poz) {
    int *afis;
    afis = new int[n];
    int numere[10] = {0};
    for (int i = 0; i < n; i++)
        numere[(v[i] / poz) % 10]++;
    for (int i = 1; i < 10; i++)
        numere[i] += numere[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        afis[numere[(v[i] / poz) % 10] - 1] = v[i];
        numere[(v[i] / poz) % 10]--;
    }
    for (int i = 0; i < n; i++)
        v[i] = afis[i];
}

void radix(int v[], int n) {
    int poz, i;
    i = maxim(v, n);
    for (poz = 1; i / poz > 0; poz *= 10)
        countingsort(v, n, poz);
}

//_________________________________________________________________________________________________________________________________________________Radix Sort

void merges(int v[], int s, int n, int d) {
    int i, j, k;
    int zona1 = n - s + 1;
    int zona2 = d - n;
    int *a, *b;
    a = new int [zona1];
    b = new int [zona2];

    for (i = 0; i < zona1; i++)
        a[i] = v[s + i];
    for (j = 0; j < zona2; j++)
        b[j] = v[n + 1 + j];

    i = 0, j = 0, k = s;

    while (i < zona1 && j < zona2) {
        if (a[i] <= b[j])
            v[k++] = a[i++];
        else
            v[k++] = b[j++];
    }

    while (i < zona1)
        v[k++] = a[i++];
    while (j < zona2)
        v[k++] = b[j++];

}

void mergesort(int v[], int s, int d) {
    int n;
    if (s < d) {
        n = s + (d - s) / 2;
        mergesort(v, s, n);
        mergesort(v, n + 1, d);

        merges(v, s, n, d);
    }
}

//_________________________________________________________________________________________________________________________________________________Merge Sort


void shellsort(int v[], int n) {
    int aux, x;
    for (int i = n / 2; i > 0; i = i / 2) {
        int j = i;
        while (j < n) {
            int aux = v[j];
            int x;
            for (x = j; x >= i && v[x - i] > aux; x -= i) {
                v[x] = v[x - i];
            }
            v[x] = aux;
            j++;
        }
    }
}

//_________________________________________________________________________________________________________________________________________________Shell Sort


int sortare(int v[], int st, int dr) {
    int nr = 0, aux;
    while (st < dr) {
        if (v[st] > v[dr]) {
            aux = v[st];
            v[st] = v[dr];
            v[dr] = aux;
            nr++;
        }
        if (nr % 2 == 0)
            dr--;
        else
            st++;
    }
    return st;
}

void quicksort(int v[], int st, int dr) {
    int p;
    if (st < dr) {
        p = sortare(v, st, dr);
        quicksort(v, st, p - 1);
        quicksort(v, p + 1, dr);
    }
}

//_________________________________________________________________________________________________________________________________________________Quick Sort


void heap(int v[], int n, int i) {
    int mare, j, x;
    mare = i;
    j = 2 * i + 1;
    x = 2 * i + 2;
    if (j < n && v[j] > v[mare])
        mare = j;
    if (x < n && v[x] > v[mare])
        mare = x;
    if (mare != i) {
        int aux;
        aux = v[i];
        v[i] = v[mare];
        v[mare] = aux;
        heap(v, n, mare);
    }
}

void sortareheap(int v[], int n) {
    int i, aux;
    i = n / 2 - 1;
    while (i >= 0) {
        heap(v, n, i);
        i--;
    }
    i = n - 1;
    while (i >= 0) {
        aux = v[0];
        v[0] = v[i];
        v[i] = aux;
        heap(v, i, 0);
        i--;
    }
}
//_________________________________________________________________________________________________________________________________________________Heap Sort


void sortarestl(int v[], int n) {
    sort(v, v + n);
}

void afisare(int v[], int n) {
    for (int i = 0; i < n; i++)
        cout << v[i] << " ";
    cout << endl;
    cout << endl;
}

int main() {
    int n, *v, *aux, nmax, T;

    f >> T;
    cout << T << "\n";
    for (int r = 0; r < T; r++) {
        f >> n >> nmax;
        cout << n << " " << nmax << endl;
        v = new int[n];
        aux = new int[n];
        srand((unsigned) time(NULL));
        for (int i = 0; i < n; i++)
            v[i] = aux[i] = rand() % nmax;
        auto start1 = std::chrono::steady_clock::now();
        radix(v, n);
        for (int j = 0; j < n - 1; j++)
            if (v[j] > v[j + 1]) {
                cout << "Algoritmul Radixsort nu a sortat corect";
                auto end1 = std::chrono::steady_clock::now();
                double timp1 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count());
                break;
            }
        auto end1 = std::chrono::steady_clock::now();
        double timp1 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count());
        cout << "Algoritmul Radixsort a sortat corect in: " << timp1 / 1e9 << "\n";

        for (int i = 0; i < n; i++)
            v[i] = aux[i];
        auto start2 = std::chrono::steady_clock::now();
        mergesort(v, 0, n - 1);
        for (int j = 0; j < n - 1; j++)
            if (v[j] > v[j + 1]) {
                cout << "Algoritmul Mergesort nu a sortat corect";
                auto end2 = std::chrono::steady_clock::now();
                double timp2 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count());
                break;
            }
        auto end2 = std::chrono::steady_clock::now();
        double timp2 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count());
        cout << "Algoritmul Mergesort a sortat corect in: " << timp2 / 1e9 << "\n";

        for (int i = 0; i < n; i++)
            v[i] = aux[i];
        auto start3 = std::chrono::steady_clock::now();
        shellsort(v, n);
        for (int j = 0; j < n - 1; j++)
            if (v[j] > v[j + 1]) {
                cout << "Algoritmul Shellsort nu a sortat corect";
                auto end3 = std::chrono::steady_clock::now();
                double timp3 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count());
                break;
            }
        auto end3 = std::chrono::steady_clock::now();
        double timp3 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count());
        cout << "Algoritmul Shellsort a sortat corect in: " << timp3 / 1e9 << "\n";

        for (int i = 0; i < n; i++)
            v[i] = aux[i];
        auto start4 = std::chrono::steady_clock::now();
        quicksort(v, 0, n - 1);
        for (int j = 0; j < n - 1; j++)
            if (v[j] > v[j + 1]) {
                cout << "Algoritmul Quicksort nu a sortat corect";
                auto end4 = std::chrono::steady_clock::now();
                double timp4 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - start4).count());
                break;
            }
        auto end4 = std::chrono::steady_clock::now();
        double timp4 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - start4).count());
        cout << "Algoritmul Quicksort a sortat corect in: " << timp4 / 1e9 << "\n";

        for (int i = 0; i < n; i++)
            v[i] = aux[i];
        auto start5 = std::chrono::steady_clock::now();
        sortareheap(v, n);
        for (int j = 0; j < n - 1; j++)
            if (v[j] > v[j + 1]) {
                cout << "Algoritmul Heapsort nu a sortat corect";
                auto end5 = std::chrono::steady_clock::now();
                double timp5 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end5 - start5).count());
                break;
            }
        auto end5 = std::chrono::steady_clock::now();
        double timp5 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end5 - start5).count());
        cout << "Algoritmul Heapsort a sortat corect in: " << timp5 / 1e9 << "\n";

        for (int i = 0; i < n; i++)
            v[i] = aux[i];
        auto start6 = std::chrono::steady_clock::now();
        sortarestl(v, n);
        for (int j = 0; j < n - 1; j++)
            if (v[j] > v[j + 1]) {
                cout << "Algoritmul Sort din STL nu a sortat corect";
                auto end6 = std::chrono::steady_clock::now();
                double timp6 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end6 - start6).count());
                break;
            }
        auto end6 = std::chrono::steady_clock::now();
        double timp6 = double(std::chrono::duration_cast<std::chrono::nanoseconds>(end6 - start6).count());
        cout << "Algoritmul Sort din STL a sortat corect in: " << timp6 / 1e9 << "\n";
    }
    return 0;
}

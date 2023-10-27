#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

void stworz_dane() {
    ofstream fout("dane.txt");
    for (int i = 1; i <= 10; i++) {
        int a = rand() % 99 + 1;
        fout << a << ";";
    }
    fout.close();
}

void min_max(double Tab[], int n_elementow) {
    int biezaca_wartosc_min, biezaca_wartosc_max, idx;
    if (Tab[0] > Tab[1]) {
        biezaca_wartosc_min = Tab[1];
        biezaca_wartosc_max = Tab[0];
    } else {
        biezaca_wartosc_min = Tab[0];
        biezaca_wartosc_max = Tab[1];
    }
    for (idx = 2; idx < n_elementow - 1; idx += 2) {
        if (Tab[idx] > Tab[idx + 1]) {
            if (Tab[idx] > biezaca_wartosc_max) {
                biezaca_wartosc_max = Tab[idx];
            }
            if (Tab[idx + 1] < biezaca_wartosc_min) {
                biezaca_wartosc_min = Tab[idx + 1];
            }
        } else {
            if (Tab[idx + 1] > biezaca_wartosc_max) {
                biezaca_wartosc_max = Tab[idx + 1];
            }
            if (Tab[idx] < biezaca_wartosc_min) {
                biezaca_wartosc_min = Tab[idx];
            }
        }
    }
    cout << "Max: " << biezaca_wartosc_max << " Min: " << biezaca_wartosc_min << endl;
}

void polaczZbiory(int poczatkowy, int srodkowy, int ostatni, double Tab[], int n_elementow) {
    int Tab_pom[n_elementow];
    int idx, jdx, qdx;
    for (idx = poczatkowy; idx <= ostatni; idx++) {
        Tab_pom[idx] = Tab[idx];
    }
    idx = poczatkowy;
    jdx = srodkowy + 1;
    qdx = poczatkowy;
    while (idx <= srodkowy && jdx <= ostatni) {
        if (Tab_pom[idx] < Tab_pom[jdx]) {
            Tab[qdx++] = Tab_pom[idx++];
        } else {
            Tab[qdx++] = Tab_pom[jdx++];
        }
    }
    while (idx <= srodkowy) {
        Tab[qdx++] = Tab_pom[idx++];
    }
}

void sortujPrzezScalanie(int poczatkowy, int ostatni, double Tab[], int n_elementow) {
    int srodkowy;
    cout << "\n poczatkowy: " << Tab[poczatkowy] << " ostatni: " << Tab[ostatni] << "\n" << endl;
    if (poczatkowy < ostatni) {
        srodkowy = static_cast<int>((poczatkowy + ostatni) / 2);
        cout << "srodkowy: " << Tab[srodkowy] << endl;
        sortujPrzezScalanie(poczatkowy, srodkowy, Tab, n_elementow);
        sortujPrzezScalanie(srodkowy + 1, ostatni, Tab, n_elementow);
        polaczZbiory(poczatkowy, srodkowy, ostatni, Tab, n_elementow);
    }
}

void quick_sort(double Tab[], int n_elementow, int lewy, int prawy) {
    if (prawy <= lewy) return;

    int i = lewy - 1, j = prawy + 1,
        pivot = Tab[static_cast<int>((lewy + prawy) / 2)]; // wybieramy punkt odniesienia
    while (1) {
        // szukam elementu wiekszego lub rownego piwot stojacego
        // po prawej stronie wartosci pivot
        while (pivot > Tab[++i]);
        // szukam elementu mniejszego lub rowego pivot stojacego
        // po lewej stronie wartosci pivot
        while (pivot < Tab[--j]);
        // jesli liczniki sie nie minely to zamien elementy ze soba
        // stojace po niewlasciwej stronie elementu pivot
        if (i <= j)
            // funkcja swap zamienia wartosciami tab[i] z tab[j]
            swap(Tab[i], Tab[j]);
        else
            break;
    }

    if (j > lewy) {
        quick_sort(Tab, n_elementow, lewy, j);
    }
    if (i < prawy) {
        quick_sort(Tab, n_elementow, i, prawy);
    }
}

int main() {
    srand(time(nullptr));
    stworz_dane();
    ifstream plik;

    // wczytaj ilosc
    plik.open("dane.txt");
    double liczba;
    int licznik = 0;
    string liczba_napis;
    while (!plik.eof()) {
        getline(plik, liczba_napis, ';');
        cout << liczba_napis << endl;
        licznik++;
    }
    plik.close();

    // wczytaj dane do tablicy
    plik.open("dane.txt");
    double* Tab;
    int n_elementow = licznik;
    Tab = new double[n_elementow];
    int i = 0;
    while (!plik.eof()) {
        getline(plik, liczba_napis, ';');
        stringstream ss;
        ss << liczba_napis;
        ss >> Tab[i];
        i++;
    }
    plik.close();

    min_max(Tab, n_elementow);
    cout << "Quick sort" << endl;
    cout << "Zbior przed sortowaniem:\n";
    for (int idx = 0; idx < n_elementow - 1; idx++) {
        cout << Tab[idx] << " ";
    }
    quick_sort(Tab, n_elementow, 0, n_elementow - 2);
    cout << "\n Zbior po sortowaniu: \n";
    for (int idx = 0; idx < n_elementow - 1; idx++) {
        cout << Tab[idx] << " ";
    }
    delete[] Tab;
    return 0;
}

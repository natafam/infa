#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

void generuj_dane() {
    ofstream fout("dane.txt");
    for (int i = 1; i <= 10; i++) {
        double a = (rand() % 99 + 1) / static_cast<double>(RAND_MAX);
        fout << a << ";";
    }
    fout.close();
}

void znajdz_min_max(double Tab[], int liczba_elementow) {
    if (liczba_elementow <= 0) {
        cout << "Brak danych do analizy." << endl;
        return;
    }

    double biezaca_wartosc_min = Tab[0], biezaca_wartosc_max = Tab[0];
    for (int idx = 1; idx < liczba_elementow; idx++) {
        if (Tab[idx] < biezaca_wartosc_min) {
            biezaca_wartosc_min = Tab[idx];
        }
        if (Tab[idx] > biezaca_wartosc_max) {
            biezaca_wartosc_max = Tab[idx];
        }
    }
    cout << "Maksymalna wartoœæ: " << biezaca_wartosc_max << " Minimalna wartoœæ: " << biezaca_wartosc_min << endl;
}

void scal_tablice(int poczatek, int srodek, int koniec, double Tab[], int liczba_elementow) {
    double* Tab_temp = new double[liczba_elementow];
    for (int idx = poczatek; idx <= koniec; idx++) {
        Tab_temp[idx] = Tab[idx];
    }
    int idx = poczatek, jdx = srodek + 1, qdx = poczatek;
    while (idx <= srodek && jdx <= koniec) {
        if (Tab_temp[idx] < Tab_temp[jdx]) {
            Tab[qdx++] = Tab_temp[idx++];
        } else {
            Tab[qdx++] = Tab_temp[jdx++];
        }
    }
    while (idx <= srodek) {
        Tab[qdx++] = Tab_temp[idx++];
    }
    while (jdx <= koniec) {
        Tab[qdx++] = Tab_temp[jdx++];
    }
    delete[] Tab_temp;
}

void sortuj_przez_scalanie(int poczatek, int koniec, double Tab[], int liczba_elementow) {
    if (poczatek < koniec) {
        int srodek = (poczatek + koniec) / 2;
        sortuj_przez_scalanie(poczatek, srodek, Tab, liczba_elementow);
        sortuj_przez_scalanie(srodek + 1, koniec, Tab, liczba_elementow);
        scal_tablice(poczatek, srodek, koniec, Tab, liczba_elementow);
    }
}

void szybkie_sortowanie(double Tab[], int liczba_elementow, int lewa, int prawa) {
    if (lewa < prawa) {
        int i = lewa - 1, j = prawa + 1;
        double pivot = Tab[(lewa + prawa) / 2];

        while (1) {
            while (Tab[++i] < pivot);
            while (Tab[--j] > pivot);
            if (i <= j) {
                swap(Tab[i], Tab[j]);
                i++;
                j--;
            } else {
                break;
            }
        }

        if (j > lewa) {
            szybkie_sortowanie(Tab, liczba_elementow, lewa, j);
        }
        if (i < prawa) {
            szybkie_sortowanie(Tab, liczba_elementow, i, prawa);
        }
    }
}

int main() {
    srand(time(nullptr));
    generuj_dane();
    ifstream plik;

    plik.open("dane.txt");
    int licznik = 0;
    string liczba_napis;
    while (getline(plik, liczba_napis, ';')) {
        licznik++;
    }
    plik.close();

    plik.open("dane.txt");
    double* Tab;
    int liczba_elementow = licznik;
    Tab = new double[liczba_elementow];
    int i = 0;
    while (getline(plik, liczba_napis, ';')) {
        stringstream ss;
        ss << liczba_napis;
        ss >> Tab[i];
        i++;
    }
    plik.close();

    znajdz_min_max(Tab, liczba_elementow);

    cout << "Sortowanie przez scalanie" << endl;
    cout << "Zbiór przed sortowaniem:\n";
    for (int idx = 0; idx < liczba_elementow; idx++) {
        cout << Tab[idx] << " ";
    }
    sortuj_przez_scalanie(0, liczba_elementow - 1, Tab, liczba_elementow);
    cout << "\nZbiór po sortowaniu: \n";
    for (int idx = 0; idx < liczba_elementow; idx++) {
        cout << Tab[idx] << " ";
    }

    cout << "\nSzybkie sortowanie" << endl;
    cout << "Zbiór przed sortowaniem:\n";
    for (int idx = 0; idx < liczba_elementow; idx++) {
        cout << Tab[idx] << " ";
    }
    szybkie_sortowanie(Tab, liczba_elementow, 0, liczba_elementow - 1);
    cout << "\nZbiór po sortowaniu: \n";
    for (int idx = 0; idx < liczba_elementow; idx++) {
        cout << Tab[idx] << " ";
    }

    delete[] Tab;
    return 0;
}

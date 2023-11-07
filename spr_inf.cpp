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



// --------------------------------------------------

// Poprawka

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

void stworz_dane() {
    ofstream fout("dane.txt");
    for (int i = 0; i < 10; i++) {  // Poprawiony zakres i zamknięcie linii
        int a = rand() % 99 + 1;
        fout << a;
        if (i < 9) fout << ";";  // Dodanie średnika, chyba że to ostatnia liczba
    }
    fout.close();
}

void min_max(double Tab[], int n_elementow) {
    int biezaca_wartosc_min = Tab[0], biezaca_wartosc_max = Tab[0];
    for (int idx = 0; idx < n_elementow; idx++) {
        if (Tab[idx] < biezaca_wartosc_min) {
            biezaca_wartosc_min = Tab[idx];
        }
        if (Tab[idx] > biezaca_wartosc_max) {
            biezaca_wartosc_max = Tab[idx];
        }
    }
    cout << "Max: " << biezaca_wartosc_max << " Min: " << biezaca_wartosc_min << endl;
}

void polaczZbiory(int poczatkowy, int srodkowy, int ostatni, double Tab[], int n_elementow) {
    int Tab_pom[n_elementow];
    int idx = poczatkowy, jdx = srodkowy + 1, qdx = poczatkowy;
    while (idx <= srodkowy && jdx <= ostatni) {
        if (Tab[idx] < Tab[jdx]) {
            Tab_pom[qdx++] = Tab[idx++];
        } else {
            Tab_pom[qdx++] = Tab[jdx++];
        }
    }
    while (idx <= srodkowy) {
        Tab_pom[qdx++] = Tab[idx++];
    }
    while (jdx <= ostatni) {
        Tab_pom[qdx++] = Tab[jdx++];
    }
    for (int k = poczatkowy; k <= ostatni; k++) {
        Tab[k] = Tab_pom[k];
    }
}

void sortujPrzezScalanie(int poczatkowy, int ostatni, double Tab[], int n_elementow) {
    if (poczatkowy < ostatni) {
        int srodkowy = (poczatkowy + ostatni) / 2;  // Poprawiony obliczanie środka
        sortujPrzezScalanie(poczatkowy, srodkowy, Tab, n_elementow);
        sortujPrzezScalanie(srodkowy + 1, ostatni, Tab, n_elementow);
        polaczZbiory(poczatkowy, srodkowy, ostatni, Tab, n_elementow);
    }
}

void quick_sort(double Tab[], int lewy, int prawy) {
    if (prawy <= lewy) return;

    int i = lewy, j = prawy;
    double pivot = Tab[(lewy + prawy) / 2];
    while (i <= j) {
        while (Tab[i] < pivot) i++;
        while (Tab[j] > pivot) j--;
        if (i <= j) {
            swap(Tab[i], Tab[j]);
            i++;
            j--;
        }
    }
    quick_sort(Tab, lewy, j);
    quick_sort(Tab, i, prawy);
}

int main() {
    srand(time(nullptr));
    stworz_dane();
    ifstream plik;
    
    plik.open("dane.txt");
    double liczba;
    int licznik = 0;
    string liczba_napis;
    while (getline(plik, liczba_napis, ';')) {  // Poprawiony sposób wczytywania
        stringstream ss(liczba_napis);
        ss >> liczba;
        licznik++;
    }
    plik.close();

    double* Tab;
    int n_elementow = licznik;
    Tab = new double[n_elementow];

    plik.open("dane.txt");
    for (int i = 0; i < n_elementow; i++) {
        getline(plik, liczba_napis, ';');
        stringstream ss(liczba_napis);
        ss >> Tab[i];
    }
    plik.close();

    min_max(Tab, n_elementow);
    
    cout << "Quick sort" << endl;
    cout << "Zbior przed sortowaniem:\n";
    for (int idx = 0; idx < n_elementow; idx++) {
        cout << Tab[idx] << " ";
    }

    quick_sort(Tab, 0, n_elementow - 1);

    cout << "\nZbior po sortowaniu: \n";
    for (int idx = 0; idx < n_elementow; idx++) {
        cout << Tab[idx] << " ";
    }
    delete[] Tab;
    return 0;
}



// --------------------------------------------------

// Poprawka v2

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
using namespace std;

void stworz_dane() {
    ofstream fout("dane.txt");
    for (int i = 0; i < 10; i++) {
        int a = rand() % 99 + 1;
        fout << a;
        if (i < 9) fout << ";";
    }
    fout.close();
}

void min_max(double Tab[], int n_elementow) {
    if (n_elementow == 0) {
        cout << "Tablica jest pusta." << endl;
        return;
    }
    
    int biezaca_wartosc_min = Tab[0], biezaca_wartosc_max = Tab[0];
    for (int idx = 0; idx < n_elementow; idx++) {
        if (Tab[idx] < biezaca_wartosc_min) {
            biezaca_wartosc_min = Tab[idx];
        }
        if (Tab[idx] > biezaca_wartosc_max) {
            biezaca_wartosc_max = Tab[idx];
        }
    }
    cout << "Max: " << biezaca_wartosc_max << " Min: " << biezaca_wartosc_min << endl;
}

// Pozostała część kodu pozostaje bez zmian



// --------------------------------------------------

// Zmieniony

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm>  // Dodane do poprawy funkcji swap

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
    cout << "Maksymalna wartość: " << biezaca_wartosc_max << " Minimalna wartość: " << biezaca_wartosc_min << endl;
}

void scal_tablice(int poczatek, int srodek, int koniec, double Tab[], int liczba_elementow) {
    int* Tab_temp = new int[liczba_elementow];
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



// --------------------------------------------------

// Zmieniony i poprawiony

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
    cout << "Maksymalna wartość: " << biezaca_wartosc_max << " Minimalna wartość: " << biezaca_wartosc_min << endl;
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


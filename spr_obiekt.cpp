#include <iostream>
#include <string>

using namespace std;

class Osoba {
private:
    string imie;
    string nazwisko;
    string dataUrodzenia;

public:
    Osoba(string imie_, string nazwisko_, string dataUrodzenia_) 
        : imie(imie_), nazwisko(nazwisko_), dataUrodzenia(dataUrodzenia_) {}

    void WypiszInfo() {
        cout << "Imie: " << imie << "\nNazwisko: " << nazwisko << "\nData urodzenia: " << dataUrodzenia << endl;
    }
};

class Student : public Osoba {
private:
    int rok;
    int grupa;
    int nrIndeksu;

public:
    Student(string imie_, string nazwisko_, string dataUrodzenia_, int rok_, int grupa_, int nrIndeksu_)
        : Osoba(imie_, nazwisko_, dataUrodzenia_), rok(rok_), grupa(grupa_), nrIndeksu(nrIndeksu_) {}

    void WypiszInfo() {
        Osoba::WypiszInfo();
        cout << "Rok: " << rok << "\nGrupa: " << grupa << "\nNr indeksu: " << nrIndeksu << endl;
    }
};

class Pilkarz : public Osoba {
private:
    string pozycja;
    string klub;
    int liczbaGoli;

public:
    Pilkarz(string imie_, string nazwisko_, string dataUrodzenia_, string pozycja_, string klub_)
        : Osoba(imie_, nazwisko_, dataUrodzenia_), pozycja(pozycja_), klub(klub_), liczbaGoli(0) {}

    void WypiszInfo() {
        Osoba::WypiszInfo();
        cout << "Pozycja: " << pozycja << "\nKlub: " << klub << "\nLiczba goli: " << liczbaGoli << endl;
    }

    void StrzelGola() {
        liczbaGoli++;
    }
};

class PilkarzNozny : public Pilkarz {
public:
    PilkarzNozny(string imie_, string nazwisko_, string dataUrodzenia_, string pozycja_, string klub_)
        : Pilkarz(imie_, nazwisko_, dataUrodzenia_, pozycja_, klub_) {}

    void StrzelGola() {
        Pilkarz::StrzelGola();
        cout << "Nożny strzelił!" << endl;
    }
};

class PilkarzReczny : public Pilkarz {
public:
    PilkarzReczny(string imie_, string nazwisko_, string dataUrodzenia_, string pozycja_, string klub_)
        : Pilkarz(imie_, nazwisko_, dataUrodzenia_, pozycja_, klub_) {}

    void StrzelGola() {
        Pilkarz::StrzelGola();
        cout << "Ręczny strzelił!" << endl;
    }
};

int main() {
    Osoba osoba("Jan", "Kowalski", "01-01-1990");
    Student student("Anna", "Nowak", "15-05-2000", 2, 101, 12345);
    Pilkarz pilkarz("Robert", "Lewandowski", "21-08-1988", "Napastnik", "Bayern Munich");
    PilkarzNozny nozny("Andrzej", "Kolarz", "10-03-1995", "Rozgrywający", "Handball Club");
    PilkarzReczny reczny("Karol", "Piłkarz", "05-07-1992", "Bramkarz", "Handball Team");

    osoba.WypiszInfo();
    cout << "\n" << endl;

    student.WypiszInfo();
    cout << "\n" << endl;

    pilkarz.WypiszInfo();
    cout << "\n" << endl;

    pilkarz.StrzelGola();
    pilkarz.WypiszInfo();

    cout << "\n" << endl;

    nozny.StrzelGola();
    reczny.StrzelGola();

    return 0;
}
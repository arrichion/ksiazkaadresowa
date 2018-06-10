#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct Osoba {
    string imie, nazwisko, adres;
    int id;
};

void odczytZPliku(Osoba* osoby, int &liczbaOsob) {
    fstream plik;
    string linia;
    int nrLinii=1;

    plik.open("ksiazka.txt", ios::in);

    if(plik.good()) {
        while (getline(plik, linia)) {
            switch (nrLinii) {
            case 1:
                osoby[liczbaOsob].id=atoi(linia.c_str());
                break;
            case 2:
                osoby[liczbaOsob].imie=linia;
                break;
            case 3:
                osoby[liczbaOsob].nazwisko=linia;
                break;
            case 4:
                osoby[liczbaOsob].adres=linia;
                break;

            }
            if(nrLinii==4) {
                nrLinii=0;
                ++liczbaOsob;
            }
            ++nrLinii;
        }
    }
    plik.close();
}

void wyswietlOsobe(Osoba* osoby, int nrOsoby) {
    cout<<osoby[nrOsoby].imie<<" "<<osoby[nrOsoby].nazwisko<<endl;
    cout<<osoby[nrOsoby].adres<<endl;
    cout<<"ID: "<<osoby[nrOsoby].id<<endl<<endl;
}

void wprowadzDane(Osoba* osoby, int &liczbaOsob) {
    fstream plik;

    cin.sync();

    cout<<"Podaj imie: ";
    getline(cin, osoby[liczbaOsob].imie);
    cout<<"Podaj nazwisko: ";
    getline(cin, osoby[liczbaOsob].nazwisko);
    cout<<"Podaj adres: ";
    getline(cin, osoby[liczbaOsob].adres);
    osoby[liczbaOsob].id=liczbaOsob+1;

    plik.open("ksiazka.txt",ios::out | ios::app);

    plik<<osoby[liczbaOsob].id<<endl;
    plik<<osoby[liczbaOsob].imie<<endl;
    plik<<osoby[liczbaOsob].nazwisko<<endl;
    plik<<osoby[liczbaOsob].adres<<endl;

    plik.close();

    ++liczbaOsob;
}

void wyszukajPoImieniu(Osoba* osoby, int liczbaOsob) {
    string imie;
    bool znalezionoOsobeWKsiazce = false;

    cout<<"Podaj szukane imie: ";
    cin>>imie;
    cout<<endl;
    for(int i=0; i<liczbaOsob; ++i)
        if(osoby[i].imie==imie) {
            wyswietlOsobe(osoby, i);
            znalezionoOsobeWKsiazce=true;
        }
    if(znalezionoOsobeWKsiazce==false)
        cout<<endl<<"Brak osob o tym imieniu.";
}

void wyszukajPoNazwisku(Osoba* osoby, int liczbaOsob) {
    string nazwisko;
    bool znalezionoOsobeWKsiazce = false;

    cout<<"Podaj szukane nazwisko: ";
    cin>>nazwisko;
    cout<<endl;
    for(int i=0; i<liczbaOsob; ++i)
        if(osoby[i].nazwisko==nazwisko) {
            wyswietlOsobe(osoby, i);
            znalezionoOsobeWKsiazce=true;
        }
    if(znalezionoOsobeWKsiazce==false)
        cout<<endl<<"Brak osob o tym imieniu.";
}

void wyswietlListeOsob(Osoba* osoby, int liczbaOsob) {
    for(int i=0; i<liczbaOsob; ++i)
        wyswietlOsobe(osoby, i);
}

int main() {
    char wybor;
    int liczbaOsob=0;
    Osoba *osoby = new Osoba[50];

    odczytZPliku(osoby, liczbaOsob);

    while(1) {
        cout<<"-----KSIAZKA ADRESOWA------"<<endl<<endl;
        cout<<"1. Wprowadz dane osoby."<<endl;
        cout<<"2. Wyszukaj osobe po imieniu."<<endl;
        cout<<"3. Wyszukaj osobe po nazwisku."<<endl;
        cout<<"4. Wyswietl wszystkie osoby z ksiazki."<<endl;
        cout<<"0. Wyjdz z programu."<<endl;

        wybor=getch();
        cout<<endl;

        switch(wybor) {
        case '1':
            wprowadzDane(osoby, liczbaOsob);
            break;
        case '2':
            wyszukajPoImieniu(osoby, liczbaOsob);
            getch();
            break;
        case '3':
            wyszukajPoNazwisku(osoby, liczbaOsob);
            getch();
            break;
        case '4':
            wyswietlListeOsob(osoby, liczbaOsob);
            getch();
            break;
        case '0':
            cout<<"Zegnaj :(";
            Sleep(1000);
            exit(0);
            break;
        default:
            cout<<"Nie ma takiej opcji.";
            Sleep(1000);
            break;
        }
        system("cls");
    }

    delete[] osoby;
}

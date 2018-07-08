#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct Osoba {
    string imie="", nazwisko="", adres="";
    int id=0;
};

void wyswietlOsobe(vector<Osoba> &osoby, int nrOsoby) {
    cout<<osoby[nrOsoby].imie<<" "<<osoby[nrOsoby].nazwisko<<endl;
    cout<<osoby[nrOsoby].adres<<endl;
    cout<<"ID: "<<osoby[nrOsoby].id<<endl<<endl;
}

void odczytZPliku(vector<Osoba> &osoby, int &liczbaOsob) {
    fstream plik;
    string linia ,nrIDstr;
    char znak;
    int nrDanej=1;
    Osoba odczytanaOsoba;

    plik.open("ksiazka.txt", ios::in);

    if(plik.good()) {
        while (getline(plik, linia)) {
            osoby.push_back(odczytanaOsoba);
            znak=' ';
            for(int i=0; znak!='|' || nrDanej!=1; ++i) {
                znak=linia[i];
                if(znak=='|')
                    nrDanej+=1;
                else {
                    switch (nrDanej) {
                    case 1:
                        nrIDstr+=znak;
                        if(linia[i+1]=='|'){
                            osoby[liczbaOsob].id=atoi(nrIDstr.c_str());
                            nrIDstr="";
                        }
                        break;
                    case 2:
                        osoby[liczbaOsob].imie+=znak;
                        break;
                    case 3:
                        osoby[liczbaOsob].nazwisko+=znak;
                        break;
                    case 4:
                        osoby[liczbaOsob].adres+=znak;
                        break;
                    }
                }
                if(nrDanej==5) {
                    nrDanej=1;
                    ++liczbaOsob;
                }
            }
        }
    }
    plik.close();
}

void zapisDoPliku(vector<Osoba> &osoby, int liczbaOsob) {
    fstream plik;

    plik.open("ksiazka.txt",ios::out);

    for(int i=0; i<liczbaOsob; ++i){
        plik<<osoby[i].id<<"|";
        plik<<osoby[i].imie<<"|";
        plik<<osoby[i].nazwisko<<"|";
        plik<<osoby[i].adres<<"|"<<endl;
    }

    plik.close();
}

void wprowadzDane(vector<Osoba> &osoby, int &liczbaOsob) {
    fstream plik;
    Osoba dodawanaOsoba;

    cin.clear();
    cin.sync();

    cout<<"Podaj imie: ";
    getline(cin, dodawanaOsoba.imie);
    cout<<"Podaj nazwisko: ";
    getline(cin, dodawanaOsoba.nazwisko);
    cout<<"Podaj adres: ";
    getline(cin, dodawanaOsoba.adres);
    if(liczbaOsob==0)
        dodawanaOsoba.id=1;
    else
        dodawanaOsoba.id=osoby[liczbaOsob-1].id+1;

    osoby.push_back(dodawanaOsoba);

    plik.open("ksiazka.txt",ios::out | ios::app);

    plik<<osoby[liczbaOsob].id<<"|";
    plik<<osoby[liczbaOsob].imie<<"|";
    plik<<osoby[liczbaOsob].nazwisko<<"|";
    plik<<osoby[liczbaOsob].adres<<"|"<<endl;

    plik.close();

    ++liczbaOsob;
}

void wyszukajPoImieniu(vector<Osoba> &osoby, int liczbaOsob) {
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

void wyszukajPoNazwisku(vector<Osoba> &osoby, int liczbaOsob) {
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
        cout<<endl<<"Brak osob o tym nazwisku.";
}

void wyswietlListeOsob(vector<Osoba> &osoby, int liczbaOsob) {
    if(liczbaOsob==0)
        cout<<"W ksiazce nie ma aktualnie zadnych zapisanych osob.";
    else
        for(int i=0; i<liczbaOsob; ++i)
            wyswietlOsobe(osoby, i);
}

void usunOsobe(vector<Osoba> &osoby, int &liczbaOsob) {
    int nrID;
    char wybor;
    bool znalezionoOsobe = false;
    vector <Osoba>::iterator itr;

    cout<<"Podaj nr ID osoby, ktora chcesz usunac: ";
    cin>>nrID;

    for(int i=0; i<liczbaOsob; ++i)
        if(osoby[i].id==nrID) {
            znalezionoOsobe = true;
            itr = osoby.begin()+i;
            cout<<"Czy na pewno chcesz usunac "<<osoby[i].imie<<" "<<osoby[i].nazwisko<<"? (t/n)";
            wybor=getch();
            switch(wybor) {
            case 't':
                cout<<endl<<"Usunieto "<<osoby[i].imie<<" "<<osoby[i].nazwisko<<" z ksiazki.";
                osoby.erase(itr);
                --liczbaOsob;
                osoby.resize(liczbaOsob);
                zapisDoPliku(osoby, liczbaOsob);
                break;
            case 'n':
                cout<<endl<<osoby[i].imie<<" "<<osoby[i].nazwisko<<" pozostal w ksiazce.";
                break;
            }
        }
    if(znalezionoOsobe==false)
        cout<<"Nie ma w ksiazce osoby o podanym ID.";
}

void edytujOsobe (vector<Osoba> &osoby, int &liczbaOsob) {
    int nrID;
    char wybor;
    string imie;
    bool znalezionoOsobe = false;

    cout<<"Podaj nr ID osoby, ktora chcesz edytowac: ";
    cin>>nrID;

    for(int i=0; i<liczbaOsob; ++i) {
        if(osoby[i].id==nrID) {
            znalezionoOsobe = true;
            cout<<endl<<osoby[i].imie<<" "<<osoby[i].nazwisko<<endl;
            cout<<osoby[i].adres<<endl;

            cout<<endl;
            cout<<"1. Edytuj imie."<<endl;
            cout<<"2. Edytuj nazwisko."<<endl;
            cout<<"3. Edytuj adres."<<endl;

            wybor = getch();
            cout<<endl;

            cin.clear();
            cin.sync();
            switch(wybor) {
            case '1':
                cout<<"Podaj nowe imie: ";
                getline(cin, osoby[i].imie);
                break;
            case '2':
                cout<<"Podaj nowe nazwisko: ";
                getline(cin, osoby[i].nazwisko);
                break;
            case '3':
                cout<<"Podaj nowy adres: ";
                getline(cin, osoby[i].adres);
                break;
            }
            zapisDoPliku(osoby, liczbaOsob);
        }
    }
    if(znalezionoOsobe==false)
        cout<<"Nie ma w ksiazce osoby o podanym ID.";
}

int main() {
    char wybor;
    int liczbaOsob=0;
    vector<Osoba> osoby;

    odczytZPliku(osoby, liczbaOsob);

    while(1) {
        cout<<"-----KSIAZKA ADRESOWA------"<<endl<<endl;
        cout<<"1. Wprowadz dane osoby."<<endl;
        cout<<"2. Wyszukaj osobe po imieniu."<<endl;
        cout<<"3. Wyszukaj osobe po nazwisku."<<endl;
        cout<<"4. Wyswietl wszystkie osoby z ksiazki."<<endl;
        cout<<"5. Usun osobe."<<endl;
        cout<<"6. Edytuj osobe."<<endl;
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
        case '5':
            usunOsobe(osoby, liczbaOsob);
            getch();
            break;
        case '6':
            edytujOsobe(osoby, liczbaOsob);
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
    return 0;
}


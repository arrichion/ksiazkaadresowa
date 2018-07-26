#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct Uzytkownik {
    string nazwa="", haslo="";
    int id=0;
};

struct Osoba {
    string imie="", nazwisko="", adres="";
    int id=0, idUzytkownika=0;
};

void odczytZPlikuUzytkownicy(vector<Uzytkownik> &uzytkownicy, int &liczbaUzytkownikow) {
    fstream plik;
    string linia, nrIDstr;
    char znak;
    int nrDanej=1;
    Uzytkownik odczytanyUzytkownik;

    plik.open("uzytkownicy.txt", ios::in);

    if(plik.good()) {
        while (getline(plik, linia)) {
            uzytkownicy.push_back(odczytanyUzytkownik);
            znak=' ';
            for(int i=0; znak!='|' || nrDanej!=1; ++i) {
                znak=linia[i];
                if(znak=='|')
                    nrDanej+=1;
                else {
                    switch (nrDanej) {
                    case 1:
                        nrIDstr+=znak;
                        if(linia[i+1]=='|') {
                            uzytkownicy[liczbaUzytkownikow].id=atoi(nrIDstr.c_str());
                            nrIDstr="";
                        }
                        break;
                    case 2:
                        uzytkownicy[liczbaUzytkownikow].nazwa+=znak;
                        break;
                    case 3:
                        uzytkownicy[liczbaUzytkownikow].haslo+=znak;
                        break;
                    }
                }
                if(nrDanej==4) {
                    nrDanej=1;
                    ++liczbaUzytkownikow;
                }
            }
        }
    }
    plik.close();
}

void logowanie(vector<Uzytkownik> uzytkownicy, int liczbaUzytkownikow, bool &zalogowano, int &idZalogowanego) {
    string nazwa, haslo;
    bool znalezionoUzytkownika=false;

    cout<<"Podaj nazwe: ";
    cin>>nazwa;
    cout<<"Podaj haslo: ";
    cin>>haslo;
    cout<<endl;
    for(int i=0; i<liczbaUzytkownikow; ++i)
        if(uzytkownicy[i].nazwa==nazwa) {
            znalezionoUzytkownika=true;
            idZalogowanego=uzytkownicy[i].id;
            if(uzytkownicy[i].haslo==haslo) {
                zalogowano=true;
                cout<<"Zalogowano";
            } else
                cout<<"Bledne haslo";
            Sleep(1000);
        }
    if(znalezionoUzytkownika==false) {
        cout<<endl<<"Nie ma takiego uzytkownika.";
        Sleep(1000);
    }
}

void wprowadzDaneUzytkownika(vector<Uzytkownik> &uzytkownicy, int &liczbaUzytkownikow) {
    fstream plik;
    Uzytkownik dodawanyUzytkownik;
    bool powtorzonaNazwa=false;

    cin.clear();
    cin.sync();

    cout<<"Utworz nazwe: ";
    getline(cin, dodawanyUzytkownik.nazwa);
    for(int i=0; i<liczbaUzytkownikow; ++i) {
        if(dodawanyUzytkownik.nazwa==uzytkownicy[i].nazwa) {
            powtorzonaNazwa=true;
            cout<<"Podana nazwa uzytkownika jest juz zajeta.";
        }
    }
    if(!powtorzonaNazwa) {
        cout<<"Utworz haslo: ";
        getline(cin, dodawanyUzytkownik.haslo);
        if(liczbaUzytkownikow==0)
            dodawanyUzytkownik.id=1;
        else
            dodawanyUzytkownik.id=uzytkownicy[liczbaUzytkownikow-1].id+1;

        uzytkownicy.push_back(dodawanyUzytkownik);

        plik.open("uzytkownicy.txt",ios::out | ios::app);

        plik<<uzytkownicy[liczbaUzytkownikow].id<<"|";
        plik<<uzytkownicy[liczbaUzytkownikow].nazwa<<"|";
        plik<<uzytkownicy[liczbaUzytkownikow].haslo<<"|"<<endl;

        plik.close();

        ++liczbaUzytkownikow;
    }
}

void zapisDoPlikuUzytkownicy(vector<Uzytkownik> uzytkownicy, int liczbaUzytkownikow) {
    fstream plik;

    plik.open("uzytkownicy.txt",ios::out);

    for(int i=0; i<liczbaUzytkownikow; ++i) {
        plik<<uzytkownicy[i].id<<"|";
        plik<<uzytkownicy[i].nazwa<<"|";
        plik<<uzytkownicy[i].haslo<<"|"<<endl;
    }

    plik.close();
}

void zmienHaslo(vector<Uzytkownik> &uzytkownicy, int idZalogowanego, int liczbaUzytkownikow) {
    string noweHaslo="";

    cout<<"Podaj nowe haslo: ";
    cin>>noweHaslo;
    for(int i=0; i<liczbaUzytkownikow; ++i)
        if(uzytkownicy[i].id==idZalogowanego) {
            uzytkownicy[i].haslo=noweHaslo;
            break;
        }
    zapisDoPlikuUzytkownicy(uzytkownicy, liczbaUzytkownikow);
    cout<<endl<<"Haslo zostalo zmienione";
    Sleep(1000);
}

void wyswietlOsobe(vector<Osoba> &osoby, int nrOsoby) {
    cout<<osoby[nrOsoby].imie<<" "<<osoby[nrOsoby].nazwisko<<endl;
    cout<<osoby[nrOsoby].adres<<endl;
    cout<<"ID: "<<osoby[nrOsoby].id<<endl<<endl;
}

void odczytZPlikuKsiazka(vector<Osoba> &osoby, int &liczbaOsob, int idZalogowanego) {
    fstream plik;
    string linia,nrIDstr;
    char znak;
    int nrDanej=0;
    Osoba odczytanaOsoba;

    plik.open("ksiazka.txt", ios::in);

    if(plik.good()) {
        while (getline(plik, linia)) {
            znak=' ';
            for(int i=0; znak!='|' || nrDanej!=0; ++i) {
                znak=linia[i];
                if(znak=='|')
                    nrDanej+=1;
                else {
                    switch (nrDanej) {
                    case 0:
                        nrIDstr+=znak;
                        if(linia[i+1]=='|') {
                            odczytanaOsoba.id=atoi(nrIDstr.c_str());
                            nrIDstr="";
                        }
                        break;
                    case 1:
                        nrIDstr+=znak;
                        if(linia[i+1]=='|') {
                            odczytanaOsoba.idUzytkownika=atoi(nrIDstr.c_str());
                            nrIDstr="";
                        }
                        break;
                    case 2:
                        odczytanaOsoba.imie+=znak;
                        break;
                    case 3:
                        odczytanaOsoba.nazwisko+=znak;
                        break;
                    case 4:
                        odczytanaOsoba.adres+=znak;
                        break;
                    }
                }
                if(nrDanej==5) {
                    if(odczytanaOsoba.idUzytkownika==idZalogowanego){
                        osoby.push_back(odczytanaOsoba);
                        ++liczbaOsob;
                    }
                    odczytanaOsoba.imie="";
                    odczytanaOsoba.nazwisko="";
                    odczytanaOsoba.adres="";
                    nrDanej=0;
                }
            }
        }
    }
    plik.close();
}

void zapisDoPlikuKsiazka(vector<Osoba> osoby, int liczbaOsob, int nrID, char funkcja) {
    fstream plik;
    ofstream plikTymczasowy("ksiazkaTymczasowa.txt");
    int nrIDpobieranyZPliku;
    string nrIDpobieranyZPlikuStr, linia;

    plik.open("ksiazka.txt",ios::in);

    if(plik.good()) {
        while (getline(plik, linia)) {
                for(int i=0; linia[i]!='|'; ++i)
                        nrIDpobieranyZPlikuStr+=linia[i];
                nrIDpobieranyZPliku = atoi(nrIDpobieranyZPlikuStr.c_str());
                nrIDpobieranyZPlikuStr="";
                getch();
                if(nrIDpobieranyZPliku == nrID){
                    switch(funkcja){
                    case 'e':
                        for(int i=0; i<liczbaOsob; ++i)
                            if(osoby[i].id==nrID){
                                plikTymczasowy<<osoby[i].id<<"|";
                                plikTymczasowy<<osoby[i].idUzytkownika<<"|";
                                plikTymczasowy<<osoby[i].imie<<"|";
                                plikTymczasowy<<osoby[i].nazwisko<<"|";
                                plikTymczasowy<<osoby[i].adres<<"|"<<endl;
                                break;
                            }
                        break;
                    case 'u':
                        break;
                    }
                }
                else
                    plikTymczasowy<<linia<<endl;
        }
    }

    plik.close();
    remove("ksiazka.txt");
    plikTymczasowy.close();
    rename("ksiazkaTymczasowa.txt", "ksiazka.txt");
}

void wprowadzDane(vector<Osoba> &osoby, int &liczbaOsob, int idZalogowanego) {
    fstream plik;
    Osoba dodawanaOsoba;

    cin.clear();
    cin.sync();

    dodawanaOsoba.idUzytkownika=idZalogowanego;
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
    plik<<osoby[liczbaOsob].idUzytkownika<<"|";
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
                zapisDoPlikuKsiazka(osoby, liczbaOsob, nrID, 'u');
                break;
            case 'n':
                cout<<endl<<osoby[i].imie<<" "<<osoby[i].nazwisko<<" pozostal w ksiazce.";
                break;
            }
            break;
        }
    if(znalezionoOsobe==false)
        cout<<"Nie ma w ksiazce osoby o podanym ID.";
        Sleep(1000);
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
            zapisDoPlikuKsiazka(osoby, liczbaOsob, nrID, 'e');
            break;
        }
    }
    if(znalezionoOsobe==false)
        cout<<"Nie ma w ksiazce osoby o podanym ID.";
        Sleep(1000);
}

int main() {
    char wybor;
    int liczbaOsob=0, liczbaUzytkownikow=0, idZalogowanego=0;
    vector<Osoba> osoby;
    vector<Uzytkownik> uzytkownicy;
    bool zalogowano = false;

    odczytZPlikuUzytkownicy(uzytkownicy, liczbaUzytkownikow);

    while(!zalogowano) {
        cout<<"-----KSIAZKA ADRESOWA------"<<endl<<endl;
        cout<<"1. Logowanie."<<endl;
        cout<<"2. Rejestracja."<<endl;
        cout<<"0. Wyjdz z programu."<<endl;

        wybor=getch();
        cout<<endl;

        switch(wybor) {
        case '1':
            logowanie(uzytkownicy, liczbaUzytkownikow, zalogowano, idZalogowanego);
            odczytZPlikuKsiazka(osoby, liczbaOsob, idZalogowanego);
            while(zalogowano) {
                system("cls");
                cout<<"-----KSIAZKA ADRESOWA------"<<endl<<endl;
                cout<<"1. Wprowadz dane osoby."<<endl;
                cout<<"2. Wyszukaj osobe po imieniu."<<endl;
                cout<<"3. Wyszukaj osobe po nazwisku."<<endl;
                cout<<"4. Wyswietl wszystkie osoby z ksiazki."<<endl;
                cout<<"5. Usun osobe."<<endl;
                cout<<"6. Edytuj osobe."<<endl;
                cout<<"7. Zmien haslo."<<endl;
                cout<<"0. Wyloguj sie."<<endl;

                wybor=getch();
                cout<<endl;

                switch(wybor) {
                case '1':
                    wprowadzDane(osoby, liczbaOsob, idZalogowanego);
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
                    break;
                case '6':
                    edytujOsobe(osoby, liczbaOsob);
                    break;
                case '7':
                    zmienHaslo(uzytkownicy, idZalogowanego, liczbaUzytkownikow);
                    break;
                case '0':
                    zalogowano=false;
                    osoby.clear();
                    liczbaOsob=0;
                    cout<<"Wylogowano";
                    Sleep(1000);
                    break;
                default:
                    cout<<"Nie ma takiej opcji.";
                    Sleep(1000);
                    break;
                }
                system("cls");
            }
            break;
        case '2':
            wprowadzDaneUzytkownika(uzytkownicy, liczbaUzytkownikow);
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

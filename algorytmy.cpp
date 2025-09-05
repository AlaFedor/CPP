#include <iostream>
#include <limits>
#include <cmath>
#include <iomanip>
using namespace std;

double Horner(double wspolczynniki[], int stopien, double x)
{
    double wynik = wspolczynniki[stopien];
    for (int i = stopien - 1; i >= 0; i--)
    {
        wynik = wynik * x + wspolczynniki[i];
    }
    return wynik;
}

void odczytajWielomian(double wielomian[], int &stopien)
{
    while (true)
    {
        cout << "Podaj stopień wielomianu: " << endl;
        cin >> stopien;
        if (cin.fail() || stopien < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podano błędną liczbę. Stopień wielomianu musi być większy od zera! " << endl;
        }
        else
        {
            break;
        }
    }

    cout << "Podaj " << stopien + 1 << " współczynniki oddzielone spacjami: (od najwyższej potęgi do stałej) ";

    for (int i = stopien; i >= 0; i--)
    {
        while (!(cin >> wielomian[i]))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Niepoprawna wartość. Podaj poprawny współczynnik dla x^" << stopien << ": ";
        }
    }
}

void wyswietlWielomian(double wielomian[], int stopien)
{
    bool wielomianZerowy = true;
    for (int i = stopien; i >= 0; i--)
    {
        if (fabs(wielomian[i]) > 0)
        {
            wielomianZerowy = false;
            if (i != stopien && wielomian[i] > 0)
                cout << " + ";
            else if (wielomian[i] < 0)
                cout << " - ";

            if (fabs(wielomian[i]) != 1 || i == 0)
                cout << fabs(wielomian[i]);
            if (i > 0)
                cout << "x";
            if (i > 1)
                cout << "^" << i;
        }
    }
    if (wielomianZerowy)
    {
        cout << "0";
    }
    cout << endl;
}

void dodaj(double wiel1[], int stopien1, double wiel2[], int stopien2, double wynik[], int &stopienwyniku)
{
    stopienwyniku = max(stopien1, stopien2);
    for (int i = 0; i <= stopienwyniku; i++)
    {
        wynik[i] = (i <= stopien1 ? wiel1[i] : 0) + (i <= stopien2 ? wiel2[i] : 0);
    }
}

void odejmij(double wiel1[], int stopien1, double wiel2[], int stopien2, double wynik[], int &stopienwyniku)
{
    stopienwyniku = max(stopien1, stopien2);
    for (int i = 0; i <= stopienwyniku; i++)
    {
        wynik[i] = (i <= stopien1 ? wiel1[i] : 0) - (i <= stopien2 ? wiel2[i] : 0);
    }
}

void mnozenie(double wiel1[], int stopien1, double wiel2[], int stopien2, double wynik[], int &stopienwyniku)
{
    stopienwyniku = stopien1 + stopien2;
    for (int i = 0; i <= stopienwyniku; i++)
        wynik[i] = 0;

    for (int i = 0; i <= stopien1; i++)
    {
        for (int j = 0; j <= stopien2; j++)
        {
            wynik[i + j] += wiel1[i] * wiel2[j];
        }
    }
}

int main()
{
    int opcja, stopien1, stopien2, stopienwyniku;
    double wiel1[100], wiel2[100], wynik[100];

    cout << "Wybierz opcję" << endl;
    cout << "1 Dodawanie" << endl;
    cout << "2 Odejmowanie" << endl;
    cout << "3 Mnożenie" << endl;
    cout << "4 Wartość wielomianu w punkcie" << endl;

    while (true)
    {
        cin >> opcja;
        if (cin.fail() || opcja < 1 || opcja > 4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Podano błędną liczbę. Podaj liczbę od 1 do 4: " << endl;
        }
        else
        {
            break;
        }
    }

    switch (opcja)
    {
    case 1:
        odczytajWielomian(wiel1, stopien1);
        odczytajWielomian(wiel2, stopien2);
        dodaj(wiel1, stopien1, wiel2, stopien2, wynik, stopienwyniku);
        cout << "Suma wielomianów: ";
        wyswietlWielomian(wynik, stopienwyniku);
        break;
    case 2:
        odczytajWielomian(wiel1, stopien1);
        odczytajWielomian(wiel2, stopien2);
        odejmij(wiel1, stopien1, wiel2, stopien2, wynik, stopienwyniku);
        cout << "Różnica wielomianów: ";
        wyswietlWielomian(wynik, stopienwyniku);
        break;
    case 3:
        odczytajWielomian(wiel1, stopien1);
        odczytajWielomian(wiel2, stopien2);
        mnozenie(wiel1, stopien1, wiel2, stopien2, wynik, stopienwyniku);
        cout << "Iloczyn wielomianów: ";
        wyswietlWielomian(wynik, stopienwyniku);
        break;
    case 4:
        odczytajWielomian(wiel1, stopien1);
        double x;
        cout << "Podaj punkt: ";
        cin >> x;
        cout << "Wartość wielomianu w punkcie " << x << " wynosi: " << Horner(wiel1, stopien1, x) << endl;
        break;
    }
    return 0;
}
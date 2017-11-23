/*
 *******************************************************
 ** Przyk³adowa aplikacja obrazuj¹ca sposób dzia³ania **
 ** asymetrycznego systemu kodowania informacji RSA.  **
 ** ------------------------------------------------- **
 **           (C)2012 mgr Jerzy Wa³aszek              **
 **            I Liceum Ogólnokszta³c¹ce              **
 **          im. Kazimierza Brodziñskiego             **
 **                   w Tarnowie                      **
 *******************************************************
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;

// Funkcja czeka na dowolny klawisz i czyœci ekran
//------------------------------------------------
void czekaj(void)
{
  char c[1];

  cout << "\nZapisz te dane\n\n";
  cin.getline(c,1);
  cin.getline(c,1);
  for(int i = 1; i < 500; i++) cout << endl;
}

// Funkcja obliczaj¹ca NWD dla dwóch liczb
//----------------------------------------
int nwd(int a, int b)
{
  int t;

  while(b != 0)
  {
    t = b;
    b = a % b;
    a = t;
  };
  return a;
}

// Funkcja obliczania odwrotnoœci modulo n
//----------------------------------------
int odwr_mod(int a, int n)
{
  int a0,n0,p0,p1,q,r,t;

  p0 = 0; p1 = 1; a0 = a; n0 = n;
  q  = n0 / a0;
  r  = n0 % a0;
  while(r > 0)
  {
    t = p0 - q * p1;
    if(t >= 0)
      t = t % n;
    else
      t = n - ((-t) % n);
    p0 = p1; p1 = t;
    n0 = a0; a0 = r;
    q  = n0 / a0;
    r  = n0 % a0;
  }
  return p1;
}

// Procedura generowania kluczy RSA
//---------------------------------
void klucze_RSA()
{
  const int tp[10] = {11,13,17,19,23,29,31,37,41,43};
  int p,q,phi,n,e,d;

  cout << "Generowanie kluczy RSA\n"
          "----------------------\n\n";

// generujemy dwie ró¿ne, losowe liczby pierwsze

  do
  {
    p = tp[rand() % 10];
    q = tp[rand() % 10];
  } while (p == q);

  phi = (p - 1) * (q - 1);
  n   = p * q;

// wyznaczamy wyk³adniki e i d

  for(e = 3; nwd(e,phi) != 1; e += 2);
  d = odwr_mod(e,phi);

// gotowe, wypisujemy klucze

  cout << "KLUCZ PUBLICZNY\n"
          "wykladnik e = " << e
       << "\n    modul n = " << n
       << "\n\nKLUCZ PRYWATNY\n"
          "wykladnik d = " << d << endl;
  czekaj();
}

// Funkcja oblicza modulo potêgê podanej liczby
//---------------------------------------------
int pot_mod(int a, int w, int n)
{
  int pot,wyn,q;

// wyk³adnik w rozbieramy na sumê potêg 2
// przy pomocy algorytmu Hornera. Dla reszt
// niezerowych tworzymy iloczyn potêg a modulo n.

  pot = a; wyn = 1;
  for(q = w; q > 0; q /= 2)
  {
    if(q % 2) wyn = (wyn * pot) % n;
    pot = (pot * pot) % n; // kolejna potêga
  }
  return wyn;
}

// Procedura kodowania danych RSA
//-------------------------------
void kodowanie_RSA()
{
  int e,n,t;

  cout << "Kodowanie danych RSA\n"
          "--------------------\n\n"
          "Podaj wykladnik = "; cin  >> e;
  cout << "    Podaj modul = "; cin  >> n;
  cout << "----------------------------------\n\n"
          "Podaj kod RSA   = "; cin  >> t;
  cout << "\nWynik kodowania = " << pot_mod(t,e,n) << endl;

  czekaj();
}

// ********************
// ** Program g³ówny **
// ********************

int main()
{
  int w;

  srand((unsigned)time(NULL));

  do
  {
    cout << "System szyfrowania danych RSA\n"
            "-----------------------------\n"
            " (C)2012 mgr Jerzy Walaszek\n\n"
            "MENU\n"
            "====\n"
            "[ 0 ] - Koniec pracy programu\n"
            "[ 1 ] - Generowanie kluczy RSA\n"
            "[ 2 ] - Kodowanie RSA\n\n"
            "Jaki jest twoj wybor? (0, 1 lub 2) : ";
    cin  >> w;
    cout << "\n\n\n";
    switch (w)
    {
      case 1 : klucze_RSA(); break;
      case 2 : kodowanie_RSA(); break;
    }
    cout << "\n\n\n";
  } while(w != 0);

  return 0;
}

// Zbiory zaimplementowane w tablicach dynamicznych
// Data   : 21.06.2014
// (C)2014 mgr Jerzy Wa�aszek
//-------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

// Definicja struktury zbioru

struct s_set
{
    int vmin, nmax;
    char * T;
};
//dodany kod do drugiej ga��zi

// Procedura usuwa wszystkie elementy ze zbioru
//---------------------------------------------
void s_clear(s_set & A)
{
  for(int i = 0; i <= A.nmax; i++) A.T[i] = 0; // Zerujemy tablic�
}

// Procedura tworzy pusty zbi�r
//-----------------------------
void s_create(s_set & A, int vmin, int vmax)
{
  A.vmin = vmin;                  // Wype�niamy struktur� A
  A.nmax = vmax - vmin;
  A.T = new char [A.nmax + 1];    // Tworzymy tablic� dynamiczn� na elementy
  s_clear(A);                     // Zbi�r zerujemy
}

// Procedura oblicza sum� zbior�w A i B.
// Wynik umieszcza w zbiorze C
//--------------------------------------
void s_union(s_set & A, s_set & B, s_set & C)
{
  for(int i = 0; i <= A.nmax; i++) C.T[i] = A.T[i] | B.T[i];
}

// Procedura oblicza iloczyn zbior�w A i B.
// Wynik umieszcza w zbiorze C
//-----------------------------------------
void s_intersection(s_set & A, s_set & B, s_set & C)
{
  for(int i = 0; i <= A.nmax; i++) C.T[i] = A.T[i] & B.T[i];
}

// Procedura oblicza r�nic� zbior�w A i B.
// Wynik umieszcza w zbiorze C
//-----------------------------------------
void s_difference(s_set & A, s_set & B, s_set & C)
{
  for(int i = 0; i <= A.nmax; i++) C.T[i] = A.T[i] & ~ B.T[i];
}

// Procedura oblicza dope�nienie zbioru A.
// Wynik umieszcza w zbiorze C
//----------------------------------------
void s_complement(s_set & A, s_set & C)
{
  for(int i = 0; i <= A.nmax; i++) C.T[i] = 1 & ~ A.T[i];
}

// Funkcja sprawdza, czy zbi�r A jest podzbiorem zbioru B.
// true  - tak
// false - nie
//--------------------------------------------------------
bool s_subset(s_set & A, s_set & B)
{
  for(int i = 0; i <= A.nmax; i++)
    if(A.T[i] && ! B.T[i]) return false;
  return true;
}

// Funkcja oblicza liczb� element�w w zbiorze A
//---------------------------------------------
int s_size(s_set & A)
{
  int s = 0;

  for(int i = 0; i <= A.nmax; i++) s = s + A.T[i];
  return s;
}

// Funkcja sprawdza, czy zbi�r jest pusty.
// true  - tak, zbi�r jest pusty
// false - nie, zbi�r nie jest pusty
//----------------------------------------
bool s_empty(s_set & A)
{
  return !s_size(A);
}

// Procedura dodaje do zbioru element
//-----------------------------------
void s_add(s_set & A, int x)
{
  A.T[x - A.vmin] = 1;
}

// Procedura usuwa ze zbioru element
//----------------------------------
void s_remove(s_set & A, int x)
{
  A.T[x - A.vmin] = 0;
}

// Funkcja bada obecno�� elementu w zbiorze.
// true  - element jest w zbiorze
// false - elementu nie ma w zbiorze
//------------------------------------------
bool s_isin(s_set & A, int x)
{
  return A.T[x - A.vmin];
}

// Procedura wy�wietla zawarto�� zbioru
//-------------------------------------
void s_print(s_set & A)
{
  for(int i = 0; i <= A.nmax; i++)
    if(A.T[i]) cout << setw(3) << i + A.vmin;
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  s_set A,B,C;
  int i,x;

  srand(time(NULL));              // Inicjujemy generator pseudolosowy

  // Tworzymy puste zbiory o zakresie element�w od -5 do 20

  s_create(A,-5,20);
  s_create(B,-5,20);
  s_create(C,-5,20);

  // Do zbioru A dodajemy 10 losowych element�w

  for(i = 0; i < 10; i++) s_add(A,-5 + (rand() % 26));

  // Do zbioru B dodajemy 25 losowych element�w

  for(i = 0; i < 15; i++) s_add(B,-5 + (rand() % 26));

  // Wy�wietlamy je

  cout << "A ="; s_print(A);
  cout << endl << "SIZE OF A IS " << s_size(A) << endl << endl
       << "B ="; s_print(B);
  cout << endl << "SIZE OF B IS " << s_size(B) << endl << endl

  // Suma zbior�w

       << "UNION OF A AND B IS"; s_union(A,B,C); s_print(C);
  cout << endl << "SIZE OF UNION IS " << s_size(C) << endl << endl

  // Iloczyn zbior�w

       << "INTERSECTION OF A AND B IS"; s_intersection(A,B,C); s_print(C);
  cout << endl << "SIZE OF INTERSECTION IS " << s_size(C) << endl << endl

  // R�nica zbior�w

       << "DIFFERENCE OF A AND B IS"; s_difference(A,B,C); s_print(C);
  cout << "SIZE OF DIFFERENCE IS " << s_size(C) << endl << endl

  // Dope�nienie zbioru

       << "COMPLEMENT OF A IS"; s_complement(A,C); s_print(C);
  cout << endl << "SIZE OF COMPLEMENT IS " << s_size(C) << endl << endl;

  // Podzbi�r

  s_union(A,A,C);                 // Kopiujemy A do C
  for(i = 0; i < 7; i++)          // Usuwamy 7 element�w
    s_remove(C,-5 + (rand() % 26));
  cout << "IS"; s_print(C);
  cout << " SUBSET OF A?" << endl;
  if(s_subset(C,A)) cout << "YES"; else cout << "NO";

  s_complement(B,C);
  for(int i = 0; i < 12; i++)     // Usuwamy 12 element�w
    s_remove(C,-5 + (rand() % 26));
  cout << endl << endl << "IS"; s_print(C);
  cout << " SUBSET OF A?" << endl;
  if(s_subset(C,A)) cout << "YES"; else cout << "NO";

  // Usuwanie

  cout << endl << endl << "FROM A WE REMOVE";
  for(i = 0; i < 5; i++)
  {
    x = -5 + (rand() % 26);
    cout << setw(3) << x;
    s_remove(A,x);
  }
  cout << endl << "A ="; s_print(A);
  cout << endl << "SIZE OF A IS " << s_size(A) << endl << endl;

  // Sprawdzamy obecno�� wybranych element�w w B

  for(int i = 0; i < 10; i++)
  {
    x = -5 + (rand() % 26);
    cout << "IS ELEMENT" << setw(3) << x << " IN SET B? ";
    if(s_isin(B,x)) cout << "YES"; else cout << "NO";
    cout << endl;
  }

  // Sprawdzenie testu na zbi�r pusty

  cout << endl << endl << "IS SET A EMPTY?" << endl;
  if(s_empty(A)) cout << "YES"; else cout << "NO";

  cout << endl << endl << "IS INTERSECTION OF A AND COMPLEMENT OF A EMPTY?" << endl;
  s_complement(A,C);
  s_intersection(A,C,C);
  if(s_empty(C)) cout << "YES"; else cout << "NO";
  cout << endl;

  // Usuwamy tablice dynamiczne w zbiorach

  delete [] A.T;
  delete [] B.T;
  delete [] C.T;

  return 0;
}

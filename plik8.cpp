// Du¿e liczby Fibonacciego
// Data: 25.10.2012
// (C)2012 mgr Jerzy Wa³aszek
//---------------------------------------

#include <iostream>
#include <string>

using namespace std;

// Oblicza sumê podanych liczb
//----------------------------
string dodaj(string & x, string & y)
{
  string z;
  int p,w,i,j,k,n;

  i = x.length();
  j = y.length();

  n = i; if(j < i) n = j;

  p = 0;

  z = "";

  for(k = 1; k <= n; k++)
  {
    w  = (int)(x[--i]) + (int)(y[--j]) + p - 96;
    p  = w / 10;
    z = (char)((w % 10) + 48) + z;
  }

  while(i)
  {
    w  = x[--i] + p - 48;
    p  = w / 10;
    z = (char)((w % 10) + 48) + z;
  }

  while(j)
  {
    w  = y[--j] + p - 48;
    p  = w / 10;
    z = (char)((w % 10) + 48) + z;
  }

  if(p) z = (char)(p + 48) + z;

  if(z == "") z = "0";

  return z;  // zwracamy wynik dodawania
}

//********************
//** PROGRAM G£ÓWNY **
//********************

int main()
{
  string f0,f1,f;
  unsigned int i,n;

  // odczytujemy n

  cin >> n;

  // obliczamy fn

  if(!n) f = "0";
  else if(n == 1) f = "1";
  else
  {
    f0 = "0";
    f1 = "1";
    for(i = 2; i <= n; i++)
    {
      f  = dodaj(f0,f1);
      f0 = f1;
      f1 = f;
    }
  }

  // wyœwietlamy wynik

  cout << f << endl;

  return 0;
}

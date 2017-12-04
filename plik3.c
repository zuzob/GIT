// Generator pseudolosowy Park-Miller
// Data:   18.04.2008
// (C)2012 mgr Jerzy Wa³aszek
//----------------------------------

#include <iostream>

using namespace std;

unsigned int x0;

// Generuje liczby pseudolosowe
//-----------------------------
unsigned int PM_RNG()
{
  unsigned int xlo,xhi;

  xlo = 16807 * (x0 & 0xffff);
  xhi = 16807 * (x0 >> 16);
  xlo += (xhi & 0x7fff) << 16;
  xlo += xhi >> 15;
  if(xlo > 0x7fffffff) xlo -= 0x7fffffff;
  return (x0 = xlo);
}
//dodany kod do drugiej ga³êzi
// Ustawia losowe x0
//------------------
void Uprzypadkowij()
{
  do x0 = (unsigned int) time(NULL); while(!x0);
}

int main()
{
  unsigned int a,b,n,i;

  cin >> a >> b >> n;
  Uprzypadkowij();
  for(i = 1; i <= n; i++) cout << (a + PM_RNG() % (b - a + 1)) << " ";
  cout << endl;
  return 0;
}

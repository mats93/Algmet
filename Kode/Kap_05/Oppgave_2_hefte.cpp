/*
      Algoritmiske metoder          -   Kapittel 5 - Oppgave 2 fra hefte.
      Mats Ove Mandt Skjærstein     -   Bitsec.

      Finner 'facorial' av et tall, rekursivt og iterativt.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////


//  INCLUDE:
#include <iostream>                                                 // cin, cout.

using namespace std;


//  DEKLARASJON AV FUNKSJONER:
int factorialRekursivt(int n);                                      // Rekursiv versjon av factorial utregning.
int factorialIterativ(int n);                                       // Iterativ versjon av factorial utregning. 


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  int n; 
  int min = 1, max = 50;
  
  do {
    cout << "\nVelg tallet du vil finne factorial av (" << min << "-" << max << "): ";
    cin >> n;  
  } while (n < min || n > max);

  // Factorial av n på en rekusiv måte.
  cout << "Rekursiv: Factorial av " << n << " er " << factorialRekursivt(n) << '\n';

  // Factorial av n på en iterativ måte.
  cout << "Iterativ: Factorial av " << n << " er " << factorialIterativ(n) << '\n';

  cout << "\n\n"; 
  return 0;
}


// ************************************  DEFINISJON AV FUNKSJONER  *************************************

int factorialRekursivt(int n) {
  if (n == 0)                                                       // Hvis n er 0, avslutt rekursjon og returner 1.
    return 1;
  return n * factorialRekursivt(n - 1);                             // Gang "n" med tallet under "n".
}

int factorialIterativ(int n) {
  int tall = n;

  for (int i = n; i > 1; i--)                                       // Telles ned fra n til 2.
    tall = tall * (i - 1);                                          // ganger "n" med tallet under "n".

  return tall;                                                      // Returnerer svaret. 
}

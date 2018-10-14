/*
      Algoritmiske metoder          -     Kapittel 11 - Oppgave 13 fra hefte.
      Mats Ove Mandt Skjærstein     -     Bitsec.

      Operasjoner på en Heap (Prioritetskø).
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS                                     // Fjerner sikkerhetsvarsler. 


//  INCLUDE:
#include <iostream>                                                 // cin, cout.

using namespace std;


//  CONST:
const int LEN = 21;                                                 // Maks antall tegn i heapen (1-20).
const int MAXITEM = 999;                                            // En stor verdi som brukes som sentinel key.


//  TYPEDEF:
typedef int itemtype;


//  KLASSER:
class PQ {
  private:
    itemtype *a;
    int n;

  public:
    PQ(int max);                                                    // Constructor.
    ~PQ();                                                          // Deconstructor.
    void display();                                                 // Skriver ut innholdet i arrayen, opp til og med "n". 
    void upheap(int k);                                             // Restorer "heap condition" når en verdi er satt inn på "k" indeks. Sjekker treet "over" k.
    void insert(itemtype v);                                        // Sett inn et nytt element i prioritetskøen / heapen.
    void downheap(int k);                                           // Restorer "heap condition" når en verdi er satt inn på "k" indeks. Sjekker treet "under" k.
    itemtype remove();                                              // Fjerner den største verdien fra heapen.
    itemtype replace(itemtype v);                                   // Bytt ut den største verdien med en ny (så lenge den nye ikke er større enn den gamle).
    void extract(int k);                                            // Sletter element nr. "k" fra heapen.
    void change(int k, int p);                                      // Legger til eller minimerer nøkkelen til element "k" med "p" (endrer prioritet).
};


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  PQ heap(LEN); 
  char ch;
  
  heap.insert(1);     cout << "\nInsert 1 :     ";  heap.display();  cin >> ch;
  heap.insert(5);     cout << "\nInsert 5 :     ";  heap.display();  cin >> ch;
  heap.insert(2);     cout << "\nInsert 2 :     ";  heap.display();  cin >> ch;
  heap.insert(6);     cout << "\nInsert 6 :     ";  heap.display();  cin >> ch;
  heap.replace(4);    cout << "\nReplace 4:     ";  heap.display();  cin >> ch;
  heap.insert(8);     cout << "\nInsert 8 :     ";  heap.display();  cin >> ch;
  heap.remove();      cout << "\nRemove   :     ";  heap.display();  cin >> ch;
  heap.insert(7);     cout << "\nInsert 7 :     ";  heap.display();  cin >> ch;
  heap.insert(3);     cout << "\nInsert 3 :     ";  heap.display();  cin >> ch;

  heap.change(4, 5);  cout << "\nChange #4 +5:  ";  heap.display();  cin >> ch;
  heap.change(1, -4); cout << "\nChange #1 -4:  ";  heap.display();  cin >> ch;
  heap.extract(2);    cout << "\nExtract #2:    ";  heap.display();  cin >> ch;
  heap.extract(2);    cout << "\nExtract #2:    ";  heap.display();  cin >> ch;
  heap.extract(1);    cout << "\nExtract #1:    ";  heap.display();

  cout << "\n\n"; 
  return 0;
}


// ************************************  DEFINISJON AV KLASSEFUNKSJONER  *******************************

PQ :: PQ(int max) {                                                 // Constructor.
  a = new itemtype[max];                                            // Lager en ny array av lengden "maks".
  n = 0;                                                            // Setter n til 0, (n = sise brukte indeks).
}

PQ :: ~PQ() {                                                       // Deconstructor.
  delete[] a;                                                       // Sletter arrayen.
}

void PQ :: display() {                                              // Skriver ut innholdet i arrayen, opp til og med "n". 
  for (int i = 1; i <= n; i++) 
    cout << a[i] << ' ';
}

void PQ :: upheap(int k) {                                          // Restorer "heap condition" når en verdi er satt inn på "k" indeks. Sjekker treet "over" k.
  itemtype v;
  v = a[k];                                                         // Tar vare på elementet i indeks "k".                                       
  a[0] = MAXITEM;                                                   // Legger inn sentinel key.

                                                                    // "k/2" for å finne "parrent" til a[k] (v).
  while (a[k/2] <= v) {                                             // Så lenge "parrent" er mindre eller lik "meg(v)". 
    a[k] = a[k/2];                                                  // Sett "parrent" ned til den posisjonen "jeg(k)" hadde. 
    k = k/2;                                                        // Tell ned k til å tilsvare "meg(k)" sin nye indeks.
  }
  a[k] = v;                                                         // Når loop er ferdig, kopier "meg selv(v)" inn på den korrekte plassen.
                                                                    // Dette er enten en "parrent / granparrent osv" eller meg selv sin gamle posisjon.
}

void PQ :: insert(itemtype v) {                                     // Sett inn et nytt element i prioritetskøen / heapen.
  a[++n] = v;                                                       // Legger 'v' inn på siste posisjon i heap arrayen, og teller opp n med 1.
  upheap(n);                                                        // Upheaper n til "heap condition" er møtt.
}

void PQ :: downheap(int k) {                                        // Restorer "heap condition" når en verdi er satt inn på "k" indeks. Sjekker treet "under" k.
  int j;
  itemtype v;
  v = a[k];                                                         // Tar vare på element i indeks "k".

  while (k <= n/2) {                                                // Hvis "min" indeks er mindre eller lik antall elementer / 2. ?????
    j = k+k;                                                        // j = k+k vil si at j = indeksen til "mitt(k)" første barn.
    
    if (j < n && a[j] < a[j+1])                                     // Hvis "mitt første barns indeks" er mindre enn det siste elementets indeks. Og
      j++;                                                          // elementet til "mitt første barn" er mindre enn elementet til "mitt andre barn", så plusses j med 1.
                                                                    // j plusses med 1, slik det blir indeksen til "mitt største barn", vil alltid sammenligne meg selv med en største.

    if (v >= a[j])                                                  // Hvis "meg(v)" er større eller lik "mitt største barn",
      break;                                                        //  så breakes det, siden "jeg(v)" har funnet min korrekte plass "k".

    a[k] = a[j];                                                    // Sett "barn" til den posisjoenen "jeg(k)" hadde.
    k = j;                                                          // Endre "min" posisjon til å være "j", siden jeg gjorde en swap over.
  }
  a[k] = v;                                                         // Når loop er ferdig, kopier "meg selv(v)" inn på den korrekte plassen.
                                                                    // Dette er enten en "barn / barnebarn osv" eller meg selv sin gamle posisjon.
}

itemtype PQ :: remove() {                                           // Fjerner den største verdien fra heapen.
  itemtype v = a[1];                                                // Tar kopi av det størst elementet.
  a[1] = a[n--];                                                    // Flytter element i indeks "n" til toppen (indeks 1), og teller ned "n" med 1.
  downheap(1);                                                      // downheaper element i indeks 1 til heap condition er møtt.
  return v;                                                         // Returnerer så den som var størst før remove() ble kjørt.
}

itemtype PQ :: replace(itemtype v) {                                // Bytt ut den største verdien med en ny (så lenge den nye ikke er større enn den gamle).
  a[0] = v;                                                         // Legg den nye verdien inn i indeks 0. Indeks 0 har bare et barn, og det er rota.
  downheap(0);                                                      // downheaper den nye verdien, hvis de nye verdien er høyere enn rota, vil det ikke skje noen endring.
  return a[0];                                                      // Returnerer så det som var den gamle rota, eller seg selv.
}

void PQ :: extract(int k) {                                         // Sletter element nr. "k" fra heapen.
  itemtype v = a[k];                                                // Tar vare på den som skal slettes.
  
  a[k] = a[n--];                                                    // Bytter plass på den siste og den som skal slettes og teller end n.
  if (v <= a[k])                                                    // Hvis den nye er større enn den som lå der, så upheapes den (flyttes oppover).
    upheap(k);  
  else                                                              // Hvis den nye nye er mindre eller lik den som lå der, så downheapes den (flyttes nedover).
    downheap(k);
}

void PQ :: change(int k, int p) {                                   // Legger til eller minimerer nøkkelen til element "k" med "p" (endrer prioritet).
  a[k] += p;                                                        // Legger til verdien "p" i nøkkelen til a[k], (p kan være + eller -). 

  if (p >= 0)                                                       // Hvis prioriteten øker, upheap elementet.
    upheap(k);
  else
    downheap(k);                                                    // Hvis prioriteten minsker, downheap elementet.
}


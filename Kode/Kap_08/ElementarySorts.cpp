/*
      Algoritmiske metoder          -     Elementære sorteringer.
      Mats Ove Mandt Skjærstein     -     Bitsec.

      Ingen oppgave knyttet til denne oppgaven.
      
      Inneholder de elementære sorterings-algoritmene:
        * selection sort
        * insertion sort
        * bubble sort
        * shellsort
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS                                     // Fjerner sikkerhetsvarsler. 


//  INCLUDE:
#include <iostream>                                                 // cin, cout.

using namespace std;


//  CONST:
const int N = 12;                                                   // Lengden til arrayen som skal sorteres.


//  TYPEDEF:
typedef char itemtype; 


//  DEKLARASJON AV FUNKSJONER:
void fillArray(itemtype a[], bool sentinal);                        // Fyller arrayen.
bool testArraySort(itemtype a[]);                                   // Sjekker om arrayen er sortert korrekt. 
void displayArray(itemtype a[], int max = N);                       // Skriver ut innholdet i en array.
void displayArrayVersjon(itemtype a[], int i, int comp, int swaps); // Skriver ut array, skal brukes etter hver endring for en sortering.
void endreBokstav(itemtype a[], int i, int j, bool tilStor);        // Endre en bokstaver i arrayen til stor hvis "true", eller til liten hvis "false".                         

void swap(itemtype a[], int i, int j);                              // Bytter plass på 2 elementer i en array.
void selectionSort(itemtype a[]);                                   // Algoritmen selection sort.
void insertionSort(itemtype a[]);                                   // Algoritmen insertion sort.
void bubbleSort(itemtype a[]);                                      // Algoritmen bubble sort.
void shellsort(itemtype a[]);                                       // Algoritmen shellsort.


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  itemtype sortArray[N+1];

  fillArray(sortArray, false);
  cout << "\n\nSortering av arrayen: \n"; 
  displayArray(sortArray);
  
  cout << "\n\n****************************************************"
       << "\nSorteringen 1: Selection sort \n";
  selectionSort(sortArray);
  if (!testArraySort(sortArray))
    cout << "\nSortering feilet, arrayen er ikke sortert korrekt\n"; 
 
  fillArray(sortArray, true);
  cout << "\n\n****************************************************"
    << "\nSorteringen 2: Insertion sort \n";
  insertionSort(sortArray);
  if (!testArraySort(sortArray))
    cout << "\nSortering feilet, arrayen er ikke sortert korrekt\n";

  fillArray(sortArray, false);
  cout << "\n\n****************************************************"
    << "\nSorteringen 3: Bubble sort \n";
  bubbleSort(sortArray);
  if (!testArraySort(sortArray))
    cout << "\nSortering feilet, arrayen er ikke sortert korrekt\n";

  fillArray(sortArray, false);
  cout << "\n\n****************************************************"
    << "\nSorteringen 4: Shellsort \n";
  shellsort(sortArray);
  if (!testArraySort(sortArray))
    cout << "\nSortering feilet, arrayen er ikke sortert korrekt\n";

  cout << "\n\n"; 
  return 0;
}


// ************************************  DEFINISJON AV FUNKSJONER  *************************************

void fillArray(itemtype a[], bool sentinal) {                       // Fyller arrayen.
  itemtype arr[] = { ' ', 'e', 'a', 's', 'y', 'q', 'u', 'e', 's', 't', 'i', 'o', 'n' };
  // Verdi:                5    1   19   25   17   21    5   19   20    9   15   14
  if (sentinal)                                                     // Hvis true, legger inn en sentinal key i indeks 0.
    a[0] = -1;
  else 
    a[0] = ' ';
  for (int i = 1; i <= N; i++) {                                    // Fyller arrayen.
    a[i] = arr[i];
  }
}

bool testArraySort(itemtype a[]) {                                  // Sjekker om arrayen er sortert korrekt. 
  itemtype korrekt[] = { ' ', 'a', 'e', 'e', 'i', 'n', 'o', 'q', 's', 's', 't', 'u', 'y' };

  for (int i = 1; i <= N; i++) {                                    // Looper gjennom array fra indeks 1 til og med N.
    if (towlower(a[i]) != korrekt[i])                               // Hvis en bokstav ligger på feil plass,
      return false;                                                 //  så returneres false.
  }
  return true;                                                      // Hvis den er sortert korrekt, så returneres true.
}

void displayArray(itemtype a[], int max) {                          // Skriver ut innholdet i en array.
  for (int i = 1; i <= max; i++)
    cout << " " << a[i];
}

void displayArrayVersjon(itemtype a[], int i, int comp, int swaps) {// Skriver ut array, skal brukes etter hver endring for en sortering.
  cout << "\n  Loop nr. " << i << ": ";                             // Skriver ut arrayen så langt.
  displayArray(a);
  cout << "\n  Antall comparisons: " << comp << "    "
       << "\n  Antall swaps: " << swaps << '\n';
}

void endreBokstav(itemtype a[], int i, int j, bool tilStor) {       // Endre en bokstaver i arrayen til stor hvis "true", eller til liten hvis "false".
  if (tilStor) {
    a[i] = toupper(a[i]);                                           // Gjør om til store bokstaver hvis true.
    a[j] = toupper(a[j]);
    cout << "\n  (" << "a[" << i << "]=" << a[i]                    // Skriver ut hva som ble endret.
         << " og " << "a[" << j << "]=" << a[j] << ")";
  }
  else {
    a[i] = tolower(a[i]);                                           // Gjør om til små bokstaver.
    a[j] = tolower(a[j]);
  }
}

void swap(itemtype a[], int i, int j) {                             // Bytter plass på 2 elementer i en array.
  itemtype t = a[i];                                                // Lagrer unna element i indeks "i".
  a[i] = a[j];                                                      // Lagrer element i indeks "j" i indeks "i".
  a[j] = t;                                                         // Lagrer det kopierte elementet i indeks "j". 
}

void selectionSort(itemtype a[]) {                                  // Algoritmen selection sort.
  int i, j, min;
  int comparisons = 0, swaps = 0; 

  for (i = 1; i < N; i++) {                                         // Outer loop: Looper til nest siste indeks i array.
                                                                    // Fordi når siste outer loop kjører skal alt være sortert, trenger ikke å 
                                                                    //   sammenligne seg selv med seg selv.
    min = i;                                                        // Setter det minste elementet til å være "meg selv(i)".
    for (j = i+1; j <= N; j++) {                                    // Inner loop: Looper 1 høyere en "meg selv", fortsetter slik ut resten av arrayen.
      comparisons++;
      if (a[j] < a[min])                                            // Hvis "den bak meg selv(i)" er mindre enn "meg(i)", oppdater "min" til å være "j".
        min = j;                                                    // Det vil si, hver gang jeg finner en mindre, oppdater min variabel til å holde dens indeks.
    }
    swaps++;
    swap(a, min, i);                                                // Når inner loop er ferdig. Bytt plass for "meg(i)" og den minste i arrayen (min). 
    endreBokstav(a, min, i, true);
    
    displayArrayVersjon(a, i, comparisons, swaps);                  // Skriver ut arrayen.
    endreBokstav(a, min, i, false);
  }
}

void insertionSort(itemtype a[]) {                                  // Algoritmen insertion sort.
  int i, j;
  itemtype v;
  int comparisons = 1, swaps = 0;

  for (i = 2; i <= N; i++) {                                        // Outer loop. Starter i andre posisjon og looper helt ut til siste posisjon.
    v = a[i];                                                       // Tar vare på det som ligger i "meg selv(i)".
    j = i;                                                          // Setter "j" til å være "meg selv" sin indeks (samme som i). 
    
    comparisons++;
    if (a[j-1] > v)
      comparisons--; 
    
    while (a[j-1] > v) {                                            // Inner loop. Sammenligner den bak "meg selv", hvis den bak er større en "meg selv",
      a[j] = a[j-1];                                                //  så bytter de plass. Looper bakover helt til den ikke finner noen som er mindre enn "meg selv".
      comparisons++;
      swaps++;
      j--;
    }
    a[j] = v;                                                       // Når inner loop er ferdig. setter elementet inn i dens riktige plass.
    swaps++;

    endreBokstav(a, i, j, true);
    displayArrayVersjon(a, i-1, comparisons, swaps);                // Skriver ut arrayen.
    endreBokstav(a, i, j, false);
  }
}

void bubbleSort(itemtype a[]) {                                     // Algoritmen bubble sort.
  int i, j;
  int comparisons = 0, swaps = 0;

  for (i = N; i >= 1; i--) {                                        // Outer loop. Etter hver loop så skal den høyeste verdien ligge på plass N. 
    for (j = 2; j <= i; j++) {                                      // Inner loop. Går gjennom alle elementene og sammenligner seg selv med den rett bak "seg selv".
      comparisons++;                                                // Dette ender med at den høyeste "bobbler" seg opp til enden etter at inner loop er ferdig.
      if (a[j-1] > a[j]) {                                          // Hvis den rett bak er høyere enn "meg selv":
        swaps++;
        swap(a, j-1, j);                                            //  Så bytter de plass. 
      }
    }
    endreBokstav(a, j - 1, j, true);
    displayArrayVersjon(a, i, comparisons, swaps);                  // Skriver ut arrayen.
    endreBokstav(a, j - 1, j, false);
  }
}

void shellsort(itemtype a[]) {                                      // Algoritmen shellsort.
  int i, j, h;
  itemtype v;
  int comparisons = 0, swaps = 0;

  for (h = 1; h <= N/9; h = 3*h+1);                                 // Velger hvilke "gap" som skal brukes basert på lengden til arrayen.
  for (; h > 0; h/=3) {                                             // Outer loop. Deler "gap" på 3 hver gang en shellsort er utført.
                                                                    // Dette vil føre til en insertion sort helt til slutt.
    for (i = h+1; i <= N; i+=1) {                                   // Setter "meg selv(i)" til å være "gappet +1" og itererer "i" med 1 for hver loop.
                                                                    // Slik vil sorten bevege seg en plass oppover og samtidig ha samme gap, til gap er utenfor array.
      v = a[i];                                                     // Mellomlagrer det som ligger i indeks "i" til variabelen "v", altså "meg selv".
      j = i;

      comparisons++;
      while (j > h && a[j-h] > v) {                                 // Så lenge "j" er av høyere verdi enn "gap" og element i indeks "j"-"h", altså det elementet "rett bak"
        swaps++;                                                    //  ("rett bak" har altså et "gap" i mellom seg): 
        a[j] = a[j-h];                                              //   Så settes settes verdien til indeks "j" til å være denne bokstaven.
        j -= h;                                                     // Teller ned j, slik at den kan sammenlige seg selv "bakover" + "gap", samme som insertion sort gjør.
        comparisons++;
      }
      
      a[j] = v;                                                     // Når enten arrayens grense er nådd, eller en høyere verdi ikke er funnet så lagres "v" i indeksen "j". 
                                                                    //  mao, "meg selv" blir lagret i indeks "j". 
      endreBokstav(a, j, j - h, true);
      displayArrayVersjon(a, i, comparisons, swaps);                // Skriver ut arrayen.
      endreBokstav(a, j, j - h, false);
    }
  }
}

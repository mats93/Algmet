/*
      Algoritmiske metoder        -   Kapittel 9 - Oppgave 10 fra hefte.
      Mats Ove Mandt Skjærstein   -   Bitsec.

      Quicksort med 'median-of-three' partisjonering og insertion sort.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS                                     // Fjerner sikkerhetsvarsler. 


//  INCLUDE:
#include <iostream>                                                 // cin, cout.

using namespace std;


//  CONST:
const int LEN = 13;                                                 // Lengden på array + '\0'.                 
const int M = 5;                                                    // Hvis arrayen er mindre eller lik M, så skal Insertion sort kjøres.


//  TYPEDEF:
typedef char itemtype;


//  DEKLARASJON AV FUNKSJONER:
void fillArray(itemtype a[]);                                       // Fyller arrayen med innhold. 
void displayArray(itemtype a[], int min, int max);                  // Skriver ut innholdet i arrayen.

void swap(itemtype a[], int i, int j);                              // Bytter om 2 elementer.
void partitionMedianOfThree(itemtype a[], int l, int r);            // Median-of-Three partisjonering.
void insertionSort(itemtype a[], int l, int r);                     // Algoritmen Insertion Sort, modifisert til å passe med quicksort.
void quicksort(itemtype a[], int l, int r);                         // Algoritmen Quicksort med bruk av "Insertion Sort" og "Median-of-Three".



//  GLOBALE VARIABLER:
int comparisons = 0;


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  itemtype a[LEN];
  
  fillArray(a); 
  cout << "\nArrayen som skal sorteres:\n";
  displayArray(a, 0, LEN-1); 

  quicksort(a, 0, LEN-2);                                           // Kjører quicksort på hele arrayen. 

  cout << "\n\nArrayen etter sortering:\n";
  displayArray(a, 0, LEN-1);

  cout << "\n\nDet ble gjort " << comparisons << " comparisons"; 
  cout << "\n\n"; 
  return 0;
}


// ************************************  DEFINISJON AV FUNKSJONER  *************************************

void fillArray(itemtype a[]) {                                      // Fyller arrayen med innhold.
  strcpy(a, "EASYQUESTION");
}

void displayArray(itemtype a[], int min, int max) {                 // Skriver ut innholdet i arrayen.
  for (int i = 0; i <= min; i++)
    cout << " " << " ";

  for (int j = min; j <= max; j++)
    cout << " " << a[j];

}

void swap(itemtype a[], int i, int j) {                             // Bytter om 2 elementer.
  itemtype b = a[i];
  a[i] = a[j];
  a[j] = b;
}

void partitionMedianOfThree(itemtype a[], int l, int r) {           // Median-of-Three partisjonering.
  int mid = (l+r) / 2;                                              // Verdien mellom l og r.

  if (a[l] > a[mid])                                                // Sorterer de tre verdiene, slik at den minste
    swap(a, l, mid);                                                //  havner til venstre, den største til høyre og 
                                                                    //  den mellomste i midten av sub-arrayen som er medsent.
  if (a[l] > a[r])
    swap(a, l, r);

  if (a[mid] > a[r])
    swap(a, mid, r); 
                                                                    // Fordi r har den største verdien, er det mest sannsnylig at 
                                                                    //  denne burde ligge i sin posisjon, til høyre i arrayen.
  swap (a, mid, r-1);                                               // Derfor settes partisjonselementet nest bakerst.
}

void insertionSort(itemtype a[], int l, int r) {                    // Algoritmen Insertion Sort, modifisert til å passe med quicksort.
  itemtype v, copy;
  int i, j; 

  copy = a[l-1];                                                    // Tar kopi av det som ligger i l-1, og
  a[l-1] = -1;                                                      //  legger inn en Sentinal key

  for (i = l+1; i <= r; i++) {                                      // Looper fra l+1 til og med r (hele subarrayen).
    v = a[i];                                                       // Det elementet det skal sammenlignes med ("meg selv").
    j = i;                                                          // Indeksen til den jeg skal sammenligne med.
    while (a[j-1] > v) {                                            // Sammenligner "meg selv" med den rett bak.
      a[j] = a[j-1];                                                // Hvis den bak er større, bytt plass.
      j--;                                                          // Sammenlign så bakover i arrayen, slik at 'v' ("meg selv") blir 
    }                                                               //  "inserted" på riktig plass.
    a[j] = v;                                                       // Legg så 'v' ("meg selv") inn på sin riktige plass. 
  }
  a[l-1] = copy;                                                    // Fjerner sentinal key, og legger korrekt verdi tilbake. 
}

void quicksort(itemtype a[], int l, int r) {                        // Algoritmen Quicksort med bruk av "Insertion Sort" og "Median-of-Three".
  int i, j;
  itemtype v;

  if (r-l <= M)                                                     // Kjører Insertion sort hvis sub-arrayen er mindre eller lik M.
    insertionSort(a, l, r);
  else {                                                            // Hvis ikke så kjører "partisjonsering". 
    partitionMedianOfThree(a, l, r);                                // Kjører "Median-of-Three" algoritmen.
    v = a[r-1];                                                     // partisjons elementet er "medianen".
    cout << "\n\nPartisjons indeks: " << r << "(" << a[r-1] << ")";
    i = l; j = r-1;                                                 // Tar ikke med elementet helt til høyre (men r-1), denne blir sortert av 
    for (;;) {                                                      //  "Median-Of-Three" og "Insertion Sort". Pga. sannsynligheten for at denne
      comparisons += 2;                                             //  er av stor verdi er høy. (Var den største i "Median-Of-Three").
      while (a[++i] < v) comparisons++;                             // Plusser på "i", så lenge elementet er mindre enn 'v' ("meg selv"). "i" vil gå én over.
      while (a[--j] > v) comparisons++;                             // Minus på "j", så lenge elementet er høyere enn 'v' ("meg selv"). "j" vil gå én under.
      if (i >= j) break;                                            // Hvis i er større eller lik j (de "krysser") så breaker den uendelige loopen.
      swap(a, i, j);                                                // Hvis ingen break, så bytter "i" og "j" plass i arrayen, og loopen starter på nytt.
    }
    swap(a, i, r-1);                                                // Bytter plass for element i indeks "i" og "r-1" (nest siste).
    
    cout << "\nArray etter partisjonering: \n";

    displayArray(a, l, r);

    quicksort(a, l, i-1);                                           // Kaller quicksort igjen, på sub-arrayen left til i-1.
    quicksort(a, i+1, r);                                           // Kaller quicksort igjen, på sub-arrayen i+1 til right.
  }
}

/*
      Algoritmiske metoder        -   Kapittel 9 - Oppgave 10 fra hefte.
      Mats Ove Mandt Skj�rstein   -   Bitsec.

      Quicksort med 'median-of-three' partisjonering og insertion sort.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS                                     // Fjerner sikkerhetsvarsler. 


//  INCLUDE:
#include <iostream>                                                 // cin, cout.

using namespace std;


//  CONST:
const int LEN = 13;                                                 // Lengden p� array + '\0'.                 
const int M = 5;                                                    // Hvis arrayen er mindre eller lik M, s� skal Insertion sort kj�res.


//  TYPEDEF:
typedef char itemtype;


//  DEKLARASJON AV FUNKSJONER:
void fillArray(itemtype a[]);                                       // Fyller arrayen med innhold. 
void displayArray(itemtype a[], int min, int max);                  // Skriver ut innholdet i arrayen.

void swap(itemtype a[], int i, int j);                              // Bytter om 2 elementer.
void partitionMedianOfThree(itemtype a[], int l, int r);            // Median-of-Three partisjonering.
void insertionSort(itemtype a[], int l, int r);                     // Algoritmen Insertion Sort, modifisert til � passe med quicksort.
void quicksort(itemtype a[], int l, int r);                         // Algoritmen Quicksort med bruk av "Insertion Sort" og "Median-of-Three".



//  GLOBALE VARIABLER:
int comparisons = 0;


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  itemtype a[LEN];
  
  fillArray(a); 
  cout << "\nArrayen som skal sorteres:\n";
  displayArray(a, 0, LEN-1); 

  quicksort(a, 0, LEN-2);                                           // Kj�rer quicksort p� hele arrayen. 

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
    swap(a, l, mid);                                                //  havner til venstre, den st�rste til h�yre og 
                                                                    //  den mellomste i midten av sub-arrayen som er medsent.
  if (a[l] > a[r])
    swap(a, l, r);

  if (a[mid] > a[r])
    swap(a, mid, r); 
                                                                    // Fordi r har den st�rste verdien, er det mest sannsnylig at 
                                                                    //  denne burde ligge i sin posisjon, til h�yre i arrayen.
  swap (a, mid, r-1);                                               // Derfor settes partisjonselementet nest bakerst.
}

void insertionSort(itemtype a[], int l, int r) {                    // Algoritmen Insertion Sort, modifisert til � passe med quicksort.
  itemtype v, copy;
  int i, j; 

  copy = a[l-1];                                                    // Tar kopi av det som ligger i l-1, og
  a[l-1] = -1;                                                      //  legger inn en Sentinal key

  for (i = l+1; i <= r; i++) {                                      // Looper fra l+1 til og med r (hele subarrayen).
    v = a[i];                                                       // Det elementet det skal sammenlignes med ("meg selv").
    j = i;                                                          // Indeksen til den jeg skal sammenligne med.
    while (a[j-1] > v) {                                            // Sammenligner "meg selv" med den rett bak.
      a[j] = a[j-1];                                                // Hvis den bak er st�rre, bytt plass.
      j--;                                                          // Sammenlign s� bakover i arrayen, slik at 'v' ("meg selv") blir 
    }                                                               //  "inserted" p� riktig plass.
    a[j] = v;                                                       // Legg s� 'v' ("meg selv") inn p� sin riktige plass. 
  }
  a[l-1] = copy;                                                    // Fjerner sentinal key, og legger korrekt verdi tilbake. 
}

void quicksort(itemtype a[], int l, int r) {                        // Algoritmen Quicksort med bruk av "Insertion Sort" og "Median-of-Three".
  int i, j;
  itemtype v;

  if (r-l <= M)                                                     // Kj�rer Insertion sort hvis sub-arrayen er mindre eller lik M.
    insertionSort(a, l, r);
  else {                                                            // Hvis ikke s� kj�rer "partisjonsering". 
    partitionMedianOfThree(a, l, r);                                // Kj�rer "Median-of-Three" algoritmen.
    v = a[r-1];                                                     // partisjons elementet er "medianen".
    cout << "\n\nPartisjons indeks: " << r << "(" << a[r-1] << ")";
    i = l; j = r-1;                                                 // Tar ikke med elementet helt til h�yre (men r-1), denne blir sortert av 
    for (;;) {                                                      //  "Median-Of-Three" og "Insertion Sort". Pga. sannsynligheten for at denne
      comparisons += 2;                                             //  er av stor verdi er h�y. (Var den st�rste i "Median-Of-Three").
      while (a[++i] < v) comparisons++;                             // Plusser p� "i", s� lenge elementet er mindre enn 'v' ("meg selv"). "i" vil g� �n over.
      while (a[--j] > v) comparisons++;                             // Minus p� "j", s� lenge elementet er h�yere enn 'v' ("meg selv"). "j" vil g� �n under.
      if (i >= j) break;                                            // Hvis i er st�rre eller lik j (de "krysser") s� breaker den uendelige loopen.
      swap(a, i, j);                                                // Hvis ingen break, s� bytter "i" og "j" plass i arrayen, og loopen starter p� nytt.
    }
    swap(a, i, r-1);                                                // Bytter plass for element i indeks "i" og "r-1" (nest siste).
    
    cout << "\nArray etter partisjonering: \n";

    displayArray(a, l, r);

    quicksort(a, l, i-1);                                           // Kaller quicksort igjen, p� sub-arrayen left til i-1.
    quicksort(a, i+1, r);                                           // Kaller quicksort igjen, p� sub-arrayen i+1 til right.
  }
}

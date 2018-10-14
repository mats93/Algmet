/*
      Algoritmiske metoder          -    Kapittel 5 - Oppgave 8 fra hefte.
      Mats Ove Mandt Skjærstein     -    Bitsec.

      Permutering av ord og filtrering på hvilke ord som skal skrives ut.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS                                     // Fjerner sikkerhetsvarsler. 


//  INCLUDE:
#include <iostream>                                                 // cin, cout.

using namespace std;


//  STRUCT:
struct node {                                                       // Til å lage en linked list.
  char ord[20];
  node *next;
};


//  DEKLARASJON AV FUNKSJONER:
char *lesTekst();                                                   // Leser inn en tekst.
int factorialIterativ(int n);                                       // Regner ut factorial av n (N!).

void permuter(char *tekst, int i);                                  // Permuterer teksten.
char *swap(char *tekst, int i, int j);                              // Bytter plass for element i indeks "i" med element i indeks "j".

void insertListe(char *tekst);                                      // Legger til en node med teksten "tekst" fremst i listen.
void displayListe(node *r);                                         // Skriver ut innholdet av listen.

bool testTekst(char *tekst);                                        // Tester de forskjellige conditionene beskrevet i (1) i oppgaven.
bool erVokal(char *tekst, int i);                                   // Sjekkor om bokstaven i indeks "i" er en vokal.
bool erKonsonant(char *tekst, int i);                               // Sjekker om bokstav i indeks "i" er en konsonant.

bool toLikeVokaler(char *tekst);                                    // Sjekker om (1-a) to like vokaler kommer etter hverandre.
bool treVokaler(char *tekst);                                       // Sjekker om (1-b) tre vokaler kommer etter hverandre. 
bool treLikeKonsonanter(char *tekst);                               // Sjekker om (1-c) tre like konsonanter kommer etter hverandre.
bool fireKonsonanter(char *tekst);                                  // Sjekker om (1-d) fire konsonanter kommer etter hverandre.
bool toLikeBokstaveriStarten(char *tekst);                          // Sjekker om (1-e) to like bokstaver (vokaler eller konsonanter) starter et ord.
bool finnesiListe(char *tekst);                                     // Sjekker om (2) ordet har blit skrevet ut før (om det finnes i listen).


//  GLOBALE VARIABLER:
int permNr = 0;                                                     // Antall permutasjoner.
node *head, *z;                                                     // Hode og hale til linked list.


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  int len;
  char *tekst;

  z = new node;                                                     // Noder til å lage en linked list.
  head = new node;
  z->next = z;
  head->next = z;

  tekst = lesTekst();                                               // Leser inn en tekst.
  len = strlen(tekst);

  cout << "\n***************************************************"
       << "\nDu har valgt: " << tekst;
  cout << "\nLengde pa teksten er: " << len;
  cout << "\nTeksten har " << factorialIterativ(len) << " mulige permuteringer";
  cout << "\n\nLovelige permuteringer er (i folge oppgaven):"; 

  permuter(tekst, 0);                                               // Permuterer teksten fra posisjon 0 (første bokstav).

  displayListe(head->next);                                         // Skriver ut innholder i listen. 

  cout << "\n\n"; 
  return 0;
}


// ************************************  DEFINISJON AV FUNKSJONER  *************************************

char *lesTekst() {
  char *string;
  char buffer[15];

  cout << "\nVelg en tekst som skal permuteres, maks 15 tegn."
       << "\nDu kan ikke ha med mellomrom i ordet."
       << "\nValg: ";

  cin.getline(buffer, 15);
  string = new char[strlen(buffer) + 1];
  strcpy(string, buffer);
  return string; 
}

int factorialIterativ(int n) {                                      // Regner ut factorial av n (N!).
  int tall = n;

  for (int i = n; i > 1; i--)                                       // Telles ned fra n til 2.
    tall = tall * (i - 1);                                          // ganger "n" med tallet under "n" (N * (N-1)).

  return tall;                                                      // Returnerer svaret. 
}

void permuter(char *tekst, int i) {                                 // Permuterer teksten.
  int len = strlen(tekst);
  int j = i+1;

  if (i == len-1) {                                                 // Hvis permutering har nådd siste bokstav.
    if (testTekst(tekst)) {                                         // Sjekkes om permuteringen er lovelig i følge oppgaven (del 1).
      cout << "\n  Permutering ";                                   // Skriver ut teksten etter en permutasjon er utført.  
      permNr++;                                                     // Plusser på antall permuteringer.
      if (permNr < 10)                                              // Legger pp 0 foran tall under 10.
        cout << "0";
      cout << permNr << ": " << tekst;

      if (permNr % 24 == 0) {                                       // Bruker må skrive en tast for å fortsette etter hver 24. utskrift. 
        cout << "\n\n  Skriv inn et tegn for a fortsette ";
        cin.ignore();
        cin.get();
      }
    }
  }
  else {
    permuter(tekst, i+1);                                           // Starter med å permutere den første bokstaven.
    for (; j < len; j++) {                                          // Looper gjennom alle bokstavene.
      tekst = swap(tekst, i, j);                                    // Bytter plass på bokstav i indeks "i" med bokstav i indeks "j".
      permuter(tekst, i+1);                                         // Permuterer igjen med inkrementert indeks for "i".
      tekst = swap(tekst, j, i);                                    // Flytter den gjeldene bokstaven bak en posisjon.
    }
  }
}

char *swap(char *tekst, int i, int j) {                             // Bytter plass for element i indeks "i" med element i indeks "j".
  char *nyTekst;
  char b1, b2;

  b1 = tekst[i];                                                    // Lagrer unna innholdet i indeks "i".
  b2 = tekst[j];                                                    // Lagrer unna innholdet i indeks "j".

  nyTekst = tekst;                                                  // Tar en kopi av teksten.
  nyTekst[i] = b2;                                                  // Setter indeks "i" til å holde det som opprinnelig var i indeks "j".
  nyTekst[j] = b1;                                                  // Setter indeks "j" til å holde det som opprinnelig var i indeks "i".

  return nyTekst;                                                   // Returnerer den nye teksten etter at elementene har byttet plass.
}

void insertListe(char *tekst) {                                     // Legger til en node med teksten "tekst" fremst i listen.
  node *newNode = new node;                                         // Lager en ny node.

  newNode->next = head->next;                                       // Den nye noden peker på hva head peker på.
  head->next = newNode;                                             // Head peker på den nye noden.
  strcpy(newNode->ord, tekst);                                      // Kopierer teksten over i noden.
}

void displayListe(node *r) {                                        // Skriver ut innholdet av listen.
  cout << "\n\nInnhold i listen: \n";
  while (r != z) {                                                  // Så lenge den gjeldene noden ikke er z (slutt noden).
    cout << ' ' << r->ord << ' ';                                   // Skriv ut ordet.
    r = r->next;                                                    // Beveger seg til høyre.
  }
}

bool testTekst(char *tekst) {                                       // Tester de forskjellige conditionene beskrevet i av oppgaven.
  if (toLikeVokaler(tekst))                                         // 1-a.
    return false;

  if (treVokaler(tekst))                                            // 1-b.
    return false; 

  if (treLikeKonsonanter(tekst))                                    // 1-c.
    return false;

  if (fireKonsonanter(tekst))                                       // 1-d.
    return false;

  if (toLikeBokstaveriStarten(tekst))                               // 1-e.
    return false;

  if (finnesiListe(tekst))                                          // 2.
    return false;
  else
    insertListe(tekst);                                             // Legger til i listen over gyldige permuterte ord.

  return true;                                                      // Returnerer true hvis ingen av testene feilet.
}

bool erVokal(char *tekst, int i) {                                  // Sjekkor om bokstaven i indeks "i" er en vokal.
  char b = tekst[i];
  b = toupper(b); 

  if (b == 'A' || b == 'E' || b == 'I' || b == 'O' || b == 'U' || 
      b == 'Y' || b == 'Æ' || b == 'Ø' || b == 'Å')
    return true; 
  else 
    return false;                                                   // Returnerer false hvis bokstaven ikke er en vokal.
}

bool erKonsonant(char *tekst, int i) {                              // Sjekker om bokstav i indeks "i" er en konsonant.
  char b = tekst[i];
  b = toupper(b);

  if (b == 'B' || b == 'C' || b == 'D' || b == 'F' || b == 'G' || 
      b == 'H' || b == 'J' || b == 'K' || b == 'L' || b == 'M' || 
      b == 'N' || b == 'P' || b == 'Q' || b == 'R' || b == 'S' || 
      b == 'T' || b == 'V' || b == 'W' || b == 'X' || b == 'Z')
    return true; 
  else 
    return false;                                                   // Returnerer false hvis bokstaven ikke er en konsonant.
}

bool toLikeVokaler(char *tekst) {                                   // Sjekker om (1-a) to like vokaler kommer etter hverandre.
  int len = strlen(tekst);                                                 

  for (int i = 0; i < len-1; i++) {                                 // Looper gjennom teksten og sjekker alle bokstavene utenom siste.
    if (tekst[i] == tekst[i+1]) {                                   // Hvis gjeldene bokstav er lik som den etterfølgende.
      if (erVokal(tekst, i))                                        // Sjekker om bokstaven er en vokal.
        return true;                                                // Returnerer true hvis bokstavene er vokaler.
    }
  }
  return false;                                                     // Returnerer false hvis utsagnet ikke stemmer.
}

bool treVokaler(char *tekst) {                                      // Sjekker om (1-b) tre vokaler kommer etter hverandre. 
  int len = strlen(tekst);
  for (int i = 0; i < len-2; i++) {                                 // Looper til lengden -2, som betyr ikke de 2 siste bokstavene, disse skal sjekkes under.
    if (erVokal(tekst, i) && erVokal(tekst, i+1)
        && erVokal(tekst, i+2))                                     // Hvis gjeldene bokstav, og de 2 neste bokstavene er vokaler:
      return true;                                                  //  Så returneres true.
  }

  return false;                                                     // Returnerer false hvis utsagnet ikke stemmer.
}

bool treLikeKonsonanter(char *tekst) {                              // Sjekker om (1-c) tre like konsonanter kommer etter hverandre.
  int len = strlen(tekst);

  for (int i = 0; i < len-2; i++) {
    if (tekst[i] == tekst[i+1] && tekst[i] == tekst[i+2]) {         // Sjekker om bokstav i indeks "i" er lik de 2 ettefølgende bokstavene.
      if (erKonsonant(tekst, i)) {                                  // Sjekker om bokstaven er en konsonant.
        return true;                                                // Hvis det er en konsonant, så vet vi at det er 3 like konsonanter etter hverandre.
      }
    }
  }

  return false;                                                     // Returnerer false hvis utsagnet ikke stemmer.
}

bool fireKonsonanter(char *tekst) {                                 // Sjekker om (1-d) fire konsonanter kommer etter hverandre.
  int len = strlen(tekst);

  for (int i = 0; i < len-3; i++) {                                 // Looper til lengde -3, som betyr ikke de 3 siste bokstavene, disse sjekkes under.
    if (erKonsonant(tekst, i) && erKonsonant(tekst, i+1) &&
        erKonsonant(tekst, i+2) && erKonsonant(tekst, i+3))         // Hvis gjeldende bokstav, og de 3 neste bokstavene er konsonanter:
      return true;                                                  //  så returneres true.
  }

  return false;                                                     // Returnerer false hvis utsagnet ikke stemmer.
}

bool toLikeBokstaveriStarten(char *tekst) {                         // Sjekker om (1-e) to like bokstaver (vokaler eller konsonanter) starter et ord.
  if (strlen(tekst) >= 2) {                                         // Hvis teksten har misnt 2 bokstaver:
    if (tekst[0] == tekst[1])                                       // Hvis første og andre bokstav er like:
      return true;                                                  // Returnerer true.
  }
  return false;                                                     // Returnerer false hvis utsagnet ikke stemmer.
}
                                
bool finnesiListe(char *tekst) {                                    // Sjekker om (2) ordet har blit skrevet ut før (om det finnes i listen).
  node *r = new node;
  r = head->next;

  while (r != z) {
    if (strcmp(r->ord, tekst) == 0)                                 // Sammenligner teksten til noden og den medsendte teksten.
      return true;                                                  // Hvis de er like, returnerer true.
    r = r->next;                                                    // Blar seg videre til neste node.
  }
  return false;                                                     // Hvis ingen like tekster ble funnet, returnerer false.
}

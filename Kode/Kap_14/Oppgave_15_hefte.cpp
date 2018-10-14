/*
      Algoritmiske metoder          -     Kapittel 14 - Oppgave 15 fra hefte.
      Mats Ove Mandt Skjærstein     -     Bitsec.

      Søking i et binært tree.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS                                     // Fjerner sikkerhetsvarsler. 


//  INCLUDE:
#include <iostream>                                                 // cin, cout.
#include <iomanip>                                                  // setw.

using namespace std;


//  CONST:
const char itemMIN = char(0);                                       // Den minste "Key-en" mulig.
      char infoNIL[] = "Z-noden";                                   // "Informasjon" til z-noden (failed søk).


//  TYPEDEF:
typedef char itemtype;                                              // Definert som en enkelt char.
typedef char* infotype;                                             // Definert som char peker (aka. tekst).


//  KLASSER:
class BinTree {                                                     // Klassen for binære trær.
  private:
    struct node {                                                   // En node er private, implementert som struct. 
      itemtype key;
      infotype info;
      node *l, *r;
      node(itemtype k, infotype i, node *ll, node *rr) {
        key = k;
        info = i;
        l = ll; r = rr; 
      }
    };
    node *head, *z;

  public:
    BinTree();                                                      // Constructor, tar seg av oppretting av head og z i bin treet.
    ~BinTree();                                                     // Deconstructor til klassen.
    infotype search(itemtype v);                                    // Søker etter en key, returnerer infoen til keyen, eller infoNILL.
    void insert(itemtype v, infotype info);                         // Legger in en ny node, opprettholder bin-tre strukturen.
    void remove(itemtype v);                                        // Fjerner en node fra treet, opprettholder bin-tre strukturen.

    void finnHoyde(node *n);                                        // Finner høyden på treet.
    void displayLevel(node *n, int level);                          // Skriver ut noder i riktig level (høyde).
    void display(node *n, int indent = 0);                          // Skriver ut det binære treet.
    void displayKaller();                                           // Funksjon for å kalle "display" fra main.
};


//  GLOBALE VARIABLER:
int hoyde = 0, maksHoyde = 0, levelIndent = 0;                      // Høyde på treet og antall interne noder (levelIndent).


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  BinTree treNode; 
  char tekst[16];
  strcpy(tekst, "MGTDJQWAEHLOSVY");

  for (int i = 0; i < 15; i++)                                      // Fyller treet. 
    treNode.insert(tekst[i], "Node med info");                      // Placeholder info. 
  
  cout << "\nUtskrift av binary tree:\n\n";
  treNode.displayKaller();                                          // Skriver ut treet.

  cout << "\n\nSletter 'T'\n\n";
  treNode.remove('T');
  treNode.displayKaller();                                          // Skriver ut treet.

  cout << "\n\nSletter 'G'\n\n";
  treNode.remove('G');
  treNode.displayKaller();                                          // Skriver ut treet.

  cout << "\n\nSoker etter A\n"
       << "  Resultat: " << treNode.search('A');

  cout << "\n\nSoker etter F\n"
       << "  Resultat: " << treNode.search('F');

  cout << "\n\n";
  return 0;
}


// ************************************  DEFINISJON AV KLASSEFUNKSJONER  *******************************

BinTree :: BinTree() {                                              // Constructor, tar seg av oppretting av head og z i bin treet.
  z = new node(0, infoNIL, 0,0);
  head = new node(itemMIN, 0, 0, z);
}

BinTree :: ~BinTree() {                                             // Deconstructor til klassen.
}

infotype BinTree :: search(itemtype v) {                            // Søker etter en key, returnerer infoen til keyen, eller infoNILL.
  node *x = head->r;                                                // node x for å traversere treet, x = rota.
  z->key = v;                                                       // Kopierer søkeordet (key-en) i z sin key.
  while (v != x->key)                                               // Looper så lenge riktig node ikke er funnet.
    x = (v < x->key) ? x->l : x->r;                                 // Hvis "min key(v)" er mindre enn den noden jeg besøker, gå videre til venstre.
                                                                    // Hvis ikke, så gå videre til høyre. 
  return x->info;                                                   // Når "while" stopper, så har vi funnet den korrekte noden, eller z noden. 
                                                                    // Returnerer da info (teksten) den inneholder. 
}

void BinTree :: insert(itemtype v, infotype info) {                 // Legger in en ny node, opprettholder bin-tre strukturen.
  node *p, *x;                                                      // p(parrent) og x(den jeg besøker) node pekere.
  p = head; x = head->r;                                            // x = rota, og p er "parrent" til x. 
  while (x != z) {                                                  // Så lenge den noden jeg er på ikke er z:
    p = x;                                                          // Flytt p(parrent) peker til x(den jeg besøker).
    x = (v < x->key) ? x->l : x->r;                                 // Hvis "min key(v)" er mindre enn "den jeg besøker(x)" sin key, gå mot venstre.
                                                                    // Hvis ikke, gå mot høyre. (oppdaterer x til å være denne "left/right" barnet".
  }
                                                                    // Nå som vi er ferdige med while, har vi funnet hvilke parrent som kan
                                                                    // ha den nye key-en under seg.
  x = new node(v, info, z, z);                                      // Lager en ny node med v og info fra parameter. 
  if (v < p->key)                                                   // Hvis "min key(v)" er mindre enn "parrent(p)" sin key, sett den nye
    p->l = x;                                                       //  noden på venstre siden. (fordi den er mindre enn parrent).
  else                                                              
    p->r = x;                                                       // Hvis ikke, sett den nye noden på høyre siden. (større eller lik parrent key). 
}

void BinTree :: remove(itemtype v) {                                // Fjerner en node fra treet, opprettholder bin-tre strukturen.
  node *c, *p, *x, *t;                                              
  z->key = v;                                                       // Kopierer over key-en som skal finnes i z sin key.
  p = head; x = head->r;                                            // p = parrent, x = den noden jeg besøker. 
  while (v != x->key) {                                             // Så lenge noden med key-en jeg skal slette ikke er den jeg er på nå:
    p = x;                                                          // Sett parrent til å være den jeg besøker.
    x = (v < x->key) ? x->l : x->r;                                 // Gå videre til venstre hvis key-en er mindre enn den jeg besøker,
                                                                    //  gå til høyre vis ikke. 
  
  }                                                                 // Når while loopen er ferdig, er den noden som skal slettes x, eller x er en z node.

  t = x;                                                            // Ta kopi av den noden jeg er på.

  if (t->r == z)                                                    // Hvis "mitt" høyre "barn" er z:
    x = x->l;                                                       // Gå til venstre.
  else if (t->r->l == z) {                                          // Hvis "mitt" høyre "barn" sitt venstre "barn" er z:
    x = x->r;                                                       // Gå til høyre (en ned), og 
    x->l = t->l;                                                    // Sett "mitt" venstre "barn" til å være min "parrent" sitt venstre "barn". 
  }
  else {                                                            // Hvis hverken den høyre barnet er z, eller det høyerets venstre barn er z:
    c = x->r;                                                       // Ta kopi av den høyre barnet.
    while (c->l->l != z)                                            // Så lenge "mitt høyre barn" sitt venstre "barn" sitt venstre "barn" ikke er z:
      c = c->l;                                                     // La "mitt barn" bevege seg ned til venstre.
    
    x = c->l; c->l = x->r;                                          // Sett "meg(x)" til å være c sin venstre og c sin venstre til å være "min(x)" høyre.
    x->l = t->l; x->r = t->r;                                       // Sett "min(x)" sin venstre til å være "den gamle kopien av meg(t)" sin venstre.
                                                                    //  og "min(x)" sin høyre til å være "den gamle kopien av meg(t)" sin høyre.
  }

  delete t;                                                         // Sletter "den gamle kopien(t)" (aka den som noden som skulle slettes).
  if (v < p->key)                                                   // Hvis Key-en som skal slettes er mindre enn "parrent(p)" sin key:
    p->l = x;                                                       // La "meg(x)" være "parrent(p)" sitt venstre barn.
  else                                                              // Hvis ikke:
    p->r = x;                                                       // La "meg(x)" være "parrent(x)" sitt høyre barn.
}

void BinTree :: finnHoyde(node *n) {                                // Finner høyden på treet. 
  hoyde++;                                                          // Teller opp høyden.
  levelIndent++;                                                    // Teller også antall interne noder, skal brukes i display funksjon.

  if (n != z) {                                                     // Traverserer treet på en postorder måte.
    if (n->l != z) finnHoyde(n->l);                                 // Går til venstre i treet.
    if (n ->r != z) finnHoyde(n->r);                                // Går til høyre i treet.
    if (hoyde > maksHoyde) maksHoyde = hoyde;                       // Oppdaterer makshøyde hvis ny makshøyde er funnet.
  }

  hoyde--;                                                          // Teller så ned høyden, når den rekursive funksjonen går "bakover/opp" i treet.
} 

void BinTree :: displayLevel(node *n, int level) {                  // Skriver ut noder i riktig level (høyde).
  if (n != z) { 
    if (level == 1) {                                               // Når riktig "level" (høyde) er nådd, skriv ut.
      cout << n->key << " ";                                        // Skriver ut Key-en.
      for (int i = 1; i <= levelIndent*2; i++)                      // Skriver ut mellomrom mellon alle "key-er" på samme level.
        cout << " ";                                                //  skal være samme som før kallet skjedde (*2 pga. /2). 
    }
    else {
      if (n->l != z) displayLevel(n->l, level-1);                   // Går til venstre, og minimerer "level"(høyde) med 1.
      if (n->r != z) displayLevel(n->r, level-1);                   // Går til høyre, og minimerer "level"(høyde) med 1.
    }
  }
}

void BinTree :: display(node *n, int indent) {                      // Skriver ut det binære treet.
  for (int i = 1; i <= maksHoyde; i++) {                            // Skriver ut på en level-order måte.
    
    for (int i = 1; i <= levelIndent; i++)                          // Legger på mellomrom foran key-en.
      cout << " ";

    displayLevel(n, i);                                             // Kaller funksjon for å skrive ut key-en.

    levelIndent = levelIndent/2;                                    // Reduserer "mellomrom" størrelsen til halvparten.
    cout << "\n";
  }
}

void BinTree :: displayKaller() {                                   // Funksjon for å kalle "display" fra main.
  finnHoyde(head->r);                                               // Finner høyden på treet (og ant. interne noder).
  display(head->r);                                                 // Skriver ut det binære treet.
}



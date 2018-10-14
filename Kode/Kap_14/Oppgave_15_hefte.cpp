/*
      Algoritmiske metoder          -     Kapittel 14 - Oppgave 15 fra hefte.
      Mats Ove Mandt Skj�rstein     -     Bitsec.

      S�king i et bin�rt tree.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS                                     // Fjerner sikkerhetsvarsler. 


//  INCLUDE:
#include <iostream>                                                 // cin, cout.
#include <iomanip>                                                  // setw.

using namespace std;


//  CONST:
const char itemMIN = char(0);                                       // Den minste "Key-en" mulig.
      char infoNIL[] = "Z-noden";                                   // "Informasjon" til z-noden (failed s�k).


//  TYPEDEF:
typedef char itemtype;                                              // Definert som en enkelt char.
typedef char* infotype;                                             // Definert som char peker (aka. tekst).


//  KLASSER:
class BinTree {                                                     // Klassen for bin�re tr�r.
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
    infotype search(itemtype v);                                    // S�ker etter en key, returnerer infoen til keyen, eller infoNILL.
    void insert(itemtype v, infotype info);                         // Legger in en ny node, opprettholder bin-tre strukturen.
    void remove(itemtype v);                                        // Fjerner en node fra treet, opprettholder bin-tre strukturen.

    void finnHoyde(node *n);                                        // Finner h�yden p� treet.
    void displayLevel(node *n, int level);                          // Skriver ut noder i riktig level (h�yde).
    void display(node *n, int indent = 0);                          // Skriver ut det bin�re treet.
    void displayKaller();                                           // Funksjon for � kalle "display" fra main.
};


//  GLOBALE VARIABLER:
int hoyde = 0, maksHoyde = 0, levelIndent = 0;                      // H�yde p� treet og antall interne noder (levelIndent).


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

infotype BinTree :: search(itemtype v) {                            // S�ker etter en key, returnerer infoen til keyen, eller infoNILL.
  node *x = head->r;                                                // node x for � traversere treet, x = rota.
  z->key = v;                                                       // Kopierer s�keordet (key-en) i z sin key.
  while (v != x->key)                                               // Looper s� lenge riktig node ikke er funnet.
    x = (v < x->key) ? x->l : x->r;                                 // Hvis "min key(v)" er mindre enn den noden jeg bes�ker, g� videre til venstre.
                                                                    // Hvis ikke, s� g� videre til h�yre. 
  return x->info;                                                   // N�r "while" stopper, s� har vi funnet den korrekte noden, eller z noden. 
                                                                    // Returnerer da info (teksten) den inneholder. 
}

void BinTree :: insert(itemtype v, infotype info) {                 // Legger in en ny node, opprettholder bin-tre strukturen.
  node *p, *x;                                                      // p(parrent) og x(den jeg bes�ker) node pekere.
  p = head; x = head->r;                                            // x = rota, og p er "parrent" til x. 
  while (x != z) {                                                  // S� lenge den noden jeg er p� ikke er z:
    p = x;                                                          // Flytt p(parrent) peker til x(den jeg bes�ker).
    x = (v < x->key) ? x->l : x->r;                                 // Hvis "min key(v)" er mindre enn "den jeg bes�ker(x)" sin key, g� mot venstre.
                                                                    // Hvis ikke, g� mot h�yre. (oppdaterer x til � v�re denne "left/right" barnet".
  }
                                                                    // N� som vi er ferdige med while, har vi funnet hvilke parrent som kan
                                                                    // ha den nye key-en under seg.
  x = new node(v, info, z, z);                                      // Lager en ny node med v og info fra parameter. 
  if (v < p->key)                                                   // Hvis "min key(v)" er mindre enn "parrent(p)" sin key, sett den nye
    p->l = x;                                                       //  noden p� venstre siden. (fordi den er mindre enn parrent).
  else                                                              
    p->r = x;                                                       // Hvis ikke, sett den nye noden p� h�yre siden. (st�rre eller lik parrent key). 
}

void BinTree :: remove(itemtype v) {                                // Fjerner en node fra treet, opprettholder bin-tre strukturen.
  node *c, *p, *x, *t;                                              
  z->key = v;                                                       // Kopierer over key-en som skal finnes i z sin key.
  p = head; x = head->r;                                            // p = parrent, x = den noden jeg bes�ker. 
  while (v != x->key) {                                             // S� lenge noden med key-en jeg skal slette ikke er den jeg er p� n�:
    p = x;                                                          // Sett parrent til � v�re den jeg bes�ker.
    x = (v < x->key) ? x->l : x->r;                                 // G� videre til venstre hvis key-en er mindre enn den jeg bes�ker,
                                                                    //  g� til h�yre vis ikke. 
  
  }                                                                 // N�r while loopen er ferdig, er den noden som skal slettes x, eller x er en z node.

  t = x;                                                            // Ta kopi av den noden jeg er p�.

  if (t->r == z)                                                    // Hvis "mitt" h�yre "barn" er z:
    x = x->l;                                                       // G� til venstre.
  else if (t->r->l == z) {                                          // Hvis "mitt" h�yre "barn" sitt venstre "barn" er z:
    x = x->r;                                                       // G� til h�yre (en ned), og 
    x->l = t->l;                                                    // Sett "mitt" venstre "barn" til � v�re min "parrent" sitt venstre "barn". 
  }
  else {                                                            // Hvis hverken den h�yre barnet er z, eller det h�yerets venstre barn er z:
    c = x->r;                                                       // Ta kopi av den h�yre barnet.
    while (c->l->l != z)                                            // S� lenge "mitt h�yre barn" sitt venstre "barn" sitt venstre "barn" ikke er z:
      c = c->l;                                                     // La "mitt barn" bevege seg ned til venstre.
    
    x = c->l; c->l = x->r;                                          // Sett "meg(x)" til � v�re c sin venstre og c sin venstre til � v�re "min(x)" h�yre.
    x->l = t->l; x->r = t->r;                                       // Sett "min(x)" sin venstre til � v�re "den gamle kopien av meg(t)" sin venstre.
                                                                    //  og "min(x)" sin h�yre til � v�re "den gamle kopien av meg(t)" sin h�yre.
  }

  delete t;                                                         // Sletter "den gamle kopien(t)" (aka den som noden som skulle slettes).
  if (v < p->key)                                                   // Hvis Key-en som skal slettes er mindre enn "parrent(p)" sin key:
    p->l = x;                                                       // La "meg(x)" v�re "parrent(p)" sitt venstre barn.
  else                                                              // Hvis ikke:
    p->r = x;                                                       // La "meg(x)" v�re "parrent(x)" sitt h�yre barn.
}

void BinTree :: finnHoyde(node *n) {                                // Finner h�yden p� treet. 
  hoyde++;                                                          // Teller opp h�yden.
  levelIndent++;                                                    // Teller ogs� antall interne noder, skal brukes i display funksjon.

  if (n != z) {                                                     // Traverserer treet p� en postorder m�te.
    if (n->l != z) finnHoyde(n->l);                                 // G�r til venstre i treet.
    if (n ->r != z) finnHoyde(n->r);                                // G�r til h�yre i treet.
    if (hoyde > maksHoyde) maksHoyde = hoyde;                       // Oppdaterer maksh�yde hvis ny maksh�yde er funnet.
  }

  hoyde--;                                                          // Teller s� ned h�yden, n�r den rekursive funksjonen g�r "bakover/opp" i treet.
} 

void BinTree :: displayLevel(node *n, int level) {                  // Skriver ut noder i riktig level (h�yde).
  if (n != z) { 
    if (level == 1) {                                               // N�r riktig "level" (h�yde) er n�dd, skriv ut.
      cout << n->key << " ";                                        // Skriver ut Key-en.
      for (int i = 1; i <= levelIndent*2; i++)                      // Skriver ut mellomrom mellon alle "key-er" p� samme level.
        cout << " ";                                                //  skal v�re samme som f�r kallet skjedde (*2 pga. /2). 
    }
    else {
      if (n->l != z) displayLevel(n->l, level-1);                   // G�r til venstre, og minimerer "level"(h�yde) med 1.
      if (n->r != z) displayLevel(n->r, level-1);                   // G�r til h�yre, og minimerer "level"(h�yde) med 1.
    }
  }
}

void BinTree :: display(node *n, int indent) {                      // Skriver ut det bin�re treet.
  for (int i = 1; i <= maksHoyde; i++) {                            // Skriver ut p� en level-order m�te.
    
    for (int i = 1; i <= levelIndent; i++)                          // Legger p� mellomrom foran key-en.
      cout << " ";

    displayLevel(n, i);                                             // Kaller funksjon for � skrive ut key-en.

    levelIndent = levelIndent/2;                                    // Reduserer "mellomrom" st�rrelsen til halvparten.
    cout << "\n";
  }
}

void BinTree :: displayKaller() {                                   // Funksjon for � kalle "display" fra main.
  finnHoyde(head->r);                                               // Finner h�yden p� treet (og ant. interne noder).
  display(head->r);                                                 // Skriver ut det bin�re treet.
}



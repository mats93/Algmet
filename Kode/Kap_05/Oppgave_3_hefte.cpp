/*
      Algoritmiske metoder          -   Kapittel 5 - Oppgave 3 fra hefte.
      Mats Ove Mandt Skj�rstein     -   Bitsec.

      Bygger et bin�rt tree fra et postfix utrykk, bruker en stack til dette.
      Traverserer treet p� en post-roder m�te (rekursivt).
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////


//  INCLUDE:
#include <iostream>                                                 // cin, cout.

using namespace std;


//  STRUCT:
struct node {                                                       // Struct til � bygge tre.
  char info;
  node *l, *r;
};


//  TYPEDEF:
typedef node *itemtype;                                             // Definert som en node av type struct.


//  KLASSER:
class Stack {                                                       // Stack klasse med array.
  private:
   itemtype *stack;
   int p;

  public:
    Stack(int max = 100);
    Stack();
    void push(itemtype v);
    itemtype pop();
    int empty();
};


//  DEKLARASJON AV FUNKSJONER:
void byggParseTree(char c);                                         // Bygger parse treet.

void antInterneNoder(node *r);                                      // Antall internal-noder i et bin�rt tre.
void antEksterneNoder(node *r);                                     // Antall external-noder i et bin�rt tre.
void antFulleNoder(node *r);                                        // Antall fulle noder i et bin�rt tre (som har to internal-noder).
void finnHoyde(node *r);                                            // Finner treets h�yde. 


//  GLOBALE VARIABLER:
Stack stack(50);
node *newNode, *z;
int interneNoder = 0, eksterneNoder = 0, fulleNoder = 0;            // Brukes til � finne ant av diverse noder.
int hoyde = 0, maksHoyde = 0;                                       // Brukes til � finne maks h�yden til treet. 


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  char c;
  node *root; 

  z = new node;
  z->l = z;
  z->r = z;

  cout << "\nSkriv inn et postfix uttrykk (eks.: ABC+DE**F+*): ";
  while ((c = cin.get()) != '\n') {                                 // Looper gjennom alle bokstaver p� linjen.
    byggParseTree(c);                                               // Bygger treet med en og en bokstav / tegn. 
  }

  root = stack.pop();

  antInterneNoder(root);
  cout << "\nAntall internal-noder i treet: " << interneNoder;

  antEksterneNoder(root); 
  cout << "\nAntall external-noder i treet: " << eksterneNoder;

  antFulleNoder(root); 
  cout << "\nAntall fulle-noder i treet: " << fulleNoder;

  finnHoyde(root);
  cout << "\nHoyden til treet: " << maksHoyde;

  cout << "\n\n\n";
  return 0;
}


// ************************************  DEFINISJON AV KLASSEFUNKSJONER  *******************************

Stack::Stack(int max) {
  stack = new itemtype[max];                                        // Array av type "itemtpye".
  p = 0;                                                            // p er antall noder i arrayen (indeks til siste element i array, aka toppen av stacken). 
}

Stack::Stack() {
  delete[]stack;                                                   // Sletter arrayen.
}

void Stack::push(itemtype v) {
  stack[p++] = v;                                                   // Legger til noden sist i arrayen (�verst i stacken).
}

itemtype Stack::pop() {
  return stack[--p];                                                // Fjerner og returnerer den siste noden i arrayen (�verste i stacken).
}

int Stack::empty() {
  return !p;
}


// ************************************  DEFINISJON AV FUNKSJONER  *************************************

void byggParseTree(char c) {
  while (c == ' ')                                                  // Hopper over blanke.
    cin.get();

  newNode = new node;                                               // Lager en ny node.
  newNode->info = c;                                                // Setter verdien til det samme som param.
  newNode->l = z;                                                   // left og right peker p� z.
  newNode->r = z;

  if (c == '+' || c == '*') {                                       // Hvis param er + eller *:
    newNode->r = stack.pop();                                       // Setter h�yre node til � v�re forrige "push".
    newNode->l = stack.pop();                                       // Setter venstre node til � v�re to "pusher" siden. 
  }
  stack.push(newNode);                                              // Legger til noden p� stacken (N�r ferdig skal hele treet ligger her).
}

void antInterneNoder(node *r) {                                     // Antall internal-noder i et bin�rt tre.
  if (r != z) {                                                     // Traverserer op en post-order m�te.            
    antInterneNoder(r->l);
    antInterneNoder(r->r);
    interneNoder++;                                                 // Teller opp den globale verdien hver gang en node ikke er en z node.
  }
}

void antEksterneNoder(node *r) {                                    // Antall external-noder i et bin�rt tre.
  if (r != z) {                                                     // Traverserer p� en post-order m�te.
    antEksterneNoder(r->l);                                         // g�r til venstre.
    antEksterneNoder(r->r);                                         // g�r til h�yre n�r venstre er z.
  }
  else                                                              // Hvis node er z:
    eksterneNoder++;                                                // Teller opp ant. eksterne noder. 
}

void antFulleNoder(node *r) {                                       // Antall fulle noder i et bin�rt tre (som har to internal-noder).
  if (r != z) {                                                     // Traverserer p� en post-order m�te.
    antFulleNoder(r->l);
    antFulleNoder(r->r);
    if (r->l != z && r->r != z)                                     // Hvis noden ikke har z som venstre eller h�yre node, er noden full.
      fulleNoder++; 
  }
}

void finnHoyde(node *r) {                                           // Finner treets h�yde. 
  hoyde++;                                                          // Teller opp h�yden til treet n�r rekursjon g�r nedover.
  
  if (r != z) {                                                     // Traverser treet i post order.
    finnHoyde(r->l);
    finnHoyde(r->r); 
    if (hoyde > maksHoyde)                                          // Hvis h�yden registrert er st�rre enn den registrerte maks h�yden:
      maksHoyde = hoyde;                                            // Maks h�yden settes til den st�rste verdien.
  }
  
  hoyde--;                                                          // Teller ned h�yden til treet n�r rekusjonen faller tilbake til noden over.
}


/*
        Algoritmiske metoder        -   Kapittel 4 - Oppgave 1 fra hefte.
        Mats Ove Mandt Skj�rstein   -   Bitsec.

        Bygger et parse-tree for et postfix uttrykk, ved hjelp av en stack.
        Traverserer treet p� en pre-order m�te, ved hjelp av en stack.
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
    Stack(int max=100);
    Stack(); 
    void push(itemtype v);
    itemtype pop();
    int empty();
}; 


//  DEKLARASJON AV FUNKSJONER:
void byggParseTree(char c);                                         // Bygger parse treet.
void traverseTreePreorder();                                        // Traverserer treet og skriver ut rekkef�lgen i preorder.


//  GLOBALE VARIABLER:
Stack stack(50); 
node *newNode, *z; 


// ************************************  H O V E D P R O G R A M M E T  ********************************

int main() {
  char c; 
  
  z = new node; 
  z->l = z; 
  z->r = z; 

  cout << "\nSkriv inn et postfix uttrykk (eks.: ABC+DE**F+*): ";
  while ((c = cin.get()) != '\n') {                                 // Looper gjennom alle bokstaver p� linjen.
    byggParseTree(c);                                               // Bygger treet med en og en bokstav / tegn. 
  } 

  cout << "\nTraverserer parse treet pa en preorder mate: ";
  traverseTreePreorder();                                           // Traverserer treet (s� lenge den ligger p� stacken). 

  cout << "\n\n\n"; 
  return 0;
}


// ************************************  DEFINISJON AV KLASSEFUNKSJONER  *******************************

Stack :: Stack(int max) {
  stack = new itemtype[max];                                        // Array av type "itemtpye".
  p = 0;                                                            // p er antall noder i arrayen (indeks til siste element i array, aka toppen av stacken). 
}

Stack :: Stack() {
  delete []stack;                                                   // Sletter arrayen.
}

void Stack :: push(itemtype v) {
  stack[p++] = v;                                                   // Legger til noden sist i arrayen (�verst i stacken).
}

itemtype Stack :: pop() { 
  return stack[--p];                                                // Fjerner og returnerer den siste noden i arrayen (�verste i stacken).
}

int Stack :: empty() {
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

void traverseTreePreorder() {                                       // Rekkef�lge: Visit root, left, right.
  node *t;                                                          // En temp node.

  while (!stack.empty()){                                           // S� lenge stacken inneholder noder.
    t = stack.pop();                                                // Pop av noden som ligger �verst i stacken.
    cout << t->info << ' '; // visit.                               // Skriv ut verdien av noden (visit). 
    
    if (t->r != z)                                                  // S� lenge right node ikke er z:
      stack.push(t->r);                                             // Legg til right node p� stacken.
    if (t->l != z)                                                  // S� lenge left node ikke er z:
      stack.push(t->l);                                             // Legg til left node p� stacken.
  }
}
/*
      Algoritmiske metoder           -     Kapittel 5 - Oppgave 4 fra hefte.
      Mats Ove Mandt Skj�rstein      -     Bitsec.

      Bygger et bin�rt tree fra et postfix utrykk, bruker en stack til dette.
      Regner ut svaret.
      Traverserer treet p� en post-order m�te (rekursivt).
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
void byggParseTree(char c);                                         // Bygger parse treet for et postfix uttrykk.
char visit(char bokstav);
void traverserPreorder(node *r);                                    // Traverser treet rekursivt p� en pre order m�te.
int regnUtTree(itemtype r);                                         // Tar et parse tree for som har et postfix uttrykk, regner ut svaret.

void skrivUtTree(node *r, int valg);                                // Skriver ut treet p� Preorder (1), inorder (2) eller postorder (3).

//  GLOBALE VARIABLER:
Stack stack(50);
node *newNode, *z;


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
  traverserPreorder(root); 

  cout << "\nTraverst i pre order:  ";
  skrivUtTree(root, 1);

  cout << "\nTraverst i inorder:    ";
  skrivUtTree(root, 2);

  cout << "\nTraverst i post order: ";
  skrivUtTree(root, 3);

  cout << "\nSummen er: " << regnUtTree(root);

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

void byggParseTree(char c) {                                        // Bygger parse treet for et postfix uttrykk.
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

char visit(char bokstav) {
  char valg; 

  do {                                                              // S� lenge tallet er - eller over 100:
    cout << "\nErstatt bokstaven " << bokstav 
         << " med et tall (1-100): ";
    cin >> valg;                                                    // Velger et nytt tall.
    return valg;
  } while (valg <= 0 || valg > 100);
}

void traverserPreorder(node *r) {                                   // Traverser treet rekursivt p� en pre order m�te.
  if (r != z) {
    if (r->info != '+' && r->info != '*')                           // Hvis det er en bokstav.
      r->info = visit(r->info);                                     // Endrer bokstaven.
    
    traverserPreorder(r->l);
    traverserPreorder(r->r);
  }
}

int regnUtTree(itemtype r) {                                        // Tar et parse tree for som har et postfix uttrykk, regner ut svaret.
  if (r != z) {
    if (r->info == '+')                                             // Hvis node er +:
      return regnUtTree(r->l) + regnUtTree(r->r);                   // Regner ut venstre side, s� plusser den med h�yre side.
    else if (r->info == '*')
      return regnUtTree(r->l) * regnUtTree(r->r);
    else 
      return r->info -'0';                                          // Gj�r om char til int.
  }
}

void skrivUtTree(node *r, int valg) {                               // Skriver ut treet p� Preorder (1), inorder (2) eller postorder (3).
  
  if (r != z) {
    switch (valg) {
      case 1: cout << " " << r->info;
        skrivUtTree(r->l, 1);
        skrivUtTree(r->r, 1);
        break;

      case 2: skrivUtTree(r->l, 2);
        cout << " " << r->info;
        skrivUtTree(r->r, 2);
        break;

      case 3: skrivUtTree(r->l, 3);
        skrivUtTree(r->r, 3);
        cout << " " << r->info;
        break; 

      default: cout << "\nFeil medsent paramater for funksjonen 'skrivUtTree()'";
               break;
    }
  }
}

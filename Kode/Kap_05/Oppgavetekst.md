# Oppgavetekst

## Oppgave 2 (kap.5)

Funksjonen aller øverst s.52 i læreboka regner ut 'N!' på en rekursiv måte.
Skriv en funksjon som regner ut 'N!' på en iterativ måte.

## Oppgave 3 (kap.5)

Lag (rekursive) funksjoner som:

- finner antall (interne) noder i et binært tre.
- antall external-noder i et binært tre.
- antall fulle noder i et binært tre (som har to internal-noder).
- finner treets høyde

Alle funksjonene tar en node-peker (root) som input-parameter. Funksjonene skal enten
returnere med en int som svar, eller at de oppdaterer en global variabel.

**Starthjelp:**
Bruk koden fra OPPG_01.CPP til å generere et binært tre fra et postfix uttrykk
(som du taster inn). Test funksjonene mot dette treet.

## Oppgave 4 (kap.5)

Bruk koden fra OPPG_01.CPP til å generere et binært tre fra et postfix uttrykk
(som du taster inn).

Traverser (og skriv ut) dette treet rekursivt på en preorder, inorder og postorder måte
( **hint** s.60).

Traverser så dette treet på en rekursiv postorder måte, der:

- brukeren for hver bokstav i treet blir bedt om å erstatte bokstaven med et tall.
- programmet skriver ut svaret på det regnstykket som når oppstår.

**Hint:** Regn ut verdien til venstre subtre, og adder/multipliser dette med verdien av det
høyre subtreet.

## Oppgave 8 (kap.5) - tidligere obligatorisk oppgave nr.2

**Innledning:**
Av og til kommer man over oppgaver (i aviser, blader o.l.) som går ut på å endre rekkefølgen
på bokstaver, slik at man får et meningsfullt ord, f.eks. stedsnavn eller et yrke. "BERGEN"
kunne ha vært skrevet som "GEERBN", eller "HEISMONTØR" som "TØRMISNEHO".

**Oppgaven:**
Denne oppgaven går ut på å lese inn en tekst (max.15 tegn), og generere alle kombinasjoner/
permutasjoner av disse bokstavene.

En tekst på N bokstaver, vil jo som kjent ha N! ulike permutasjoner. For å sile vekk
(avskjære) noen av alternativene så skal programmet ikke skrive ut ord der:

1) a: to like vokaler kommer etter hverandre.
b: tre vokaler kommer etter hverandre.
c: tre like konsonanter kommer etter hverandre.
d: fire konsonanter kommer etter hverandre
(vi ser altså helt bort fra sammensatte ord, som f.eks: «angstskrik»).
e: to like bokstaver (vokaler eller konsonanter) starter et ord.

2) ett tegn havner i en posisjon der et identisk tegn allerede har vært.
(F.eks. i ordet "BIRI" vil ombytte av 'I'ene være uinteressant.)

Output fra programmet skal være de permuterte ordene:

- Nummerert fra 1 og fortløpende oppover.
- Stans for hver 24.utskrift (og vent på at ett tegn blir skrevet/tastet inn)

**Eksempel:**
Ordet "SOLO" har egentlig 24 permutasjoner. Med avskjæringene ovenfor (pkt.1 og 2), så vil
kun 6 permutasjoner bli skrevet ut. Disse er merket med '*' nedenfor. Forklaring på hvorfor de
andre ikke skrives ut er å finne i høyre kolonne:

* SOLO


SOOL |


SLOO | Avskjæring 1a: To like vokaler etter hverandre


SLOO |


SOOL |


SOLO Avskjæring 2

* OSLO
* OSOL
* OLSO
* OLOS


OOSL Avskjæring 1e


OOLS Avskjæring 1e


LSOO Avskjæring 1a


LSOO Avskjæring 1a

* LOSO


LOOS Avskjæring 1a


LOSO Avskjæring 2


LOOS Avskjæring 1a


OSOL |


OSLO | Avskjæring 2: 'O' har allerede vært i 1.posisjon, og disse


OOSL | permutasjonene er allerede generert.


OOLS |


OLSO |


OLOS |

**Hint / tips / fremgangsmåte:**
Følgende måte å utvikle programmet på tilrådes:

```
A) Bygg på EKS_06.CPP (denne skal brukes). Endre denne slik at int(-arrayen) hele
veien blir erstattet med char(-array). Sørg for at innholdet i arrayen blir lest inn
fra tastaturet. Upcase alle bokstavene, også 'æ', 'ø' og 'å'.
```
B) Endre funksjonen 'display' slik at den ivaretar kravene til output.

C) Lag en funksjon 'navnOK(char a[], int len)' som sjekker at teksten "a" i de "len"
første posisjonene tilfredsstiller kravene i gitt i 1). Denne kalles fra "passelige"
steder inni funksjonen 'perm'. Funksjonen returnerer med '1' dersom navnet er OK,
ellers '0'.

D) Lag en funksjon som sjekker etter om en bokstav allerede har vært i en posisjon,
og som kalles et "passende" sted fra 'perm'. (Parametre og returverdi får du selv
finne ut.)

**Testing:**
Dersom programmet ditt fungerer helt korrekt med alle avskjæringer, så skal følgende ord gi
antall output som beskrevet i høyre kolonne:

OSLO 6 ULLA 10
SOLO 6 ULLU 3
LENA 24 ABBA 3
TOTEN 54 AABBA 1
HAMAR 36 AABBAB 4
GJØVIK 576 MISSISSIPPI 4673 (av 39.916.800 mulige!)

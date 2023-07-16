# Übung 2: Abstrakte Datentypen in Konkret

Diese Übung wird sich vor allem um die Implementierung und Anwendung der eingeführten Datentypen aus der VL drehen. 
Zusätzlich können Sie für einen nontrivialen Algorithmus den Korrektheitsbeweis führen.

## Aufgabe 1 - Stack Mit Linked List

> Dateien die innerhalb dieser Aufgabe editiert werden sollten:
>
> - `Stack.h`
> - `ex1.cpp`

Gegeben sei der folgende Abstrakte Datentyp (bekannt aus der VL):

```cpp
type Stack<T>:
    operators:
        empty -> Stack
        is_empty: Stack -> Bool
        push: Stack x T -> S
        pop: Stack -> Stack
        top: Stack -> T
    axioms:
        pop(push(S,x)) = S
        top(push(S,x)) = x
        is_empty(push(S,x)) = false
        is_empty(empty) = true
```

In der VL wurde Ihnen eine Implementierung vorgestellt in der ein Stack selbst seine Daten, mit Hilfe eines `arrays` verwaltet.
Ein Nachteil dieser Implementierungsform des Stacks ist das `arrays` grundsätzlich von **statischer** Kapazität sind und der Stack sich daher um die Speicherverwaltung kümmern muss.
Alternativ kann eine **Verkette Liste** (Linked List) eingesetzt werden, da diese eine Variable Länge hat.
Nun können wir aber nicht mehr ohne weiteres Abfragen wie groß der verbleibende Stapel ist.
Daher erweitern wir den oben genannten ADT um folgende Operatoren und Axiome:

```cpp
type Stack<T>:
    operators:
        ... # wie oben
        length: Stack -> int
    axioms:
        ... # wie oben
        length(empty) = 0
        length(push(S,x)) = length(S) + 1
```

Der hinzugefügte Operator erlaubt uns nun die Länge eines Stacks anzufragen.
Die beiden Axiome bilden ab das ein leerer Stack eine Länge von 0 haben sollte,
sowie das ein Stack dem ein Element angefügt wird um 1 größer wird.

> Warum reichen diese beiden Axiome?

**Aufgabe 1.1 (2p):** Erweitern Sie den Stack in `Stack.h` sodass er die neuen Axiome und operatoren unterstützt.

## Aufgabe 2. - Arithmetrische Ausdrücke Verarbeiten

> Dateien die in dieser Aufgabe editiert werden sollen:
>
> - arithmetric.cpp
> - repl.cpp

In dieser Aufgabe sollen Sie den implementierten Stack zur Auswertung von Arithmetischen Ausdrücken verwenden. 
Ein Arithmetischer Ausdruck sei eine Zeichenfolge bestehend aus Gleitkommazahlen, Operatoren sowie runden Klammern.
Beispiel für einen solchen Ausdruck wäre:

```infix-notation

(2.0 * 3.0 + (2.0 / 4.0)) * 7.0
```

> ( ) + - * /
> sowie Gleitkommazahlen mit Dezimalpunkt
> als Trenzeichen zwischen "Tokens" kommen Leertasten zum Einatz

Um die Auswertung zu vereinfachen sollen Sie zu aller erst den Arithmetischen Ausdruck von der gebräuchlichen *Infix-Notation* in die *Postfix-Notation* (auch umgekehrte polnische Notation genannt) überführen.
In der Postfix-Notation sind die Operanden **nach** den Argumenten genannt, wodurch Klammersetzung überflüssig wird.
Dabei würde das Beispiel von oben wie folgt abgebildet werden:

```postfix-notation
	2.0 3.0 * 2.0 4.0 / + 7.0 *
```

**Aufgabe 2.1 (4p):** Implementieren Sie in `arithmetic.cpp::infix_to_postfix` den Shunting-yard Algorithmus um einen Ausdruck in Infix-Notation in Postfix-Notation umzuwandeln.

Der Shunting-yard Algorithmus funktioniert wie folgt:

```julia
Eingabe: string von tokens, gleitkommazahlen separiert durch " "
S = Stack
Q = Queue
while tokens not empty:
	t = nächster token
	if t ist Gleitkommazahl:
		push(Q, t)
	else if t ist Operator:
		while not is_empty(S) and 
			top(S) ist Operator and
			t hat Präzidenz kleiner gleich top(S):
				push(Q, pop(S)) # stack top zu Ausgabe
		push(S,t)
	else if t ist "(":
		push(S,t)
	else if t ist ")":
		while top(S) ist nicht "(":
			push(Q, pop(S))
		pop(S)
while not is_empty(S)
	if top(S) ist "(": Fehler
	push(Q,pop(s))
return Q (als string)
```

> Hinweis: werfen sie einen Fehler wenn der Algorithmus in einen Fall läuft der einem ungültigen Infix Ausdruck entspricht.
> - Z. 18: Der Stack könnte leer werden.
> - Z. 21: Es gibt nicht genügend schließende Klammern

**Aufgabe 2.2 (4p):** Implementieren Sie in `arithmetic.cpp:evaluate_infix` einen Algorithmus welcher einen Ausdruck in Infix-Notation entgegen nimmt und das Ergebnis dieses zurück gibt.

> Hinweis: Ihr Algorithmus sollte nicht von der Korrektheit der Eingabe ausgehen, d.h. der Algorithmus sollte einen Fehler werfen wenn der Infix-Ausdruck in seiner Form oder Aussage ungültig ist.

>Hinweis: Nutzen Sie einen Stack für Zwischenergebnisse.

**Aufgabe 2.3 (4p):** Implementieren sie einen [Read-Evaluate-Print-Loop (REPL)](https://en.wikipedia.org/wiki/Read%E2%80%93eval%E2%80%93print_loop) welcher Arithmetische Ausdrücke in **Infix-Notation** als Eingabe entgegen nimmt, und bei `Enter` Ausführt und das Ergebnis printed und danach auf eine erneute Eingabe wartet. 

> Denken Sie daran etwaige fehlerhafte Eingaben abzufangen damit Ihr Programm nicht abstürzt.

Erweitern Sie Ihren REPL um die Möglichkeit Zuweisungen in der folgenden Form zu unterstützen:

```bash
>>> set x
>>> 24.0 + 2.0
```

In späteren Ausdrücken kann dann `x` wiederverwendet werden und wird durch das Ergebnis der Definition ersetzt:

```bash
>>> (2.0 + x)
>>> Ergebnis: 28.0
```

## Aufgabe 3. - Einen ADT Umsetzen.

> Dateien die in dieser Aufgabe editiert werden sollen:
>
> - Set.h
> - set_operations.cpp

Gegeben sei der folgende ADT:

```cpp
type Set<T>:
    operators:
        empty: -> Set
        add: Set x T -> Set
        remove: Set x T -> Set
        contains: Set x T --> Bool
        size: Set -> int
        []: Set x int -> T
		==: Set x Set -> bool
    axioms:
        add(add(Set,x),x) = add(Set,x)
        remove(add(empty,x), x) = empty
        contains(add(Set,x), x) = true
        contains(remove(Set, x),x) = false
        // size axioms
        size(empty) = 0
        contains(Set,x) = true -> size(add(Set,x)) = size(Set)
        contains(Set,x) = false -> size(add(Set,x)) = size(Set) + 1
		∀x,y: contains(Set1,x) == contains(Set2,y) <-> Set1 == Set2
```

**Aufgabe 3.1 (4p):** Implementieren Sie in `Set.h` die `operatoren` sodass Sie die gegebenen `axiome` erfüllen. Nutzen Sie dazu erneut das Konzept einer Linked List als Speicherstruktur.

> Hinweis: Denken Sie dabei an die [Rule of Three](https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)#Rule_of_three).

Implementieren sie weiterhin die beiden cpp operatoren `operator[]` und `operator==` für die `Set` Klasse (diese werden für Tests benötigt)

**Aufgabe 3.2 (2p):** Nutzen Sie Ihre Implementierung des Sets um die binären Set-Operationen aus `set_operations.cpp` zu Vervollständigen.

## Aufgabe 4: Korrektheit und Terminierung

> Dateien die in dieser Aufgabe editiert werden sollen:
> - README.md

Der im Folgenden gegebene Algorithmus berechnet die minimale Anzahl an Münzen
die benötigt werden um Rückgeld in Höhe von `amount` auszugeben, 
wenn die Erlaubten denominationen {25,10,5,1} sind.


```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int min_coins(int amount)
{
    int coins[] = {25, 10, 5, 1};
    int num_coins = 0;
    int remaining = amount;

    for (int coin : coins)
    {
        while (remaining >= coin)
        {
            remaining -= coin;
            num_coins += 1;
        }
    }

    return num_coins;
}

int main()
{
    int amount = 42;
    std::cout << min_coins(amount) << std::endl; // Output: 5
    return 0;
}
```

**Aufgabe 4.1 (3p, Zusatz):** 
Beweisen sie die **totale** Korrektheit des oben gegebenen Algorithmus.
Beweisen sie hierzu die partielle Korrektheit und Terminierung des Algorithmus.

Schreiben Sie Ihre Antwort in diese `README`.
> Hinweis: Sie können Mathematische Formeln wie in Latex schreiben indem Sie die Formel mit Dollarzeichen umschließen. Mehr Infos hier: [Latex - Formeln](https://www.grund-wissen.de/informatik/latex/mathematischer-formelsatz.html)
> Einfache Dollarzeichen erlauben Formeln im Text, doppelte Dollarzeichen als Block.
> Bsp: $\alpha$
>
$$
\begin{align}
    F_n = F_{n-1}+F_{n-2}\\
    F_0 = 0 \\
    F_1 = 1
\end{align}
$$
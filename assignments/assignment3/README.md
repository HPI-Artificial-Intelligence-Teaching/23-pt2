# Programmiertechnik II SS23, Übung 3

Pro Übung gibt es 20 Punkte. Für eine Zulassung zur Klausur ist der Erwerb von mindestens 50% aller Punkte über alle Übungsaufgaben erforderlich, wobei Leerabgaben von Übungen nicht erlaubt sind.

## Aufgabe 1 - CountingComparator (3 Punkte):
Relevante Dateien: sorting.cpp, sorting.h.

In dieser Übung soll die Performance verschiedener Sortieralgorithmen in
bestimmten Fällen betrachtet werden. Wir werden dafür die Anzahl der Vergleiche auf das jeweilige Array als Messgröße heranziehen.

Für diesen Schritt benötigen wir 2 Klassen:
- Einen Comparator, dessen Aufgabe darin besteht 2 ihm übergegebene Argumente auf Gleichheit zu überprüfen
- Einen CountingComparator, der als Wrapper um den ersten dient und jede Vergleichsoperation zählt.

Der Comparator erhält nur eine Funktion: compare. Diese bekommt ein Array von Daten und 2 Indizes übergeben. Der Comparator soll eine Zahl größer 0
zurückgeben, wenn der Wert des Arrays an Position x größer ist als an Position y. Bei Gleichheit soll 0 zurückgegeben werden, bei umgekehrter Ordnung ein
Wert < 0. Dieser Comparator kann zum Vergleichen genutzt werden indem z.B. auf (comparator.compare(data, x, y) > 0) getestet wird.

Der CountingComparator dient als Wrapper um den ersten, und soll weiterhin einen Zähler implementieren, der bei jedem Compare inkrementiert wird. Dieser
Zähler soll über getCounter() ausgelesen werden können und über reset() auf 0 zurückgesetzt werden können.

Bei anderen Daten, ließe sich dieser Comparator leicht durch eine alternative Implementierung ersetzten. Diese Konstruktion soll auch als Beispiel für das "Composition over Inheritance" Paradigma dienen, nachdem funktionelle Erweiterung
bei objektorientierten Sprachen am Besten durch Komposition mehrerer Objekte und nicht durch vererben/überschreiben erreicht wird.
Hier ließe sich jeder Comparator innerhalb des Wrappers nutzen ohne dass der Wrapper über seinen Inhalt bescheid wissen müsste,
während bei Vererbung jedes mal neu vererbt werden muss.

## Aufgabe 2 - Sortieralgorithmen (7 Punkte)
Relevante Dateien: sorting.cpp, sorting.h

In dieser Aufgabe sollen 3 Sortieralgorithmen implementiert werden:
- Mergesort
- Bubblesort
- Quicksort

Für die folgenden Messungen wollen unsere Implementierung von Mergesort noch mit einer kleinen Ergänzung erweitern: Durch einen Test in merge() ob das letzte
Element der ersten Menge kleiner ist als das erste Element der zweiten Menge kann Mergesort deutlich effizienter bei günstigen Eingabedaten werden, da in diesem Fall, wenn beide Teillisten sortiert sind, die Daten in dieser Reihenfolge im Speicher belassen werden können ohne weitere Vergleiche vorzunehmen. Fügen sie diese Überprüfung in ihrer Implementierung ein.

Bei Quicksort soll als Pivotelement immer das am weitesten links stehende Element der Teilliste genutzt werden.

Achten sie bei allen ihren Implementierung darauf, dass wann immer zwei Elemente in einem Array (den Daten oder im Falle von MS dem aux-Array) verglichen werden sollen, dafür der in der Variable comp referenzierte CountingComparator genutzt wird. Dies ermöglicht das Zählen der Vergleichsoperationen in jeder Implementierung.

## Aufgabe 3 - Datengeneratoren (6 Punkte)
Relevante Dateien: main.cpp, generator.cpp, generator.h

Ihre so implementierten Algorithmen sollen vermessen werden. Dafür stellt die main.cpp bereits ein Programm bereit, welches auf unterschiedlich großen Datensätzen jeweils den Best- und den Worst-Case aller 3 Algorithmen ausmessen soll, jeweils auf einem Datensatz aus 10, 100 und 1000 Elementen.

Ihre Aufgabe besteht darin 6 Datengeneratoren zu entwickeln, die jeweils für jeden der drei Algorithmen den Best- und den Worst-Case herbeiführen.
Hierzu ein paar Tipps und Hinweise:
- Die Anforderung besteht darin, den Datensatz determistisch und in beliebiger Länge erzeugen zu können. Einen Datensatz hart abzuspeichern erfüllt diese Aufgabenstellung NICHT. Zufälliges Anordnen der Elemente wäre zwar praxisnah, soll aber aus Verständnisgründen hier ebenfalls nicht erfolgen.
- Die generierten Daten sollen n Elemente aufsteigend und ohne Duplikate enthalten, also jeweils den Datensatz (0,1,...,n-1)
- Implementieren sie zuerst generateSorted(int n), eine Funktion welche eine Reihe von n Zahlen erzeugt und sortiert in einem Array ablegt. Diese kann
  für alle folgenden Teilaufgaben genutzt werden.
- Der Best- und Worst-Case von Bubblesort ist einfach zu erzeugen.
- Ohne die oben genannte Erweiterung wäre die zu erwartende Komplexität auf dem Papier bei Mergesort immer gleich. Mit dieser Erweiterung kann der Best-Case
  jedoch erheblich schneller erreicht werden, wobei der erzeugende Algorithmus ebenfalls einfach zu implementieren ist.
- Der praktische Worst-Case bei Mergesort, kann generiert werden, indem wir die Logik von Mergesort umkehren. Wir beginnen bei einem sortierten Array und 
  trennen dieses in zwei neue Teilarrays auf, die jeweils alternierend die Elemente des ersten Enthalten (Indizes 1,3,5,... und 0,2,4,6,...). Danach wenden
  wir dieselbe Operation (separate) auf beide neuen Teillisten an. Hat eine Teilliste in dieser Rekursion nur noch ein Element, wird sie unverändert zurückgebeben. Hat sie nur noch 2 Elemente, werden diese vertauscht und dann zurückgegeben. Sobald beide separate() auf beiden Teillisten terminiert hat, werden beide Listen wieder zusammengefügt (merge()), indem sie im ursprünglichen Datensatz aneinander gehängt werden. Dieser Algorithmus erzeugt eine Liste, die die Anzahl notwendiger Tauschoperationen bei Mergesort in jeder Implementierung maximiert. Dies sorgt auch bei Mergesort ohne Erweiterungen dafür, dass die Laufzeit des Algorithmus leicht höher ausfällt als im Best-Case, ein Unterschied der jedoch nicht dominant ist und deswegen in der Landau-Notation nicht genannt wird.
- Der Best-Case bei Quicksort, kann ebenfalls erreicht werden indem ausgehend von einer sortierten Liste, der Quicksort-Prozess umgekehrt wird (rearrange()). 
  Dafür wird ein Element aus der Mitte der Liste als Pivotelement ausgewählt und an die Stelle des Pivotelements gesetzt. Dann werden beide Teillisten bestimmt die kleiner, respektive größer als das Pivotelement sind und mit ihnen wird in einem rekursiven Aufruf identisch verfahren. Die Rekursion terminiert, wenn die Funktion auf eine Teilliste der Länge 1 oder 2 angewendet wird. Dieser Algorithmus erzeugt einen Datensatz, bei dem beide Teillisten
  immer in etwa gleich lang sind. Dies maximiert die Effizienz von Quicksort.
- Der Worst-Case von Quicksort ist nicht unbedingt auf den ersten Blick intuitiv, jedoch mit dem bisherigen Code leicht zu implementieren.

Es gibt potenziell mehrere mögliche Lösungen für manche dieser Teilaufgaben. Deswegen haben wir auf automatisierte Tests verzichtet. Im Tausch dafür bitten wir Sie, jeweils eine durch ihre Lösung generierte Beispielfolge von 10 Zahlen (0,...,9) in der Solution MD anzugeben.

## Aufgabe 4 - Messungen (4 Punkte)
Relevante Dateien: main.cpp, solution.md
Führen sie mit den nun implementierten Generatoren die main.cpp aus. Erfassen sie ihre Ausgabe und speichern Sie sie in der solution.md in diesem Ordner.

Diskutieren sie, ob die gemessene Anzahl Vergleiche mit ihren Erwartungen übereinstimmt. Entspricht die gemessene Zahl in ihrer Größenordnung (Multiplikation um eine Konstante kann dabei durchaus auftreten) dem, was die Theorie für den jeweiligen Algorithmus vorhersagt? Wenn nicht, wie könnte diese Diskrepanz entstehen? Ist die Anzahl der Vergleiche im Array überhaupt ein praktisch sinnvoller Messwert für diese Art von Experiment?
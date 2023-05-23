# Programmiertechnik II SS23, Übung 1

Pro Übung gibt es 20 Punkte. Für die Zulassung zur Prüfung müssen in allen Übungen mindestens 50% der Punkte erzielt werden.

## Aufgabe 1 - GradingTable (10 Punkte)

Die folgende Übung dient als Einführung in C++ und das Abgabesystem.
Als Grundlage dient die letzte Übung aus PT1 im WS22/23.
Das in dieser Übung implementierte System zur Auswertung von Aufgaben soll in C++ mit einigen der nun verfügbaren Spracherweitungen erneut implementiert werden.
Dazu ist in diesem Repository ein Rahmen für alle notwendigen Komponenten gegeben.

Das System soll aus 2 Komponenten bestehen: Der GradingTable, die zuständig ist für das Einlesen der Datenbank aus der Datei grading_results.db, und den GradingAgents, die unterschiedliceh Aufgaben zur Auswertung übernehmen sollen.

Die GradingTable soll eine einfach verkettete Liste speichern, die alle Einträge des .db-Files enthält. Dazu ist das aus PT1 bekannte Struct bereits gegebeben. GradingTable soll sowohl den Verweis auf der erste- als auch auf das letzte Element dieser Element speichern.

Der Konstruktor der GradingTable bekommt eine Referenz auf einene C++-Filestream übergeben, der ausgelesen werden und in eine Liste umgewandelt werden soll. Die zugrundeliegende Logik ist identisch zu der aus PT1 bekannten. Einzig das neue fp-Interface muss genutzt werden.

Eine Spezifikation des ifstream-Interfaces ist erhältlich unter:
https://cplusplus.com/reference/fstream/ifstream/
Relevant sind hierbei die Methoden: fp.read(), fp.eof(), fp.isopen(). Da fp.read immer einen char* erwartet, kann reinterpret_cast genutzt werden um die Eingabedaten in den gewünschten Datentyp umzuwandeln.

Weiterhin müssen für die GradingTable zwei weitere Funktionen implementiert werden:

1. Der Destruktor der GradingTable muss den gesamten Inhalt der Liste korrekt wieder freigeben.


2. Die GradingTable soll für die Benutzung in den Agenten das Interface eines Iterators erlauben. Iteratoren stellen eine Schnittstelle bereit, über die unkompliziert mittels einer for-Loop iteriert werden kann, ohne Abbruchbedingungen oder Zählvariablen selber Verwalten zu müssen.

Für einen Iterator muss eine Klasse 2 Methoden und einen Datentyp bereitstellen: 
- Der Datentyp Iterator ist ein Struct, dass die Zählvariable (in diesem Fall ein Pointer auf das aktuell betrachtete Objekt der Liste) und mehrere Zugriffsmethoden auf diesen bereitstellt:
- Der Iterator überlädt folgende Methoden:
- operator*, um beim Auflösen des Iterators direkt auf der interne Objekt zuzugreifen *iterator soll also nicht den Iterator zurückgeben, sondern das Element der Liste.
- operator-> mitdemselben Zweck.
- operator++ Um ein Element weiterzuspringen und um das dann referenzierte Objekt zurückzugeben
- operator++(int) Um ein Element weiterzuspringen und das VORHER referenzierte Objekt zurückzugeben.
- operator== um bei zwei Iteratoren zu überprüfen ob sie auf dasselbe Element verweisen.
- operator!= um bei zwei Iteratoren zu überprüfen ob sie auf unterschiedliche Element.
- Einen Konstruktor, der einen Pointer auf das initiale Objekt übergeben bekommt.

Der Klasse GradingTable muss weiterhin zwei Methoden bereitstellen:
- begin() gibt einen Iterator zurück, der auf das erste Element der Liste verweist.
- end() gibt einen Iterator zurück, der identisch ist zu einem Iterator der das Ende der Liste bereits erreicht hat.

Wird mit for auf einen Iterator zugegriffen, wird zuallererst die begin() Methode aufgerufen um den Iterator zu erzeugen. Danach wird mit operator++ sukkeszive je ein Element der Liste abgefragt. Mit end() wird ein fertiger Iterator erzeugt. Die Schleife bricht ab, sobald der Vergleich des Rückgabewerts von end() und des aktiv genutzten Iterators zu true auswertet.

## Aufgabe 2 - TaskAgents (10 Punkte)

Die so erzeugte GradingTable soll für die Auswertung genutzt werden. Dafür sind 2 Arten von TaskAgents zu implementieren. Einfache TaskAgents iterieren über die Liste, und rufen mit jedem Element der Liste visit() auf um dieses spezifische Element auszuwerten. Es werden keine Informationen über mehrere Elemente aggregiert.

Die ReducingTaskAgents, aggregieren einen bestimmten Aspekt der Listenelement. Hierzu werden die beiden Methoden reduceAll() und reduce() genutzt. reduceAll() ruft reduce() für jedes Element der Liste auf, gemeinsam mit dem Rückgabewert des letzten reduce()-Aufrufs.

Beide Agenten implementieren die Methode performTask(), welche den jeweiligen spezifischen Auftrag auslöst und im Falle des ReducingTaskAgents den Rückgabewert mit printf ausgibt. Im Falle des einfachen Taskagents, soll diese Methode einfach visitAll() aufrufen. Diese gemeinsame Methode, ermöglicht es bei Aufruf des Programms, alle TaskAgents mitdemselben DatenTyp zu behandeln, TaskAgent. Die Main-Methode soll in einer Fallunterscheidung feststellen welcher Agent zu nutzen ist, diesen initialisieren und dessen performTask()-Methode dann aufrufen. Dabei soll die Variable in der die Referenz auf den TaskAgent abgelegt ist vom Typ TaskAgent* sein.

Für beide Aufgaben sind die Interfaces größtenteils vordefiniert, bei manchen Methoden muss jedoch das Interface an den markierten Stellen noch um Rückgabedatentypen oder Parameter vervollständigt werden. Die Main-Funktion enthält bereits die Logik zum Parsen der Parameter und öffnen der Datenbankdatei, alles weitere muss selber implementiert werden.

Es sollen folgende 5 Agenten verfügbar sein:
- 'a': Soll alle Ergebnisse ausgeben, insbesondere jedoch die mat_no, die aktuelle series und die punkte. Der für printf zu nutzende-Formatstring ist: "%d hat in %d %d Punkt(e) erreicht.\n"
- 'b': Soll nur jene Ergebnisse anzeigen, deren Punkte unter 10 liegen. Der für printf zu nutzende Format-String ist: "%d %d\n"
- 'c': Ein ReducingTaskAgent, der die Anzahl der Elemente zählt
- 'd': Ein ReducingTaskAgent, der die höchste erreichte Punktzahl bestimmt
- 'e': Ein ReducingTaskAgent, der die insgesamt in Series 3 bestimmten Punkte erfasst.
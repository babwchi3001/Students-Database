# Assignment 4: Datenbank für Studenten
## Lernziel
In diesem Assignment soll der Umgang mit binärem Suchbaum und Rekursion gelernt werden. Um die Lernziel zu erreichen soll ein Programm mit der im folgenden definierten Funktionalität implementiert werden.
## Beschreibung
Die Schüler werden in verschiedenen Schulen platziert (die durch eine "unique school_id" definiert sind) und in diesen Schulen werden sie entweder in die erste, zweite oder dritte Klasse platziert, basierend auf dem Geburtsjahr des Schülers.
Es gibt mehrere Klassen für dasselbe Jahr (parallele Klassen), wobei ich die Anzahl der parallelen Klassen zunächst standardmäßig auf 4 festgelegt habe. Jede Klasse kann maximal 30 Schüler aufnehmen. Falls alle 4 Klassen gefüllt sind und weitere Schüler untergebracht werden müssen, wird eine neue Klasse angelegt. Beim Verknüpfen der Schüler in den Klassen ist eine binäre Suche mit Rekursion erforderlich.

Folgende Funktionen sollen implementiert werden:
- SEARCH
- ADD
- REMOVE
- SAVE
- HELP
- EXIT

Jeder Schüler wird eine bestimmte Anzahl von Punkten haben, die seine Position im binären Baum bestimmt. Jede Klasse wird ihren eigenen binären Suchbaum haben.

## Programmaufruf
Das Programm soll mit 2 Kommandozeilenargumenten aufgerufen werden können:
```sh
./ass4 <school_file> <students_file> 
```
*ass4*: Programmname.
*<school_file>*: Datei mit Schuleninformation.
*<students_file>*: Datei mit Studenteninformation.

Beispiel (die bereitgestellten Dateien *school.txt* und *names_surnames.txt* sollten verwendet werden):
```sh
./ass4 school.txt names_surnames.txt
```
## Schul- und Studentendatei format
Die Datei hat das folgendes Format:
Shule:
```
school_id number_of_classes_first_year number_of_classes_second_year number_of_classes_third_year
```
Beispiel:
```
1 4 4 4
2 4 4 4
3 4 4 4
```
Studenten:
```
Name Surname  School_id Year_of_birth Points
```
Beispiel:
```
Elizabeth Lopez  3 2001 19214
Summer Cook  1 2001 974
Eleanor Johnson  2 2001 2041
Autumn Scott  2 2002 9236
Sophia Adams  1 2000 10446
```

## Fehlermeldungen
Sollte die Anzahl an Argumenten ungleich 2 sein, soll die folgende Fehlermeldung ausgegeben werden und sich das Programm mit Returnwert 2 beenden:
```
Wrong parameters!!!
```
Wenn die Datei nicht geöffnet wird, soll die folgende Fehlermeldung ausgegeben werden und sich das Programm mit Returnwert 1 beenden:
```
File could not be opened!!!
```
Wenn die Speicher für die Schule nicht allokiert werden könnte,  soll die folgende Fehlermeldung ausgegeben werden und sich das Programm mit Returnwert 3 beenden:
```
Memory could not be allocated!!!
```
Es wird empfohlen, die bereits definierten Rückgabewerte in framework.h zu verwenden.
## Hübsche Ausgabe
Für alle Ausgabe, die von SEARCH, ADD, REMOVE, SAVE, HELP and EXIT kommt, soll man Farben verwenden, die in **framework.h** definiert sind. Alle Beispielen sind in *Beispiele von ein paar Ein- und Ausgaben* Abschnitt.
Beispiel:
```c
printf(RED"\nThis is an example of text printed in red colour.");
```
Dieses Beispiel gibt aus:

$`\textcolor{red}{\text{This is an example of text printed in red colour.}}`$ 

## Beschreibung der Funktionen und Beispiele von ein paar Ein- und Ausgaben
### SEARCH
Funktion sucht nach einem Schüler und gibt die Schule aus, die der Schüler besucht.

Beispel Ausgabe:
```
                 WELCOME TO THE ESP-STUDENT-DATABASE

=============================================================================
Please choose one of the following options:
SEARCH
ADD
REMOVE
SAVE
LOAD
HELP
EXIT
=============================================================================
search

Which student are you looking for???

Hadley Clark
```
$`\textcolor{green}{\text{Student: Hadley Clark has been found in school 1.}}`$ 

---
### ADD
Funktion fügt einer Schule einen Schüler hinzu. Für diese Funktion müssen einige Informationen eingegeben werden, wie Name, Nachname, Schulkennzeichen, Geburtsjahr, Punkte. Der Schüler sollte in die erste Klasse hinzugefuegt(!!) werden, die nicht voll ist.

Beispel Ausgabe: 
```
                 WELCOME TO THE ESP-STUDENT-DATABASE

=============================================================================
Please choose one of the following options:
SEARCH
ADD
REMOVE
SAVE
LOAD
HELP
EXIT
=============================================================================
add
Please give the student information in this order: "Name Surname  School_id Year_of_birth Points"

Max Mustermann  1 2000 19546

```
$`\textcolor{green}{\text{Student Max Mustermann has been successfully added to school 1}}`$ 

---
### REMOVE
Funktion entfernt einen Schüler namentlich von einer Schule. Der Schüler soll namentlich gefunden werden.

Beispel Ausgabe:
```
                 WELCOME TO THE ESP-STUDENT-DATABASE

=============================================================================
Please choose one of the following options:
SEARCH
ADD
REMOVE
SAVE
LOAD
HELP
EXIT
=============================================================================
remove
Please give the name and surname of the student you want to remove.

Gemma Clark

```
$`\textcolor{green}{\text{Student Gemma Clark has been successfully removed from school 1}}`$ 

---
### SAVE
Funktion speichert die Informationen über die Schule und die Schüler in der Datei *<original_filename> + <_save>*.

Beispel Ausgabe:
```
                 WELCOME TO THE ESP-STUDENT-DATABASE

=============================================================================
Please choose one of the following options:
SEARCH
ADD
REMOVE
SAVE
LOAD
HELP
EXIT
=============================================================================
save

```
---
### LOAD
Funktion lädt die Informationen über die Schule und die Schüler aus der Datei *<original_file_name> + <_save>*.

Beispel Ausgabe:
```
                 WELCOME TO THE ESP-STUDENT-DATABASE

=============================================================================
Please choose one of the following options:
SEARCH
ADD
REMOVE
SAVE
LOAD
HELP
EXIT
=============================================================================
load

```
---
### HELP
Funktion gibt alle möglichen Befehle aus.

Beispel Ausgabe:
```
                 WELCOME TO THE ESP-STUDENT-DATABASE

=============================================================================
Please choose one of the following options:
SEARCH
ADD
REMOVE
SAVE
LOAD
HELP
EXIT
=============================================================================
help
```
++++++++++++++++++++++++++++++++++HELP MENU++++++++++++++++++++++++++++++++++++++++++

$`\textcolor{red}{\text{SEARCH: Searches in the binary tree for a specified student.}}`$

$`\textcolor{blue}{\text{ADD: Searches for the correct school, class and node. After finding it it inserts the student on the correct position.}}`$

$`\textcolor{yellow}{\text{REMOVE: Searches for the correct school, class and node. After finding it it removes the student completely. The BST needs to be correctly formated after the student remove.}}`$

$`\textcolor{purple}{\text{SAVE: Re-writes the files with the current student and school data.}}`$

$`\textcolor{green}{\text{LOAD: Rerolls to the current version of the file without needing to restart the program.}}`$

HELP: Displays the HELP menu.

$`\textcolor{grey}{\text{EXIT: Exits the program.}}`$

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


---
### EXIT
Funktion beendet das Programm.

Beispel Ausgabe:
```
                 WELCOME TO THE ESP-STUDENT-DATABASE

=============================================================================
Please choose one of the following options:
SEARCH
ADD
REMOVE
SAVE
LOAD
HELP
EXIT
=============================================================================
exit
```
## Erlaubte Bibliotheken
- stdio.h
- stdlib.h
- string.h

## Abgabe
- Deadline: 09.06.2023 23:59

## Bewertung
- Mögliche erreichbare Punkte: 34

- | Kategorie | Punkte |
  | ------ | ------ |
  | Funktionaliät | 25 |
  | Sonstige | 9 |


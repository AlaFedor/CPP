# ASCII rendering

Zadanie na temat ASCII rendering, rysowanie figur do pliku.

Projekt polega na stworzeniu systemu do rysowania figur na "canvasie" w formacie ASCII. Canvas, czyli obszar do rysowania, ma zdefiniowaną szerokość, wysokość oraz symbol tła, który może być dowolnym znakiem. W projekcie wykorzystano klasę ASCIICanvas, która umożliwia tworzenie i rysowanie na prostym kanwie ASCII.

Figury, takie jak prostokąt, kwadrat i koło, są definiowane jako klasy dziedziczące po abstrakcyjnej klasie Figure. Każda figura ma swoje wymiary, współrzędne środka oraz symbol, którym jest rysowana na canvasie. Klasy figur mają metodę draw, która rysuje odpowiednią figurę na podanym canvasie.

Plik konfiguracyjny zawiera informacje o wymiarach canvasu, nazwie pliku wyjściowego, symbolu tła oraz szczegółach dotyczących figur, które mają być narysowane. Program wczytuje ten plik, tworzy odpowiednie obiekty canvasu i figur, a następnie rysuje figury na canvasie zgodnie z danymi z pliku konfiguracyjnego i zapisuje do podanego pliku wyjsciowego.

klonowanie repozytorium:

```
git clone
```

kompilacja:

```
g++ zadanie5.cpp -o zadanie5
```

Aby uruchomic nalezy wywolac program i podac nazwe pliku konfiguracyjnego.
Przykładowe uruchomienie:

```
./zadanie5 input
```

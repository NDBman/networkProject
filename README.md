# Beadandó
Hálózati architektúrák és protokollok tárgyra készült önálló beadandó.

## Leírás
###Kétszemélyes kvíz játék
**A feladat rövid leírása:** A feladat megvalósítása egy szerver és egy kliens program írásából áll. Az eredményként bemutatott programok segítségével lehetővé kell tenni, hogy két ember a kliens program egy-egy példányát használva egyszerű kvíz játékot játsszon egymással a szerveren keresztül.

**Játékszabályok:** A játékosok a játékvezetőtől egy numerikus értékkel megválaszolható kérdést kapnak, s egyszerre megadják a kérdésre vonatkozó tippjüket. Az a játékos nyeri a játszmát, akinek a tippje közelebb áll a helyes válaszhoz. Ha a két tipp eltérése a helyes választól ugyanannyi, akkor az eredmény döntetlen.

**A programok működése:** A szerver indítási paraméterként megkapja a játszmák számát. A szerveren előre (statikusan megadott módon) tárolhatók a kérdések és a hozzájuk tartozó helyes válasz. Indítás után a szerver két játékos jelentkezésére vár. Az első játékos bejelentkezése után üzenetet kap, miszerint a szerver még a másik játékosra vár. A második játékos jelentkezése után a játék automatikusan elindul; a kliensek megkapják a szervertől a játszmák számát. Két játszmában egy bizonyos kérdés csak egy alkalommal tehető fel. A szerver feltesz egy véletlenszerűen választott kérdést a klienseknek, s bekéri a kliensek válaszát. A válaszok beérkezése után a szerver tájékoztatja a klienseket a játszma eredményéről. Az utolsó játszma után a végeredmény közzéteszik, s a játéknak vége.
A játékmenettel kapcsolatos minimális elvárások: A programnak fel kell ismernie a játszma befejeződését (nyertes játékos, vesztes játékos, döntetlen); továbbá lehetőséget kell adni a klienseknek a feladásra a (feladom) üzenet elküldésével. A játék befejezésekor a végeredmény közlése után mindhárom alkalmazás (szerver + 2 kliens) bezárul.

## Fordítás
  - gcc kvzsrv.c -o kvzsrv
  - gcc kvzclnt.c -o kvzclnt
## Futtatás
  - szerver indítása terminál ablakban **./kvzsrv**
  - első játékos indítása újabb terminál ablakban **./kvzclnt**
  - második játékos indítása újabb terminál ablakban **./kvzclnt**


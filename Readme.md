# AvengersAssembly (pénztárgép)

- Horváth Gergely Zsolt **(BYVAM0)**
- Stefán Kornél **(TFRXIL)**
- Vass Kinga Fanni **(IZT6ZK)**

## Feladat szempontok

### Make rendszer

Clion használata végett `CMake`-re esett a választás és Kinga csinálta meg.

#### Program építése/tesztelése/futtatása

```bash
mkdir cmake-build
cd cmake-build
cmake -preset x64-release ..
make
make test # Tesztelés 
./Kaszas/Kaszas 20 # Futtatás
```

### Modularitás

A program az átláthatóság és különszedhetőség végett több részre lett bontva.

#### Könyvtárak

1. Billentyu (Gergő)
> A beolvasást ez a modul valósítja meg.
2. Nyomtato (Kinga)
> A kiírást ez a modul valósítja meg.
3. Közös/Common (Kornél)
> A programban használt adatok és a hozzájuk tartozó segédfüggvények.

#### Futtathatók

1. Kaszas (Kornél)
> Ez tartalmazza a programot és a program logikáját.

2. (Teszt)
> Ez indítja el a teszteket.
> 
> Mivel nem találtunk rá jobb módot, így ez belenyúl a Kaszas futtatható 
> forrás fájlaiba, de mivel "nem része" a programnak, így ezt 
> elfogadható kompromisszumnak találtuk az integrációs tesztért.

### Makróhasználat

A programban az alábbi módon alkalmaztunk makrókat:
1. A tesztekben az asszertálás makrókkal történt.
2. A fő program a belső állapotát feltételes fordításra
   (DEBUG makró) kiírja a program futása közben.
3. A kiírást végző modul kódduplikáció csökkentésére használja.

### Tesztek

A programban egység és integrációs teszt(ek) találhatóak.

#### Egység tesztek
Minden modul összes függvénye egység tesztekkel van ellátva
a megfelelő működés ellenőrzése érdekében.

#### Integrációs teszt
A fő program egy integrációs teszttel van ellátva,
hogy ellenőrizzük, hogy egy egyszerű helyzetben a 
program a megfelelő adatokat feldolgozza helyesen.

### Dinamikus viselkedés

A program dinamikus viselkedése tesztelhető a következő módon:
```bash
mkdir cmake-test
cd cmake-test
cmake -preset x64-debug ..
make
valgrind ./CUnitRunner # Plusz további paraméterek.
```

### Biztonsági szempontok

A beolvasásnál külön figyelmet szenteltünk a biztonságos C
függvények alkalmazására.

### Egyéb hasznos/helyénvaló technikai megoldások

i. DDebug kapcsolóval beleláthatunk a program belső állapotába.

### Egyéni munka

- Brit humor
- Menő beolvasás
- Szép kód

#### Felosztás

A program fejlesztésének a felosztását a kód dokumentáció tartalmazza.

Ahol nincs ez megjelelölve azt együtt találtuk ki és írtuk meg.
Természetesen nem együtt gépeltünk, csak peer programming történt.
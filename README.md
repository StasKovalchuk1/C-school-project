## Popis
V tomto projektu byl implementovan Strassenův algoritmus pro násobení matic, který bude porovnání s klasickým násobením matic.
Matici lze zadat dvěma způsoby:
1. Cteni ze souboru
2. Generování náhodného pro danou velikost pres argument v CLI

## CLI
Pro spuštěni programu s argumentem —help (-h) se vypíše následující:
```
Usage: ./nasobeni_matic {-h | --help |-f <file>   <file2> | -r <x>} {-b|-s} {-short|-full}
Options:
    -h, --help Show this help message and exit
    -f <file1> <file2> Read matrices from file
    -r <x> Generate random matrices with size <x>
    -b Use basic solver
    -s Use strassen solver
    -short Print only time
    -full Print time and result matrix
```

## Návod k použití.
Vytvořte adresář pro sestavení
```
mkdir build
```
Spusťte CMake pro generování souborů sestavení
```
cmake .. 
```
Zkompilujte projekt
```
make
```
Spusťte svůj spustitelný soubor
```
./nasobeni_matic -help
```

## Příklad práce se souborem
V prvním řádku zadejte počet řad a sloupců. Všimněte si, že Strassenův algoritmus funguje na čtvercových maticích, takže **počet řad a sloupců by měl být stejný**. Dále po řádku zadejte hodnoty matice. 
```
4 4
1 2 3 4
1 2 3 4
1 2 3 4
1 2 3 4
```

## Srovnání výkonu
Pro testovaný výkon byl použit operační systém macOS Ventura s osmijádrovým procesorem
```
Size 16*16
Classic: 0,0000125s
Strassen: 0,007663s
Strassen/Classic: 61

Size 64*64
Classic: 0,002607s
Strassen: 0,281892s
Strassen/Classic: 108

Size 128*128
Classic: 0,019947s
Strassen: 1,442440s
Strassen/Classic: 72

Size 256*256
Classic: 0,165129s
Strassen: 10,085978s
Strassen/Classic: 61

Size 512*512
Classic: 0,780003s
Strassen: 43,844878s
Strassen/Classic: 56

Size 1024*1024
Classic: 7,273497s
Strassen: 317,741490s
Strassen/Classic: 43

Size 2048*2048
Classic: 140,168868s
Strassen:3517,573768s
Strassen/Classic:25
```

## Výsledek:
Jak je vidět, rozdíl v průběhu programu se snižuje s rostoucí velikostí matic. Dalo by se říci, že na maticích více než 4096*4096 bude Strassenův algoritmus pracovat rychleji než naivní metoda. Avšak Strassenův algoritmus obecně je nežádoucí pro řešení praktických problémů.
- Konstanty použité ve Strassenově metodě jsou vysoké a pro typickou aplikaci naivní metoda funguje lépe.
- Submatrice v rekurzi zabírají více místa.

# Setcal
*Druhý projekt IZP 2021 na FIT VUT.*

## Použití
Programu při spuštění poskytněte cestu ke vestupnímu souboru.

``` sh
./setcal FILE
```

Vstupní soubor obsahuje definici univerza *(U)*, množin *(S)* a relací *(R)* a následně operace *(C)* na nich. Pokud je výsledkem operace relace nebo množina, lze na této množině provádět další operace. To o jaký druh příkazu se jedná rozhoduje první písmeno, které je buď U, S, R nebo C. Na prvním řádku každého souboru musí být definováno universum, jen prvky které universum obsahuje je pak mohou objevit v relacích a množinách. Po definování první operace již není možné definovat další množiny nebo relace.

Příkazy nad množinami:
- **empty A** - tiskne true nebo false podle toho, jestli je množina definovaná na řádku A prázdná nebo neprázdná.
- **card A** - tiskne počet prvků v množině A (definované na řádku A).
- **complement A** - tiskne doplněk množiny A.
- **union A B** - tiskne sjednocení množin A a B.
- **intersect A B** - tiskne průnik množin A a B.
- **minus A B** - tiskne rozdíl množin A \ B.
- **subseteq A B** - tiskne true nebo false podle toho, jestli je množina A podmnožinou množiny B.
- **subset A B** - tiskne true nebo false, jestli je množina A vlastní podmnožina množiny B.
- **equals A B** - tiskne true nebo false, jestli jsou množiny rovny.

Příkazy nad relacemi:
- **reflexive R** - tiskne true nebo false, jestli je relace reflexivní.
- **symmetric R** - tiskne true nebo false, jestli je relace symetrická.
- **antisymmetric R** - tiskne true nebo false, jestli je relace antisymetrická.
- **transitive R** - tiskne true nebo false, jestli je relace tranzitivní.
- **function R** - tiskne true nebo false, jestli je relace R funkcí.
- **domain R** - tiskne definiční obor funkce R (lze aplikovat i na relace - první prvky dvojic).
- **codomain R** - tiskne obor hodnot funkce R (lze aplikovat i na relace - druhé prvky dvojic).
- **injective R A B** - tiskne true nebo false, jestli je funkce R injektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R.
- **surjective R A B** - tiskne true nebo false, jestli je funkce R surjektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R.
- **bijective R A B** - tiskne true nebo false, jestli je funkce R bijektivní. A a B jsou množiny; a∈A, b∈B, (a,b)∈R.
- **closure_ref R** - tiskne reflexivní uzávěr relace R
- **closure_sym R** - tiskne symetrický uzávěr relace R
- **closure_trans R** - tiskne tranzitivní uzávěr relace R

Příklad syntakticky platného vstupního souboru:
```
U a b c x y z
S a b c x
S x y z
R (a b) (a c) (a a)
S
C empty 2
C card 3
C complement 3
C union 2 3
C intersect 2 3
```

Pro demnostraci všech funkcí se můžete podívat na [dummy.txt](dummy.txt).

## Sestavení
Program lze sestavit pomocí příkazu `make build`.

## Autoři
 - [Ondřej Zobal](https://github.com/OndrejZobal)
 - [Petr Kolouch](https://github.com/KolouchPetr)
 - [Vladimír Hucovič](https://github.com/hucovic-vladimir)
 
## Licence
Program je licencován pod [MIT Licencí](LICENSE).

# PARitLE_Solver

Risolutore del gioco PARitLE.

Per avviare il programma eseguire:
```
$ ./main
```
Di seguito un esempio di utilizzo:
```
Dizionario caricato con successo
Percorso del file: possible_word.txt
 --- TENTATIVO 1 ---
Inserire la parola: porta
                    10002
Numero di parole rimaste: 58
alpha, ampia, apina, apnea, appia, apula, ... 
 --- TENTATIVO 2 ---
Inserire la parola: siepa
                    00122
Numero di parole rimaste: 4
ceppa, felpa, leppa, zeppa, 

 --- TENTATIVO 3 ---
Inserire la parola: felpa
                    22222
Numero di parole rimaste: 1
felpa

FINE!!!
```
Ogni volta che viene inserita una parola, viene richiesto il risultato di tale parola che va inserito seguendo (carattere per carattere) i criteri:
- *0* carattere sbagliato;
- *1* carattere corretto in posizione sbagliata;
- *2* carattere corretto in posizione corretta.
Il programma di volta in volta dà una lista di parole possibili. La lunghezza della lista è programmabile utilizzando il metodo `Solver::SetLenghtRes(const int & len)`. Ad ogni tentativo il programma mostrerà al massimo `len` parole possibili.


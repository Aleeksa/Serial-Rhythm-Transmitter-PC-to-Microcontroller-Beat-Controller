# Serial Rhythm Transmitter (C & Windows API) 🎶🔌

Ovaj projekat omogućava slanje definisanih muzičkih ritmova sa računara na mikrokontroler (poput Arduina) putem serijske (COM) veze. Sistem je dizajniran da interpretira tekstualne zapise ritma i konvertuje ih u instrukcije koje hardver može da izvrši.

## 📝 Kako sistem funkcioniše
1. **Ulazni podaci:** Program čita fajl `ritam.txt` u kojem je definisan tempo i sekvenca nota.
2. **Validacija:** C program proverava da li su uneti karakteri validni (`F`, `H`, `Q`, `E`, `S`) i da li je tempo ispravno postavljen.
3. **Komunikacija:** Koristeći Windows `CreateFileA` i `WriteFile` funkcije, program uspostavlja vezu sa specifičnim COM portom i šalje podatke bajt po bajt.



## 📂 Sadržaj repozitorijuma
- `send_rhythm.c`: Glavni izvorni kod za Windows konzolnu aplikaciju.
- `ritam.txt`: Primer konfiguracionog fajla (Tempo + Ritam).
- `send_rhythm.exe`: Kompajlirana verzija programa spremna za korišćenje.

## 🎹 Format ritma
U fajlu `ritam.txt` možete koristiti sledeće oznake:
- **F (Full):** Cela nota
- **H (Half):** Polovina
- **Q (Quarter):** Četvrtina
- **E (Eighth):** Osmina
- **S (Sixteenth):** Šesnaestina



## ⚙️ Upotreba
Program se pokreće iz komandne linije (CMD) uz navođenje COM porta:

```bash
send_rhythm.exe COM3

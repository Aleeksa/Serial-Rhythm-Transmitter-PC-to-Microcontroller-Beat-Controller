# Serial Rhythm Transmitter (C & Windows API) 🎶🔌

This project enables sending defined musical rhythms from a PC to a microcontroller (such as an Arduino) via a serial (COM) connection. The system is designed to interpret textual rhythm notations and convert them into instructions that the hardware can execute.

## 📝 How the System Works
1. **Input Data:** The program reads a `ritam.txt` file containing the defined tempo and note sequence.
2. **Validation:** The C program verifies if the entered characters are valid (`F`, `H`, `Q`, `E`, `S`) and ensures the tempo is correctly set.
3. **Communication:** Using Windows `CreateFileA` and `WriteFile` functions, the program establishes a connection with a specific COM port and transmits data byte-by-byte.



## 📂 Repository Content
- `send_rhythm.c`: Main source code for the Windows console application.
- `ritam.txt`: Sample configuration file (Tempo + Rhythm).
- `send_rhythm.exe`: Compiled version of the program, ready for use.

## 🎹 Rhythm Format
You can use the following notations in the `ritam.txt` file:
- **F (Full):** Whole note
- **H (Half):** Half note
- **Q (Quarter):** Quarter note
- **E (Eighth):** Eighth note
- **S (Sixteenth):** Sixteenth note



[Image of musical note durations and symbols]


## ⚙️ Usage
The program is executed from the Command Prompt (CMD) by specifying the COM port:

```bash
send_rhythm.exe COM3

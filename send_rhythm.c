#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void trim(char* s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r' || s[n-1] == ' ' || s[n-1] == '\t')) {
        s[n-1] = '\0';
        n--;
    }
}

static int valid_rhythm(const char* r) {
    if (!r || !r[0]) return 0;
    for (size_t i = 0; r[i]; i++) {
        char u = (char)toupper((unsigned char)r[i]);
        if (!(u == 'F' || u == 'H' || u == 'Q' || u == 'E' || u == 'S'))
            return 0;
    }
    return 1;
}

static int send_all(HANDLE h, const char* data, DWORD len) {
    DWORD sent = 0;
    while (sent < len) {
        DWORD out = 0;
        if (!WriteFile(h, data + sent, len - sent, &out, NULL)) return 0;
        if (out == 0) return 0;
        sent += out;
    }
    return 1;
}

int main(void) {
    char filename[260];
    char comname[64];

    printf("Unesi ime fajla (npr ritam.txt): ");
    if (!fgets(filename, sizeof(filename), stdin)) return 1;
    trim(filename);

    printf("Unesi COM port (npr COM5): ");
    if (!fgets(comname, sizeof(comname), stdin)) return 1;
    trim(comname);

    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("GRESKA: Ne mogu da otvorim fajl.\n");
        return 1;
    }

    char tempo_line[64];
    char rhythm_line[2048];

    if (!fgets(tempo_line, sizeof(tempo_line), f) ||
        !fgets(rhythm_line, sizeof(rhythm_line), f)) {
        printf("GRESKA: Fajl mora imati 2 reda (tempo i ritam).\n");
        fclose(f);
        return 1;
    }
    fclose(f);

    trim(tempo_line);
    trim(rhythm_line);

    int tempo = atoi(tempo_line);
    if (tempo <= 0) {
        printf("GRESKA: Tempo nije validan.\n");
        return 1;
    }

    if (!valid_rhythm(rhythm_line)) {
        printf("GRESKA: Nevalidni znakovi u ritmu.\n");
        printf("Dozvoljeno: F H Q E S (mala/velika slova).\n");
        return 1;
    }

    // \\.\ je obavezno (radi i za COM3, COM10, itd.)
    char device[128];
    snprintf(device, sizeof(device), "\\\\.\\%s", comname);

    HANDLE h = CreateFileA(
        device,
        GENERIC_WRITE | GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (h == INVALID_HANDLE_VALUE) {
        printf("GRESKA: Ne mogu da otvorim %s.\n", comname);
        return 1;
    }

    // Podesi port (CDC ignoriše baud, ali Windows traži da je setovan)
    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    GetCommState(h, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(h, &dcb);

    // Poruka: tempo\nritam\n
    char msg[4096];
    snprintf(msg, sizeof(msg), "%d\n%s\n", tempo, rhythm_line);

    if (!send_all(h, msg, (DWORD)strlen(msg))) {
        printf("GRESKA: Slanje nije uspelo.\n");
        CloseHandle(h);
        return 1;
    }

    printf("OK! Poslato Pico-u: tempo=%d ritam=%s\n", tempo, rhythm_line);

    CloseHandle(h);
    return 0;
}

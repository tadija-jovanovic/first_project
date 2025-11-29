// Ukljucujemo standardnu biblioteku za input/output operacije (printf, scanf)
#include <stdio.h>

// Ukljucujemo biblioteku za generisanje random brojeva (rand, srand)
#include <stdlib.h>

// Ukljucujemo biblioteku za rad sa vremenom (time funkcija za seed)
#include <time.h>

// Glavna funkcija programa - odavde pocinje izvrsavanje
int main() {
    // Deklarisemo promenljivu za cuvanje broja koji se generise
    int broj;

    // Deklarisemo promenljivu za brojac petlje (iteracije od 0 do 9)
    int i;

    // Inicijalizujemo generator random brojeva sa trenutnim vremenom
    // time(NULL) vraca broj sekundi od 1. januara 1970. godine
    // Ovo osigurava da dobijemo razlicite brojeve pri svakom pokretanju programa
    srand(time(NULL));

    // Ispisujemo naslov programa
    printf("Program za proveru parnosti 10 random brojeva\n");
    printf("=============================================\n\n");

    // Pokrecemo petlju koja ce se izvrsiti 10 puta (od i=0 do i=9)
    for (i = 0; i < 10; i++) {
        // Generisemo random broj izmedju 0 i 99
        // rand() generise broj izmedju 0 i RAND_MAX
        // % 100 nam daje ostatak pri deljenju sa 100, sto daje brojeve 0-99
        broj = rand() % 100;

        // Ispisujemo redni broj (i+1 jer brojimo od 1, a ne od 0)
        printf("%d. ", i + 1);

        // Ispisujemo generisani broj
        printf("Broj: %d - ", broj);

        // Proveravamo da li je broj paran ili neparan
        // Koristimo modulo operator (%) koji vraca ostatak pri deljenju
        // Ako je broj % 2 == 0, to znaci da broj deljiv sa 2 bez ostatka (PARAN)
        if (broj % 2 == 0) {
            // Ako je uslov tacan, broj je paran
            printf("PARAN\n");
        } else {
            // Ako uslov nije tacan (ostatak je 1), broj je neparan
            printf("NEPARAN\n");
        }
    }

    // Ispisujemo praznu liniju radi citljivosti
    printf("\n");

    // Ispisujemo poruku korisniku
    printf("Pritisnite Enter za izlaz...");

    // getchar() ceka da korisnik pritisne Enter pre nego sto se program zatvori
    // Ovo sprecava da se konzolni prozor odmah zatvori
    getchar();

    // Vracamo 0 operativnom sistemu sto znaci da je program uspesno zavrsen
    return 0;
}

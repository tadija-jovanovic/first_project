// Ukljucujemo standardnu biblioteku za input/output operacije
#include <stdio.h>

// Ukljucujemo matematicku biblioteku za PI konstantu i ugradjenu sin() funkciju
#include <math.h>

// Definisemo PI konstantu (odnos obima kruga i precnika)
// Koristimo M_PI iz math.h ako je dostupna, ili definisemo sami
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

// Funkcija za racunanje faktorijela broja n
// Faktorijel: n! = 1 * 2 * 3 * ... * n
// Primer: 5! = 1 * 2 * 3 * 4 * 5 = 120
long long int faktorijel(int n) {
    // Deklarisemo promenljivu za rezultat, pocinjemo od 1
    long long int rezultat = 1;

    // Deklarisemo brojac za petlju
    int i;

    // Petlja koja mnozi sve brojeve od 1 do n
    for (i = 1; i <= n; i++) {
        rezultat = rezultat * i;  // Mnozimo trenutni rezultat sa i
    }

    // Vracamo izracunati faktorijel
    return rezultat;
}

// Funkcija za racunanje stepena broja (osnova^eksponent)
// Primer: stepen(2.0, 3) = 2.0 * 2.0 * 2.0 = 8.0
double stepen(double osnova, int eksponent) {
    // Deklarisemo promenljivu za rezultat, pocinjemo od 1.0
    double rezultat = 1.0;

    // Deklarisemo brojac za petlju
    int i;

    // Petlja koja mnozi osnovu sama sa sobom eksponent puta
    for (i = 0; i < eksponent; i++) {
        rezultat = rezultat * osnova;  // Mnozimo rezultat sa osnovom
    }

    // Vracamo izracunati stepen
    return rezultat;
}

// Funkcija za racunanje sinusa pomocu Tejlorovog reda
// Tejlorov razvoj: sin(x) = x - x³/3! + x⁵/5! - x⁷/7! + x⁹/9! - ...
// Parametar x je ugao u radijanima
// Parametar n_clanova je broj clanova Tejlorovog reda koji koristimo
double tejlorov_sinus(double x, int n_clanova) {
    // VAZNO: Tejlorov red za sinus dobro konvergira samo za male uglove!
    // Zato moramo da svedemo ugao na interval [-PI, PI]
    // koristeci periodičnost sinusa: sin(x) = sin(x - 2*PI*n)

    // Svodimo ugao na interval [0, 2*PI] pomocu modulo operacije
    // fmod(x, 2*M_PI) vraca ostatak pri deljenju x sa 2*PI
    x = fmod(x, 2 * M_PI);

    // Ako je x negativan, dodajemo 2*PI da bi bio u [0, 2*PI]
    if (x < 0) {
        x = x + 2 * M_PI;
    }

    // Sada svodimo na interval [-PI, PI] za bolju konvergenciju
    // Ako je x > PI, koristimo sin(x) = sin(x - 2*PI)
    if (x > M_PI) {
        x = x - 2 * M_PI;
    }

    // Deklarisemo promenljivu za rezultat (zbir clanova)
    double rezultat = 0.0;

    // Deklarisemo brojac za petlju
    int i;

    // Petlja koja racuna prvih n_clanova Tejlorovog reda
    for (i = 0; i < n_clanova; i++) {
        // Racunamo eksponent: 2*i + 1 (daje nam 1, 3, 5, 7, 9, ...)
        int eksponent = 2 * i + 1;

        // Racunamo clan: x^eksponent / eksponent!
        double clan = stepen(x, eksponent) / faktorijel(eksponent);

        // Proveravamo da li je clan pozitivan ili negativan
        // Clanovi se smenjuju: +, -, +, -, +, ...
        // Ako je i parno (0, 2, 4, ...), clan je pozitivan
        // Ako je i neparno (1, 3, 5, ...), clan je negativan
        if (i % 2 == 0) {
            rezultat = rezultat + clan;  // Dodajemo pozitivan clan
        } else {
            rezultat = rezultat - clan;  // Oduzimamo negativan clan
        }
    }

    // Vracamo izracunatu vrednost sinusa
    return rezultat;
}

// Funkcija za konvertovanje stepeni u radijane
// Formula: radijani = stepeni * PI / 180
double stepeni_u_radijane(double stepeni) {
    return stepeni * M_PI / 180.0;
}

// Glavna funkcija programa
int main() {
    // Deklarisemo promenljive
    double ugao_stepeni;    // Ugao u stepenima
    double ugao_radijani;   // Ugao u radijanima
    double tejlorov_rez;    // Rezultat Tejlorovog razvoja
    double ugradjeni_rez;   // Rezultat ugradjene sin() funkcije
    double greska;          // Razlika (greska) izmedju dve metode
    int i;                  // Brojac za petlju

    // Definisemo niz uglova koje zelimo da testiramo (u stepenima)
    double uglovi[] = {0, 30, 45, 60, 90, 120, 150, 180, 270, 360};

    // Racunamo broj elemenata u nizu
    // sizeof(uglovi) daje ukupnu velicinu niza u bajtovima
    // sizeof(uglovi[0]) daje velicinu jednog elementa u bajtovima
    // Njihov odnos daje broj elemenata
    int broj_uglova = sizeof(uglovi) / sizeof(uglovi[0]);

    // Definisemo broj clanova Tejlorovog reda koji cemo koristiti
    int n_clanova = 10;

    // Ispisujemo naslov programa
    printf("========================================================\n");
    printf(" Poredjenje Tejlorovog razvoja i ugradjene sin funkcije\n");
    printf("========================================================\n");
    printf("Broj clanova Tejlorovog reda: %d\n\n", n_clanova);

    // TABELA 1: Odabrani uglovi
    printf("TABELA 1: Odabrani glavni uglovi\n");
    printf("========================================================================\n");
    printf("| Ugao |  sin(Tejlorov)  | sin(ugradjena)  |    Razlika    | Greska %% |\n");
    printf("|------|-----------------|-----------------|---------------|----------|\n");

    // Prolazimo kroz sve uglove iz niza
    for (i = 0; i < broj_uglova; i++) {
        // Uzimamo trenutni ugao u stepenima
        ugao_stepeni = uglovi[i];

        // Konvertujemo ugao iz stepeni u radijane
        // Ovo je neophodno jer trigonometrijske funkcije koriste radijane
        ugao_radijani = stepeni_u_radijane(ugao_stepeni);

        // Racunamo sinus pomocu Tejlorovog razvoja
        tejlorov_rez = tejlorov_sinus(ugao_radijani, n_clanova);

        // Racunamo sinus pomocu ugradjene funkcije iz math.h
        ugradjeni_rez = sin(ugao_radijani);

        // Racunamo apsolutnu gresku (razliku) izmedju dve metode
        greska = tejlorov_rez - ugradjeni_rez;
        // Uzimamo apsolutnu vrednost greske
        if (greska < 0) {
            greska = -greska;
        }

        // Racunamo procenat greske (relativna greska u procentima)
        double procenat_greske = 0.0;
        // Izbegavamo deljenje sa nulom
        if (ugradjeni_rez != 0.0) {
            procenat_greske = (greska / ugradjeni_rez) * 100.0;
        }

        // Ispisujemo rezultate u tabelarnom formatu
        // %5.0f - ispisuje ugao sa 5 karaktera bez decimala
        // %15.12f - ispisuje broj sa 15 karaktera i 12 decimala
        // %13.10e - ispisuje razliku u naucnoj notaciji
        // %8.4f - ispisuje procenat sa 4 decimale
        printf("| %4.0f | %15.12f | %15.12f | %13.10e | %7.4f%% |\n",
               ugao_stepeni, tejlorov_rez, ugradjeni_rez, greska, procenat_greske);
    }

    printf("========================================================================\n\n");

    // TABELA 2: Svi uglovi od 0 do 360 stepeni na svakih 15 stepeni
    printf("TABELA 2: Kompletna tabela - uglovi od 0 do 360 stepeni (korak 15)\n");
    printf("========================================================================\n");
    printf("| Ugao |  sin(Tejlorov)  | sin(ugradjena)  |    Razlika    | Greska %% |\n");
    printf("|------|-----------------|-----------------|---------------|----------|\n");

    // Prolazimo kroz sve uglove od 0 do 360 na svakih 15 stepeni
    for (ugao_stepeni = 0; ugao_stepeni <= 360; ugao_stepeni += 15) {
        // Konvertujemo ugao iz stepeni u radijane
        ugao_radijani = stepeni_u_radijane(ugao_stepeni);

        // Racunamo sinus pomocu Tejlorovog razvoja
        tejlorov_rez = tejlorov_sinus(ugao_radijani, n_clanova);

        // Racunamo sinus pomocu ugradjene funkcije
        ugradjeni_rez = sin(ugao_radijani);

        // Racunamo apsolutnu gresku
        greska = tejlorov_rez - ugradjeni_rez;
        if (greska < 0) {
            greska = -greska;
        }

        // Racunamo procenat greske
        double procenat_greske = 0.0;
        if (ugradjeni_rez != 0.0) {
            procenat_greske = (greska / ugradjeni_rez) * 100.0;
        }

        // Ispisujemo redak tabele
        printf("| %4.0f | %15.12f | %15.12f | %13.10e | %7.4f%% |\n",
               ugao_stepeni, tejlorov_rez, ugradjeni_rez, greska, procenat_greske);
    }

    printf("========================================================================\n\n");

    // Ispisujemo dodatne informacije
    printf("\n========================================================\n");
    printf("Napomena:\n");
    printf("- Uglovi su dati u stepenima, ali se racunaju u radijanima\n");
    printf("- Greska pokazuje razliku izmedju dve metode\n");
    printf("- Sa vise clanova Tejlorovog reda, greska je manja\n");
    printf("- Uglovi se SVODE na interval [-PI, PI] za bolju konvergenciju!\n");
    printf("  (Tejlorov red lose konvergira za velike uglove)\n");
    printf("========================================================\n\n");

    // Dodatni test: prikaz konvergencije Tejlorovog reda
    printf("\nPrikaz konvergencije Tejlorovog reda za ugao od 90 stepeni:\n");
    printf("-----------------------------------------------------------\n");

    // Postavljamo ugao na 90 stepeni (pi/2 radijana)
    ugao_stepeni = 90.0;
    ugao_radijani = stepeni_u_radijane(ugao_stepeni);

    // Racunamo tacnu vrednost pomocu ugradjene funkcije
    ugradjeni_rez = sin(ugao_radijani);

    // Ispisujemo zaglavlje za tabelu konvergencije
    printf("Broj clanova | Tejlorov rezultat | Greska\n");
    printf("-------------+-------------------+-----------\n");

    // Testiramo sa razlicitim brojem clanova (od 1 do 15)
    for (i = 1; i <= 15; i++) {
        // Racunamo sinus sa i clanova
        tejlorov_rez = tejlorov_sinus(ugao_radijani, i);

        // Racunamo gresku
        greska = tejlorov_rez - ugradjeni_rez;
        if (greska < 0) {
            greska = -greska;
        }

        // Ispisujemo rezultat
        printf("%12d | %17.14f | %.2e\n", i, tejlorov_rez, greska);
    }

    // Ispisujemo poruku i cekamo na Enter
    printf("\nPritisnite Enter za izlaz...");

    // Cekamo da korisnik pritisne Enter pre zatvaranja programa
    getchar();

    // Vracamo 0 sto znaci uspesno izvrsenje programa
    return 0;
}

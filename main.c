#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FISIER_AUTOTURISME "autoturisme.txt"
#define MAX_AUTOTURISME 100

#define ANSI_COLOR_MOV "\x1b[35m"
#define ANSI_COLOR_ROZ "\x1b[95m"
#define ANSI_COLOR_CIAN "\x1b[36m"
#define ANSI_COLOR_ROSU "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

typedef struct
{
    char marca[50];
    char tip[50];
    int nrlocuri;
    int disponibil;
    float pretpezi;
    char nrinmatriculare[15];
} Autoturism;

void adaugare_auto(Autoturism autoturism[], int *numar_autoturisme);
void actualizare_auto(Autoturism autoturism[], int numar_autoturisme);
void stergere_auto(Autoturism autoturism[], int *numar_autoturisme);
void cautare_auto(Autoturism autoturism[], int numar_autoturisme);
void afisare_auto_disp(Autoturism autoturism[], int numar_autoturisme);
void afisare_toate_auto(Autoturism autoturism[], int numar_autoturisme);
void rezervare_auto(Autoturism autoturism[], int numar_autoturisme);
void anuleaza_rezervare(Autoturism autoturism[], int numar_autoturisme);
void meniu_principal();
void clearscreen();
void asteapta_enter();
int input_auto_fisier(Autoturism autoturism[], int *numar_autoturisme);
void salvare_auto_in_fisier(Autoturism autoturism[], int numar_autoturisme);

int main()
{
    int optiune;
    Autoturism autoturism[MAX_AUTOTURISME];
    int numar_autoturisme = 0;

    numar_autoturisme = input_auto_fisier(autoturism, &numar_autoturisme);

    do {
        clearscreen();
        meniu_principal();
        printf("Introduceti optiunea dorita: ");

        while (scanf("%d", &optiune) != 1) {
            printf("Optiune invalida! Introduceti un numar: ");
            while (getchar() != '\n');
        }
        getchar();

        clearscreen();

        switch (optiune)
        {
        case 1:
            adaugare_auto(autoturism, &numar_autoturisme);
            break;
        case 2:
            actualizare_auto(autoturism, numar_autoturisme);
            break;
        case 3:
            stergere_auto(autoturism, &numar_autoturisme);
            break;
        case 4:
            cautare_auto(autoturism, numar_autoturisme);
            break;
        case 5:
            afisare_auto_disp(autoturism, numar_autoturisme);
            break;
        case 6:
            rezervare_auto(autoturism, numar_autoturisme);
            break;
        case 7:
            anuleaza_rezervare(autoturism, numar_autoturisme);
            break;
         case 8:
            afisare_toate_auto(autoturism, numar_autoturisme);
            break;
        case 0:
            salvare_auto_in_fisier(autoturism, numar_autoturisme);
            printf("La revedere!\n");
            break;
        default:
            printf(ANSI_COLOR_ROSU"Optiune invalida!\n"ANSI_COLOR_RESET);
        }

        if (optiune != 0) {
             salvare_auto_in_fisier(autoturism, numar_autoturisme);
             asteapta_enter();
             clearscreen();
        }

    } while (optiune != 0);

    return 0;
}


void meniu_principal()
{
    printf("\n     Meniu Principal     \n");
    printf("---------------------------\n");
    printf("1. Adauga autoturism\n");
    printf("2. Actualizeaza autoturism\n");
    printf("3. Sterge autoturism\n");
    printf("4. Cauta autoturism\n");
    printf("5. Afiseaza autoturisme disponibile\n");
    printf("6. Rezerva autoturism\n");
    printf("7. Anuleaza rezervare\n");
    printf("8. Afiseaza toate autoturismele\n");
    printf("0. Iesire\n");
    printf("---------------------------\n");
}

void clearscreen()
{
    system("cls");
}

void asteapta_enter() {

  printf("Apasati Enter pentru a continua...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


void adaugare_auto(Autoturism autoturism[], int *numar_autoturisme)
{
    if (*numar_autoturisme >= MAX_AUTOTURISME) {
        printf(ANSI_COLOR_ROSU"Nu se mai pot adauga autoturisme (capacitate maxima atinsa!).\n"ANSI_COLOR_RESET);
        return;
    }

    Autoturism nou_autoturism;
    printf("\n     Adaugare Autoturism     \n");
    printf("-----------------------------\n");

    printf("%sIntroduceti marca autoturismului: %s",ANSI_COLOR_MOV,ANSI_COLOR_RESET);
    fgets(nou_autoturism.marca, sizeof(nou_autoturism.marca), stdin);
    nou_autoturism.marca[strcspn(nou_autoturism.marca, "\n")] = 0;

    printf("%sIntroduceti tipul autoturismului: %s",ANSI_COLOR_MOV,ANSI_COLOR_RESET);
    fgets(nou_autoturism.tip, sizeof(nou_autoturism.tip), stdin);
    nou_autoturism.tip[strcspn(nou_autoturism.tip, "\n")] = 0;

    printf("Introduceti numarul de locuri: ");
    while (scanf("%d", &nou_autoturism.nrlocuri) != 1 || nou_autoturism.nrlocuri <= 0) {
        printf("Numar invalid. Introduceti un numar pozitiv de locuri: ");
        while (getchar() != '\n');
    }
    getchar();

    printf("Introduceti pretul pe zi: ");
     while (scanf("%f", &nou_autoturism.pretpezi) != 1 || nou_autoturism.pretpezi < 0) {
        printf("Pret invalid. Introduceti un pret pozitiv: ");
        while (getchar() != '\n');
    }
    getchar();

    printf("Introduceti numarul de inmatriculare: ");
    fgets(nou_autoturism.nrinmatriculare, sizeof(nou_autoturism.nrinmatriculare), stdin);
    nou_autoturism.nrinmatriculare[strcspn(nou_autoturism.nrinmatriculare, "\n")] = 0;


    for (int i = 0; i < *numar_autoturisme; ++i) {
        if (strcmp(autoturism[i].nrinmatriculare, nou_autoturism.nrinmatriculare) == 0) {
            printf("Eroare: Un autoturism cu acest numar de inmatriculare exista deja!\n");
            return;
        }
    }


    nou_autoturism.disponibil = 1;

    autoturism[*numar_autoturisme] = nou_autoturism;
    (*numar_autoturisme)++;

    printf("Autoturism adaugat cu succes!\n");
}

void afisare_auto_disp(Autoturism autoturism[], int numar_autoturisme)
{
    int gasit = 0;
    printf("\n     Autoturisme Disponibile     \n");
    printf("---------------------------------\n");
    printf("Nr. | Marca        | Tip          | Locuri | Pret/Zi | Inmatriculare\n");
    printf("----|--------------|--------------|--------|---------|--------------\n");

    for (int i = 0; i < numar_autoturisme; i++)
    {
        if (autoturism[i].disponibil == 1)
        {
            gasit = 1;
            printf("%-3d | " ANSI_COLOR_MOV "%-12s" ANSI_COLOR_RESET " | " ANSI_COLOR_MOV "%-12s" ANSI_COLOR_RESET " | %-6d | %s%-7.2f%s | "ANSI_COLOR_ROZ"%-13s"ANSI_COLOR_RESET "\n",
                   i + 1,
                   autoturism[i].marca,
                   autoturism[i].tip,
                   autoturism[i].nrlocuri,
                   ANSI_COLOR_CIAN,autoturism[i].pretpezi,ANSI_COLOR_RESET,
                   autoturism[i].nrinmatriculare);
        }
    }
    if (!gasit) {
        printf("Nu exista autoturisme disponibile.\n");
    }
     printf("--------------------------------------------------------------\n");
}

void afisare_toate_auto(Autoturism autoturism[], int numar_autoturisme)
{
    printf("\n       Toate Autoturismele       \n");
    printf("---------------------------------\n");
    printf("Nr. | Marca        | Tip          | Locuri | Pret/Zi | Inmatriculare | Status\n");
    printf("----|--------------|--------------|--------|---------|---------------|----------\n");

    if (numar_autoturisme == 0) {
        printf("Nu exista autoturisme inregistrate.\n");
    } else {
        for (int i = 0; i < numar_autoturisme; i++)
        {
           printf("%-3d | " ANSI_COLOR_MOV "%-12s" ANSI_COLOR_RESET " | " ANSI_COLOR_MOV "%-12s" ANSI_COLOR_RESET " | %-6d | %s%-7.2f%s | "ANSI_COLOR_ROZ"%-13s"ANSI_COLOR_RESET" | %s\n",
                   i + 1,
                   autoturism[i].marca,
                   autoturism[i].tip,
                   autoturism[i].nrlocuri,
                    ANSI_COLOR_CIAN,autoturism[i].pretpezi,ANSI_COLOR_RESET,
                   autoturism[i].nrinmatriculare,
                   autoturism[i].disponibil ? "Disponibil" : "Rezervat");
        }
    }
     printf("-------------------------------------------------------------------------\n");
}


void actualizare_auto(Autoturism autoturism[], int numar_autoturisme)
{
     if (numar_autoturisme == 0) {
        printf("Nu exista autoturisme de actualizat.\n");
        return;
    }

    int index;
    afisare_toate_auto(autoturism, numar_autoturisme);

    printf("\nIntroduceti numarul autoturismului pe care doriti sa il actualizati (0 pentru a anula): ");
    while (scanf("%d", &index) != 1 || index < 0 || index > numar_autoturisme) {
        printf("Numar invalid. Introduceti un numar intre 1 si %d (sau 0): ", numar_autoturisme);
        while (getchar() != '\n');
    }
    getchar();

    if (index == 0) {
      printf("Actualizare anulata.\n");
        return;
    }

    index--;

   printf("\nActualizare detalii pentru: "ANSI_COLOR_MOV"%s %s"ANSI_COLOR_RESET" ("ANSI_COLOR_ROZ"%s"ANSI_COLOR_RESET")\n", autoturism[index].marca, autoturism[index].tip, autoturism[index].nrinmatriculare);

    Autoturism auto_actualizat = autoturism[index];

    printf("Introduceti noua marca (lasati gol pentru a pastra '%s'): ", auto_actualizat.marca);
    char input_buffer[100];
    fgets(input_buffer, sizeof(input_buffer), stdin);
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    if (strlen(input_buffer) > 0) {
        strcpy(auto_actualizat.marca, input_buffer);
    }

    printf("Introduceti noul tip (lasati gol pentru a pastra '%s'): ", auto_actualizat.tip);
    fgets(input_buffer, sizeof(input_buffer), stdin);
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    if (strlen(input_buffer) > 0) {
        strcpy(auto_actualizat.tip, input_buffer);
    }

    printf("Introduceti noul numar de locuri (lasati gol pt a pastra '%d'): ", auto_actualizat.nrlocuri);
    fgets(input_buffer, sizeof(input_buffer), stdin);
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    if (strlen(input_buffer) > 0) {
        int nrlocuri_nou;
        if (sscanf(input_buffer, "%d", &nrlocuri_nou) == 1 && nrlocuri_nou > 0) {
            auto_actualizat.nrlocuri = nrlocuri_nou;
        } else {
            printf("Numar de locuri invalid, valoarea anterioara '%d' a fost pastrata.\n", auto_actualizat.nrlocuri);
        }
    }


    printf("Introduceti noul pret pe zi (lasati gol pt a pastra '%.2f'): ", auto_actualizat.pretpezi);
    fgets(input_buffer, sizeof(input_buffer), stdin);
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    if (strlen(input_buffer) > 0) {
         float pret_nou;
        if (sscanf(input_buffer, "%f", &pret_nou) == 1 && pret_nou >= 0) {
           auto_actualizat.pretpezi = pret_nou;
        } else {
             printf("Pret invalid, valoarea anterioara '%.2f' a fost pastrata.\n", auto_actualizat.pretpezi);
        }
    }


    printf("Introduceti noul numar de inmatriculare (lasati gol pt a pastra '%s'): ", auto_actualizat.nrinmatriculare);
    fgets(input_buffer, sizeof(input_buffer), stdin);
    input_buffer[strcspn(input_buffer, "\n")] = 0;
    if (strlen(input_buffer) > 0) {
        int duplicat = 0;
        for (int i = 0; i < numar_autoturisme; ++i) {
            if (i != index && strcmp(autoturism[i].nrinmatriculare, input_buffer) == 0) {
                duplicat = 1;
                break;
            }
        }
        if (duplicat) {
             printf("Eroare: Noul numar de inmatriculare '%s' este deja folosit! Valoarea anterioara '%s' a fost pastrata.\n", input_buffer, auto_actualizat.nrinmatriculare);
        } else {
            strcpy(auto_actualizat.nrinmatriculare, input_buffer);
        }
    }

    printf("Doriti sa modificati statusul de disponibilitate? (Actual: %s) (d/n): ", auto_actualizat.disponibil ? "Disponibil" : "Rezervat");
    char raspuns_status;
    scanf(" %c", &raspuns_status);
    getchar();
    if (tolower(raspuns_status) == 'd') {
        printf("Este autoturismul disponibil? (1 = Da, 0 = Nu): ");
        int status_nou;
         while (scanf("%d", &status_nou) != 1 || (status_nou != 0 && status_nou != 1)) {
             printf("Status invalid. Introduceti 1 pentru Da sau 0 pentru Nu: ");
            while (getchar() != '\n');
        }
        getchar();
        auto_actualizat.disponibil = status_nou;
    }


    autoturism[index] = auto_actualizat;

    printf("\nAutoturismul a fost actualizat cu succes!\n");
}


void stergere_auto(Autoturism autoturism[], int *numar_autoturisme)
{
     if (*numar_autoturisme == 0) {
       printf(ANSI_COLOR_ROSU"Nu exista autoturisme de sters.\n"ANSI_COLOR_RESET);
        return;
    }

    int index;
    afisare_toate_auto(autoturism, *numar_autoturisme);

    printf("\nIntroduceti numarul autoturismului pe care doriti sa il stergeti (0 pentru a anula): ");
     while (scanf("%d", &index) != 1 || index < 0 || index > *numar_autoturisme) {
        printf("Numar invalid. Introduceti un numar intre 1 si %d (sau 0): ", *numar_autoturisme);
        while (getchar() != '\n');
    }
    getchar();

    if (index == 0) {
       printf("Stergere anulata.\n");
        return;
    }

    index--;

   printf("Sunteti sigur ca doriti sa stergeti autoturismul: %s %s ("ANSI_COLOR_ROZ"%s"ANSI_COLOR_RESET")? (d/n): ",
           autoturism[index].marca, autoturism[index].tip, autoturism[index].nrinmatriculare);

    char confirmare;
    scanf(" %c", &confirmare);
    getchar();

    if (tolower(confirmare) == 'd') {
        for (int i = index; i < *numar_autoturisme - 1; i++)
 { autoturism[i] = autoturism[i + 1]; }

        (*numar_autoturisme)--;
        printf("Autoturism sters cu succes!\n");
    } else {
         printf("Stergerea a fost anulata.\n");
    }
}

void cautare_auto(Autoturism autoturism[], int numar_autoturisme)
{
    if (numar_autoturisme == 0) {
         printf("Nu exista autoturisme inregistrate.\n");
        return;
    }

    char criteriu_cautare[50];
    int gasit = 0;

    printf("\n     Cautare Autoturism     \n");
    printf("----------------------------\n");
    printf("Introduceti marca, tipul sau numarul de inmatriculare: ");
    fgets(criteriu_cautare, sizeof(criteriu_cautare), stdin);
    criteriu_cautare[strcspn(criteriu_cautare, "\n")] = 0;

    printf("\nRezultate cautare pentru '%s':\n", criteriu_cautare);
    printf("Nr. | Marca        | Tip          | Locuri | Pret/Zi | Inmatriculare | Status\n");
    printf("----|--------------|--------------|--------|---------|---------------|----------\n");


    for (int i = 0; i < numar_autoturisme; i++) {

        char marca_lower[50], tip_lower[50], nrinmatriculare_lower[15], criteriu_lower[50];
        int k = 0;
        while(autoturism[i].marca[k]) { marca_lower[k] = tolower(autoturism[i].marca[k]); k++; }
        marca_lower[k] = '\0';
        k = 0;
         while(autoturism[i].tip[k]) { tip_lower[k] = tolower(autoturism[i].tip[k]); k++; }
        tip_lower[k] = '\0';
        k = 0;
         while(autoturism[i].nrinmatriculare[k]) { nrinmatriculare_lower[k] = tolower(autoturism[i].nrinmatriculare[k]); k++; }
        nrinmatriculare_lower[k] = '\0';
         k = 0;
         while(criteriu_cautare[k]) { criteriu_lower[k] = tolower(criteriu_cautare[k]); k++; }
        criteriu_lower[k] = '\0';


        if (strstr(marca_lower, criteriu_lower) != NULL ||
            strstr(tip_lower, criteriu_lower) != NULL ||
            strstr(nrinmatriculare_lower, criteriu_lower) != NULL)
        {
            gasit = 1;
           printf("%-3d | " ANSI_COLOR_MOV "%-12s" ANSI_COLOR_RESET " | " ANSI_COLOR_MOV "%-12s" ANSI_COLOR_RESET" | %-6d | %s%-7.2f%s | "ANSI_COLOR_ROZ"%-13s"ANSI_COLOR_RESET" | %s\n",
                 i + 1,
                  autoturism[i].marca,
                 autoturism[i].tip,
                autoturism[i].nrlocuri,
                   ANSI_COLOR_CIAN, autoturism[i].pretpezi, ANSI_COLOR_RESET,
                autoturism[i].nrinmatriculare,
              autoturism[i].disponibil ? "Disponibil" : "Rezervat");
        }
    }

    if (!gasit) {
       printf("Nu s-a gasit niciun autoturism care sa corespunda criteriului '%s'.\n", criteriu_cautare);
    }
     printf("-------------------------------------------------------------------------\n");
}


void rezervare_auto(Autoturism autoturism[], int numar_autoturisme)
{
     if (numar_autoturisme == 0) {
          printf("Nu exista autoturisme in sistem.\n");
        return;
    }

    int index;
    int count_disponibile = 0;


    for(int i=0; i<numar_autoturisme; ++i) {
        if (autoturism[i].disponibil == 1) {
            count_disponibile++;
        }
    }

    if (count_disponibile == 0) {
          printf("\nToate autoturismele sunt momentan rezervate.\n");
         return;
    }


    afisare_auto_disp(autoturism, numar_autoturisme);

    printf("\nIntroduceti numarul autoturismului pe care doriti sa il rezervati (conform listei de mai sus, 0 pentru a anula): ");
     while (scanf("%d", &index) != 1 || index < 0 || index > numar_autoturisme) {
        printf("Numar invalid. Introduceti un numar valid din lista (sau 0): ");
        while (getchar() != '\n');
    }
    getchar();

     if (index == 0) {
       printf("Rezervare anulata.\n");
        return;
    }

    index--;
     if (index >= 0 && index < numar_autoturisme) {
              if (autoturism[index].disponibil == 1) {
                  autoturism[index].disponibil = 0;
                     printf("Autoturismul '"ANSI_COLOR_MOV"%s %s"ANSI_COLOR_RESET"' ("ANSI_COLOR_ROZ"%s"ANSI_COLOR_RESET") a fost rezervat cu succes!\n",
                   autoturism[index].marca, autoturism[index].tip, autoturism[index].nrinmatriculare);
        } else {
              printf("Eroare: Autoturismul selectat nu este disponibil pentru rezervare (poate a fost rezervat intre timp).\n");
        }
    } else {
             printf("Index invalid sau autoturismul nu este in lista celor disponibile!\n");
    }
}

void anuleaza_rezervare(Autoturism autoturism[], int numar_autoturisme)
{
     if (numar_autoturisme == 0) {
           printf("Nu exista autoturisme in sistem.\n");
        return;
    }

    int index;
    int count_rezervate = 0;

    printf("\n     Anulare Rezervare     \n");
    printf("---------------------------\n");
    printf("Autoturisme Rezervate:\n");
    printf("Nr. | Marca        | Tip          | Inmatriculare\n");
    printf("----|--------------|--------------|--------------\n");

    for (int i = 0; i < numar_autoturisme; i++) {
        if (autoturism[i].disponibil == 0) {
           printf("%-3d | %-12s | %-12s | "ANSI_COLOR_ROZ"%s"ANSI_COLOR_RESET"\n",
                   i + 1,
                   autoturism[i].marca,
                   autoturism[i].tip,
                   autoturism[i].nrinmatriculare);
        }
    }

    if (count_rezervate == 0) {
      printf("Nu exista autoturisme rezervate.\n");
         printf("-------------------------------------------------\n");
        return;
    }
    printf("-------------------------------------------------\n");

    printf("\nIntroduceti numarul autoturismului pentru care doriti sa anulati rezervarea (conform listei, 0 pentru a anula): ");
     while (scanf("%d", &index) != 1 || index < 0 || index > numar_autoturisme) {
        printf("Numar invalid. Introduceti un numar valid din lista (sau 0): ");
        while (getchar() != '\n');
    }
    getchar();

     if (index == 0) {
        printf("Anulare rezervare anulata.\n");
         return;
    }

    index--;

    if (index >= 0 && index < numar_autoturisme) {
         if (autoturism[index].disponibil == 0)
         {
            autoturism[index].disponibil = 1;
               printf("Rezervarea pentru autoturismul '%s %s' ("ANSI_COLOR_ROZ"%s"ANSI_COLOR_RESET") a fost anulata cu succes!\n",
                   autoturism[index].marca, autoturism[index].tip, autoturism[index].nrinmatriculare);
            }
           else
           {
            printf("Eroare: Autoturismul selectat nu era rezervat.\n");
        }
    } else {
        printf("Index invalid!\n");
    }
}

int input_auto_fisier(Autoturism autoturism[], int *numar_autoturisme)
{
    FILE *fp;
    fp = fopen(FISIER_AUTOTURISME, "r");

    if (fp == NULL) {
         printf("Info: Fisierul '%s' nu a fost gasit. Va fi creat la prima salvare.\n", FISIER_AUTOTURISME);
        *numar_autoturisme = 0;
        return 0;
    }
 *numar_autoturisme = 0;
    char line[256];
    fgets(line, sizeof(line), fp);
    while (fgets(line, sizeof(line), fp) != NULL && *numar_autoturisme < MAX_AUTOTURISME) {
        int result = sscanf(line, "%49[^,],%49[^,],%d,%d,%f,%14[^\n]",
                  autoturism[*numar_autoturisme].marca,
                  autoturism[*numar_autoturisme].tip,
                  &autoturism[*numar_autoturisme].nrlocuri,
                  &autoturism[*numar_autoturisme].disponibil,
                  &autoturism[*numar_autoturisme].pretpezi,
                  autoturism[*numar_autoturisme].nrinmatriculare);

        if (result == 6) {
            if (autoturism[*numar_autoturisme].nrlocuri > 0 &&
                autoturism[*numar_autoturisme].pretpezi >= 0 &&
                (autoturism[*numar_autoturisme].disponibil == 0 || autoturism[*numar_autoturisme].disponibil == 1)) {
                 (*numar_autoturisme)++;
            } else {
                 printf("Avertisment: Linie invalida in fisier ignorata (date incorecte): %s", line);
            }
        } else if (strlen(line) > 1) {
             printf("Avertisment: Linie invalida in fisier ignorata (format incorect): %s", line);
        }
    }


    if (*numar_autoturisme >= MAX_AUTOTURISME && !feof(fp)) {
         printf("Atentie: S-a atins capacitatea maxima de %d autoturisme. Nu s-au mai incarcat altele din fisier.\n", MAX_AUTOTURISME);
    }
    fclose(fp);
     printf("Am incarcat %d autoturisme din fisier '%s'.\n", *numar_autoturisme, FISIER_AUTOTURISME);
    return *numar_autoturisme;
}

void salvare_auto_in_fisier(Autoturism autoturism[], int numar_autoturisme)
{
    FILE *fp;
    fp = fopen(FISIER_AUTOTURISME, "w");

    if (fp == NULL) {
        perror("Eroare critica: Nu am putut deschide fisierul pentru scriere");
         printf("Nu am putut deschide fisierul %s pentru scriere!\n");
        return;
    }
     fprintf(fp, "Marca,Tip,NrLocuri,Disponibil,PretPeZi,Inmatriculare\n");

    for (int i = 0; i < numar_autoturisme; i++) {
        fprintf(fp, "%s,%s,%d,%d,%.2f,%s\n",
                autoturism[i].marca,
                autoturism[i].tip,
                autoturism[i].nrlocuri,
                autoturism[i].disponibil,
                autoturism[i].pretpezi,
                autoturism[i].nrinmatriculare);
    }

    fclose(fp);
     printf("Am salvat %d autoturisme in fisier.\n", numar_autoturisme);
}

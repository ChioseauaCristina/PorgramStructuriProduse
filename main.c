#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct{
    char nume[100];
    int pret;
}produs;

produs produse[100];
int nproduse=0;

void populare();

void sortare_produse();

void afisare_produse();

int cautare(char nume_produs[]);

int adaugare_produs(produs p);

void stergere_produse(char nume_produs[]);

void salvare();

int main()
{
    populare();
    sortare_produse();


    printf("1.Cauta un produs dupa nume si, daca e gasit, ii afiseaza pretul\n");
    printf("2.Afiseaza toate produsele\n");
    printf("3. Adauga un nou produs\n");
    printf("4.Sterge un produs, dupa numele sau\n");
    printf("5.Salveaza in fisierul originar baza de date din memorie\n");
    printf("6.Iesire din program\n");

    int c;
    char numeProdus[100];
    produs p;

    int condition = 0;
    while (!condition)
    {
        printf("\nIntroduceti optiune:");
        scanf("%d", &c);
        getchar();
        switch(c)
        {
        case 1:
            printf("nume produs:");
            fgets(numeProdus, 30, stdin);
            numeProdus[strcspn(numeProdus, "\n")]='\0';
            printf("pret produs:");
            int pret = cautare(numeProdus);
            printf("%d", pret);
            break;
        case 2:
            afisare_produse();
            break;
        case 3:
            printf("nume produs:");
            scanf("%s", p.nume);
            printf("pret produs:");
            scanf("%d", &p.pret);

            if(adaugare_produs(p)) printf("am adaugat");
            else printf("depaseste numar maxim produse");
            break;
        case 4:
            printf("nume produs");
            scanf("%s", numeProdus);
            stergere_produse(numeProdus);
            break;
        case 5:
            salvare();
            break;
        case 6:
            condition = 1;
            break;
        default:
            printf("alege alta optiune");
            break;
        }
    }
    return 0;
}

void populare()
{
    FILE *fis;
    if((fis=fopen("fisier.txt", "r"))==NULL)
    {
        printf("eroare deschidere fisier");
        exit(EXIT_FAILURE);
    }

    char linie[100];
    while(fgets(linie, 100, fis)!=NULL)
    {
        printf("%s", linie);
        sscanf(linie, "%s %d", produse[nproduse].nume, &produse[nproduse].pret);
        nproduse++;
    }
    fclose(fis);
}

void afisare_produse()
{

    for(int i=0; i<nproduse; i++)
    {
        printf("\nprodus:%s;  pret:%d", produse[i].nume, produse[i].pret );
    }
}

int cautare(char nume_produs[])
{
    int pret=0;
    for(int i=0; i<nproduse; i++)
    {
        if(strcmp(produse[i].nume, nume_produs)==0)
            pret = produse[i].pret;
    }
    return pret;
}



int adaugare_produs(produs p)
{
    if(nproduse < 100)
    {

    int poz=-1;
    for(int i=0; i<nproduse; i++)
    {
        if(strcmp(produse[i].nume, p.nume) > 0)
        {
            poz=i;
            break;
        }
    }
    if(poz!=-1)
    {
        for(int i=nproduse-1; i>=poz; i--)
        {
            produse[i+1]=produse[i];
        }
        produse[poz]=p;
        nproduse++;
    }
    return TRUE;
    }
    else return FALSE;
}

void sortare_produse()
{
    produs aux;
    for(int i=0; i<nproduse-1; i++) {
        for(int j=i+1; j<nproduse; j++) {
            if(strcmp(produse[i].nume, produse[j].nume) > 0) {
                aux=produse[i];
                produse[i]=produse[j];
                produse[j]=aux;
            }
        }
    }
}

void stergere_produse(char nume_produs[])
{
    int poz=-1;
    for(int i=0; i<nproduse; i++)
    {
        if(!strcmp(produse[i].nume, nume_produs))
        {
            poz=i;
            break;
        }
    }
    if(poz!=-1)
    {
        for(int i=poz+1; i<nproduse; i++)
        {
            produse[i-1]=produse[i];
        }
        nproduse--;
    }
    else printf("produsul nu exista");
}

void salvare()
{
    FILE *fisout;
    if((fisout=fopen("fisier_out.txt", "w"))==NULL)
    {
        printf("eroare deschidere fisier");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<nproduse; i++)
    {
        fprintf(fisout, "\n%s  %d",  produse[i].nume, produse[i].pret);
    }
    fclose(fisout);
}


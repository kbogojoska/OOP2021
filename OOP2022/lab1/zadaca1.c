//
// Created by kbogojoska on 19.6.2022.
//

#include <stdio.h>

struct proizvod {
    char ime[20];
    float cena;
    float kolicina;
};
typedef struct proizvod proizvod;

void readProizvod(proizvod * p)
{
    scanf("%s %f %f", p->ime, &p->cena, &p->kolicina);
}

void printProizvod(proizvod p)
{
    printf("%s\t%.2f x %.1f = %.2f\n", p.ime, p.cena, p.kolicina, p.cena*p.kolicina);
}

void sum(proizvod p[], int n)
{
    float suma=0;
    for(int i=0; i<n; i++)
    {
        suma+=(p[i].cena*p[i].kolicina);
    }
    printf("Total: %.2f", suma);
}

int main()
{
    proizvod p[100];
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++)
    {
        readProizvod(p+i);

    }

    for(int i=0; i<n; i++)
    {
        printf("%d. ", i+1);
        printProizvod(p[i]);
    }

    sum(p, n);
    return 0;
}









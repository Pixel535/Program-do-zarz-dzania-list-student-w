#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char imie[20];
    char nazwisko[30];
    double srednia;
    char plec[1];
    struct student* next;


}student;

//Do Funkcji 1

void dodajstudenta(student** lista, student* nowy)
{
     nowy->next=NULL;
     if((*lista)==NULL)
     {
        *lista = nowy;
     }
     else
     {
        student* wsk = *lista;
         while((wsk)->next != NULL)
         {
            wsk = wsk->next;
         }
        wsk->next = nowy;
     }

}


void nowyStudent (student** lista)
{
    student* nowy = (student*)malloc(sizeof(student));
    printf("Podaj [imie] [nazwisko] [srednia] [plec]: ");
	scanf("%s %s %lf %s", nowy->imie, nowy->nazwisko, &nowy->srednia, nowy->plec);

    if(nowy->srednia>5 || nowy->srednia<2)
    {
        printf("Podana srednia nie nalezy do przedzialu");
        return -1;
    }

    dodajstudenta(lista, nowy);
}

//Do Funkcji 2

void pokazListe (student* lista)
{
    student* wsk = lista;
    int x = 1;
    printf("Lista studentow:\n");
    while (wsk != NULL)
    {
        printf("%d) %s %s %.2lf %s\n", x, wsk->imie, wsk->nazwisko, wsk->srednia, wsk->plec);
        wsk = wsk->next;
        ++x;
    }

	if(lista == NULL)
    {
        printf("Lista jest pusta\n");
    }


}

//Do Funkcji 3

int dlugosclisty(student* lista)
{
    int d = 0;
    student* wsk = lista;
    while(wsk != NULL)
    {
        d++;
        wsk = wsk->next;
    }
    return d;
}

void pokazStudenta(student* lista)
{
    int numer;
    printf("Podaj numer z listy: ");
    scanf("%d", &numer);


    if ((numer < 1) || (numer > dlugosclisty(lista)))
    {
        printf("Blad danych");
    }
    else
    {
        int i;
        student* wsk = lista;
        for(i = 1; i<numer; i++)
        {
            wsk = wsk->next;
        }
        printf(" %s %s %.2f %s", wsk->imie, wsk->nazwisko, wsk->srednia, wsk->plec);
    }

}


//Do Funkcji 4

int usun(char* imie, char* nazwisko, student** lista)
{
        student* poprzedni=NULL;
        student* wsk= *lista;

        while((wsk != NULL) && ( (strcmp(wsk->imie, imie) != 0) || (strcmp(wsk->nazwisko, nazwisko) != 0) ))
        {
                poprzedni = wsk;
                wsk = wsk->next;
        }

        if(wsk == NULL)
        {
            return 0;
        }
        else
        {
            if(poprzedni == NULL)
            {
                (*lista)=(*lista)->next;
                free(wsk);
            }
            else
            {
             poprzedni->next=wsk->next;
             free(wsk);
            }
            return 1;
        }
}

void usunStudentaPoIm(student** lista)
{
    char imie[20];
    char nazwisko[30];
    printf("Podaj imie i nazwisko studenta ktorego chcesz usunac: ");
    scanf("%s %s", imie, nazwisko);

    if(usun(imie, nazwisko, lista))
    {
        printf("Osoba zostala pomyslnie usunieta");
    }
    else
    {
        printf("Nie ma takiej osoby");
    }

}

//Do Funkcji 5

int usunPoNum(student** lista, int numer)
{
        student* poprzedni=NULL;
        student* wsk= *lista;
        int i;
        for(i=1; i<numer; i++)
        {
                poprzedni = wsk;
                wsk = wsk->next;
        }

        if(wsk == NULL)
        {
            return 0;
        }
        else
        {
            if(poprzedni == NULL)
            {
                (*lista)=(*lista)->next;
                free(wsk);
            }
            else
            {
             poprzedni->next=wsk->next;
             free(wsk);
            }
            return 1;
        }
}

void usunStudentaPoNum(student** lista)
{
    int i;
    printf("Podaj numer z listy studenta ktorego chcesz usunac: ");
    scanf("%d", &i);


    if((i<1) || (i>dlugosclisty(*lista)))
    {
        printf("Zly numer nie ma takiej osoby");
    }
    else
    {
        usunPoNum(lista, i);
        printf("Osoba zostala pomyslnie usunieta");
    }
}

//Do Funkcji 6

int wyswietlKobiety(student** lista)
{
    student* srednia = lista;
    int k = 1;
    double avg; //œrednia pobrana od u¿ytkownika
    printf("Podaj srednia: ");
    scanf("%lf", &avg);
    if((avg > 5) || (avg < 2))
    {
        printf("Podana srednia nie nalezy do przedzialu\n");
        return -1;
    }
    float min_roznica = 5.0;
    float roznica;


    while (srednia)
    {
        if(strcmp(srednia->plec, "k") == 0)
        {
            roznica = srednia->srednia;
            roznica = avg - roznica;
            roznica = roznica * roznica;
            roznica = sqrt(roznica);
            if (roznica< min_roznica)
            {
                min_roznica = roznica;
            }
        }
        srednia = srednia->next;
    }
     student* srednia2 = lista;
     while (srednia2 && (k == 1))
     {
            roznica = srednia2->srednia;
            roznica = avg - roznica;
            roznica = roznica * roznica;
            roznica = sqrt(roznica);
            if (roznica == min_roznica)
            {
                k = 0;
                printf ("Podana srednia wynosi: %.2f\n", avg);
                printf("Kobieta o najblizszej sredni to: %s %s", srednia2->imie, srednia2->nazwisko);
            }
            srednia2 = srednia2->next;
     }
     if(min_roznica == 5)
     {
         printf("Nie ma takiej kobiety\n");
     }
     return 0;
}

int main()
{
    int komenda;
	student* lista = NULL;
    printf("Program do zarzadzania lista studentow\n");
	printf("----------------------------------------------\n");
	printf("[0] Wyjscie z programu\n");
	printf("[1] Wprowadz dane nowego studenta\n");
	printf("[2] Wyswietl liste studentow\n");
	printf("[3] Wyswietl studenta ze wskazanej pozycji na liscie\n");
	printf("[4] Usun studenta o podanym imieniu i nazwisku\n");
	printf("[5] Usun studenta ze wskazanej pozycji na liscie\n");
	printf("[6] Wyswietl dane kobiety o sredniej najbardziej zblizonej do wprowadzonej\n");
	printf("----------------------------------------------\n\n");


	while(1)
    {
		printf("\nWybrana komenda: ");
		scanf("%d", &komenda);
		printf("\n");
		switch (komenda)
		{
			case 0: return 0; break;
			case 1: nowyStudent(&lista); break;
			case 2: pokazListe(lista); break;
			case 3: pokazStudenta(lista); break;
			case 4: usunStudentaPoIm(&lista); break;
			case 5: usunStudentaPoNum(&lista); break;
			case 6: wyswietlKobiety(lista); break;

        }
    }

    return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include "header.h"

int main()
{
	int izb, izb2, pro;
	pro = provjera();
	
	if (pro == -1)
	{
		system("pause");
		return 0;
	}

	do {
		printf("***GLAVNI IZBORNIK***\n\t1) Izmjena postojecega stanja kolicine (unos/otpis)\n\t2) Izmjena artikala\n\t3) Pregled liste stanja\n\t4)\
 Sortiranje liste stanja - abecedno\n\t5) Ispravak stanja prethodnih radnih dana\n\t6) Pregled obracuna prethodnih radnih dana\n\t7) ZAKLJUCAK RADNOGA DAN\
A\n\t0) Izlaz\n\tVas odabir: ");
		scanf("%d", &izb);
		if (izb < 0 || izb>7)
			izb = 8;
		switch (izb)
		{



		case 1:
			do
			{
				printf("\n\tIZMIJENA POSTOJECEGA STANJA\n\t\t1) Unos robe (kolicine)\n\t\t2) Otpis robe (kolicine)\n\t\t0) Povratak u glavni izborn\ik\n\t\tVas odabir: ");
				scanf("%d", &izb2);
				switch (izb2)
				{
				case 1:
					unosRobe();
					break;
				case 2:
					otpisRobe();
					break;
				case 0:
					break;
				default:
					printf("\n\t\tUNIJELI STE KRIVU VRIJEDNOST! Pokusajte ponovno!\n\n\t\t");
					system("pause");
					break;
				}
			} while (izb2 < 0 || izb2 > 2);
			break;



		case 2:
			do
			{
				printf("\n\tIZMIJENA ARTIKALA\n\t\t1) Unos novoga artikla\n\t\t2) Brisanje postojecega artikla\n\t\t3) Izmjena naziva postojecega artikla\n\t\t4) Izmjena\
 cijene postojecega artikla\n\t\t0) Povrat\
ak u glavni izbornik\n\t\tVas odabir: ");
				scanf("%d", &izb2);
				switch (izb2)
				{
				case 1:
					unosNovogaArtikla();
					break;
				case 2:
					brisanjeArtikla();
					break;
				case 3:
					izmjenaNaziva();
					break;
				case 4:
					izmjenaCijene();
					break;
				case 0:
					break;
				default:
					printf("\n\t\tUNIJELI STE KRIVU VRIJEDNOST! Pokusajte ponovno!\n\n\t\t");
					system("pause");
					break;
				}
			} while (izb2 < 0 || izb2 > 4);
			break;


		case 3:
			printf("\n\t\tLISTA STANJA:\n");
			listaStanja();
			printf("\t\t");
			system("pause");
			break;



		case 4:
			do {
				printf("\n\tSORTIRANJE LISTE STANJA - abecedno\n\t\t1) Sortiraj\n\t\t0) Povratak u glavni izbornik\n\t\tVas odabir: ");
				scanf("%d", &izb2);
				switch (izb2)
				{
				case 1:
					sortiranjeArtikala();
					break;
				case 0:
					break;
				default:
					printf("\n\t\tUNIJELI STE KRIVU VRIJEDNOST! Pokusajte ponovno!\n\n\t\t");
					system("pause");
					break;
				}
			} while (izb2 < 0 || izb2 > 1);
			break;



		case 5:
			printf("\n\tISPRAVAK STANJA PRETHODNIH RADNIH DANA");
			ispravakStanja();
			break;



		case 6:
			printf("\n\tPREGLED OBRACUNA PRETHODNIH RADNIH DANA");
			pregledObracuna();
			break;



		case 7:
			zakljucakRadnogaDana();
			break;



		case 0:
			return 0;
			break;

		default:
			printf("\n\tUNIJELI STE KRIVU VRIJEDNOST! Pokusajte ponovno!\n\n\t");
			system("pause");
			printf("\n\n");
		}
		printf("\n");
		izb = 1;
	} while (izb = !0);
	return 0;
}
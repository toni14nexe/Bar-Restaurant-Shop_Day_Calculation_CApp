#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "header.h"



// POMOCNE FUNKCIJE

int brojArtikala()
{
	int br = 0;
	FILE* fp;
	fp = fopen("num.txt", "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'num.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
		fscanf(fp, "%d", &br);
	fclose(fp);
	return br;
}



ARTIKLI* alokacijaStrukture(int novi)
{
	int br;
	char nebzn[2];
	br = brojArtikala();
	ARTIKLI *artikl = NULL;
	FILE* fp;
	fp = fopen("stanje.txt", "r");
	artikl = (ARTIKLI*)calloc(br + novi, sizeof(ARTIKLI));
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
	{
		for (int i = 0; i < br; i++)
		{
			fscanf(fp, "%s %s %f %f %f\n", nebzn, artikl[i].naziv, &artikl[i].kolicina, &artikl[i].cijena1kom, &artikl[i].ukupnaVrijednost);
			artikl[i].ukupnaVrijednost = artikl[i].kolicina * artikl[i].cijena1kom;
		}
	}
	fclose(fp);
	return artikl;
}



int provjera()
{
	int provjera = -1, br;
	float kolicina, cijena1kom, ukupnaVrijednost;
	char nebzn, naziv[21];
	br = brojArtikala();
	FILE *fp;
	fp = fopen("stanje.txt", "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
	{
		for (int i = 0; i < br; i++)
		{
			fscanf(fp, "%c\n%s\n%f\n%f\n%f\n", &nebzn, naziv, &kolicina, &cijena1kom, &ukupnaVrijednost);
			if (nebzn != '/')
			{
				printf("\n\t\tERROR: Postoji problem s dadotekom 'stanje.txt' ili 'num.txt' (neispravna ili ne postoji)!\n\n");
				return provjera;
			}
		}
		provjera = 0;
	}
	fclose(fp);
	return provjera;
}



// 1) UNOS & OTPIS

int unosRobe()
{
	int br = 0;
	float staraKolicina = 0;
	ARTIKLI *artikl;
	artikl = alokacijaStrukture(0);
	br = brojArtikala();
	FILE* fp;
	fp = fopen("stanje.txt", "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
	{
		printf("\n\t\t\tUnesite kolicinu nove robe za:\n");
		for (int i = 0; i < br; i++)
		{
			printf("\t\t\t   %s: ", artikl[i].naziv);
			staraKolicina = artikl[i].kolicina;
			scanf("%f", &artikl[i].kolicina);
			if (artikl[i].kolicina < 0)
			{
				printf("\n\n\t\tERROR - unesen je neispravan broj!\n");
				return 0;
			}
			artikl[i].kolicina += staraKolicina;
			artikl[i].ukupnaVrijednost = artikl[i].kolicina * artikl[i].cijena1kom;
		}
		fclose(fp);
		fp = fopen("stanje.txt", "w+");
		fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[0].naziv, artikl[0].kolicina, artikl[0].cijena1kom, artikl[0].ukupnaVrijednost);
		fp = fopen("stanje.txt", "a+");
		for (int i = 0; i < br; i++)
		{
			fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
		}
	}
	fclose(fp);
	free(artikl);
}



int otpisRobe()
{
	int br = 0;
	float staraKolicina = 0;
	ARTIKLI *artikl;
	artikl = alokacijaStrukture(0);
	br = brojArtikala();
	FILE* fp;
	fp = fopen("stanje.txt", "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
	{
		printf("\n\t\t\tUnesite kolicinu otpisa robe za:\n");
		for (int i = 0; i < br; i++)
		{
			printf("\t\t\t   %s: ", artikl[i].naziv);
			staraKolicina = artikl[i].kolicina;
			scanf("%f", &artikl[i].kolicina);
			if (artikl[i].kolicina > staraKolicina)
			{
				printf("\n\nERROR - unesen je preveliki broj!\n\n");
				return 0;
			}
			else if (artikl[i].kolicina < 0)
			{
				printf("\n\n\t\tERROR - unesen je neispravan broj!\n");
				return 0;
			}
			artikl[i].kolicina = staraKolicina - artikl[i].kolicina;
			artikl[i].ukupnaVrijednost = artikl[i].kolicina * artikl[i].cijena1kom;
		}
		fp = fopen("stanje.txt", "w+");
		fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[0].naziv, artikl[0].kolicina, artikl[0].cijena1kom, artikl[0].ukupnaVrijednost);
		fp = fopen("stanje.txt", "a+");
		for (int i = 0; i < br; i++)
		{
			fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
		}
	}
	fclose(fp);
	free(artikl);
}



// 2) IZMJENA ARTIKLA

int unosNovogaArtikla()
{
	FILE* fp;
	fp = fopen("stanje.txt", "a+");
	int br = 0, art;
	char nebzn = '/', art1;
	br = brojArtikala();
	printf("\n\n\t\tKoliko novih artikala zelite unjeti: ");
	scanf("%d", &art);
	if (art < 0)
	{
		printf("\n\n\t\tERROR - unesen je neispravan broj!\n");
		fclose(fp);
		return 0;
	}
	else
	{
		ARTIKLI *artikl;
		artikl = alokacijaStrukture(art);
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
			return 0;
		}
		else
		{
			for (int i = 0; i < art; i++)
			{
				printf("\n\t\t\tUnesite naziv novoga artikla (koristiti _ umjesto razmaka): ");
				scanf("%s", artikl[br + i].naziv);
				printf("\t\t\tUnesite kolicinu novoga artikla: ");
				scanf("%f", &artikl[br + i].kolicina);
				printf("\t\t\tUnesite cijenu novoga artikla (1 kom): ");
				scanf("%f", &artikl[br + i].cijena1kom);
				artikl[br + i].ukupnaVrijednost = artikl[br + i].kolicina * artikl[br + i].cijena1kom;
				fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[br + i].naziv, artikl[br + i].kolicina, artikl[br + i].cijena1kom, artikl[br + i].ukupnaVrijednost);
			}
			fclose(fp);
			fp = fopen("stanje.txt", "w+");
			for (int i = 0; i < br + art; i++)
			{
				fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
			}
			fclose(fp);
			br = brojArtikala();
			fp = fopen("num.txt", "r+");
			fprintf(fp, "%d", br + art);
			fclose(fp);
			free(artikl);
		}
	}
}



int brisanjeArtikla()
{
	int br = 0, obr = 0, rbr = 0;
	ARTIKLI *artikl;
	artikl = alokacijaStrukture(0);
	br = brojArtikala();
	do {
		printf("\n\t\t\tKoliko artikala zelite obrisati: ");
		scanf("%d", &obr);
		if (obr < 0 || obr > br)
		{
			printf("\n\n\t\t\tERROR - unesen je neispravan broj!\n\t\t\tPOKUSAJTE PONOVNO!\n");
		}
		else if (obr == 0)
		{
			return 0;
			system("pause");
		}
	} while (obr < 0 || obr > br);

	if (obr == br)
	{
		FILE* fp;
		fp = fopen("stanje.txt", "w+");
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
			return 0;
		}
		else
		{
			fprintf(fp, "");
		}
		fclose(fp);
		fp = fopen("num.txt", "w+");
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'num.txt' je neispravna ili ne postoji!\n\n");
			return 0;
		}
		else
		{
			fprintf(fp, "0");
			fclose(fp);
			return 0;
		}
	}

	else if (obr == 1)
	{
		listaStanja();
		printf("\n\t\t\tUpisite redni broj artikla kojega zelite obrisati: ");
		scanf("%d", &rbr);
		if (rbr < 1 || rbr > br)
		{
			printf("\n\n\t\tERROR - unesen je neispravan broj!\n");
			return 0;
		}
		rbr -= 1;
		FILE* fp;
		fp = fopen("stanje.txt", "w+");
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
			fclose(fp);
			return 0;
		}
		else
		{
			for (int i = 0; i < br; i++)
			{
				if (i != rbr)
				{
					fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
				}
			}
			fclose(fp);
		}
		fp = fopen("num.txt", "w+");
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'num.txt' je neispravna ili ne postoji!\n\n");
			fclose(fp);
			return 0;
		}
		else
		{
			fprintf(fp, "%d", br - 1);
			fclose(fp);
		}
	}

	else
	{
		{
			FILE* fp;
			listaStanja();
			fp = fopen("stanje.txt", "w+");
			if (fp == NULL)
			{
				printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
				return 0;
			}
			else
			{
				printf("\n");
				fclose(fp);
				for (int i = 0; i < obr; i++)
				{
					fp = fopen("stanje.txt", "w+");
					printf("\n\t\t\tUpisite redni broj %d. artikla kojega zelite obrisati: ", i + 1);
					scanf("%d", &rbr);
					if (rbr < 1 || rbr > br)
					{
						printf("\n\n\t\tERROR - unesen je neispravan broj!\n");
						return 0;
					}
					rbr -= 1;
					for (int i = 0; i < br; i++)
					{
						if (i != rbr)
						{
							fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
						}
					}
					fclose(fp);
				}
			}
			fp = fopen("num.txt", "w+");
			if (fp == NULL)
			{
				printf("\n\t\t\tDatoteka 'num.txt' je neispravna ili ne postoji!\n\n");
				return 0;
			}
			else
			{
				fprintf(fp, "%d", br - obr);
			}
		}
	}
	free(artikl);
}



int izmjenaNaziva()
{
	int br = 0, izm = 0;
	ARTIKLI *artikl;
	artikl = alokacijaStrukture(0);
	br = brojArtikala();
	FILE* fp;
	fp = fopen("stanje.txt", "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
	{
		printf("\n\t\t\tOdaberite redni broj artikla ciji naziv zelite izmijeniti\n");
		listaStanja();
		printf("\t\t\tVas odabir: ");
		scanf("%d", &izm);
		izm -= 1;
		printf("\n\t\t\t\tStari naziv: %s\n\t\t\t\tNovi naziv (koristiti _ umjesto razmaka): ", artikl[izm].naziv);
		scanf("%19s", artikl[izm].naziv);
		printf("%d", br);
		fp = fopen("stanje.txt", "w+");
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
			return 0;
		}
		else
		{
			for (int i = 0; i < br; i++)
			{
				fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
			}
		}
	}
	fclose(fp);
	free(artikl);
}



int izmjenaCijene()
{
	int br = 0, izm = 0;
	ARTIKLI *artikl;
	artikl = alokacijaStrukture(0);
	br = brojArtikala();
	FILE* fp;
	fp = fopen("stanje.txt", "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
	{
		printf("\n\t\t\tOdaberite redni broj artikla ciju cijenu zelite izmijeniti\n");
		listaStanja();
		printf("\t\t\tVas odabir: ");
		scanf("%d", &izm);
		izm -= 1;
		printf("\n\t\t\t\tStara cijena: %.2f\n\t\t\t\tNova cijena: ", artikl[izm].cijena1kom);
		scanf("%f", &artikl[izm].cijena1kom);
		fp = fopen("stanje.txt", "w+");
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
			return 0;
		}
		else
		{
			for (int i = 0; i < br; i++)
			{
				fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
			}
		}
	}
	fclose(fp);
	free(artikl);
}



// 3) LISTA STANJA

void listaStanja()
{
	int br = 0;
	ARTIKLI *artikl;
	artikl = alokacijaStrukture(0);
	br = brojArtikala();
	for (int i = 0; i < br; i++)
	{
		printf("\n\t\t%d.\t%s\n\t\t\tKolicina: %.2f\n\t\t\tCijena: %.2f\n\t\t\tUkupna vrijednost: %.2f\n\t\t\t", i + 1, artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
	}
	printf("\n");
	free(artikl);
}



// 4) SORTIRANJE ARTIKALA

int sortiranjeArtikala()
{
	int br, sl = 0;
	ARTIKLI artikl1;
	ARTIKLI *artikl;
	artikl = alokacijaStrukture(0);
	br = brojArtikala();
	FILE* fp;
	fp = fopen("stanje.txt", "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
		return 0;
	}
	else
	{
		for (int i = 0; i < br; i++)
		{
			for (int j = i + 1; j < br; j++)
			{
				for (sl = 0; sl < 20;)
				{
					if (artikl[i].naziv[sl] == artikl[j].naziv[sl])
					{
						sl++;
					}
					else
					{
						break;
					}
				}
				if (artikl[i].naziv[sl] > artikl[j].naziv[sl])
				{
					artikl1 = artikl[i];
					artikl[i] = artikl[j];
					artikl[j] = artikl1;
				}
			}
		}

		fp = fopen("stanje.txt", "w+");

		for (int i = 0; i < br; i++)
		{
			fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
		}
	}
	fclose(fp);
	free(artikl);
}



// 5) ISPRAVAK STANJA

int ispravakStanja()
{
	int br, odg=0;
	float troskovi = 0, novci = 0, promet = 0, baksa = 0, kol = 0;
	char naziv[35], nebzn[2];
	FILE *fp;
	ARTIKLI *artikl;
	ARTIKLI *artikl1;
	printf("\n\t\tUnesite naziv obracuna kojega zelite ispraviti (npr. '1.1.2019'): ");
	scanf("%30s", naziv);
	printf("\n\t\t-Za povratak na prethodnu stavku unesite '-1'!");
	printf("\n\t\t-Ako zelite ostaviti staru vrijednost unesite '-2'!\n");
	for (int i = 0; i < 31; i++)
	{
		if (naziv[i] == '\0')
		{
			naziv[i] = '.';
			naziv[i + 1] = 't';
			naziv[i + 2] = 'x';
			naziv[i + 3] = 't';
			naziv[i + 4] = '\0';
			i = 30;
		}
	}
	fp = fopen(naziv, "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka '%s' je neispravna ili ne postoji!\n\n", naziv);
		return -1;
	}
	else
	{
		fscanf(fp, "%d", &br);
		artikl = alokacijaStrukture(0);
		artikl1 = alokacijaStrukture(0);
		for (int i = 0; i < br; i++)
		{
			fscanf(fp, "%s\n%s\n%f\n%f\n%f\n", nebzn, artikl[i].naziv, &artikl[i].kolicina, &artikl[i].cijena1kom, &artikl[i].ukupnaVrijednost);
		}
		fp = fopen(naziv, "r");
		fscanf(fp, "%d", &br);
		for (int i = 0; i < br; i++)
		{
			fscanf(fp, "%s\n%s\n%f\n%f\n%f\n", nebzn, artikl1[i].naziv, &artikl1[i].kolicina, &artikl1[i].cijena1kom, &artikl1[i].ukupnaVrijednost);
		}
		for (int i = 0; i < br; i++)
		{
			do {
				printf("\n\t\t%d.%s\n\t\t\tKolicina: ", i + 1, artikl[i].naziv);
				scanf("%f", &kol);
				if (kol > -1)
				{
					printf("\t\t\tProdano: %.2f", artikl[i].kolicina - kol);
				}
				if (kol < -2)
				{
					printf("\n\t\tERROR - unesen je neispravan broj!\n\t\tPOKUSAJTE PONOVNO!\n");
				}
			} while (kol < -2);
			if (i < 1 && kol == -1)
			{
				printf("\n\t\tERROR - nije se moguce vratiti na prethodni korak!\n");
				i -= 1;
			}
			if (i > 0 && kol == -1)
			{
				i -= 2;
			}
			if (kol > -1)
			{
				artikl[i].kolicina = kol;
			}
			if (kol == -2)
			{
				artikl[i].kolicina = artikl1[i].kolicina;
				printf("\t\t\tProdano: 0.00");
			}
		}
		printf("\n\n\t\tSljedeci dio obavezno ispuniti:");
		printf("\n\t\t\t-Troskovi (R1, limun, razbijeno...) (KN): ", &troskovi);
		scanf("%f", &troskovi);
		printf("\t\t\t-Predano novaca (KN): ", novci);
		scanf("%f", &novci);
		fp = fopen(naziv, "w");
		fprintf(fp, "%d\n", br);
		for (int i = 0; i < br; i++)
		{
			artikl[i].ukupnaVrijednost = artikl[i].cijena1kom * artikl[i].kolicina;
			promet = promet + (artikl[i].ukupnaVrijednost - artikl1[i].ukupnaVrijednost);
			fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
		}
		promet -= troskovi;
		baksa = novci - promet;
		printf("\n\t\tOstali troskovi: %.2f KN\n\t\tPredano: %.2f KN\n\t\tUkupni promet: %.2f KN\n\t\tBaksa: %.2f KN\n", troskovi, novci, baksa, promet);
		fprintf(fp, "\n\tOstali troskovi: %.2f KN\n\tPredano: %.2f KN\n\tUkupni promet: %.2f KN\n\tBaksa: %.2f KN\n", troskovi, novci, baksa, promet);
		printf("\n\t\tObracun radnoga dana %s je pohranjen u mapu s projektom!\n\t\t", naziv);
		fclose(fp);
		do {
			printf("\tOstatak artikala spremiti u listu stanja (da = 1 / ne = 0): ");
			scanf("%d", &odg);
			if (odg == 1)
			{
				fp = fopen("stanje.txt", "w");
				for (int i = 0; i < br; i++)
				{
					fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
				}
				fclose(fp);
				fp = fopen("num.txt", "w");
				fprintf(fp, "%d", br);
				fclose(fp);
			}
		} while (odg < 0 || odg>1);
		system("pause");
		printf("\n");
	}
	fclose(fp);
	free(artikl);
	free(artikl1);
}



// 6) PREGLED OBRAÈUNA PRETHODNIH RADNIH DANA

int pregledObracuna()
{
	int br, br1, rez;
	char naziv[35], nebzn[2], znak[5], troskovi[50], predano[30], promet[35], baksa[30];
	ARTIKLI *artikl;
	FILE* fp;
	br = brojArtikala();
	printf("\n\t\tNapisite naziv obracuna kojega zelite otvoriti (npr. '1.1.2019'): ");
	scanf("%30s", naziv);
	for (int i = 0; i < 31; i++)
	{
		if (naziv[i] == '\0')
		{
			naziv[i] = '.';
			naziv[i + 1] = 't';
			naziv[i + 2] = 'x';
			naziv[i + 3] = 't';
			naziv[i + 4] = '\0';
			i = 30;
		}
	}
	fp = fopen(naziv, "r");
	if (fp == NULL)
	{
		printf("\n\t\t\tDatoteka '%s' je neispravna ili ne postoji!\n\n", naziv);
		return -1;
	}
	else
	{
		fscanf(fp, "%d", &br1);
		rez = br1 - br;
		artikl = alokacijaStrukture(rez);
		for (int i = 0; i < br + rez; i++)
		{
			fscanf(fp, "%s %s %f %f %f\n", nebzn, artikl[i].naziv, &artikl[i].kolicina, &artikl[i].cijena1kom, &artikl[i].ukupnaVrijednost);
			printf("\n\t\t%d.\t%s\n\t\t\tKolicina: %.2f\n\t\t\tCijena: %.2f\n\t\t\tUkupna vrijednost: %.2f\n\t\t\t", i + 1, artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
		}
		fscanf(fp, "\n\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]", troskovi, predano, promet, baksa);
		printf("\n\t\t%s\n\t\t%s\n\t\t%s\n\t\t%s\n\n\t\t", troskovi, predano, promet, baksa);
		system("pause");
	}
	fclose(fp);
	free(artikl);
}



// 7) ZAKLJUÈAK RADNOGA DANA

int zakljucakRadnogaDana()
{
	int odg, br;
	float kol = 0, troskovi = 0, novci = 0, promet = 0, baksa = 0;
	char naziv[35];
	ARTIKLI *artikl;
	ARTIKLI *artikl1;
	artikl = alokacijaStrukture(0);
	artikl1 = alokacijaStrukture(0);
	br = brojArtikala();
	FILE* fp;
	FILE* fprd;
	printf("\n\n\t\tZakljuciti radni dan:\n\t\t\t1) Zakljuciti\n\t\t\t0) Odustani\n");
	do {
		printf("\n\t\tVas odabir: ");
		scanf("%d", &odg);
		if (odg < 0 || odg>1)
		{
			printf("\n\t\t\tERROR - unesen je neispravan broj!\n\t\t\tPOKUSAJTE PONOVNO!\n");
		}
	} while (odg < 0 || odg>1);
	if (odg == 0)
	{
		return 0;
	}
	else if (odg == 1)
	{
		fp = fopen("stanje.txt", "r");
		if (fp == NULL)
		{
			printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
			return -1;
		}
		else
		{
			printf("\n\t\tUnesite datum radnoga dana (naziv dokumenta obracuna) - predlozeno dd.mm.gggg:\n\t\tOBAVEZNO: BEZ RAZMAKA!\n\t\t\t");
			scanf("%30s.txt", naziv);
			for (int i = 0; i < 31; i++)
			{
				if (naziv[i] == '\0')
				{
					naziv[i] = '.';
					naziv[i + 1] = 't';
					naziv[i + 2] = 'x';
					naziv[i + 3] = 't';
					naziv[i + 4] = '\0';
					i = 30;
				}
			}
			fprd = fopen(naziv, "w");
			if (fprd == NULL)
			{
				printf("\n\t\t\tDatoteka 'stanje.txt' je neispravna ili ne postoji!\n\n");
				return -1;
			}
			else
			{
				printf("\n\t\tZa povratak na prethodnu stavku unesite '-1'!\n");
				for (int i = 0; i < br; i++)
				{
					do {
						printf("\n\t\t%d.%s\n\t\t\tKolicina: ", i + 1, artikl[i].naziv);
						scanf("%f", &kol);
						if (kol > -1)
						{
							printf("\t\t\tProdano: %.2f", artikl1[i].kolicina - kol);
						}
						if (kol < -1)
						{
							printf("\n\t\tERROR - unesen je neispravan broj!\n\t\tPOKUSAJTE PONOVNO!\n");
						}
						artikl[i].kolicina = kol;
					} while (artikl[i].kolicina < -1);
					if (i < 1 && artikl[i].kolicina == -1)
					{
						printf("\n\t\tERROR - nije se moguce vratiti na prethodni korak!\n");
						i -= 1;
					}
					if (i > 0 && artikl[i].kolicina == -1)
					{
						i -= 2;
					}
				}
				printf("\n\t\tTroskovi (R1, limun, razbijeno...) (KN): ", &troskovi);
				scanf("%f", &troskovi);
				printf("\t\tPredano novaca (KN): ", novci);
				scanf("%f", &novci);
				fprintf(fprd, "%d\n", br);
				for (int i = 0; i < br; i++)
				{
					artikl[i].ukupnaVrijednost = artikl[i].cijena1kom * artikl[i].kolicina;
					promet = promet + (artikl1[i].ukupnaVrijednost - artikl[i].ukupnaVrijednost);
					fprintf(fprd, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
				}
				promet -= troskovi;
				baksa = novci - promet;
				printf("\n\t\tOstali troskovi: %.2f KN\n\t\tPredano: %.2f KN\n\t\tUkupni promet: %.2f KN\n\t\tBaksa: %.2f KN\n", troskovi, novci, promet, baksa);
				fprintf(fprd, "\n\tOstali troskovi: %.2f KN\n\tPredano: %.2f KN\n\tUkupni promet: %.2f KN\n\tBaksa: %.2f KN\n", troskovi, novci, promet, baksa);
				printf("\n\t\tObracun radnoga dana %s je pohranjen u mapu s projektom!\n\t\t", naziv);
				system("pause");
				printf("\n");
				fclose(fp);
				do {
					printf("\tOstatak artikala spremiti u listu stanja (da = 1 / ne = 0): ");
					scanf("%d", &odg);
					if (odg == 1)
					{
						fp = fopen("stanje.txt", "w");
						for (int i = 0; i < br; i++)
						{
							fprintf(fp, "/\n%s\n%.2f\n%.2f\n%.2f\n", artikl[i].naziv, artikl[i].kolicina, artikl[i].cijena1kom, artikl[i].ukupnaVrijednost);
						}
						fclose(fp);
						fp = fopen("num.txt", "w");
						fprintf(fp, "%d", br);
						fclose(fp);
					}
				} while (odg < 0 || odg>1);
				system("pause");
				printf("\n");
			}
			fclose(fprd);
			fclose(fp);
		}
	}
	free(artikl);
	free(artikl1);
}
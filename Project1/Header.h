#ifndef HEADER_H
#define HEADER_H

typedef struct artikli {
	char naziv[21];
	float kolicina;
	float cijena1kom;
	float ukupnaVrijednost;
}ARTIKLI;

int brojArtikala();
ARTIKLI* alokacijaStrukture(int novi);

int unosRobe();
int otpisRobe();
int provjera();

int unosNovogaArtikla();
int brisanjeArtikla();
int izmjenaNaziva();
int izmjenaCijene();

void listaStanja();

int sortiranjeArtikala();

int ispravakStanja();

int pregledObracuna();

int zakljucakRadnogaDana();

#endif
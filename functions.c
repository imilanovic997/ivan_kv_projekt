#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

static int brojIgraca = 0, i, j, br = 0;				

int izbornik() {

	int opcija = 0;											// 1
	static IGRAC* polje = NULL;								// 5

	printf("Dobrodosli u bazu podataka nogometnog kluba!\nOdabirom jednih od opcija uredite, dodajte ili saznajte vise o Vasem omiljenom nogometnom igracu.\n");
	printf("Pritiskom na broj odaberite opciju\n");			// 8
	printf("' 1 ' Dodaj igraca\n");
	printf("' 2 ' Uredi postojeceg igraca\n");
	printf("' 3 ' Ispis igraca\n");
	

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		ucitavanjeIgraca();								// 4
		if (brojIgraca == 0) {
			kreiranjeDat();
		}
		dodavanjeIgraca();
		break;
	case 2:
		azuriranje();
		break;
	case 3:
		if (polje != NULL) {
			free(polje);
			polje = NULL;
		}
		polje = (IGRAC*)ucitavanjeIgraca();
		ispisivanje(polje);
		break;

	default:
		printf("\nOdabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

void kreiranjeDat() {
	FILE* fp = NULL;
	fp = fopen("igraci.bin", "wb");					
	if (fp == NULL) {
		perror("Kreiranje");
	}
	fwrite(&brojIgraca, sizeof(int), 1, fp);
	fclose(fp);
}

void dodavanjeIgraca() {
	FILE* fp = NULL;
	fp = fopen("igraci.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");

	fread(&brojIgraca, sizeof(int), 1, fp);
	printf("Trenutni broj igraca: %d", brojIgraca);

	IGRAC igraci;
	igraci.id = brojIgraca;
	br++;
	getchar();
	printf("Unesite ime igraca: ");
	scanf("%24[^\n]", igraci.ime);
	getchar();
	printf("Unesite prezime igraca: ");
	scanf("%29[^\n]", igraci.prezime);
	getchar();
	printf("Unesite poziciju igraca: ");
	scanf("%9[^\n]", igraci.pozicija);
	getchar();
	printf("Unesite broj registracije igraca: ");
	scanf("%d", &igraci.brreg);
	getchar();
	fseek(fp, sizeof(IGRAC) * brojIgraca, SEEK_CUR);
	fwrite(&igraci, sizeof(IGRAC), 1, fp);
	rewind(fp);
	brojIgraca++;
	fwrite(&brojIgraca, sizeof(int), 1, fp);
	fclose(fp);
}

void azuriranje() {
	FILE* fp = NULL;
	int reload;
	fp = fopen("igraci.bin", "rb+");
	if (fp == NULL)
		printf("Niste unijeli niti jednog igraca.\n");
	else {
		printf("Unesi broj igraca kojeg zelite ispraviti:\n");
		scanf("%d", &reload);
		fseek(fp, sizeof(int) + (sizeof(IGRAC) * (reload - 1)), SEEK_SET);
		IGRAC ispravljenIgrac;
		ispravljenIgrac.id = reload;
		getchar();
		printf("Unesite ispravljeno ime igraca: ");
		scanf("%24[^\n]", ispravljenIgrac.ime);
		getchar();
		printf("Unesite ispravljeno prezime igraca: ");
		scanf("%29[^\n]", ispravljenIgrac.prezime);
		getchar();
		printf("Unesite ispravljenu poziciju igraca: ");
		scanf("%9[^\n]", ispravljenIgrac.pozicija);
		getchar();
		printf("Unesite ispravljen broj registracije igraca: ");
		scanf("%d", &ispravljenIgrac.brreg);
		getchar();
		fwrite(&ispravljenIgrac, sizeof(IGRAC), 1, fp);
		rewind(fp);
		fwrite(&brojIgraca, sizeof(int), 1, fp);
		fclose(fp);
	}
}

void* ucitavanjeIgraca() {
	FILE* fp = fopen("igraci.bin", "rb");
	if (fp == NULL) {
		printf("Niste unijeli niti jednog igraca.\n");
		return NULL;
	}
	fread(&brojIgraca, sizeof(int), 1, fp);
	IGRAC* polje = NULL;
	polje = (IGRAC*)calloc(brojIgraca, sizeof(IGRAC));
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}
	fread(polje, sizeof(IGRAC), brojIgraca, fp);
	fclose(fp);
	return polje;
}

void ispisivanje(IGRAC* polje) {
	for (i = 0; i < brojIgraca; i++) {
		printf("Ime:%s  Prezime:%s  Pozicija:%s  Broj registracije: %d\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->pozicija, (polje + i)->brreg);
	}
}


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"										//10

static int brojIgraca = 0, i, j, br = 0;

int izbornik() {

	int opcija = 0;											//1
	static IGRAC* polje = NULL;								//5

	printf("Dobrodosli u bazu podataka nogometnog kluba!\nOdabirom jednih od opcija uredite, dodajte ili saznajte vise o Vasem omiljenom nogometnom igracu.\n");
	printf("Pritiskom na broj opcije odaberite opciju.\n");		//8
	printf("' 1 ' Dodaj igraca\n");
	printf("' 2 ' Uredi postojeceg igraca\n");
	printf("' 3 ' Ispis igraca\n");
	printf("' 4 ' Trazilica igraca\n");
	printf("' 5 ' Sortiraj igrace po registraciji\n");


	scanf("%d", &opcija);									
	system("cls");

	switch (opcija) {
	case 1:
		ucitavanjeIgraca();									//4
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
	case 4:
		while (opcija != 90) {
			opcija = izbornikSrch();
		}
		break;
	case 5:
		while (opcija != 89)
			opcija = izbornikSrt();
		break;

	default:
		printf("\nOdabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

izbornikSrch() {												//20
	int opcija = 0;												//9
	IGRAC* polje = NULL;
	polje = (IGRAC*)ucitavanjeIgraca();
	printf("Pretrazi po:\n");
	printf("\t' 1 ' Imenu\n");
	printf("\t' 2 ' Prezimenu\n");
	printf("\t' 3 ' Poziciji\n");
	printf("\t' 4 ' Broju registracije\n");
	printf("\t' 5 ' Natrag\n");

	scanf("%d", &opcija);										//9
	system("cls");

	switch (opcija) {
	case 1:
		SearchIme(polje);
		break;
	case 2:
		SearchPrezime(polje);
		break;
	case 3:
		SearchPozicija(polje);
		break;
	case 4:
		SearchBrReg(polje);
		break;
	case 5:
		return 90;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

int izbornikSrt() {												//21
	int opcija = 0;
	IGRAC* polje = NULL;
	polje = (IGRAC*)ucitavanjeIgraca();
	printf("Sortiraj prema:\n");
	printf("\t' 1 ' Broju registracije uzlazno\n");
	printf("\t' 2 ' Broju registracije silazno\n");
	printf("\t' 3 ' Natrag\n");

	scanf("%d", &opcija);
	system("cls");

	switch (opcija) {
	case 1:
		selectionSortBrRegUzl(polje);
		break;
	case 2:
		selectionSortBrRegSil(polje);
		break;
	case 3:
		return 89;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return opcija;
}

void kreiranjeDat() {
	FILE* fp = NULL;
	fp = fopen("igraci.bin", "wb");
	if (fp == NULL) {
		perror("Kreiranje");									//19
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
	fseek(fp, sizeof(IGRAC) * brojIgraca, SEEK_CUR);			//17
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

void* SearchIme(IGRAC* polje) {
	char reqName[25];
	int br = 0;

	printf("Upisite ime trazenog igraca:\n");
	getchar();
	scanf("%24[^\n]", reqName);

	for (i = 0; i < brojIgraca; i++) {
		if (!strcmp(reqName, (polje + i)->ime)) {
			printf("\nIme:%s  Prezime:%s  Pozicija:%s  Broj registracije: %d\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->pozicija, (polje + i)->brreg);
			br++;
		}
	}
	if (br == 0)
		printf("\nIgrac pod ovim imenom nije pronaden.\n");
	return NULL;
}

void* SearchPrezime(IGRAC* polje) {
	char reqSurname[25];
	int br = 0;

	printf("Upisite prezime trazenog igraca:\n");
	getchar();
	scanf("%29[^\n]", reqSurname);

	for (i = 0; i < brojIgraca; i++) {
		if (!strcmp(reqSurname, (polje + i)->prezime)) {
			printf("\nIme:%s  Prezime:%s  Pozicija:%s  Broj registracije: %d\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->pozicija, (polje + i)->brreg);
			br++;
		}
	}
	if (br == 0)
		printf("\nIgrac pod ovim prezimenom nije pronaden.\n");
	return NULL;
}

void* SearchPozicija(IGRAC* polje) {
	char reqPosition[25];
	int br = 0;

	printf("Upisite poziciju koju trazite:\n");
	getchar();
	scanf("%9[^\n]", reqPosition);

	for (i = 0; i < brojIgraca; i++) {
		if (!strcmp(reqPosition, (polje + i)->pozicija)) {
			printf("\nIme:%s  Prezime:%s  Pozicija:%s  Broj registracije: %d\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->pozicija, (polje + i)->brreg);
			br++;
		}
	}
	if (br == 0)
		printf("\nNije unesen niti jedan igrac na ovoj poziciji.\n");
	return NULL;
}

void* SearchBrReg(IGRAC* polje) {
	int reqNo, br = 0;

	printf("Unesite broj registracije koju trazite:\n");
	scanf("%d", &reqNo);

	for (i = 0; i < brojIgraca; i++) {
		if (reqNo == (polje + i)->brreg) {
			printf("\nIme:%s  Prezime:%s  Pozicija:%s  Broj registracije: %d\n", (polje + i)->ime, (polje + i)->prezime, (polje + i)->pozicija, (polje + i)->brreg);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazena registracija nije pronadjena.\n");
	return NULL;
}

void subs(IGRAC* veci, IGRAC* manji) {
	IGRAC temp = { 0 };
	temp = *veci;
	*veci = *manji;
	*manji = temp;
}

void subs2(IGRAC* manji, IGRAC* veci) {
	IGRAC temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSortBrRegUzl(IGRAC* polje) {
	for (int j = 0; j < brojIgraca; j++) {
		for (int i = 0; i < brojIgraca - 1; i++) {
			if (polje[i].brreg > polje[i + 1].brreg) {
				subs2((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojIgraca; i++) {
		printf("\nID: %d Ime:%s  Prezime:%s  Pozicija:%s  Broj registracije: %d\n", (polje + i)->id, (polje + i)->ime, (polje + i)->prezime, (polje + i)->pozicija, (polje + i)->brreg);
	}
	printf("\n");
}

void selectionSortBrRegSil(IGRAC* polje) {
	for (int j = 0; j < brojIgraca; j++) {
		for (int i = 0; i < brojIgraca - 1; i++) {
			if (polje[i].brreg < polje[i + 1].brreg) {
				subs((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojIgraca; i++) {
		printf("\nID: %d Ime:%s  Prezime:%s  Pozicija:%s  Broj registracije: %d\n", (polje + i)->id, (polje + i)->ime, (polje + i)->prezime, (polje + i)->pozicija, (polje + i)->brreg);
	}
	printf("\n");
}

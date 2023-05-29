#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct igrac {					// 3
	int id;
	char ime[25];
	char prezime[30];
	char pozicija[10];
	int brreg;
}IGRAC;									// 2

int izbornik();
void kreiranjeDat();
void dodavanjeIgraca();					// 6
void azuriranje();
void* ucitavanjeIgraca();
void ispisivanje(IGRAC*);

#endif //FUNCTIONS_H

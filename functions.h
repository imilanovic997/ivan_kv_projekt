#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct igrac {									//3
	int id;
	char ime[25];
	char prezime[30];
	char pozicija[10];
	int brreg;
}IGRAC;													//2

int izbornik();
int izbornikSrch();
int izbornikSrt();
void kreiranjeDat();
void dodavanjeIgraca();									//6
void azuriranje();
void* ucitavanjeIgraca();
void ispisivanje(IGRAC*);
void* SearchIme(IGRAC*);
void* SearchPrezime(IGRAC*);
void* SearchPozicija(IGRAC*);
void* SearchBrReg(IGRAC*);
void subs(IGRAC*, IGRAC*);
void subs2(IGRAC*, IGRAC*);
void selectionSortBrRegUzl(IGRAC*);
void selectionSortBrRegSil(IGRAC*);

#endif //FUNCTIONS_H
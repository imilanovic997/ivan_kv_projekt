#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct igrac {										//2,3
	int id;
	char ime[25];
	char prezime[30];
	char pozicija[10];
	int brreg;
}IGRAC;

int izbornik();
int izbornikSrch();
int izbornikSrt();
void kreiranjeDat();
void dodavanjeIgraca();
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
void brisanjeIgr(IGRAC*);
void brisanjeBaze(IGRAC*);

#endif //FUNCTIONS_H

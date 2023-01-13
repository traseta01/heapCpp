#include "heap.h"
#include <ncurses.h>
#include <iostream>
#include <algorithm>

using std::ostringstream;

// funkcija koja ucitava string ncurses
string ucitaj_str()
{
	string ulaz;
	

	// let the terminal do the line editing
	nocbreak();
	echo();

	int c = getch();

	while (c != '\n')
	{
		ulaz.push_back(c);
		c = getch();
	}
	// vrati podesavanja za cbreak i echo
	cbreak();
	noecho();
	
	return ulaz;
}

int main(int argc, char ** argv)
{
	//string koji prikazuje uputstvo za koriscenje
	string uputstvostr  = "Komande: (q) - zatvori; (r) - uzmi koren; (d) - dodaj element\n";

	// niz za stampanje grana
	vector<string> nizstampa;
	// init niz grana
	Stampa::napuni_grane(nizstampa);

	Heap hip;

	vector<int> nizhip = {3, 2, 6, 5, 76, 87, 12, 34};
	
	std::make_heap(nizhip.begin(), nizhip.end());


	hip.dodaj_u_hip(3);
	hip.dodaj_u_hip(2);
	hip.dodaj_u_hip(6);
	hip.dodaj_u_hip(5);
	hip.dodaj_u_hip(76);
	hip.dodaj_u_hip(857);
	hip.dodaj_u_hip(152);
	hip.dodaj_u_hip(354);
	hip.dodaj_u_hip(554);
	hip.dodaj_u_hip(354);
	hip.dodaj_u_hip(754);
	hip.dodaj_u_hip(351);
	hip.dodaj_u_hip(251);
	hip.dodaj_u_hip(451);
	hip.dodaj_u_hip(851);
	hip.dodaj_u_hip(359);
	hip.dodaj_u_hip(455);
	hip.dodaj_u_hip(455);
	hip.dodaj_u_hip(455);
	hip.dodaj_u_hip(455);
	hip.dodaj_u_hip(455);
	hip.dodaj_u_hip(455);
	hip.dodaj_u_hip(954);
	hip.dodaj_u_hip(953);
	hip.dodaj_u_hip(353);
	hip.dodaj_u_hip(753);
	hip.dodaj_u_hip(153);
	hip.dodaj_u_hip(153);
	hip.dodaj_u_hip(153);
	hip.dodaj_u_hip(153);

	initscr();
	//raw();

	// alociraj memoriju za pokazivac na prozor
	WINDOW *prozor;

	int visina = 50;
	int sirina = 113;
	int start_y = 3;
	int start_x = 10;
	// kreiraj novi prozor zadate visine i sirine
	// na start_y redova od vrha ekrana i start_x 
	// kolona od leve ivice ekrana
	// prozor  = newwin(visina, sirina, start_y, start_x);
	refresh();

	// create a box around window
	//	box(prozor, 0, 0);
	
	noecho();
	curs_set(0);
	
	// sstream u koji spakujemo izlaz
	ostringstream izlaz;
	izlaz << uputstvostr;
	izlaz << "velicinahipa: " << Stampa::num_to_string(hip.brel_heap()) << endl;
	izlaz << "broj nivoa: " << Stampa::num_to_string(hip.brsprat_hip()) << endl;
	hip.ispis_hip_redovi(izlaz, nizstampa);
	//printw uzima const char * kao argument za stampu
	//nekistring.data() resava problem
	//wprintw stampaj u prosledjenom prozoru
	printw(izlaz.str().data());
	//wrefresh(prozor);

	//move(1, 5);
	move(1, 24);
	int karakter;

	while((karakter = getch()))
	{
		if (karakter == 'q')
			break;
		else if (karakter == 'r')
		{
			if(hip.brel_heap() == 0)
				continue;
			// postavi kursor na nevidiljiv
			curs_set(0);
			hip.uzmi_koren();
			clear();
			ostringstream izlaz1;
			izlaz1 << uputstvostr;
			izlaz1 << "velicinahipa: " << Stampa::num_to_string(hip.brel_heap()) << endl;
			izlaz1 << "broj nivoa: " << Stampa::num_to_string(hip.brsprat_hip()) << endl;
			hip.ispis_hip_redovi(izlaz1, nizstampa);
			printw(izlaz1.str().data());
			refresh();
		}
		else if (karakter == 'd')
		{
			move(1, 24);

			if (hip.brel_heap() > 30)
			{
				printw("Hip je pun!");
				refresh();
			}
			else
			{
				printw("Unesite broj: ");
				hip.dodaj_u_hip(stoi(ucitaj_str()));
				clear();
				ostringstream izlaz1;
				izlaz1 << uputstvostr;
				izlaz1 << "velicinahipa: " << Stampa::num_to_string(hip.brel_heap()) << endl;
				izlaz1 << "broj nivoa: " << Stampa::num_to_string(hip.brsprat_hip()) << endl;
				hip.ispis_hip_redovi(izlaz1, nizstampa);
				printw(izlaz1.str().data());
				refresh();
			}
		}

	}
	int k = Stampa::PROBA;

	//echo();
	curs_set(1);

	endwin();

	return 0;
}

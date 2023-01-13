#ifndef __HEAP_H__
#define __HEAP_H__
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::pow;


/***** Klasa Heap ******/
class Heap
{
	public:
		//Konstruktor
		Heap()
		{}

		// swap
		void zameni(int &, int &);
		// vrati br elemenata hipa
		int brel_heap();

		// vrati broj spratova (visinu) heapa
		int brsprat_hip();

		// indikator levog i desnog roditelja
		int ima_levi(unsigned);
		int ima_desni(unsigned);

		// dodaj elem u hip
		void dodaj_u_hip(int);
		// uzmi koren i vrati vrednost
		int uzmi_koren();

		// ispisi niz
		void ispis_hip();
		// ispisi u redovima
		std::ostringstream &  ispis_hip_redovi(std::ostringstream &, vector<string>&);

	private:
		// niz u kojem cuvamo heap
		vector<int> _hv;
};

namespace Stampa
{
	extern int PROBA;
	// niz spaceova u koji upisujemo nivoe hipa na zadatim razmacima
	extern string prazansprat;
	extern int niz_razmaka[]; 

	void napuni_grane(vector<string> &);

	string ispis_sprat(const vector<int> &, int);

	// prebaci int u string
	string num_to_string(int);


	// deklaracija stringova za ispis
	extern string stampa01;
	extern string stampa02;
	extern string stampa03;
	extern string stampa04;
	extern string stampa05;
	extern string stampa06;
	extern string stampa07;
	extern string stampa08;
	extern string stampa09;
	extern string stampa10;
	extern string stampa11;
	extern string stampa12;
	extern string stampa13;
	extern string stampa14;
	extern string stampa15;
	extern string stampa16;
	extern string stampa17;
	extern string stampa18;
	extern string stampa19;
	extern string stampa20;
	extern string stampa21;
	extern string stampa22;
	extern string stampa23;
	extern string stampa24;
	extern string stampa25;
	extern string stampa26;
	extern string stampa27;
	extern string stampa28;
	extern string stampa29;
	extern string stampa30;


}
#endif

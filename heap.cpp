#include "heap.h"


/********* Metodi klase heap **********/

/**** konstruktor ****/

int Heap::brel_heap()
{
	return _hv.size();
}

// vrati broj spratova (visinu) heapa
int Heap::brsprat_hip()
{
	int brsprat = 0;
	int pom = _hv.size()/2;

	while (pom > 0)
	{
		brsprat++;
		pom /= 2;
	}
	return brsprat;
}

// swap funkcija
void Heap::zameni(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

// dve pomocne funkcije koje za prosledjeni indeks
// vracaju indeks levog/desnog roditelja, ako on postoji
// vracaju nula inace
int Heap::ima_levi(unsigned ind)
{
	// brojimo od nule - koren
	// levi sin je na poziciji 2i+1
	if (_hv.size() - 1 < 2*ind + 1)
		return 0;
	else
		return 2*ind + 1;
}

int Heap::ima_desni(unsigned ind)
{
	// brojimo od nule - koren
	// desni sin je na poziciji 2i+2
	if (_hv.size() - 1 < 2*ind + 2)
		return 0;
	else
		return 2*ind + 2;
}


// funkcija dodaje element u hip, prvo ga smesta na kraj niza a zatim
// se penje dok ne dodje do prave pozicije ili ne postane koren
void Heap::dodaj_u_hip(int vrednost)
{
	// ako je hip veci od 31 ne radi nista
	if(_hv.size() > 30)
		return;
	// element stavljamo na kraj niza
	_hv.push_back(vrednost);

	// nalazi se na poslednjoj poziciji inicijalno
	int indeks = this->brel_heap() - 1;

	// indeks njegovog roditelja je indeks - 1 / 2
	int roditelj = (indeks - 1)/2;

	// sve dok je element na indeksu veci od roditlja ili nije nula zameni
	while (indeks != 0 && _hv[indeks] > _hv[roditelj])
	{
		zameni(_hv[roditelj], _hv[indeks]);

		// indeks postaje roditelj
		indeks = roditelj;
		// roditelj dobija novu vrednost
		roditelj = (indeks - 1)/2;
	}
}

// uzmi koren hipa i vrati njegovu vrednost
int Heap::uzmi_koren()
{
	// zapamti vr korena
	int vrkorena = _hv[0];

	//zameni koren i poslednji element
	zameni(_hv[0], _hv[_hv.size() - 1]);

	// izbaci stari koren
	_hv.pop_back();


	// element sa pozicije korena spustamo na pravu poziciju
	// krecemo se levo ili desno
	
	// element je pocetno na poziciji korena
	int indeks = 0;
	// indeks levog sina
	int levi = ima_levi(indeks);

	// sve dok element ima levog ili desnog sina ako je manji
	// zameni ih
	while(levi)
	{
		int desni = ima_desni(indeks);

		// ima levog sina i veci je 
		if(_hv[levi] > _hv[indeks])
		{
			// ako ima desnog sina i desni je veci od levog, zameni
			if (desni && _hv[desni] > _hv[levi])
			{
				zameni(_hv[desni], _hv[indeks]);
				indeks = desni;
			}
			// u suprotnom zameni sa levim sinom
			else
			{
				zameni(_hv[indeks], _hv[levi]);
				indeks = levi;
			}
		}
		// levi nije veci ali jeste desni
		else if (desni && _hv[desni] > _hv[indeks])
		{
			zameni(_hv[desni], _hv[indeks]);
			indeks = desni;
		
		}
		// nema ni levog ni desnog sina
		else
			break;

		// azuriraj indeks levog sina
		levi = ima_levi(indeks);
	}
	// element je na pravoj poziciji
	// vrati vrednost korena
	return vrkorena;
}

// stampaj hip kao niz
void Heap::ispis_hip()
{
	for (int x : _hv)
		cout << x << " ";
	cout << endl;
}

// stampaj hip u redovima
std::ostringstream& Heap::ispis_hip_redovi(std::ostringstream& izlaz, vector<string> &vek)
{

	int bs = this->brsprat_hip();
	int vel = this->brel_heap();



	izlaz << Stampa::ispis_sprat(_hv, 0);
	for (int i=1; i <= bs; ++i)
	{


		if(vel-1 >= pow(2, i+1)-2 )
			izlaz << vek[pow(2, i+1)-2];
		else
			izlaz << vek[vel-1];
	//	//izlaz << Stampa::ispis_sprat(_hv, 1);
	//	if(i == 2)
	//		izlaz << Stampa::stampa06;
	//	//izlaz << Stampa::ispis_sprat(_hv, 2);
	//	if(i == 3)
	//		izlaz << Stampa::stampa14;
	//	//izlaz << Stampa::ispis_sprat(_hv, 3);
	//	if(i == 4)
	//		izlaz << Stampa::stampa30;
	//	//izlaz << Stampa::ispis_sprat(_hv, 4);

		izlaz << Stampa::ispis_sprat(_hv, i);
	}

	return izlaz;
}

/********* Namespace Stampa **********/

namespace Stampa
{
	int PROBA=5;
	// string spaceova za ispis nivoa
	string prazansprat(99, ' ');

	// niz razmaka za ispis sprata
	//					 1    2  3    4   5   6   7   8   9   10  11  12  13  14  15
	int niz_razmaka[] = {52, 36, 68, 25, 41, 63, 79, 16, 27, 37, 46, 58, 67, 77, 88,
						11, 16, 24, 29, 34, 39, 43, 48, 55, 60, 64, 69, 75, 80, 86, 92};

	// ispis clanova hipa na zadatom spratu
	string ispis_sprat(const vector<int> &vek, int brsprata)
	{
		string pomocni(prazansprat);
		if(vek.size() <= 0)
			return pomocni;

		if (brsprata == 0)
			pomocni.replace(niz_razmaka[0], 2, num_to_string(vek[0]));
		
		if (brsprata == 1)
		{
			for (unsigned i = 1; i < 3; ++i)
			{
				if ( i > vek.size()-1)
					break;
				pomocni.replace(niz_razmaka[i], 2, num_to_string(vek[i]));
			}
		}

		if (brsprata == 2)
		{
			for (unsigned i = 3; i < 7; ++i)
			{
				if ( i > vek.size()-1)
					break;
				pomocni.replace(niz_razmaka[i], 2, num_to_string(vek[i]));
			}
		}

		if (brsprata == 3)
		{
			for (unsigned i = 7; i < 15; ++i)
			{
				if ( i > vek.size()-1)
					break;
				pomocni.replace(niz_razmaka[i], 2, num_to_string(vek[i]));
			}
		}

		if (brsprata == 4)
		{
			for (unsigned i = 15; i < 31; ++i)
			{
				if ( i > vek.size()-1)
					break;
				pomocni.replace(niz_razmaka[i], 2, num_to_string(vek[i]));
			}
		}
		return pomocni;
	}

	// prebaci int u string
	string num_to_string(int vrednost)
	{
		std::ostringstream prebaci;
		if (vrednost < 10)
			prebaci <<"0";
		prebaci << vrednost;
		return prebaci.str();
	}

	// funkcija koja ce napuniti niz grana za stampanje
	void napuni_grane(vector<string> &vek)
	{
		vek.push_back(stampa01);
		vek.push_back(stampa01);
		vek.push_back(stampa02);
		vek.push_back(stampa03);
		vek.push_back(stampa04);
		vek.push_back(stampa05);
		vek.push_back(stampa06);
		vek.push_back(stampa07);
		vek.push_back(stampa08);
		vek.push_back(stampa09);
		vek.push_back(stampa10);
		vek.push_back(stampa11);
		vek.push_back(stampa12);
		vek.push_back(stampa13);
		vek.push_back(stampa14);
		vek.push_back(stampa15);
		vek.push_back(stampa16);
		vek.push_back(stampa17);
		vek.push_back(stampa18);
		vek.push_back(stampa19);
		vek.push_back(stampa20);
		vek.push_back(stampa21);
		vek.push_back(stampa22);
		vek.push_back(stampa23);
		vek.push_back(stampa24);
		vek.push_back(stampa25);
		vek.push_back(stampa26);
		vek.push_back(stampa27);
		vek.push_back(stampa28);
		vek.push_back(stampa29);
		vek.push_back(stampa30);
	
	}

	/**** Stringovi za stampanje grana, smestamo ih u niz
	 * i na osnovu velicine niza znamo koju granu stampamo **/

	string stampa01 = R"(
                                               __/    
                                            __/       
                                         __/          
                                      __/             
)";
	string stampa02 = R"(
                                               __/      \__                                           
                                            __/            \__          
                                         __/                  \__       
                                      __/                        \__    
)";
	string stampa03 = R"(
                                   _/                       
                                 _/                         
                               _/                           
                             _/                             
                           _/                               
)";
	string stampa04 = R"(
                                   _/\                            
                                 _/   \                           
                               _/      \                          
                             _/         \                         
                           _/            \                        
)";
	string stampa05 = R"(
                                   _/\                              /                      
                                 _/   \                            /                       
                               _/      \                          /                        
                             _/         \                        /                         
                           _/            \                      /                          
)";

	string stampa06 = R"(
                                   _/\                              /\_                               
                                 _/   \                            /   \_                             
                               _/      \                          /      \_                           
                             _/         \                        /         \_                         
                           _/            \                      /            \_                       
)";
	string stampa07 = R"(
                       _             
                     _/              
                   _/                
                 _/                  
)";

	string stampa08 = R"(
                       _                 
                     _/ \                
                   _/    \               
                 _/       \_             
)";


	string stampa09 = R"(
                       _                  _             
                     _/ \                /              
                   _/    \              /               
                 _/       \_          _/                
)";

	string stampa10 = R"(
                       _                  _                  
                     _/ \                / \                 
                   _/    \              /   \                
                 _/       \_          _/     \_              
)";

	string stampa11 = R"(
                       _                  _                    _             
                     _/ \                / \                  /              
                   _/    \              /   \                /               
                 _/       \_          _/     \_            _/                
)";

	string stampa12 = R"(
                       _                  _                    _                 
                     _/ \                / \                  / \                
                   _/    \              /   \                /   \               
                 _/       \_          _/     \_            _/     \_             
)";

	string stampa13 = R"(
                       _                  _                    _                  _             
                     _/ \                / \                  / \                /              
                   _/    \              /   \                /   \              /               
                 _/       \_          _/     \_            _/     \_          _/                
)";

	string stampa14 = R"(
                       _                  _                    _                  _                   
                     _/ \                / \                  / \                / \_                 
                   _/    \              /   \                /   \              /    \_               
                 _/       \_          _/     \_            _/     \_          _/       \_             
)";

	string stampa15 = R"(
             _/         
            /           
)";

	string stampa16 = R"(
             _/\             
            /   \            
)";

	string stampa17 = R"(
             _/\           /         
            /   \         /          
)";

	string stampa18 = R"(
             _/\           /\           
            /   \         /  \          
)";

	string stampa19 = R"(
             _/\           /\        /         
            /   \         /  \      /          
)";
	
	string stampa20 = R"(
             _/\           /\        /\           
            /   \         /  \      /  \          
)";

	string stampa21 = R"(
             _/\           /\        /\       /         
            /   \         /  \      /  \     /          
)";

	string stampa22 = R"(
             _/\           /\        /\       /\          
            /   \         /  \      /  \     /  \         
)";

	string stampa23 = R"(
             _/\           /\        /\       /\          /         
            /   \         /  \      /  \     /  \        /          
)";

	string stampa24 = R"(
             _/\           /\        /\       /\          /\          
            /   \         /  \      /  \     /  \        /  \         
)";

	string stampa25 = R"(
             _/\           /\        /\       /\          /\       /         
            /   \         /  \      /  \     /  \        /  \     /          
)";
	
	string stampa26 = R"(
             _/\           /\        /\       /\          /\       /\                
            /   \         /  \      /  \     /  \        /  \     /  \               
)";

	string stampa27 = R"(
             _/\           /\        /\       /\          /\       /\        /         
            /   \         /  \      /  \     /  \        /  \     /  \      /          
)";

	string stampa28 = R"(
             _/\           /\        /\       /\          /\       /\        /\          
            /   \         /  \      /  \     /  \        /  \     /  \      /  \         
)";

	string stampa29 = R"(
             _/\           /\        /\       /\          /\       /\        /\          /         
            /   \         /  \      /  \     /  \        /  \     /  \      /  \        /          
)";

	string stampa30 = R"(
             _/\           /\        /\       /\          /\       /\        /\          /\_          
            /   \         /  \      /  \     /  \        /  \     /  \      /  \        /   \         
)";

}

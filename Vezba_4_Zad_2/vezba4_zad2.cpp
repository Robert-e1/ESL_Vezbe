/*ZADATAK:
 *
 * Modelovati modul koji predstavlja coveka koji pokusava da prodje kroz troje vrata po pravilima sa slike (v4.pdf slika1.18)
 *
 * Na pocetku covek - H, ceka ispred vrata A. Kada prodje kroz vrata A, treba da prodje kroz vrata B,
 * a potom C.
 *
 * Ukoliko ispred bilo kojih vrata ceka duze od 5s, mora da se vrati ispred vrata A.
 *
 * Vrata se otvaraju nasumicno u intervalu 3 do 7s.
 *
 * Simulacijom odrediti procenat uspesnosti prolaska coveka kroz troje vrata.
 *
 * RESULT: The script counts the number of tries the person tried to get through all 3 doors and the number of successes, for the given simulation time.
 */
#include <systemc>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdlib.h>

using namespace sc_core;
using namespace std;

int number_of_tries;
int success;

SC_MODULE(person)
{
public:
	SC_HAS_PROCESS(person);
	person(sc_module_name);
	int at_door ;
	//events:
protected:
	sc_event event_door_open;
	int waited_for;
	void advance();
};

person :: person(sc_module_name name)
{
	SC_METHOD(advance);
	srand(time(NULL));
	number_of_tries = 1;
	at_door = 1;
	waited_for = 0;

}

void person :: advance()
{

	waited_for =rand() % 5 + 3;
	next_trigger(waited_for, SC_SEC);
	cout <<"Waited for " << waited_for << "seconds" << endl;
	if(waited_for <= 5)
	{
		at_door++;
		if(at_door == 4)
		{
			cout << "Success! Walked through all 3 doors! " << endl;
			success++;
			number_of_tries++;
			at_door = 1;
		}
		else
		{
			cout<< "Advancing to door number: " << at_door << endl;
		}
	}
	else
	{
		at_door = 1;
		number_of_tries++;
		cout<< "Returning back to door number 1" << endl;
	}
}

int sc_main(int argc, char* argv[])
{
	person p("uut");
	sc_start(60, SC_SEC);

	cout <<"Out of " << number_of_tries << ", " << success << " tries were successful!" << endl;

return 0;
}

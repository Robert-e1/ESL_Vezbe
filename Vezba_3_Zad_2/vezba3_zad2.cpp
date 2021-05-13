/*ZADATAK:
 *
 * Modelovati jedan modul koji ce se instancirati 1000 puta (nuklearni proces). Svaki modul sadrzi jedan proces.
 * Interakcije medju procesima (cesticama) modelovati pomocu jednog dogadjaja na koji ce sve cestice biti osetljive.
 * Cestica moze biti u tri stanja : NEAKTIVNO, AKTIVNO, EKSPLODIRANO
 * Sa verovatnocom od 1% ce cestica postati AKTIVNA kada se aktivira dogadjaj. Kada cestica postane AKTIVNA, ona eksplodira za
 * 1ns do 10ns i aktivira isti dogadjaj.
 * Ispisati broj eksplodiranih cestica nakon 100ns simulacije.
 * U pocetnom trenutku samo jedna cestica je AKTIVNA.
 */
/*
 * PROBLEM: process doesn't seem to enter into EXPLODED state when using SC_THREAD
 * FIX: works fine using SC_METHOD
 *
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

enum particle_state{INACTIVE, ACTIVE, EXPLODED};

SC_MODULE(cern)
{
public:
	SC_HAS_PROCESS(cern);
	cern(sc_module_name name, particle_state s);
	static int exploded ;
	sc_event collision_event;

protected:
	particle_state state;
	void collision();								//process that emulates particle collision
};

cern :: cern(sc_module_name name, particle_state s)
{
	state = s;
	srand(time(NULL));
	SC_METHOD(collision);
		sensitive << collision_event;
	cout << "Particle created with state "<< state <<endl;
}

int cern :: exploded = 0;

void cern :: collision()
{
	while(1)
	{
		if (state == INACTIVE)
		{
			next_trigger(collision_event);
			//wait(collision_event);
			if((rand() % 100) == 1)					//probability of 1%
			{
				state = ACTIVE;
			}
		}
		else if(state == EXPLODED)
		{
			//cout << "boom" << endl;
			break;
		}
		else if(state == ACTIVE)
		{
			next_trigger((rand() + 10 + 1), SC_NS);
			//wait((rand() + 10 + 1), SC_NS);
			state = EXPLODED;
			//cout << "particle exploded" << endl;
			exploded++;
			//cout << exploded << endl;
			collision_event.notify();
			//cout << "collision notification " << endl;
		}
	}
}

int sc_main(int argc, char* argv[])
{
	vector<cern*> vec;									//vector for holding particles
	//generate 1000 particles:
	for(int i = 0; i< 999; i++)
	{
		cern *p = new cern(("particle_" + to_string(i)).c_str(),INACTIVE);
		vec.push_back(p);
	}
	cern* p = new cern(("particle_" + to_string(1000)).c_str(), ACTIVE);
	vec.push_back(p);
	cout << "Number of particles created: " << vec.size() << endl;
	sc_start(10000, SC_NS);
	cout<< "Simulation finished, number of exploded particles are: " << vec[0]->exploded << endl;

	return 0;
}

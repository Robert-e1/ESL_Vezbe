/*ZADATAK:
 *
 * Modelovati automat (v4.pdf slika 1.17) koriscenjem SC_METHOD procesa i veceg broja dogadjaja (event).
 * Stanje automata se pamti promenom osetljivosti procesa.
 * Prelazi automata se desavaju kada se posalje poruka odgovarajuceg dogadjaja (event).
 * Ulaze automata modelovati dpgadjajima.
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

enum fsm_states{IDLE, STEP1, STEP2, STEP3};

SC_MODULE(fsm)
{
public:
	SC_HAS_PROCESS(fsm);
	fsm(sc_module_name);
	//events:
protected:
	fsm_states state;
	sc_event idle_event, step1_event_a, step1_event_b, return_to_idle_event;

	void switch_state();						//fsm process
	void gen_event();						//process for generating events


};

fsm :: fsm(sc_module_name name) : sc_module(name)
{
	srand(time(NULL));

	SC_THREAD(gen_event);

	state = IDLE; 								//initial state
	SC_METHOD(switch_state);
		sensitive << idle_event << step1_event_a << step1_event_b << return_to_idle_event;
		dont_initialize();

	cout << "FSM created !" << endl;
}

void fsm :: gen_event()
{
	while(1)
	{
		wait(50, SC_NS); 						//wait some time before generating event
		cout<< "Notify IDLE" << endl;
		idle_event.notify();
		wait(50, SC_NS); 						//wait some time before generating event
		cout<< "Notify STEP1" << endl;

		step1_event_a.notify();
		step1_event_b.notify();
		wait(50, SC_NS); 						//wait some time before generating event
		cout<< "Notify RETURN" << endl;

		return_to_idle_event.notify();
	}
}


void fsm :: switch_state()
{

		switch(state)
		{
		default:
			break;

		case IDLE:
				next_trigger(idle_event);
				state = STEP1;
				cout << "FSM entered state STEP1 at sim time: " << sc_time_stamp() << endl;
				break;

		case STEP1:
			if(rand() % 2 == 1)
			{
					next_trigger(step1_event_a);
					state = STEP2;
				cout << "FSM entered state STEP2 at sim time: " << sc_time_stamp() << endl;

			}
			else
			{
					next_trigger(step1_event_b);
					state = STEP3;
				cout << "FSM entered state STEP3 at sim time: " << sc_time_stamp() << endl;

			}
			break;

		case STEP2:
					next_trigger(return_to_idle_event);
					state = IDLE;
				cout << "FSM entered state IDLE at sim time: " << sc_time_stamp() << endl;
			break;

		case STEP3:
					next_trigger(return_to_idle_event);
					state = IDLE;
				cout << "FSM entered state IDLE at sim time: " << sc_time_stamp() << endl;
			break;
		}
}

int sc_main(int argc, char* argv[])
{
	fsm konacni_automat("uut");
	sc_start(1000, SC_NS);
	return 0;
}

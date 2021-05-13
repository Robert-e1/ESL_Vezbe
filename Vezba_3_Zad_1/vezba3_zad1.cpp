/*ZADATAK:
 *
 *Modelovati modul sa dva procesa.
 *
 *Prvi proces stvara kruznu sekvencu 64 Fibonacijevih brojeva u slucajnom vremenskom intervalu (od 10ns do 100ns).
 *Prvi Drugi proces ispisuje poruku 5ns nakon sto se broj generise. Poruka sadrzi generisani broj i simulaciono vreme.
 *
 *Za komunikaciju medju procesima koristiti dogadjaj (event).
 */

#include <systemc>
#include <iostream>
#include <list>
#include <cstdlib>
#include <ctime>
#include <string>
#include <stdlib.h>

using namespace sc_core;
using namespace std;

SC_MODULE(fibonacci)
{
public:
	SC_HAS_PROCESS(fibonacci);
	fibonacci(sc_module_name name);

protected:
	sc_event gen_event;
	unsigned long long fib1 =0;
	unsigned long long fib2 =0;
	//processes:
	void generate_fib();							//generate fibonacci sequence
	void print_fib();								//print generated sequence and sim. time
};

fibonacci :: fibonacci(sc_module_name name)
{

	SC_THREAD(generate_fib);
	SC_THREAD(print_fib);
		sensitive << gen_event;

	srand(time(NULL));
}
//function for generating fibonacci sequence
void fibonacci :: generate_fib()
{
	int i = 0, n = 64, tmp;
	while(1)
	{
		wait(rand() % 91 + 10, SC_NS);	//wait for 10 to 100 ns
		if(i < n)
		{
			i++;
			tmp = fib1;
			fib1 += fib2;
			fib2 = tmp;
		}
		else
		{
			i = 1;
			fib1 = 1;
			fib2 = 0;
		}
		gen_event.notify();				//trigger event
	}
}
//function for printing fibonacci sequence
void fibonacci :: print_fib()
{
	while(1)
	{
		wait(gen_event);				//wait for event
		wait(5, SC_NS);
		cout << "Next number is Fibonacci sequence is: " << fib1 << ". Time of creation (sim time) is: " << sc_time_stamp() << endl;
	}
}

int sc_main(int argc, char* argv[])
{
	fibonacci fibo("uut");
	sc_start(10000, SC_NS);

	return 0;
}

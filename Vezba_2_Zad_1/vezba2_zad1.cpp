/*ZADATAK:
 *
 *	Modelovati dva procesa:
 *	Prvi stvara kruznu sekvencu prvih 64 Fibonacijevih brojeva u slucajnim vremenskim intervalima
 *	(u intervalu 10ns do 100ns)
 *	Drugi proces ispisuje broj stvorenih brojeva svake sekunde
 *	Simulacija traje 20s
 *	Za komunikaciju izmedju procesa koristiti red ili vektor
 */
#include <systemc>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace sc_core;
using namespace std;

SC_MODULE(fibonacci)							//modul that contains 2 processes
{
	public:

		SC_HAS_PROCESS(fibonacci);
		fibonacci(sc_module_name name);

		vector<unsigned long long> vec;

		void generate_fibonacci(void)			//function for generating fibonacci sequence
		{
			int i = 0, n = 64;
			unsigned long long fib1 = 0, fib2 = 0;
			while(1)
			{
				wait(rand() % 91 + 10, SC_NS);	//wait for 10 to 100 ns
				if(i < n)
				{
					i++;
					fib2 = vec.back();
					vec.push_back(fib1 + fib2);
					fib1 = fib2;
				}
				else
				{
					i = 1;
					fib1 = 1;
					vec.push_back(fib1);
				}
			}
		}

		void print_fibonacci(void)				//function for printing number of generated numbers
		{
			while(1)
			{
				wait(1, SC_SEC);
				cout << "Number of gnerated numbers is: " << vec.size() << ". \n Time of simulation is: " << sc_time_stamp() << endl;
			}
		}
};

fibonacci :: fibonacci(sc_module_name name)
{
	SC_THREAD(generate_fibonacci);
	SC_THREAD(print_fibonacci);

	vec.push_back(0);							//initializing first element of generated numbers
	srand(time(NULL));							//rand seed
}

int sc_main(int argc, char* argv[])
{
	fibonacci fibo("fib");
	sc_start(20, SC_SEC);

	return 0;
}



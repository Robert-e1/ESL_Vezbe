/*ZADATAK:
 *
 *	Modelovati modul sa 5 procesa:
 *
 *	Prvi proces predstavlja ulogu loto masine (7 do 39) koja svake sekunde stvara 7 brojeva
 *	Sledeca 3 procesa su "igraci" - odlucuju da li ce u nekom od izvlacenja ucestvovati u igri. Ako ucestvuju, pave svoju kombinaciju.
 *	Peti proces uporedjuje kombinacije igraca i masine. Ovaj proces jos ispise simulaciono vreme, pobednike i njihove kombinacije sa oznacenim pogodjenim brojevima.
 *
 *	Pobednik/ci igre su oni sa najvise pogodjenih brojeva.
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

SC_MODULE(lotto)
{
public:
		SC_HAS_PROCESS(lotto);
		lotto(sc_module_name name);

protected:
		//procesess:
		void machine();
		void player1();
		void player2();
		void player3();
		void winner();

		//vectors for holding lotto numbers
		vector<int> generated;
		vector<int> player1_picks;
		vector<int> player2_picks;
		vector<int> player3_picks;
		//iterator through list:
		vector<int>::iterator it;

		//which players are playing?
		bool pl1 = 0;
		bool pl2 = 0;
		bool pl3 = 0;
		//lotto numbers generated
};

lotto :: lotto(sc_module_name name)
{
	//create processes from module lotto:
	SC_THREAD(machine);
	SC_THREAD(player1);
	SC_THREAD(player2);
	SC_THREAD(player3);
	SC_THREAD(winner);
	//init vectors:
	generated = {0, 0, 0, 0, 0, 0, 0};
	player1_picks = {0, 0, 0, 0, 0, 0, 0};
	player2_picks = {0, 0, 0, 0, 0, 0, 0};
	player3_picks = {0, 0, 0, 0, 0, 0, 0};
	//seed the rand() function:
	srand(time(NULL));
}

//define processes:
void lotto :: machine()
{
	while(1)
	{
		wait(1, SC_SEC);
		cout << "\n\n\n " << "Generated numbers are: " << endl;

		for(int i =0; i< 7; i++)
		{
			generated[i] = (rand() % 33 + 8);
			cout << generated[i] << " ";
		}
		cout << "\n";
	}
}

void lotto :: player1()
{
	while(1)
		{
			wait(1.001, SC_SEC);
			pl1 = rand() % 2;
			if(pl1 == 1)
			{
				cout << "\n"<<"Player 1 is playing, picks are: " << endl;
				for(int i =0; i< 7; i++)
				{
					player1_picks[i] = (rand() % 33 + 8);
					cout << player1_picks[i] << " ";
				}
				cout << "\n";
			}
			else
			{
				cout << "\n"<<"Player 1 is not playing !" << endl;
				cout << "\n";
			}
		}
}

void lotto :: player2()
{
	while(1)
		{
			wait(1.002, SC_SEC);
			pl2 = rand() % 2;
			if(pl2 == 1)
			{
				cout << "\n"<<"Player 2 is playing, picks are: " << endl;
				for(int i =0; i< 7; i++)
				{
					player2_picks[i] = (rand() % 33 + 8);
					cout << player2_picks[i] << " ";
				}
				cout << "\n";
			}
			else
			{
				cout << "\n"<<"Player 2 is not playing !" << endl;
				cout << "\n";
			}
		}
}

void lotto :: player3()
{
	while(1)
		{
			wait(1.003, SC_SEC);
			pl3 = rand() % 2;
			if(pl1 == 1)
			{
				cout << "\n"<<"Player 3 is playing, picks are: " << endl;
				for(int i =0; i< 7; i++)
				{
					player3_picks[i] = (rand() % 33 + 8);
					cout << player3_picks[i] << " ";
				}
				cout << "\n";
			}
			else
			{
				cout << "\n"<<"Player 3 is not playing !" << endl;
				cout << "\n";
			}
		}
}

void lotto :: winner()
{
	int max = 0;
	int correct1 = 0;
	int correct2 = 0;
	int correct3 = 0;

	while(1)
			{

				wait(1.004, SC_SEC);
				correct1 = 0;
				correct2 = 0;
				correct3 = 0;
				cout << "\n\n\n";
				if(pl1 == 1)
				{
					for(int i =0; i< 7; i++)
					{
						if (player1_picks[i] == generated[i])
							correct1++;
					}
				}
				if(pl2 == 1)
				{
					for(int i =0; i< 7; i++)
					{
						if (player2_picks[i] == generated[i])
							correct2++;
					}
				}
				if(pl3 == 1)
				{
					for(int i =0; i< 7; i++)
					{
						if (player3_picks[i] == generated[i])
							correct3++;
					}
				}
				//PRINT SYSTEM TIME
				cout << "Time of simulations is: " << sc_time_stamp() << "\n\n";
				//DECIDING THE WINNER: not implemented correctly, just to check if everything works (also not sure if position of generated numbers should matter)
				if(pl1 && correct1 >= correct2 && correct1 >= correct3)
				{
					max = correct1;
					cout << "Player 1 WON ! His lucky numbers are: " << endl;
					for(int i =0; i< 7; i++)
					{
						if (player1_picks[i] == generated[i])
								cout << player1_picks[i] <<" ";
					}
				}
				else if(pl2 &&correct2 > correct1 && correct2 > correct3)
				{
					max = correct2;
					cout << "Player 2 WON ! His lucky numbers are: " << endl;
					for(int i =0; i< 7; i++)
					{
						if (player2_picks[i] == generated[i])
								cout << player2_picks[i] <<" ";
					}
				}
				else if(pl3 && correct3 > correct1 && correct3 > correct2)
				{
					max = correct3;
					cout << "Player 3 WON ! His lucky numbers are: " << endl;
					for(int i =0; i< 7; i++)
					{
						if (player3_picks[i] == generated[i])
								cout << player3_picks[i] <<" ";
					}
				}
				else
				{
					cout << "Nobody played! : " << endl;
				}
			}
}

int sc_main(int argc, char* argv[])
{
	lotto lot("uut");
	sc_start(20, SC_SEC);

	return 0;
}



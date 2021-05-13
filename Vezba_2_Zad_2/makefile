SYSCDIR=/usr/include
LDFLAGS= -L$(SYSCDIR)/lib-linux -lsystemc
LANG=C
SOCDAM=/ux/clteach/SOCDAM
CXXFLAGS=-Wno-deprecated -I$(SYSCDIR)/include -I$(SOCDAM)/TLM-2008-06-09/include/tlm

all: Vezba_2_Zad_1

Vezba_2_Zad_1: vezba2_zad2.cpp
	g++ -lsystemc -o vezba2_zad2 vezba2_zad2.cpp

clean:
	rm vezba2_zad2

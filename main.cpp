#include <iostream>
using std::cout; 
#include "genetic.hpp"
#define NUM_ITER 10000
#define NUM_ELITES 10


int main()
{
	populacao pop;
	populacao nova_pop;
	std::generate(pop.begin(), pop.end(), []() {return gen_state();});	
	std::array<std::thread, SIZE_P/2> threads;
	auto best = pop.begin(); 
	int k = 0;
	for (int n = 0; n < NUM_ITER; n++)
	{
		//if(fitness(*best) >= 775) break; 
		std::cout << fitness(*best) << '\n';
		int j = 0;
		for(int i = 0; i < (SIZE_P - NUM_ELITES); i+=2)
		{
			threads[j++] = std::thread(run, std::ref(pop), std::ref(nova_pop), i);	
		}
		
		
		for(int i = 0; i < (SIZE_P - NUM_ELITES)/2; i++)
		{
			threads[i].join();
		}

		std::nth_element(pop.begin(), pop.begin() + (NUM_ELITES - 1), pop.end(), [](const tabuleiro& t1, const tabuleiro& t2){return fitness(t1) > fitness(t2);});
		
		std::copy(pop.begin(), pop.begin() + NUM_ELITES, nova_pop.begin() + (SIZE_P - NUM_ELITES));
		
		std::swap(pop, nova_pop);
		best = std::max_element(pop.begin(), pop.end(), [](const tabuleiro& t1, const tabuleiro& t2) { return fitness(t1) < fitness(t2); } );
		/*
		system("clear");
		cout << std::string("\033[;") << k++ << "f";
		if (k == 200) k = 0;
		cout << std::string("\U0001F62A\n");
		*/
	}

		
	//cout << *best << '\n' << "fitness: " << static_cast<int>(fitness(*best)) << '\n';

	system("ffplay -nodisp -autoexit tetra.mp3 >/dev/null 2>&1 ");

	return 0;
}

#include <iostream>
using std::cout; 
#include "genetic.hpp"
#define NUM_ITER 1000



int main()
{
	populacao pop;
	populacao nova_pop;
	std::generate(pop.begin(), pop.end(), []() {return gen_state();});
	std::array<std::thread, SIZE_P> threads;
	for (int n = 0; n < NUM_ITER; n++)
	{
		for(int i = 0; i < SIZE_P; i++)
		{
			threads[i] = std::thread(run, std::ref(pop), std::ref(nova_pop), i);	

		}

		for(int i = 0; i < SIZE_P; i++)
		{
			threads[i].join();
		}

		std::swap(pop, nova_pop);
		cout << "next iteration\n";
	}

	auto best = std::max_element(pop.begin(), pop.end(), [](const tabuleiro& t1, const tabuleiro& t2) { return fitness(t1) < fitness(t2); } );
	
	cout << *best << '\n' << "fitness: " << static_cast<int>(fitness(*best)) << '\n';


	return 0;
}

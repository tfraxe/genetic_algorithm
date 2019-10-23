#include <iostream>
#include <thread>
#include <functional>
#include "queens.hpp"
#include "genetic.hpp"
#include <queue>

int main()
{
	tabuleiro tab = gen_state();
	
//	std::cout << tab;
	
	/*
	std::vector<tabuleiro> suc;
	auto f = std::bind(gen_sucessores, tab, std::placeholders::_1, std::ref(suc));
	std::thread first(f, 0);
	std::thread second(f, 1);
	first.join();
	second.join();
	std::cout << "terminou" << std::endl;
	for (auto s : suc) std::cout << s;
	*/

	
//	std::cout << static_cast<int> (fitness(tabuleiro{1, 3, 6, 3, 7, 4, 4, 1})) << '\n';	
	
	populacao pop{ tabuleiro{1, 3, 6, 3, 7, 4, 4, 1}, tabuleiro {2, 1, 6, 4, 1, 3, 0, 0},
			tabuleiro{1, 3, 3, 0, 4, 0, 1, 3}, tabuleiro{2, 1, 4, 3, 2, 1, 0, 2}};

	std::array<unsigned int, SIZE_P> acc = prep_accumulate(pop);


	/*	
	for (auto a : acc)
	{
		std::cout << a << " ";
	}
	*/
	
	std::cout << '\n';
/*	
	for (int i = 0; i < 1000000; i++)
		std::cout << selection(acc) << '\n';

*/
	/*
	std::cout << crossover(gen_state(), gen_state()) << '\n';
	
	std::cout << "antes da mutação: " << tab << '\n';
	mutation(tab);
	std::cout << "depois da mutação: " << tab << '\n';	
*/


		populacao p1;
		std::generate(p1.begin(), p1.end(), gen_state);
	
		for (auto p : p1) std::cout << fitness(p) << '\n';
		
		std::nth_element(p1.begin(), p1.begin() + 5, p1.end(), [](const tabuleiro& t1, const tabuleiro& t2){return fitness(t1) > fitness(t2);});
	
		std::cout << '\n';
		for (auto p : p1) std::cout << fitness(p) << '\n';		

		return 0;

}

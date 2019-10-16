#include <iostream>
#include <thread>
#include <functional>
#include "queens.hpp"
#include "genetic.hpp"
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
	std::cout << crossover(gen_state(), gen_state()) << '\n';
	return 0;

}

#ifndef GENETIC_HPP
#define GENETIC_HPP

#include "queens.hpp"

#define SIZE_P 1000 
using populacao = std::array<tabuleiro, SIZE_P>;

std::array<unsigned int, SIZE_P> prep_accumulate(populacao& pop)
{
	std::array<unsigned int, SIZE_P> acc;
	//auto p = pop.begin();
	std::generate(acc.begin(), acc.end(), [p = pop.begin(), s = 0] () mutable {
							int f = fitness(*(p++));
							s += f;
							return s;
							});


	return acc;


}

unsigned int selection(const std::array<unsigned int, SIZE_P>& acc)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	
	std::uniform_int_distribution<> dis(0, acc[SIZE_P -1]);

	unsigned int r = dis(gen);	

	auto escolhido = std::lower_bound(acc.begin(), acc.end(), r);


	return static_cast<unsigned int> (escolhido - acc.begin());

} 


tabuleiro crossover(const tabuleiro& tab1, const tabuleiro& tab2)
{

	//std::cout << "tab1 = " << tab1 << '\n';
	//std::cout << "tab2 = " << tab2 << '\n';
	static std::random_device rd;
	static std::mt19937 gen(rd());
	
	std::uniform_int_distribution<> dis(1, SIZE - 1);
	
	// choosing two random points to cut the first parent
	unsigned int alA = dis(gen);
	unsigned int alB;
	do { alB = dis(gen); } while( alA == alB);
	if (alA > alB) std::swap(alA, alB);

	//std::cout << "al : " << alA << " alB: " << alB << '\n';

	std::array<bool, SIZE> cortados;
	std::fill(cortados.begin(), cortados.end(), false);

	std::for_each(tab1.begin() + alA, tab1.begin() + alB + 1, [&cortados](linha l) {cortados[l] = true;} );									
						
	//for (auto& c : cortados) std::cout << c << " ";
	//std::cout << '\n';
	tabuleiro filho;
	std::copy(tab1.begin() + alA, tab1.begin() + alB + 1, filho.begin() + alA);
	//std::cout << "copy : " << filho << '\n';
	
	{
		auto it_filho = filho.begin();
		const auto it_inicial = filho.begin();
		for (auto& t : tab2)
		{
			if(!cortados[t])
			{
				*(it_filho++) = t;
				if (it_filho - it_inicial == alA) it_filho = it_inicial + alB + 1;

			}	


		}

	}

	//std::cout << "filho: " << filho << '\n';
	return filho;
	
	

}

void mutation(tabuleiro& tab)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, SIZE - 1);
	
	unsigned int alA = dis(gen);
	unsigned int alB;

	do {alB = dis(gen);} while(alB == alA);
	
	std::swap(tab[alA], tab[alB]);

}

void run(populacao& pop, populacao& nova_pop, unsigned int i)
{
	static std::array<unsigned int, SIZE_P> acc = prep_accumulate(pop);
	unsigned int parent1 = selection(acc);
	unsigned int parent2 = selection(acc);
			
	//tabuleiro filho = crossover(pop[parent1], pop[parent2]);
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<> dis(0, 1);
	tabuleiro filho1;
	tabuleiro filho2;	
	if (dis(gen) <= 0.65)
	{	
		filho1 = crossover(pop[parent1], pop[parent2]);
		filho2 = crossover(pop[parent2], pop[parent1]);
	}
	else 
	{
		filho1 = pop[parent1];
		filho2 = pop[parent2];
	}
	if (dis(gen) <= 0.1) mutation(filho1);
	if (dis(gen) <= 0.1) mutation(filho2);		
	nova_pop[i] = filho1;
	nova_pop[i+1] = filho2;	


}

#endif
    

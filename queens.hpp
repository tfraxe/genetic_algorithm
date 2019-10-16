#ifndef QUEENS_HPP
#define QUEENS_HPP

#include <random>
#include <array>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>
#include <cmath>
#define SIZE 8
using linha = unsigned char;
using tabuleiro = std::array<linha, SIZE>;
using posicao = std::array<unsigned char, 2>;
using fitness_value = unsigned char;
linha gen_rand_linha()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, SIZE - 1);
	return dis(gen);

}

tabuleiro gen_state2()
{
	tabuleiro tab;
	std::generate(tab.begin(), tab.end(), gen_rand_linha);
	return tab;


}

tabuleiro gen_state()
{
	tabuleiro tab;
	std::iota(tab.begin(), tab.end(), 0); 
	static std::random_device rd;
	static std::mt19937 gen(rd());
	
	std::shuffle(tab.begin(), tab.end(), gen);	
	
	return tab;

}

inline std::ostream& operator<< (std::ostream& os, const tabuleiro& tab)
{
	for (auto& t : tab)
	{
		os << static_cast<unsigned short int> (t) << " ";

	}
	os << '\n';
	return os;

}


/*

--- Não será usado para o algoritmo genético --- 


std::mutex suc_mut;
void gen_sucessores(tabuleiro tab, unsigned char col, std::vector<tabuleiro>& sucessores)
{
	for (int i = 0; i < SIZE-1; i++)
	{
		
		linha l = tab[col];
		tab[col] = (l+1) % SIZE;
		std::lock_guard<std::mutex> lock(suc_mut);
		sucessores.emplace_back(tab);
		
	}

}
*/

bool is_attacking(const posicao& p1, const posicao& p2)
{
	if (p1[0] == p2[0]) return true;
	
	if ( abs(p1[0] - p2[0]) == abs(p1[1] - p2[1])) return true;
	else return false; 

}

fitness_value fitness(const tabuleiro& tab)
{

	fitness_value f_value = 0;
	int number = 0;

	for (unsigned char i = 0; i < SIZE - 1; i++)
	{
		for (unsigned char j = i+1; j < SIZE; j++)
		{
			if( !is_attacking(posicao{tab[i], i}, posicao{tab[j], j})) f_value++; 			
		}
		

	}
	
	

	return f_value;

}


#endif
    

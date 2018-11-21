#include "cstdint"
#include "iostream"
#include <algorithm>
#include <functional>
#include <ctime>
#include "handy.h"
#include "windows.h"
#include "sortings.h"
#include "vector"
#include <random>

using std::cout;
using std::cin;
using std::endl;


template <typename t>
t qlinsearch(std::vector<t>& input, const t& to_find, size_t size){
	resetCounters();
	int32_t i=0;
	std::vector<t>temp(size+1);
	for (size_t i = 0; i < temp.size()-1; i++) {
		temp[i] = input[i];
	}
	temp[size] = to_find;
	for(size_t i=0; i< size+1; i++){
		comps_count++;
		if(temp[i] == to_find){
			comps_count++;
			if(i == size){
				return -1;
			}
			else{
				return	input[i];
			}
		}
	}
}

template <typename t>
t qlinsearch_ordered(std::vector<t>& input, const t& to_find, size_t size, bool reset=true) {
	if (reset) {
		resetCounters();
	}
	int32_t i = 0;
	std::vector<t>temp(size + 1);
	for (size_t i = 0; i < temp.size() - 1; i++) {
		temp[i] = input[i];
	}
	temp[size] = to_find;
	for (size_t i = 0; i< size + 1; i++) {
		comps_count++;
		if (temp[i] > to_find) {
			return -1;
		}
		else {
			comps_count++;
			if (temp[i] == to_find) {
				comps_count++;
				if (i == size) {
					return -1;
				}
				else {
					return	input[i];
				}
			}
		}
	}
}

template <typename t>
t linsearch(std::vector<t>& input, const t& to_find, size_t size){
	resetCounters();
	size_t i = 0;
	while (i < size){
		comps_count+=2;
		if (input[i] == to_find) {
			return input[i];
		}
		i++;
	}
	return -1;
}

template <typename t>
t binsearch_ordered(std::vector<t>& input, const t& to_find, size_t left, size_t right, bool first_run = true) {
	if (first_run) {
		resetCounters();
		first_run = false;
	}
	t pivot;
	if (right>=1) {
		pivot = left + (right - left) / 2;
		comps_count++;
		if (pivot == to_find) {
			return pivot;
		}
		else {
			if (to_find > pivot) {
				return binsearch_ordered(input, to_find, pivot+1, right, false);
			}	
			else {
				return binsearch_ordered(input, to_find, left, pivot-1, false);
			}
		}
	}
	return -1;
}

template <typename t>
t blocksearch(std::vector<t>& input, const t& to_find, size_t size) {
	resetCounters();
	int32_t blocks = 10;
	int32_t start = 0;
	for (size_t i = 10; i <= size; i+=blocks, start+=blocks) {
		comps_count++;
		if (to_find < i) {
			std::vector<t> temp(input.begin() + start, input.begin()+start+blocks);
			return qlinsearch_ordered(temp, to_find, blocks-1, false);
		}
	}
	return -1;
}



int32_t main(){
	SetConsoleOutputCP(1251);
	srand(time(0));
	int32_t algos = 5;
	int32_t arrays = 9;
	int** max_comps = new int*[algos];
	int** avg_comps = new int*[algos];
	for (size_t i = 0; i < algos; i++) {
		max_comps[i] = new int[arrays];
		avg_comps[i] = new int[arrays];
	}
	size_t size = 450;
	std::vector<int32_t> array(size);
	std::vector<int32_t> array_ordered(size);
	std::random_device rd;
	std::mt19937 g(rd());
	for(size_t i = 0; i<size; i++){
		array[i] = i;
		array_ordered[i] = i;
	}
	std::shuffle(array.begin(), array.end(), g);
	cout << "јнализ количества операций сравнени€ дл€ различных алгоритмов поиска, массивы размером от 50 до 450 элементов с шагом 50.\n";
	cout << "\t" << "ћаксимальное количество операций сравнени€ \n";
	for (size_t i=0; i < algos; i++) {
		for (size_t k = 50, col=0; k <= 450; k += 50, col++) {
			switch (i) {
				case 0: {
					linsearch(array, array[k-1], k);
					max_comps[i][col] = comps_count;
					break;
					}
				case 1: {
					qlinsearch(array, array[k-1], k);
					max_comps[i][col] = comps_count;
					break;
				}
				case 2: {
					qlinsearch_ordered(array_ordered, array_ordered[k - 1], k);
					max_comps[i][col] = comps_count;
					break;
				}
				case 3: {
					binsearch_ordered(array_ordered, array_ordered[k -1], 0, k);
					max_comps[i][col] = comps_count;
					break;
				}
				case 4: {
					blocksearch(array_ordered, array_ordered[k - 1], k);
					max_comps[i][col] = comps_count;
					break;
				}
				default: {
					break;
				}
			}
		}
	}
	
	print_matrix(max_comps, 5, arrays);
	cout << "\t" << "—реднее количество операций сравнени€ \n";
	int32_t comps_stored = 0;
	for (size_t i = 0; i < algos; i++) {
		for (size_t k = 50, col = 0; k <= 450; k += 50, col++) {
			switch (i) {
				case 0: {
					comps_stored = 0;
					for (size_t j = 0; j < k; j++) {
						linsearch(array, array[j], k);
						comps_stored += comps_count;
					}
					avg_comps[i][col] = comps_stored/k;
					break;
				}
				case 1: {
					comps_stored = 0;
					for (size_t j = 0; j < k; j++) {
						qlinsearch(array, array[j], k);
						comps_stored += comps_count;
					}
					avg_comps[i][col] = comps_stored/k;
					break;
				}
				case 2: {
					comps_stored = 0;
					for (size_t j = 0; j < k; j++) {
						qlinsearch_ordered(array_ordered, array_ordered[j], k);
						comps_stored += comps_count;
					}
					avg_comps[i][col] = comps_stored/k;
					break;
				}
				case 3: {
					comps_stored = 0;
					for (size_t j = 0; j < k; j++) {
						binsearch_ordered(array_ordered, array_ordered[j], 0, k);
						comps_stored += comps_count;
					}
					avg_comps[i][col] = comps_stored/k;
					break;
				}
				case 4: {
					comps_stored = 0;
					for (size_t j = 0; j < k; j++) {
						blocksearch(array_ordered, array_ordered[j], k);
						comps_stored += comps_count;
					}
					blocksearch(array_ordered, array_ordered[k - 1], k);
					avg_comps[i][col] = comps_stored/k;
					break;
				}
				default: {
					break;
				}
			}
		}
	}
	cout << endl;
	print_matrix(avg_comps, 5, arrays);
	print_array(array, size);
}
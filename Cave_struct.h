#ifndef CAVE_STRUCT_H
#define CAVE_STRUCT_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono> 
#include <algorithm>
#include <random>

enum Kind{
	kCave,
	kForest
};

template <Kind>
struct DMatrix {
};



template<> struct DMatrix<kCave> {
	using value_type = int;
	using data_type = std::vector<value_type>;
    using return_type = DMatrix<kCave>;

	data_type data;
	value_type rows = 0, cols = 0;

    int &operator()(std::size_t row, std::size_t col) {
        return data[row * cols + col];
    }

	int operator()(std::size_t row, std::size_t col) const {
		if ((row > rows) || (col > cols))
			return 1;
		return data[row * cols + col];
	}

	void print (){
		for (std::size_t row = 0 ; row < rows; row ++){
			for (std::size_t col = 0 ; col < cols; col ++){
				int v = (*this) (row, col);
				if ( v == 1){
					std::cout << std::setw(2) << '#';
				}
				else if ( v == 0){
					std::cout << std::setw(2) << ' ';
				}
				else {
                    std::cout << std::setw(2) << v;
                }
			}
			std::cout << '\n';
		}
	}

    bool save_cave(std::string& fileName){

    }
    
    void InitializeCave(value_type rows, value_type cols, value_type live_chance){
        std::default_random_engine DRE(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution <value_type> dist(0, 100);
        this->rows = rows;
        this->cols = cols;
        data.resize(rows * cols);
        std::generate(data.begin(), data.end(), [&dist, &DRE, live_chance] {
            value_type chance = dist(DRE);
            return chance <= live_chance ? 1 : 0;
        });

    };

};







#endif // CAVE_STRUCT_H
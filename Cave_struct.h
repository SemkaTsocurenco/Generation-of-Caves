#ifndef CAVE_STRUCT_H
#define CAVE_STRUCT_H

#include <vector>
#include <iostream>
#include <iomanip>


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
					std::cout << std::setw(3) << '#';
				}
				else if ( v == 0){
					std::cout << std::setw(3) << '.';
				}
				else {
                    std::cout << std::setw(3) << v;
                }
			}
			std::cout << '\n';
		}
	}

};

#endif // CAVE_STRUCT_H
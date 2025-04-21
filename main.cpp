#include "Cave_struct.h"



struct GenerationSettings {
	int rows, cols;
	int live_chance;
	int generation_count;
	std::pair <int, int> live_limit, born_limit;
};



int main (){



	DMatrix<kCave> cave;
	cave.rows = 10;
	cave.cols = 12;

	cave.data.resize(cave.cols * cave.rows);

	cave(2, 5) = 1;
	cave(2, 6) = 1;
	cave(2, 7) = 1;
	cave(3, 5) = 1;
	cave(3, 7) = 1;
	cave(11, 11) = 1;
	std::cout<<cave(2, 5)<<"   ,"<< cave(11,11)<<"\n";

	cave.print();

	return 0;
}

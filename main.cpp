#include "Cave_struct.h"


using value_type = int;

struct GenerationSettings {
	value_type rows, cols;
	value_type live_chance;
	value_type generation_count;
	std::pair <value_type, value_type> live_limit, born_limit;
};

int main (){
	DMatrix<kCave> cave;
	cave.InitializeCave(10 ,12, 40);
	cave.print();

	return 0;
}

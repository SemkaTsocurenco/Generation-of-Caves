#include "Cave_struct.h"
#include "Gen_settings.h"


using value_type = int;

int main (){
	GenerationSettings settings;
	settings.read_settings("../config.csv");

	DMatrix<kCave> cave;
	cave.InitializeCave(settings.rows ,settings.cols, settings.live_chance);
	cave.print();

	return 0;
}

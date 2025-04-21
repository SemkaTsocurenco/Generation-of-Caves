#include "Cave_struct.h"
#include "Gen_settings.h"


using value_type = int;

value_type CountLiveNeigbors(value_type row, value_type col, const DMatrix<kCave>& cave){
	value_type count = 0;
	for (auto item: {cave(row, col - 1), cave(row, col + 1), cave(row - 1, col), cave(row + 1, col),
					cave(row - 1, col - 1), cave(row - 1, col + 1), cave(row + 1, col - 1),
					cave(row + 1, col + 1)})
	if (item != 0)
		count++;
	return count;
}

DMatrix<kCave> Generate(GenerationSettings &s) {
	
	std::string name = "../config.csv";
	if (s.read_settings(name)){
		std::cout<<"\nПуть до файла настроек : \33[33m"<< name<<"\n\33[0m";
		s.print();
		std::cout<<"\33[32mФайл настроек генерации успешно прочитан! \33[0m\n\n\n";
	} else {
		std::cout<<"\n\33[31mФайл настроек не прочитан! \n\n\n";
	}

    DMatrix<kCave> cave;
	cave.InitializeCave(s.rows ,s.cols, s.live_chance);
	DMatrix<kCave> tmp = cave;

    value_type generation = 0;
    while (generation++ != s.generation_count) {
        for (value_type row = 0; row != cave.rows; ++row) {
            for (value_type col = 0; col != cave.cols; ++col) {
                value_type count = CountLiveNeigbors(row, col, cave);

                if (cave(row, col) == 1 and (count < s.live_limit.first or count > s.live_limit.second))
                    tmp(row, col) = 0;
                else if (cave(row, col) == 0 and (count >= s.born_limit.first and count <= s.born_limit.second))
                    tmp(row, col) = 1;
            }
        }
        std::copy(tmp.data.begin(), tmp.data.end(), cave.data.begin());
    }
    return cave;
}

int main (){

	GenerationSettings settings;
	DMatrix<kCave> cave;
	cave = Generate(settings);
	cave.print();

	return 0;
}

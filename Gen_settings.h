#ifndef GEN_SETTINGS_H
#define GEN_SETTINGS_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <fstream>    
#include <sstream>    
#include <string>
#include <cctype>     

struct GenerationSettings {
    using value_type = int;
    value_type rows   = 10;
    value_type cols   = 10;
    value_type live_chance      = 40;
    value_type generation_count = 20;
    std::pair<value_type, value_type> live_limit  = {0, 100};
    std::pair<value_type, value_type> born_limit  = {0, 100};


    bool read_settings(const std::string& config_file) {
        std::ifstream in(config_file);
        if (!in) {
            std::ofstream out(config_file);
            out << "rows,cols,live_chance,generation_count,"
                   "live_limit_min,live_limit_max,"
                   "born_limit_min,born_limit_max\n";
            out << rows << "," << cols << ","
                << live_chance << "," << generation_count << ","
                << live_limit.first << "," << live_limit.second << ","
                << born_limit.first << "," << born_limit.second << "\n";
            return true;
        }

        std::string line;
        if (!std::getline(in, line)) 
            return false;

        if (!std::getline(in, line)) 
            return false;

        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            // удаляем пробелы по краям
            while (!token.empty() && std::isspace(token.front())) token.erase(token.begin());
            while (!token.empty() && std::isspace(token.back()))  token.pop_back();
            tokens.push_back(token);
        }
        if (tokens.size() < 8)
            return false;

        // 4) Конвертируем в числа
        rows             = std::stoi(tokens[0]);
        cols             = std::stoi(tokens[1]);
        live_chance      = std::stoi(tokens[2]);
        generation_count = std::stoi(tokens[3]);
        live_limit.first  = std::stoi(tokens[4]);
        live_limit.second = std::stoi(tokens[5]);
        born_limit.first  = std::stoi(tokens[6]);
        born_limit.second = std::stoi(tokens[7]);

        return true;
    }


};





#endif // GEN_SETTINGS_H
#ifndef CAVE_STRUCT_H
#define CAVE_STRUCT_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>    

enum Kind {
    kCave,
    kForest
};

template <Kind>
struct DMatrix { };

template<>
struct DMatrix<kCave> {
    using value_type  = int;
    using data_type   = std::vector<value_type>;
    using return_type = DMatrix<kCave>;

    data_type   data;
    value_type  rows = 0, cols = 0;

    int &operator()(std::size_t row, std::size_t col) {
        return data[row * cols + col];
    }

    int operator()(std::size_t row, std::size_t col) const {
        if (row >= rows || col >= cols)
            return 1;
        return data[row * cols + col];
    }

    void print() const {
        for (std::size_t r = 0; r < rows; ++r) {
            for (std::size_t c = 0; c < cols; ++c) {
                int v = (*this)(r, c);
                if (v == 1)
                    std::cout << std::setw(2) << '#';
                else
                    std::cout << std::setw(2) << ' ';
            }
            std::cout << "\n";
        }
    }


    bool save_cave(const std::string& fileName) const {
        std::ofstream out(fileName);
        if (!out.is_open()) {
            return false;
        }
        for (std::size_t r = 0; r < rows; ++r) {
            for (std::size_t c = 0; c < cols; ++c) {
                int v = (*this)(r, c);
                // стены как '#', пустое пространство — пробел
                out << (v == 1 ? '#' : ' ');
            }
            out << '\n';
        }
        return true;
    }

    void InitializeCave(value_type rows_, value_type cols_, value_type live_chance) {
        rows = rows_;
        cols = cols_;
        data.resize(rows * cols);

        std::default_random_engine DRE(
            std::chrono::system_clock::now().time_since_epoch().count()
        );
        std::uniform_int_distribution<value_type> dist(0, 100);

        std::generate(data.begin(), data.end(),
            [&dist, &DRE, live_chance]() {
                return dist(DRE) <= live_chance ? 1 : 0;
            }
        );
    }
};

#endif // CAVE_STRUCT_H

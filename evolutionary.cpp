/*
** EPITECH PROJECT, 2020
** TSP
** File description:
** evolutionary
*/

#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include "City.hpp"

int main(int argc, char const *argv[])
{
    if (argc < 3) {
        std::cout << "You must use it like : ./TSP (number of city > 3) (number for population > 3)" << std::endl;
        return 0;
    }
    int citys = std::stoi(argv[1]);
    int pop = std::stoi(argv[2]);
    if (citys < 4 || pop < 4) {
        std::cout << "You must use it like : ./TSP (number of city > 3) (number for population > 3)" << std::endl;
        return 0;
    }
    srand(std::time(0));
    City Genetic(citys, pop);
    Genetic.PrintPoints();
    int generation = 0;
    while (Genetic._bestTurn < 10) {
        Genetic.Generation();
        generation++;
    }
    std::cout << "best fistness : " << Genetic._best << ", at gen : " << generation - 10 << std::endl;
    return 0;
}

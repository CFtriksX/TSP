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
        std::cout << "You must use it like : ./TSP (number of city > 2) (number for population > 2)" << std::endl;
        return;
    }
    int citys = std::stoi(argv[1]);
    int pop = std::stoi(argv[2]);
    if (citys < 2 || pop < 2) {
        std::cout << "You must use it like : ./TSP (number of city > 2) (number for population > 2)" << std::endl;
        return;
    }
    srand(std::time(0));
    City Genetic(citys, pop);
    Genetic.PrintPoints();
    while (Genetic._bestTurn < 10) {
        Genetic.Generation();
    }
    std::cout << "best fistness : " << Genetic._best << std::endl;
    return 0;
}

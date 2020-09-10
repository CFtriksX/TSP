/*
** EPITECH PROJECT, 2020
** SalesMan
** File description:
** City
*/

#ifndef CITY_HPP_
#define CITY_HPP_

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

class City {
    public:
        City(int cityCount, int population);
        ~City() {}
        void CalculateFitness(void);
        void Generation(void);
        void PrintPoints(void);
        std::vector<Region> _allPopulation;
        std::map<std::string, std::pair<int, int>> _mapPosition;
        float _best;
        int _bestTurn = 0;

    protected:
    private:
        void GenerateAllPoints(void);
        void CrossOver(Region a, Region b);
        void Mutate(Region &a);
        int _cityCount;
        int _population;
        int _mutation = 20;

};

class Region {
    public:
        Region(int cityCount, std::vector<std::string> allPoints);
        Region();
        ~Region() {}
        void FitnessCount(std::map<std::string, std::pair<int, int>> mapPosition);
        int Distance(std::pair<int, int> city1, std::pair<int, int> city2);

        float _Fitness;
        std::vector<std::string> _order;

    private:

};

#endif /* !CITY_HPP_ */

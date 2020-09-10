/*
** EPITECH PROJECT, 2020
** Salesman
** File description:
** City
*/

#include "City.hpp"

City::City(int cityCount, int population) : _cityCount(cityCount), _population(population)
{
    std::vector<std::string> allPoints;

    GenerateAllPoints();
    for (int i = 0; i != _cityCount; i++) {
        allPoints.push_back(std::to_string(i + 1));
    }
    for (int i = 0; i != _population; i++) {
        _allPopulation.push_back(Region(_cityCount, allPoints));
    }
}

void City::PrintPoints(void)
{
    std::vector<std::vector<char>> map;
    std::vector<char> buffer;
    for (int i = 0; i != 101; i++) {
        buffer.push_back(' ');
    }
    for (int i = 0; i != 101; i++) {
            map.push_back(buffer);
    }
    std::cout << "Here is all city on the map : " << std::endl;
    for (auto it = _mapPosition.begin(); it != _mapPosition.end(); it++) {
        map[it->second.second][it->second.first] = 'X';
        std::cout << "City : " << it->first << " [" << it->second.first << ", " << it->second.second << "]" << std::endl;
    }
    std::cout << "Here is the map :" << std::endl;
    for (auto it = map.begin(); it != map.end(); it++) {
        for (auto it2 = it->begin(); it2 != it->end(); it2++) {
            std::cout << *it2;
        }
        std::cout << std::endl;
    }
}

void City::GenerateAllPoints(void)
{
    for (int i = 0; i != _cityCount; i++) {
        std::pair<int, int> buffer;
        buffer.first = rand() % 101;
        buffer.second = rand() % 101;
        _mapPosition[std::to_string(i + 1)] = buffer;
    }
}

void City::CalculateFitness(void)
{
    for (auto it = _allPopulation.begin(); it != _allPopulation.end(); it++) {
        it->FitnessCount(_mapPosition);
    }
    struct {
        bool operator()(Region a, Region b) const
        {   
            return a._Fitness < b._Fitness;
        }   
    } customSort;
    std::sort(_allPopulation.begin(), _allPopulation.end(), customSort);
    int i = 0;
    for (auto it = _allPopulation.begin(); it != _allPopulation.end() && i < 50; it++, i++) {
        std::cout << "Fitness : " << it->_Fitness << " Order :";
        for (auto cityIt = it->_order.begin(); cityIt != it->_order.end(); cityIt++) {
            std::cout << ", " << *cityIt;
        }
        std::cout << std::endl;
    }
}

void City::Mutate(Region &a)
{
        if (rand() % 100 < _mutation) {
            int posBuff = rand() % _cityCount;
            int newPosBuff = rand() % _cityCount;
            std::string cityBuff = a._order[posBuff];

            a._order[posBuff] = a._order[newPosBuff];
            a._order[newPosBuff] = cityBuff;
        }
}

void City::CrossOver(Region a, Region b)
{
    int lim = (rand() % (_cityCount - 1)) + 1;
    Region newRegionA;
    Region newRegionB;

    for (int i = 0; i != _cityCount; i++) {
        if (i < lim) {
            newRegionA._order.push_back(a._order[i]);
            newRegionA._order.push_back(b._order[i]);
        } else {
            newRegionA._order.push_back(b._order[i]);
            newRegionA._order.push_back(a._order[i]);
        }
    }
    Mutate(a);
    Mutate(b);
    _allPopulation.push_back(a);
    if (_allPopulation.size() != _population) {
        _allPopulation.push_back(b);
    }
}

void City::Generation(void)
{
    std::vector<Region> newMap;

    std::cout << "Calculate Fitness : " << std::endl;
    CalculateFitness();
    if (_best == _allPopulation.begin()->_Fitness) {
        _bestTurn += 1;
    } else if (_best > _allPopulation.begin()->_Fitness) {
        _bestTurn = 0;
        _best = _allPopulation.begin()->_Fitness;
    }

    _best = _allPopulation.begin()->_Fitness;
    for (int i = 0; i < _population / 2; i++) {
        newMap.push_back(_allPopulation[i]);
    }
    _allPopulation.clear();
    _allPopulation = newMap;
    std::cout << "Creation new pop !" << std::endl; 
    auto it = _allPopulation.begin();
    for (auto itNext = _allPopulation.begin() + 1; _allPopulation.size() < _population; it++, itNext++) {
        if (itNext == _allPopulation.end()) {
            break;
        }
        CrossOver(*it, *itNext);
    }
    while (_allPopulation.size() != _population) {
        CrossOver(*it, *_allPopulation.begin());
    }
    _mutation -= 2;
    if (_mutation < 0) {
        _mutation = 0;
    }
}

Region::Region(int citycCount, std::vector<std::string> allPoints)
{
    for (int i = 0; i != citycCount; i++) {
        int toAdd = rand() % allPoints.size();
        _order.push_back(allPoints[toAdd]);
        auto it = allPoints.begin();
        for (int j = 0; j != toAdd; j++, it++);
        allPoints.erase(it);
    }
}

void Region::FitnessCount(std::map<std::string, std::pair<int, int>> mapPosition)
{
    _Fitness = 0;
    auto it = _order.begin();
    for (auto nextIt = _order.begin() + 1; nextIt != _order.end(); it++, nextIt++) {
        _Fitness += Distance(mapPosition[*it], mapPosition[*nextIt]);
    }
    _Fitness += Distance(mapPosition[*(_order.begin())], mapPosition[*it]);
}

float Region::Distance(std::pair<int, int> city1, std::pair<int, int> city2)
{
    float xValue = pow(city1.first - city2.first, 2);
    float yValue = pow(city1.second - city2.second, 2);
    return (sqrt(xValue + yValue));
}
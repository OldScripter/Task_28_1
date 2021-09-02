#include <iostream>
#include "include/Swimmer.h"
#include <map>
#include <list>

/**
 * @function Get the double value from input.
 * @param [in] label std::string
 * @return double
 */
double getDoubleFromCin(std::string label)
{
    std::cout << label;
    double result{-1};
    std::string buffer;
    std::getline(std::cin, buffer);
    try
    {
        result = std::stod(buffer);
    }
    catch (...)
    {
        std::cerr << "Double value input error. Try again.\n";
    }
    return result;
}

/**
 * @function Run swim method for pointed swimmer. Convenient to use in separate thread.
 * @param [in,out] swimmer
 */
void swim(Swimmer* swimmer)
{
    swimmer->swim();
}

const int SWIMMERS_COUNT = 6;

int main()
{
    //Create swimmers:
    std::map<double, Swimmer*> swimmers;
    for (int i = 0; i < SWIMMERS_COUNT; ++i)
    {
        std::cout << "Please enter the swimmer name: ";
        std::string name;
        std::getline(std::cin, name);

        double speed{0};
        do
        {
            speed = getDoubleFromCin("Please enter his speed [m/s]: ");
        } while (speed <= 0);

        Swimmer* swimmer = new Swimmer(name, speed);
        std::pair<double, Swimmer*> pair = std::make_pair(swimmer->getTimeInSeconds(), swimmer);
        swimmers.emplace(pair);
    }

    //Start swimming:
    std::cout << "Swimming is started!\n";
    std::list<std::thread*> swimmingThreads;
    for (auto & swimmer : swimmers)
    {
        std::thread* swimmingThread = new std::thread(swim, swimmer.second);
        swimmingThreads.push_back(swimmingThread);
    }

    //Joining swimming threads:
    for (std::thread* t : swimmingThreads)
    {
        if (t->joinable()) t->join();
    }

    //Print swimmers dashboard:
    std::cout << "Swimming is finished!\n";
    std::cout << "-----Results-----\n";
    for (auto & swimmer : swimmers)
    {
        std::cout << swimmer.second->getName() << " : " << swimmer.first << " [sec]\n";
    }

    return 0;
}
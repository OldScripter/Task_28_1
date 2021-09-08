#include <iostream>
#include "include/Swimmer.h"
#include <cassert>

//---------- Global     ----------

std::mutex mutex;
const int SWIMMERS_COUNT = 6;

//---------- Functions  ----------

/**
 * @function Get the double value from input.
 * @param [in] label std::string
 * @return double
 */
double getDoubleFromCin(std::string label, double min, double max)
{
    assert(min <= max);
    std::cout << label << "\n\t - from " << min << " to " << max << " (inclusive).\n";
    double result{-1};
    do
    {
        std::string buffer;
        std::getline(std::cin, buffer);

        result = min - 1;
        try
        {
            result = std::stod(buffer);
            if (result < min || result > max)
            {
                std::cerr << "Double value is not between min and max. Try again.\n";
                continue;
            }
        }
        catch (...)
        {
            std::cerr << "Double value input error. Try again.\n";
        }
    } while (result < min || result > max);

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

/**
 * @method Print the distance passed by swimmer.
 * @param [in] swimmer Swimmer*
 */
void getSwimmingStatus(Swimmer* swimmer)
{
    if (swimmer->getDistancePassed() < Swimmer::DISTANCE_TARGET_METERS)
    {
        mutex.lock();
        std::cout << "\t - Swimmer " << swimmer->getName() << " swam " << swimmer->getDistancePassed() << " [meters]\n";
        mutex.unlock();
    }
}

int main()
{
    //Create auxiliary containers:
    std::vector<Swimmer*> swimmers;
    std::vector<Swimmer*> swimResults;

    //Create swimmers:
    for (int i = 0; i < SWIMMERS_COUNT; ++i)
    {
        std::cout << "Please enter the swimmer name: ";
        std::string name;
        std::getline(std::cin, name);
        double speed{0};
        speed = getDoubleFromCin("Please enter his speed [m/s]", Swimmer::MIN_SPEED, Swimmer::MAX_SPEED);
        Swimmer* swimmer = new Swimmer(name, speed, &swimResults, &mutex);
        swimmers.push_back(swimmer);
    }

    //Start swimming:
    std::cout << "Swimming is started!\n";
    std::vector<std::thread*> swimmingThreads;
    for (auto & swimmer : swimmers)
    {
        std::thread* swimmingThread = new std::thread(swim, swimmer);
        swimmingThreads.push_back(swimmingThread);
    }

    //Status update:
    int timePassed = 0;
    do
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        ++timePassed;
        std::cout << "Time passed: " << timePassed << " [sec]\n";
        for (Swimmer* swimmer : swimmers)
        {
            getSwimmingStatus(swimmer);
        }
    } while (swimResults.size() < SWIMMERS_COUNT);

    //Joining swimming threads:
    for (std::thread* t : swimmingThreads)
    {
        if (t->joinable()) t->join();
    }

    //Print swimmers dashboard:
    std::cout << "Swimming is finished!\n";
    std::cout << "-----Results-----\n";
    for (auto & swimmer : swimResults)
    {
        std::cout << swimmer->getName() << " : " << swimmer->getTimeInSeconds() << " [sec]\n";
    }

    return 0;
}
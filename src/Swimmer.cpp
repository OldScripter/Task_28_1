#include "../include/Swimmer.h"

static const int DISTANCE_TARGET_METERS = 100;

Swimmer::Swimmer(std::string name, double speed)
{
    this->name = std::move(name);
    this->speed = speed;
    this->timeInMilliseconds = (int) (DISTANCE_TARGET_METERS * 1000 / speed);
}

void Swimmer::swim()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(timeInMilliseconds));
    std::cout << "Swimmer " << name << " finished!\n";
}

double Swimmer::getTimeInSeconds() const
{
    return ((double)timeInMilliseconds / 1000);
}

std::string Swimmer::getName()
{
    return this->name;
}
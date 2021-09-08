#include "../include/Swimmer.h"

Swimmer::Swimmer(std::string name, double speed, std::vector<Swimmer*>* swimResults, std::mutex* mutex)
{
    this->name = std::move(name);
    this->speed = speed;
    this->calculatedTimeMilliseconds = (int) (DISTANCE_TARGET_METERS * 1000 / speed);
    this->elapsedTimeInMilliseconds = calculatedTimeMilliseconds;
    this->swimResults = swimResults;
    this->mutex = mutex;
}

void Swimmer::swim()
{
    do {
        if (elapsedTimeInMilliseconds > UPDATE_RATE_MILLISECONDS)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(UPDATE_RATE_MILLISECONDS));
            elapsedTimeInMilliseconds -= UPDATE_RATE_MILLISECONDS;
            distancePassed += speed * UPDATE_RATE_MILLISECONDS / 1000;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(elapsedTimeInMilliseconds));
            mutex->lock();
            std::cout << "Swimmer " << name << " finished!\n";
            distancePassed = DISTANCE_TARGET_METERS;
            swimResults->push_back(this);
            mutex->unlock();
            break;
        }
    } while (true);
}

double Swimmer::getTimeInSeconds() const
{
    return ((double)calculatedTimeMilliseconds / 1000);
}

std::string Swimmer::getName()
{
    return this->name;
}

int Swimmer::getDistancePassed() const
{
    return this->distancePassed;
}
#ifndef TASK_28_1_SWIMMER_H
#define TASK_28_1_SWIMMER_H

#include <iostream>
#include <thread>
#include <ctime>
#include <vector>
#include <mutex>

class Swimmer {

private:
    const int UPDATE_RATE_MILLISECONDS = 1000;
    std::string name {"No name"};
    double speed {0};
    double distancePassed {0};
    int calculatedTimeMilliseconds{0};
    int elapsedTimeInMilliseconds{0};
    std::vector<Swimmer*>* swimResults;
    std::mutex* mutex;

public:
    static constexpr double MAX_SPEED = 10.0;
    static constexpr double MIN_SPEED = 0.02;
    static constexpr int DISTANCE_TARGET_METERS = 100;
    Swimmer(std::string name, double speed, std::vector<Swimmer*>* swimResults, std::mutex* mutex);
    std::string getName();
    double getTimeInSeconds() const;

    /**
     * @method Start swimming and update passed distance each second.
     */
    void swim();
    int getDistancePassed() const;
};

#endif //TASK_28_1_SWIMMER_H
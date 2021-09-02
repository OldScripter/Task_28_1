#ifndef TASK_28_1_SWIMMER_H
#define TASK_28_1_SWIMMER_H

#include <iostream>
#include <thread>
#include <ctime>

class Swimmer {

private:
    std::string name {"No name"};
    double speed {0};
    int timeInMilliseconds{0};

public:
    Swimmer(std::string name, double speed);
    std::string getName();
    double getTimeInSeconds() const;
    void swim();
};

#endif //TASK_28_1_SWIMMER_H
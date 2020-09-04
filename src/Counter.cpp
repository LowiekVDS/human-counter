#include "Counter.h"

void Counter::reset() {
    counter = 0;
}

void Counter::increase() {
    counter += 1;
}

void Counter::decrease() {
    counter = counter - 1 > 0 ? counter - 1 : 0;
}

int Counter::getCounter() {
    return counter;
}
#include "Counter.h"

void Counter::reset() {
    counter = 0;
    totalInCounter = 0;
    totalOutCounter = 0;
}

void Counter::increase() {
    totalInCounter += 1;
}

void Counter::decrease() {
    totalOutCounter = totalOutCounter + 1 > totalInCounter ? totalOutCounter : totalOutCounter + 1;
}

int Counter::getCounter() {
    return totalInCounter - totalOutCounter;
}

int Counter::getTotalIn() {
  return totalInCounter;
}

int Counter::getTotalOut() {
  return totalOutCounter;
}

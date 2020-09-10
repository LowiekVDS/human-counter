#if !defined(COUNTER_H)
#define COUNTER_H

/**
 * COUNTER HANDLER
 *    This class creates objects that can handle counting natural object (like people)
 */

class Counter {
  public:

    void reset();
    void increase();
    void decrease();

    int getCounter();

  private:
    int counter;
};
#endif // COUNTER_H
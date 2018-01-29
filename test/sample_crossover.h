#ifndef _SAMPLE_CROSSOVER_H_
#define _SAMPLE_CROSSOVER_H_

#include "crossover.h"

namespace gatests {

class SampleCrossover
    : public genericga::Crossover<int> {
public:
  void Cross(int *gen1, int *gen2) override {
    int temp = *gen1;
    *gen1 = (*gen1 + *gen2)/2;
    *gen2 = (temp + *gen2)/2;
  }
};

} // namespace gatests

#endif // _SAMPLE_CROSSOVER_H_

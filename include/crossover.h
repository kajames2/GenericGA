#ifndef _CROSSOVER_H_
#define _CROSSOVER_H_

namespace genericga {

template <class Gen> class Crossover {
public:
  virtual void Cross(Gen *genotype1, Gen *genotype2);
};
} // namespace genericga

#endif // _CROSSOVER_H_

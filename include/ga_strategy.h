#ifndef _GA_STRATEGY_H_
#define _GA_STRATEGY_H_

namespace genericga {
template <class Gen, class Phen> struct GAStrategy {
public:
  GAStrategy(Gen genotype, Phen phenotype, double fitness);
  Gen genotype;
  Phen phenotype;
  double fitness;

  bool operator<(const GAStrategy other) const {
    return fitness > other.fitness;
  }
};
} // namespace genericga

#endif // _GA_STRATEGY_H_

#ifndef _GA_STRATEGY_H_
#define _GA_STRATEGY_H_

namespace genericga {
template <class Genotype, class Phenotype> struct GAStrategy {
public:
  GAStrategy(Genotype genotype, Phenotype phenotype, double fitness);
  Genotype genotype;
  Phenotype phenotype;
  double fitness;

  bool operator<(const GAStrategy other) const {
    return fitness > other.fitness;
  }
};
} // namespace genericga

#endif // _GA_STRATEGY_H_

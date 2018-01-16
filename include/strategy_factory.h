#ifndef _STRATEGY_FACTORY_H_
#define _STRATEGY_FACTORY_H_

#include "ga_strategy.h"
#include <vector>

namespace genericga {

template <class Genotype, class Phenotype> class Population {
public:
  using Strategy = GAStrategy<Genotype, Phenotype>;
  Population(const std::vector<Strategy> strats);
  SelectStrats(const StrategySelector &) {}

private:
  std::vector<Strategy> pop;
};

} // namespace genericga

#endif // _STRATEGY_FACTORY_H_

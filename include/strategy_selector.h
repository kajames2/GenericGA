#ifndef _STRATEGY_SELECTOR_H_
#define _STRATEGY_SELECTOR_H_

#include "vector_ops.h"
#include "population.h"
#include <algorithm>
#include <map>
#include <memory>
#include <vector>

namespace genericga {

template <class Gen, class Phen> class StrategySelector {
public:
public:
  virtual Population<Gen, Phen>
  SelectPopulation(const Population<Gen, Phen> &pop, int n) {
    return pop.GetPopulation(SelectIndexCounts(pop, n));
  }

  virtual std::vector<GAStrategy<Gen, Phen>>
  SelectStrategies(const Population<Gen, Phen> &pop, int n) {
    pop.GetStrategies(SelectIndicies(pop, n));
  }

protected:
  virtual std::vector<int> SelectIndices(const Population<Gen, Phen> &pop,
                                         int n) {
    return CountsToVector(SelectIndexCounts(pop, n));
  }
  
  virtual std::map<int, int> SelectIndexCounts(const Population<Gen, Phen> &pop,
                                               int n) {
    return VectorToCounts(SelectIndices(pop, n));
  }
};
} // namespace genericga

#endif // _STRATEGY_SELECTOR_H_

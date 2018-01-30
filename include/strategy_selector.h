#ifndef _STRATEGY_SELECTOR_H_
#define _STRATEGY_SELECTOR_H_

#include "population.h"
#include "vector_ops.h"
#include <algorithm>
#include <map>
#include <memory>
#include <vector>

namespace genericga {

template <class Gen, class Phen> class StrategySelector {
public:
  virtual Population<Gen, Phen>
  SelectPopulation(const Population<Gen, Phen> &pop, int n);
  virtual std::vector<GAStrategy<Gen, Phen>>
  SelectStrategies(const Population<Gen, Phen> &pop, int n);

  virtual std::vector<int> SelectIndices(const Population<Gen, Phen> &pop,
                                         int n);
  virtual std::map<int, int> SelectIndexCounts(const Population<Gen, Phen> &pop,
                                               int n);
};

template <class Gen, class Phen>
Population<Gen, Phen>
StrategySelector<Gen, Phen>::SelectPopulation(const Population<Gen, Phen> &pop,
                                              int n) {
  return pop.GetPopulation(SelectIndexCounts(pop, n));
}

template <class Gen, class Phen>
std::vector<GAStrategy<Gen, Phen>>
StrategySelector<Gen, Phen>::SelectStrategies(const Population<Gen, Phen> &pop,
                                              int n) {
  return pop.GetStrategies(SelectIndices(pop, n));
}

template <class Gen, class Phen>
std::vector<int>
StrategySelector<Gen, Phen>::SelectIndices(const Population<Gen, Phen> &pop,
                                           int n) {
  return CountsToVector(SelectIndexCounts(pop, n));
}

template <class Gen, class Phen>
std::map<int, int>
StrategySelector<Gen, Phen>::SelectIndexCounts(const Population<Gen, Phen> &pop,
                                               int n) {
  return VectorToCounts(SelectIndices(pop, n));
}

} // namespace genericga

#endif // _STRATEGY_SELECTOR_H_

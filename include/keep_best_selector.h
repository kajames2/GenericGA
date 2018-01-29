#ifndef _KEEP_BEST_SELECTOR_H_
#define _KEEP_BEST_SELECTOR_H_

#include "population.h"
#include "strategy_selector.h"
#include "vector_ops.h"
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class KeepBestSelector : public StrategySelector<Gen, Phen> {
public:
  KeepBestSelector() {}
  std::map<int, int> SelectIndexCounts(const Population<Gen, Phen> &pop,
                                       int n) override {
    std::map<int, int> index_counts;
    auto ordering = GetOrderings(pop.GetUniqueFitnesses());
    auto counts = pop.GetFrequencies();
    auto it = ordering.rbegin();
    auto rem_count = n;
    while (it != ordering.rend() && rem_count > 0) {
      int n_add = std::min(rem_count, counts[*it]);
      index_counts.emplace(*it, n_add);
      rem_count -= n_add;
      ++it;
    }
    return index_counts;
  }
};
} // namespace genericga

#endif // _KEEP_BEST_SELECTOR_H_

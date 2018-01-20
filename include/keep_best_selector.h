#ifndef _KEEP_BEST_SELECTOR_H_
#define _KEEP_BEST_SELECTOR_H_

#include "strategy_selector.h"
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class KeepBestSelector : public StrategySelector<Gen, Phen> {
public:
  KeepBestSelector() {}
  std::map<int, int> Select(Population<Gen, Phen> *pop, int n) override {
    std::map<int, int> index_counts;
    pop->Sort();
    auto counts = pop->GetCounts();
    auto i = counts.size() - 1;
    auto rem_count = n;
    while (rem_count > 0 && i >= 0) {
      int n_add = std::min(n, counts[i]);
      index_counts.emplace(i, n_add);
      rem_count -= n_add;
    }
    return index_counts;
  }
};
} // namespace genericga

#endif // _KEEP_BEST_SELECTOR_H_

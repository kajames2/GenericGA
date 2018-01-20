#ifndef _KEEP_BEST_SELECTOR_H_
#define _KEEP_BEST_SELECTOR_H_

#include "strategy_selector.h"
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class KeepBestSelector : public StrategySelector<Gen, Phen> {
public:
  KeepBestSelector() {}
  std::vector<int> SelectIndices(Population<Gen, Phen> *pop, int n) override {
    std::vector<int> ind_vec(n);
    pop->Sort();
    for (int i = pop->size() - n; i < pop->size(); ++i) {
      ind_vec.push_back(i);
    }
    return ind_vec;
  }
};
} // namespace genericga

#endif // _KEEP_BEST_SELECTOR_H_

#ifndef _STRATEGY_SELECTOR_H_
#define _STRATEGY_SELECTOR_H_

#include "population.h"
#include <memory>
#include <vector>
#include <map>
#include <algorithm>

namespace genericga {

template <class Gen, class Phen> class StrategySelector {
public:
  virtual std::map<int, int> Select(Population<Gen, Phen> *strats, int n) {
    std::map<int, int> index_counts;
    auto indices = SelectIndices(strats, n);
    for (auto i : indices) {
      auto loc = std::find(index_counts.begin(), index_counts.end(), i);
      if(loc == index_counts.end()) {
        index_counts.emplace(i, 1);
      } else {
        index_counts[i]++;
      }
    }
  }
 protected:
    virtual std::vector<int> SelectIndices(Population<Gen, Phen> *strats, int n);
};
} // namespace genericga

#endif // _STRATEGY_SELECTOR_H_

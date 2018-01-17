#ifndef _STRATEGY_SELECTOR_H_
#define _STRATEGY_SELECTOR_H_

#include "ga_strategy.h"
#include <memory>
#include <vector>

namespace genericga {

template <class In, class Out> class StrategySelector {
public:
  virtual std::vector<std::shared_ptr<GAStrategy<In, Out>>>
  Select(std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats, int n);

  std::vector<std::shared_ptr<GAStrategy<In, Out>>>
  Select(const std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats,
         const std::vector<int> &indices) {
    int size = strats->size();
    std::vector<std::shared_ptr<GAStrategy<In, Out>>> out_vec(size);
    for (int i = 0; i < size; ++i) {
      out_vec.push_back(strats[indices[i]]);
    }
    return out_vec;
  }
};
} // namespace genericga

#endif // _STRATEGY_SELECTOR_H_

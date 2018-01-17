#ifndef _KEEP_BEST_SELECTOR_H_
#define _KEEP_BEST_SELECTOR_H_

#include "strategy_selector.h"
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class In, class Out>
class KeepBestSelector : public StrategySelector<In, Out> {
public:
  KeepBestSelector() {}
  std::vector<std::shared_ptr<GAStrategy<In, Out>>>
  Select(std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats,
         int n) override {
    std::vector<std::shared_ptr<GAStrategy<In, Out>>> out_vec(n);
    std::sort(strats->begin(), strats->end());
    std::copy(strats->rbegin(), strats->rbegin() + n, out_vec.begin());
    return out_vec;
  }

};
} // namespace genericga

#endif // _KEEP_BEST_SELECTOR_H_

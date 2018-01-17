#ifndef _RANKED_EXPONENTIAL_SELECTOR_H_
#define _RANKED_EXPONENTIAL_SELECTOR_H_

#include "ga_strategy.h"
#include "random_selector.h"
#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

namespace genericga {

template <class In, class Out>
class RankedExponentialSelector : public RandomSelector<In, Out> {
public:
  RankedExponentialSelector() : RandomSelector<In, Out>() {}
  explicit RankedExponentialSelector(int seed)
      : RandomSelector<In, Out>(seed) {}
  virtual std::vector<double> CalculateWeights(
      std::vector<std::shared_ptr<const GAStrategy<In, Out>>> *strats) const {
    int size = strats->size();
    std::sort(strats->begin(), strats->end());
    std::vector<double> out_vec(strats->size());
    for (int i = 0; i < size; ++i) {
      out_vec.push_back(1 - std::exp(-i));
    }
    return out_vec;
  }

private:
  double weight_;
};
} // namespace genericga

#endif // _RANKED_EXPONENTIAL_SELECTOR_H_

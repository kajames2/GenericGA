#ifndef _RANKED_SELECTOR_H_
#define _RANKED_SELECTOR_H_

#include "ga_strategy.h"
#include "random_selector.h"
#include <algorithm>
#include <memory>
#include <vector>

namespace genericga {

template <class In, class Out>
class RankedSelector : public RandomSelector<In, Out> {
public:
  explicit RankedSelector(double weight)
      : weight_(weight), RandomSelector<In, Out>() {}
  explicit RankedSelector(double weight, int seed)
      : weight_(weight), RandomSelector<In, Out>(seed) {}
  virtual std::vector<double> CalculateWeights(
      std::vector<std::shared_ptr<const GAStrategy<In, Out>>> *strats) const {
    int size = strats->size();
    std::sort(strats->begin(), strats->end());
    std::vector<double> out_vec(strats->size());
    for (int i = 0; i < size; ++i) {
      out_vec.push_back((2 - weight_) / size +
                        (2 * i * (weight_ - 1)) / (size * (size - 1)));
    }
    return out_vec;
  }

private:
  double weight_;
};
} // namespace genericga

#endif // _RANKED_SELECTOR_H_

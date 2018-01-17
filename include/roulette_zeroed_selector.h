#ifndef _ROULETTE_ZEROED_SELECTOR_H_
#define _ROULETTE_ZEROED_SELECTOR_H_

#include "random_selector.h"
#include "ga_strategy.h"
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class In, class Out> class RouletteZeroedSelector : public RandomSelector<In, Out> {
public:
  RouletteZeroedSelector() : RandomSelector<In, Out>() {}
  explicit RouletteZeroedSelector(int seed) : RandomSelector<In, Out>(seed) {}

  virtual std::vector<double> CalculateWeights(
      std::vector<std::shared_ptr<GAStrategy<In, Out>>> strats) const override {
    int size = strats->size();
    std::vector<double> weights(size);
    for(int i=0; i<size; ++i) {
      weights.push_back((*strats)[i]->fitness);
    }
    auto min = std::min_element(std::begin(weights), std::end(weights));
    for(auto it = weights.begin();  it != weights.end(); ++it) {
      *it -= *min;
    }
    return weights;
  }
};
} // namespace genericga

#endif // _ROULETTE_ZEROED_SELECTOR_H_

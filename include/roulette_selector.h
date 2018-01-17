#ifndef _ROULETTE_SELECTOR_H_
#define _ROULETTE_SELECTOR_H_

#include "ga_strategy.h"
#include "random_selector.h"
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class In, class Out>
class RouletteSelector : public RandomSelector<In, Out> {
public:
  RouletteSelector() : RandomSelector<In, Out>() {}
  explicit RouletteSelector(int seed) : RandomSelector<In, Out>(seed) {}

  virtual std::vector<double> CalculateWeights(
      std::vector<std::shared_ptr<GAStrategy<In, Out>>> strats) const override {
    int size = strats->size();
    std::vector<double> weights(size);
    for (int i = 0; i < size; ++i) {
      weights.push_back((*strats)[i]->fitness);
    }
    return weights;
  }
};
} // namespace genericga

#endif // _ROULETTE_SELECTOR_H_

#ifndef _ROULETTE_SELECTOR_H_
#define _ROULETTE_SELECTOR_H_

#include "weighted_strategy_selector.h"
#include "ga_strategy.h"
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class In, class Out> struct RouletteSelector : public WeightedStrategySelector<In, Out> {
public:
  RouletteSelector() : WeightedStrategySelector<In, Out>() {}
  explicit RouletteSelector(int seed) : WeightedStrategySelector<In, Out>(seed) {}

  virtual std::vector<double> CalculateWeights(
      std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats) const override {
    std::vector<double> weights(strats->size());
    for(int i=0; i<weights.size(); ++i) {
      weights[i] = (*strats)[i]->fitness;
    }
    return weights;
  }

private:
  std::mt19937 gen_;
};
} // namespace genericga

#endif // _ROULETTE_SELECTOR_H_

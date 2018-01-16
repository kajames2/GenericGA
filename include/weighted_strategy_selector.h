#ifndef _WEIGHTED_STRATEGY_SELECTOR_H_
#define _WEIGHTED_STRATEGY_SELECTOR_H_

#include "ga_strategy.h"
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class In, class Out> struct WeightedStrategySelector {
public:
  WeightedStrategySelector() : gen_(std::random_device()()) {}
  explicit WeightedStrategySelector(int seed) : gen_(seed) {}

  std::vector<std::shared_ptr<GAStrategy<In, Out>>>
  Select(std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats,
         int n) override {
    auto weights = CalculateWeights();
    std::discrete_distribution<> dist(weights.begin(), weights.end());
    std::vector<std::shared_ptr<GAStrategy<In, Out>>> out_vec(n);
    for (int i = 0; i < n; ++i) {
      out_vec[i] = dist(gen_);
    }
    return out_vec;
  }

  virtual std::vector<double> CalculateWeights(
      std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats) const;

private:
  std::mt19937 gen_;
};
} // namespace genericga

#endif // _WEIGHTED_STRATEGY_SELECTOR_H_

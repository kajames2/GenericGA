#ifndef _ROULETTE_SELECTOR_H_
#define _ROULETTE_SELECTOR_H_

#include "population.h"
#include "strategy_selector.h"
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class RouletteSelector : public StrategySelector<Gen, Phen> {
public:
  RouletteSelector() : gen_(std::random_device()()) {}
  explicit RouletteSelector(int seed) : gen_(seed) {}

  virtual std::vector<double>
  CalculateWeights(const Population<Gen, Phen> &pop) const = 0;

  std::vector<int> SelectIndices(const Population<Gen, Phen> &pop,
                                 int n) override {
    auto weights = CalculateWeights(pop);
    auto base_weights = pop.GetFrequencies();
    for (int i = 0; i < weights.size(); ++i) {
      weights[i] *= std::max(0, base_weights[i]);
    }
    std::discrete_distribution<> dist(weights.begin(), weights.end());
    std::vector<int> ind_vec;
    ind_vec.reserve(n);
    for (int i = 0; i < n; ++i) {
      ind_vec.push_back(dist(gen_));
    }
    return ind_vec;
  }

private:
  std::mt19937 gen_;
};
} // namespace genericga

#endif // _ROULETTE_SELECTOR_H_

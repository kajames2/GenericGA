#ifndef _ROULETTE_SELECTOR_H_
#define _ROULETTE_SELECTOR_H_

#include "population.h"
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen> class RouletteSelector {
public:
  RouletteSelector() : gen_(std::random_device()()) {}
  explicit RouletteSelector(int seed) : gen_(seed) {}
  virtual std::vector<double>
  CalculateWeights(Population<Gen, Phen> *pop) const;

  std::vector<int> SelectIndices(Population<Gen, Phen> *pop, int n) override {
    auto weights = CalculateWeights(pop);
    std::discrete_distribution<> dist(weights.begin(), weights.end());
    std::vector<int> ind_vec(n);
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

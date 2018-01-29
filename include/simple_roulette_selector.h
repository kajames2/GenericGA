#ifndef _SIMPLE_ROULETTE_SELECTOR_H_
#define _SIMPLE_ROULETTE_SELECTOR_H_

#include "population.h"
#include "roulette_selector.h"
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class SimpleRouletteSelector : public RouletteSelector<Gen, Phen> {
public:
  SimpleRouletteSelector() : RouletteSelector<Gen, Phen>() {}
  explicit SimpleRouletteSelector(int seed)
      : RouletteSelector<Gen, Phen>(seed) {}

  std::vector<double>
  CalculateWeights(const Population<Gen, Phen> &pop) const override {
    return pop.GetUniqueFitnesses();
  }
};
} // namespace genericga

#endif // _SIMPLE_ROULETTE_SELECTOR_H_

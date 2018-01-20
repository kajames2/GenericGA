#ifndef _ROULETTE_ZEROED_SELECTOR_H_
#define _ROULETTE_ZEROED_SELECTOR_H_

#include "population.h"
#include "roulette_selector.h"
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class RouletteZeroedSelector : public RouletteSelector<Gen, Phen> {
public:
  RouletteZeroedSelector() : RouletteSelector<Gen, Phen>() {}
  explicit RouletteZeroedSelector(int seed) : RouletteSelector<Gen, Phen>(seed) {}

  virtual std::vector<double>
  CalculateWeights(Population<Gen, Phen> *pop) const override {
    auto weights = pop->GetFitnesses();
    auto min = std::min_element(std::begin(weights), std::end(weights));
    for (auto it = weights.begin(); it != weights.end(); ++it) {
      *it -= *min;
    }
    return weights;
  }
};
} // namespace genericga

#endif // _ROULETTE_ZEROED_SELECTOR_H_

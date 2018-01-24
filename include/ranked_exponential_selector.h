#ifndef _RANKED_EXPONENTIAL_SELECTOR_H_
#define _RANKED_EXPONENTIAL_SELECTOR_H_

#include "population.h"
#include "ranked_selector.h"
#include <cmath>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class RankedExponentialSelector : public RankedSelector<Gen, Phen> {
public:
  RankedExponentialSelector() : RankedSelector<Gen, Phen>() {}
  explicit RankedExponentialSelector(int seed)
      : RankedSelector<Gen, Phen>(seed) {}
  std::vector<double>
  CalculateWeights(Population<Gen, Phen> *pop) const override {
    auto ranks = CalculateAverageRanks(pop);
    std::vector<double> out_vec(ranks.size());
    for (auto rank : ranks) {
      out_vec.push_back(1 - std::exp(-rank));
    }
    return out_vec;
  }
};
} // namespace genericga

#endif // _RANKED_EXPONENTIAL_SELECTOR_H_

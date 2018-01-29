#ifndef _WEIGHTED_RANKED_SELECTOR_H_
#define _WEIGHTED_RANKED_SELECTOR_H_

#include "population.h"
#include "ranked_selector.h"
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class WeightedRankedSelector : public RankedSelector<Gen, Phen> {
public:
  WeightedRankedSelector(double weight)
      : weight_(weight), RankedSelector<Gen, Phen>() {}
  explicit WeightedRankedSelector(double weight, int seed)
      : weight_(weight), RankedSelector<Gen, Phen>(seed) {}
  std::vector<double>
  CalculateWeights(const Population<Gen, Phen> &pop) const override {
    auto ranks = CalculateAverageRanks(pop);
    int size = pop.GetNStrategies();
    std::vector<double> out_vec(ranks.size());
    for (auto rank : ranks) {
      out_vec.push_back((1 - weight_) / size +
                        (2 * rank * weight_) / (size * (size - 1)));
    }
    return out_vec;
  }

private:
  double weight_;
};
} // namespace genericga

#endif // _WEIGHTED_RANKED_SELECTOR_H_

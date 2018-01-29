#ifndef _RANKED_SELECTOR_H_
#define _RANKED_SELECTOR_H_

#include "population.h"
#include "roulette_selector.h"
#include "vector_ops.h"
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class RankedSelector : public RouletteSelector<Gen, Phen> {
public:
  explicit RankedSelector() : RouletteSelector<Gen, Phen>() {}
  RankedSelector(int seed) : RouletteSelector<Gen, Phen>(seed) {}

protected:
  // Ranking fitnesses.  Ties get the average of the ranks at that value.
  // ex. fitnesses of 5,6,5,1,5 have ranks: 2,4,2,0,2 (2 = mean(1,2,3))
  std::vector<double> CalculateAverageRanks(const Population<Gen, Phen> &pop) const {
    std::vector<double> out_vec(pop.GetNStrategies(), 0);
    auto fitnesses = pop.GetUniqueFitnesses();
    auto counts = pop.GetFrequencies();
    return GetRankingsWithTies(fitnesses, counts);
  }
};
} // namespace genericga

#endif // _RANKED_SELECTOR_H_

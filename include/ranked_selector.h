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
  std::vector<double> CalculateAverageRanks(Population<Gen, Phen> *pop) const {
    std::vector<double> out_vec(pop->size(), 0);
    auto fitnesses = pop->GetUniqueFitnesses();
    // 1st element is index of smallest fitness, 2nd is of next smallest, etc.
    auto ordering = GetRankings(GetRankings(fitnesses));
    auto counts = pop->GetCounts();
    int low_count = 0;
    int count = 0;
    int n_equal = 0;
    for (auto it = ordering.begin(); it != ordering.end(); ++it) {
      count += counts[*it];
      n_equal++;
      if (it + 1 == ordering.end() || fitnesses[*(it + 1)] != fitnesses[*it]) {
        for (int i = n_equal - 1; i >= 0; ++i) {
          out_vec[*(it - i)] = (count + low_count - 1) / 2.0;
        }
        low_count = count;
        n_equal = 0;
      }
    }
    return out_vec;
  }
};
} // namespace genericga

#endif // _RANKED_SELECTOR_H_

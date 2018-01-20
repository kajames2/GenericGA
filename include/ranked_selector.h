#ifndef _RANKED_SELECTOR_H_
#define _RANKED_SELECTOR_H_

#include "population.h"
#include "roulette_selector.h"
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class RankedSelector : public RouletteSelector<Gen, Phen> {
public:
  explicit RankedSelector()
      : RouletteSelector<Gen, Phen>() {}
  RankedSelector(int seed)
      : RouletteSelector<Gen, Phen>(seed) {}

 protected:
  std::vector<double> CalculateRanks(Population<Gen, Phen> *pop) const {
    int size = pop->size();
    pop->Sort();
    std::vector<double> out_vec(size);
    auto counts = pop->GetCounts();
    auto fitnesses = pop->GetUniqueFitnesses();
    int low_count = 0;
    int count = 0;
    int n_equal = 0;
    for (int i = 0; i < size; ++i) {
      count += counts[i];
      n_equal++;
      if (i == size - 1 || fitnesses[i + 1] != fitnesses[i]) {
        for (int j = 0; j < n_equal; ++j) {
          out_vec.push_back((count + low_count - 1) / 2.0);
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

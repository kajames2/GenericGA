#ifndef _ELITISM_SELECTOR_H_
#define _ELITISM_SELECTOR_H_

#include "keep_best_selector.h"
#include "strategy_selector.h"
#include "vector_ops.h"
#include <algorithm>
#include <map>
#include <memory>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class ElitismSelector : public StrategySelector<Gen, Phen> {
public:
  ElitismSelector(std::shared_ptr<StrategySelector<Gen, Phen>> sel,
                  int n_elites);

  std::vector<int> SelectIndices(const Population<Gen, Phen> &pop,
                                 int n) override;
  std::map<int, int> SelectIndexCounts(const Population<Gen, Phen> &pop,
                                       int n) override;

private:
  std::shared_ptr<StrategySelector<Gen, Phen>> sel_;
  std::unique_ptr<KeepBestSelector<Gen, Phen>> elite_sel_;
  int n_elites_;
};

template <class Gen, class Phen>
ElitismSelector<Gen, Phen>::ElitismSelector(
    std::shared_ptr<StrategySelector<Gen, Phen>> sel, int n_elites)
    : sel_(sel), n_elites_(n_elites),
      elite_sel_(std::make_unique<KeepBestSelector<Gen, Phen>>()) {}

template <class Gen, class Phen>
std::vector<int>
ElitismSelector<Gen, Phen>::SelectIndices(const Population<Gen, Phen> &pop,
                                          int n) {
  int actual_n_elites = std::min(n, n_elites_);
  auto elites = elite_sel_->SelectIndices(pop, actual_n_elites);
  auto rest = sel_->SelectIndices(pop, n - actual_n_elites);
  rest.reserve(elites.size() + rest.size());
  rest.insert(rest.end(), elites.begin(), elites.end());
  return rest;
}

template <class Gen, class Phen>
std::map<int, int>
ElitismSelector<Gen, Phen>::SelectIndexCounts(const Population<Gen, Phen> &pop,
                                              int n) {
  int actual_n_elites = std::min(n, n_elites_);
  auto elites = elite_sel_->SelectIndexCounts(pop, actual_n_elites);
  auto rest = sel_->SelectIndexCounts(pop, n - actual_n_elites);
  AddFrequencies(&rest, &elites);
  return rest;
}

} // namespace genericga

#endif // _ELITISM_SELECTOR_H_

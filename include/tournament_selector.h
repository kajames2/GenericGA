#ifndef _TOURNAMENT_SELECTOR_H_
#define _TOURNAMENT_SELECTOR_H_

#include "population.h"
#include "strategy_selector.h"
#include "vector_ops.h"
#include <random>
#include <vector>

namespace genericga {

template <class Gen, class Phen>
class TournamentSelector : public StrategySelector<Gen, Phen> {
public:
  TournamentSelector(int tourn_size)
      : tourn_size_(tourn_size), gen_(std::random_device()()) {}
  TournamentSelector(int tourn_size, int seed)
      : tourn_size_(tourn_size), gen_(seed) {}
  std::vector<int> SelectIndices(const Population<Gen, Phen> &pop, int n) override {
    auto fitnesses = pop.GetUniqueFitnesses();
    auto counts = pop.GetFrequencies();
    dist = std::discrete_distribution<>(counts.begin(), counts.end());
    std::vector<int> ind_vec;
    ind_vec.reserve(n);
    for (int i = 0; i < n; ++i) {
      ind_vec.push_back(TournamentRound(fitnesses));
    }
    return ind_vec;
  }

  int TournamentRound(const std::vector<double> &fitnesses) {
    return TournamentRound(fitnesses, GenerateTournamentIndices());
  }

  int TournamentRound(const std::vector<double> &fitnesses,
                      std::vector<int> indices) {
    return *std::max_element(
        indices.begin(), indices.end(),
        [&fitnesses](int i1, int i2) { return fitnesses[i1] < fitnesses[i2]; });
  }

  std::vector<int> GenerateTournamentIndices() {
    std::vector<int> tourn_vec(tourn_size_);
    for (int i = 0; i < tourn_size_; ++i) {
      tourn_vec.push_back(dist(gen_));
    }
    return tourn_vec;
  }

private:
  int tourn_size_;
  std::mt19937 gen_;
  std::discrete_distribution<> dist;
};
} // namespace genericga

#endif // _TOURNAMENT_SELECTOR_H_

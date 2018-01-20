#ifndef _TOURNAMENT_SELECTOR_H_
#define _TOURNAMENT_SELECTOR_H_

#include "population.h"
#include "strategy_selector.h"
#include <memory>
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
  std::vector<int> SelectIndices(Population<Gen, Phen> *pop, int n) override {
    pop->Sort();
    dist = std::uniform_int_distribution<>(0, pop->size() - 1);
    std::vector<int> ind_vec(n);
    for (int i = 0; i < n; ++i) {
      ind_vec.push_back(TournamentRound());
    }
    return ind_vec;
  }

  int TournamentRound() { return TournamentRound(GenerateTournamentIndices()); }

  int TournamentRound(std::vector<int> indices) {
    return *std::max_element(indices.begin(), indices.end());
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
  std::uniform_int_distribution<> dist;
};
} // namespace genericga

#endif // _TOURNAMENT_SELECTOR_H_

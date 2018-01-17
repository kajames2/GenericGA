#ifndef _TOURNAMENT_SELECTOR_H_
#define _TOURNAMENT_SELECTOR_H_

#include "strategy_selector.h"
#include <memory>
#include <random>
#include <vector>

namespace genericga {

template <class In, class Out>
class TournamentSelector : public StrategySelector<In, Out> {
public:
  TournamentSelector(int tourn_size)
      : tourn_size_(tourn_size), gen_(std::random_device()()) {}
  TournamentSelector(int tourn_size, int seed)
      : tourn_size_(tourn_size), gen_(seed) {}
  std::vector<std::shared_ptr<GAStrategy<In, Out>>>
  Select(std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats,
         int n) override {
    dist = std::uniform_int_distribution<>(0, strats->size() - 1);
    std::vector<std::shared_ptr<GAStrategy<In, Out>>> out_vec(n);
    for (int i = 0; i < n; ++i) {
      out_vec.push_back(Tournament(strats));
    }
    return out_vec;
  }

  std::shared_ptr<GAStrategy<In, Out>>
  TournamentRound(std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats) {
    return TournamentRound(strats, GenerateTournamentIndices());
  }

  std::shared_ptr<GAStrategy<In, Out>>
  TournamentRound(std::vector<std::shared_ptr<GAStrategy<In, Out>>> *strats,
                  std::vector<int> indices) {
    std::vector<GAStrategy<In, Out>> tourn_vec(tourn_size_);
    for (int index : indices) {
      tourn_vec.push_back((*strats)[index]);
    }
    return std::max_element(tourn_vec.begin(), tourn_vec.end());
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

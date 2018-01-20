#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "ga_strategy.h"
#include <algorithm>
#include <map>
#include <memory>
#include <numeric>
#include <vector>

namespace genericga {

template <class Gen, class Phen> class Population {
public:
  Population();
  Population(const std::vector<GAStrategy<Gen, Phen>> &strats);
  Population(const std::vector<GAStrategy<Gen, Phen>> &unique_strats,
             const std::vector<int> &counts);
  Population SelectStrats(const std::map<int, int> &index_counts);
  const GAStrategy<Gen, Phen> &operator[](int i) const;
  std::vector<double> GetUniqueFitnesses() const;
  std::vector<GAStrategy<Gen, Phen>> GetUniqueStrats() const;
  std::vector<int> GetCounts() const;
  void AddStrategy(GAStrategy<Gen, Phen> strat);
  void Sort();
  int GetNStrategies() const;

private:
  std::vector<GAStrategy<Gen, Phen>> strats_;
  std::vector<int> counts_;
  std::vector<size_t> sorted_indices_;
  int n_strategies_;
  bool is_sorted_;
};

template <class Gen, class Phen>
Population<Gen, Phen>::Population()
    : strats_(), counts_(), is_sorted_(false), sorted_indices_() {}

template <class Gen, class Phen>
Population<Gen, Phen>::Population(
    const std::vector<GAStrategy<Gen, Phen>> &strats)
    : strats_(), counts_(), is_sorted_(false), sorted_indices_() {
  for (auto strat : strats) {
    AddStrategy(strat);
  }
}

template <class Gen, class Phen>
Population<Gen, Phen>::Population(
    const std::vector<GAStrategy<Gen, Phen>> &unique_strats,
    const std::vector<int> &counts)
    : strats_(unique_strats), counts_(counts), is_sorted_(false),
      sorted_indices_(unique_strats.size()) {
  std::iota(sorted_indices_.begin(), sorted_indices_.end(), 0);
  n_strategies_ = 0;
  for (int count : counts) {
    n_strategies_ += count;
  }
}

template <class Gen, class Phen>
Population<Gen, Phen>
Population<Gen, Phen>::SelectStrats(const std::map<int, int> &index_counts) {
  std::vector<GAStrategy<Gen, Phen>> selected_strats(index_counts.size());
  std::vector<int> selected_counts(index_counts.size());
  for (auto pair : index_counts) {
    if (pair.second > 0) {
      selected_strats.push_back(strats_[pair.first]);
      selected_counts.push_back(pair.second);
    }
  }
  return Population(std::move(selected_strats), std::move(selected_counts));
}

template <class Gen, class Phen>
const GAStrategy<Gen, Phen> &Population<Gen, Phen>::operator[](int i) const {
  return strats_[sorted_indices_[i]];
}

template <class Gen, class Phen>
std::vector<double> Population<Gen, Phen>::GetUniqueFitnesses() const {
  std::vector<double> fitnesses(strats_.size());
  for (auto i : sorted_indices_) {
    fitnesses.push_back(strats_[i].fitness);
  }
  return fitnesses;
}

template <class Gen, class Phen>
std::vector<GAStrategy<Gen, Phen>>
Population<Gen, Phen>::GetUniqueStrats() const {
  std::vector<GAStrategy<Gen, Phen>> strats(strats_.size());
  for (auto i : sorted_indices_) {
    strats.push_back(strats_[i]);
  }
  return strats;
}

template <class Gen, class Phen>
std::vector<int> Population<Gen, Phen>::GetCounts() const {
  std::vector<int> counts(strats_.size());
  for (auto i : sorted_indices_) {
    counts.push_back(counts_[i]);
  }
  return counts;
}

template <class Gen, class Phen>
void Population<Gen, Phen>::AddStrategy(GAStrategy<Gen, Phen> strat) {
  auto loc = std::find(strats_.begin(), strats_.end(), strat);
  if (loc == strats_.end()) {
    sorted_indices_.push_back(strats_.size());
    is_sorted_ = false;
    strats_.push_back(strat);
    counts_.push_back(1);
  } else {
    counts_[std::distance(strats_.begin(), loc)]++;
  }
}

template <class Gen, class Phen> void Population<Gen, Phen>::Sort() {
  if (!is_sorted_) {
    std::iota(sorted_indices_.begin(), sorted_indices_.end(), 0);
    sort(sorted_indices_.begin(), sorted_indices_.end(),
         [this](size_t i1, size_t i2) { return strats_[i1] < strats_[i2]; });
    is_sorted_ = true;
  }
}

template <class Gen, class Phen>
int Population<Gen, Phen>::GetNStrategies() const {
  return n_strategies_;
}
} // namespace genericga

#endif // _POPULATION_H_

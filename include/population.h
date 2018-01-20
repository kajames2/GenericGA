#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "ga_strategy.h"
#include <map>
#include <memory>
#include <numeric>
#include <vector>
#include <algorithm>

namespace genericga {

template <class Gen, class Phen> class Population {
public:
  Population(const std::vector<GAStrategy<Gen, Phen>> &strats,
             const std::vector<int> &counts)
      : strats_(strats), counts_(counts), is_sorted_(false), sorted_indices_(strats.size()) {
    std::iota(sorted_indices_.begin(), sorted_indices_.end(), 0);
    n_strategies_ = 0;
    for (int count : counts) {
      n_strategies_ += count;
    }
  }

  Population SelectStrats(const std::map<int, int> &index_counts) {
    std::vector<GAStrategy<Gen, Phen>> selected_strats(index_counts.size());
    std::vector<int> selected_counts(index_counts.size());
    for (auto pair : index_counts) {
      if(pair.second > 0) {
        selected_strats.push_back(strats_[pair.first]);
        selected_counts.push_back(pair.second);
      }
    }
    return Population(std::move(selected_strats), std::move(selected_counts));
  }

  const GAStrategy<Gen, Phen> &operator[](int i) {
    return strats_[sorted_indices_[i]];
  }

  std::vector<double> GetFitnesses() const {
    std::vector<double> fitnesses(strats_.size());
    for (auto i : sorted_indices_) {
      fitnesses.push_back(strats_[i].fitness);
    }
    return fitnesses;
  }

  std::vector<GAStrategy<Gen, Phen>> GetStrats() {
    std::vector<GAStrategy<Gen, Phen>> strats(strats_.size());
    for (auto i : sorted_indices_) {
      strats.push_back(strats_[i]);
    }
    return strats;
  }

  std::vector<int> GetCounts() const {
    std::vector<int> counts(strats_.size());
    for (auto i : sorted_indices_) {
      counts.push_back(counts_[i]);
    }
    return counts;
  }

  void AddStrategy(GAStrategy<Gen, Phen> strat) {
    auto loc = std::find(strats_.begin(), strats_.end(), strat);
    if (loc == strats_.end()) {
      strats_.push_back(strat);
      counts_.push_back(1);
      sorted_indices_.push_back(strats_.size());
      is_sorted_ = false;
    } else {
      counts_[std::distance(strats_.begin(), loc)]++;
    }
  }

  void Sort() {
    if(!is_sorted_) {
      std::iota(sorted_indices_.begin(), sorted_indices_.end(), 0);
      sort(sorted_indices_.begin(), sorted_indices_.end(),
           [this](size_t i1, size_t i2) { return strats_[i1] < strats_[i2]; });
      is_sorted_ = true;
    }
  }

  int GetNStrategies() {
    return n_strategies_;
  }

 private:
  std::vector<GAStrategy<Gen, Phen>> strats_;
  std::vector<int> counts_;
  std::vector<size_t> sorted_indices_;
  int n_strategies_;
  bool is_sorted_;
};

} // namespace genericga

#endif // _POPULATION_H_

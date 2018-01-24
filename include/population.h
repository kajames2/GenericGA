#ifndef _POPULATION_H_
#define _POPULATION_H_

#include "fitness_calculator.h"
#include "ga_strategy.h"
#include "phenotype_converter.h"
#include "vector_ops.h"
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
             const std::vector<int> &frequencies);
  Population GetPopulation(const std::map<int, int> &index_frequencies) const;
  std::vector<GAStrategy<Gen, Phen>>
  GetStrategies(const std::vector<int> &indices) const;
  const GAStrategy<Gen, Phen> &operator[](int i) const;
  std::vector<double> GetUniqueFitnesses() const;
  std::vector<GAStrategy<Gen, Phen>> GetUniqueStrats() const;
  std::vector<int> GetFrequencies() const;
  void AddStrategies(std::vector<GAStrategy<Gen, Phen>> strats);
  void AddStrategies(const Population<Gen, Phen> &pop);
  std::vector<int> GetFitnessRankings() const;
  int GetNStrategies() const;
  void SetFitnessCalculator(std::shared_ptr<FitnessCalculator<Phen>> phen_conv);
  void SetPhenotypeConverter(
      std::shared_ptr<PhenotypeConverter<Gen, Phen>> phen_conv);

private:
  void Aggregate();
  void CalculateNStrategies();
  void AddStrategies(const std::vector<GAStrategy<Gen, Phen>> &sorted_strats,
                     const std::vector<int> &frequencies);

  // Strats are sorted by Genotype
  std::vector<const GAStrategy<Gen, Phen>> sorted_strats_;
  std::vector<int> frequencies_;
  int n_strategies_;
};

template <class Gen, class Phen>
Population<Gen, Phen>::Population()
    : sorted_strats_(), frequencies_(), n_strategies_(0) {}

template <class Gen, class Phen>
Population<Gen, Phen>::Population(
    const std::vector<GAStrategy<Gen, Phen>> &strats)
    : sorted_strats_(), frequencies_(), n_strategies_(strats.size()) {
  AddStrategies(strats);
}

template <class Gen, class Phen>
Population<Gen, Phen>::Population(
    const std::vector<GAStrategy<Gen, Phen>> &sorted_strats,
    const std::vector<int> &frequencies)
    : sorted_strats_(sorted_strats), frequencies_(frequencies) {
  CalculateNStrategies();
}

template <class Gen, class Phen>
Population<Gen, Phen> Population<Gen, Phen>::GetPopulation(
    const std::map<int, int> &index_frequencies) const {
  std::vector<GAStrategy<Gen, Phen>> selected_strats(index_frequencies.size());
  std::vector<int> selected_frequencies(index_frequencies.size());
  for (auto pair : index_frequencies) {
    if (pair.second > 0) {
      selected_strats.push_back(sorted_strats_[pair.first]);
      selected_frequencies.push_back(pair.second);
    }
  }
  return Population(std::move(selected_strats),
                    std::move(selected_frequencies));
}

template <class Gen, class Phen>
std::vector<GAStrategy<Gen, Phen>>
Population<Gen, Phen>::GetStrategies(const std::vector<int> &indices) const {
  std::vector<GAStrategy<Gen, Phen>> strats(indices.size());
  for (auto i : indices) {
    strats.push_back(sorted_strats_[i]);
  }
  return strats;
}

template <class Gen, class Phen>
const GAStrategy<Gen, Phen> &Population<Gen, Phen>::operator[](int i) const {
  return sorted_strats_[i];
}

template <class Gen, class Phen>
std::vector<double> Population<Gen, Phen>::GetUniqueFitnesses() const {
  std::vector<double> fitnesses(sorted_strats_.size());
  for (auto strat : sorted_strats_) {
    fitnesses.push_back(strat.GetFitness());
  }
  return fitnesses;
}

template <class Gen, class Phen>
std::vector<GAStrategy<Gen, Phen>>
Population<Gen, Phen>::GetUniqueStrats() const {
  return sorted_strats_;
}

template <class Gen, class Phen>
std::vector<int> Population<Gen, Phen>::GetFrequencies() const {
  return frequencies_;
}

template <class Gen, class Phen>
void Population<Gen, Phen>::AddStrategies(
    std::vector<GAStrategy<Gen, Phen>> strats) {
  auto other_map = VectorToFrequencies(strats);
  std::vector<GAStrategy<Gen, Phen>> o_sorted_strats(other_map.size());
  std::vector<int> o_frequencies(other_map.size());
  for (auto pair : other_map) {
    o_sorted_strats.push_back(pair.first);
    o_frequencies.push_back(pair.second);
  }
  AddStrategies(o_sorted_strats, o_frequencies);
}

template <class Gen, class Phen>
void Population<Gen, Phen>::AddStrategies(const Population<Gen, Phen> &pop) {
  AddStrategies(pop.sorted_strats_, pop.strat_frequencies);
}

template <class Gen, class Phen>
void Population<Gen, Phen>::AddStrategies(
    const std::vector<GAStrategy<Gen, Phen>> &o_sorted_strats,
    const std::vector<int> &o_frequencies) {
  std::vector<GAStrategy<Gen, Phen>> new_strats(sorted_strats_.size() +
                                                o_sorted_strats.size());
  std::vector<int> new_frequencies(frequencies_.size() + o_frequencies.size());
  int i = 0;
  int j = 0;
  while (j < o_sorted_strats && i < sorted_strats_.size()) {
    if (sorted_strats_[i] < o_sorted_strats[j]) {
      new_strats.push_back(sorted_strats_[i]);
      new_frequencies.push_back(frequencies_[i]);
      ++i;
    } else if (o_sorted_strats[j] < sorted_strats_[i]) {
      new_strats.push_back(o_sorted_strats[j]);
      new_frequencies.push_back(o_frequencies[j]);
      ++j;
    } else {
      new_strats.push_back(sorted_strats_[i]);
      new_frequencies.push_back(frequencies_[i] + o_frequencies[j]);
      ++i;
      ++j;
    }
  }

  if (j < o_sorted_strats.size()) {
    for (; j < o_sorted_strats.size(); ++j) {
      new_strats.push_back(o_sorted_strats[j]);
      new_frequencies.push_back(o_frequencies[j]);
    }
  }
  if (i < sorted_strats_.size()) {
    for (; i < sorted_strats_.size(); ++i) {
      new_strats.push_back(sorted_strats_[i]);
      new_frequencies.push_back(frequencies_[i]);
    }
  }
  sorted_strats_ = std::move(new_strats);
  frequencies_ = std::move(new_frequencies);
  n_strategies_ +=
      std::accumulate(o_frequencies.begin(), o_frequencies.end(), 0);
}

template <class Gen, class Phen>
std::vector<int> Population<Gen, Phen>::GetFitnessRankings() const {
  return GetRankings(GetUniqueFitnesses());
}

template <class Gen, class Phen>
int Population<Gen, Phen>::GetNStrategies() const {
  return n_strategies_;
}

template <class Gen, class Phen> void Population<Gen, Phen>::Aggregate() {
  auto sorted_map = AggregateUnique(sorted_strats_, frequencies_);
  sorted_strats_ = std::vector<GAStrategy<Gen, Phen>>(sorted_map.size());
  frequencies_ = std::vector<GAStrategy<Gen, Phen>>(sorted_map.size());
  for (auto pair : sorted_map) {
    sorted_strats_.push_back(pair.first);
    frequencies_.push_back(pair.second);
  }
}

template <class Gen, class Phen>
void Population<Gen, Phen>::SetFitnessCalculator(
    std::shared_ptr<FitnessCalculator<Phen>> fit_calc) {
  for (auto strat : sorted_strats_) {
    strat.SetFitnessCalculator(fit_calc);
  }
}

template <class Gen, class Phen>
void Population<Gen, Phen>::SetPhenotypeConverter(
    std::shared_ptr<PhenotypeConverter<Gen, Phen>> phen_conv) {
  for (auto strat : sorted_strats_) {
    strat.SetPhenotypeConverter(phen_conv);
  }
}

} // namespace genericga
#endif // _POPULATION_H_

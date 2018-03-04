#ifndef _GENERICGA_SINGLE_POPULATION_GA_H_
#define _GENERICGA_SINGLE_POPULATION_GA_H_

#include <memory>
#include <vector>

#include "genericga/children_factory.h"
#include "genericga/fitness_calculator.h"
#include "genericga/population.h"
#include "genericga/selector/abstract_selector.h"

namespace genericga {

template <class Gen, class Phen>
class SinglePopulationGA {
 public:
  SinglePopulationGA(
      Population<Gen, Phen> init_pop,
      std::unique_ptr<selector::AbstractSelector> survivor_selector,
      std::unique_ptr<ChildrenFactory<Gen>> children_fact);
  void RunRound();
  void RunRound(int n);
  void SetFitnessCalculator(std::unique_ptr<FitnessCalculator<Phen>> fit_calc);

 private:
  Population<Gen, Phen> pop_;
  int n_strategies_;
  int n_children_;

  std::unique_ptr<selector::AbstractSelector> survivor_selector_;
  std::unique_ptr<ChildrenFactory<Gen>> children_fact_;
};

template <class Gen, class Phen>
SinglePopulationGA<Gen, Phen>::SinglePopulationGA(
    Population<Gen, Phen> init_pop,
    std::unique_ptr<selector::AbstractSelector> survivor_selector,
    std::unique_ptr<ChildrenFactory<Gen>> children_fact)
    : pop_(init_pop),
      survivor_selector_(std::move(survivor_selector)),
      children_fact_(std::move(children_fact)) {}

template <class Gen, class Phen>
void SinglePopulationGA<Gen, Phen>::RunRound() {
  auto children = children_fact_.GetChildren(pop_, n_children_);
  pop_.AddStrategies(children);
  pop_ = pop_.SetGenotypes(
      pop_.SelectGenotypes(*survivor_selector_, n_strategies_));
}

template <class Gen, class Phen>
void SinglePopulationGA<Gen, Phen>::RunRound(int n) {
  for (int i = 0; i < n; ++i) {
    RunRound();
  }
}

template <class Gen, class Phen>
void SinglePopulationGA<Gen, Phen>::SetFitnessCalculator(
    std::unique_ptr<FitnessCalculator<Phen>> fit_calc) {
  pop_.SetFitnessCalculator(std::move(fit_calc));
}
}  // namespace genericga

#endif  // _GENERICGA_SINGLE_POPULATION_GA_H_

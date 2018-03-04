#ifndef _GENERICGA_MULTI_POPULATION_GA_H_
#define _GENERICGA_MULTI_POPULATION_GA_H_

#include "genericga/children_factory.h"
#include "genericga/crossover.h"
#include "genericga/fitness_calculator.h"
#include "genericga/mutator.h"
#include "genericga/population.h"
#include "genericga/selector/abstract_selector.h"

namespace genericga {

template <class Gen, class Phen>
class MultiPopulationGA {
 public:
  MultiPopulationGA(
      Population<Gen, Phen> init_pop,
      std::unique_ptr<selector::AbstractSelector<Gen, Phen>> survivor_selector,
      std::unique_ptr<ChildrenFactory<Gen, Phen>> children_fact);
  void RunRound();
  void RunRound(int n);
  void SetPhenotypeConverter(
      std::shared_ptr<PhenotypeConverter<Gen, Phen>> phen_conv);
  void SetFitnessCalculator(std::shared_ptr<FitnessCalculator<Phen>> fit_calc);

 private:
  Population<Gen, Phen> pop_;
  int n_strategies_;
  int n_children_;

  std::shared_ptr<PhenotypeConverter<Gen, Phen>> phen_conv_;
  std::shared_ptr<FitnessCalculator<Phen>> fit_calc_;
  std::unique_ptr<selector::AbstractSelector<Gen, Phen>> survivor_selector_;
  std::unique_ptr<ChildrenFactory<Gen, Phen>> children_fact_;
};

template <class Gen, class Phen>
MultiPopulationGA<Gen, Phen>::MultiPopulationGA(
    Population<Gen, Phen> init_pop,
    std::unique_ptr<selector::AbstractSelector<Gen, Phen>> survivor_selector,
    std::unique_ptr<ChildrenFactory<Gen, Phen>> children_fact)
    : pop_(init_pop),
      survivor_selector_(std::move(survivor_selector)),
      children_fact_(std::move(children_fact)),
      phen_conv_(nullptr),
      fit_calc_(nullptr) {}

template <class Gen, class Phen>
void MultiPopulationGA<Gen, Phen>::RunRound() {
  auto children = children_fact_.GetChildren(pop_, n_children_);
  pop_.AddStrategies(children);
  pop_ = survivor_selector_.SelectPopulation(pop_, n_strategies_);
}

template <class Gen, class Phen>
void MultiPopulationGA<Gen, Phen>::RunRound(int n) {
  for (int i = 0; i < n; ++i) {
    RunRound();
  }
}

template <class Gen, class Phen>
void MultiPopulationGA<Gen, Phen>::SetFitnessCalculator(
    std::shared_ptr<FitnessCalculator<Phen>> fit_calc) {
  fit_calc_ = fit_calc;
  pop_.SetFitnessCalculator(fit_calc.get());
}

template <class Gen, class Phen>
void MultiPopulationGA<Gen, Phen>::SetPhenotypeConverter(
    std::shared_ptr<PhenotypeConverter<Gen, Phen>> phen_conv) {
  phen_conv_ = phen_conv;
  pop_.SetPhenotypeConverter(phen_conv.get());
}
}  // namespace genericga

#endif  // _GENERICGA_MULTI_POPULATION_GA_H_

#ifndef _SINGLE_POPULATION_GA_H_
#define _SINGLE_POPULATION_GA_H_

#include "children_factory.h"
#include "crossover.h"
#include "fitness_calculator.h"
#include "mutator.h"
#include "population.h"
#include "strategy_selector.h"

namespace genericga {

template <class Gen, class Phen> class SinglePopulationGA {
public:
  SinglePopulationGA(
      Population<Gen, Phen> init_pop,
      std::unique_ptr<StrategySelector<Gen, Phen>> survivor_selector,
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
  std::unique_ptr<StrategySelector<Gen, Phen>> survivor_selector_;
  std::unique_ptr<ChildrenFactory<Gen, Phen>> children_fact_;
};

template <class Gen, class Phen>
SinglePopulationGA<Gen, Phen>::SinglePopulationGA(
    Population<Gen, Phen> init_pop,
    std::unique_ptr<StrategySelector<Gen, Phen>> survivor_selector,
    std::unique_ptr<ChildrenFactory<Gen, Phen>> children_fact)
    : pop_(init_pop), survivor_selector_(std::move(survivor_selector)),
      children_fact_(std::move(children_fact)), phen_conv_(nullptr),
      fit_calc_(nullptr) {}

template <class Gen, class Phen>
void SinglePopulationGA<Gen, Phen>::RunRound() {
  auto children = children_fact_.GetChildren(pop_, n_children_);
  pop_.AddStrategies(children);
  pop_ = survivor_selector_.SelectPopulation(pop_, n_strategies_);
}

template <class Gen, class Phen>
void SinglePopulationGA<Gen, Phen>::RunRound(int n) {
  for (int i = 0; i < n; ++i) {
    RunRound();
  }
}

template <class Gen, class Phen>
void SinglePopulationGA<Gen, Phen>::SetFitnessCalculator(
    std::shared_ptr<FitnessCalculator<Phen>> fit_calc) {
  fit_calc_ = fit_calc;
  pop_.SetFitnessCalculator(fit_calc.get());
}

template <class Gen, class Phen>
void SinglePopulationGA<Gen, Phen>::SetPhenotypeConverter(
    std::shared_ptr<PhenotypeConverter<Gen, Phen>> phen_conv) {
  phen_conv_ = phen_conv;
  pop_.SetPhenotypeConverter(phen_conv.get());
}
} // namespace genericga

#endif // _SINGLE_POPULATION_GA_H_

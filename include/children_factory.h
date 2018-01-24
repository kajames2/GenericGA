#ifndef _CHILDREN_FACTORY_H_
#define _CHILDREN_FACTORY_H_

#include "crossover.h"
#include "mutator.h"
#include "population.h"
#include "strategy_selector.h"
#include <memory>

namespace genericga {

template <class Gen, class Phen> class ChildrenFactory {
public:
  ChildrenFactory(std::shared_ptr<Crossover<Gen>> crossover,
                  std::shared_ptr<Mutator<Gen>> mutator,
                  std::shared_ptr<StrategySelector<Gen, Phen>> parent_selector);
  std::vector<GAStrategy<Gen, Phen>> GetChildren(const Population<Gen, Phen> &pop_,
                                    int n_children_);

  void ConductCrossover(std::vector<GAStrategy<Gen, Phen>> *children);
  void ConductMutation(std::vector<GAStrategy<Gen, Phen>> *children);
private:
  std::shared_ptr<Crossover<Gen>> crossover_;
  std::shared_ptr<Mutator<Gen>> mutator_;
  std::shared_ptr<StrategySelector<Gen, Phen>> parent_selector_;
};

template <class Gen, class Phen>
ChildrenFactory<Gen, Phen>::ChildrenFactory(
    std::shared_ptr<Crossover<Gen>> crossover,
    std::shared_ptr<Mutator<Gen>> mutator,
    std::shared_ptr<StrategySelector<Gen, Phen>> parent_selector)
    : crossover_(crossover), mutator_(mutator),
      parent_selector_(parent_selector) {}

template <class Gen, class Phen>
std::vector<GAStrategy<Gen, Phen>>
ChildrenFactory<Gen, Phen>::GetChildren(const Population<Gen, Phen> &pop_,
                                        int n_children_) {
  auto children = parent_selector_.SelectStrategies(pop_, n_children_);
  ConductCrossover(&children);
  ConductMutation(&children);
  return children;
}

template <class Gen, class Phen>
void ChildrenFactory<Gen,Phen>::ConductCrossover(std::vector<GAStrategy<Gen, Phen>> *children) {
  for (int i = 0; i < children->size() - 1; i += 2) {
    Gen gen1 = (*children)[i].GetGenotype();
    Gen gen2 = (*children)[i + 1].GetGenotype();
    crossover_->Cross(&gen1, &gen2);
    (*children)[i].SetGenotype(gen1);
    (*children)[i+1].SetGenotype(gen2);
  }
}

template <class Gen, class Phen>
void ChildrenFactory<Gen,Phen>::ConductMutation(std::vector<GAStrategy<Gen, Phen>> *children) {
  for (auto child : *children) {
    child->SetGenotype(mutator_->Mutate(child->GetGenotype()));
  }
}

} // namespace genericga

#endif // _CHILDREN_FACTORY_H_

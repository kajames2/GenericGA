#ifndef _GENERICGA_CHILDREN_FACTORY_H_
#define _GENERICGA_CHILDREN_FACTORY_H_

#include <memory>
#include <vector>

#include "genericga/crossover.h"
#include "genericga/genotype_population.h"
#include "genericga/mutator.h"
#include "genericga/selector/abstract_selector.h"

namespace genericga {

template <class Gen>
class ChildrenFactory {
 public:
  ChildrenFactory(std::unique_ptr<Crossover<Gen>> crossover,
                  std::unique_ptr<Mutator<Gen>> mutator,
                  std::unique_ptr<selector::AbstractSelector> parent_selector);
  std::vector<Gen> GetChildren(const GenotypePopulation<Gen>& pop_,
                               int n_children_);

  void ConductCrossover(std::vector<Gen>* children);
  void ConductMutation(std::vector<Gen>* children);

 private:
  std::unique_ptr<Crossover<Gen>> crossover_;
  std::unique_ptr<Mutator<Gen>> mutator_;
  std::unique_ptr<selector::AbstractSelector> parent_selector_;
};

template <class Gen>
ChildrenFactory<Gen>::ChildrenFactory(
    std::unique_ptr<Crossover<Gen>> crossover,
    std::unique_ptr<Mutator<Gen>> mutator,
    std::unique_ptr<selector::AbstractSelector> parent_selector)
    : crossover_(std::move(crossover)),
      mutator_(std::move(mutator)),
      parent_selector_(std::move(parent_selector)) {}

template <class Gen>
std::vector<Gen> ChildrenFactory<Gen>::GetChildren(
    const GenotypePopulation<Gen>& pop, int n_children) {
  auto children = pop.SelectGenotypes(*parent_selector_, n_children);
  ConductCrossover(&children);
  ConductMutation(&children);
  return children;
}

template <class Gen>
void ChildrenFactory<Gen>::ConductCrossover(std::vector<Gen>* children) {
  for (int i = 0; i < children->size() - 1; i += 2) {
    crossover_->Cross(&((*children)[i]), &((*children)[i + 1]));
  }
}

template <class Gen>
void ChildrenFactory<Gen>::ConductMutation(std::vector<Gen>* children) {
  for (auto& gen : *children) {
    mutator_->Mutate(&gen);
  }
}

}  // namespace genericga

#endif  // _GENERICGA_CHILDREN_FACTORY_H_

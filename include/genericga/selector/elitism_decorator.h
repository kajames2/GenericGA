#ifndef _GENERICGA_SELECTOR_ELITISM_DECORATOR_H_
#define _GENERICGA_SELECTOR_ELITISM_DECORATOR_H_

#include <memory>
#include <vector>

#include "genericga//selector/keep_best.h"
#include "genericga/fitness_collection.h"
#include "genericga/selector/abstract_selector.h"

namespace genericga {
namespace selector {

class ElitismDecorator : public AbstractSelector {
 public:
  ElitismDecorator(std::unique_ptr<AbstractSelector> sel, int n_elites);

  std::vector<int> SelectIndices(const FitnessCollection& col, int n) override;

 private:
  std::unique_ptr<AbstractSelector> sel_;
  std::unique_ptr<KeepBest> elite_sel_;
  int n_elites_;
};

}  // namespace selectorx
}  // namespace genericga

#endif  // _GENERICGA_SELECTOR_ELITISM_DECORATOR_H_

#ifndef _GENERICGA_SELECTOR_ABSTRACT_SELECTOR_H_
#define _GENERICGA_SELECTOR_ABSTRACT_SELECTOR_H_

#include <vector>

#include "genericga/fitness_collection.h"

namespace genericga {
namespace selector {

class AbstractSelector {
 public:
  virtual std::vector<int> SelectIndices(const FitnessCollection& col,
                                         int n) = 0;
};

}  // namespace selector
}  // namespace genericga

#endif  // _GENERICGA_SELECTOR_ABSTRACT_SELECTOR_H_

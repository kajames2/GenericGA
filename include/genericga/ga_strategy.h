#ifndef _GENERICGA_GA_STRATEGY_H_
#define _GENERICGA_GA_STRATEGY_H_

namespace genericga {

template <class Phen>
struct GAStrategy {
  Phen phenotype;
  double fitness = -1;
};

}  // namespace genericga

#endif  // _GENERICGA_GA_STRATEGY_H_

#ifndef _GENERICGA_CROSSOVER_H_
#define _GENERICGA_CROSSOVER_H_

namespace genericga {

template <class Gen>
class Crossover {
 public:
  virtual void Cross(Gen *genotype1, Gen *genotype2);
};
}  // namespace genericga

#endif  // _GENERICGA_CROSSOVER_H_

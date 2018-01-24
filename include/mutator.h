#ifndef _MUTATOR_H_
#define _MUTATOR_H_

namespace genericga {

template <class Gen> class Mutator {
public:
  virtual void Mutate(Gen *genotype);
};
} // namespace genericga

#endif // _MUTATOR_H_

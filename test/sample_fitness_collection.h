#ifndef _SAMPLE_FITNESS_COLLECTION_H_
#define _SAMPLE_FITNESS_COLLECTION_H_

#include <vector>

#include "genericga/fitness_collection.h"

namespace gatests {

class SampleFitnessCollection : public genericga::FitnessCollection {
 public:
  SampleFitnessCollection() : fits(std::vector<double>{1, 3, 6, -2}) {}
  std::vector<double> GetFitnesses() const override { return fits; }
  double GetFitness(int i) const override { return fits[i]; }

 private:
  std::vector<double> fits;
};

}  // namespace gatests

#endif // _SAMPLE_FITNESS_COLLECTION_H_

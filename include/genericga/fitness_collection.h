#ifndef _GENERICGA_FITNESS_COLLECTION_H_
#define _GENERICGA_FITNESS_COLLECTION_H_

#include <vector>

namespace genericga {
class FitnessCollection {
 public:
  virtual std::vector<double> GetFitnesses() const = 0;
  virtual double GetFitness(int i) const = 0;
  // Ranking fitnesses.  Ties get the average of the ranks at that value.
  // ex. fitnesses of 5,6,5,1,5 have ranks: 2,4,2,0,2 (2 = mean(1,2,3))
  std::vector<double> GetFitnessRankings() const;

  // First element is index of smallest element, next is index of 2nd smallest element, etc.
  // ex. fitnesses of 5,8,1 have orderings: 2,0,1
  std::vector<int> GetFitnessOrderings() const;
  int Size() const;
};

}  // namespace genericga

#endif  // _GENERICGA_FITNESS_COLLECTION_H_

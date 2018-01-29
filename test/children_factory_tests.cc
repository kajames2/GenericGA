#include "ga_strategy.h"
#include "population.h"
#include "sample_fitness_calculator.h"
#include "sample_phenotype_converter.h"
#include "children_factory.h"
#include "sample_crossover.h"
#include "sample_mutation.h"
#include "keep_best_selector.h"

#include <gtest/gtest.h>
#include <map>
#include <memory>

namespace gatests {

class ChildrenFactoryTest : public ::testing::Test {
public:
  ChildrenFactoryTest() {}

protected:
  virtual void SetUp() {
    fit = std::make_shared<SampleFitnessCalculator>(1);
    phen = std::make_shared<SamplePhenotypeConverter>(5);

    auto strats = std::vector<genericga::GAStrategy<int, int>>();
    strats.push_back(
        genericga::GAStrategy<int, int>(-2, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(0, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(3, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(3, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(5, phen.get(), fit.get()));
    pop = genericga::Population<int, int>(strats);

    auto cross = std::make_shared<SampleCrossover>();
    auto mut = std::make_shared<SampleMutation>();
    auto sel = std::make_shared<genericga::KeepBestSelector<int, int>>();
    fact = std::make_unique<genericga::ChildrenFactory<int, int>>(cross, mut, sel);    
  }
  
  std::unique_ptr<genericga::ChildrenFactory<int, int>> fact;
  genericga::Population<int, int> pop;
  std::shared_ptr<SampleFitnessCalculator> fit;
  std::shared_ptr<SamplePhenotypeConverter> phen;
};

TEST_F(ChildrenFactoryTest, InitializedTest) {
  auto children = fact->GetChildren(pop, 2);
  ASSERT_EQ(2, children.size());
  ASSERT_EQ(0, children[0].GetGenotype());
}

} // namespace gatests

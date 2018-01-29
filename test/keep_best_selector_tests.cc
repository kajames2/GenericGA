#include "keep_best_selector.h"
#include "population.h"
#include "sample_fitness_calculator.h"
#include "sample_phenotype_converter.h"

#include <gtest/gtest.h>
#include <map>
#include <memory>

namespace gatests {

class KeepBestSelectorTest : public ::testing::Test {
public:
  KeepBestSelectorTest() {}

protected:
  virtual void SetUp() {
    fit = std::make_shared<SampleFitnessCalculator>(1);
    phen = std::make_shared<SamplePhenotypeConverter>(5);

    auto strats = std::vector<genericga::GAStrategy<int, int>>();
    strats.push_back(
        genericga::GAStrategy<int, int>(-1, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(0, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(2, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(5, phen.get(), fit.get()));
    auto counts = std::vector<int>(4, 1);
    counts[2] = 2;
    pop = genericga::Population<int, int>(strats, counts);

    sel = std::make_shared<genericga::KeepBestSelector<int, int>>();
  }
  genericga::Population<int, int> pop;
  std::shared_ptr<genericga::StrategySelector<int, int>> sel;
  std::shared_ptr<SampleFitnessCalculator> fit;
  std::shared_ptr<SamplePhenotypeConverter> phen;
};

TEST_F(KeepBestSelectorTest, SelectIndexCountsTest) {
  auto map = sel->SelectIndexCounts(pop, 4);
  auto it = map.begin();
  ASSERT_EQ(3, map.size());
  ASSERT_EQ(0, it->first);
  ASSERT_EQ(1, it->second);
  ++it;
  ++it;
  ASSERT_EQ(2, it->first);
  ASSERT_EQ(2, it->second);
}

TEST_F(KeepBestSelectorTest, SelectIndicesTest) {
  auto vec = sel->SelectIndices(pop, 4);
  ASSERT_EQ(4, vec.size());
  ASSERT_EQ(0, vec[0]);
  ASSERT_EQ(2, vec[2]);
  ASSERT_EQ(2, vec[3]);
}

} // namespace gatests

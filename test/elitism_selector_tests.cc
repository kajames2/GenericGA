#include "keep_best_selector.h"
#include "elitism_selector.h"
#include "population.h"
#include "sample_fitness_calculator.h"
#include "sample_phenotype_converter.h"

#include <gtest/gtest.h>
#include <map>
#include <memory>

namespace gatests {

class ElitismSelectorTest : public ::testing::Test {
public:
  ElitismSelectorTest() {}

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

    auto inner_sel = std::make_shared<genericga::KeepBestSelector<int, int>>();
    sel = std::make_shared<genericga::ElitismSelector<int, int>>(inner_sel, 2);
  }
  genericga::Population<int, int> pop;
  std::shared_ptr<genericga::StrategySelector<int, int>> sel;
  std::shared_ptr<SampleFitnessCalculator> fit;
  std::shared_ptr<SamplePhenotypeConverter> phen;
};

TEST_F(ElitismSelectorTest, SelectIndexCountsTest) {
  auto map = sel->SelectIndexCounts(pop, 5);
  auto it = map.begin();
  ASSERT_EQ(3, map.size());
  ASSERT_EQ(0, it->first);
  ASSERT_EQ(2, it->second);
  ++it;
  ++it;
  ASSERT_EQ(2, it->first);
  ASSERT_EQ(1, it->second);
}

TEST_F(ElitismSelectorTest, SelectIndicesTest) {
  auto vec = sel->SelectIndices(pop, 5);
  ASSERT_EQ(5, vec.size());
  std::map<int, int> counts;
  for (int val : vec) {
    if (counts.find(val) == counts.end()) {
      counts.emplace(val, 1);
    } else {
      counts[val] += 1;
    }
  }
  ASSERT_EQ(2, counts[0]);
  ASSERT_EQ(2, counts[1]);
  ASSERT_EQ(1, counts[2]);
}


TEST_F(ElitismSelectorTest, AllElitesTest) {
  auto vec = sel->SelectIndices(pop, 1);
  ASSERT_EQ(1, vec.size());
  ASSERT_EQ(1, vec[0]);
}

} // namespace gatests

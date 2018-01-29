#include "population.h"
#include "ga_strategy.h"
#include "sample_fitness_calculator.h"
#include "sample_phenotype_converter.h"

#include <gtest/gtest.h>
#include <memory>
#include <map>

namespace gatests {

class PopulationTest : public ::testing::Test {
public:
  PopulationTest() {}

protected:
  virtual void SetUp() {
    fit = std::make_shared<SampleFitnessCalculator>(1);
    phen = std::make_shared<SamplePhenotypeConverter>(5);

    strats = std::vector<genericga::GAStrategy<int, int>>();
    strats.push_back(
        genericga::GAStrategy<int, int>(-2, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(0, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(2, phen.get(), fit.get()));
    strats.push_back(genericga::GAStrategy<int, int>(5, phen.get(), fit.get()));
    counts = std::vector<int>(4, 1);
    counts[2] = 2;
    pop = genericga::Population<int, int>(strats, counts);

    extra_strats = std::vector<genericga::GAStrategy<int, int>>();
    extra_strats.push_back(genericga::GAStrategy<int, int>(5, phen.get(), fit.get()));
    extra_strats.push_back(genericga::GAStrategy<int, int>(-2, phen.get(), fit.get()));
    extra_strats.push_back(genericga::GAStrategy<int, int>(5, phen.get(), fit.get()));
    extra_strats.push_back(genericga::GAStrategy<int, int>(1, phen.get(), fit.get()));

    extra_counts = std::vector<int>();
    extra_counts.push_back(1);
    extra_counts.push_back(1);
    extra_counts.push_back(1);
    extra_counts.push_back(3);

    sel_map.emplace(0, 2);
    sel_map.emplace(2, 1);
  }
  std::vector<genericga::GAStrategy<int, int>> strats, extra_strats;
  std::vector<int> counts, extra_counts;
  genericga::Population<int, int> pop;
  std::shared_ptr<SampleFitnessCalculator> fit;
  std::shared_ptr<SamplePhenotypeConverter> phen;
  std::map<int, int> sel_map;
};

TEST_F(PopulationTest, InitializedTest) { ASSERT_EQ(5, pop.GetNStrategies()); }

TEST_F(PopulationTest, GetPopulationTest) {
  auto sel_pop = pop.GetPopulation(sel_map);
  ASSERT_EQ(-2, sel_pop[0].GetGenotype());
  ASSERT_EQ(3, sel_pop.GetNStrategies());
}

TEST_F(PopulationTest, GetStrategiesTest) {
  auto ind_vec = std::vector<int>{3,0,0,2,1};
  auto sel_vec = pop.GetStrategies(ind_vec);
  ASSERT_EQ(5, sel_vec[0].GetGenotype());
  ASSERT_EQ(0, sel_vec[4].GetGenotype());
}

TEST_F(PopulationTest, AccessorTest) { ASSERT_EQ(-2, pop[0].GetGenotype()); }

TEST_F(PopulationTest, GetUniqueFitnessesTest) {
  auto fitnesses = pop.GetUniqueFitnesses();
  ASSERT_DOUBLE_EQ(2.0, fitnesses[0]);
  ASSERT_DOUBLE_EQ(-19.0, fitnesses[3]);
}

TEST_F(PopulationTest, AddStrategiesTest) {
  pop.AddStrategies(extra_strats, extra_counts);
  ASSERT_EQ(11, pop.GetNStrategies());
  ASSERT_EQ(1, pop[2].GetGenotype());
  ASSERT_EQ(-2, pop[0].GetGenotype());
  ASSERT_EQ(2, pop.GetFrequencies()[0]);
}

TEST_F(PopulationTest, GetFitnessRankingsTest) {
  auto ranks = pop.GetFitnessRankings();
  ASSERT_EQ(3, ranks[1]);
  ASSERT_EQ(0, ranks[3]);
}

} // namespace gatests

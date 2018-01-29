#include "tournament_selector.h"
#include "population.h"
#include "sample_fitness_calculator.h"
#include "sample_phenotype_converter.h"

#include <gtest/gtest.h>
#include <map>
#include <memory>

namespace gatests {

class TournamentSelectorTest : public ::testing::Test {
public:
  TournamentSelectorTest() {}

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

    sel = std::make_shared<genericga::TournamentSelector<int, int>>(3);
  }
  genericga::Population<int, int> pop;
  std::shared_ptr<genericga::TournamentSelector<int, int>> sel;
  std::shared_ptr<SampleFitnessCalculator> fit;
  std::shared_ptr<SamplePhenotypeConverter> phen;
};

TEST_F(TournamentSelectorTest, TournamentRoundTest) {
  ASSERT_EQ(0, sel->TournamentRound(pop.GetUniqueFitnesses(), std::vector<int>{0,2,2}));
  ASSERT_EQ(1, sel->TournamentRound(pop.GetUniqueFitnesses(), std::vector<int>{0,2,1,2}));
}

} // namespace gatests

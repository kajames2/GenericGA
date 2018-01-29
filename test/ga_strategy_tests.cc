#include "ga_strategy.h"
#include "sample_fitness_calculator.h"
#include "sample_phenotype_converter.h"

#include <gtest/gtest.h>
#include <memory>

namespace gatests {

class GAStrategyTest : public ::testing::Test {
public:
  GAStrategyTest() {}

protected:
  virtual void SetUp() {
    fit = std::make_shared<SampleFitnessCalculator>(1);
    phen = std::make_shared<SamplePhenotypeConverter>(5);
    strat = std::make_shared<genericga::GAStrategy<int, int>>(5, phen.get(),
                                                              fit.get());
    strat2 = std::make_shared<genericga::GAStrategy<int, int>>(0, phen.get(),
                                                               fit.get());
    strat3 = std::make_shared<genericga::GAStrategy<int, int>>(0, phen.get(),
                                                               fit.get());
  }
  std::shared_ptr<genericga::GAStrategy<int, int>> strat, strat2, strat3;
  std::shared_ptr<SampleFitnessCalculator> fit;
  std::shared_ptr<SamplePhenotypeConverter> phen;
};

TEST_F(GAStrategyTest, GetGenotypeTest) { ASSERT_EQ(0, strat3->GetGenotype()); }

TEST_F(GAStrategyTest, GetPhenotypeTest) {
  ASSERT_EQ(5, strat3->GetPhenotype());
}

TEST_F(GAStrategyTest, GetFitnessTest) {
  ASSERT_DOUBLE_EQ(6, strat3->GetFitness());
}

TEST_F(GAStrategyTest, UpdateGenotypeTest) {
  strat3->SetGenotype(3);
  ASSERT_EQ(3, strat3->GetGenotype());
  ASSERT_EQ(-4, strat3->GetPhenotype());
  ASSERT_EQ(-3, strat3->GetFitness());
}

TEST_F(GAStrategyTest, UpdatePhenotypeTest) {
  auto new_phen = std::make_shared<SamplePhenotypeConverter>(2);
  strat3->SetPhenotypeConverter(new_phen.get());
  ASSERT_EQ(0, strat3->GetGenotype());
  ASSERT_EQ(2, strat3->GetPhenotype());
  ASSERT_EQ(3, strat3->GetFitness());
}

TEST_F(GAStrategyTest, UpdateFitnessTest) {
  auto new_fit = std::make_shared<SampleFitnessCalculator>(2);
  strat3->SetFitnessCalculator(new_fit.get());
  ASSERT_EQ(0, strat3->GetGenotype());
  ASSERT_EQ(5, strat3->GetPhenotype());
  ASSERT_EQ(7, strat3->GetFitness());
}

TEST_F(GAStrategyTest, ComparatorTest) {
  auto new_fit = std::make_shared<SampleFitnessCalculator>(-1);
  strat2->SetFitnessCalculator(new_fit.get());
  auto new_conv = std::make_shared<SamplePhenotypeConverter>(2);
  strat3->SetPhenotypeConverter(new_conv.get());

  ASSERT_TRUE(*strat > *strat3);
  ASSERT_TRUE(*strat2 >= *strat3);
  ASSERT_FALSE(*strat < *strat3);
  ASSERT_TRUE(*strat2 <= *strat3);
  ASSERT_TRUE(*strat2 == *strat3);
  ASSERT_TRUE(*strat != *strat3);
}

} // namespace gatests

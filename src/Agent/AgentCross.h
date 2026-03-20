

#ifndef _AgentCross_hpp_
#define _AgentCross_hpp_

#include <vector>
#include "Agent.h"
#include "../RandomGenerator/RandomGenerator.h"
#include "../VariableContainer/Price.h"
#include "../VariableContainer/GlobalNews.h"
#include "../VariableContainer/ExcessDemand.h"

#if BUILD_TESTS
#include "gtest/gtest_prod.h"
#endif

/** Agent as defined in "Rod Cross, Michael Grinfeld, Harbir Lamba, Tim Seaman.
 * A Threshold Model of Investor Psychology, 2005"
 */
class AgentCross : public Agent {
#if BUILD_TESTS
FRIEND_TEST(AgentCrossTest, constructor);
FRIEND_TEST(AgentCrossTest, preStepUpdate);
FRIEND_TEST(AgentCrossTest, stepUpdate);
FRIEND_TEST(AgentCrossTest, postStepUpdate);
FRIEND_TEST(AgentCrossTest, updateBisection);
FRIEND_TEST(fullSimulationTest, fullSimulation_Cross);
#endif
protected:
    /// lower bound of the inaction interval (see p.4).
	double inactionLowerBound;
    /// uppwer bound of the inaction interval (see p.4).
	double inactionUpperBound;
    /// Corresponds to c_i (for agent i) in the paper.
	double herdingPressure;

    /// Corresponds to H_i (for agent i) in the paper.
	double inactionThreshold;
    /// Corresponds to C_i (for agent i) in the paper.
	double herdingThreshold;

	ExcessDemand* excessDemand; /**< Pointer to the ExcessDemand container */

public:
	AgentCross();
	AgentCross(RandomGenerator* newRandomGenerator, Price* newPrice, ExcessDemand* newExcessDemand);
	AgentCross(RandomGenerator* newRandomGenerator, Price* newPrice, ExcessDemand* newExcessDemand,
			double newCash, double newStock);
	AgentCross(RandomGenerator* newRandomGenerator, Price* newPrice, ExcessDemand* newExcessDemand,
			   double newCash, double newStock, DeltaT* deltaT, double b1, double b2, double A1, double A2);

    /// Draws initial thresholds and herdingPressure from respective uniform distributions (cf. eq. 3.1, p.8),
    /// assigns a random initial decision.


    /// Check whether the agent must change position because price or herdingPressure are out of bounds
    ///  and perform the position change, if necessary (cf p.6)
	virtual void preStepUpdate();

	virtual void stepUpdate();

	virtual void postStepUpdate();
    /// Assume a new price has been calculated and check whether the agent must change position.
    /// Perform the position change, if necessary. In contrast to updateAgent, herdingPressure is not set to zero.
    /// @todo rename this to updatePrice?
	virtual void updateBisection(const double& newIterPrice);

    /// Calculate the inaction bounds for the given price (see p.4).
    void updateBounds(double price);
};

#endif

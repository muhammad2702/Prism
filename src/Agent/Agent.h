

#ifndef _Agent_hpp_
#define _Agent_hpp_

#include "../RandomGenerator/RandomGenerator.h"
#include "../Switching/Switchable.h"
#include "../VariableContainer/Price.h"
#include "../VariableContainer/DeltaT.h"
#include "../Input/Input.h"
#include "../Group/Group.h"
#include "../VariableContainer/ExcessDemand.h"
#include "../VariableContainer/GlobalNews.h"
#include "../VariableContainer/Dividend.h"

#include <vector>


/** Virtual parent class for all Agent.
 *
 */
class Agent: public Group {

protected:
	double cash; /**< Current cash (Bargeld) of the agent */
	double stock; /**< Current amount of stock of the agent */
	int decision; /**< Last decision of the agent. Depending on implementation of subclass! Often: +1 -> Buying, -1 -> Selling, 0 -> Passive */
	double tradingVolume; /**< Amount of stock to sell/buy at the current timestep. Selling/Buying depends on decision.*/

	RandomGenerator* randomGenerator; /**< Pointer to the random number generator */
	Price* price; /**< Pointer to the Price container */
	DeltaT* deltaT; /**< Pointer to the DeltaT container */

public:
	Agent();
	Agent(RandomGenerator* newRandomGenerator, Price* newPrice);
	Agent(RandomGenerator* newRandomGenerator, Price* newPrice, double newCash, double newStock);
    ///
    /// \brief factory
    /// \param input
    /// \param randomNumberPool
    /// \param price
    /// \param excessDemand
    /// \param globalNews
    /// \param dividend
    /// \param deltaT
    /// \param switchableGroups[out] groups of agents that may switch between strategies, if any.
    /// \return
    ///
    static std::vector<Agent*>* factory(Input& input, RandomGenerator* randomNumberPool, Price* price,
                                        ExcessDemand* excessDemand, GlobalNews* globalNews, Dividend* dividend,
                                        DeltaT* deltaT, std::vector<Switchable *> &switchableGroups);
	virtual ~Agent();

    double getCash() const;
    void setCash(double newCash);
    int getDecision() const;
	void setRandomGenerator(RandomGenerator* newRandomGenerator);
	void setPrice(Price* newPrice);
    double getStock() const;
    void setStock(double newStock);
    double getTradingVolume() const;
	void setDeltaT(DeltaT* newDeltaT);

	virtual void preStepUpdate() = 0;
	virtual void stepUpdate() = 0;
	virtual void postStepUpdate() = 0;

	virtual void updateBisection(const double& newIterPrice) = 0;

};



#endif

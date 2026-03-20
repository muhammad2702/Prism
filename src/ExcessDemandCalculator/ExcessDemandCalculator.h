
#ifndef _ExcessDemandCalculator_hpp_
#define _ExcessDemandCalculator_hpp_

#include <vector>

#include "../Input/Input.h"
#include "../Agent/Agent.h"
#include "../VariableContainer/ExcessDemand.h"
#include "../VariableContainer/Dividend.h"


/** Virtual parent class for all ExcessDemandCalculator.
 * This class defines the public interface for all ExcessDemandCalculators.
 */
class ExcessDemandCalculator {
protected:
	std::vector<Agent*>* agents; /**< Pointer to the vector full of agents. */
	ExcessDemand* excessDemand; /**< Pointer to the ExcessDemand container  */

public:
	ExcessDemandCalculator();
	ExcessDemandCalculator(std::vector<Agent*>* newAgents, ExcessDemand* newExcessDemand);

	static ExcessDemandCalculator* factory(Input& input, std::vector<Agent*>* agents,
										   ExcessDemand* excessDemand, Price* price, Dividend* dividend);

	virtual ~ExcessDemandCalculator();

	virtual void preStepCalculate() = 0;
	virtual void stepCalculate() = 0;
	virtual void postStepCalculate() = 0;

	void setAgents(std::vector<Agent*>* newAgents);
};



#endif



#include "ExcessDemandCalculator.h"
#include "ExcessDemandCalculatorHarras.h"
#include "ExcessDemandCalculatorLLS.h"
#include "../VariableContainer/Dividend.h"
#include "ExcessDemandCalculatorFW.h"
#include "../Input/Input.h"


/** Standardconstructor
 */
ExcessDemandCalculator::ExcessDemandCalculator(): ExcessDemandCalculator(nullptr, nullptr){


}


/** Constructor for pure-virtual ExcessDemandCalculator.
 * Requires a pointer to a vector of agents and the ExcessDemandContainer.
 * \param newAgents Pointer to a vector of agents
 * \param newExcessDemand Pointer to the ExcessDemand container
 */
ExcessDemandCalculator::ExcessDemandCalculator(std::vector<Agent*>* newAgents, ExcessDemand* newExcessDemand){

	agents = newAgents;
	excessDemand = newExcessDemand;

}

ExcessDemandCalculator* ExcessDemandCalculator::factory(Input& input, std::vector<Agent*>* agents,
														ExcessDemand* excessDemand, Price* price, Dividend* dividend){

    Input& EDCinput = input["excessDemandCalculatorSettings"];

	ExcessDemandCalculator* excessDemandCalculator;
    if (EDCinput["excessDemandCalculatorClass"].getString() == "excessdemandcalculatorharras") {
		excessDemandCalculator = new ExcessDemandCalculatorHarras(agents,excessDemand);
	}
    else if (EDCinput["excessDemandCalculatorClass"].getString() == "excessdemandcalculatorlls") {
        double stocksPerAgent = 0;
        size_t agentCount = agents->size();
        for (auto &agent : *agents) {
            stocksPerAgent += agent->getStock();
        }
        stocksPerAgent /= double(agentCount);

        excessDemandCalculator = new ExcessDemandCalculatorLLS(agents, excessDemand, price, dividend,
                                                               EDCinput["excessDemandCalculatorClass"]("mode") ? EDCinput["excessDemandCalculatorClass"]["mode"].getString():"original",
                                                               stocksPerAgent);
	}
    else if (EDCinput["excessDemandCalculatorClass"].getString() == "excessdemandcalculatorfw"){
		excessDemandCalculator = new ExcessDemandCalculatorFW(agents, excessDemand);
	}

	else {
		throw("excessDemandCalculatorClass unknown!");
	}
	return excessDemandCalculator;
}

/** Destructor of the ExcessDemandCalculator
 */
ExcessDemandCalculator::~ExcessDemandCalculator() = default;


/** Setter method for the agents.
 */
void ExcessDemandCalculator::setAgents(std::vector<Agent*>* newAgents) {

	agents = newAgents;

}


#ifndef _PriceCalculator_hpp_
#define _PriceCalculator_hpp_

#include "../Input/Input.h"
#include "../ExcessDemandCalculator/ExcessDemandCalculator.h"
#include "../VariableContainer/Price.h"
#include "../VariableContainer/ExcessDemand.h"
#include "../VariableContainer/DeltaT.h"
#include "../RandomGenerator/RandomGenerator.h"

// forward declaration
class StockExchange;



/** Virtual parent class for all PriceCalculator.
 * This class defines the public interface for all PriceCalculators. It relies on the ExcessDemandCalculator
 * to calculate a new price.
 * Can only be constructed if an ExcessDemandCalculator is provided.
 */
class PriceCalculator {
    friend StockExchange;

protected:
	ExcessDemandCalculator* excessDemandCalculator;	/**< Pointer to an ExcessDemandCalculator object. */
	Price* price;	/**< Holds the last calculated price for later reference. */
	ExcessDemand* excessDemand; /**< Pointer to the ExcessDemand container */
    DeltaT* deltaT;
	double marketDepth; /**< Lambda from the Harras model and Kappa in the Cross model */


public:
	PriceCalculator();
	PriceCalculator(ExcessDemandCalculator* newExcessDemandCalculator, Price* newPrice, ExcessDemand* newExcessDemand);
    static PriceCalculator* factory(Input& input, ExcessDemandCalculator* excessDemandCalculator,
                                    Price* price, ExcessDemand* excessDemand, DeltaT* deltaT,
                                    RandomGenerator* randomNumberPool, std::vector<Agent*>* agents);
	virtual ~PriceCalculator();

	void setDeltaT(DeltaT* newDeltaT);
	void setMarketDepth(double newMarketDepth);
	void setExcessDemandCalculator(ExcessDemandCalculator* newExcessDemandCalculator);

	virtual void preStepCalculate() = 0;
	virtual void stepCalculate() = 0;
	virtual void postStepCalculate() = 0;
};



#endif

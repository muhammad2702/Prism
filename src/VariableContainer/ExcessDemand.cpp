

#include "ExcessDemand.h"






/** Constructor for the ExcessDemand. Default: Initiliaze excess demand to 0.
 */
ExcessDemand::ExcessDemand(double newExcessDemand) {
	excessDemand = newExcessDemand;
	term1LLS = 0;
	term2LLS = 0;
}


/** Destructor
 */
ExcessDemand::~ExcessDemand() {
	// TODO Auto-generated destructor stub
}


/** Setter method for the excessDemand. Is private and only callable by befriended implementations
 * of the ExcessDemandCalculator.
 * \param newExcessDemand Reference to the new excess demand
 */
void ExcessDemand::setExcessDemand(double newExcessDemand){
	excessDemand = newExcessDemand;
}


/** Getter method for the excessDemand.
 * \return Returns the excessDemand.
 */
const double& ExcessDemand::getExcessDemand() const{
	return excessDemand;
}

void ExcessDemand::setLLSinfo(double term1, double term2){
	term1LLS = term1;
	term2LLS = term2;
}

void ExcessDemand::getLLSinfo(double& term1, double& term2){
	term1 = term1LLS;
	term2 = term2LLS;
}

#include "DeltaT.h"





/** Constructor for the DeltaT container that is initialized to 1.
 */
DeltaT::DeltaT() {
	deltaT = 1;
}

DeltaT::DeltaT(double newDeltaT) {
	deltaT = newDeltaT;
}


/** Destructor
 */
DeltaT::~DeltaT() {
	// TODO Auto-generated destructor stub
}


/** Setter method for the DeltaT. Is private and only callable by befriended implementations of the DeltaTCalculator.
 * \param newDeltaT The new DeltaT
 */
void DeltaT::setDeltaT(double deltaT){
    this->deltaT = deltaT;
}


/** Getter method for the current DeltaT.
 * \return const reference to the current DeltaT
 */
const double& DeltaT::getDeltaT() const{
	return deltaT;
}

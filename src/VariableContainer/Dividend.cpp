
#include "Dividend.h"
#include <cassert>


/** Constructor for the Dividend container that is initialized to 1.
 */
Dividend::Dividend():Dividend(nullptr,nullptr){

}

Dividend::Dividend(RandomGenerator* newRandomGenerator, DeltaT* newDeltaT):
		Dividend(newRandomGenerator, newDeltaT,
				 0, 1, 0)
{

}

Dividend::Dividend(RandomGenerator* newRandomGenerator, DeltaT* newDeltaT,
				   double newZ1, double newZ2, double newInitialDividend):
		randomGenerator(newRandomGenerator),
        deltaT(newDeltaT),
		dividend(newInitialDividend)
{
	setZ(newZ1, newZ2);
}


/** Destructor
 */
Dividend::~Dividend() {
	// TODO Auto-generated destructor stub
}


/// Setter method for the Dividend. Is private and only callable by befriended implementations
/// of the DividendCalculator.
void Dividend::calculateDividend(){
	assert(randomGenerator != nullptr);
	assert(deltaT != nullptr);

	double eta = 0;
	randomGenerator->getUniformRandomDouble(z1,z2,&eta); /// @todo According to Torsten:
/// Truncated random variable? Which distribution?

	dividend = (1 + deltaT->getDeltaT() * eta) * dividend;
}


/** Getter method for the current Dividend.
 * \return const reference to the current Dividend
 */
const double& Dividend::getDividend() const{
	return dividend;
}

/** Sets the bounds of the uniform distribution and calculates the expected value.
 *
 */
void Dividend::setZ(double newZ1, double newZ2){
	assert(newZ2>=newZ1);
	z1 = newZ1;
	z2 = newZ2;
    expectedIncrease = (z1+z2)/2;
}

const double& Dividend::getExpectedIncrease() const{
    return expectedIncrease;
}

const double& Dividend::getZ1() const{
	return z1;
}
const double& Dividend::getZ2() const{
	return z2;
}

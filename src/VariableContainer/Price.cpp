

#include "Price.h"
#include <cmath>


/// Constructor for the Price container that is intialized to 1.
Price::Price(bool take_exponential): take_exponential(take_exponential) {
	price = 1;
}

/// Constructor for the Price container that is intialized to 1.
Price::Price(): Price(false) {
}


/** Destructor
 */
Price::~Price() {
	// TODO Auto-generated destructor stub
}


/** Setter method for the price. Is private and only callable by befriended implementations of the PriceCalculator.
 * \param price The new price
 */
void Price::setPrice(double price){
    this->price = price;
}


/** Getter method for the current price.
 * \return const reference to the current price
 */
const double& Price::getPrice() const{
	return price;
}

/** Getter method for the current price.
 * \return const reference to the current price
 */
double Price::getPrice_tracking(){
	if(take_exponential){
		return exp(price);
	}
	return price;
}
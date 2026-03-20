

#include "PriceCalculatorLLS.h"

PriceCalculatorLLS::PriceCalculatorLLS() = default;

PriceCalculatorLLS::PriceCalculatorLLS(ExcessDemandCalculator* newExcessDemandCalculator, Price* newPrice,
                                       ExcessDemand* newExcessDemand, bool adaptive, double low, double high, double epsilon, size_t maxIterations):
        PriceCalculatorBisection(newExcessDemandCalculator, newPrice, newExcessDemand, adaptive, low, high, epsilon, maxIterations){

}
PriceCalculatorLLS::~PriceCalculatorLLS() = default;


void PriceCalculatorLLS::postStepCalculate(){

    double term1 = 0;
    double term2 = 0;

    excessDemand->getLLSinfo(term1, term2);

    double newPriceAfterNoise = 1/(1-term1)*term2;
    /// @todo ugly hack!
    price->setPrice(newPriceAfterNoise);
}

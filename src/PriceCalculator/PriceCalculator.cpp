
#include "PriceCalculator.h"
#include "PriceCalculatorBisection.h"
#include "PriceCalculatorCross.h"
#include "PriceCalculatorGeneral.h"
#include "PriceCalculatorHarras.h"
#include "PriceCalculatorLLS.h"
#include "PriceCalculatorLLSNoise.h"
#include "PriceCalculatorLLS1.h"
#include "PriceCalculatorHarrasNoise.h"
#include "PriceCalculatorFW.h"
#include "../Input/Input.h"

#include "../VariableContainer/Price.h"
#include "../VariableContainer/DeltaT.h"
#include "../VariableContainer/ExcessDemand.h"
#include "../RandomGenerator/RandomGenerator.h"
#include <string>



/** Standardconstructor for the PriceCalculator.
 */
PriceCalculator::PriceCalculator(): PriceCalculator(nullptr, nullptr, nullptr){
}


/** Constructor for the pure-virtual PriceCalculator.
 * Requires an ExcessDemandCalculator for the object to work properly.
 * \param newExcessDemandCalculator Pointer to an ExcessDemandCalculator object
 * \param newPrice Pointer to the Price container
 * \param newExcessDemand Pointer to the ExcessDemand container
 */
PriceCalculator::PriceCalculator(ExcessDemandCalculator* newExcessDemandCalculator, Price* newPrice,
								 ExcessDemand* newExcessDemand) {
	excessDemandCalculator = newExcessDemandCalculator;
	price = newPrice;
	excessDemand = newExcessDemand;
	deltaT = nullptr;
	marketDepth = 0.25;
}

PriceCalculator* PriceCalculator::factory(Input& input, ExcessDemandCalculator* excessDemandCalculator,
										  Price* price, ExcessDemand* excessDemand, DeltaT* deltaT,
                                          RandomGenerator* randomNumberPool, std::vector<Agent*>* agents){
	//priceCalculator
	Input& PCinput = input["priceCalculatorSettings"];
	std::string type = PCinput["priceCalculatorClass"].getString();

	PriceCalculator* priceCalculator;

	if (type == "pricecalculatorharras") {
		priceCalculator = new PriceCalculatorHarras(excessDemandCalculator,price, excessDemand);
		priceCalculator->setMarketDepth(PCinput["marketDepth"].getDouble());
	}
	else if (type == "pricecalculatorharrasadd") {
		priceCalculator = new PriceCalculatorHarrasNoise(excessDemandCalculator,price, excessDemand,
														 PriceCalculatorHarrasNoise::ADD,
														 PCinput["noiseFactor"].getDouble(),
														 0, randomNumberPool);
		priceCalculator->setMarketDepth(PCinput["marketDepth"].getDouble());
	}
	else if (type == "pricecalculatorharrasmult") { //TODO: 0 ist theta!!
		priceCalculator = new PriceCalculatorHarrasNoise(excessDemandCalculator,price, excessDemand,
														 PriceCalculatorHarrasNoise::MULT,
														 PCinput["noiseFactor"].getDouble(),
														 PCinput["theta"].getDouble(), randomNumberPool);
		priceCalculator->setMarketDepth(PCinput["marketDepth"].getDouble());
	}
		//priceCalculator General
	else if (type == "pricecalculatorgeneral") {
		auto * calculator = new PriceCalculatorGeneral(
				excessDemandCalculator, randomNumberPool, price, excessDemand);
		calculator->setFFunction(PCinput["ffunction"].getString());
		/// @todo calculator should do this check
		if (PCinput("fconstant")){
			calculator->setFConstant(PCinput["fconstant"].getDouble());
		}

		calculator->setGFunction(PCinput["gfunction"].getString());
		if (PCinput("gconstant")){
			calculator->setFConstant(PCinput["gconstant"].getDouble());
		}

		priceCalculator = calculator;
		priceCalculator->setMarketDepth(PCinput["marketDepth"].getDouble());

	}
		//priceCalculator Bisection
    else if (type== "pricecalculatorbisection" || type == "pricecalculatorlls" || type == "pricecalculatorllsnoise") {
        double low;
        double high;

		bool adaptive = false;
        if (PCinput("adaptive")){
        	adaptive = PCinput["adaptive"].getBool();
        }

        if(adaptive)
        {
            low = PCinput["deviationLow"].getDouble();
            high = PCinput["deviationHigh"].getDouble();
        }
        else
        {
            low = PCinput["lowerBound"].getDouble();
            high = PCinput["upperBound"].getDouble();
        }

        if(type == "pricecalculatorbisection")
            priceCalculator = new PriceCalculatorBisection(excessDemandCalculator,price, excessDemand,
                                                       adaptive,
                                                       low,high,
													   PCinput["epsilon"].getDouble(),
														PCinput["maxIterations"].getSizeT());
                                                       
        else if(type == "pricecalculatorlls")
            priceCalculator = new PriceCalculatorLLS(excessDemandCalculator,price, excessDemand,
                                                       adaptive,
                                                       low,high,
													   PCinput["epsilon"].getDouble(),
														PCinput["maxIterations"].getSizeT());
        else if(type == "pricecalculatorllsnoise")
            priceCalculator = new PriceCalculatorLLSNoise(excessDemandCalculator,price, excessDemand,
                                                     adaptive,
                                                     low,high,
                                                     PCinput["epsilon"].getDouble(),
														PCinput["maxIterations"].getSizeT(),
                                                     PCinput["mean"].getDouble(),
														PCinput["sigma"].getDouble(),
                                                     *randomNumberPool);
		else
			throw("priceCalculatorClass unknown!");



        (dynamic_cast<PriceCalculatorBisection*>(priceCalculator))->setAgents(agents);
	}
		//priceCalculator Cross
	else if (type == "pricecalculatorcross") {
		priceCalculator = new PriceCalculatorCross(excessDemandCalculator,price, excessDemand, randomNumberPool,
												   PriceCalculatorCross::ORIGINAL);
		(dynamic_cast<PriceCalculatorCross*>(priceCalculator))->setTheta(PCinput["theta"].getDouble());
		priceCalculator->setMarketDepth(PCinput["marketDepth"].getDouble());
	}
	else if (type == "pricecalculatorcrossmartingale" ){
		priceCalculator = new PriceCalculatorCross(excessDemandCalculator,price, excessDemand, randomNumberPool,
												   PriceCalculatorCross::MARTINGALE);
		(dynamic_cast<PriceCalculatorCross*>(priceCalculator))->setTheta(PCinput["theta"].getDouble());
		priceCalculator->setMarketDepth(PCinput["marketDepth"].getDouble());
	}
	else if (type == "pricecalculatorfw"){
		priceCalculator = new PriceCalculatorFW(excessDemandCalculator, price,
                                                excessDemand, PCinput["mu"].getDouble(),
												dynamic_cast<AgentFW*>(agents->at(0))->getSwitchingStrategy()
                                                );
	}
    else if (type == "pricecalculatorlls1"){
        priceCalculator = new PriceCalculatorLLS1(price, deltaT, PCinput["marketDepth"].getDouble(),
                                                  excessDemand, excessDemandCalculator,
                                                  randomNumberPool,
												  PCinput["mean"].getDouble(),
												  PCinput["sigma"].getDouble(),
                                                  agents);
    }
	else {
		throw("priceCalculatorClass unknown!");
	}

	priceCalculator->setDeltaT(deltaT);
	return priceCalculator;
}

/** Virtual destructor of the PriceCalculator.
 */
PriceCalculator::~PriceCalculator() = default;


/** Setter method for private excessDemandCalculator
 * \param newExcessDemandCalculator Pointer to an ExcessDemandCalculator object
 */
void PriceCalculator::setExcessDemandCalculator(ExcessDemandCalculator* newExcessDemandCalculator) {
	excessDemandCalculator = newExcessDemandCalculator;
}

void PriceCalculator::setDeltaT(DeltaT* newDeltaT){
	deltaT = newDeltaT;
}

void PriceCalculator::setMarketDepth(double newMarketDepth){
	marketDepth = newMarketDepth;
}

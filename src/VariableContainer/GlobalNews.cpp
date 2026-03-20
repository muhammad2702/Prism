

#include <cassert>

#include "GlobalNews.h"


/** Standardconstructor
 */
GlobalNews::GlobalNews(): GlobalNews(nullptr) {


}


/** Constructor
 * \param newRandomGenerator Pointer to a RandomGenerator
 */
GlobalNews::GlobalNews(RandomGenerator* newRandomGenerator):
randomGenerator(newRandomGenerator)
{

	assert(randomGenerator != nullptr);
	randomGenerator->getNormalRandomDouble(0,1,&curGlobalNews);
	randomGenerator->getNormalRandomDouble(0,1,&prevGlobalNews);


}


/** Destructor
 */
GlobalNews::~GlobalNews() = default;


/** Getter method for the current global information
 * \return Current global information
 */
const double& GlobalNews::getCurGlobalNews() const{


	return curGlobalNews;
}


/** Getter method for the previous global information
 * \return Previous global information
 */
const double& GlobalNews::getPrevGlobalNews() const{


	return prevGlobalNews;
}


/** Generate new global information.
 */
void GlobalNews::generateNewGlobalNews(){


	assert(randomGenerator != nullptr);
	prevGlobalNews = curGlobalNews;
	randomGenerator->getNormalRandomDouble(0,1,&curGlobalNews);


}


#ifndef DATACOLLECTORCOMPOSITE_H_
#define DATACOLLECTORCOMPOSITE_H_

#include <vector>
#if BUILD_TESTS
#include "gtest/gtest_prod.h"
#endif

#include "DataItemCollector.h"
#include "../Input/Input.h"
#include "../VariableContainer/Price.h"
#include "../VariableContainer/ExcessDemand.h"
#include "../Agent/Agent.h"


class DataCollectorTest;

/** Composite of DataCollectors.
 * Administers the implementations of the DataCollectorBase class. They can be added at runtime to specify which data has
 * to be collected.
 */
class DataCollector{
#if BUILD_TESTS
    friend class DataCollectorTest;
    FRIEND_TEST(DataCollectorTest, deleteDataItemCollectors);
    FRIEND_TEST(DataCollectorTest, add);
#endif
private:
	std::vector<DataItemCollector*> components; /** Pointers to all activated DataCollectors */

public:
	static DataCollector* factory(Input& input, Price* price, ExcessDemand* excessDemand,
                                  std::vector<Agent*>* agents, std::vector<Switchable *> &switchableGroups);
	DataCollector();
	~DataCollector();

	void checkInitilisation();

	void collect();
	void clearData();

	void add(DataItemCollector* newDataCollector);
	void deleteDataItemCollectors();

};

#endif /* DATACOLLECTORCOMPOSITE_H_ */

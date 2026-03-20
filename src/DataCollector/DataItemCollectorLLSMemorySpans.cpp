
#include <cstddef> //for std::size_t
#include "DataItemCollectorLLSMemorySpans.h"

using namespace std;

DataItemCollectorLLSMemorySpans::DataItemCollectorLLSMemorySpans(vector<Agent*>* newAgents)
    : collected(false){
    /// @todo error handling for the cast
    agents = (vector<AgentLLS*>*)newAgents;

        std::vector<double> temp;
        dataMatrix.push_back(temp);
}


DataItemCollectorLLSMemorySpans::DataItemCollectorLLSMemorySpans(): DataItemCollectorLLSMemorySpans(nullptr){ }




/** Check if everything is initialized and ready to run.
 */
void DataItemCollectorLLSMemorySpans::checkInitilisation(){
    assert(agents!=nullptr);
}


void DataItemCollectorLLSMemorySpans::collectData(){
    if(collected)
        return;

    collected = true;

    assert(agents != nullptr);

    for (auto &agent : *agents) {
        if(agent->hasGroup(groupToTrack_))
            dataMatrix.at(0).push_back(double(agent->getMemorySpan()));
    }
}

void DataItemCollectorLLSMemorySpans::setAgents(std::vector<Agent*>* newAgents){
    agents = (vector<AgentLLS*>*)newAgents;
}

vector<vector<double>> * DataItemCollectorLLSMemorySpans::getData(){
    return &dataMatrix;
}
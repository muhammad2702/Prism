
#include <string>
#include <vector>
#include <iostream>
#include <csignal>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>

#include "Simulation.h"
#include "Input/Input.h"

using namespace std;

/// simulations might be aborted to user or operating system interruption.
bool aborted;

void signalHandler(int s)
{
    cout << endl;
    cout << "signal '" << string(strerror(s)) << "' caught." << endl;
    cout << "Aborting the simulation sanely and flushing the results to disk..." <<  endl;
    aborted = true;
}

void registerSignalHandler()
{
#ifdef __linux__
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = signalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);
    sigaction(SIGTERM, &sigIntHandler, NULL);
    sigaction(SIGABRT, &sigIntHandler, NULL);
#endif
}

int main(int argc,char *argv[])
{

    registerSignalHandler();


	time_t start;
	time(&start);


    if(argc != 2)
    {
        cerr << "Expected exactly one argument." << endl;
        return -1;
    }
	string filename = argv[1];


	Input::fromFile inputs = Input::readFromFile(filename);

    bool success = Simulation::executeSimulations(inputs, aborted);

    //remove loaded xml from memory
    delete inputs.doc;
    inputs.doc = nullptr;

	time_t end;
	time(&end);

	if(success){
        std::cout << "All simulations finished successfully. Time: ";
	}else{
		std::cout << "There was an error during the simulations. Treat the results with care. Time: ";
	}

	std::cout << difftime(end, start) << " Seconds" << std::endl;



	return 0;
}

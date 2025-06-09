#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "Request.h"

using namespace std;

class BankersAlgorithm
{
    private:
        int numOfProcesses;
        vector<string> processesNames;
        int numOfResources;
        vector<string> resourcesNames;
        vector<int> numOfInstances;
        vector<int> availabilityVector;
        vector<vector<int>> allocationMatrix;
        vector<vector<int>> maxMatrix;
        vector<vector<int>> needMatrix;
        vector<Request> requests;
        vector<int> executionOrder;

    public:
        BankersAlgorithm(int numOfProcesses, vector<string> processesNames, int numOfResources, vector<string> resourcesNames,
        vector<int> numOfInstances, vector<int> availabilityVector, vector<vector<int>> allocationMatrix,
        vector<vector<int>> maxMatrix, vector<Request> requests);

        void printVector(const vector<int>& vec, const string& name) const;
        void printMatrix(const vector<vector<int>>& matrix, const string& name) const;
        void printBA() const;
        bool isStateSafe();
        bool isFinished(const vector<bool>& finish);
        int findProcess(const vector<bool>& finish, vector<int>& work);
        bool canBeSatisfied(int processIndex, vector<int>& work);
        void printState();
        void printExecutionOrder();
        bool requestResources(const Request& request);
        int getProcessIndexByName(const string& processName);
        void requestsStates();
};
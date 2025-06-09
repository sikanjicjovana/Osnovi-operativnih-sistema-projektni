#include "BankersAlgorithm.h"

BankersAlgorithm::BankersAlgorithm(int numOfProcesses, vector<string> processesNames, int numOfResources, 
        vector<string> resourcesNames, vector<int> numOfInstances, vector<int> availabilityVector,
        vector<vector<int>> allocationMatrix, vector<vector<int>> maxMatrix, vector<Request> requests) : 
        numOfProcesses(numOfProcesses) , processesNames(processesNames) , numOfResources(numOfResources) , resourcesNames(resourcesNames) ,
        numOfInstances(numOfInstances) , availabilityVector(availabilityVector) , allocationMatrix(allocationMatrix) , maxMatrix(maxMatrix) , requests(requests)
        {
            needMatrix.resize(numOfProcesses, vector<int>(numOfResources));
            for(int i = 0; i < numOfProcesses; i++)
            {
                for(int j = 0; j < numOfResources; j++)
                {
                    needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
                }
            }
        }
        
void BankersAlgorithm::printVector(const vector<int>& vec, const string& name) const
{
    cout << name << ": ";
    for(const auto& val : vec)
    {
        cout << val << " ";
    }
    cout << endl;
}

void BankersAlgorithm::printMatrix(const vector<vector<int>>& matrix, const string& name) const
{
    cout << name << ": " << endl;
    for(const auto& row : matrix)
    {
        for(const auto& val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

void BankersAlgorithm::printBA() const
{
    cout << "Broj procesa: " << numOfProcesses << endl;
    cout << "Nazivi procesa: ";
    for(const auto& p : processesNames)
    {
        cout << p << " ";
    }
    cout << endl;
    cout << "Broj resursa: " << numOfResources << endl;
    cout << "Nazivi resursa: ";
    for(const auto& r : resourcesNames)
    {
        cout << r << " ";
    }
    cout << endl;
    
    printVector(numOfInstances,"Broj instanci po resursu");
    printVector(availabilityVector,"Vektor raspolozivosti");
    printMatrix(allocationMatrix,"Matrica alokacija");
    printMatrix(maxMatrix,"Matrica maksimalnih zahtjeva");
    printMatrix(needMatrix,"Matrica potreba");

    cout << "Lista zahtjeva: " << endl;
    for(const auto& request : requests)
    {
        request.printRequest();
    }
}

bool BankersAlgorithm::isFinished(const vector<bool>& finish)
{
    for(int i = 0; i < numOfProcesses; i++)
    {
        if(!finish[i])
        {
            return false;
        }
    }
    return true;
}

bool BankersAlgorithm::canBeSatisfied(int processIndex, vector<int>& work)
{
    for(int i = 0; i < numOfResources; i++)
    {
        if(needMatrix[processIndex][i] > work[i])
        {
            return false;
        }
    }
    return true;
}

int BankersAlgorithm::findProcess(const vector<bool>& finish, vector<int>& work)
{
    for(int i = 0; i < numOfProcesses; i++)
    {
        if(!finish[i] && canBeSatisfied(i, work))
        {
            return i;
        }
    }
    return -1; 
}

bool BankersAlgorithm::isStateSafe()
{
    vector<int> work = availabilityVector;
    vector<bool> finish(numOfProcesses,false);
    executionOrder.clear();

    while(!isFinished(finish))
    {
        int processIndex = findProcess(finish,work);
        if(processIndex == -1)
        {
            return false;
        }

        for(int i = 0; i < numOfResources; i++)
        {
            work[i] = work[i] - needMatrix[processIndex][i] + maxMatrix[processIndex][i];
            if(work[i] > numOfInstances[i])
            {
                work[i] = numOfInstances[i];
            }
        }
        finish[processIndex] = true;
        executionOrder.push_back(processIndex);
    }
    return true;
}

void BankersAlgorithm::printExecutionOrder()
{
    cout << "Redoslijed izvrsavanja procesa: (";
    for(int i = 0; i < executionOrder.size(); i++)
    {
        cout << processesNames[executionOrder[i]];
        if(i < executionOrder.size() - 1)
        {
            cout << "->";
        }
    }
    cout << ")" << endl;
}

void BankersAlgorithm::printState() 
{
    if(isStateSafe())
    {
        cout << "Sistem je u stabilnom stanju." << endl;
        printExecutionOrder();
    }
    else
    {
        cout << "Sistem nije u stabilnom stanju." << endl;
    }
}

int BankersAlgorithm::getProcessIndexByName(const string& processName)
{
    for(int i = 0; i < numOfProcesses; i++)
    {
        if(processesNames[i] == processName)
        {
            return i;
        }
    }
    return -1;
}

bool BankersAlgorithm::requestResources(const Request& request)
{
    int processIndex = getProcessIndexByName(request.processName);
    if(processIndex == -1)
    {
        cout << "Proces ne postoji." << endl;
        return false;
    }

    const vector<int>& requestedResources = request.resources;

    vector<int> originalAvailability = availabilityVector;
    vector<vector<int>> originalAllocation = allocationMatrix;
    vector<vector<int>> originalNeed = needMatrix;

    for(int i = 0; i < numOfResources; i++)
    {
        if(requestedResources[i] > needMatrix[processIndex][i])
        {
            cout << "Zahtjev je veci od maksimalnog zahtjeva, pa zbog toga" << endl;
            return false;
        }
    }

    for(int i = 0; i < numOfResources; i++)
    {
        if(requestedResources[i] > availabilityVector[i])
        {
            cout << "Zahtjev je veci od raspolozivih, pa zbog toga" << endl;
            return false;
        }
    }

    for( int i = 0; i < numOfResources; i++)
    {
        availabilityVector[i] -= requestedResources[i];
        allocationMatrix[processIndex][i] += requestedResources[i];
        needMatrix[processIndex][i] -= requestedResources[i];
    }

    if(isStateSafe())
    {
        availabilityVector = originalAvailability;
        allocationMatrix = originalAllocation;
        needMatrix = originalNeed;

        return true;
    }
    else
    {
        for(int i = 0; i < numOfResources; i++)
        {
            availabilityVector[i] += requestedResources[i];
            allocationMatrix[processIndex][i] -= requestedResources[i];
            needMatrix[processIndex][i] += requestedResources[i];
        }
        return false;
    }
}

void BankersAlgorithm::requestsStates()
{
    for(const auto& request : requests)
    {
        if(requestResources(request))
        {
            cout << "-" << request << " ce biti odobren." << endl;
        }
        else
        {
            cout << "-" << request << " nece biti odobren." << endl;
        }
    }
}
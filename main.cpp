#include <iostream>
#include <fstream>
#include <sstream>
#include "BankersAlgorithm.h"

using namespace std; 

int main()
{
    string selector;
    cout << "Da li zelite da pokrenete simulaciju?[DA/NE]" << endl;
    cin >> selector;
    if(selector == "DA")
    {
        cout << "Unesite ime datoteke:" << endl;
        string filename;
        cin >> filename;
        ifstream file(filename);
        if(file.is_open())
        {
            string line;
            int numOfProcesses;
            getline(file,line);
            istringstream iss(line);
            iss >> numOfProcesses;

            vector<string> processesNames;
            getline(file,line);
            istringstream processesStream(line);
            string processesName;
            while(processesStream >> processesName)
            {
                processesNames.push_back(processesName);
            }

            int numOfResources;
            getline(file,line);
            istringstream iss1(line);
            iss1 >> numOfResources;

            vector<string> resourcesNames;
            getline(file,line);
            istringstream resourcesStream(line);
            string resourcesName;
            while(resourcesStream >> resourcesName)
            {
                resourcesNames.push_back(resourcesName);
            }

            vector<int> numOfInstances;
            getline(file,line);
            istringstream instancesStream(line);
            int instance;
            while(instancesStream >> instance)
            {
                numOfInstances.push_back(instance);
            }

            vector<int> availabilityVector;
            getline(file,line);
            istringstream availabilityStream(line);
            int available;
            while(availabilityStream >> available)
            {
                availabilityVector.push_back(available);
            }

            getline(file,line);

            vector<vector<int>> allocationMatrix;
            for(int i = 0; i < numOfProcesses; i++)
            {
                getline(file,line);
                istringstream iss(line);
                vector<int> row;
                int val;
                while(iss >> val)
                {
                    row.push_back(val);
                }
                allocationMatrix.push_back(row);
            }

            getline(file,line);

            vector<vector<int>> maxMatrix;
            for(int i = 0; i < numOfProcesses; i++)
            {
                getline(file,line);
                istringstream iss(line);
                vector<int> row;
                int val;
                while(iss >> val)
                {
                    row.push_back(val);
                }
                maxMatrix.push_back(row);
            }

            getline(file,line);

            vector<Request> requests;
            while(getline(file,line))
            {
                istringstream iss(line);
                string name;
                iss >> name;
                vector<int> resources;
                int val;
                while(iss >> val)
                {
                    resources.push_back(val);
                }
                requests.push_back(Request(name,resources));
            }
            file.close();
            BankersAlgorithm ba(numOfProcesses,processesNames,numOfResources,resourcesNames,numOfInstances,availabilityVector,allocationMatrix,maxMatrix,requests);
            cout << "------------Simulacija pokrenuta-------------" << endl;
            cout << endl;
            cout << " ___________________________________________ " << endl;
            cout << "|                                           |" << endl;
            cout << "|           Rezultati simulacije:           |" << endl;
            cout << "|___________________________________________|" << endl;
            cout << endl;
            ba.printBA();
            cout << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << endl;
            ba.printState();
            cout << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << endl;
            ba.requestsStates();
            cout << endl;
            cout << "---------------------------------------------------------" << endl;
            cout << endl;
        }
    }
    else if(selector == "NE")
    {
        cout << "Niste pokrenuli simulaciju." << endl;
    }
    else
    {
        cout << "Nepoznata opcija." << endl;
    }
    return 0;
}
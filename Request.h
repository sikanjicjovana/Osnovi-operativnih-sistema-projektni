#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Request
{
    public:
        string processName;
        vector<int> resources;

        Request( const string& name, const vector<int>& res);
        void printRequest() const;       
};

ostream& operator<<(ostream& os, const Request& request);
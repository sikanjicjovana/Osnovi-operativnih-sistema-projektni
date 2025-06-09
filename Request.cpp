#include "Request.h"

Request::Request( const string& name, const vector<int>& res) : processName(name) , resources(res) {}

void Request::printRequest() const
{
    cout << processName << " ";
    for(auto val : resources)
    {
        cout << val << " ";
    }
    cout << endl;
}

ostream& operator<<(ostream& os, const Request& request)
{
    os <<  "Zahtjev (" << request.processName;
    for (int res : request.resources)
    {
        os << ", " << res;
    }
    os << ")";
    return os;
}
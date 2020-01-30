#ifndef PROJ1NEW_RESOURCE_H
#define PROJ1NEW_RESOURCE_H
#include <iostream>
#include <vector>
using namespace std;

class Resource
{
private:
    int state; // 1 (free) or 0 (allocated)
    int inventory;
    vector<vector<int>> waitlist;

public:

    void setState(int st)
    {
        state = st;
    }

    int getState()
    {
        return state;
    }

    void setInventory(int inv)
    {
        inventory = inv;
    }

    int getInventory()
    {
        return inventory;
    }

    vector<vector<int>> &getWaitlist()  {
        return waitlist;
    }

    void setWaitlist(int proc, int k) {
        vector<int> arr;
        arr.push_back(proc);
        arr.push_back(k);
        Resource::waitlist.push_back(arr);
    }
//    vector<int> &getWaitlist()  {
//        return waitlist;
//    }
//
//    void setWaitlist(int proc)
//    {
//        Resource::waitlist.push_back(proc);
//    }

};

#endif //PROJ1NEW_RESOURCE_H

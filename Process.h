
#ifndef PROJ1NEW_PCB_H
#define PROJ1NEW_PCB_H
#include <iostream>
#include <vector>
using namespace std;

class Process
{
private:
    int id;
    int state;
    int parent;
    int priority;
    int units;
    vector<int> children;
    vector<vector<int>> resource;

public:

    int getPriority() const {
        return priority;
    }

    int setPriority(int priority)
    {
        Process::priority = priority;
    }

    int getUnits() const {
        return units;
    }

    int setUnits(int units)
    {
        Process::units = units;
    }


    int getId() const {
        return id;
    }

    int setId(int id)
    {
        Process::id = id;
    }

    int getState() const {
        return state;
    }

    void setState(int state) {
        Process::state = state; // 1 (ready) or 0 (blocked)
    }

    int getParent() const {
        return parent;
    }

    void setParent(int parent) {
        Process::parent = parent;
    }

    vector<int> &getChildren()  {
        return children;
    }

    void setChildren(int proc) {
        Process::children.push_back(proc);
    }

    vector<vector<int>> &getResource()  {
        return resource;
    }

    void setResource(int rec, int unit) {
        vector<int> arr;
        arr.push_back(rec);
        arr.push_back(unit);
        Process::resource.push_back(arr);
    }

    void changeResourceUnits(int index, int units)
    {
        resource[index][1] = units;
    }


};

#endif //PROJ1NEW_PCB_H

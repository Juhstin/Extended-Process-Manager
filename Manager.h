#ifndef PROJ1NEW_MANAGER_H
#define PROJ1NEW_MANAGER_H
#include "Process.h"
#include "Resource.h"

class Manager
{
private:
    int currProc;
    int procCount;
    vector<Process*> PCB;
    vector<int> RL[3];
    vector<Resource*> RCB;
    vector<int> freeID;

public:
    void init()
    {
        currProc = 0;
        procCount = 0;
        PCB.clear();
        RL[2].clear();
        RL[1].clear();
        RL[0].clear();
        RCB.clear();
        freeID.clear();

        Process * newProc = new Process();
        newProc->setState(1);
        newProc->setId(procCount);
        newProc->setPriority(0);
        PCB.push_back(newProc);
        RL[0].push_back(procCount);

        incProcCount();

        // Creating 4 free resources
        for(int i = 0; i < 4; i++)
        {
            Resource* r = new Resource();
            if(i == 0 || i == 1)
                r->setState(1);
            else if(i == 2)
                r->setState(2);
            else if(i == 3)
                r->setState(3);
            RCB.push_back(r);
        }

        for(int i = 1; i < 16; i++)
        {
            freeID.push_back(i);
        }
//        cout << "* Process 0 created" << endl;
        scheduler();
    }

    void incProcCount()
    {
       procCount += 1;
    }

    void setCurrProc(int proc)
    {
        procCount = proc;
    }

    int getCurrProc()
    {
        return currProc;
    }

    int getProcCount()
    {
        return procCount;
    }

    const vector<Process *> &getPCB() const {
        return PCB;
    }

    const vector<int> &getRL2() const {
        return RL[2];
    }

    const vector<int> &getRL1() const {
        return RL[1];
    }
    const vector<int> &getRL0() const {
        return RL[0];
    }

    void create(int p)
    {
        if(p < 1 || p > 2 || procCount == 16)
        {
            cout << "-1 ";
            return;
        }

        sort(freeID.begin(),freeID.end());

//        allocate new PCB[j]
        Process * newProc = new Process();

//        state = ready
        newProc->setState(1);

//        insert j into children of i
        PCB[getIndex(currProc)]->setChildren(freeID[0]);

//        parent = i
        newProc->setParent(currProc);

        newProc->setId(freeID[0]);

//        children = NULL
//        resources = NULL

        newProc->setPriority(p);

//        insert j into RL
        RL[p].push_back(freeID[0]);

        PCB.push_back(newProc);



//        display: “process j created”
//        cout << "* Process " << freeID[0] << " created" << endl;

        incProcCount();
        freeID.erase(freeID.begin());

//        cout << "Scheduler Create()" << endl;
        scheduler();
    }

    void destroy(int proc,bool first=true)
    {
        if(procCount == 1 || proc == 0)
        {
            cout << "-1 ";
            return;
        }

//        for all k in children of proc destroy(k)
        while(!PCB[getIndex(proc)]->getChildren().empty())
        {
            int child = PCB[getIndex(proc)]->getChildren().back();
            destroy(child,false);
            PCB[getIndex(proc)]->getChildren().pop_back();

        }

//        remove proc from parent's list
        if(first)
        {
            int parent = PCB[getIndex(proc)]->getParent();
            for(int i = 0; i < PCB[getIndex(parent)]->getChildren().size(); i++)
            {
                if(PCB[getIndex(parent)]->getChildren()[i] == proc)
                {
                    PCB[getIndex(parent)]->getChildren().erase(PCB[getIndex(parent)]->getChildren().begin() + i);
                    break;
                }
            }
        }


//        remove proc from RL or waiting list
        for(int i = 0; i < RL[PCB[getIndex(proc)]->getPriority()].size(); i++)
        {
            if(RL[PCB[getIndex(proc)]->getPriority()][i] == proc)
            {
                RL[PCB[getIndex(proc)]->getPriority()].erase(RL[PCB[getIndex(proc)]->getPriority()].begin()+i);
                break;
            }
        }

//        release all resources of proc
        for(int i = 0; i < PCB[getIndex(proc)]->getResource().size(); i++)
            release(PCB[getIndex(proc)]->getResource()[i][0],PCB[getIndex(proc)]->getResource()[i][1],false);


//        free PCB of proc
        PCB.erase(PCB.begin()+getIndex(proc));

        procCount-=1;
        freeID.push_back(proc);

//        display: “n processes destroyed”
//        cout << "* Process " << proc << " destroyed" << endl;
//        cout << "Scheduler Destroy()" << endl;
        if(first)
            scheduler();
    }

    void request(int r,int k)
    {
        if(containR(r) != -1)
        {
            cout << "-1 ";
            return;
        }
        if(currProc == 0)
        {
            cout << "-1 ";
            return;
        }

        if(r == 0 || r == 1)
        {
            if(k != 1)
            {
                cout << "-1 ";
                return;
            }
        }
        else if(r == 2)
        {
            if(k < 1 || k > 2)
            {
                cout << "-1 ";
                return;
            }
        }
        else if(r == 3)
        {
            if(k < 1 || k > 3)
            {
                cout << "-1 ";
                return;
            }
        }

//        if state of r is free
        if(RCB[r]->getState() >= k && RCB[r]->getWaitlist().empty())
        {
//             Set remaining units
            RCB[r]->setState(RCB[r]->getState()-k);

//            insert r into list of resources of process i
            PCB[getIndex(currProc)]->setResource(r,k);

//            display: “resource r allocated”
//            cout << "* Resource " << r << " allocated" << endl;
//            cout << "Resource for Proc" << currProc << ": " << PCB[getIndex(currProc)]->getResource()[0][0] << ","<< PCB[getIndex(currProc)]->getResource()[0][1] << endl;
        }
        else
        {
//            state of i = blocked
            PCB[getIndex(currProc)]->setState(0);

//            move i from RL to waitlist of r
            RL[PCB[getIndex(currProc)]->getPriority()].erase(RL[PCB[getIndex(currProc)]->getPriority()].begin());
            RCB[r]->setWaitlist(currProc,k);

//            display: “process i blocked”
//            cout << "* Process " << currProc << " blocked" << endl;
//            scheduler()
        }
//        cout <<  "Scheduler Request()" << endl;
        scheduler();
    }

    void release(int r, int k, bool notDest = true)
    {
        if(containR(r) != -1)
        {
            if(k > PCB[getIndex(currProc)]->getResource()[containR(r)][1])
            {
                // k (units to be released) is greater than currproc's resource's allocated units
                cout << "-1 ";
                return;
            }

            if(k == PCB[getIndex(currProc)]->getResource()[containR(r)][1])
            {
                // remove r from resources list of process i if k == resource's allocated units
                PCB[getIndex(currProc)]->getResource().erase(PCB[getIndex(currProc)]->getResource().begin() + containR(r));
                RCB[r]->setState(RCB[r]->getState() + k);
            }
            else
            {
                // less than so don't remove from resources list of process i
                // instead subtract units its using
                PCB[getIndex(currProc)]->changeResourceUnits(containR(r),PCB[getIndex(currProc)]->getResource()[containR(r)][1] - r);
//                PCB[getIndex(currProc)]->getResource()[containR(r)][1] -= r;
                RCB[r]->setState(RCB[r]->getState() + k);
            }

//            cout << RCB[r]->getState() << endl;

            while(!RCB[r]->getWaitlist().empty() && RCB[r]->getState() > 0)
            {
                int arr[2];
                arr[0] = RCB[r]->getWaitlist()[0][0];
                arr[1] = RCB[r]->getWaitlist()[0][1];
                if(RCB[r]->getState() >= arr[1] && getIndex(arr[0]) != -1)
                {
                    RCB[r]->setState(RCB[r]->getState()-arr[1]);
                    PCB[getIndex(arr[0])]->setState(1);
                    PCB[getIndex(arr[0])]->setResource(r,arr[1]);
                    RL[PCB[getIndex(arr[0])]->getPriority()].push_back(arr[0]);
                    RCB[r]->getWaitlist().erase(RCB[r]->getWaitlist().begin());
                }
                else
                    break;
            }
//            cout << "Scheduler Release()" << endl;
            if(notDest)
                scheduler();
        }
        else
        {
            if(notDest)
                cout << "-1 ";
        }
    }

    int getIndex(int proc)
    {
        for(int i = 0; i < PCB.size(); i++)
        {
            if(PCB[i]->getId() == proc)
                return i;
        }
        return -1;
    }

    void timeout()
    {
        if(!RL[2].empty())
        {
            int temp = RL[2][0];
            RL[2].erase(RL[2].begin());
            RL[2].push_back(temp);
        }
        else if(!RL[1].empty())
        {
            int temp = RL[1][0];
            RL[1].erase(RL[1].begin());
            RL[1].push_back(temp);
        }
        else if(!RL[0].empty())
        {
            int temp = RL[0][0];
            RL[0].erase(RL[0].begin());
            RL[0].push_back(temp);
        }
//        int temp = RL[0];
//        RL.erase(RL.begin());
//        RL.push_back(temp);
//        cout << "Scheduler Timeout()" << endl;
        scheduler();
    }

    void scheduler()
    {
        if(!RL[2].empty())
            currProc = RL[2][0];
        else if(!RL[1].empty())
            currProc = RL[1][0];
        else if(!RL[0].empty())
            currProc = RL[0][0];
//        currProc = RL[0];
//        cout << "* Process " << currProc << " running" << endl;
        cout << currProc << " ";
    }

    //Returns resource position in vector of resources from Process
    int containR(int r)
    {
        for(int i = 0; i < PCB[getIndex(currProc)]->getResource().size(); i++)
        {
            if(PCB[getIndex(currProc)]->getResource()[i][0] == r)
            {
                return i;
            }
        }
        return -1;
    }

    int containC(int c)
    {
        for(int i = 0; i < PCB[getIndex(currProc)]->getChildren().size();i++)
        {
            if(PCB[getIndex(currProc)]->getChildren()[i] == c)
                return 0;
        }
        return -1;
    }


};

#endif //PROJ1NEW_MANAGER_H

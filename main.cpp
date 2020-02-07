#include <iostream>
#include "Process.h"
#include "Manager.h"
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
using namespace std;


int main() {

    Manager *testManager = new Manager();
    ifstream inFile;
    inFile.open("/Users/JustinFu/Documents/CompSci 143B/Proj1New/input.txt");
    string input;

    while(getline(inFile,input))
    {
//        string input;
//        cout << "> ";
//        getline(cin,input);

        regex reg("\\s+");
        sregex_token_iterator iter(input.begin(), input.end(), reg, -1);
        sregex_token_iterator end;
        vector<string> inputV(iter, end);

//        stringstream ss(input);
//        string tmp;
//        while(getline(ss, tmp, ' '))
//            inputV.push_back(tmp);

//        cout << inputV[0] << endl;

        if(inputV[0].size() == 0)
        {
            continue;
        }
        else if(inputV[0] == "cr")
        {
            try {
                if (inputV.size() != 2 || stoi(inputV[1]) < 1 || stoi(inputV[1]) > 2) {
                    cout << "-1 ";
                    continue;
                }
                testManager->create(stoi(inputV[1]));
            }
            catch(...)
            {
                cout << "-1 ";
            }
        }
        else if(inputV[0] == "de")
        {
            if(stoi(inputV[1]) != testManager->getCurrProc())
            {
                if(testManager->containC(stoi(inputV[1])) == -1)
                {
                    cout << "-1 ";
                    continue;
                }
            }
            testManager->destroy(stoi(inputV[1]));
        }
        else if(inputV[0] == "rq")
        {
            if(inputV.size() != 3 || stoi(inputV[1]) < 0 || stoi(inputV[1]) > 3)
            {
                cout << "-1 ";
                continue;
            }
            testManager->request(stoi(inputV[1]),stoi(inputV[2]));
        }
        else if(inputV[0] == "rl")
        {
            if(inputV.size() != 3 || stoi(inputV[1]) < 0 || stoi(inputV[1]) > 3)
            {
                cout << "-1 ";
                continue;
            }
            testManager->release(stoi(inputV[1]),stoi(inputV[2]));
        }
        else if(inputV[0] == "to")
        {
            testManager->timeout();
        }
        else if(inputV[0] == "in")
        {
            cout << endl;
            testManager->init();
        }
        else
        {
            cout << "-1 ";
        }
        /*
        if(testManager->getPCB().size() > 2)
        {
            cout << "Children of Proc(2): ";
            for(int i = 0; i < testManager->getPCB()[2]->getChildren().size(); i++)
                cout << testManager->getPCB()[2]->getChildren()[i] << " ";
            cout << endl;
        }
    */
//        cout << "RL2: ";
//        for(int i = 0; i < testManager->getRL2().size(); i++)
//        {
//            cout << testManager->getRL2()[i] << "->";
//        }
//        cout << endl << "RL1: ";
//        for(int i = 0; i < testManager->getRL1().size(); i++)
//        {
//            cout << testManager->getRL1()[i] << "->";
//        }
//        cout << endl << "RL0: ";
//        for(int i = 0; i < testManager->getRL0().size(); i++)
//        {
//            cout << testManager->getRL0()[i] << "->";
//        }
//        cout << endl;
    }




    return 0;
}
#include <iostream>
#include "Process.h"
#include "Manager.h"
#include <sstream>
#include <string>
#include <fstream>
using namespace std;


int main() {

    Manager *testManager = new Manager();
    ifstream inFile;
    inFile.open("/Users/JustinFu/Documents/CompSci 143B/Proj1New/input.txt");
    string input;
//    while(getline(inFile,input))
//    {
////        cout << input << endl;
//        vector<string> inputV;
//        stringstream ss(input);
//        string tmp;
//        while(getline(ss,tmp,' '))
//            inputV.push_back(tmp);
//        cout << inputV[0] << endl;
//    }
//    return 0;
    while(true)
    {
        string input;
        cout << "> ";
        getline(cin,input);
        vector<string> inputV;
        stringstream ss(input);
        string tmp;
        while(getline(ss, tmp, ' '))
            inputV.push_back(tmp);

//        cout << inputV[0] << endl;

        if(inputV[0] == "cr")
        {
            if(inputV.size() != 2 || stoi(inputV[1]) < 0 || stoi(inputV[1]) > 2)
            {
                cout << "* error" << endl;
                continue;
            }
            testManager->create(stoi(inputV[1]));
        }
        else if(inputV[0] == "de")
        {
            testManager->destroy(stoi(inputV[1]));
        }
        else if(inputV[0] == "rq")
        {
            if(inputV.size() != 3 || stoi(inputV[1]) < 0 || stoi(inputV[1]) > 3)
            {
                cout << "* error" << endl;
                continue;
            }
            testManager->request(stoi(inputV[1]),stoi(inputV[2]));
        }
        else if(inputV[0] == "rl")
        {
            if(inputV.size() != 3 || stoi(inputV[1]) < 0 || stoi(inputV[1]) > 3)
            {
                cout << "* error from main" << endl;
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
            testManager->init();
        }
        else
        {
            cout << "* error" << endl;
        }
        /*
        if(testManager->getPCB().size() > 2)
        {
            cout << "Children of Proc(2): ";
            for(int i = 0; i < testManager->getPCB()[2]->getChildren().size(); i++)
                cout << testManager->getPCB()[2]->getChildren()[i] << " ";
            cout << endl;
        }

        cout << "RL2: ";
        for(int i = 0; i < testManager->getRL2().size(); i++)
        {
            cout << testManager->getRL2()[i] << "->";
        }
        cout << endl << "RL1: ";
        for(int i = 0; i < testManager->getRL1().size(); i++)
        {
            cout << testManager->getRL1()[i] << "->";
        }
        cout << endl << "RL0: ";
        for(int i = 0; i < testManager->getRL0().size(); i++)
        {
            cout << testManager->getRL0()[i] << "->";
        }
        cout << endl;*/
    }




    return 0;
}
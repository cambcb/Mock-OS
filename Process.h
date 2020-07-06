//Camryn Buonamassa
#pragma once
#include <string>
using namespace std;

class Process {
    public:
        Process();
        Process(int pid, long long int size, long long int start, long long int end, string state, string type);
        int getPid();
        long long int getSize();
        string getType();
        void setState(string i);

    private:
        long long int pid;
        long long int start;
        long long int end;
        long long int size;
        string state;
        string type;      
};
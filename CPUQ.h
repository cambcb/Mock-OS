//Camryn Buonamassa
#pragma once
#include "Process.cpp"
#include "Disk.cpp"
#include <deque>
using namespace std;

class CPUQ {
    public: 
        CPUQ();
        bool rtQIsEmpty();
        bool commonQIsEmpty();
        int rtSize();
        int commonSize();
        Process commonFront();
        Process rtFront();
        void setUsingCPU(Process p);
        Process getUsingCPU();
        deque<Process> getRtQ();
        deque<Process> getCommonQ();
        void pushCommon(Process p);
        void pushFrontCommon(Process p); 
        void pushRt(Process p);
        void popCommon();
        void popRt();

    private:
        Process usingCPU;
        deque<Process> rtQ;
        deque<Process> commonQ; 
};
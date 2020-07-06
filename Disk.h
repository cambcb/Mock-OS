//Camryn Buonamassa
#pragma once
#include "Process.cpp"
#include <deque>
#include <vector>
using namespace std;

class Disk {
    public: 
        Disk();
        Disk(int numDisks);
        Process getUsingDisk(int diskId);
        Process getFrontProcess(int diskId);
        bool diskIsBusy(int diskId);
        int getDiskQueueSize(int diskId);
        void setUsingDisk(Process p, int diskId);
        void pushProcessToDisk(Process p, int diskId); //adds to back of queue //push
        void popProcessFromDisk(int diskId); //adds to back of queue //push_back
        void printDisks();
    private:
        //index is hard disk number, pair key is running process, deque has waiting processes
        vector<pair<Process, deque<Process> > > diskQueues;
};
//Camryn Buonamassa
#pragma once
#include "Disk.h"
#include <deque>
#include <iostream>
using namespace std;

Disk::Disk(){

}

Disk::Disk(int numDisks){
    Process nullProcess = Process();
    diskQueues.resize(numDisks);
}

bool Disk::diskIsBusy(int diskId){
    return (diskQueues[diskId].first.getPid() != 0);
}

int Disk::getDiskQueueSize(int diskId){
    return diskQueues[diskId].second.size();
}

void Disk::setUsingDisk(Process p, int diskId){
    diskQueues[diskId].first = p;
}

Process Disk::getUsingDisk(int diskId){
    return(diskQueues[diskId].first);
}

Process Disk::getFrontProcess(int diskId){
    return diskQueues[diskId].second[0];
}

void Disk::pushProcessToDisk(Process p, int diskId){ //adds to back of queue //push
    diskQueues[diskId].second.push_back(p);
}

void Disk::popProcessFromDisk(int diskId){ //adds to back of queue //push_back
    diskQueues[diskId].second.pop_front();
}

void Disk::printDisks(){
    for(int i = 0; i < diskQueues.size(); i++){
        if(diskQueues[i].first.getPid() == 0){
            cout << "Disk " << i << ": empty" << endl;
            continue;
        }
        cout << "Disk " << i << ": P" << diskQueues[i].first.getPid() << endl;
        cout << "I/O " << i << ":";
        if(diskQueues[i].second.empty()){
            cout << " empty";
        }
        else{
            for(int j = 0; j < diskQueues[i].second.size(); j++){
                cout << " P" << diskQueues[i].second[j].getPid();
            }
        }
        cout << endl;
    }
}

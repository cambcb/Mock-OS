//Camryn Buonamassa
#pragma once
#include "CPUQ.cpp"
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <string>
using namespace std;

Process createNullProcess(){
    return Process();
}

void createNewProcess(int pid, long long int size, long long int start, long long int end, vector<pair<int, vector<long long int> > > & memory, long long int memoryIndex, long long int & memUsed, bool & isCpuBusy, CPUQ & readyQueue, string type){
    if(type == "common"){
        if(isCpuBusy){
            Process process(pid, size, start, end, "waiting", "common");
            readyQueue.pushCommon(process);
            vector<long long int> newVec;
            newVec.push_back(start);
            newVec.push_back(start + size - 1);
            pair<int, vector<long long int> > newPair;
            newPair = make_pair(pid, newVec);
            memory.insert(memory.begin() + memoryIndex, newPair);
            memUsed = memUsed + size;
        }
        else{
            Process process(pid, size, start, end, "running", "common");
            readyQueue.setUsingCPU(process);
            isCpuBusy = true;
            vector<long long int> newVec;
            newVec.push_back(start);
            newVec.push_back(start + size - 1);
            pair<int, vector<long long int> > newPair;
            newPair = make_pair(pid, newVec);
            memory.insert(memory.begin() + memoryIndex, newPair);
            memUsed = memUsed + size;
        }
    }
    else{
        if(isCpuBusy){
            if(readyQueue.getUsingCPU().getType() == "common"){
                readyQueue.pushFrontCommon(readyQueue.getUsingCPU());
                Process process(pid, size, start, end, "running", "real-time");
                readyQueue.setUsingCPU(process);
                vector<long long int> newVec;
                newVec.push_back(start);
                newVec.push_back(start + size - 1);
                pair<int, vector<long long int> > newPair;
                newPair = make_pair(pid, newVec);
                memory.insert(memory.begin() + memoryIndex, newPair);
                memUsed = memUsed + size;
            }
            else{
                Process process(pid, size, start, end, "waiting", "real-time");
                readyQueue.pushRt(process);
                vector<long long int> newVec;
                newVec.push_back(start);
                newVec.push_back(start + size - 1);
                pair<int, vector<long long int> > newPair;
                newPair = make_pair(pid, newVec);
                memory.insert(memory.begin() + memoryIndex, newPair);
                memUsed = memUsed + size;
            }
        }
        else{
            Process process(pid, size, start, end, "running", "real-time");
            readyQueue.setUsingCPU(process);
            isCpuBusy = true;
            vector<long long int> newVec;
            newVec.push_back(start);
            newVec.push_back(start + size - 1);
            pair<int, vector<long long int> > newPair;
            newPair = make_pair(pid, newVec);
            memory.insert(memory.begin() + memoryIndex, newPair);
            memUsed = memUsed + size;
        }
    }
}

void newProcess(int pid, long long int size, CPUQ & readyQueue, bool & isCpuBusy, vector<pair<int, vector<long long int> > > & memory, long long int & memUsed, const long long int & RAM, string type){ //A & AR
    long long int start = 0; //where process starts in memory
    int memoryIndex = 0; //where to insert new memory block in relation to the others

    if(memory.size() == 0){
        createNewProcess(pid, size, 0, size - 1, memory, 0, memUsed, isCpuBusy, readyQueue, type);
        return;
    }
    else if(memory.size() == 1){
        if(memory[0].second[0] == 0){
            if(memory[0].second[1] + size < RAM){
                start = memory[0].second[1] + 1;
                createNewProcess(pid, size, start, start + size - 1, memory, 1, memUsed, isCpuBusy, readyQueue, type);
                return;
            }
            else{
                cout << "There is not enough memory available for this process." << endl;
                return;
            }
        }
        else{
            if(size < memory[0].second[0]){
                createNewProcess(pid, size, 0, size - 1, memory, 0, memUsed, isCpuBusy, readyQueue, type);
                return;
            }
            else{
                cout << "There is not enough memory available for this process." << endl;
                return;
            }
        }
    }
    else{
        if(memory[0].second[0] != 0){ //check that there is no room before first memory block
            if(size <= memory[0].second[0]){ //there is room at the beginning of memory
                createNewProcess(pid, size, 0, size - 1, memory, 0, memUsed, isCpuBusy, readyQueue, type);
                return;
            }
        }
        for(long long int i = 0; i < memory.size() - 1; i++){
            long long int beginSpace = memory[i].second[1]; //end of last memory block
            long long int endSpace = memory[i+1].second[0]; //start of next memory block
            long long int space = endSpace - beginSpace - 1;
            if(space >= size){
                start = beginSpace + 1;
                createNewProcess(pid, size, start, start + size - 1, memory, i + 1, memUsed, isCpuBusy, readyQueue, type);
                return;
            }
        }
        long long int memEnd = memory[memory.size()-1].second[1];
        if(memEnd + size > RAM){
            cout << "There is not enough sequential memory for this process." << endl;
            return;
        }
        else{
            start = memEnd + 1;
            long long int newProcessIndex = memory.size();
            createNewProcess(pid, size, start, start + size - 1, memory, newProcessIndex, memUsed, isCpuBusy, readyQueue, type);
            return;
        }
    }
}

void endTimeSlice(CPUQ & readyQueue){ //Q
    Process endedProcess = readyQueue.getUsingCPU();
    int pid = endedProcess.getPid();
    string type = endedProcess.getType();
    if(pid == 0){
        cout << "There is no running process." << endl;
        return;
    }
    else if(readyQueue.rtSize() == 0 && readyQueue.commonSize() == 0){ //there are no other processes, leave it on CPU
        return;
    }
    else if(readyQueue.rtSize() > 0){
        readyQueue.setUsingCPU(readyQueue.rtFront());
        readyQueue.popRt();
    }
    else if(readyQueue.commonSize() > 0){
        readyQueue.setUsingCPU(readyQueue.commonFront());
        readyQueue.popCommon();
    }
    if(type == "common"){
        readyQueue.pushCommon(endedProcess);
    }
    else{
        readyQueue.pushRt(endedProcess);
    }
}

void requestDisk(int disk, bool & isCpuBusy, CPUQ & readyQueue, Disk & disks){ //d#
    if(disks.diskIsBusy(disk) && readyQueue.getUsingCPU().getPid() != 0){
        disks.pushProcessToDisk(readyQueue.getUsingCPU(), disk);
    }
    else if(!disks.diskIsBusy(disk) && readyQueue.getUsingCPU().getPid() != 0) {
        disks.setUsingDisk(readyQueue.getUsingCPU(), disk);
    }
    if(!readyQueue.rtQIsEmpty()){
        readyQueue.setUsingCPU(readyQueue.rtFront());
        readyQueue.popRt();
    }
    else if(!readyQueue.commonQIsEmpty()){
        readyQueue.setUsingCPU(readyQueue.commonFront());
        readyQueue.popCommon();
    }
    else{
        Process nullProcess = createNullProcess();
        readyQueue.setUsingCPU(nullProcess);
        isCpuBusy = false;
    }
}

void completeDiskProcess(int disk,  Disk & disks, CPUQ & readyQueue, bool & isCpuBusy){ //D#
    if(!isCpuBusy){
        readyQueue.setUsingCPU(disks.getUsingDisk(disk));
        isCpuBusy = true;
    }
    else{
        if(readyQueue.getUsingCPU().getType() == "common" && disks.getUsingDisk(disk).getType() == "real-time"){
            readyQueue.pushFrontCommon(readyQueue.getUsingCPU());
            readyQueue.setUsingCPU(disks.getUsingDisk(disk));
            isCpuBusy = true;
        }
        else if(disks.getUsingDisk(disk).getType() == "common"){
            readyQueue.pushCommon(disks.getUsingDisk(disk));
        }
        else{
            if(disks.getUsingDisk(disk).getPid() != 0){
                readyQueue.pushRt(disks.getUsingDisk(disk));
            }
        }
    }
    if(disks.getDiskQueueSize(disk) > 0 && disks.getFrontProcess(disk).getPid() != 0){
        disks.setUsingDisk(disks.getFrontProcess(disk), disk);
        disks.popProcessFromDisk(disk);
    }
    else{
        Process nullProcess = createNullProcess();
        disks.setUsingDisk(nullProcess, disk);
    }
}

void showReadyQueue(bool & isCpuBusy, CPUQ & readyQueue){ //Sr also shows process using CPU
    if(readyQueue.getUsingCPU().getPid() == 0){
        cout << "CPU: " << "empty" << endl;
    }
    else{
        cout << "CPU: " << "P" << readyQueue.getUsingCPU().getPid() << " " << endl;
    }
    cout << "Real-time queue: ";
    if(readyQueue.rtSize() > 0){
        for(Process process : readyQueue.getRtQ()){
            cout << "P" << process.getPid() << " ";
        }
        cout << endl;
    }
    else{
        cout << "empty" << endl;
    }
    cout << "Common queue: ";
    if(readyQueue.commonSize() > 0){
        for(Process process : readyQueue.getCommonQ()){
            cout << "P" << process.getPid() << " ";
        }
        cout << endl;
    }
    else{
        cout << "empty" << endl;
    }
}

void showDisks(Disk & disks){ //Si
    disks.printDisks();
}

void showMemory(const vector<pair<int, vector<long long int> > > & memory){ //Sm
    if(memory.size() == 0){
        cout << "Memory is empty." << endl;
        return;
    }
    else{
        for(auto it : memory){
            cout << 'P' << it.first << ' ' << it.second[0] << '-' << it.second[1] << endl;
        }
    }
}

void terminateProcess(vector<pair<int, vector<long long int> > > & memory, long long int & memUsed, bool & isCpuBusy, CPUQ & readyQueue){
    int terminatePid = readyQueue.getUsingCPU().getPid();
    memUsed = memUsed - readyQueue.getUsingCPU().getSize();
    if(readyQueue.rtSize() > 0){
        readyQueue.setUsingCPU(readyQueue.rtFront());
        readyQueue.popRt();
        isCpuBusy = true;
    }
    else if(readyQueue.commonSize() > 0){
        readyQueue.setUsingCPU(readyQueue.commonFront());
        readyQueue.popCommon();
        isCpuBusy = true;
    }
    else{
        Process nullProcess = createNullProcess();
        readyQueue.setUsingCPU(nullProcess);
        isCpuBusy = false;
    }
    for(auto it = memory.begin(); it != memory.end(); it++){
        if(it->first == terminatePid){
            memory.erase(it);
            return;
        }
    }
}
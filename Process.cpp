//Camryn Buonamassa
#pragma once
#include "Process.h"
#include <string>
using namespace std;

Process::Process(){
    pid = 0;
    size = 0;
    start = 0;
    end = 0;
    state = "";
    type = "";
}

Process::Process(int newPid, long long int newSize, long long int newStart, long long int newEnd, string newState, string newType) {
    pid = newPid;
    size = newSize;
    start = newStart;
    end = newEnd;
    state = newState;
    type = newType;
}

int Process::getPid(){
    return pid;
}

long long int Process::getSize(){
    return size;
}

string Process::getType(){
    return type;
}

void Process::setState(string s){
    state = s;
}
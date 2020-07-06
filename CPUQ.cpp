//Camryn Buonamassa
#pragma once
#include "CPUQ.h"
#include <deque>
using namespace std;

CPUQ::CPUQ(){
    usingCPU = Process();
}

bool CPUQ::rtQIsEmpty(){
    return rtQ.empty();
}

bool CPUQ::commonQIsEmpty(){
    return(commonQ.empty());
}

int CPUQ::rtSize(){
    return rtQ.size();
}

int CPUQ::commonSize(){
    return commonQ.size();
}

Process CPUQ::commonFront(){
    return commonQ.front();
}

Process CPUQ::rtFront(){
    return rtQ.front();
}

void CPUQ::setUsingCPU(Process p){
    usingCPU = p;
}

Process CPUQ::getUsingCPU(){
    return usingCPU;
}

deque<Process> CPUQ::getRtQ(){
    return rtQ;
}

deque<Process> CPUQ::getCommonQ(){
    return commonQ;
}

void CPUQ::pushCommon(Process p){ //adds to back of queue
    commonQ.push_back(p);
} 

void CPUQ::pushFrontCommon(Process p){ //used for preempting common processes //push_front
    commonQ.push_front(p);
}

void CPUQ::pushRt(Process p){ //adds to back of queue //push
    rtQ.push_back(p);
}

void CPUQ::popCommon(){ //removes front, oldest process //pop_front
    commonQ.pop_front();
}

void CPUQ::popRt(){ //removes front, oldest process //pop
    rtQ.pop_front();
}
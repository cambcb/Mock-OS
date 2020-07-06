//Camryn Buonamassa
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "funcs.cpp"
using namespace std;

int main(){
    long long int RAM = 0;
    int numDisks = 0;

    cout << "How much RAM?" << endl;
    cin >> RAM;
    while(RAM < 1 || RAM > 4000000000 || cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter a number between 1 and 4000000000:" << endl;
        cin >> RAM;
    }

    cout << "How many hard disks?" << endl;
    cin >> numDisks;
    while(numDisks < 1 || cin.fail()){
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Enter a number greater than 1:" << endl;
        cin >> numDisks;
    }

    CPUQ readyQueue; //common and rt queues
    Disk disks(numDisks);
    bool isCpuBusy = false;
    int pidCount = 1; //keep track of non-reusable process ids
    long long int memUsed = 0; //make sure memory used doesn't exceed RAM
    vector<pair<int, vector<long long int> > > memory;
    
    while(1){ 
        string input;
        string func;
        getline(cin, input);
        for(char c : input){ //Removes whitespace. Could use isalnum to remove all other characters, but not necessary here
            if (c != ' ' && c != '\t' && c != '\n') {
                func += c;
            }
        } 
        
        if(func[0] == 'A' && isdigit(func[1])){ //function A
            if(memUsed + stoll(func.substr(1)) > RAM){
                cout << "Not enough RAM for process." << endl;
            }
            else{
                newProcess(pidCount, stoll(func.substr(1)), readyQueue, isCpuBusy, memory, memUsed, RAM, "common");
                pidCount++;
            }
        } 
        else if(func[0] == 'A' && func[1] == 'R' && isdigit(func[2])){ //function AR
            if(memUsed + stoll(func.substr(2)) > RAM){
                cout << "Not enough RAM for process." << endl;
            }
            else{
                newProcess(pidCount, stoll(func.substr(2)), readyQueue, isCpuBusy, memory, memUsed, RAM, "real-time");
                pidCount++;
            }
        } 
        else if(func == "Q"){ //function Q
            endTimeSlice(readyQueue);
        } 
        else if(func[0] == 'd' && isdigit(func[1])){ //function d number
            int disk = stoi(func.substr(1));
            if(disk >= 0 && disk < numDisks){ //make sure disk number is valid
                if(readyQueue.getUsingCPU().getPid() == 0 || memory.empty()){
                    cout << "There is no process using the CPU." << endl;
                }
                else{
                    requestDisk(disk, isCpuBusy, readyQueue, disks);
                }
            } 
            else{ 
                cout << "Hard disk requested does not exist." << endl;
            }
        } 
        else if(func[0] == 'D' && isdigit(func[1])){ //function D number
            int disk = stoi(func.substr(1));
            if(disk >= 0 && disk < numDisks){ //make sure disk number is valid
                if(disks.getUsingDisk(disk).getPid() == 0 || memory.empty()){
                    cout << "There is no process using the disk." << endl;
                }
                else{
                    completeDiskProcess(disk, disks, readyQueue, isCpuBusy);
                }
            } 
            else{ 
                cout << "Hard disk specified does not exist." << endl;
            }
        }
        else if(func[0] == 'S'){ //one of S functions
            if(func[1] == 'r'){
                cout << endl;
                showReadyQueue(isCpuBusy, readyQueue);
            }
            else if(func[1] == 'i'){
                if(numDisks == 0){
                    cout << "There are no hard disks." << endl;
                }
                else{
                    cout << endl;
                    showDisks(disks);
                }
            }
            else if(func[1] == 'm'){
                cout << endl;
                showMemory(memory);
            }
        }
        else if(func == "t"){ //function t
            if(!isCpuBusy){
                cout << "There is no running process to terminate." << endl;
            }
            else{
                terminateProcess(memory, memUsed, isCpuBusy, readyQueue);
            }
        }
        cout << endl;
    }   
}

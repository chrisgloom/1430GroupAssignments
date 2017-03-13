#include <queue>
#include "Server.h"
#include "StatsPerHour.h"
using namespace std;

class Simulation {
private:

// Two Servers, bob and alice
Server alice;
Server bob;
StatsPerHour myStats;

//Needs two lines one per server
queue<Customer> aliceLine;
queue<Customer> bobLine;


//currentMinute
int currentMinute = 1;

// Simulation Time
int simulationTimeLimit = 4320;

public:
void runSimulation(){
        srand(time(NULL));
        // Assign wait times to both servers
        alice.assignBothServingTimes((int[]){1,2,3,4,5},(int[]){8,9,10,11,12});
        bob.assignBothServingTimes((int[]){4,5,6,7,8},(int[]){6,7,8,9,10});


        for (; currentMinute < simulationTimeLimit; currentMinute++) {
                // Generate customers if neccesary
                generateCustomers(currentMinute);
                myStats.hourTracker(currentMinute);
                // If Alice is available and there's someone in the line, get a customer
                if (alice.serverAvailable(currentMinute) && aliceLine.size()>0) {
                        processCustomer(alice, aliceLine);
                }
                // If Bob is available, get a customer from his queue
                if (bob.serverAvailable(currentMinute) && bobLine.size()>0) {
                        processCustomer(bob, bobLine);
                }



                // End of for loop
        }

        // TEMP: Print out what we had in the stack
        // cout<<"aliceLine: \n";
        // printAndEmptyQueue(aliceLine);
        // cout<<"bobLine: \n";
        // printAndEmptyQueue(bobLine);

        cout<<endl;
        // Print out alice and bob's stats around here
        cout<<"Alice\n";
        alice.printStats();
        cout<<"\nBob\n";
        bob.printStats();

        cout<<"\nCustomers\n"
            <<"Total Served: "<<myStats.getTotalCustomers()<<endl
            <<"Average Wait Time: "<<myStats.getAverageWaitTime()<<" minutes"<<endl;
}



// Line that the customers choose is random

//Customer generation
void generateCustomers(int inputTime){
        if (inputTime%5==0 && rand()%100<=69) {
                // cout<<"Customer made at "<<inputTime<<endl;
                //Generate Customers every five minutes
                Customer temp((rand()%101)+1,inputTime);
                // Randomly into each line
                if (rand()%2==0) {
                        aliceLine.push(temp);
                }else{
                        bobLine.push(temp);
                }
        }
}
void printAndEmptyQueue(queue<Customer> input){
        while (input.size()) {
                input.front().printMe();
                input.pop();
        }

}
void processCustomer(Server &myServer, queue<Customer> &myQueue){
        int wait = myServer.serveCustomer(&myQueue.front(), currentMinute);
        if (myQueue.front().getOrder()==HOTDOG) {
                myStats.setHotdogAndGeneralWait(wait);
        }else{
                myStats.setHamburgerAndGeneralWait(wait);
        }
        myQueue.pop();
}


};

#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Customer.h"
using namespace std;

class Server {
// Array randomly chosen between 5 values
int *hotDogServingTimes;
int *hamburgerServingTimes;
int availableAtMin;
bool isBusy;

Customer *currentCust;

double customersServedThisHour = 0;

double cashierAVGHotDog=0,cashierAVGHamburger=0, cashierAVGOrderTime=0, avgCustomersServedPerHour;
vector<double> hotDogServingTimesList, hamburgerServingTimesList, allServingTimesList, customersServedInHourList;

int bookKeeping(int *arrayOfTimes, vector<double> &recordedTimes, int currentTime){
        int waitTime = arrayOfTimes[rand()%5];
        recordedTimes.push_back(waitTime);
        availableAtMin = currentTime + waitTime;

        allServingTimesList.push_back(waitTime);
        return waitTime;
}

void customersPerHourTally(){
  customersServedInHourList.push_back(customersServedThisHour);
  customersServedThisHour = 0;
}


public:
// Default Constructor
Server(){
        hotDogServingTimes = NULL;
        hamburgerServingTimes = NULL;
        currentCust = NULL;
        isBusy = false;
}
void assignBothServingTimes(int hotdog[],int hamburger[]){
        hotDogServingTimes = hotdog;
        hamburgerServingTimes = hamburger;
}
int serveCustomer (Customer* myCust, int currentTime){

        if (myCust->getOrder()==HAMBURGER) {
                customersServedThisHour++;
                return bookKeeping(hamburgerServingTimes,hamburgerServingTimesList, currentTime);

        }else if(myCust->getOrder()==HOTDOG) {
                customersServedThisHour++;
                return bookKeeping(hotDogServingTimes, hotDogServingTimesList, currentTime);
        }else{exit(1);}

        isBusy = true;
}
bool serverAvailable(int currentTime){
        // tally and reset customers per hour if it's a new hour
        if (currentTime%60==0) {
          customersPerHourTally();
        }

        if (!isBusy) {
                return true;
        }else{
                if (currentTime>=availableAtMin) {
                        isBusy=false;
                        return true;
                }
                // Should only be reached if busy is true and it isn't time for it to be false yet
                return false;
        }
}
double populateAverage(vector<double> &servingTimesList){
  if (servingTimesList.size()==0) {
    return 0;
  }
  double sum=0;
  for(int i=0;i<servingTimesList.size();i++){
    sum+=servingTimesList[i];
  }
  return sum/servingTimesList.size();
}
void printStats(){
        cashierAVGHotDog = populateAverage(hotDogServingTimesList);
        cashierAVGHamburger = populateAverage(hamburgerServingTimesList);
        avgCustomersServedPerHour = populateAverage(customersServedInHourList);
        cashierAVGOrderTime = populateAverage(allServingTimesList);


  cout<<"Average Number of Customers Served per hour: "<<avgCustomersServedPerHour<<endl
      <<"Average Time spent on Hotdog Combo orders: "<<cashierAVGHotDog<<endl
      <<"Average Time spent on Hamburger Combo orders: "<<cashierAVGHamburger<<endl
      <<"Average Time spent on all orders: "<<cashierAVGOrderTime<<endl;
}

void printVector(vector<double> printMe){
  for (size_t i = 0; i < printMe.size(); i++) {
    cout<<printMe[i]<<endl;
  }
}

};

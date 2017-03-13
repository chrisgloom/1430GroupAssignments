#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class StatsPerHour {
int currentHour;
float globalAVGHotdog;
float globalAVGHamburger;
float globalAVGCustomers;
float globalAVGWait;
vector<double> timesToServeAHotdog;
vector<double> timesToServeAHamburger;
// NOTE: variable keeps track of how many customers in the current hour and then resets
int currentHourCustomerCounter = 0;
// NOTE: Total customers served is just adding up each vector member without dividing
vector<double> customersInAnHour;
vector<double> waitTimesForCustomer;

void printStatsInColumns(int hour, double avgHotdog, double avgHamburger, double avgCustomers,double avgWait){
        cout<<left<<setw(7)<<hour<<setw(14)<<setprecision(2)<<fixed<<avgHotdog<<setw(15)
            <<avgHamburger<<setw(15)<<avgCustomers
            <<setw(12)<<avgWait<<endl;
}
void resetAndTallyUpCustomersPerHour(){
  customersInAnHour.push_back(currentHourCustomerCounter);
  currentHourCustomerCounter = 0;
}

public:
void hourTracker(int time){
        currentHour = time/60;

        if (time%60==0) {
                // NOTE: We need to do some housekeeping for the customers per hour here
                // take the customers served per hour sum, add it to the vector and reset it
                resetAndTallyUpCustomersPerHour();

                if (currentHour==1) {
                        cout<<left<<setw(7)<<"Hour"<<setw(14)<<"AVG-Hotdog"<<setw(15)
                            <<"AVG-Hamburger"<<setw(15)<<"AVG-Customers"
                            <<setw(12)<<"AVG-Wait"<<endl;
                }
                // Do all the calculations and output
                globalAVGHotdog = populateAverage(timesToServeAHotdog);
                globalAVGCustomers = populateAverage(customersInAnHour);
                globalAVGHamburger = populateAverage(timesToServeAHamburger);
                globalAVGWait = populateAverage(waitTimesForCustomer);

                // Print them
                printStatsInColumns(currentHour,globalAVGHotdog,globalAVGHamburger,globalAVGCustomers,globalAVGWait);
        }
}

void setHotdogAndGeneralWait(int wait){
        timesToServeAHotdog.push_back(wait);
        waitTimesForCustomer.push_back(wait);
        currentHourCustomerCounter++;
}
void setHamburgerAndGeneralWait(int wait){
        timesToServeAHamburger.push_back(wait);
        waitTimesForCustomer.push_back(wait);
        currentHourCustomerCounter++;
}
float populateAverage(vector<double> input){
        if (input.size()==0) {
                return 0;
        }

        double sum=0;
        for(int i=0; i<input.size(); i++) {
                sum+=input[i];
        }
        return sum/input.size();
}
int getTotalCustomers(){
  int sum = 0;
  for (size_t i = 0; i < customersInAnHour.size(); i++) {
    sum+=customersInAnHour[i];
  }
  return sum;
}

double getAverageWaitTime(){
  return globalAVGWait;
}

};

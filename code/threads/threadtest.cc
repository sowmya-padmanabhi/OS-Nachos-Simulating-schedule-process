#include "kernel.h"
#include "main.h"
#include "thread.h"
#include "person.h"
#include "../lib/list.h"
#include "request.h"
#include "bitmap.h"
#include "scheduler.h"

using namespace std;
void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %d looped %d times\n", which, num);
	printf("Hello World!");
        kernel->currentThread->Yield();
    }
}

// ---- Compare function to compare higher priority between two person----
int comparePriority(Person per1, Person per2){
    if(per1.getPersonPriority() < per2.getPersonPriority())
        return -1;
    else if(per1.getPersonPriority() > per2.getPersonPriority())
        return 1;
    else return 0;
}
// ---- Print function to print out each person and associated information of the person ----
void print(Person per){
    std::cout << "Person with the sequence number: " << per.getPersonSequence() << ", priority number: " << per.getPersonPriority() << ", has  " << per.getTotalClothes() << "  number of clothes and needs total of " << per.getTimeWash() << " time to finish washing the clothes\n";
}
// ---- Simunation 1 ----
void simulation1(int numb){
    // ---- Using the existing SortedList function to sort the Person list- highest priority to lowest priority----
    SortedList<Person> *sortPerson = new SortedList<Person>(comparePriority);
    int seq = 0;
    int timeTotal = 0;
    //----Generating 20 Persons----
    for(int i=0; i<numb; i++){
        Person per(seq++, rand()%20, rand()%30, rand()%50);
        sortPerson->Insert(per);
    }
    //---- Printing the Person order ----
    std::cout << "\n***************Simulation 1 Running *****************\n \n Laundry line up according to priority \n \n ";
    ListIterator<Person> list = sortPerson;
    sortPerson->Apply(print);
    std::cout << "\n _________ Simulation 1 begins.....__________\n\n";
    int order = 0;
    Person prevPerson;
    while (!list.IsDone()){
        Person per = sortPerson->Front();
        timeTotal += per.getTimeWash();
        std::cout << "The order is " << order++ << ": ";
        print(per);
        if(prevPerson.getPersonSequence() != NULL)
            std::cout << "Person with the sequence number" << prevPerson.getPersonSequence() << " leaves the room. This person took a total time of " << prevPerson.getTimeWash() << " to finish washing all the clothes.\n";
        else
            std::cout << "\n";
        prevPerson = per;
        list.Next();
        sortPerson->RemoveFront();
    }
    std::cout << "\nThe Total time taken for washing clothes of all 20 people are: " << timeTotal << "\n";
}

//---- Function to determine the highest priority for Simulation 2 ----
Person highPriorityPerson(List<Person> *list){
    int highest = 0;
    Person newHigh;
    List<Person> *temp = list;
    ListIterator<Person> list1 = temp;
    while (!list1.IsDone()) {
        Person per = list1.Item();
        if (per.getPersonPriority() >=  highest) {
            newHigh = per;
            highest = per.getPersonPriority();
        }
        list1.Next();
    }
    return newHigh;
}
//---- Simulation 2 ----
void simulation2(int numb){
    List<Person> *newPerson = new List<Person>();
    int seq = 0;
    int timeTotal = 0;
    //---- Generation 20 Persons
    for(int i=0; i<numb; i++){
        Person per(seq++, rand()%10, rand()%30, rand()%50);
        newPerson->Append(per);
    }
    //----Printing the Person oreder ----
    std::cout << "\n*************** Simulation 2 Running *******************\n \n Laundry line up according to priority \n \n Highest Priority = 0 Lowest Priority = 9 \n\n";
    ListIterator<Person> list = newPerson;
    newPerson->Apply(print);
    std::cout << "\n____________Simulation 2 begins.....______________\n\n";
    int order = 0;
    Person prevPerson;
    while(!list.IsDone() && newPerson->NumInList()!=0){
        Person current = highPriorityPerson(newPerson);
        timeTotal += current.getTimeWash();
        std::cout << "The order is " << order++ << ": ";
        print(current);
        if(prevPerson.getPersonSequence() != NULL)
            std::cout << "Person with the sequence number " << prevPerson.getPersonSequence() << " leaves the room. This person took a total time of " << prevPerson.getTimeWash() << " to finish washing all the clothes.\n";
        else
        std::cout << "\n";
        newPerson->Remove(current);
//	list.Next();
        prevPerson = current;

    }
    std::cout << "\nThe total time taken for washing clothes of all 20 people are: " << timeTotal  << "\n";
}

 // -----------------------Lab Assignment 3 ------------------------------------------------

//Declaring global variables required.
int n = 0;
Request *req;
int i;
Bitmap *bm = new Bitmap(20);
List<Request *> *grantedRequests = new List<Request *>();
List<Request *> *discardedRequests = new List<Request *>();
List<int> *seatNo = new List<int>;
List<Thread *> *cityB = new List<Thread *>();
List<Thread *> *cityC = new List<Thread *>();
List<Thread *> *cityD = new List<Thread *>();
List<Thread *> *cityE = new List<Thread *>();
int probability;
void reserveSeat(int threadID){

    char cities[] = {'A','B','C','D','E'};

    req = new Request();

    req->setRequestId(rand()%100);

    req->setNumPassengers((rand()%5)+1);

    req->setDepartureCity(cities[i]);

    probability = (rand()%100);

    int s[req->getNumberOfPassengers()];
	
//Assigning destination city based on probability generated for random numbers.
    switch (req->getDepartureCity()){
        case 'A': if(probability>0 && probability<=25){
                req->setDestinationCity(cities[1]);
            }
            else if(probability>25 && probability<50){
                req->setDestinationCity(cities[2]);
            }
            else if(probability>50 && probability<75){
                req->setDestinationCity(cities[3]);
            }
            else{
                req->setDestinationCity(cities[4]);
            }
            break;

        case 'B': if(probability>0 && probability<=35){
                req->setDestinationCity(cities[2]);
            }
            else if(probability>35 && probability<=75){
                req->setDestinationCity(cities[3]);
            }
            else if(probability>75 && probability<=100){
                req->setDestinationCity(cities[4]);
            }
            break;

        case 'C': if(probability>0 && probability<=50){
                req->setDestinationCity(cities[3]);
            }
            else if(probability>50 && probability<=100){
                req->setDestinationCity(cities[4]);
            }
            break;

        case 'D': req->setDestinationCity(cities[4]);
            break;

        default: req->setDestinationCity(cities[4]);
    }

//Displaying the required details for each request.
    cout << " The departure City is: " << req->getDepartureCity() << "\n";
    cout << " The Request ID is: " << req->getRequestId() << "\n";
    cout << " Number of Passengers for this request is: " << req->getNumberOfPassengers() << "\n";
    cout << " The destination city for this request is: " << req->getDestinationCity() << "\n";
//Checking if seats are available in the flight for the current request. If there are seats available, then request is granted else request is discarded.	
    int seatsAvailable = bm->NumClear();
    cout << " The number of seats available at this point are: " << seatsAvailable <<"\n";
    if(bm->NumClear() >= req->getNumberOfPassengers()) {
        cout << " Requests granted. \n";
//Using Bitmap's FindAndSet method to assign seat numbers. 
        for (int m = 0; m < req->getNumberOfPassengers(); m++) {
	    s[m] = bm->FindAndSet();
		cout <<" The seat number is: "<< s[m] << "\n";           
       } 
//Checking if the request is at its current destination, if it is, append it.
        switch(req->getDestinationCity()) {
                case 'B': cityB->Append(kernel->currentThread); cout << "\n";
                        break;
                case 'C': cityC->Append(kernel->currentThread); cout << "\n";
                        break;
                case 'D': cityD->Append(kernel->currentThread); cout << "\n";
                        break;
                case 'E': cityE->Append(kernel->currentThread); cout << "\n";
                        break;
               default : cout << "\nError. Has to be one of the given destination city.\n";

                        break;
        }
//Interrupts are turned off before calling the Sleep or the ReadyToRun functions.
	kernel->interrupt->SetLevel(IntOff);
        kernel->currentThread->Sleep(FALSE);
	int sz = sizeof(s)/(sizeof(s[0]));
	for(int a = 0; a < sz ; a++){
	cout<<" Seat clearing out for Request ID "<<req->getRequestId() <<" is - "<< s[a] << "\n ";	
	}
	kernel->currentThread->Finish();
    }


    else {
        discardedRequests->Append(req);
        cout << "** Flight is full. Request denied**.\n";
	cout << "\n";
	kernel->currentThread->Finish();
	}
}
//The flight function starts here.
void FlightReservation() {
	srand(time(NULL));
//The outer for loop with in the flight function to generate threads and functions for 5 cities.
    for ( i = 0; i < 5; i++) {
        if (i > 0){
	 	cout<<"\n";
//If the departure city is anything other than A, it enters the switch case, the respective cases execute to iterate through the thread list and puts the thread in the ready to run list and starts yielding.
            switch (i) {
                case 1 : {
			    cout << "************************Destination City B*************************************\n";
			    ListIterator<Thread *> *iterReq1 = new ListIterator<Thread *>(cityB);
                            while (!iterReq1->IsDone()) {
				kernel->interrupt->SetLevel(IntOff);
                            kernel->scheduler->ReadyToRun(iterReq1->Item());
    			    kernel->currentThread->Yield();
			    iterReq1->Next(); 

                        }
                        break;
                    }
                case 2 : {  
			    cout << "************************Destination City C*************************************\n";
                            ListIterator<Thread *> *iterReq2 = new ListIterator<Thread *>(cityC);
                            while (!iterReq2->IsDone()){
				kernel->interrupt->SetLevel(IntOff);
                            kernel->scheduler->ReadyToRun(iterReq2->Item());
			    kernel->currentThread->Yield();
			    iterReq2->Next();
				 cout<<"\n";  
                        }
                        break;
                }
                case 3 : {
			    cout << "************************Destination City D*************************************\n";
                            ListIterator<Thread *> *iterReq3 = new ListIterator<Thread *>(cityD);
                            while (!iterReq3->IsDone()){
				kernel->interrupt->SetLevel(IntOff);
                                kernel->scheduler->ReadyToRun(iterReq3->Item());
                                kernel->currentThread->Yield();
				iterReq3->Next();
				 cout<<"\n"; 
                       }
                       break;
                }
                case 4 : {   
			    cout << "********************************************************************************\n";
                            ListIterator<Thread *> *iterReq4 = new ListIterator<Thread *>(cityE);
                            while (!iterReq4->IsDone()){
				kernel->interrupt->SetLevel(IntOff);
                            kernel->scheduler->ReadyToRun(iterReq4->Item());
                            kernel->currentThread->Yield();
				iterReq4->Next();
				// cout<<"\n";
                        }
                        break;
                }
                default : cout << "\n Error.\n ";
            }
		//After each city's execution, the occupancy rate of the flight at that point is calculated and displayed.
		cout << " The occupancy rate is: "<< 20 - (bm->NumClear()) << "/20\n";
		cout<<"\n The available seats are : "; bm->Print();cout<<endl;	
	//A list iterator is declared and defined to iterate through a list of requests that have been discarded and displayed that request's requestID.
	if(i==4){
		ListIterator<Request *> *rejectedRequest = new ListIterator<Request *>(discardedRequests);
		while (!rejectedRequest->IsDone()){
			cout <<" The rejected requests are: " << rejectedRequest->Item()->getRequestId() << "\n";
				rejectedRequest->Next();
			
			}
			kernel->currentThread->Finish();
		}
        }
	
//The inner for loop to generate upto 5 flight threads for each city.
	Thread *flightThread[6];
        for (int j = 1; j <= 5; j++){
           	 flightThread[j] = new Thread("flight thread");
                 flightThread[j]->Fork((VoidFunctionPtr) reserveSeat, (void *) j);
		 kernel->currentThread->Yield();
        }
    }
}

void
ThreadTest()
{
//The main thread object is created and forked which calls the flight function.
    Thread *mainThread = new Thread("main thread");
    mainThread->Fork((VoidFunctionPtr) FlightReservation, (void *) 1);
    kernel->currentThread->Yield();
    //Thread *t = new Thread("forked thread");
    //t->Fork((VoidFunctionPtr) SimpleThread, (void *) 1);
    //---- Calling Simulation 1 ----
    //simulation1(20);
    //---- Calling Simulation 2 ----
    //simulation2(20);
    //SimpleThread(0);
}



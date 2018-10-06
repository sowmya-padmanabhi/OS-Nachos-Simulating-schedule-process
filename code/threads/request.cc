#include "request.h"
#include <stdlib.h>
#include <iostream>

int seat = 0;
void Request ::setNumPassengers(int numOfPass)  {
     numPassenger = numOfPass;
}

int Request :: getNumberOfPassengers() const {
    return numPassenger;
}

void Request :: setDepartureCity(char departureCity) {
	departCity = departureCity;
}

char Request :: getDepartureCity() const {
    return departCity;
}

void Request :: setDestinationCity(char destinationCity) {
    destCity = destinationCity;
}

char Request :: getDestinationCity() const {
    return destCity;
}

int Request :: setRequestId(int requestID) {
    reqID = requestID;
}

int Request :: getRequestId() const {
    return reqID;
}

void Request ::setSeatNumbers(int seatNumbers) {
    seatNum[seat]=seatNumbers;
	seat++;
}
int Request ::getSeatNumbers(int newseat) const {
    return seatNum[newseat];
}

int Request :: seatarray_size(){
	int seatsize = sizeof(seatNum)/sizeof(seatNum[0]);
	return seatsize;
}
Request::Request() {
//    cout << "Constructor";
}

Request::~Request() {
  //  cout << "Destructor";
}



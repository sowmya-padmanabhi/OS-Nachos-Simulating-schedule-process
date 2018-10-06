//
// Created by sowmya on 9/29/2018.
//

#ifndef NACHOS_REQUEST_H
#define NACHOS_REQUEST_H

#include "../lib/list.h"


class Request{

private:
    int reqID;
    int numPassenger;
    int * seatNum;
    char departCity;
    char destCity;
//    List<int> seatsNumb;

public:
    // Declaring the methods required.

    Request();
    ~Request();

    int setRequestId(int requestID);
    int getRequestId() const;

    void setNumPassengers(int numOfPass);
    int getNumberOfPassengers() const;

    void setSeatNumbers(int seatNumbers);
    int  getSeatNumbers(int i) const;

    void setDepartureCity(char departureCity);
    char getDepartureCity() const ;

    void setDestinationCity(char destinationCity);
    char getDestinationCity() const ;

    int seatarray_size();

    List<int> *seatsNumb = new List<int>(); 

    friend void FlightReservation();
    friend void  reserveSeat(int ID);
};
    void FlightReservation();
    void  reserveSeat(int ID);


#endif // NACHOS_REQUEST_H


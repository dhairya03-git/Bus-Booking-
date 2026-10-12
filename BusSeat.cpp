#include<iostream>
#include<fstream>
#include<string>
using namespace std;

const int TOTAL_SEATS = 20;

struct Info{
    string name;
    int seatNum;
};

Info s[TOTAL_SEATS];
int total = 0;

void loadBookings(){
    ifstream file("BusTicket/bus.txt");
    string name;
    int seat;

    total = 0;

    while(getline(file,name)){
        if(!(file>>seat))
            break;

        file.ignore();

        if(seat>=1 && seat<=TOTAL_SEATS && total<TOTAL_SEATS){
            bool duplicate = false;

            for(int i=0;i<total;i++){
                if(s[i].seatNum==seat){
                    duplicate = true;
                    break;
                }
            }

            if(!duplicate){
                s[total].name = name;
                s[total].seatNum = seat;
                total++;
            }
        }
    }

    file.close();
}

void saveBookings(){
    ofstream file("BusTicket/bus.txt");

    for(int i=0;i<total;i++){
        file<<s[i].name<<endl;
        file<<s[i].seatNum<<endl;
    }

    file.close();
}

int findSeat(int seat){
    for(int i=0;i<total;i++){
        if(s[i].seatNum==seat)
            return i;
    }

    return -1;
}

void showSeats(){
    cout<<"_______ BUS SEAT LAYOUT _______"<<endl;
    for(int seat=1;seat<=TOTAL_SEATS;seat++){
        if(findSeat(seat)!=-1)
            cout<<"[ X ]";
        else
            cout<<"[ "<<seat<<" ]";

        if(seat%2==0)
            cout<<endl;
        else
            cout<<"  ";
    }

    cout<<"______________"<<endl;
    cout<<"X = Booked Seat"<<endl;
}

void showBookings(){
    cout<<"_______ ALL BOOKINGS _______"<<endl;
    if(total==0){
        cout<<"No bookings found!"<<endl;
        return;
    }

    for(int i=0;i<total;i++){
        cout<<"Name: "<<s[i].name<<endl;
        cout<<"Seat: "<<s[i].seatNum<<endl;
        cout<<"----------------------------------"<<endl;
    }
}

void showAvailability(){
    cout<<"\nTotal Seats: "<<TOTAL_SEATS<<endl;
    cout<<"Booked Seats: "<<total<<endl;
    cout<<"Available Seats: "<<TOTAL_SEATS-total<<endl;
}

void bookTicket(){
    int n;
    showSeats();
    cout<<"Enter number of passengers: ";
    if(!(cin>>n)){
        cin.clear();
        cin.ignore();
        cout<<"Invalid input!"<<endl;
        return;
    }
    if(n<=0){
        cout<<"Enter a valid passenger count!"<<endl;
        return;
    }
    if(n>TOTAL_SEATS-total){
        cout<<"Only "<<TOTAL_SEATS-total<<" seats are available!"<<endl;
        return;
    }
    for(int j=0;j<n;j++){
        string name;
        int seat;

        cin.ignore();

        cout<<"Enter passenger name: ";
        getline(cin,name);

        while(true){
            cout<<"Enter seat number (1-"<<TOTAL_SEATS<<"): ";

            if(!(cin>>seat)){
                cin.clear();
                cin.ignore();
                cout<<"Invalid input! Enter a number."<<endl;
                continue;
            }

            if(seat<1 || seat>TOTAL_SEATS){
                cout<<"Seat number must be between 1 and "<<TOTAL_SEATS<<"!"<<endl;
            }
            else if(findSeat(seat)!=-1){
                cout<<"Seat already booked! Choose another."<<endl;
            }
            else{
                break;
            }
        }

        s[total].name = name;
        s[total].seatNum = seat;
        total++;

        cout<<"Seat selected successfully!"<<endl;
    }

    saveBookings();
    cout<<"Booking completed successfully!"<<endl;
}

void searchBooking(){
    int seat;

    cout<<"Enter seat number to search: ";

    if(!(cin>>seat)){
        cin.clear();
        cin.ignore();
        cout<<"Invalid input!"<<endl;
        return;
    }

    int index = findSeat(seat);

    if(index==-1){
        cout<<"No booking found for this seat."<<endl;
    }
    else{
        cout<<"Passenger Name: "<<s[index].name<<endl;
        cout<<"Seat Number: "<<s[index].seatNum<<endl;
    }
}

void cancelBooking(){
    int seat;

    cout<<"Enter seat number to cancel: ";

    if(!(cin>>seat)){
        cin.clear();
        cin.ignore();
        cout<<"Invalid input!"<<endl;
        return;
    }

    int index = findSeat(seat);

    if(index==-1){
        cout<<"This seat is not booked!"<<endl;
        return;
    }

    cout<<"Booking cancelled for: "<<s[index].name<<endl;

    for(int i=index;i<total-1;i++){
        s[i] = s[i+1];
    }

    total--;
    saveBookings();

    cout<<"Seat "<<seat<<" is now available."<<endl;
}

int main(){
    loadBookings();

    while(true){
        cout<<"____________________________"<<endl;
        cout<<"  ARYA COLLEGE BUS SERVICES"<<endl;
        cout<<"____________________________"<<endl;
        cout<<"1. View Seat Layout"<<endl;
        cout<<"2. Book Ticket"<<endl;
        cout<<"3. View All Bookings"<<endl;
        cout<<"4. Search Booking"<<endl;
        cout<<"5. Cancel Booking"<<endl;
        cout<<"6. Check Seat Availability"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"____________________________"<<endl;
        cout<<"Enter your choice: ";

        int choice;
        if(!(cin>>choice)){
            cin.clear();
            cin.ignore();
            cout<<"Invalid input! Enter a menu number."<<endl;
            continue;
        }
        switch(choice){
            case 1:
                showSeats();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                showBookings();
                break;
            case 4:
                searchBooking();
                break;
            case 5:
                cancelBooking();
                break;
            case 6:
                showAvailability();
                break;
            case 0:
                cout<<"Thank you for using Arya College Bus Services!"<<endl;
                return 0;
            default:
                cout<<"Invalid choice! Select 0-6."<<endl;
        }
    }
    return 0;
}

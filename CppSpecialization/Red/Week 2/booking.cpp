#include <iostream>
#include <stdint.h>
#include <string>
#include <map>
#include <queue>
// #include "test_runner.h"
using namespace std;

struct bookingEvent_t {
    string hotelName;
    int64_t clientID;
    int64_t roomCount;
    int64_t time;
};

class Hotel {
private:
    map<int, int> roomsByClients;

    int64_t clientsNumber = 0;
    int64_t roomsNumber = 0;
public:
    Hotel() {
        clientsNumber = 0;
        roomsNumber = 0;
    };

    ~Hotel() {};
    void AppendClient(int64_t clientID, int64_t roomCount){
        if (roomCount == 0)
            return;
        roomsNumber += roomCount;
        auto client = roomsByClients.find(clientID);
        if (client == roomsByClients.end()){
            clientsNumber++;
            roomsByClients[clientID] = roomCount;
        } else if (client->second == 0) {
            clientsNumber++;
            client->second = roomCount;
        } else {
            client->second += roomCount;
        }
    }
    void DeleteClient(int64_t clientID, int64_t roomCount){
        roomsNumber -= roomCount;
        roomsByClients[clientID] -= roomCount;
        if (roomsByClients[clientID] == 0)
            clientsNumber--;
    }
    int64_t GetClientsNumber(){ return clientsNumber; }
    int64_t GetRoomsNumber(){ return roomsNumber; }
};

class Booking {
private:
    queue<bookingEvent_t> events;
    map<string, Hotel> hotels;

    const int64_t dayTime = 86400;
    bool CheckTime(int64_t time){
        int64_t currentTime = events.back().time;
        return ((currentTime - dayTime) < time) && (time <= currentTime);
    }

    void DeleteOldEvents(){
        while (!events.empty()){
            auto event = events.front();
            if (!CheckTime(event.time)){
                hotels[event.hotelName].DeleteClient(event.clientID, event.roomCount);
                events.pop();
            } else {
                return;
            }
        }
    }
public:
    Booking(){};

    void AddClient(int64_t time, const string &hotel_name, int64_t client_id, int64_t room_count){
        bookingEvent_t newEvent = {hotel_name, client_id, room_count, time};
        events.push(newEvent);
        hotels[hotel_name].AppendClient(client_id, room_count);
        DeleteOldEvents();
    }

    int64_t GetHotelClients(const string &hotel_name){
        auto hotel = hotels.find(hotel_name);
        return (hotel == hotels.end()) ? 0 : hotel->second.GetClientsNumber();
    }
    
    int64_t GetHotelRooms(const string &hotel_name){
        auto hotel = hotels.find(hotel_name);
        return (hotel == hotels.end()) ? 0 : hotel->second.GetRoomsNumber();
    }
};

// void Test1(){
//     Booking b;
    
//     ASSERT_EQUAL(b.GetHotelRooms("Marriott"), 0);
//     ASSERT_EQUAL(b.GetHotelClients("Marriott"), 0);

//     b.AddClient( 10,"FourSeasons", 1, 2);
//     b.AddClient( 10,"Marriott", 1 , 1);
//     b.AddClient( 86409,"FourSeasons", 2, 1);

//     ASSERT_EQUAL(b.GetHotelClients("FourSeasons"), 2);
//     ASSERT_EQUAL(b.GetHotelRooms("FourSeasons"), 3);
//     ASSERT_EQUAL(b.GetHotelClients("Marriott"), 1);
    
//     b.AddClient( 86410,"Marriott", 2, 10);
//     ASSERT_EQUAL(b.GetHotelRooms("FourSeasons"), 1);
//     ASSERT_EQUAL(b.GetHotelRooms("Marriott"), 10);
// }

// void Test2(){
//     Booking b;
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 0);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel2"), 0);
    
//     b.AddClient(0, "hotel1", 0, 10);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 1);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 10);

//     b.AddClient(0, "hotel1", 1, 2);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 2);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 12);

//     b.AddClient(0, "hotel1", 0, 2);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 2);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 14);

//     b.AddClient(86399, "hotel1", 10, 1);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 3);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 15);

//     b.AddClient(86400, "hotel1", 11, 2);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 2);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 3);

//     b.AddClient(86401, "hotel1", 12, 10);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 3);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 13);
// }

// void Test3(){
//     Booking b;
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 0);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel2"), 0);
    
//     b.AddClient(0, "hotel1", 0, 1);
//     b.AddClient(0, "hotel2", 0, 1);
//     b.AddClient(0, "hotel2", 1, 3);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 1);
//     ASSERT_EQUAL(b.GetHotelClients("hotel2"), 2);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 1);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel2"), 4);
    
//     b.AddClient(86410, "hotel3", 3, 10);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 0);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 0);
//     ASSERT_EQUAL(b.GetHotelClients("hotel2"), 0);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel2"), 0);
//     ASSERT_EQUAL(b.GetHotelClients("hotel3"), 1);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel3"), 10);
// }

// void Test4(){
//     Booking b;

//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 0);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 0);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel2"), 0);
//     ASSERT_EQUAL(b.GetHotelClients("hotel3"), 0);

//     b.AddClient( -100000,"hotel1",100000,1000 );
//     b.AddClient( -100000,"hotel1",100003,1000 );
//     b.AddClient( -100000,"hotel2",100002,1000 );
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 2000);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 2);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel2"), 1000);
//     ASSERT_EQUAL(b.GetHotelClients("hotel2"), 1);

//     b.AddClient( 1000000,"hotel1",100001,1000 );
//     b.AddClient( 1000000,"hotel1",100002,1000 );
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 2000);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 2);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel2"), 0);
//     ASSERT_EQUAL(b.GetHotelClients("hotel2"), 0);
// }

// void Test5(){
//     Booking b;
    
//     b.AddClient(0, "hotel1", 0, 1);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 1);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 1);

//     b.AddClient(100000, "hotel2", 0, 1);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 0);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 0);
    
//     b.AddClient(200000, "hotel1", 0, 2);
//     ASSERT_EQUAL(b.GetHotelClients("hotel1"), 1);
//     ASSERT_EQUAL(b.GetHotelRooms("hotel1"), 2);
// }

int main(){
//     Test1();
//     Test2();
//     Test3();
//     Test4();
//     Test5();
    unsigned int q;
    cin >> q;

    string cmd, hotel_name;
    int64_t time;
    int64_t client_id, room_count;
    Booking book;
    for (int i = 0; i < q; ++i){
        cin >> cmd;
        if (cmd == "BOOK") {
            cin >> time >> hotel_name >> client_id >> room_count;
            book.AddClient(time, hotel_name, client_id, room_count);
        } else if (cmd == "CLIENTS"){
            cin >> hotel_name;
            cout << book.GetHotelClients(hotel_name) << endl;
        } else if (cmd == "ROOMS"){
            cin >> hotel_name;
            cout << book.GetHotelRooms(hotel_name) << endl;
        }
    }

    return 0;
}
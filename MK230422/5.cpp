#include <iostream>

class Car {
    int number;
    int order;
    static int next;
public:
    Car(int id) : number(id), order(-1) {}
    void entersTrack() {
        order = next;
        ++next;
    }
    int getNumber() const { return number; }
    int getOrder() const { return order; }

    bool operator<(const Car& masik) const {
        return this->order < masik.order;
    }
};

int Car::next = 1;

std::ostream& operator<<(std::ostream& os, const Car& car) {
    return os << car.getNumber() << " " << car.getOrder();
}

int main() {
    using namespace std;

    Car c2(999);
    Car c3(2000);
    c1.entersTrack();
    c3.entersTrack(); //a 2000-s azonosítójú autó másodikként lép pályára
    c2.entersTrack();
    cout << c3; //(*) Kiirjuk c3 adatait: "Car #2000 entered the track as the 2. car"
    if (c3 < c2) //(**) Ha c3 előbb került pályára, mint c2
    {
    cout << c3.getNumber() << " entered the track earlier.";
    }
}

class Room{};
class Owner{};

class House{
private:
    Room* livingroom;
    Room* bedroom;
    Owner* landlord;
public:
    House(Owner* landlord)
    {
        livingroom = new Room{};
        bedroom = new Room{};
        this->landlord = landlord;
    }
    ~House()
    {
        delete livingroom;
        delete bedroom;
    }
};
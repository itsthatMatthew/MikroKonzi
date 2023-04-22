class Centipede {
    static int legCount;
    //...
public:
    static void setLegCount(int uj)
    {
        if (uj % 2 == 0) {
            legCount = uj;
        }
    }
    //...
};

Centipede::setLegCount(101);
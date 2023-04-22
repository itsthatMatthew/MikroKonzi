#include <iostream>
#include <vector>

class Spray {
    int type;
    bool used;
public:
    Spary(int t = 0) : type(t), used(false) {}
    void vaporize() {
        if (!used) {
            std::cout << "Permet: " << type << std::endl;
        }
        else {
            used = true;
            std::cout << "Mar felhasznaltak" << std::endl;
        }
    }
};

class Tractor {
    Spray* tarolt;
    size_t meret;
public:
    Tractor() : tarolt(nullptr), meret(0) {}
    void addSpray(Spray s) {
        Spray* uj_tarolo = new Spray[++meret];
        for (size_t idx = 0; idx != meret - 1; ++idx)
            uj_tarolo[idx] = tarolt[idx];
        uj_tarolo[meret - 1] = s;
        delete[] tarolt;
        tarolt = uj_tarolo;
    }
    Spray& operator[](size_t idx) {
        return tarolt[idx];
    }
    ~Tractor() {
        if (tarolt != nullptr) {
            delete[] tarolt;
        }
    }

    Tractor(const Tractor&) = delete;
    Tractor& operator=(const Tractor&) = delete;
};

int main() {
    Tractor zetor;
    Spray s1(1); //1-es tipus, pl. csigaolo permet
    Spray s2(2); //2-es tipus, pl. bekataszito permet
    zetor.addSpray(s1);
    zetor.addSpray(s2);
    zetor[0].vaporize(); //(*) “Permet: 1”
    //A túlcímzéssel nem kell foglalkoznunk.
    zetor[0].vaporize(); // “Mar felhasznaltak.”
    zetor[1].vaporize(); //”Permet: 2”
}
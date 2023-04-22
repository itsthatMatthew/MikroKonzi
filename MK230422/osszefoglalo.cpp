// 2. MikroKonzi villanyos ZH-ra készüléshez
// jelige: most eskü megpróbálom nem 4 óráig kihúzni
// Pozsi: inkább "nem ígérem, hogy nem fogom 4 óráig kihúzni"

// 1.a típusértékű struct, enum, bool
{
    struct osszefoglalo
    {
        /* data */
    };

    enum { pelda1, pelda2 };

    bool igaz = true;
    igaz = false;
}

// 1.b függvényhívások, prototípusok, referenciák
{
    void foo(const int& a) {
        std::cout << a;
    }

    foo(4);
}

// 2.a függvénynév túlterhelés
{
    void foo(int a);
    void foo(double a);
    float foo(float a);

    foo(1);
    foo(0.1);
}

// 2.b default függvényargumentumok
{
    void foo(int a, int b = 0, int c = 3);

    foo(1);
}

// 2.c makrók kiváltása inline függvényekkel
{
    //#define MAX(int x, int y) { x > y ? return x : return y; }
    inline int MAX(int x, int y) { x > y ? return x : return y; }

    int a = 1;
    int b = 0;

    MAX(++a, ++b);
}

// 2.d névterek, láthatóság
{
    #include <string>

    class string { /*...*/};

    std::string a;

    namespace nevterem
    {
        void foo();
    } // namespace nevterem
    
    nevterem::foo();
}

// 2.e memóriakezelés és kivétel kezelés
{
    size_t n = 0;
    //...
    int* egyetlen = new int(0); // new
    int* tomb = new int[n]; // new[]

    delete egyetlen; // new
    delete[] tomb; // new[]

    void hibas_fuggvenyunk() {
        throw "ABC123";
    }

    try {
        // ...
        hibas_fuggvenyunk();
        // más kód
    }
    catch (const char* neptun) {
        std::cout << neptun;
    }
}

// 3.a osztály, objektum
{
    struct Struktura {
    
    };

    class Osztaly {

    };

    Osztaly objektum;
}

// 3.b egységbezárás, láthatóság és információrejtés, tagváltozók és
// tagfüggvények, getterek és setterek, a this pointer
{
    struct Struktura {
    public:
        int a;
        void foo() {
            this->a = 3;
        }
    private:
        int privat;
    };

    Struktura s;
    s.foo(); // this = &s

    class Osztaly {
    private:
        int b;
    public:
        int get_b() { return b; }
    };


    Osztaly o;
    o.get_b();
    
}

// 3.c konstruktor, destruktor
{
    class Osztaly {
        int a, b, c;
    public:
        Osztaly(int a, int b, int c) {
            this->a = a;
            this->b = b;
            this->c = c;
        }

        ~Osztaly() {
        }
    };

    Osztaly o1(1, 2, 3);
    Osztaly specialis{1, 2, 3};
    Osztaly o2 = Osztaly(1, 2, 3);
}

{
    int tomb[10] = {0};
    // int*
}

// 4.a konstruktor és destruktor, dinamikus adatokat karban tartó osztályok
{
    class DinTomb {
        int* ptr;
        size_t meret;
    public:
        DinTomb() {
            meret = 0;
            ptr = nullptr;
        }
        Felvesz(int a) {
            ptr = new int[++meret];
        }
        //...
        ~DinTomb() { // RAII
            if (ptr != nullptr)
                delete[] ptr;
        }
    };

    DinTomb tomb{};
    //...
    // tomb.~DinTom();
}

// 4.b másoló konstruktor és értékadás
{
    class DinTomb {
        int* ptr;
        size_t meret;
    public:
        DinTomb() {
            meret = 0;
            ptr = nullptr;
        }
        
        ~DinTomb() { // RAII
            if (ptr != nullptr)
                delete[] ptr;
        }

        DinTomb(const DinTomb& masik) {
            meret = masik.meret;
            ptr = new int[meret];
            for (size_t idx = 0; idx != meret; idx++)
                ptr[idx] = masik.ptr[idx];
        }

        DinTomb& operator=(const DinTomb& masik) {
            if (this != &masik) {
                if (ptr != nullptr)
                    delete[] ptr;
                meret = masik.meret;
                ptr = new int[meret];
                for (size_t idx = 0; idx != meret; idx++)
                    ptr[idx] = masik.ptr[idx];
            }
            return *this;
        }
    };

    DinTomb tomb1{};

    DinTomb tomb2 = tomb1;
    DinTomb tomb3;

    tomb1 = tomb1;
    tomb1 = tomb2;
    tomb3 = (tomb2 = tomb1);
}

// 4.c tagváltozók inicializálása
{
    class Osztaly {
        int a, b, c;
    public:
        Osztaly()
            : a(0), b(0), c(0)
        {
        }

        Osztaly(int x, int y, int z)
            : a(x), b(y), c(z)
        {
            int r = a;
        }
    };

    Osztaly objektum{1, 2, 3};
}

// 4.d konstans és statikus adattagok
{
    class Osztaly {
        static int s;
        const int c;
    public:
        Osztaly()
            : c(s)
        {
            
        }

        static void foo() {/*...*/}
    };

    int Osztaly::s = 0;

    Osztaly objektum;
    //objektum.foo();
    Osztaly::foo();
}

// 5.a friend mechanizmus
{
    class Osztaly {
        int a;
    public:
        void foo() { a = 3; }
        friend void bar(Osztaly o);
    };

    void bar(Osztaly o) { o.a = 2; }
}

// 5.b operátorok túlterhelése,
// megvalósítása tagfüggvénnyel és globális függvénnyel
{
    class DinTomb {
    public:
        int& operator[](size_t idx)
        {
            return ptr[idx];
        }
        const int operator[](size_t idx) const
        {
            return ptr[idx];
        }
    };

    DinTomb tomb;
    tomb[0] = 3;
    
    const DinTomb const_tomb{/**/};

    const int ct = const_tomb[1];
}

// 6.a öröklés, származtatott osztály, alaposztály
{
    class Os_osztaly {
    public:
        void foo() {}
    };

    class Leszarmazott_osztaly : public Os_osztaly {
        
    };

    Leszarmaztatott_osztaly leszarmazott{};
    leszarmazott.foo(); // Osnek foo-ja
}

// 6.b az öröklés hatása a láthatóságra
{
    class Os_osztaly {
    private:
        int x;
    protected:
        int a;
    public:
        void foo() {}
    };

    class Leszarmazott_osztaly : public Os_osztaly {
    public:
        void foo() { a = 2; }
    };

    Leszarmaztatott_osztaly leszarmazott{};
    leszarmazott.foo(); // a = 2 -> leszarmazotte
}

// 6.c konstruktorok és az öröklés
{
    class Os_osztaly {
    private:
        int x;
    public:
        Os_osztaly(int a) : x(a) {}
    };

    class Leszarmazott_osztaly : public Os_osztaly {
    public:
        Leszarmazott_osztaly(int a)
            : Os_osztaly(a)
        {

        }
    };


}
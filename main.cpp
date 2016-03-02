#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Zwierze {
public:
    virtual void daj_glos() = 0;
    virtual ~Zwierze() {};
};


class ZwierzeKreator {
public:
    virtual Zwierze* tworz() = 0;
    virtual ~ZwierzeKreator() {};
};

class FabrykaZwierzat {
private:
    vector<ZwierzeKreator*> kreatory;
public:
    void nowy_gatunek(ZwierzeKreator* kreator) {
        kreatory.push_back(kreator);
    }
    Zwierze* tworz() {
        uint32_t index = rand() % (kreatory.size());
        return kreatory.at(index)->tworz();
    }
    ~FabrykaZwierzat() {
        //zwolnij pamiec zajata przez kreatory
        for(uint32_t i = 0; i < kreatory.size();i++) {
            delete kreatory.at(i);
        }
        //wyczysc vektor
        kreatory.clear();
    }
};

class Kon : public Zwierze{
public:
    virtual void daj_glos() {
        cout<<"Iha Iha"<<endl;
    }
};

class KonKreator: public ZwierzeKreator {
public:
    virtual Zwierze* tworz() {
        return new Kon();
    }
};

class Krowa: public Zwierze {
public:
    virtual void daj_glos() {
        cout<<"Muu Muu"<<endl;
    }
};

class KrowaKreator: public ZwierzeKreator {
public:
    virtual Zwierze* tworz() {
        return new Krowa();
    }
};

int main()
{
    srand(time(NULL));
    vector<Zwierze*> zoo;
    FabrykaZwierzat fabryka;
    //dodaj kreatory zwierzat do fabryki
    fabryka.nowy_gatunek(new KonKreator());
    fabryka.nowy_gatunek(new KrowaKreator());
    //tworz zwierzaki
    for(uint32_t i = 0; i< 20; i++) {
        zoo.push_back(fabryka.tworz());
    }
    //daj glos kazdego zwierzaka
    for(uint32_t i = 0; i< zoo.size(); i++) {
        zoo.at(i)->daj_glos();
    }
    //wyczysc pamiec zwierzakow
    for(uint32_t i = 0; i< zoo.size(); i++) {
        delete zoo.at(i);
    }
    zoo.clear();
    return 0;
}

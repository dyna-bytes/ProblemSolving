#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define endl '\n'
#define debug(x) cout << "[debug] " << #x << " is " << x << endl

struct Car {
    string carName;
    int primeCost;
    int initialRentalCost;
    int costPerDist;
};

struct Spy {
    string spyName;
    Car* car;
    int pickupTime;
    int returnTime;
    int accidentTime;
    int cost = 0;
    void init() {
        car = nullptr;
        pickupTime = returnTime = accidentTime = -1;
    }
    bool setPickupTime(int pickupTime, Car* car) {
        if (cost == -1 || this->car) {
            cost = -1;
            return false;
        }
        
        this->car = car;
        this->pickupTime = pickupTime;
        cost += car->initialRentalCost;
        return true;
    }
    bool setReturnTime(int returnTime, int dist) {
        if (cost == -1 || this->pickupTime == -1 || 
        this->pickupTime > returnTime ||
        this->accidentTime > returnTime) {
            cost = -1;
            return false;
        }

        this->returnTime = returnTime;
        cost += dist * car->costPerDist;

        this->init();
        return true;
    }
    bool setAccidentTime(int accidentTime, int damage) {
        if (cost == -1 || this->pickupTime == -1 ||
        this->pickupTime > accidentTime) {
            cost = -1;
            return false;
        }

        cost += ceil((double)damage * car->primeCost / 100);
        return true;
    }
};

int N, M;
unordered_map<string, Car*> carDB;
map<string, Spy*> spyDB;
void init() {
    carDB = {};
    spyDB = {};
}
void input() {
    cin >> N >> M;
    string car_name;
    int p, q, k;
    for (int i = 0; i < N; i++) {
        cin >> car_name >> p >> q >> k;
        Car* car = new Car();
        car->carName = car_name;
        car->primeCost = p;
        car->initialRentalCost = q;
        car->costPerDist = k;

        carDB[car_name] = car;
    }
    int time, d;
    string spy_name;
    Spy* spy;
    char e;
    for (int i = 0; i < M; i++) {
        cin >> time >> spy_name >> e;
        if (e == 'p') {
            cin >> car_name;
            if ((spy = spyDB[spy_name]) == nullptr) {
                spy = spyDB[spy_name] = new Spy();
                spy->init();
            }

            spy->spyName = spy_name;
            spy->setPickupTime(time, carDB[car_name]);
        } else if (e == 'r') {
            cin >> d;
            if ((spy = spyDB[spy_name]) == nullptr) {
                spy = spyDB[spy_name] = new Spy();
                spy->init();
            }

            spy->setReturnTime(time, d);
        } else if (e == 'a') {
            cin >> d;
            if ((spy = spyDB[spy_name]) == nullptr) {
                spy = spyDB[spy_name] = new Spy();
                spy->init();
            }

            spy->setAccidentTime(time, d);
        }
    }
}

void solve() {
    for (auto [name, spy_p]: spyDB) {
        cout << name << ' ';
        if (spy_p->cost == -1 || spy_p->car) cout << "INCONSISTENT" << endl;
        else cout << spy_p->cost << endl;
    }
}

int main() {
    FASTIO;
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        init();
        input();
        solve();
    }
    return 0;
}
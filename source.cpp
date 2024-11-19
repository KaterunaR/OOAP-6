#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <random>
using namespace std;

class Counter {
private:
    int foodCount = 0;
    int medicineCount = 0;
    int clothesCount = 0;
    double total = 0.0;
    ofstream MyFile;

    Counter() {
        MyFile.open("file.txt", ios::app);
        if (!MyFile.is_open()) {
            cerr << "Error opening file!" << endl;
            exit(1);
        }
        cout << "File opened successfully." << endl;
    }

    ~Counter() {
        if (MyFile.is_open()) {
            MyFile.close();
        }
    }

    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;

    string getCurrentTime() {
        time_t now = time(nullptr);
        tm localTime;
        localtime_s(&localTime, &now);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
        return string(buffer);
    }

public:
    static Counter& getObject() {
        static Counter obj;
        return obj;
    }

    void addSale(const string& category, double startPrice) {
        double finalPrice = startPrice;

        if (category == "food") {
            finalPrice += startPrice * 0.05;
            foodCount++;
        }
        else if (category == "medicine") {
            finalPrice += startPrice * 0.10;
            medicineCount++;
        }
        else if (category == "clothes") {
            finalPrice += startPrice * 0.15;
            clothesCount++;
        }

        total += finalPrice;


        MyFile << getCurrentTime() << " - Sold " << category << " for $" << finalPrice << endl;
        cout << getCurrentTime() << " - Sold " << category << " for $" << finalPrice << endl;

    }

    void showResult() const {
        cout << "Sales report:" << endl;
        cout << "Food sold: " << foodCount << endl;
        cout << "Medicine sold: " << medicineCount << endl;
        cout << "Clothes sold: " << clothesCount << endl;
        cout << "Total: $" << total << endl;
    }
};

double generateRandomPrice() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_real_distribution<> dis(10, 200);
    return dis(gen);
}


int main() {
    Counter& counter = Counter::getObject();
    Counter& counter2 = Counter::getObject();

    counter.addSale("food", generateRandomPrice());
    counter.addSale("medicine", generateRandomPrice());
    counter.addSale("clothes", generateRandomPrice());
    counter2.addSale("clothes", generateRandomPrice());

    counter.showResult();
    counter2.showResult();

    return 0;
}

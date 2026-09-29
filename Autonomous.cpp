#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Base Abstract Class
class BaggageTerminal {
protected:
    string terminalID;
    int bagsProcessed;

public:
    static int activeTerminals;
    static double totalWeightProcessedKG;

    BaggageTerminal(string id, int bags)
        : terminalID(id), bagsProcessed(bags) {
        activeTerminals++;
    }

    virtual ~BaggageTerminal() {
        cout << "[TERMINAL SHUTDOWN] Terminal " << terminalID << " conveyor powered off." << endl;
        activeTerminals--;
    }

    // Pure Virtual Interfaces
    virtual double calculateEfficiencyScore() const = 0;
    virtual void printConveyorReport() const = 0;
};

// Static initializations outside class boundary
int BaggageTerminal::activeTerminals = 0;
double BaggageTerminal::totalWeightProcessedKG = 0.0;

// Derived Class 1: Passenger Luggage Carousel
class PassengerCarousel : public BaggageTerminal {
private:
    double averageBagWeightKG;
    int lostBaggageFlags;

public:
    PassengerCarousel(string id, int bags, double avgWeight, int lostFlags)
        : BaggageTerminal(id, bags),
          averageBagWeightKG(avgWeight),
          lostBaggageFlags(lostFlags) {
        totalWeightProcessedKG += (bags * avgWeight);
    }

    ~PassengerCarousel() override {
        cout << " -> Locking optical bag scanners for " << terminalID << "..." << endl;
    }

    double calculateEfficiencyScore() const override {
        if (bagsProcessed == 0) return 0.0;
        // Lost bags penalize the carousel performance score
        double score = 100.0 - (lostBaggageFlags * 12.5);
        return (score < 0.0) ? 0.0 : score;
    }

    void printConveyorReport() const override {
        cout << "\n==============================================" << endl;
        cout << "   PASSENGER LUGGAGE CAROUSEL: " << terminalID << endl;
        cout << "==============================================" << endl;
        cout << "  Bags Processed       : " << bagsProcessed << endl;
        cout << "  Average Bag Weight   : " << fixed << setprecision(1) << averageBagWeightKG << " kg" << endl;
        cout << "  Lost Luggage Incidents: " << lostBaggageFlags << endl;
        cout << "  Carousel Efficiency  : " << fixed << setprecision(2) << calculateEfficiencyScore() << " / 100" << endl;
        cout << "  Operational Health   : " << (lostBaggageFlags == 0 ? "EXCELLENT" : "DISPATCH AUDIT NEEDED") << endl;
        cout << "==============================================" << endl;
    }
};

// Derived Class 2: International Heavy Air Cargo Bay
class HeavyCargoBay : public BaggageTerminal {
private:
    double totalCargoPalletTons;
    int hazardousMaterialCrates;

public:
    HeavyCargoBay(string id, int containers, double palletTons, int hazmatCrates)
        : BaggageTerminal(id, containers),
          totalCargoPalletTons(palletTons),
          hazardousMaterialCrates(hazmatCrates) {
        totalWeightProcessedKG += (palletTons * 1000.0);
    }

    ~HeavyCargoBay() override {
        cout << " -> Disengaging hydraulic lifters and sealing bay for " << terminalID << "..." << endl;
    }

    double calculateEfficiencyScore() const override {
        if (bagsProcessed == 0) return 0.0;
        // Efficiency scales with tonnage moved safely per container unit
        return (totalCargoPalletTons * 10.0) / bagsProcessed;
    }

    void printConveyorReport() const override {
        cout << "\n==============================================" << endl;
        cout << "   HEAVY CARGO DISPATCH BAY: " << terminalID << endl;
        cout << "==============================================" << endl;
        cout << "  Cargo Containers     : " << bagsProcessed << endl;
        cout << "  Payload Mass         : " << fixed << setprecision(2) << totalCargoPalletTons << " tons" << endl;
        cout << "  Hazmat Inspections   : " << hazardousMaterialCrates << " units" << endl;
        cout << "  Throughput Index     : " << fixed << setprecision(2) << calculateEfficiencyScore() << " pts" << endl;
        cout << "  Clearance Status     : " << (hazardousMaterialCrates > 0 ? "HAZMAT PROTOCOL ACTIVE" : "STANDARD CLEAR") << endl;
        cout << "==============================================" << endl;
    }
};

int main() {
    cout << "\n>>> AIRPORT LOGISTICS TELEMETRY SYSTEM ONLINE <<<\n" << endl;

    const int TOTAL_TERMINALS = 2;
    BaggageTerminal* terminalArray[TOTAL_TERMINALS];

    // Carousel 1: Domestic arrival belt (320 bags, 21.5 kg average, 1 misplaced bag)
    terminalArray[0] = new PassengerCarousel("BELT-DOMESTIC-03", 320, 21.5, 1);

    // Bay 2: Freight cargo depot (40 heavy containers, 85.4 tons, 3 hazmat units)
    terminalArray[1] = new HeavyCargoBay("CARGO-DEPOT-NORTH", 40, 85.4, 3);

    // Polymorphic display loop
    for (int i = 0; i < TOTAL_TERMINALS; i++) {
        terminalArray[i]->printConveyorReport();
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Baggage Terminals  : " << BaggageTerminal::activeTerminals << endl;
    cout << "Total Mass Handled Today  : " << fixed << setprecision(2) 
         << BaggageTerminal::totalWeightProcessedKG << " kg" << endl;
    cout << "----------------------------------------------\n" << endl;

    cout << ">>> INITIATING TERMINAL NIGHTLY CLEARANCE <<<\n" << endl;

    // Polymorphic deallocation
    for (int i = 0; i < TOTAL_TERMINALS; i++) {
        delete terminalArray[i];
        terminalArray[i] = nullptr;
    }

    cout << "\n----------------------------------------------" << endl;
    cout << "Active Baggage Terminals After Teardown : " << BaggageTerminal::activeTerminals << endl;
    cout << "----------------------------------------------" << endl;

    return 0;
}

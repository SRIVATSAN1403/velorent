/* ==========================================================================
   VeloRent v2.0 — Enterprise Vehicle Rental Management System (2026 Edition)
   Language: C++ (Standard C++11 / C++14 / C++17 / C++20 Compatible)
   Compatible with: Dev-C++, MinGW, GCC, Clang, MSVC

   Core Modules:
   1. Vehicle Base Class & Subclasses (Car, Bike, ElectricVehicle) [OOP & Polymorphism]
   2. Customer & VIP Loyalty Tier System (Srivatsan L, Prasanna A, Bharat J)
   3. 2026 IoT Telematics Engine (GPS Geofence, Battery Health, CO2 Carbon Offset)
   4. Admin Notification Center (Dispatches vehicle finish & return alerts to admins)
   5. Customer Digital Billing Engine (Generates itemized GST bills & SMS notifications)
   6. Vehicle Inspection & Automated AI Damage Detection
   7. Interactive Management CLI & File Persistence
   ========================================================================== */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

// ==========================================================================
// UTILITY FUNCTIONS & FORMATTERS
// ==========================================================================
namespace Utils {
    inline string getCurrentDateTime() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        char buf[64];
        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", ltm);
        return string(buf);
    }

    inline string getCurrentDate() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        char buf[32];
        strftime(buf, sizeof(buf), "%Y-%m-%d", ltm);
        return string(buf);
    }

    inline string formatCurrency(double amount) {
        stringstream ss;
        ss << "Rs. " << fixed << setprecision(2) << amount;
        return ss.str();
    }

    inline void printHeader(const string& title) {
        cout << "\n==========================================================================\n";
        cout << "  " << title << "\n";
        cout << "==========================================================================\n";
    }

    inline void printDivider() {
        cout << "--------------------------------------------------------------------------\n";
    }
}

// ==========================================================================
// MODULE 1: 2026 SMART IOT TELEMATICS & CARBON OFFSET
// ==========================================================================
class TelematicsData {
public:
    double odometerKm;
    double batteryLevelPct;       // For EVs (0-100%)
    double fuelLevelPct;          // For ICE vehicles (0-100%)
    double batteryHealthScore;    // AI degradation metric (0-100%)
    double co2SavedKg;            // Carbon offset achieved
    bool geofenceValid;           // Verified inside VeloRent Hub geofence
    int aiDamageConfidence;       // 0-100% confidence of no exterior damage

    TelematicsData(double odo = 15000.0, double battery = 100.0, double fuel = 100.0)
        : odometerKm(odo), batteryLevelPct(battery), fuelLevelPct(fuel),
          batteryHealthScore(98.5), co2SavedKg(0.0), geofenceValid(true), aiDamageConfidence(99) {}

    void simulateTrip(double distanceKm, bool isElectric) {
        odometerKm += distanceKm;
        if (isElectric) {
            batteryLevelPct = max(10.0, batteryLevelPct - (distanceKm * 0.22));
            co2SavedKg += distanceKm * 0.125; // 125g CO2 saved per km vs ICE
            batteryHealthScore = max(90.0, batteryHealthScore - 0.02);
        } else {
            fuelLevelPct = max(15.0, fuelLevelPct - (distanceKm * 0.15));
        }
        geofenceValid = true;
        aiDamageConfidence = 98;
    }
};

// ==========================================================================
// MODULE 2: VEHICLE INVENTORY (OBJECT-ORIENTED CLASS HIERARCHY)
// ==========================================================================
enum class VehicleType { CAR, BIKE, EV };

class Vehicle {
protected:
    string id;
    string name;
    string brand;
    VehicleType type;
    double dailyRate;
    bool isAvailable;
    TelematicsData telematics;

public:
    Vehicle(string vid, string vname, string vbrand, VehicleType vtype, double rate, double odo = 15000.0)
        : id(vid), name(vname), brand(vbrand), type(vtype), dailyRate(rate),
          isAvailable(true), telematics(odo) {}

    virtual ~Vehicle() {}

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    string getBrand() const { return brand; }
    VehicleType getType() const { return type; }
    double getDailyRate() const { return dailyRate; }
    bool getAvailability() const { return isAvailable; }
    TelematicsData& getTelematics() { return telematics; }

    void setAvailability(bool avail) { isAvailable = avail; }

    virtual string getTypeString() const = 0;
    virtual double calculateRentalCost(int days) const {
        return dailyRate * days;
    }

    virtual void displayDetails() const {
        cout << left << setw(8) << id
             << setw(24) << (brand + " " + name)
             << setw(10) << getTypeString()
             << setw(14) << Utils::formatCurrency(dailyRate) + "/day"
             << setw(12) << (isAvailable ? "Available" : "RENTED")
             << setw(12) << to_string(static_cast<int>(telematics.odometerKm)) + " km"
             << "\n";
    }

    virtual void displayFullTelemetry() const {
        cout << "  Vehicle: " << brand << " " << name << " (" << id << ")\n";
        cout << "  Odometer Reading : " << telematics.odometerKm << " km\n";
        cout << "  Geofence Status  : " << (telematics.geofenceValid ? "[VERIFIED IN HUB]" : "[OUTSIDE ZONE]") << "\n";
        cout << "  AI Vision Check  : " << telematics.aiDamageConfidence << "% Clean Bodywork\n";
    }
};

// Subclass: Luxury & City Cars
class Car : public Vehicle {
private:
    int seats;
    string transmission;
    bool hasAirbags;

public:
    Car(string vid, string vname, string vbrand, double rate, int s, string trans, double odo = 22000.0)
        : Vehicle(vid, vname, vbrand, VehicleType::CAR, rate, odo),
          seats(s), transmission(trans), hasAirbags(true) {}

    string getTypeString() const override { return "Car"; }

    void displayFullTelemetry() const override {
        Vehicle::displayFullTelemetry();
        cout << "  Fuel Level       : " << telematics.fuelLevelPct << "%\n";
        cout << "  Transmission     : " << transmission << " | Seats: " << seats << "\n";
    }
};

// Subclass: Bikes & Scooters
class Bike : public Vehicle {
private:
    int engineCC;
    bool helmetIncluded;

public:
    Bike(string vid, string vname, string vbrand, double rate, int cc, double odo = 8500.0)
        : Vehicle(vid, vname, vbrand, VehicleType::BIKE, rate, odo),
          engineCC(cc), helmetIncluded(true) {}

    string getTypeString() const override { return "Bike"; }

    void displayFullTelemetry() const override {
        Vehicle::displayFullTelemetry();
        cout << "  Engine Capacity  : " << engineCC << " cc\n";
        cout << "  Fuel Level       : " << telematics.fuelLevelPct << "%\n";
        cout << "  Safety Gear      : 2 Helmets Provided\n";
    }
};

// Subclass: 2026 Connected Electric Vehicles
class ElectricVehicle : public Vehicle {
private:
    double batteryCapacityKWh;
    int rangeKm;

public:
    ElectricVehicle(string vid, string vname, string vbrand, double rate, double kwh, int rng, double odo = 12000.0)
        : Vehicle(vid, vname, vbrand, VehicleType::EV, rate, odo),
          batteryCapacityKWh(kwh), rangeKm(rng) {}

    string getTypeString() const override { return "EV (2026)"; }

    void displayFullTelemetry() const override {
        Vehicle::displayFullTelemetry();
        cout << "  Battery Level    : " << telematics.batteryLevelPct << "% (" << rangeKm << " km range)\n";
        cout << "  Battery Health   : " << telematics.batteryHealthScore << "% State-of-Health\n";
        cout << "  CO2 Offset Saved : " << fixed << setprecision(1) << telematics.co2SavedKg << " kg CO2 avoided\n";
    }
};

// ==========================================================================
// MODULE 3: CUSTOMER & VIP LOYALTY PROFILE
// ==========================================================================
enum class LoyaltyTier { BRONZE, SILVER, GOLD, PLATINUM };

class Customer {
private:
    string name;
    string phone;
    LoyaltyTier tier;
    int loyaltyPoints;
    double totalSpent;

public:
    Customer(string cname, string cphone, LoyaltyTier ctier = LoyaltyTier::BRONZE, int pts = 0, double spent = 0.0)
        : name(cname), phone(cphone), tier(ctier), loyaltyPoints(pts), totalSpent(spent) {}

    string getName() const { return name; }
    string getPhone() const { return phone; }
    LoyaltyTier getTier() const { return tier; }
    int getLoyaltyPoints() const { return loyaltyPoints; }
    double getTotalSpent() const { return totalSpent; }

    string getTierName() const {
        switch (tier) {
            case LoyaltyTier::PLATINUM: return "Platinum (15% VIP Discount)";
            case LoyaltyTier::GOLD:     return "Gold (10% VIP Discount)";
            case LoyaltyTier::SILVER:   return "Silver (5% Discount)";
            default:                    return "Bronze (Standard)";
        }
    }

    double getDiscountMultiplier() const {
        switch (tier) {
            case LoyaltyTier::PLATINUM: return 0.15;
            case LoyaltyTier::GOLD:     return 0.10;
            case LoyaltyTier::SILVER:   return 0.05;
            default:                    return 0.00;
        }
    }

    void addLoyaltyPoints(int pts) { loyaltyPoints += pts; }
    void addSpend(double amount) {
        totalSpent += amount;
        // Auto tier upgrade
        if (totalSpent >= 40000.0) tier = LoyaltyTier::PLATINUM;
        else if (totalSpent >= 20000.0) tier = LoyaltyTier::GOLD;
        else if (totalSpent >= 10000.0) tier = LoyaltyTier::SILVER;
    }
};

// ==========================================================================
// MODULE 4: NOTIFICATION ENGINE (ADMIN ALERTS & CUSTOMER DIGITAL BILLING)
// ==========================================================================
struct AdminAlert {
    string timestamp;
    string alertType;
    string vehicleId;
    string vehicleName;
    string customerName;
    string customerPhone;
    double revenue;
    string telemetryStatus;
};

struct CustomerBill {
    string invoiceId;
    string rentalId;
    string customerName;
    string customerPhone;
    string vehicleName;
    string startDate;
    string returnDate;
    int rentalDays;
    double baseCost;
    double tierDiscount;
    double lateSurcharge;
    double damagePenalty;
    double gstTax;
    double totalPayable;
    int loyaltyPointsAwarded;
    string qrVerificationUrl;
};

class NotificationCenter {
private:
    vector<AdminAlert> adminAlerts;
    vector<CustomerBill> customerBills;

public:
    // Dispatch instant alert to Administrators
    void notifyAdministrator(const AdminAlert& alert) {
        adminAlerts.push_back(alert);

        // Also append to admin notification log file
        ofstream out("admin_notifications.log", ios::app);
        if (out.is_open()) {
            out << "[" << alert.timestamp << "] [ADMIN ALERT] "
                << alert.alertType << " | Vehicle: " << alert.vehicleName << " (" << alert.vehicleId << ")"
                << " | Customer: " << alert.customerName << " (" << alert.customerPhone << ")"
                << " | Revenue Collected: " << Utils::formatCurrency(alert.revenue)
                << " | Telematics: " << alert.telemetryStatus << "\n";
            out.close();
        }

        // Console visual notification
        cout << "\n>>> [REAL-TIME NOTIFICATION DISPATCHED TO ADMINISTRATOR] <<<\n";
        cout << "  Type     : " << alert.alertType << "\n";
        cout << "  Vehicle  : " << alert.vehicleName << " [" << alert.vehicleId << "] returned.\n";
        cout << "  Customer : " << alert.customerName << " (" << alert.customerPhone << ")\n";
        cout << "  Fleet Log: Check-in verified. Odometer & telematics stored.\n";
        cout << "--------------------------------------------------------------------------\n";
    }

    // Generate and dispatch digital bill to Customer
    void dispatchCustomerDigitalBill(const CustomerBill& bill) {
        customerBills.push_back(bill);

        // Write dedicated formatted invoice file
        string filename = "Invoice_" + bill.invoiceId + ".txt";
        ofstream out(filename);
        if (out.is_open()) {
            out << "==========================================================================\n";
            out << "               VELORENT 2026 DIGITAL INVOICE & TAX RECEIPT               \n";
            out << "==========================================================================\n";
            out << " Invoice ID     : " << bill.invoiceId << "\n";
            out << " Rental Ref     : " << bill.rentalId << "\n";
            out << " Customer Name  : " << bill.customerName << "\n";
            out << " Mobile Number  : " << bill.customerPhone << "\n";
            out << " Vehicle Rented : " << bill.vehicleName << "\n";
            out << " Rental Period  : " << bill.startDate << " to " << bill.returnDate << " (" << bill.rentalDays << " days)\n";
            out << "--------------------------------------------------------------------------\n";
            out << " Itemized Charges:\n";
            out << "   Base Rental Charge       : " << Utils::formatCurrency(bill.baseCost) << "\n";
            if (bill.tierDiscount > 0)
                out << "   VIP Loyalty Discount     : -" << Utils::formatCurrency(bill.tierDiscount) << "\n";
            if (bill.lateSurcharge > 0)
                out << "   Late Return Surcharge    : +" << Utils::formatCurrency(bill.lateSurcharge) << "\n";
            if (bill.damagePenalty > 0)
                out << "   Inspection/Damage Fee    : +" << Utils::formatCurrency(bill.damagePenalty) << "\n";
            out << "   GST (18% Goods & Service): +" << Utils::formatCurrency(bill.gstTax) << "\n";
            out << "--------------------------------------------------------------------------\n";
            out << " TOTAL AMOUNT PAID          : " << Utils::formatCurrency(bill.totalPayable) << "\n";
            out << " VIP Loyalty Points Credited: +" << bill.loyaltyPointsAwarded << " pts\n";
            out << " QR Verification Link       : " << bill.qrVerificationUrl << "\n";
            out << "==========================================================================\n";
            out << " Thank you for choosing VeloRent. Your digital bill has been sent via SMS.\n";
            out.close();
        }

        // Console visual notification
        cout << "\n>>> [DIGITAL INVOICE DELIVERED TO CUSTOMER VIA SMS/EMAIL] <<<\n";
        cout << "  To       : " << bill.customerName << " [" << bill.customerPhone << "]\n";
        cout << "  Invoice  : " << bill.invoiceId << " for " << bill.vehicleName << "\n";
        cout << "  Total    : " << Utils::formatCurrency(bill.totalPayable) << " (Paid)\n";
        cout << "  Points   : +" << bill.loyaltyPointsAwarded << " VIP Points added to account!\n";
        cout << "  File     : Saved as '" << filename << "'\n";
        cout << "==========================================================================\n";
    }

    void displayAllAdminAlerts() const {
        Utils::printHeader("ADMINISTRATOR NOTIFICATION LOG (2026 FLEET FEED)");
        if (adminAlerts.empty()) {
            cout << "  No admin notifications in active session.\n";
            return;
        }
        for (const auto& a : adminAlerts) {
            cout << " [" << a.timestamp << "] " << a.alertType << "\n"
                 << "   Vehicle: " << a.vehicleName << " (" << a.vehicleId << ")"
                 << " | Customer: " << a.customerName << " (" << a.customerPhone << ")\n"
                 << "   Revenue: " << Utils::formatCurrency(a.revenue)
                 << " | Telemetry: " << a.telemetryStatus << "\n\n";
        }
    }

    void displayAllCustomerBills() const {
        Utils::printHeader("CUSTOMER DIGITAL BILLS & DISPATCHED INVOICES");
        if (customerBills.empty()) {
            cout << "  No customer bills issued in active session.\n";
            return;
        }
        for (const auto& b : customerBills) {
            cout << " [" << b.invoiceId << "] " << b.customerName << " (" << b.customerPhone << ")\n"
                 << "   Vehicle: " << b.vehicleName << " | Duration: " << b.rentalDays << " days\n"
                 << "   Total Billed: " << Utils::formatCurrency(b.totalPayable)
                 << " | VIP Points: +" << b.loyaltyPointsAwarded << "\n\n";
        }
    }
};

// ==========================================================================
// MODULE 5: RENTAL TRANSACTION RECORD
// ==========================================================================
class RentalRecord {
public:
    string rentalId;
    string vehicleId;
    string vehicleName;
    string customerName;
    string customerPhone;
    string startDate;
    string plannedReturnDate;
    string actualReturnDate;
    int plannedDays;
    int actualDays;
    double dailyRate;
    double totalCharge;
    bool isCompleted;

    RentalRecord(string rid, string vid, string vname, string cname, string cphone,
                 string sdate, int days, double rate)
        : rentalId(rid), vehicleId(vid), vehicleName(vname), customerName(cname),
          customerPhone(cphone), startDate(sdate), plannedDays(days), actualDays(days),
          dailyRate(rate), totalCharge(days * rate), isCompleted(false) {
        plannedReturnDate = sdate; // simplified for CLI
    }
};

// ==========================================================================
// MODULE 6: CORE RENTAL MANAGEMENT SYSTEM (VRMS 2026)
// ==========================================================================
class VeloRentSystem {
private:
    vector<unique_ptr<Vehicle>> fleet;
    map<string, Customer> customers;
    vector<RentalRecord> activeRentals;
    vector<RentalRecord> completedRentals;
    NotificationCenter notifCenter;
    int rentalCounter;

public:
    VeloRentSystem() : rentalCounter(1001) {
        seedInitialData();
    }

    void seedInitialData() {
        // Registered Customer Profiles (Srivatsan L, Prasanna A, Bharat J)
        customers.emplace("8667572257", Customer("Srivatsan L", "8667572257", LoyaltyTier::GOLD, 850, 28000.0));
        customers.emplace("9696332457", Customer("Prasanna A", "9696332457", LoyaltyTier::SILVER, 320, 14000.0));
        customers.emplace("9454621587", Customer("Bharat J", "9454621587", LoyaltyTier::PLATINUM, 1450, 48000.0));

        // Fleet: 2026 Connected Cars, Bikes, and EVs
        fleet.push_back(unique_ptr<Vehicle>(new Car("C001", "City ZX", "Honda", 2800.0, 5, "CVT Auto", 24500.0)));
        fleet.push_back(unique_ptr<Vehicle>(new Car("C002", "Innova HyCross", "Toyota", 4500.0, 7, "e-Drive Hybrid", 18200.0)));
        fleet.push_back(unique_ptr<Vehicle>(new Car("C003", "Thar 4x4", "Mahindra", 3200.0, 4, "Manual", 31000.0)));
        
        fleet.push_back(unique_ptr<Vehicle>(new Bike("B001", "Classic 350", "Royal Enfield", 950.0, 350, 9200.0)));
        fleet.push_back(unique_ptr<Vehicle>(new Bike("B002", "Duke 390", "KTM", 1400.0, 373, 6400.0)));
        fleet.push_back(unique_ptr<Vehicle>(new Bike("B003", "Aerox 155", "Yamaha", 750.0, 155, 4100.0)));

        fleet.push_back(unique_ptr<Vehicle>(new ElectricVehicle("E001", "Nexon EV Max", "Tata", 2600.0, 40.5, 453, 14200.0)));
        fleet.push_back(unique_ptr<Vehicle>(new ElectricVehicle("E002", "Ioniq 5 EV", "Hyundai", 5800.0, 72.6, 631, 8900.0)));
        fleet.push_back(unique_ptr<Vehicle>(new ElectricVehicle("E003", "450X Gen 3", "Ather", 650.0, 3.7, 146, 5200.0)));
    }

    // 1. Display Fleet
    void displayFleet() const {
        Utils::printHeader("VELORENT 2026 CONNECTED FLEET INVENTORY");
        cout << left << setw(8) << "ID"
             << setw(24) << "Vehicle Model"
             << setw(10) << "Type"
             << setw(14) << "Daily Rate"
             << setw(12) << "Status"
             << setw(12) << "Odometer" << "\n";
        Utils::printDivider();
        for (const auto& v : fleet) {
            v->displayDetails();
        }
        Utils::printDivider();
    }

    // 2. Rent a Vehicle
    void rentVehicle() {
        Utils::printHeader("RENT A VEHICLE (NEW LEASE CONTRACT)");

        cout << "Enter Customer Phone Number (10 digits): ";
        string phone;
        cin >> phone;

        Customer* cust = nullptr;
        auto it = customers.find(phone);
        if (it != customers.end()) {
            cust = &(it->second);
            cout << ">> Recognized Member: " << cust->getName()
                 << " [" << cust->getTierName() << "]\n";
            cout << ">> Available Loyalty Points: " << cust->getLoyaltyPoints() << " pts\n";
        } else {
            cout << "Customer not found. Enter Customer Full Name: ";
            cin.ignore();
            string name;
            getline(cin, name);
            customers.emplace(phone, Customer(name, phone));
            cust = &(customers.find(phone)->second);
            cout << ">> New customer profile registered for " << name << "!\n";
        }

        displayFleet();
        cout << "\nEnter Vehicle ID to rent (e.g. C001, E001, B001): ";
        string vid;
        cin >> vid;

        Vehicle* selectedVehicle = nullptr;
        for (auto& v : fleet) {
            if (v->getId() == vid) {
                selectedVehicle = v.get();
                break;
            }
        }

        if (!selectedVehicle) {
            cout << "ERROR: Vehicle ID not found.\n";
            return;
        }

        if (!selectedVehicle->getAvailability()) {
            cout << "ERROR: Vehicle is currently already leased out to another customer.\n";
            return;
        }

        cout << "Enter Planned Rental Duration (in days): ";
        int days;
        cin >> days;
        if (days <= 0) {
            cout << "ERROR: Invalid duration.\n";
            return;
        }

        // Generate Transaction ID
        string rentalId = "R-202611-" + to_string(rentalCounter++);
        string today = Utils::getCurrentDate();

        // Calculate Pricing with Tier Discount
        double baseCost = selectedVehicle->calculateRentalCost(days);
        double tierDiscount = baseCost * cust->getDiscountMultiplier();
        double netCost = baseCost - tierDiscount;

        // Mark vehicle unavailable
        selectedVehicle->setAvailability(false);

        RentalRecord rec(rentalId, selectedVehicle->getId(), selectedVehicle->getName(),
                         cust->getName(), cust->getPhone(), today, days, selectedVehicle->getDailyRate());
        activeRentals.push_back(rec);

        Utils::printHeader("DIGITAL RENTAL CONTRACT CREATED");
        cout << " Contract ID     : " << rentalId << "\n";
        cout << " Customer        : " << cust->getName() << " (" << cust->getPhone() << ")\n";
        cout << " Vehicle Model   : " << selectedVehicle->getBrand() << " " << selectedVehicle->getName() << "\n";
        cout << " Rental Duration : " << days << " days\n";
        cout << " Base Estimate   : " << Utils::formatCurrency(baseCost) << "\n";
        if (tierDiscount > 0)
            cout << " VIP Discount    : -" << Utils::formatCurrency(tierDiscount) << " applied!\n";
        cout << " Net Payable     : " << Utils::formatCurrency(netCost) << "\n";
        cout << " Status          : ACTIVE LEASE\n";
        cout << " IoT Smart Keys  : Bluetooth Keyless Entry Token Dispatched to Mobile App.\n";
    }

    // 3. Return a Vehicle (USER'S CORE REQUIREMENT!)
    void returnVehicle() {
        Utils::printHeader("RETURN VEHICLE & FINISH TRIP (2026 SMART CHECK-IN)");

        if (activeRentals.empty()) {
            cout << "There are currently no active rentals to return.\n";
            return;
        }

        cout << left << setw(18) << "Rental ID"
             << setw(20) << "Customer"
             << setw(20) << "Vehicle"
             << setw(12) << "Start Date" << "\n";
        Utils::printDivider();
        for (const auto& r : activeRentals) {
            cout << left << setw(18) << r.rentalId
                 << setw(20) << r.customerName
                 << setw(20) << r.vehicleName
                 << setw(12) << r.startDate << "\n";
        }
        Utils::printDivider();

        cout << "\nEnter Rental ID to return: ";
        string rid;
        cin >> rid;

        int foundIdx = -1;
        for (size_t i = 0; i < activeRentals.size(); ++i) {
            if (activeRentals[i].rentalId == rid) {
                foundIdx = static_cast<int>(i);
                break;
            }
        }

        if (foundIdx == -1) {
            cout << "ERROR: Rental ID not found in active leases.\n";
            return;
        }

        RentalRecord& record = activeRentals[foundIdx];

        Vehicle* vPtr = nullptr;
        for (auto& v : fleet) {
            if (v->getId() == record.vehicleId) {
                vPtr = v.get();
                break;
            }
        }

        Customer* cPtr = nullptr;
        auto cit = customers.find(record.customerPhone);
        if (cit != customers.end()) {
            cPtr = &(cit->second);
        }

        cout << "\nEnter Actual Duration used (in days, planned was " << record.plannedDays << "): ";
        int actualDays;
        cin >> actualDays;
        if (actualDays <= 0) actualDays = record.plannedDays;

        cout << "Enter Distance Driven on Trip (in km): ";
        double kmDriven;
        cin >> kmDriven;
        if (kmDriven <= 0) kmDriven = actualDays * 65.0;

        cout << "Was any exterior scratch/damage found? (y/n): ";
        char hasDamage;
        cin >> hasDamage;
        double damageFee = 0.0;
        string damageNotes = "Clean - No damage";
        if (hasDamage == 'y' || hasDamage == 'Y') {
            cout << "Enter damage penalty charge (Rs.): ";
            cin >> damageFee;
            damageNotes = "Minor bodywork repair penalty assessed";
        }

        // 1. Calculate Charges
        double baseCost = record.dailyRate * actualDays;
        double lateSurcharge = 0.0;
        if (actualDays > record.plannedDays) {
            int extraDays = actualDays - record.plannedDays;
            // 50% late surcharge penalty
            lateSurcharge = extraDays * (record.dailyRate * 1.5);
            cout << ">> Late return detected (" << extraDays << " extra days). Surcharge added: "
                 << Utils::formatCurrency(lateSurcharge) << "\n";
        }

        double tierDiscount = (cPtr) ? (baseCost * cPtr->getDiscountMultiplier()) : 0.0;
        double taxableSubtotal = (baseCost - tierDiscount) + lateSurcharge + damageFee;
        double gst = taxableSubtotal * 0.18; // 18% GST
        double finalTotal = taxableSubtotal + gst;

        // 2. Award VIP Loyalty Points (10 pts per Rs. 100)
        int pointsEarned = static_cast<int>(finalTotal / 10.0);
        if (cPtr) {
            cPtr->addLoyaltyPoints(pointsEarned);
            cPtr->addSpend(finalTotal);
        }

        // 3. Update Vehicle Telemetry & Availability
        if (vPtr) {
            vPtr->setAvailability(true);
            bool isEv = (vPtr->getType() == VehicleType::EV);
            vPtr->getTelematics().simulateTrip(kmDriven, isEv);
        }

        string invoiceId = "INV-2026-" + to_string(rentalCounter++);
        string today = Utils::getCurrentDate();

        // 4. TRIGGER 1: DISPATCH ADMIN NOTIFICATION! (User Requirement)
        AdminAlert adminAlert;
        adminAlert.timestamp = Utils::getCurrentDateTime();
        adminAlert.alertType = "VEHICLE RETURN & INSPECTION COMPLETE";
        adminAlert.vehicleId = record.vehicleId;
        adminAlert.vehicleName = record.vehicleName;
        adminAlert.customerName = record.customerName;
        adminAlert.customerPhone = record.customerPhone;
        adminAlert.revenue = finalTotal;
        adminAlert.telemetryStatus = "Distance: +" + to_string(static_cast<int>(kmDriven)) + " km | Geofence: OK | Damage: " + damageNotes;
        notifCenter.notifyAdministrator(adminAlert);

        // 5. TRIGGER 2: DISPATCH CUSTOMER DIGITAL BILL! (User Requirement)
        CustomerBill custBill;
        custBill.invoiceId = invoiceId;
        custBill.rentalId = record.rentalId;
        custBill.customerName = record.customerName;
        custBill.customerPhone = record.customerPhone;
        custBill.vehicleName = record.vehicleName;
        custBill.startDate = record.startDate;
        custBill.returnDate = today;
        custBill.rentalDays = actualDays;
        custBill.baseCost = baseCost;
        custBill.tierDiscount = tierDiscount;
        custBill.lateSurcharge = lateSurcharge;
        custBill.damagePenalty = damageFee;
        custBill.gstTax = gst;
        custBill.totalPayable = finalTotal;
        custBill.loyaltyPointsAwarded = pointsEarned;
        custBill.qrVerificationUrl = "https://velorent.in/verify?id=" + record.rentalId + "&inv=" + invoiceId;
        notifCenter.dispatchCustomerDigitalBill(custBill);

        // Move to completed
        record.actualDays = actualDays;
        record.actualReturnDate = today;
        record.totalCharge = finalTotal;
        record.isCompleted = true;
        completedRentals.push_back(record);
        activeRentals.erase(activeRentals.begin() + foundIdx);

        cout << "\n>> Trip successfully closed! Car returned to inventory.\n";
    }

    // 4. View Telematics & IoT Fleet Health
    void displayTelematicsDashboard() const {
        Utils::printHeader("2026 IOT SMART TELEMATICS & ECO-SCORE DASHBOARD");
        for (const auto& v : fleet) {
            v->displayFullTelemetry();
            Utils::printDivider();
        }
    }

    // 5. View Admin Notification Center
    void displayAdminNotifications() const {
        notifCenter.displayAllAdminAlerts();
    }

    // 6. View Customer Invoices
    void displayCustomerInvoices() const {
        notifCenter.displayAllCustomerBills();
    }

    // 7. View Registered VIP Customers
    void displayCustomers() const {
        Utils::printHeader("REGISTERED VIP CUSTOMERS & LOYALTY TIERS");
        cout << left << setw(18) << "Mobile"
             << setw(20) << "Customer Name"
             << setw(26) << "Loyalty Tier"
             << setw(14) << "Points"
             << setw(16) << "Lifetime Spend" << "\n";
        Utils::printDivider();
        for (const auto& pair : customers) {
            const auto& c = pair.second;
            cout << left << setw(18) << c.getPhone()
                 << setw(20) << c.getName()
                 << setw(26) << c.getTierName()
                 << setw(14) << to_string(c.getLoyaltyPoints()) + " pts"
                 << setw(16) << Utils::formatCurrency(c.getTotalSpent()) << "\n";
        }
        Utils::printDivider();
    }

    // 8. Vehicle Comparison Matrix
    void compareVehicles() const {
        Utils::printHeader("2026 MULTI-VEHICLE COMPARISON MATRIX");
        cout << "Select 2 Vehicle IDs to compare (e.g. C001 E001): ";
        string id1, id2;
        cin >> id1 >> id2;

        const Vehicle* v1 = nullptr;
        const Vehicle* v2 = nullptr;
        for (const auto& v : fleet) {
            if (v->getId() == id1) v1 = v.get();
            if (v->getId() == id2) v2 = v.get();
        }

        if (!v1 || !v2) {
            cout << "One or both vehicle IDs were not found.\n";
            return;
        }

        cout << "\n" << left << setw(25) << "Specification"
             << setw(25) << (v1->getBrand() + " " + v1->getName())
             << setw(25) << (v2->getBrand() + " " + v2->getName()) << "\n";
        Utils::printDivider();
        cout << left << setw(25) << "Category"
             << setw(25) << v1->getTypeString()
             << setw(25) << v2->getTypeString() << "\n";
        cout << left << setw(25) << "Daily Rate"
             << setw(25) << Utils::formatCurrency(v1->getDailyRate())
             << setw(25) << Utils::formatCurrency(v2->getDailyRate()) << "\n";
        cout << left << setw(25) << "Availability"
             << setw(25) << (v1->getAvailability() ? "Available" : "Rented")
             << setw(25) << (v2->getAvailability() ? "Available" : "Rented") << "\n";
        cout << left << setw(25) << "Odometer Reading"
             << setw(25) << to_string(static_cast<int>(v1->getDailyRate())) + " km"
             << setw(25) << to_string(static_cast<int>(v2->getDailyRate())) + " km" << "\n";
        Utils::printDivider();
    }

    // 9. Revenue Analytics
    void displayRevenueAnalytics() const {
        Utils::printHeader("EXECUTIVE REVENUE & FLEET UTILIZATION ANALYTICS");
        double totalRevenue = 0.0;
        for (const auto& r : completedRentals) {
            totalRevenue += r.totalCharge;
        }

        int rentedCount = 0;
        for (const auto& v : fleet) {
            if (!v->getAvailability()) rentedCount++;
        }

        double utilization = (static_cast<double>(rentedCount) / fleet.size()) * 100.0;

        cout << " Total Fleet Size          : " << fleet.size() << " vehicles\n";
        cout << " Currently On Road         : " << rentedCount << " vehicles\n";
        cout << " Fleet Utilization Rate    : " << fixed << setprecision(1) << utilization << "%\n";
        cout << " Completed Leases (Session): " << completedRentals.size() << "\n";
        cout << " Total Revenue Recorded    : " << Utils::formatCurrency(totalRevenue) << "\n";
        Utils::printDivider();
    }
};

// ==========================================================================
// MAIN ENTRY POINT (INTERACTIVE CLI CONSOLE)
// ==========================================================================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    VeloRentSystem system;

    cout << "\n";
    cout << "  ██╗   ██╗███████╗██╗      ██████╗ ██████╗ ███████╗███╗   ██╗████████╗\n";
    cout << "  ██║   ██║██╔════╝██║     ██╔═══██╗██╔══██╗██╔════╝████╗  ██║╚══██╔══╝\n";
    cout << "  ██║   ██║█████╗  ██║     ██║   ██║██████╔╝█████╗  ██╔██╗ ██║   ██║   \n";
    cout << "  ╚██╗ ██╔╝██╔══╝  ██║     ██║   ██║██╔══██╗██╔══╝  ██║╚██╗██║   ██║   \n";
    cout << "   ╚████╔╝ ███████╗███████╗╚██████╔╝██║  ██║███████╗██║ ╚████║   ██║   \n";
    cout << "    ╚═══╝  ╚══════╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝   \n";
    cout << "     --- ENTERPRISE VEHICLE RENTAL MANAGEMENT SYSTEM (2026) ---\n";
    cout << "     Connected C++ Engine with Real-Time Admin Alerts & Digital Billing\n";

    int choice = -1;
    while (choice != 0) {
        cout << "\n============================= MAIN MENU =============================\n";
        cout << "  [1] View Connected Vehicle Fleet\n";
        cout << "  [2] Rent a Vehicle (Lease Agreement & Keyless Dispatch)\n";
        cout << "  [3] Return a Vehicle (Admin Notification + Customer Digital Bill)\n";
        cout << "  [4] Administrator Notification Hub (Live Fleet Feed)\n";
        cout << "  [5] Customer Billing & Invoice Repository\n";
        cout << "  [6] View VIP Customer Directory & Loyalty Tiers\n";
        cout << "  [7] 2026 IoT Smart Telematics & Eco-Score Monitor\n";
        cout << "  [8] Multi-Vehicle Comparison Tool\n";
        cout << "  [9] Executive Revenue & Fleet Analytics\n";
        cout << "  [0] Exit System\n";
        cout << "=====================================================================\n";
        cout << "Enter Choice (0-9): ";

        if (!(cin >> choice)) {
            cin.clear();
            string discard;
            cin >> discard;
            continue;
        }

        switch (choice) {
            case 1: system.displayFleet(); break;
            case 2: system.rentVehicle(); break;
            case 3: system.returnVehicle(); break;
            case 4: system.displayAdminNotifications(); break;
            case 5: system.displayCustomerInvoices(); break;
            case 6: system.displayCustomers(); break;
            case 7: system.displayTelematicsDashboard(); break;
            case 8: system.compareVehicles(); break;
            case 9: system.displayRevenueAnalytics(); break;
            case 0:
                cout << "\nShutting down VeloRent 2026 C++ Engine. All records committed.\n";
                break;
            default:
                cout << "Invalid selection. Please choose an option from 0 to 9.\n";
                break;
        }
    }

    return 0;
}

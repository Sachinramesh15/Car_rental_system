#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Add this header for file handling

using namespace std;
class Vehicle {
protected:
    string make;
    string model;
    int year;
    bool available;
    string customerName;
    string phoneNumber;
    string idNumber;

public:
    Vehicle(string make, string model, int year)
        : make(make),
          model(model),
          year(year),
          available(true) {}
    void setCustomerDetails(const string& name, const string& phone, const string& id) {
        customerName = name;
        phoneNumber = phone;
        idNumber = id;
    }

    string getMake() const {
        return make;
    }

    string getModel() const {
        return model;
    }

    int getYear() const {
        return year;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool status) {
        available = status;
    }

    virtual void displayDetails() const = 0;
};

class Car : public Vehicle {
public:
 

    Car(string make, string model, int year) : Vehicle(make, model, year) {}
    

    string getCustomerName() const {
        return customerName;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }

    string getIDNumber() const {
        return idNumber;
    }
    void displayDetails() const override {
        cout << year << " " << make << " " << model << " (Available: " << (available ? "Yes" : "No") << ")\n";
    }

    // Function to display details to the file
    void displayDetailsToFile(ofstream& outputFile) const {
        outputFile << year << " " << make << " " << model << " (Available: " << (available ? "Yes" : "No") << ")\n";
    }
};

class CarRentalSystem {
private:
    vector<Car> vehicles; 

public:
    void addVehicle(const Car& car) {
        vehicles.push_back(car);
    }

    void rentVehicle(int vehicleIndex) {
        if (vehicleIndex >= 0 && vehicleIndex < vehicles.size()) {
            if (vehicles[vehicleIndex].isAvailable()) {
                string name, phone, id;
                cout << "Enter your name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your phone number: ";
                getline(cin, phone);
                cout << "Enter your ID number: ";
                getline(cin, id);  
                vehicles[vehicleIndex].setCustomerDetails(name, phone, id);
                vehicles[vehicleIndex].setAvailable(false);
                cout << "You have rented the vehicle:\n";
                vehicles[vehicleIndex].displayDetails();
            } else {
                cout << "Sorry, the vehicle is not available for rent.\n";
            }
        } else {
            cout << "Invalid vehicle index.\n";
        }
    }
    void saveRentalDetailsToFile() {
        ofstream outputFile("rental_details.txt");
        if (!outputFile.is_open()) {
            cout << "Error creating file.\n";
            return;
        }

        for (const Car& car : vehicles) {
            if (!car.isAvailable()) {
                outputFile << "Customer Name: " << car.getCustomerName() << endl;
                outputFile << "Phone Number: " << car.getPhoneNumber() << endl;
                outputFile << "ID Number: " << car.getIDNumber() << endl;
                outputFile << "Vehicle Details: ";
                car.displayDetailsToFile(outputFile);
                outputFile << endl;
            }
        }

        outputFile.close();
    }
    void returnVehicle(int vehicleIndex) {
        if (vehicleIndex >= 0 && vehicleIndex < vehicles.size()) {
            if (!vehicles[vehicleIndex].isAvailable()) {
                vehicles[vehicleIndex].setAvailable(true);
                cout << "You have returned the vehicle:\n";
                vehicles[vehicleIndex].displayDetails();
            } else {
                cout << "No vehicle is rented currently!.\n";
            }
        } else {
            cout << "Invalid vehicle index.\n";
        }
    }

    void displayAvailableVehicles() const {
        cout << "Available Vehicles:\n";
        for (size_t i = 0; i < vehicles.size(); ++i) {
            cout << i + 1 << ". ";
            vehicles[i].displayDetails();
        }
    }
};
int main() {
    CarRentalSystem rentalSystem;
     rentalSystem.addVehicle(Car("Toyota", "Corolla", 2020));
    rentalSystem.addVehicle(Car("Honda", "Civic", 2021));
    rentalSystem.addVehicle(Car("Ford", "Mustang", 2019));
    rentalSystem.addVehicle(Car("Chevrolet", "Cruze", 2022));
    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display available vehicles\n";
        cout << "2. Rent a vehicle\n";
        cout << "3. Return a vehicle\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                rentalSystem.displayAvailableVehicles();
                break;
            case 2: {
                int vehicleIndex;
                cout << "Enter the vehicle number to rent: ";
                cin >> vehicleIndex;
                rentalSystem.rentVehicle(vehicleIndex - 1);
                rentalSystem.saveRentalDetailsToFile();
                break;
            }

            case 3: {
                int vehicleIndex;
                cout << "Enter the vehicle number to return: ";
                cin >> vehicleIndex;
                rentalSystem.returnVehicle(vehicleIndex - 1);
                break;
            }
            case 4:
                cout << "Thank you for using the vehicle rental system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
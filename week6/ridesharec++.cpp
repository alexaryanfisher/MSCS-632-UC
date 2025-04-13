#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Ride Sharing Application

// Ride Class - Base Class for all ride types.
class Ride {
public:
    //Ride variables of rideID, pickuplocation, dropofflocation, distance.
    Ride(int rideID, const std::string& pickupLocation, const std::string& dropoffLocation, double distance)
    : rideID(rideID), pickupLocation(pickupLocation), dropoffLocation(dropoffLocation), distance(distance) {}

    //Virtual destructor for polymorphism with inhertance
    virtual ~Ride() = default;

    //Virtual fare calculation function to make the Ride class abstract and force derived class.
    virtual double fare() const = 0;

    // Vitural function which can be overriden in derived classes.
    virtual std::string getRideDetails() const {
        std::ostringstream oss;
        oss << "Ride ID: " << rideID
            << ", Pickup Location: " << pickupLocation
            << ", Dropoff Location: " << dropoffLocation
            << ", Distance: " << std::fixed << std::setprecision(2) << distance
            << ", Fare: " <<std::fixed << std::setprecision(2) << fare();
        return oss.str();
    }
    
    //Methods for attributes
    int getRideID() const {return rideID; }
    std::string getPickupLocation() const {return pickupLocation; }
    std::string getDropoffLocation() const {return dropoffLocation; }
    double getDistance() const {return distance; }

protected:
    int rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance;
};

//Subclass of Ride Class: StandardRide
class StandardRide : public Ride {
public:
    //Standard Ride variables: rideID, pickupLocation, dropoffLocation, distance
    StandardRide(int rideID, const std::string& pickupLocation, const std::string& dropoffLocation, double distance)
    : Ride(rideID, pickupLocation, dropoffLocation, distance) {}

    //Standard fare calculation, override fare().
    double fare() const override {
        return distance * 3.50;
    }
};

//Subclass of Ride Class: PremiumRide
class PremiumRide : public Ride {
 public:
     //Premium Ride variables: rideID, pickupLocation, dropoffLocation, distance
     PremiumRide(int rideID, const std::string& pickupLocation, const std::string& dropoffLocation, double distance)
     : Ride(rideID, pickupLocation, dropoffLocation, distance) {}
 
     //Standard fare calculation, override fare().
     double fare() const override {
         return distance * 4.50;
     }
 };

 //Driver Class
 class Driver {
public:
    //Driver variables: driverID, driverName, rating
    Driver(int driverID, const std::string& driverName, double rating)
    : driverID(driverID), driverName(driverName), rating(rating) {}

    //Function to add ride to driver list of assignedRides.
    void addRide (Ride* ride){
        assignedRides.push_back(ride);
    }

    //Function to get driver info.
    std::string getDriverInfo() const {
        std::ostringstream oss;
        oss << "Driver ID: " << driverID
            << ", Driver Name: " << driverName
            << ", Rating: " << std::fixed << std::setprecision(1) << rating
            << ", Rides: " << assignedRides.size();
        return oss.str();
    }

    //Function to get Driver's assignedRides
    const std::vector <Ride*>& getAssignedRides() const {
        return assignedRides;
    }

private:
    int driverID;
    std::string driverName;
    double rating;
    std::vector<Ride*> assignedRides;
 };

 //Rider Class
 class Rider{
public:
    //Rider variables: riderID, riderName
    Rider(int riderID, const std::string& riderName)
    : riderID(riderID), riderName(riderName) {}

    //Function to request ride and add to rider's list.
    void requestRide(Ride* ride) {
        requestedRides.push_back(ride);
    }

    //Function to review ride history.
    std::string viewRides() const {
        std::ostringstream oss;
        oss << "Rider ID: " << riderID
            <<", Rider Name: " << riderName
            << ", Rides (count): " << requestedRides.size();
        return oss.str();
    }

    //Function to get requested rides.
    const std::vector <Ride*>& getRequestedRides() const {
        return requestedRides;
    }
private:
    int riderID;
    std::string riderName;
    std::vector<Ride*> requestedRides;
 };

 //Main program
 int main(){
    //Create Ride Objects
    StandardRide stdRide(1, "Home", "Work", 5.0);
    PremiumRide premRide(2, "Work", "Airport", 10.0);

    //Create vector of pointers to Ride Objects to show Polymorphism.
    std::vector<Ride*> rides;
    //Store addresses of ride objects
    rides.push_back(&stdRide);
    rides.push_back(&premRide);

    //Polymorphism, call virtual functions on ride pointers
    for (Ride* ride: rides){
        //Call overidden version
        std::cout << ride-> getRideDetails() << std::endl;
    }

    //Create Drive and Rider Objects
    Driver driver(200, "William Fisher", 4.9);
    driver.addRide(&stdRide);
    driver.addRide(&premRide);

    Rider rider(1000, "Kimberly Holmes");
    rider.requestRide(&stdRide);
    rider.requestRide(&premRide);

    //Show Driver and Rider info.
    std::cout << driver.getDriverInfo() << std::endl;
    std::cout << rider.viewRides() << std::endl;
    
    return 0;
 }
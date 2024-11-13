#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DisasterTracker {
private:
    static int totalDisasters;

public:
    // Increment totalDisasters count
    static void increment(){
        ++totalDisasters;
    }

    // Get total number of disasters
    static int getTotalDisasters(){
        return totalDisasters;
    }
};

// Initializing static variable
int DisasterTracker::totalDisasters = 0;

// Class to handle display logic for Disaster
class DisasterDisplay {
public:
    static void display(const Disaster& disaster){
        std:: cout << "\nDisaster: " << disaster.getName()
                        << "\nSeverity: " << disaster.getSeverity()
                        << "\nAffected Area: " << disaster.getAffectedArea()
                        << std::endl;
    }
};

// Factory class for creating Disaster instances
class DisasterFactory {
public:
    static Disaster createDisaster(const std::string& name, int severity, const std::string& affectedArea){
        DisasterTracker::increment();
        return Disaster(name, severity, affectedArea);
    }
};

// Class to validate disaster data
class DisasterValidator{
public:
    static bool validateSeverity(int severity){
        return (severity >= 1 && severity <= 5);
    }
};



// Class to represent a Disaster
class Disaster {
private:
    std::string name;
    int severity; // Severity level of the disaster
    std::string affectedArea; // Name of the area affected

public:
    // Default Constructor
    Disaster() : name("Unknown"), severity(1), affectedArea("Unknown") {
        cout << "Default Disaster Constructor called" << endl;
    }

    // Parameterized Constructor
    Disaster(const std::string& name, int severity, const std::string& affectedArea)
        : name(name), severity(severity), affectedArea(affectedArea) {
            cout << "Parameterized Disaster Constructor Called" << endl;
        }

    // Getter for severity
    int getSeverity() const {
        return severity;
    }

    // setter for severity
    void setSeverity(int newSeverity){
        if(DisasterValidator::validateSeverity(newSeverity)){
            severity = newSeverity;
        }else{
            cout << "Invalid severity value.  Please enter a value between 1 and 5." << endl;
        }
    }

    // Getter for name
    string getName() const {
        return name;
    }

    // setter for name
    void setName(const std::string& newName){
        name = newName;
    }

    string getAffectedArea() const {
        return affectedArea;
    }

        // setter for affected Area
    void setAffectedArea(const std::string& newAffectedArea){
        affectedArea = newAffectedArea;
    }

    // virtual destructor to ensure proper cleanup in derived classes
    virtual ~Disaster() {
        cout << "Disaster Desutructor Called" << endl;
    }
};

// Class to represent a Response Team (Base Class for Single Inheritance)
class ResponseTeam {
private:
    std::string teamName;
    int teamSize;
    std::vector<std::string> resources;

protected:
    // Static variable to count total number of response teams
    static int totalResponseTeams;

public:
    // Default constructor
    ResponseTeam() : teamName("Default Ream"), teamSize(1) {
        ++totalResponseTeams; // Increment totalResponseTeams for each new ResponseTeam instance
        cout << "Default Response Team Constructor Called" << endl;
    }

    // Parameterized Constructor
    ResponseTeam(const std::string& teamName, int teamSize)
        : teamName(teamName), teamSize(teamSize) {
            ++totalResponseTeams; // Increment totalResponseTeams for each new ResponseTeam instance
            cout << "Parameterized ResponseTeam Constructor Called" << endl;
        }

    // Getter for team name
    string getTeamName() const {
        return teamName;
    }

    // setter for team name
    void setTeamName(const std::string& newTeamName){
        teamName = newTeamName;
    }

    // Getter for team size
    int getTeamSize() const {
        return teamSize;
    }

    // setter for team size
    void setTeamSize(int newTeamSize){
        if(newTeamSize > 0){
            teamSize = newTeamSize;
        }else{
            cout << "Invalid team size.  It must be greater than 0." << endl;
        }
    }

    // Function overloading to add resources
    void addResource(const std::string& resource){
        this->resources.push_back(resource);
    }

    void addResource(const std::vector<std::string>& resourceList) {
        for (const auto& resource : resourceList) {
            resources.push_back(resource);
        }
    }

    // Method to display team information
    virtual void displayTeamInfo() {
        std::cout << "\nTeam: " << teamName << "\nTeam Size: " << teamSize 
                  << "\nResources: ";
        for (const auto& res : resources) {
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }

    // Method to get the total number of response teams
    static int getTotalResponseTeams() {
        return totalResponseTeams;
    }

    // Virtual method to be overridden by specific team types
    virtual void respond(Disaster& disaster) {
        std::cout << teamName << " is responding to the disaster in " 
                  << disaster.getAffectedArea() << std::endl;
    }

    // virtual destructor to nesure proper cleanup in derived classes
    virtual ~ResponseTeam() {
        cout << "ResponseTeam Destructor Called" << endl;
    }
};

// Inititalizing static variable
int ResponseTeam::totalResponseTeams = 0;

// Abstract Class to represent an Emergency Response Team
class EmergencyResponse {
public:
    //Pure virtual function to be overriden in derived classes
    virtual void respondToDisaster() = 0;

    // Virtual destructor for proper cleanup
    virtual ~EmergencyResponse() {
        cout << "EmergencyResponse Destructor Called" << endl;
    }
};

// Derived class for Medical Team implementing the abstract class
class MedicalTeam : public EmergencyResponse {
private:
    std::string teamName;
    int teamSize;

public:
    MedicalTeam(const std::string& name, int size) : teamName(name), teamSize(size) {}

    // Overriding the pure virtual function
    void respondToDisaster() override {
        cout << teamName << " (Medical Team) is providing medical assistance with " << teamSize << " members." << endl;
    }
};

// Derived class for FireFighter Team implementing the abstract class
class FireFighterTeam : public EmergencyResponse {
private:
    std::string teamName;
    int teamSize;

public:
    FireFighterTeam(const std::string& name, int size) : teamName(name), teamSize(size) {}

    // Overriding the pure virtual function
    void respondToDisaster() override {
        cout << teamName << " (Firefighter Team) is putting out fires with " << teamSize << " members." << endl;
    }
};

// Derived class for Search and Rescue Team implementing the abstract class
class SearchAndRescueTeam : public EmergencyResponse {
private:
    std::string teamName;
    int teamSize;

public:
    SearchAndRescueTeam(const std::string& name, int size) : teamName(name), teamSize(size) {}

    // Overriding the pure virtual function
    void respondToDisaster() override {
        cout << teamName << " (Search and Rescue Team) is rescuing trapped individuals with " << teamSize << " members." << endl;
    }
};

// Derived class to represent a specific Response Team (e.g., Medical Team)
// Derived class (Single Inheritance)
class MedicalResponseTeam : public ResponseTeam {
public:
    // Default constructor
    MedicalResponseTeam() : ResponseTeam() {}

    // Constructor
    MedicalResponseTeam(const std::string& teamName, int teamSize)
        : ResponseTeam(teamName, teamSize) {}

    // Overriding the respond method for Medical Team
    void respond(Disaster& disaster) override {
        std::cout << getTeamName() << " is providing medical assistance in " 
                  << disaster.getAffectedArea() << std::endl;
    }
};

// Derived class (Multilevel Inheritance)
class AdvancedMedicalTeam : public MedicalResponseTeam {
public:
    // Default constructor
    AdvancedMedicalTeam() : MedicalResponseTeam() {}

    // Constructor
    AdvancedMedicalTeam(const std::string& teamName, int teamSize)
        : MedicalResponseTeam(teamName, teamSize) {}

    // Overriding the respond method for Advanced Medical Team
    void respond(Disaster& disaster) override {
        std::cout << getTeamName() << " is providing advanced medical care in " << disaster.getAffectedArea() << std::endl;
    }

    // Special function for advanced care
    void advancedCare(){
        std::cout << "Providing specialized advanced care and life-saving treatments." << std::endl;
    }
};

// Derived class to represent a specific type of Disaster (e.g., Hurricane)
class Hurricane : public Disaster {
public:
    // Constructor
    Hurricane(const std::string& name, int severity, const std::string& affectedArea)
        : Disaster(name, severity, affectedArea) {}

    // Overriding the impact method for a Hurricane
    void impact() override {
        std::cout << "Hurricane: " << getName() << " is causing severe damage in " 
                  << getAffectedArea() << " with a severity of " << getSeverity() << std::endl;
    }
};

// Function to create a disaster instance using DisasterFactory
Disaster createDisaster(){
    std::string disasterName, affectedArea;
    int severity;

    std::cout << "Enter the name of the disaster: ";
    std::getline(std::cin, disasterName);

    do{
        std::cout << "Enter the severity level of the disaster (1-5): ";
        std::cin >> severity;
        if(severity < 1 || severity > 5){
            std::cout << "Invalid input. Please enter a severity level between 1 and 5." << std::endl;
        }
    }while(severity < 1 || severity > 5);

    std::cin.ignore();

    std::cout << "Enter the affected area: ";
    std::getline(std::cin, affectedArea);

    return DisasterFactory::createDisaster(disasterName, severity, affectedArea);
};

// Function to create response teams
std::vector<ResponseTeam*> createResponseTeams(){
    int numTeams;
    std::vector<ResponseTeam*> teams;

    std::cout << "Enter the number of response teams:";
    std::cin >> numTeams;

    if(numTeams <= 0){
        std::cout << "Invalid input.  Number of response teams must be greater than 0." << std::endl;
        return teams;
    }

    for(int i=0; i<numTeams; i++){
        std::string teamName;
        int teamSize;

        std::cout << "Enter the name of response team " << (i+1) << ": ";
        std::cin >> std::ws;
        std::getline(std::cin, teamName);

        do{
            std::cout << "Enter the size of response team " << (i+1) << ": ";
            std::cin >> teamSize;
            if(teamSize <= 0){
                std::cout << "Invalid input.  Team size must be greater than 0." << std::endl;
            }
        }while(teamSize <= 0);

        ResponseTeam* team = new MedicalResponseTeam(teamName, teamSize);
        teams.push_back(team);
    }
    return teams;
};

int main() {
    // Disaster creation using factory
    Disaster hurricane = createDisaster();

    // Display disaster details using DisasterDisplay
    DisasterDisplay::display(hurricane);

    // Create response teams
    std::vector<ResponseTeam*> teams = createResponseTeams();

    // Display team information and respond to disaster
    for (ResponseTeam* team : teams) {
        team->displayTeamInfo();
        team->respond(hurricane);
    }

    // Clean up memory
    for (ResponseTeam* team : teams) {
        delete team; // Deleting each response team object
    }

    std::cout << "Total Disasters: " << DisasterTracker::getTotalDisasters() << std::endl;
    std::cout << "Total Response Teams: " << ResponseTeam::getTotalResponseTeams() << std::endl;

    return 0;
}
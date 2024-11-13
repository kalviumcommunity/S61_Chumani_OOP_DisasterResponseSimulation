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
    static Disaster* createDisaster(const std::string& type, const std::string& name, int severity, const std::string& affectedArea){
        DisasterTracker::increment();
        if(type == "Hurricane"){
            return new Hurricane(name, severity, affectedArea);
        }else if(type == "Flood"){
            return new Flood(name, severity, affectedArea);
        }
        return nullptr;
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

    virtual void impact() const = 0;

    virtual ~Disaster() = default;

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
};

// Class to represent a Response Team (Base Class for Single Inheritance)
class ResponseTeam {
private:
    std::string teamName;
    int teamSize;
    std::vector<std::string> resources;

protected:
    static int totalResponseTeams;

public:
    ResponseTeam(const std::string& teamName, int teamSize)
        : teamName(teamName), teamSize(teamSize) {
        ++totalResponseTeams;
    }

    string getTeamName() const { return teamName; }
    int getTeamSize() const { return teamSize; }

    void addResource(const std::string& resource) { resources.push_back(resource); }
    void addResource(const std::vector<std::string>& resourceList) {
        resources.insert(resources.end(), resourceList.begin(), resourceList.end());
    }

    virtual void respond(Disaster& disaster) {
        std::cout << teamName << " is responding to the disaster in " << disaster.getAffectedArea() << std::endl;
    }

    virtual void displayTeamInfo() const {
        std::cout << "\nTeam: " << teamName << "\nTeam Size: " << teamSize
                  << "\nResources: ";
        for (const auto& res : resources) {
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }

    virtual ~ResponseTeam() {
        cout << "ResponseTeam Destructor Called" << endl;
    }
};

// Inititalizing static variable
int ResponseTeam::totalResponseTeams = 0;

// Derived class to represent a specific Response Team (e.g., Medical Team)
// Derived class (Single Inheritance)
class MedicalResponseTeam : public ResponseTeam {
public:
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

// Derived class to represent a specific type of Disaster (e.g., Hurricane)
class Hurricane : public Disaster {
public:
    // Constructor
    Hurricane(const std::string& name, int severity, const std::string& affectedArea)
        : Disaster(name, severity, affectedArea) {}

    // Overriding the impact method for a Hurricane
    void impact() const override {
        std::cout << "Hurricane: " << getName() << " is causing severe damage in " 
                  << getAffectedArea() << " with a severity of " << getSeverity() << std::endl;
    }
};

class Flood : public Disaster {
public:
    Flood(const std::string& name, int severity, const std::string& affectedArea)
        : Disaster(name, severity, affectedArea) {}

    void impact() const override {
        std::cout << "Flood: " << getName() << " is flooding the area of " << getAffectedArea() << " with a severity of " << getSeverity() << std::endl;
    }
};

// Function to create a disaster instance using DisasterFactory
Disaster* createDisaster(){
    std::string type, name, affectedArea;
    int severity;

    std::cout << "Enter the type of the disaster (Hurricane/Flood): ";
    std::getline(std::cin, type);

    std::cout << "Enter the name of the disaster: ";
    std::getline(std::cin, name);

    std::cout << "Enter the severity level of the disaster (1-5): ";
    std::cin >> severity;
    std::cin.ignore();

    std::cout << "Enter the affected area: ";
    std::getline(std::cin, affectedArea);

    return DisasterFactory::createDisaster(type, name, severity, affectedArea);
};

// Function to create response teams
std::vector<ResponseTeam*> createResponseTeams() {
    int numTeams;
    std::vector<ResponseTeam*> teams;

    std::cout << "Enter the number of response teams: ";
    std::cin >> numTeams;
    std::cin.ignore();

    for(int i = 0; i < numTeams; ++i) {
        std::string teamName;
        int teamSize;

        std::cout << "Enter the name of response team " << (i + 1) << ": ";
        std::getline(std::cin, teamName);

        std::cout << "Enter the size of response team " << (i + 1) << ": ";
        std::cin >> teamSize;
        std::cin.ignore();

        teams.push_back(new MedicalResponseTeam(teamName, teamSize));
    }
    return teams;
}

int main() {
    // Disaster creation
    Disaster* disaster = createDisaster();
    DisasterDisplay::display(*disaster);
    disaster->impact();

    // Create response teams
    std::vector<ResponseTeam*> teams = createResponseTeams();

    // Display team information and respond to disaster
    for (ResponseTeam* team : teams) {
        team->displayTeamInfo();
        team->respond(*disaster);
    }

    // Clean up memory
    delete disaster;
    for (ResponseTeam* team : teams) {
        delete team;
    }

    std::cout << "Total Disasters: " << DisasterTracker::getTotalDisasters() << std::endl;

    return 0;
}




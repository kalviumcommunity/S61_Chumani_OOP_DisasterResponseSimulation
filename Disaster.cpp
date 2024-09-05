#include <iostream>
#include <vector>
#include <string>

// Class to represent a Disaster
class Disaster {
protected:
    std::string name;
    int severity; // Severity level of the disaster
    std::string affectedArea; // Name of the area affected

    // Static variable to count total number of disasters
    static int totalDisasters;

public:
    // Constructor
    Disaster(const std::string& name, int severity, const std::string& affectedArea)
        : name(name), severity(severity), affectedArea(affectedArea) {
            ++totalDisasters; // Increment totalDisasters for each new Disaster instance
        }

    // Method to display the impact of the disaster
    virtual void impact() {
        std::cout << "\nDisaster: " << name << "\nSeverity: " << severity 
                  << "\nAffected Area: " << affectedArea << std::endl;
    }

    // Getter for affectedArea using 'this' pointer
    std::string getAffectedArea() const {
        return this->affectedArea;  // Using 'this' pointer
    }

    // Method to get the total number of disasters
    static int getTotalDisasters() {
        return totalDisasters;
    }

    // virtual destructor to ensure proper cleanup in derived classes
    virtual ~Disaster() {}
};

// Initializing static variable
int Disaster::totalDisasters = 0;

// Class to represent a Response Team
class ResponseTeam {
protected:
    std::string teamName;
    int teamSize;
    std::vector<std::string> resources;

    // Static variable to count total number of response teams
    static int totalResponseTeams;

public:
    // Default constructor
    ResponseTeam() : teamName(""), teamSize(0) {
        ++totalResponseTeams; // Increment totalResponseTeams for each new ResponseTeam instance
    }

    // Constructor
    ResponseTeam(const std::string& teamName, int teamSize)
        : teamName(teamName), teamSize(teamSize) {
            ++totalResponseTeams; // Increment totalResponseTeams for each new ResponseTeam instance
        }

    // Method to add a resource to the team's inventory
    ResponseTeam& addResource(const std::string& resource) {
        this->resources.push_back(resource);  // Using 'this' pointer for clarity
        return *this;  // Returning the current object to allow method chaining
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
    virtual ~ResponseTeam() {}
};

// Inititalizing static variable
int ResponseTeam::totalResponseTeams = 0;

// Derived class to represent a specific type of Disaster (e.g., Hurricane)
class Hurricane : public Disaster {
public:
    // Constructor
    Hurricane(const std::string& name, int severity, const std::string& affectedArea)
        : Disaster(name, severity, affectedArea) {}

    // Overriding the impact method for a Hurricane
    void impact() override {
        std::cout << "Hurricane: " << name << " is causing severe damage in " 
                  << affectedArea << " with a severity of " << severity << std::endl;
    }
};

// Derived class to represent a specific Response Team (e.g., Medical Team)
class MedicalTeam : public ResponseTeam {
public:
    // Default constructor
    MedicalTeam() : ResponseTeam() {}

    // Constructor
    MedicalTeam(const std::string& teamName, int teamSize)
        : ResponseTeam(teamName, teamSize) {}

    // Overriding the respond method for Medical Team
    void respond(Disaster& disaster) override {
        std::cout << teamName << " is providing medical assistance in " 
                  << disaster.getAffectedArea() << std::endl;
    }
};

int main() {
    std::string disasterName, affectedArea;
    int severity, numTeams;

    // Taking user input for disaster details
    std::cout << "Enter the name of the disaster: ";
    std::getline(std::cin, disasterName);
    
    std::cout << "Enter the severity level of the disaster (1-5): ";
    std::cin >> severity;
    std::cin.ignore(); // To ignore the leftover newline character

    std::cout << "Enter the affected area: ";
    std::getline(std::cin, affectedArea);

    // Creating a Hurricane object using dynamic memory allocation
    Disaster* hurricane = new Hurricane(disasterName, severity, affectedArea);

    // Taking user input for number of response teams
    std::cout << "Enter the number of response teams: ";
    std::cin >> numTeams;
    std::cin.ignore(); // To ignore the leftover newline character

    // Creating an array of MedicalTeam objects based on user input
    MedicalTeam** teams = new MedicalTeam*[numTeams];
    for (int i = 0; i < numTeams; ++i) {
        std::string teamName;
        int teamSize;

        std::cout << "\nEnter the name of team " << i + 1 << ": ";
        std::getline(std::cin, teamName);

        std::cout << "Enter the size of team " << i + 1 << ": ";
        std::cin >> teamSize;
        std::cin.ignore(); // To ignore the leftover newline character

        // using dynamic memory allocation for each team
        teams[i] = new MedicalTeam(teamName, teamSize);

        int numResources;
        std::cout << "Enter the number of resources for " << teamName << ": ";
        std::cin >> numResources;
        std::cin.ignore(); // To ignore the leftover newline character

        for (int j = 0; j < numResources; ++j) {
            std::string resource;
            std::cout << "Enter resource " << j + 1 << ": ";
            std::getline(std::cin, resource);
            teams[i]->addResource(resource);
        }
    }

    // Displaying disaster impact
    hurricane->impact();

    // Displaying team information and responding to the disaster
    for (int i = 0; i < numTeams; ++i) {
        std::cout << "\nTeam " << i + 1 << " Information:" << std::endl;
        teams[i]->displayTeamInfo();
        teams[i]->respond(*hurricane);
    }

    // Displaying the total number of disasters and response teams
    std::cout << "\nTotal number of disasters: " << Disaster::getTotalDisasters() << std::endl;
    std::cout << "Total number of response teams: " << ResponseTeam::getTotalResponseTeams() << std::endl;

    // Freeing the dynamically allocated memory for teams
    for(int i = 0; i < numTeams; i++){
        delete teams[i];
    }

    delete[] teams; // Freeing the dynamically allocated memory

    // Freeing the dynamically allocated memory for hurricane
    delete hurricane;

    return 0;
}




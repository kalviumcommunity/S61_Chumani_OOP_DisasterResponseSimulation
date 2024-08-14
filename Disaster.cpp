#include <iostream>
#include <vector>
#include <string>

// Class to represent a Disaster
class Disaster {
protected:
    std::string name;
    int severity; // Severity level of the disaster
    std::string affectedArea; // Name of the area affected

public:
    // Constructor
    Disaster(const std::string& name, int severity, const std::string& affectedArea)
        : name(name), severity(severity), affectedArea(affectedArea) {}

    // Method to display the impact of the disaster
    virtual void impact() {
        std::cout << "\nDisaster: " << name << "\nSeverity: " << severity 
                  << "\nAffected Area: " << affectedArea << std::endl;
    }

    // Getter for affectedArea using 'this' pointer
    std::string getAffectedArea() const {
        return this->affectedArea;  // Using 'this' pointer
    }
};

// Class to represent a Response Team
class ResponseTeam {
protected:
    std::string teamName;
    int teamSize;
    std::vector<std::string> resources;

public:
    // Default constructor
    ResponseTeam() : teamName(""), teamSize(0) {}

    // Constructor
    ResponseTeam(const std::string& teamName, int teamSize)
        : teamName(teamName), teamSize(teamSize) {}

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

    // Virtual method to be overridden by specific team types
    virtual void respond(Disaster& disaster) {
        std::cout << teamName << " is responding to the disaster in " 
                  << disaster.getAffectedArea() << std::endl;
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

    // Creating a Hurricane object using user input
    Hurricane hurricane(disasterName, severity, affectedArea);

    // Taking user input for number of response teams
    std::cout << "Enter the number of response teams: ";
    std::cin >> numTeams;
    std::cin.ignore(); // To ignore the leftover newline character

    // Creating an array of MedicalTeam objects based on user input
    MedicalTeam* teams = new MedicalTeam[numTeams];
    for (int i = 0; i < numTeams; ++i) {
        std::string teamName;
        int teamSize;

        std::cout << "\nEnter the name of team " << i + 1 << ": ";
        std::getline(std::cin, teamName);

        std::cout << "Enter the size of team " << i + 1 << ": ";
        std::cin >> teamSize;
        std::cin.ignore(); // To ignore the leftover newline character

        teams[i] = MedicalTeam(teamName, teamSize);

        int numResources;
        std::cout << "Enter the number of resources for " << teamName << ": ";
        std::cin >> numResources;
        std::cin.ignore(); // To ignore the leftover newline character

        for (int j = 0; j < numResources; ++j) {
            std::string resource;
            std::cout << "Enter resource " << j + 1 << ": ";
            std::getline(std::cin, resource);
            teams[i].addResource(resource);
        }
    }

    // Displaying disaster impact
    hurricane.impact();

    // Displaying team information and responding to the disaster
    for (int i = 0; i < numTeams; ++i) {
        std::cout << "\nTeam " << i + 1 << " Information:" << std::endl;
        teams[i].displayTeamInfo();
        teams[i].respond(hurricane);
    }

    delete[] teams; // Freeing the dynamically allocated memory

    return 0;
}



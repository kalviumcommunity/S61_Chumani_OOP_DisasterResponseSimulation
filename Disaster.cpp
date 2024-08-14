#include <iostream>
#include <vector>
#include <string>

class Disaster{
protected:
    std::string name;
    int severity;
    std::string affectedArea;

public:
    Disaster(const std::string& name, int severity, const std::string& affectedArea)
        : name(name), severity(severity), affectedArea(affectedArea){}

    // Method to display the impact of the disaster
    virtual void impact(){
        std::cout << "Disaster: "<< name << "\nSeverity: " << severity << "\nAffected Area: " << affectedArea << std::endl;
    }

    // Getter for affectedArea
    std::string getAffectedArea() const {
        return affectedArea;
    }
};
class ResponseTeam {
protected:
    std::string teamName;
    int teamSize;
    std::vector<std::string> resources;
public:
    // Default constructor
    ResponseTeam() : teamName(""), teamSize(0) {}

    // constructor
    ResponseTeam(const std::string& teamName, int teamSize)
        : teamName(teamName), teamSize(teamSize) {}

    // Method to add a resource to the team's inventory
    void addResource(const std::string& resource){
        resources.push_back(resource);
    }

    // Method to display team information
    virtual void displayTeamInfo() {
        std::cout << "\nTeam: " << teamName << "\nTeam size: " << teamSize << "\nResources: ";
        for(const auto& res : resources){
            std::cout << res << " ";
        }
        std::cout << std::endl;
    }

    // virtual method to be overrider by specific team types
    virtual void response(Disaster& disaster){
        std::cout << teamName << " is responding to the disaster in " << disaster.getAffectedArea() << std::endl;
    }
};
class Hurricane: public Disaster {
public:
    // constructor
    Hurricane(const std::string& name, int severity, const std::string& affectedArea)
        :Disaster(name, severity, affectedArea){}
    
    // Overriding the impact method for a Hurricane
    void impact() override{
        std::cout << "Hurricane: " << name << " is causing severe damage in " << affectedArea << " with a severity of " << severity << std::endl;
    }
};
class MedicalTeam : public ResponseTeam {
public:
    // Default construcotr
    MedicalTeam() : ResponseTeam() {}

    // Constructor
    MedicalTeam(const std::string& teamName, int teamSize)
        : ResponseTeam(teamName, teamSize){}
    
    // overriding the respond method for Medical Team
    void respond(Disaster& disaster) override {
        std::cout << teamName << " is providing medical assistance in " << disaster.getAffectedArea() << std::endl;
    }
};
int main(){
    std::string disasterName, affectedArea;
    int severity, numTeams;

    // Taking user input for disaster details
    std::cout << "Enter the name of the disaster: ";
    std::getline(std::cin, disasterName);

    std::cout << "Enter the severity level of the disaster (1-5): ";
    std::cin >>severity;
    std::cin.ignore();

    std::cout << "Enter the affected area: ";
    std::getline(std::cin, affectedArea);

    // Creating a Hurricane object using user input
    Hurricane hurricane(disasterName, severity, affectedArea);

    std::cout << "Enter the number of response teams: ";
    std::cin >> numTeams;
    std::cin.ignore();

    // Creating an array of MedicalTeam objects based on user input
    MedicalTeam* teams = new MedicalTeam[numTeams];
    for(int i=0;i<numTeams;++i){
        std::string teamName;
        int teamSize;

        std::cout << "\nEnter the name of team " << i + 1 << ": ";
        std::getline(std::cin, teamName);

        std::cout << "Enter the size of team " << i +1 << ": ";
        std::cin >> teamSize;
        std::cin.ignore();

        teams[i] = MedicalTeam(teamName, teamSize);

        int numResources;
        std::cout << "Enter the number of resources for " << teamName << ": ";
        std::cin >> numResources;
        std::cin.ignore();

        for(int j=0;j<numResources;j++){
            std::string resource;
            std::cout << "Enter resource " << j +1 << " ";
            std::getline(std::cin, resource);
            teams[i].addResource(resource);
        }

        // Displaying disaster impact
        hurricane.impact();

        for(int i=0;i<numTeams;i++){
            std::cout << "\nTeam" << i + 1 << "Information:" << std::endl;
            teams[i].displayTeamInfo();
            teams[i].respond(hurricane);
        }

        delete[] teams;
    }
    return 0;
}
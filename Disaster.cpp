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
    Hurricane hurricane("Katrina", 5, "New Orleans");

    // Creating a Medical Team object
    MedicalTeam medTeam("Red Cross", 50);

    // Displaying disaster impact
    hurricane.impact();

    // Displaying team information and responding to the disaster
    medTeam.displayTeamInfo();
    medTeam.respond(hurricane);

    // std::cout << "Hello from cpp" << std::endl;
    return 0;
}
#ifndef EDXPhysicsList_h
#define EDXPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class EDXPhysicsList : public G4VModularPhysicsList {
public:
    EDXPhysicsList();
    virtual ~EDXPhysicsList();
    virtual void SetCuts() override;
    virtual void ConstructProcess() override;
};

#endif

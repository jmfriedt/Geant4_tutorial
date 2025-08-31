#ifndef EDXSteppingAction_h
#define EDXSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4Step;

class EDXSteppingAction : public G4UserSteppingAction {
public:
    EDXSteppingAction();
    virtual ~EDXSteppingAction();

    virtual void UserSteppingAction(const G4Step* step) override;
};

#endif

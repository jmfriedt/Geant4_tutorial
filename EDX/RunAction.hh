#ifndef EDXRunAction_h
#define EDXRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;

class EDXRunAction : public G4UserRunAction {
public:
    EDXRunAction();
    virtual ~EDXRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif

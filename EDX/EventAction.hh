#ifndef EDXEventAction_h
#define EDXEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

class EDXEventAction : public G4UserEventAction {
public:
    EDXEventAction();
    virtual ~EDXEventAction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
};

#endif

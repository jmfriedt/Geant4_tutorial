#include "EventAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"

EventAction::EventAction() : G4UserEventAction() {}

EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* event) {
    G4int eventID = event->GetEventID();
    if (eventID % 1000 == 0) {
        G4cout << "---> Begin of event: " << eventID << G4endl;
    }
}

void EventAction::EndOfEventAction(const G4Event* event) {
    // Optional: Placeholder for per-event processing
}

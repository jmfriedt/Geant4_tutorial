#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include <fstream>
#include <vector>

std::ofstream edxOut("edx_spectrum.csv");

SteppingAction::SteppingAction() {
    // Optionally log or prepare files here
}

SteppingAction::~SteppingAction() {
    edxOut.close();
}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    // Get all secondaries produced in this step
    const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();

    // loop through the secondaries
    for (const G4Track* track : *secondaries) {
        // Only record gamma (X-ray) photons
        if (track->GetDefinition()->GetParticleName() == "gamma") {
            double energy = track->GetKineticEnergy(); // energy of individual gamma
            edxOut << energy / keV << std::endl;       // write each one separately
        }
    }
}

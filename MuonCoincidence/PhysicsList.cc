#include "G4EmStandardPhysics_option4.hh"
#include "G4SystemOfUnits.hh"

#include "PhysicsList.hh"
#include "G4EmLivermorePhysics.hh"  // Use low-energy EM physics
#include "G4EmPenelopePhysics.hh"  // Use low-energy EM physics
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"

PhysicsList::PhysicsList() : G4VModularPhysicsList() {
  defaultCutValue = 0.1*nm;   // default cut value

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  SetCutValue(defaultCutValue, "gamma");
  SetCutValue(defaultCutValue, "e-");
  SetCutValue(defaultCutValue, "e+");

    // see https://geant4.web.cern.ch/documentation/pipelines/master/plg_html/PhysicsListGuide/hadronic/index.html
    RegisterPhysics(new G4EmStandardPhysics_option4());
}

PhysicsList::~PhysicsList() {}

void PhysicsList::SetCuts() {
    SetCutsWithDefault(); // default cut values for all particles
}

void PhysicsList::ConstructProcess() {
    // Call base class to construct physics processes
    G4VModularPhysicsList::ConstructProcess();
}

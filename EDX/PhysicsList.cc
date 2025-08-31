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
    // RegisterPhysics(new G4EmStandardPhysics_option4()); // original
    RegisterPhysics(new G4EmLivermorePhysics());           // Low-energy EM physics (for XRAY)
    // RegisterPhysics(new G4EmPenelopePhysics())   ;      // Low-energy EM physics (for XRAY)
    // RegisterPhysics(new G4DecayPhysics());              // Particle decays
    // RegisterPhysics(new G4RadioactiveDecayPhysics());   // Optional, can be removed
}

PhysicsList::~PhysicsList() {}

void PhysicsList::SetCuts() {
    SetCutsWithDefault(); // default cut values for all particles
}

void PhysicsList::ConstructProcess() {
    // Call base class to construct physics processes
    G4VModularPhysicsList::ConstructProcess();

    // Enable atomic de-excitation (X-ray emission, Auger, PIXE)
    G4LossTableManager* lossManager = G4LossTableManager::Instance();

    /* JMF */
    G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(150*eV, 1*GeV); // JMF valid in Galactic
    auto* deexcitation = new G4UAtomicDeexcitation();
    deexcitation->SetFluo(true);   // Enable fluorescence X-rays
    deexcitation->SetAuger(true);  // Enable Auger electrons
    deexcitation->SetPIXE(true);   // Enable PIXE if needed

    lossManager->SetAtomDeexcitation(deexcitation);
}

/*
 * Use G4EmLivermorePhysics	Enables low-energy interactions, including shell ionization
Enable G4UAtomDeexcitation	Allows characteristic X-ray emission (fluorescence)
Set SetFluo(true)	Enables X-ray fluorescence
Set SetAuger(true)	Enables Auger electrons (complementary to X-rays)
*/
// even if low-energy physics is used, X-rays won't be emitted unless atomic de-excitation is enabled.

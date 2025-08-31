#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//#include "G4UIterminal.hh" // JMF

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "PhysicsList.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

int main(int argc, char** argv) {
    auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());

    runManager->SetUserAction(new PrimaryGeneratorAction());
    runManager->SetUserAction(new RunAction());
    runManager->SetUserAction(new EventAction());
    runManager->SetUserAction(new SteppingAction());

    runManager->Initialize();

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager::GetUIpointer()->ApplyCommand("/control/execute vis.mac");

/* JMF https://geant4-forum.web.cern.ch/t/interpreting-range-cuts-with-energy-thresholds/5831/5 */
//    G4double range = emCal.GetCSDARange(1.*keV, G4Electron::Electron(), alFeAlloy);
    ui->SessionStart();

    delete visManager;
    delete runManager;
    delete ui;

    return 0;
}

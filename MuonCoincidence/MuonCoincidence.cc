/*
Detector 0 hit times:
  0.000817503 us
  0.000817503 us
Detector 1 hit times:
  0.000483828 us
  0.000483828 us
(0.000817503-0.000483828)*300=10 cm !
*/

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

int main(int argc, char** argv) {
    auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    runManager->SetUserInitialization(new DetectorConstruction());
    // see https://geant4.in2p3.fr/IMG/pdf_PhysicsLists.pdf
    runManager->SetUserInitialization(new QGSP_BERT());
    runManager->SetUserAction(new PrimaryGeneratorAction());

    runManager->Initialize();

    auto visManager = new G4VisExecutive();
    visManager->Initialize();

    auto uiManager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        auto ui = new G4UIExecutive(argc, argv);
        uiManager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        uiManager->ApplyCommand(command + fileName);
    }

    delete visManager;
    delete runManager;
}

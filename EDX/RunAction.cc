#include "RunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

RunAction::RunAction() : G4UserRunAction() {
    // Create analysis manager (optional for future extension)
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);
}

RunAction::~RunAction() {
    delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/) {
    // Open output file (optional if using analysis manager)
    G4cout << "### Run started ###" << G4endl;

    // Reset random number seed per run for reproducibility
    G4RunManager::GetRunManager()->SetRandomNumberStore(false);
}

void RunAction::EndOfRunAction(const G4Run* run) {
    G4int nEvents = run->GetNumberOfEvent();
    if (nEvents == 0) return;

    G4cout << "### Run finished: " << nEvents << " events processed. ###" << G4endl;
}

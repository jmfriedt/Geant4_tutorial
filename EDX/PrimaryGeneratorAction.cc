#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    G4int nParticle = 1;
    fParticleGun = new G4ParticleGun(nParticle);

    auto particleTable = G4ParticleTable::GetParticleTable();
    auto electron = particleTable->FindParticle("e-");

    fParticleGun->SetParticleDefinition(electron);
    fParticleGun->SetParticleEnergy(40 * keV);
    // Set source position: 1 cm below target center
    fParticleGun->SetParticlePosition(G4ThreeVector(0, 0, -1 * cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

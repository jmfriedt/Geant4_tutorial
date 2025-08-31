#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1);

    auto particleTable = G4ParticleTable::GetParticleTable();
    auto muon = particleTable->FindParticle("mu-");

    fParticleGun->SetParticleDefinition(muon);
    fParticleGun->SetParticleEnergy(4*GeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    // Generate from above with some angle
    auto x = (G4UniformRand() - 0.5) * 10*cm;
    auto y = (G4UniformRand() - 0.5) * 10*cm;
    auto z = 20*cm;

    G4ThreeVector pos(x, y, z);
    G4ThreeVector dir(0, 0, -1);  // vertical muons

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(dir);
    fParticleGun->GeneratePrimaryVertex(event);
}

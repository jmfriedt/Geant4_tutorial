#ifndef EDXPrimaryGeneratorAction_h
#define EDXPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class EDXPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    EDXPrimaryGeneratorAction();
    virtual ~EDXPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event) override;

private:
    G4ParticleGun* fParticleGun; // pointer to the particle gun
};

#endif

#ifndef EDXDetectorConstruction_h
#define EDXDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class EDXDetectorConstruction : public G4VUserDetectorConstruction {
public:
    EDXDetectorConstruction();
    virtual ~EDXDetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override;
};

#endif

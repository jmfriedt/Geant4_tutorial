#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

// Constructor
DetectorConstruction::DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    G4NistManager* nist = G4NistManager::Instance();

    G4double worldSize = 10 * cm;
    //auto air = nist->FindOrBuildMaterial("G4_AIR");  // JMF air
    auto air = nist->FindOrBuildMaterial("G4_Galactic"); // JMF vacuum 

    G4Box* solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, true);

    // target
    // auto targetMat = nist->FindOrBuildMaterial("G4_Al");
    G4Element* elAl = nist->FindOrBuildElement("Al");
    G4Element* elFe = nist->FindOrBuildElement("Fe");

    // Define the Al-Fe alloy material
    // Example: 90% Al and 10% Fe by mass fraction (adjust as needed)
    G4double density = 2.7 * g/cm3;  // Approximate density, adjust if needed
    G4Material* alFeAlloy = new G4Material("AlFeAlloy", density, 2);
    alFeAlloy->AddElement(elAl, 0.90);
    alFeAlloy->AddElement(elFe, 0.10);

    // Aluminum-iron alloy target volume
    G4double targetSizeXY = 1*mm;
    G4double targetThickness = 1*mm;
    G4Box* solidTarget = new G4Box("Target", targetSizeXY, targetSizeXY, targetThickness);
    G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget, alFeAlloy, "Target");

    // Place the target at the center of the world
    new G4PVPlacement(0, G4ThreeVector(0,0,0), logicTarget, "Target", logicWorld, false, 0, true);
    return physWorld;
}

// Destructor
DetectorConstruction::~DetectorConstruction() {}

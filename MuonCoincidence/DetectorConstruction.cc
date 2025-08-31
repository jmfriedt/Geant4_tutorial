#include "DetectorConstruction.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "SensitiveDetector.hh"
#include "G4SDManager.hh"

DetectorConstruction::DetectorConstruction() {}
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    auto nist = G4NistManager::Instance();
    auto worldSize = 1.0 * m;
    auto worldBox = new G4Box("World", worldSize/2, worldSize/2, worldSize/2);
    auto worldMat = nist->FindOrBuildMaterial("G4_AIR");
    auto worldLV = new G4LogicalVolume(worldBox, worldMat, "World");
    auto worldPV = new G4PVPlacement(nullptr, {}, worldLV, "World", nullptr, false, 0);

    auto scintMat = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"); // material
    auto detSize = 10*cm;                                                    // detector dimensions
    auto detThick = 1*cm;
    auto detBox = new G4Box("Detector", detSize/2, detSize/2, detThick/2);
    auto det1LV = new G4LogicalVolume(detBox, scintMat, "Detector1");
    auto det2LV = new G4LogicalVolume(detBox, scintMat, "Detector2");
    new G4PVPlacement(nullptr, G4ThreeVector(0,0,-5*cm), det1LV, "Detector1", worldLV, false, 0);
    new G4PVPlacement(nullptr, G4ThreeVector(0,0, 5*cm), det2LV, "Detector2", worldLV, false, 1);

    auto sdMan = G4SDManager::GetSDMpointer();                               // sensitive detectors
    auto detectorSD = new SensitiveDetector("MuonDetector");
    sdMan->AddNewDetector(detectorSD);
    det1LV->SetSensitiveDetector(detectorSD);
    det2LV->SetSensitiveDetector(detectorSD);
    return worldPV;
}

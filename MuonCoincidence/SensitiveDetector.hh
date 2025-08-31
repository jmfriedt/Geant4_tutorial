#ifndef SENSITIVE_DETECTOR_HH
#define SENSITIVE_DETECTOR_HH

#include <G4VSensitiveDetector.hh>
#include <G4SystemOfUnits.hh>
#include <map>
#include <vector>

class G4Step;
class G4TouchableHistory;

class SensitiveDetector : public G4VSensitiveDetector {
public:
    SensitiveDetector(const G4String& name);
    virtual ~SensitiveDetector();

    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
    virtual void EndOfEvent(G4HCofThisEvent* hitCollection) override;

private:
    std::map<int, bool> detectorHits;
// add for 10 us window
    std::map<int, std::vector<G4double>> hitTimes;  // copyNo -> list of hit times
    const G4double coincidenceWindow = 10 * microsecond;
// add 50 us deadtime
    std::map<int, G4double> lastHitTime;
    const G4double deadTime = 50 * microsecond;      
};

#endif

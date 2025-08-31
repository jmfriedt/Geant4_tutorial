#include "SensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include <iostream>

SensitiveDetector::SensitiveDetector(const G4String& name)
    : G4VSensitiveDetector(name) {}

SensitiveDetector::~SensitiveDetector() {}

G4bool SensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    auto preStepPoint = step->GetPreStepPoint();
    auto physVol = preStepPoint->GetTouchableHandle()->GetVolume();
    int copyNo = preStepPoint->GetTouchableHandle()->GetCopyNumber();

    // add measurement of deposited energy
    G4double edep = step->GetTotalEnergyDeposit(); // in MeV
    if (edep <= 0) return false;
    std::cout << "Detector " << copyNo << " triggered: Edep = " << edep / MeV << "\n";

    // aded for 10 us window
    G4double globalTime = preStepPoint->GetGlobalTime();

    // 50 us deadtime
    G4double time = preStepPoint->GetGlobalTime();
    if (lastHitTime.count(copyNo) == 0 || (time - lastHitTime[copyNo]) > deadTime) {
        hitTimes[copyNo].push_back(time);
        lastHitTime[copyNo] = time;
    }
    // end of deadtime

    // Mark this detector as hit
    detectorHits[copyNo] = true;

    // added for 10 us window
    hitTimes[copyNo].push_back(globalTime);

    return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*) {
    if (detectorHits.size() >= 2) {
        std::cout << "[Coincidence] Muon detected in both detectors!" << std::endl;
    }

    // added for coincidence window
    if (hitTimes.size() >= 2 &&
        hitTimes.count(0) > 0 &&
        hitTimes.count(1) > 0) {

        const auto& hits0 = hitTimes[0];
        const auto& hits1 = hitTimes[1];

        bool coincidenceFound = false;

        for (auto t0 : hits0) {
            for (auto t1 : hits1) {
                if (std::abs(t0 - t1) <= coincidenceWindow) {
                    coincidenceFound = true;
                    break;
                }
            }
            if (coincidenceFound) break;
        }

        if (coincidenceFound) {
            std::cout << "[Coincidence] Detectors fired within 10 us!" << std::endl;
            std::cout << "Detector 0 hit times:\n";
            for (auto t : hitTimes[0]) std::cout << "  " << t / microsecond << " us\n";
            std::cout << "Detector 1 hit times:\n";
            for (auto t : hitTimes[1]) std::cout << "  " << t / microsecond << " us\n";
        }
    }

    hitTimes.clear();
    lastHitTime.clear();
    detectorHits.clear();
}


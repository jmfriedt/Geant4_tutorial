cmake_minimum_required(VERSION 3.16)
project(MuonCoincidence)

find_package(Geant4 REQUIRED ui_all vis_all)

add_executable(MuonCoincidence
    MuonCoincidence.cc
    DetectorConstruction.cc
    PrimaryGeneratorAction.cc
    SensitiveDetector.cc
    PhysicsList.cc
)

target_include_directories(MuonCoincidence PRIVATE ${Geant4_INCLUDE_DIRS})
target_link_libraries(MuonCoincidence PRIVATE ${Geant4_LIBRARIES})

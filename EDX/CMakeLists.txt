cmake_minimum_required(VERSION 3.16)
project(EDX)

find_package(Geant4 REQUIRED ui_all vis_all)

add_executable(EDX
    EDX.cc
    DetectorConstruction.cc
    PrimaryGeneratorAction.cc
    PhysicsList.cc
    RunAction.cc
    EventAction.cc
    SteppingAction.cc
)

target_include_directories(EDX PRIVATE ${Geant4_INCLUDE_DIRS})
target_link_libraries(EDX PRIVATE ${Geant4_LIBRARIES})


#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "PhysicsListMessenger.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList
{
public:
  PhysicsList();
 ~PhysicsList();

public:
  virtual void ConstructParticle();
  virtual void ConstructProcess();
  virtual void SetCuts();
  void AddPhysicsList(const G4String& name);
  G4VPhysicsConstructor*        fEmPhysicsList; 
  G4String                      fEmName;
  PhysicsListMessenger *fMessenger;
  void AddDecay();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
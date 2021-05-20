#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "Analysis.hh"




#include <vector>
class DetectorConstruction;
class G4Event;

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction();
  virtual void GeneratePrimaries(G4Event*);
   G4ParticleGun* GetParticleGun() {return fParticleGun;}


private:
  G4ParticleGun* fParticleGun;
};
#endif

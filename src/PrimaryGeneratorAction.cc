#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "Analysis.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4RunManager.hh"
#include "G4ChargedGeantino.hh"
#include "Randomize.hh"
#include "G4PhysicalConstants.hh"
//#include "G4MTRandGauss.hh"
#include "CLHEP/Random/RandGauss.h"

#include <time.h>



PrimaryGeneratorAction::PrimaryGeneratorAction()
  : G4VUserPrimaryGeneratorAction(),
    fParticleGun(0)
{
  fParticleGun=new G4ParticleGun(1);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* part
                    = particleTable->FindParticle("e-");
  fParticleGun->SetParticleDefinition(part);  
  
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  
   // position 
  G4double posZ=0*cm, posX=0*cm, posY=0*cm;
  G4double a=2.*pi*G4UniformRand(); //angle
  G4double rc=(std::sqrt(1./pi))*mm;//radius
  G4double r=(rc*std::sqrt(G4UniformRand()));
  G4double Xo=0.*mm, Yo=0.*mm;//origin 
  posX=r*std::cos(a)+Xo;
  posY=r*std::sin(a)+Yo;
  G4LogicalVolume* cellVolume=G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox=dynamic_cast<G4Box*>(cellVolume->GetSolid());
  posZ=worldBox->GetZHalfLength();
  posZ=-(posZ);
  fParticleGun->SetParticlePosition(G4ThreeVector(posX,posY,posZ));

  // Energy
  G4long seed=time(NULL);
  CLHEP::HepRandomEngine* randGen = new CLHEP::RanecuEngine;
  randGen->setSeed(seed,0);
  CLHEP::RandGauss *Grand=new CLHEP::RandGauss(randGen);
  G4double Emean=15.;//MeV
  G4double E = Emean;
  //G4double Esigma=0.03;//MeV
  //G4double E=(Grand->shoot(Emean,Esigma))*MeV;
  fParticleGun->SetParticleEnergy(E);
  //G4cout<<G4BestUnit(E,"Energy")<<G4endl;
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1));
  fParticleGun->GeneratePrimaryVertex(anEvent);

  /*
  {
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(1,0,posX);
    analysisManager->FillNtupleDColumn(1,1,posY);
    analysisManager->FillNtupleDColumn(1,2,E);
    analysisManager->AddNtupleRow(1);
  }
  */
  delete Grand;
}


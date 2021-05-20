#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4EventManager.hh"
#include "Analysis.hh"
#include "G4HadronicProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4Isotope.hh"

SteppingAction::SteppingAction()
  : G4UserSteppingAction()
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  // Get energy deposit and step length for current step:
  G4double edep=step->GetTotalEnergyDeposit();
  G4double stepL=step->GetStepLength();

  // Get pointers to pre-point, post-point, track for current step
  G4StepPoint* prePoint=dynamic_cast<G4StepPoint*>(step->GetPreStepPoint());
  if (!prePoint)
    {
      G4cout<<"No point assciated or step -Exitting!!!"<<G4endl;
      exit(0);
    }
  G4double preE = prePoint->GetKineticEnergy();

  G4StepPoint* postPoint=dynamic_cast<G4StepPoint*>(step->GetPostStepPoint());
  if (!postPoint)
    {
      G4cout<<"No point associated to step - Exiting!!!"<<G4endl;
      exit(0);
    }
  
  G4Track *track=dynamic_cast<G4Track*>(step->GetTrack());
  if (!track)
    {
      G4cout<<"No track associated to step - Exiting!!!"<<G4endl;
      exit(0);
    }
  G4ParticleDefinition *particle=track->GetDefinition();
  G4String partname=particle->GetParticleName();
  G4int parentID = track->GetParentID();
  G4int Apro=particle->GetAtomicMass();
  G4int Zpro=particle->GetAtomicNumber();
  // Get current volume
  G4VPhysicalVolume*
    stepVol=dynamic_cast<G4VPhysicalVolume*>(prePoint->GetTouchableHandle()->GetVolume());
  if (!stepVol)
    {
      G4cout<<"No volume associated to step - Exiting!!!"<<G4endl;
      exit(0);
    }
  
  

  // det ID
  G4int iDet=-1;
  if (stepVol->GetName() == "Target") iDet=4;
  else if (stepVol->GetName() == "World") iDet=1;
  else if (stepVol->GetName() == "Brem") iDet=2;
  else if (stepVol->GetName() == "Col") iDet=3;


  // // event ID
  G4int eventID=G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
  G4VProcess* process=const_cast<G4VProcess*>(postPoint->GetProcessDefinedStep());
  G4HadronicProcess* hproc = dynamic_cast<G4HadronicProcess*>(process);
  const G4Isotope* target=NULL;
  G4String targetName="";
  G4int Ztar=0;
  G4int Atar = 0;
  if (hproc)
    {/*
      target = hproc->GetTargetIsotope();
      targetName = target->GetName();
      Ztar = target->GetZ();
      Atar=target->GetN();
      */
    }

 
 
    // 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  if ((partname == "gamma") && (iDet==4) && (prePoint->GetStepStatus() == fGeomBoundary)&& preE>0){
    analysisManager->FillNtupleDColumn(1,0,preE);
    analysisManager->AddNtupleRow(1);
  }


   const std::vector<const G4Track*>* secondary
   	= step->GetSecondaryInCurrentStep();
   //if ((*secondary).size() >0 && (iDet==4) && (hproc))
   if ((*secondary).size() >0 && (iDet==2))
     {
       G4bool isEu152=false;
       for (size_t nn=0;nn<(*secondary).size();nn++)
     {
       G4ParticleDefinition* part=(*secondary)[nn]->GetDefinition();
       G4String name=part->GetParticleName();
       if (name == "neutron") isEu152=true;
       }

      for (size_t nn=0;nn<(*secondary).size();nn++)
   	{
   	  G4ParticleDefinition* part=(*secondary)[nn]->GetDefinition();
   	  G4String name=part->GetParticleName();
   	  //if (name == "e-") fEventAction->AddElectron(1);
      //if (name != "Eu152")
        if (iDet ==2){
   	      //G4cout<<"Part#"<<nn<<": "<<name<<";\t at "<<iDet<<G4endl;
   	      G4int A=part->GetAtomicMass();
   	      G4int Z=part->GetAtomicNumber();
   	      G4double E=(*secondary)[nn]->GetKineticEnergy();
   	      G4ThreeVector mVtx=(*secondary)[nn]->GetMomentumDirection();
   	      G4double TrkTheta=mVtx.theta();
   	      G4int paID = (*secondary)[nn]->GetParentID();
   	      analysisManager->FillNtupleDColumn(0,0,E);
   	      analysisManager->FillNtupleDColumn(0,1,TrkTheta);
   	      analysisManager->FillNtupleIColumn(0,2,Z);
   	      analysisManager->FillNtupleIColumn(0,3,A);
   	      analysisManager->FillNtupleIColumn(0,4,paID);
   	      analysisManager->FillNtupleIColumn(0,5,eventID);
   	      analysisManager->FillNtupleSColumn(0,6,name);
   	      analysisManager->AddNtupleRow(0);

   	    }
	  
   	}
     }
}
  //----------------------------------------------------------------

  

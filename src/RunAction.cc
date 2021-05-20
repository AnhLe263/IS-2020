#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
//#include "G4ParameterManager.hh"
#include "Randomize.hh"
#include <iomanip>
#include "Analysis.hh"

RunAction::RunAction()
  : G4UserRunAction()
{
  G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
  analysisManager->SetNtupleMerging(true);
  
  analysisManager->CreateNtuple("Fairy","step Inform");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleDColumn("Theta");
  analysisManager->CreateNtupleIColumn("Z"); 
  analysisManager->CreateNtupleIColumn("A");
  analysisManager->CreateNtupleIColumn("ParentID");
  analysisManager->CreateNtupleIColumn("eventID");
  analysisManager->CreateNtupleSColumn("partName");
  analysisManager->FinishNtuple(0);
/*
  analysisManager->CreateNtuple("BeamInfo","step Inform");
  analysisManager->CreateNtupleDColumn("X");
  analysisManager->CreateNtupleDColumn("Y");
  analysisManager->CreateNtupleDColumn("E");
  analysisManager->FinishNtuple(1);
*/

  analysisManager->CreateNtuple("BremSpec","step Inform");
  analysisManager->CreateNtupleDColumn("E");
  analysisManager->FinishNtuple(1);


  
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}



void RunAction::BeginOfRunAction(const G4Run*)
{
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "result";
  analysisManager->OpenFile(fileName);
  //analysisManager->SetActivation(true);

  
}


void RunAction::EndOfRunAction(const G4Run*)
{
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

 
  if (IsMaster())
    {
      G4cout<<"-------------------End of global run---------------------\n";
    }
  else G4cout<<"-------------------End of local run---------------------\n";

  
}



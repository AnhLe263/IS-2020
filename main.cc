
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif


#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "time.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

int main(int argc,char** argv) {
 
  //choose the Random engine
  G4long seed=time(NULL);
  CLHEP::HepRandomEngine* randGen = new CLHEP::RanecuEngine;
  G4Random::setTheEngine(randGen); // choose the Random engine
  G4Random::setTheSeed(seed);
  
  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  //runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
  runManager->SetNumberOfThreads(1);
#else
  G4RunManager* runManager = new G4RunManager;
#endif  


  // set mandatory initialization classes
  //
  DetectorConstruction *det=new DetectorConstruction;
  runManager->SetUserInitialization(det);
  runManager->SetUserInitialization(new PhysicsList);
      
  // set user action classes
  // 
  runManager->SetUserInitialization(new ActionInitialization);
    
  //Initialize G4 kernel
  runManager->Initialize();

  // get the pointer to the User Interface manager 
  G4UImanager* UI = G4UImanager::GetUIpointer();  

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  if (argc!=1)   // batch mode  
    { 
     G4String command = "/control/execute ";
     G4String fileName = argv[1];
     UI->ApplyCommand(command+fileName);  
    }
    
  else           // define visualization and UI terminal for interactive mode 
    { 
#ifdef G4UI_USE
     G4UIExecutive * ui = new G4UIExecutive(argc,argv);      
#ifdef G4VIS_USE
    UI->ApplyCommand("/control/execute vis.mac");
#endif
     ui->SessionStart();
     delete ui;
#endif
    }

#ifdef G4VIS_USE
  delete visManager;
#endif     

  // job termination
  //
  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo..... 


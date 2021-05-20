#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include "Analysis.hh"
//#include "G4Parameter.hh"


class DetectorConstruction;
#include "PrimaryGeneratorAction.hh"
class G4Run;

class RunAction: public G4UserRunAction
{
public:
  RunAction();
  ~RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);

  
private:
  
};

#endif

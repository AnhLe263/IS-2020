#ifndef Stepping_h
#define Stepping_h

#include "G4UserSteppingAction.hh"
#include "RunAction.hh"
#include "Analysis.hh"
//#include "EventAction.hh"
class SteppingAction: public G4UserSteppingAction
{
public:
  SteppingAction();
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step* step);

};
#endif

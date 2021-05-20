#ifndef Anh_Phys
#define Anh_Phys

#include "G4VUserPhysicsList.hh"

class PhysicsList: public G4VUserPhysicsList
{
public:
  PhysicsList();
  ~PhysicsList();
protected:
  void ConstructParticle();
  void ConstructProcess();
};
#endif

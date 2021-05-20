#ifndef Anh_det
#define Anh_det

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"
class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();
  virtual G4VPhysicalVolume* Construct();
};
#endif

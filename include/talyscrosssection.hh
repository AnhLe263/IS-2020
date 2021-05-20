#ifndef TALYSCROSSSECTION_HH
#define TALYSCROSSSECTION_HH
#include "G4VCrossSectionDataSet.hh"
#include "G4HadronInelasticDataSet.hh"
#include "TGraph.h"
#include "TSpline.h"
class talyscrosssection:public G4VCrossSectionDataSet
{
public:
    talyscrosssection();
    ~talyscrosssection();
    virtual G4bool IsIsoApplicable(const G4DynamicParticle *, G4int Z, G4int A, const G4Element *elm, const G4Material *mat);
    virtual G4double GetIsoCrossSection(const G4DynamicParticle *, G4int Z, G4int A, const G4Isotope *iso, const G4Element *elm, const G4Material *mat);
    G4double GetIsomericPropability(G4int mid,G4double E);
    G4int GetNumberOfIsomericStates() {return N;}
private:
    G4int N;
    TGraph **gr;
    //TSpline5* spline;
  //TGraph* gr2;
    TSpline5 **spline;
    G4HadronInelasticDataSet* fGheisa;

};
#endif // TALYSCROSSSECTION_HH

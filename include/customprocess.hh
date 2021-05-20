#ifndef CUSTOMPROCESS_HH
#define CUSTOMPROCESS_HH
#include "G4HadronInelasticProcess.hh"
#include "talyscrosssection.hh"
#include "G4PhotoNuclearCrossSection.hh"
class customprocess: public G4HadronInelasticProcess
{
public:
    customprocess(const G4String& processName="customProcess")
        : G4HadronInelasticProcess(processName,G4Gamma::Gamma())
    {
        G4CrossSectionDataStore* theStore= GetCrossSectionDataStore();
        theStore->AddDataSet(new talyscrosssection);
    }
    ~customprocess() {}
};
#endif // CUSTOMPROCESS_HH

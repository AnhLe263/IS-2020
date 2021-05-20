#include "talyscrosssection.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4DynamicParticle.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
talyscrosssection::talyscrosssection()
    : G4VCrossSectionDataSet("GammaEu153"),N(3)
{
    N=3;
    std::string fName[N];
    fName[0]="Eu152m0ld2.txt";
    fName[1]="Eu152m1ld2.txt";
    fName[1]="Eu152m2ld2.txt";
    gr = new TGraph*[N];
    spline = new TSpline5*[N];
    gr[0]=new TGraph("Eu152m0ld6.txt");
    gr[1]=new TGraph("Eu152m1ld6.txt");
    gr[2]=new TGraph("Eu152m2ld6.txt");
    for (G4int i=0;i<N;i++){
        //gr[i]=new TGraph(fName[i].c_str());
        spline[i]=new TSpline5("fitting",gr[i]);
    }
    fGheisa=new G4HadronInelasticDataSet();
}


talyscrosssection::~talyscrosssection(){
    delete [] spline;
    delete [] gr;
    //delete spline2;
    //delete gr2;
    delete fGheisa;
}


G4bool talyscrosssection::IsIsoApplicable(const G4DynamicParticle *aPart, G4int Z, G4int A, const G4Element *elm, const G4Material *mat)
{
    return true;//(1<=aPart->GetDefinition()->GetBaryonNumber());
}



G4double talyscrosssection::GetIsoCrossSection(const G4DynamicParticle *aPart, G4int Z, G4int A, const G4Isotope *iso, const G4Element *elm, const G4Material *mat)
{
    G4double cross_section=0.*millibarn;
    G4double Ekin=0.*MeV;
    Ekin=aPart->GetKineticEnergy();
    G4double bias=1;

    if ((Z==63) && (A==153)) {
        for (G4int i=0;i<N;i++){
            G4double tmp=(spline[i]->Eval(Ekin)*bias)*millibarn;
            if (tmp<0) tmp=0;
            cross_section += tmp;
        }
    }
    else cross_section =  fGheisa->GetElementCrossSection(aPart,Z,mat);

    if (cross_section <0 ) cross_section=0.*millibarn;
    //G4cout<<"A= "<<A<<"\tZ="<<Z<<"\tE= "<<Ekin<<"\tcross= "<<G4BestUnit(cross_section,"Surface")<<G4endl;
    //G4cout<<GetIsomericPropability(1,20*MeV)<<G4endl;
    return cross_section;
}

G4double talyscrosssection::GetIsomericPropability(G4int mid, G4double E)
{
    if (mid >=N){
        G4cerr<<"isomesic state "<<mid<<" do not exist."<<G4endl;
        return 0;
    }
G4double tmp=0;
for (G4int i=0;i<N;i++){
    tmp += spline[i]->Eval(E);
}

return spline[mid]->Eval(E)/tmp;
}

#include "PhysicsList.hh"

#include "G4PhysicsListHelper.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhotoNuclearCrossSection.hh"
#include "talyscrosssection.hh"
#include "custommodel.hh"
#include "G4GammaNuclAngDst.hh"
PhysicsList::PhysicsList() : G4VUserPhysicsList()
{}

PhysicsList::~PhysicsList() {}

// construct particle
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

void PhysicsList::ConstructParticle()
{
  G4BosonConstructor bosonConst;
  bosonConst.ConstructParticle();

  G4LeptonConstructor leptonConst;
  leptonConst.ConstructParticle();

  G4MesonConstructor mesonConst;
  mesonConst.ConstructParticle();

  G4BaryonConstructor baryonConst;
  baryonConst.ConstructParticle();

  G4IonConstructor ionConst;
  ionConst.ConstructParticle();

  G4ShortLivedConstructor shortLivedConst;
  shortLivedConst.ConstructParticle();
}

// Processes
// General
#include "G4Decay.hh"
#include "G4RadioactiveDecay.hh"
//for gamma
#include "G4ComptonScattering.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4GammaConversion.hh"
//for e- and e+
#include "G4eIonisation.hh"
#include "G4eMultipleScattering.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4PhotoNuclearProcess.hh"
#include "G4CascadeInterface.hh"
#include "G4BinaryCascade.hh"
#include "G4CascadeParameters.hh"
#include "G4LENDorBERTModel.hh"

#include "G4hMultipleScattering.hh"
#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"
#include "customprocess.hh"
void PhysicsList::ConstructProcess()
{
  AddTransportation();

  G4PhysicsListHelper* ph =G4PhysicsListHelper::GetPhysicsListHelper();
  
  GetParticleIterator()->reset();
  while ((*GetParticleIterator())())
    {
      G4ParticleDefinition* particle=GetParticleIterator()->value();
      G4String partName=particle->GetParticleName();
      G4Decay *aDecay=new G4Decay();
      if (aDecay->IsApplicable(*particle)) ph->RegisterProcess(aDecay,particle);
      G4RadioactiveDecay* aRadioactiveDecay=new G4RadioactiveDecay();
      aRadioactiveDecay->SetARM(false);
      ph->RegisterProcess(aRadioactiveDecay,particle);
      if (partName == "gamma")
	{
	  ph->RegisterProcess(new G4ComptonScattering(),particle);
	  ph->RegisterProcess(new G4PhotoElectricEffect(),particle);
	  ph->RegisterProcess(new G4GammaConversion(),particle);
      G4PhotoNuclearProcess* InPro = new G4PhotoNuclearProcess;
      //customprocess* InPro = new customprocess;
      InPro->BiasCrossSectionByFactor(100.);
      //G4CascadeInterface* Bert=new G4CascadeInterface;
      //Bert->usePreCompoundDeexcitation();
      //Bert->useCascadeDeexcitation();
      //InPro->RegisterMe(Bert);
      //InPro->RegisterMe(new G4BinaryCascade);
      //G4LENDorBERTModel *lend=new G4LENDorBERTModel(particle);
      //lend->SetMinEnergy(0*keV);
      //lend->SetMaxEnergy(500*MeV);
      //InPro->RegisterMe(lend);
      talyscrosssection* Xs=new talyscrosssection;
      InPro->AddDataSet(Xs);
      custommodel* customModel=new custommodel;
      //InPro->RegisterMe(customModel);
      //ph->RegisterProcess(InPro,particle);
	}
      else if (partName == "e-" || partName == "e+")
	{
	  ph->RegisterProcess(new G4eMultipleScattering(),particle);
	  ph->RegisterProcess(new G4eBremsstrahlung(),particle);
	  ph->RegisterProcess(new G4eIonisation(),particle);
	  if (partName == "e+")
	    ph->RegisterProcess(new G4eplusAnnihilation(),particle);
	}
      else if (partName=="GenericIon")
            {

       ph->RegisterProcess(new G4hMultipleScattering(),particle);
                G4ionIonisation* ionIon=new G4ionIonisation();
       ionIon->SetEmModel(new G4IonParametrisedLossModel());
       ph->RegisterProcess(ionIon,particle);
       ph->RegisterProcess(new G4NuclearStopping,particle);

      }
    }
}



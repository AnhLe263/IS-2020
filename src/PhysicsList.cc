#include "PhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmStandardPhysicsWVI.hh"
#include "G4EmStandardPhysicsGS.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmLowEPPhysics.hh"
#include "G4EmParameters.hh"
#include "GammaNuclearPhysics.hh"
PhysicsList::PhysicsList(): G4VModularPhysicsList()
{
    fMessenger = new PhysicsListMessenger(this);
    fEmPhysicsList = new G4EmStandardPhysics();
}

PhysicsList::~PhysicsList()
{

}
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
void PhysicsList::ConstructParticle()
{

    G4BosonConstructor  pBosonConstructor;
    pBosonConstructor.ConstructParticle();

    G4LeptonConstructor pLeptonConstructor;
    pLeptonConstructor.ConstructParticle();

    G4MesonConstructor pMesonConstructor;
    pMesonConstructor.ConstructParticle();

    G4BaryonConstructor pBaryonConstructor;
    pBaryonConstructor.ConstructParticle();

    G4IonConstructor pIonConstructor;
    pIonConstructor.ConstructParticle();

    G4ShortLivedConstructor pShortLivedConstructor;
    pShortLivedConstructor.ConstructParticle(); 
}


void PhysicsList::ConstructProcess()
{
    // transportation
    //
    AddTransportation();
  
    // electromagnetic physics list
    //
    fEmPhysicsList->ConstructProcess();
    // Gamma
    GammaNuclearPhysics* gammaN=new GammaNuclearPhysics();
    gammaN->ConstructProcess();
    // decay process

    //
    AddDecay();
}


void PhysicsList::AddPhysicsList(const G4String& name)
{
    if (verboseLevel>-1) {
        G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
    }

    if (name == "emstandard_opt0") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics();
    
    } else if (name == "emstandard_opt1") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option1();

    } else if (name == "emstandard_opt2") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option2();
        
    }  else if (name == "emstandard_opt3") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option3();
    
    } else if (name == "emstandard_opt4") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysics_option4();
    
    } else if (name == "emstandardSS") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsSS();

    } else if (name == "emstandardWVI") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsWVI();

    } else if (name == "standardGS") {

    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmStandardPhysicsGS();
                    
    } else if (name == "emlivermore") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLivermorePhysics();
    
    } else if (name == "empenelope") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmPenelopePhysics();

    } else if (name == "emlowenergy") {
    fEmName = name;
    delete fEmPhysicsList;
    fEmPhysicsList = new G4EmLowEPPhysics();

    } else {

    G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
           << " is not defined"
           << G4endl;
    }
    G4EmParameters::Instance()->SetBuildCSDARange(true);
}


void PhysicsList::SetCuts()
{
    //SetDefaultCutValue();
}

#include "G4GenericIon.hh"
#include "G4Radioactivation.hh"
void PhysicsList::AddDecay()
{
  // decay process
  //
  //G4Decay* fDecayProcess = new G4Decay();
 G4PhysicsListHelper* ph =G4PhysicsListHelper::GetPhysicsListHelper();
  auto particleIterator=GetParticleIterator();
  particleIterator->reset();
  while( (*particleIterator)() ){
    G4ParticleDefinition* particle = particleIterator->value();
     G4String partName=particle->GetParticleName();
      if (partName=="GenericIon")
	{
	  G4Radioactivation* radioactiveDecay = new G4Radioactivation();
	  radioactiveDecay->SetARM(true);               //Atomic Rearangement
	  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());
	}
  }
}
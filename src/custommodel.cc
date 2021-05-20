#include "custommodel.hh"
#include "G4NucleiProperties.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4MTRandGeneral.hh"
#include "Randomize.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4IonTable.hh"
#include "G4Proton.hh"
#include "G4Deuteron.hh"
#include "G4GammaNuclAngDst.hh"
#include "G4VTwoBodyAngDst.hh"
#include "G4TwoBodyAngularDist.hh"
G4HadFinalState* custommodel::ApplyYourself(const G4HadProjectile &aTrack, G4Nucleus &targetNucleus)
{
    theParticleChange.Clear();
    theParticleChange.SetStatusChange( stopAndKill );
    theParticleChange.SetEnergyChange( 0.0 );



    // Projectile gamma
    G4double ma = 0.*kg;
    G4double Ta = aTrack.GetKineticEnergy();
    //Target
    G4int Ztar = targetNucleus.GetZ_asInt();
    G4int Atar =  targetNucleus.GetA_asInt();
    G4double mX = G4NucleiProperties::GetNuclearMass(Atar,Ztar);
    // choose reaction, which isomeric state
    G4int N = talysXcross->GetNumberOfIsomericStates();
    G4double *Exm=new G4double[N];
    Exm[0]=0*MeV;
    Exm[1]=45.5998*keV;
    Exm[2]=147.86*keV;
    G4double P[N];
    P[0] = talysXcross->GetIsomericPropability(0,Ta);
    P[1] = talysXcross->GetIsomericPropability(1,Ta);
    P[2] = talysXcross->GetIsomericPropability(2,Ta);

    // sapw xeplaij nho ->Lon
    for (G4int i=0;i<N;i++){
        for (G4int j=i+1;j<N;j++){
            if (P[i]>=P[j]){
                G4double tmp=P[i];
                P[i] = P[j];
                P[j] = tmp;
                tmp=Exm[i];
                Exm[i]=Exm[j];
                Exm[j]=tmp;
            }
        }
    }

    G4double Ex=0*MeV;
    G4double sum=0;
    G4double r=G4UniformRand();
    for (G4int i=0;i<N;i++){
        if (i==0) sum=P[i];
        else sum += P[i];
        if (r<=sum){
            Ex = Exm[i];
            break;
        }
    }

    // San pham sau phan ung
    // neutron
    G4double Zp=0;
    G4double Ap=1;
    G4double mb =  G4NucleiProperties::GetNuclearMass(Ap,Zp);
    // Residual
    G4int ZC = Ztar  - Zp;
    G4int AC =  Atar  - Ap;
    G4double mY = G4NucleiProperties::GetNuclearMass(AC,ZC);


    G4double Q = mX + ma - mY -mb;
    Q -= Ex;
    // Angular distribution of Proton of deuteron

    G4double p_theta=GetRandomTheta()*rad;
    //G4double p_theta=G4UniformRand()*pi;
    G4double Tb = GetTb(ma,mX,mb,mY,Ta,Q,p_theta);
    G4double p_phi = 0*rad;
    p_phi = G4UniformRand()*twopi;

    //Angular distribution of Residual
    G4double Res_theta = 0*rad;
    Res_theta = G4UniformRand()*pi;
    G4double Res_phi =0* rad;
    Res_phi = G4UniformRand()*twopi;
    G4double Ty = Ta-Tb+Q;

    // Add theParticleChange
    /* Residual-------------------*/

    G4ParticleDefinition* DefRes = G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(ZC,AC,Ex);
    G4ThreeVector secDir1(0.,0.,0);
    secDir1.setRThetaPhi(1,Res_theta,Res_phi);
    G4DynamicParticle* gRes = new G4DynamicParticle(DefRes,secDir1,Ty);
    theParticleChange.AddSecondary(gRes);

    //proton or deuteron
    //Thu chua boost xem the nao
    //G4GammaNuclAngDst* angDis=new G4GammaNuclAngDst;
    //angDis->GetCosTheta
    G4ThreeVector secDir2(0,0,0);
    secDir2.setRThetaPhi(1,p_theta,p_phi);
    G4DynamicParticle* gPro= new G4DynamicParticle(G4Neutron::NeutronDefinition(),secDir2,Tb);


    theParticleChange.AddSecondary(gPro);

    return &theParticleChange;
}


G4double custommodel::GetTb(G4double ma, G4double mX, G4double mb, G4double mY,G4double Ta, G4double Q, G4double theta)
{
G4double Tb=0;

G4double tmp1=ma*mb*Ta;
tmp1 = std::sqrt(tmp1);
tmp1 *= std::cos(theta);

G4double tmp2 = ma*mb*Ta*std::cos(theta)*std::cos(theta);
G4double tmp3 = (mY+mb)*(mY*Q + (mY-ma)*Ta);
G4double tmp4 = tmp2+tmp3;
tmp4 = std::sqrt(tmp4);
Tb = (tmp1 - tmp4)/(mY + mb);
if (Tb <0) Tb = (tmp1 + tmp4)/(mY + mb);
if (Tb <0) Tb=0;
Tb *= Tb;
return Tb;
}


G4double custommodel::GetRandomTheta()
{
    G4MTRandGeneral* r=new G4MTRandGeneral(Theta,360,0);
    G4double a =  r->shoot();
    delete r;
    return 3.14*a;
}


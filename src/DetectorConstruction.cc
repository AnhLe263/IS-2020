#include "DetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

DetectorConstruction::DetectorConstruction()
  :G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Material
  G4NistManager* nist=G4NistManager::Instance();
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* brem_mat = nist->FindOrBuildMaterial("G4_W");
  G4Material* brem_mat2 = nist->FindOrBuildMaterial("G4_Pt");
  G4Material* col_mat = nist->FindOrBuildMaterial("G4_Pb");
  G4Material* Al = nist->FindOrBuildMaterial("G4_Al");
  G4Material* tar_mat = nist->FindOrBuildMaterial("G4_Eu");
  G4Material* water = nist->FindOrBuildMaterial("G4_WATER");
  // Eu2O3
  G4Isotope *IO=new G4Isotope("Oxygen",8,16,16.00*g/mole);
  G4Element *elO=new G4Element("Oxygen","O",1);
  elO->AddIsotope(IO,100.*perCent);

  G4Isotope *IEu151=new G4Isotope("Eu151",63,151,151.00*g/mole);
  G4Isotope *IEu153=new G4Isotope("Eu153",63,153,153.00*g/mole);
  G4Element *elEu=new G4Element("Eu","Eu",1);
  //elEu->AddIsotope(IEu151,47.8*perCent);
  //elEu->AddIsotope(IEu153,52.2*perCent);
  elEu->AddIsotope(IEu153,100*perCent);
  G4double EuDen=7.40*g/cm3;
  //G4Material *Eumat=new G4Material("Eu",EuDen,2);
  //Eumat->AddElement(elEu,2);
  //Eumat->AddElement(elO,3);
  G4Material *Eu153=new G4Material("Eu",EuDen,1);
  Eu153->AddElement(elEu,1);
  //G4Material* tar_mat=Eumat;
  G4cout << *(G4Material::GetMaterialTable()); 
  // World
  G4double world_XY = 40.*cm;
  G4double world_Z = 80.*cm;
  G4Box* solidWorld =    
    new G4Box("World",0.5*world_XY, 0.5*world_XY, 0.5*world_Z); 
      
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,world_mat,"World");
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false,0,true);
  // Target for brem emission
  G4double xy = 100.*mm;
  G4double z = 0.1*mm; //thay do
  //G4double z = 0.3*mm; //thay Thie
  //G4double z = 3*mm; //Kato
  //G4double AlZ=20.*mm;
  //G4double disAlTar = 2.7*cm;
  //Co Chau H2O sau target
  G4Box* solidBrem =    
    new G4Box("Brem",0.5*xy, 0.5*xy, 0.5*z); 
      
  G4LogicalVolume* logicBrem = new G4LogicalVolume(solidBrem,brem_mat,"Brem");
  G4double pos=0*mm;
                                    
  new G4PVPlacement(0,G4ThreeVector(0,0,pos),logicBrem,"Brem",logicWorld,false,0,true);


  //G4Box* solidAl=
  //  new G4Box("Al",0.5*xy, 0.5*xy, 0.5*AlZ);

  //G4LogicalVolume* logicAl = new G4LogicalVolume(solidAl,Al,"Al");
  //pos=-disAlTar - AlZ/2.;
  //new G4PVPlacement(0,G4ThreeVector(0,0,pos),logicAl,"Al",logicWorld,false,0,true);

  //H20
  G4double water_Z = 10.*cm;
  G4double water_XY = 10.*cm;
  G4double disWater = 1.*cm;
  G4double posWaterZ = water_Z/2. + disWater + z/2.;
  G4Box* solidWater= new G4Box("Water",0.5*water_XY, 0.5*water_XY, 0.5*water_Z);
  G4LogicalVolume* logicWater = new G4LogicalVolume(solidWater,water,"Water");
  new G4PVPlacement(0,G4ThreeVector(0,0,posWaterZ),logicWater,"Water",logicWorld,false,0,true);
  //Collimator
  // G4double innerRadius=.1*cm;
  // G4double outerRadius=xy*std::sqrt(2);
  // G4double col_Z=10.*cm;
  // G4double startAngle=0.*deg;
  // G4double spanningAngle=360.*deg;

  // G4VSolid* colS=new G4Tubs("Col",innerRadius,outerRadius,
  // 			     col_Z,startAngle,spanningAngle);
  // G4LogicalVolume* ColLV=new G4LogicalVolume(colS,col_mat,"Col");
  // new G4PVPlacement(0,G4ThreeVector(),ColLV,"Col",logicWorld,
  // 			      false,0,true);



  // target for photon-reaction

  //G4double SurDen=0.1*g/cm2;
  //G4double Rin = 0.*cm;
  //G4double Rout=0.8*cm;
  //G4double thickness=SurDen/EuDen;

  //G4cout<<"/n/n/nhhhhhhhhhh "<<G4BestUnit(thickness,"Length")<<G4endl;
  //G4Tubs* solidTar =
   // new G4Tubs("Target",Rin, Rout, thickness/2., 0.*deg, 360.*deg);
  G4double target_Z =0.05*mm;
  G4double target_XY = 15.*mm;
  G4double posTargetZ = 12.*cm + target_Z/2.;
  G4Box* solidTar= new G4Box("Target",0.5*target_XY, 0.5*target_XY, 0.5*target_Z);
  G4LogicalVolume* logicTar = new G4LogicalVolume(solidTar,Eu153,"Target");
                                    
  new G4PVPlacement(0,G4ThreeVector(0,0,posTargetZ),logicTar,"Target",logicWorld,false,0,true);


  return physWorld;
}

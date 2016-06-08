//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: GammaRayTelTrackerSD.cc,v 1.6 2001/12/04 11:40:28 flongo Exp $
// GEANT4 tag $Name: geant4-04-00 $
// ------------------------------------------------------------
//      GEANT 4 class implementation file
//      CERN Geneva Switzerland
//
//
//      ------------ GammaRayTelTrackerSD  ------
//           by  R.Giannitrapani, F.Longo & G.Santin (13 nov 2000)
//
// ************************************************************
#include "G4RunManager.hh"
#include "GammaRayTelTrackerSD.hh"

#include "GammaRayTelTrackerHit.hh"
#include "GammaRayTelDetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"

#include "G4Step.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GammaRayTelTrackerSD::GammaRayTelTrackerSD(G4String name):G4VSensitiveDetector(name)
{
 G4RunManager* runManager = G4RunManager::GetRunManager();
  Detector =
    (GammaRayTelDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
  G4int NbOfTKRTiles  =  Detector->GetNbOfTKRTiles();
  NbOfTKRStrips  = Detector->GetNbOfTKRStrips();
  NbOfTKRLayers  = Detector->GetNbOfTKRLayers();  
  NbOfTKRStrips = NbOfTKRStrips*NbOfTKRTiles;  
  
  NbOfTKRChannels = NbOfTKRStrips* NbOfTKRTiles * NbOfTKRLayers;
  
  ThitXID = new G4int[NbOfTKRChannels];
  ThitYID = new G4int[NbOfTKRChannels];
  collectionName.insert("TrackerCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

GammaRayTelTrackerSD::~GammaRayTelTrackerSD()
{
  delete [] ThitXID;
  delete [] ThitYID;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelTrackerSD::Initialize(G4HCofThisEvent*HCE)
{
  TrackerCollection = new GammaRayTelTrackerHitsCollection
    (SensitiveDetectorName,collectionName[0]);

 for (G4int i=0;i<NbOfTKRChannels;i++)
   {
     ThitXID[i] = -1;
     ThitYID[i] = -1;
   };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4bool GammaRayTelTrackerSD::ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist)
{ 

  G4double edep = aStep->GetTotalEnergyDeposit();
  if ((edep/keV == 0.)) return false;      
  
  G4int StripTotal = Detector->GetNbOfTKRStrips();
  G4int TileTotal  = Detector->GetNbOfTKRTiles();  
  
  // This TouchableHistory is used to obtain the physical volume
  // of the hit
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(aStep->GetPreStepPoint()->GetTouchable());
  
  G4VPhysicalVolume* phys_tile = theTouchable->GetVolume();  
  G4VPhysicalVolume* plane = phys_tile->GetMother();  
  
  G4int PlaneNumber = 0;
  PlaneNumber=plane->GetCopyNo();
  G4String PlaneName = plane->GetName();

  // The RO History is used to obtain the real strip
  // of the hit

  G4int StripNumber = 0;
  G4VPhysicalVolume* strip = 0;
  strip = ROhist->GetVolume();
  G4String StripName = strip->GetName();
  StripNumber= strip->GetCopyNo();  

  ROhist->MoveUpHistory();
  G4VPhysicalVolume* tile = ROhist->GetVolume(); 
  G4int TileNumber = tile->GetCopyNo();  
  G4String TileName = tile->GetName();   
  
  G4int NTile = (TileNumber%TileTotal);  
  G4int j=0;
  
  G4int NChannel = 0;
  
  for (j=0;j<TileTotal;j++)
    {
      if(NTile==j) StripNumber += StripTotal*NTile;
    }  
  
  NChannel = PlaneNumber*TileTotal*StripTotal + StripNumber;

  /*  G4cout << NChannel << " Channel Number" << G4endl;
      G4cout << " Plane Number = " << PlaneNumber << " " << PlaneName 
      << G4endl;
      G4cout << StripName << " " << StripNumber << G4endl;      */ 
  
  if (PlaneName == "TKRDetectorX" )
    // The hit is on an X silicon plane
    {
      // This is a new hit
      if (ThitXID[NChannel]==-1)
	{       
	  GammaRayTelTrackerHit* TrackerHit = new GammaRayTelTrackerHit;
	  TrackerHit->SetPlaneType(1);
	  TrackerHit->AddSil(edep);
	  TrackerHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  TrackerHit->SetNSilPlane(PlaneNumber);
	  TrackerHit->SetNStrip(StripNumber);
	  ThitXID[NChannel] = 
	    TrackerCollection->insert(TrackerHit) -1;
	}
      else // This is not new
	{
	  (*TrackerCollection)[ThitXID[NChannel]]->AddSil(edep);
          // G4cout << "X" << PlaneNumber << " " << StripNumber << G4endl;
	}
    }
  
  if (PlaneName == "TKRDetectorY")
    // The hit is on an Y silicon plane    
    {   
      // This is a new hit
      if (ThitYID[NChannel]==-1)
	{       
	  GammaRayTelTrackerHit* TrackerHit = new GammaRayTelTrackerHit;
	  TrackerHit->SetPlaneType(0);
	  TrackerHit->AddSil(edep);
	  TrackerHit->SetPos(aStep->GetPreStepPoint()->GetPosition());
	  TrackerHit->SetNSilPlane(PlaneNumber);
	  TrackerHit->SetNStrip(StripNumber);
	  ThitYID[NChannel] = 
	    TrackerCollection->insert(TrackerHit)-1;
	}
      else // This is not new
	{
	  (*TrackerCollection)[ThitYID[NChannel]]->AddSil(edep);
          // G4cout << "Y" << PlaneNumber << " " << StripNumber << G4endl;
	}
    }
  
  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelTrackerSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  static G4int HCID = -1;
  if(HCID<0)
    { 
      HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
    }
  HCE->AddHitsCollection(HCID,TrackerCollection);


  for (G4int i=0;i<NbOfTKRChannels;i++) 
    {
      ThitXID[i] = -1;
      ThitYID[i] = -1;
    };
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelTrackerSD::clear()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelTrackerSD::DrawAll()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void GammaRayTelTrackerSD::PrintAll()
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....














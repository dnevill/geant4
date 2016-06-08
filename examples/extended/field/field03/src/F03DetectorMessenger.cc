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
// $Id: F03DetectorMessenger.cc,v 1.3 2001/10/25 10:03:54 grichine Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "F03DetectorMessenger.hh"

#include "F03DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

F03DetectorMessenger::F03DetectorMessenger(F03DetectorConstruction * F03Det)
:F03Detector(F03Det)
{ 
  F03detDir = new G4UIdirectory("/calor/");
  F03detDir->SetGuidance("F03 detector control.");
      
  AbsMaterCmd = new G4UIcmdWithAString("/calor/setAbsMat",this);
  AbsMaterCmd->SetGuidance("Select Material of the Absorber.");
  AbsMaterCmd->SetParameterName("choice",true);
  AbsMaterCmd->SetDefaultValue("Lead");
  AbsMaterCmd->AvailableForStates(Idle);
  
  WorldMaterCmd = new G4UIcmdWithAString("/calor/setWorldMat",this);
  WorldMaterCmd->SetGuidance("Select Material of the World.");
  WorldMaterCmd->SetParameterName("wchoice",true);
  WorldMaterCmd->SetDefaultValue("Air");
  WorldMaterCmd->AvailableForStates(Idle);
  
  AbsThickCmd = new G4UIcmdWithADoubleAndUnit("/calor/setAbsThick",this);
  AbsThickCmd->SetGuidance("Set Thickness of the Absorber");
  AbsThickCmd->SetParameterName("SizeZ",false,false);
  AbsThickCmd->SetDefaultUnit("mm");
  AbsThickCmd->SetRange("SizeZ>0.");
  AbsThickCmd->AvailableForStates(Idle);
  
  AbsRadCmd = new G4UIcmdWithADoubleAndUnit("/calor/setAbsRad",this);
  AbsRadCmd->SetGuidance("Set radius of the Absorber");
  AbsRadCmd->SetParameterName("SizeR",false,false);
  AbsRadCmd->SetDefaultUnit("mm");
  AbsRadCmd->SetRange("SizeR>0.");
  AbsRadCmd->AvailableForStates(Idle);
  
  AbsZposCmd = new G4UIcmdWithADoubleAndUnit("/calor/setAbsZpos",this);
  AbsZposCmd->SetGuidance("Set Z pos. of the Absorber");
  AbsZposCmd->SetParameterName("Zpos",false,false);
  AbsZposCmd->SetDefaultUnit("mm");
  AbsZposCmd->AvailableForStates(Idle);
  
  WorldZCmd = new G4UIcmdWithADoubleAndUnit("/calor/setWorldZ",this);
  WorldZCmd->SetGuidance("Set Z size of the World");
  WorldZCmd->SetParameterName("WSizeZ",false,false);
  WorldZCmd->SetDefaultUnit("mm");
  WorldZCmd->SetRange("WSizeZ>0.");
  WorldZCmd->AvailableForStates(Idle);
  
  WorldRCmd = new G4UIcmdWithADoubleAndUnit("/calor/setWorldR",this);
  WorldRCmd->SetGuidance("Set R size of the World");
  WorldRCmd->SetParameterName("WSizeR",false,false);
  WorldRCmd->SetDefaultUnit("mm");
  WorldRCmd->SetRange("WSizeR>0.");
  WorldRCmd->AvailableForStates(Idle);
  
  UpdateCmd = new G4UIcmdWithoutParameter("/calor/update",this);
  UpdateCmd->SetGuidance("Update calorimeter geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

F03DetectorMessenger::~F03DetectorMessenger()
{
  delete AbsMaterCmd; 
  delete AbsThickCmd; 
  delete AbsRadCmd;  
  delete AbsZposCmd; 
  delete WorldMaterCmd;
  delete WorldZCmd;
  delete WorldRCmd;
  delete UpdateCmd;
  delete F03detDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void F03DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == AbsMaterCmd )
   { F03Detector->SetAbsorberMaterial(newValue);}
   
  if( command == WorldMaterCmd )
   { F03Detector->SetWorldMaterial(newValue);}
   
  if( command == AbsThickCmd )
   { F03Detector->SetAbsorberThickness(AbsThickCmd->GetNewDoubleValue(newValue));}
   
  if( command == AbsRadCmd )
   { F03Detector->SetAbsorberRadius(AbsRadCmd->GetNewDoubleValue(newValue));}
   
  if( command == AbsZposCmd )
   { F03Detector->SetAbsorberZpos(AbsZposCmd->GetNewDoubleValue(newValue));}
   
  if( command == WorldZCmd )
   { F03Detector->SetWorldSizeZ(WorldZCmd->GetNewDoubleValue(newValue));}
   
  if( command == WorldRCmd )
   { F03Detector->SetWorldSizeR(WorldRCmd->GetNewDoubleValue(newValue));}
   
  if( command == UpdateCmd )
   { F03Detector->UpdateGeometry(); }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

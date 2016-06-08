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
// $Id: Em1SteppingAction.cc,v 1.7 2001/10/26 12:51:26 maire Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "Em1SteppingAction.hh"
#include "Em1RunAction.hh"
#include "Em1EventAction.hh"
#include "G4SteppingManager.hh"
#include "G4VProcess.hh"

#ifndef G4NOHIST
 #include "CLHEP/Hist/HBookFile.h"
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Em1SteppingAction::Em1SteppingAction(Em1RunAction* RuAct, Em1EventAction* EvAct)
:runAction(RuAct),eventAction(EvAct)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

Em1SteppingAction::~Em1SteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void Em1SteppingAction::UserSteppingAction(const G4Step* aStep)
{ 
 G4double EdepStep = aStep->GetTotalEnergyDeposit();
 if (EdepStep > 0.) eventAction->addEdep(EdepStep);
 
 const G4VProcess* process = aStep->GetPostStepPoint()->GetProcessDefinedStep();
 if (process) runAction->CountProcesses(process->GetProcessName());
 
 G4double charge  = aStep->GetTrack()->GetDefinition()->GetPDGCharge();
 G4double steplen = aStep->GetStepLength();
 
#ifndef G4NOHIST 
 if (charge != 0.) runAction->GetHisto(2)->accumulate(steplen);
#endif                    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



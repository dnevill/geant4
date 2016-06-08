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
// $Id: PersEx02TrackerSD.hh,v 1.4 2001/07/11 09:58:15 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $
//

#ifndef PersEx02TrackerSD_h
#define PersEx02TrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "PersEx02TrackerHitsCollection.hh"
#include "G4Step.hh"
#include "HepODBMS/odbms/HepODBMS.h"

class G4PersistentHitMan;

class PersEx02TrackerSD : public G4VSensitiveDetector
{

  public:
      PersEx02TrackerSD(G4String name);
      ~PersEx02TrackerSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
      void EndOfEvent(G4HCofThisEvent*HCE);
      void clear();
      void DrawAll();
      void PrintAll();

  private:
      G4PersistentHitMan* f_hitMan;
      HepRef(PersEx02TrackerHitsCollection) EvenCollection;
      HepRef(PersEx02TrackerHitsCollection)  OddCollection;
      HepContainerRef hitContainer;
};

#endif


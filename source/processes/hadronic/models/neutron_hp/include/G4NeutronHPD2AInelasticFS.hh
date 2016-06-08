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
// * authors in the GEANT4 collaboration.                             *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4NeutronHPD2AInelasticFS.hh,v 1.5 2001/07/26 09:27:55 hpw Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
#ifndef G4NeutronHPD2AInelasticFS_h
#define G4NeutronHPD2AInelasticFS_h 1

#include "globals.hh"
#include "G4Track.hh"
#include "G4ParticleChange.hh"
#include "G4NeutronHPInelasticBaseFS.hh"

class G4NeutronHPD2AInelasticFS : public G4NeutronHPInelasticBaseFS
{
  public:
  
  G4NeutronHPD2AInelasticFS(){}
  ~G4NeutronHPD2AInelasticFS(){}
  void Init (G4double A, G4double Z, G4String & dirName, G4String & aFSType);
  G4ParticleChange * ApplyYourself(const G4Track & theTrack);
  G4NeutronHPFinalState * New() 
  {
   G4NeutronHPD2AInelasticFS * theNew = new G4NeutronHPD2AInelasticFS;
   return theNew;
  }
  
  private:
};
#endif

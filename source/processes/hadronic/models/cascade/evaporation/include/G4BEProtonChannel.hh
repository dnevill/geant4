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
// Implementation of the HETC88 code into Geant4.
// Evaporation and De-excitation parts
// T. Lampen, Helsinki Institute of Physics, 30-May-2000

#ifndef G4BEProtonChannel_h
#define G4BEProtonChannel_h 1

#include "G4BEChargedChannel.hh"

class G4BEProtonChannel : public G4BEChargedChannel
{
public:
  G4BEProtonChannel();
  virtual ~G4BEProtonChannel(); 

  G4DynamicParticle * emit();
  G4double constant();
  virtual G4double coulombFactor();
  virtual G4double qmFactor( );
  
private:  
};


#endif

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
// $Id: G4PPVPlacement.ddl,v 1.6 2001/07/11 10:02:18 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $

// Class Description:
//   Persistent version of G4PVPlacement.

#ifndef G4PPVPLACEMENT_DDL
#define G4PPVPLACEMENT_DDL 1

#include "G4PersistentTypes.hh"
#include "G4PersistentSchema.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4PLogicalVolume;

#include "G4PVPhysicalVolume.hh"

class G4PPVPlacement : public G4PVPhysicalVolume
{
public: // With description
  G4PPVPlacement( G4VPhysicalVolume *PhysVol,
		          HepRef(G4PLogicalVolume) persLogVol);
  ~G4PPVPlacement();
    // Constructor and Destructor

  G4VPhysicalVolume* MakeTransientObject(
                             G4LogicalVolume* aLogical,
                             G4VPhysicalVolume* aMother );
    // Make a transient G4PVPlacement object.

  virtual G4bool IsMany() const;
  virtual G4int GetCopyNo() const;
    // Returns the multiplicity of the volume.

protected:
  virtual void  SetCopyNo(G4int CopyNo);

private:
  G4bool fmany;	    // flag for booleans
//  G4bool fallocatedRotM;  // flag for allocation of Rotation Matrix
  G4Pint fcopyNo;	    // for identification
};

#endif

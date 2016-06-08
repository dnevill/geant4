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
// $Id: G4PPVReplica.ddl,v 1.7 2001/07/11 10:02:19 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $

// Class Description:
//  Persistent-capable class of G4PVReplica

// History:
// 05.11.99  Y.Morita  First non-stub version

#ifndef G4PPVREPLICA_DDL
#define G4PPVREPLICA_DDL

#include "G4Pglobals.hh"

#include "G4PersistentTypes.hh"
#include "G4PersistentSchema.hh"
#include "G4VPhysicalVolume.hh"
// #include "G4RotationMatrix.hh"

#include "G4PVPhysicalVolume.hh"

class G4PPVReplica
 : public G4PVPhysicalVolume
{
public: // With description
  G4PPVReplica( G4VPhysicalVolume *PhysVol,
                HepRef(G4PLogicalVolume) persLogVol);
  ~G4PPVReplica();
    // Constructor and Destructor

  G4VPhysicalVolume* MakeTransientObject(
                             G4LogicalVolume* aLogical,
                             G4VPhysicalVolume* aMother );
    // Creates a transient G4PVReplica object.

  virtual G4bool IsMany() const;
  virtual G4int GetCopyNo() const;
    // Returns the multiplicity of the volume.

protected:
  virtual void  SetCopyNo(G4int CopyNo);

protected:
  EAxis faxis;
  G4Pint fnReplicas;
  G4Pdouble fwidth,foffset;
    
  G4Pint    fcopyNo;
};

#endif




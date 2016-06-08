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
// $Id: G4PCSGSolid.ddl,v 1.5 2001/07/11 10:02:23 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $

// Class Description:
//   Persistent version of G4CSGSolid

// History:
// 19.06.98 A.Kimura Converted G4CSGSolid.hh

#ifndef G4PCSGSOLID_DDL
#define G4PCSGSOLID_DDL

#include "G4PersistentSchema.hh"
#include "G4PVSolid.hh"

class G4PCSGSolid
 : public G4PVSolid
{
public: // With description
    G4PCSGSolid(const G4String& pName);
    virtual ~G4PCSGSolid();
    // Constructor and Destructor
};

#endif

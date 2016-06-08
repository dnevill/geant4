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
// $Id: G4PlacedSolid.cc,v 1.4 2001/07/11 09:59:46 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
// ----------------------------------------------------------------------
// GEANT 4 class source file
//
// G4PlacedSolid.cc
//
// ----------------------------------------------------------------------

#include "G4PlacedSolid.hh"

G4PlacedSolid::G4PlacedSolid()
{
  solid =0;
  solidRotation =0;
  solidTranslation =0;
}


G4PlacedSolid::G4PlacedSolid(G4BREPSolid* s, G4Axis2Placement3D* p)
{
  solid =s;

  if(p)
  {
    G4double x,y,z;
    G4Point3D srfpoint = p->GetLocation();
    
    x = srfpoint.x();
    y = srfpoint.y();
    z = srfpoint.z();
    solidTranslation = new G4ThreeVector(x,y,z);
    
    G4Vector3D tmpvec = p->GetAxis();
    x = tmpvec.x();
    y = tmpvec.y();
    z = tmpvec.z();
    G4ThreeVector x_axis(x,y,z);

    if( (x<kCarTolerance)&&
	(y<kCarTolerance)&&
	(z<kCarTolerance)   )
      solidRotation=0;
    else
    {
      tmpvec = p->GetRefDirection();
      x = tmpvec.x();
      y = tmpvec.y();
      z = tmpvec.z();

      G4ThreeVector y_axis(x,y,z);
      solidRotation = new G4RotationMatrix();
      solidRotation->rotateAxes(x_axis, y_axis, x_axis.cross(y_axis));
    }
  }
  else
  {
    solidTranslation=0;
    solidRotation=0;
  }
}


G4PlacedSolid::~G4PlacedSolid()
{
  //delete solid;
  if(solidRotation)
    delete solidRotation;
  
  if(solidTranslation)
    delete solidTranslation;
}

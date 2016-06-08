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
// $Id: G4DynamicParticleFastVector.hh,v 1.3 2001/07/11 10:01:55 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
// 
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
//	History: first implementation, based on object model of
//	2nd December 1995, G.Cosmo
// ------------------------------------------------------------

#ifndef G4DynamicParticleFastVector_h
#define G4DynamicParticleFastVector_h 1

#include "globals.hh"
#include "G4ios.hh"

class G4DynamicParticle;
#include "G4FastVector.hh"


typedef G4FastVector<G4DynamicParticle,512> G4DynamicParticleFastVector;
//  Contains pointers to G4DynamicParticle objects which are
//  generated by either primary or secondary interaction.

#endif


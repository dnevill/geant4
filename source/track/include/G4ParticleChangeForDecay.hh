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
// $Id: G4ParticleChangeForDecay.hh,v 1.5 2001/07/11 10:08:35 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
// 
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
// 
// ------------------------------------------------------------
//   Implemented for the new scheme                 23 Mar. 1998  H.Kurahige
//
// Class Description 
//  This class is a concrete class for ParticleChange which
//  has functionality for G4Decay.
//
//  This class contains the results after invocation of the decay process.
//  This includes secondary particles generated by the interaction.
// ------------------------------------------------------------
#ifndef G4ParticleChangeForDecay_h
#define G4ParticleChangeForDecay_h 1

#include "globals.hh"
#include "G4ios.hh"
#include "G4ThreeVector.hh"
class G4DynamicParticle;
#include "G4VParticleChange.hh"

class G4ParticleChangeForDecay: public G4VParticleChange
{
   public:
    // default constructor
    G4ParticleChangeForDecay();

    // destructor
    virtual ~G4ParticleChangeForDecay();

  protected:
    // hide copy constructor and assignment operaor as protected
    G4ParticleChangeForDecay(const G4ParticleChangeForDecay &right);
    G4ParticleChangeForDecay & operator=(const G4ParticleChangeForDecay &right);

  public:
    // equal/unequal operator
    G4bool operator==(const G4ParticleChangeForDecay &right) const;
    G4bool operator!=(const G4ParticleChangeForDecay &right) const;

  public: // with description
    // ----------------------------------------------------
    // --- the following methods are for updating G4Step -----   
    // Return the pointer to the G4Step after updating the Step information
    // by using final state information of the track given by a physics
    // process    
 
    // !!! No effect for  AlongSteyp
    // virtual G4Step* UpdateStepForAlongStep(G4Step* Step);

    virtual G4Step* UpdateStepForAtRest(G4Step* Step);
    virtual G4Step* UpdateStepForPostStep(G4Step* Step);
 
    virtual void Initialize(const G4Track&);
    // Initialize all propoerties by using G4Track information

    G4double GetTimeChange() const;
    void     SetTimeChange(G4double t);
    //  Get/Set theTimeChange vector.

  public:
    virtual void DumpInfo() const;

  protected:
    G4double theTimeChange;
    //  The change of global time of a given particle.
 
 public:
    // for Debug 
    virtual G4bool CheckIt(const G4Track&);
};

inline 
  G4double G4ParticleChangeForDecay::GetTimeChange() const
{
  return  theTimeChange;
}

inline 
  void G4ParticleChangeForDecay::SetTimeChange(G4double t)
{
  theTimeChange = t;
}


#endif

















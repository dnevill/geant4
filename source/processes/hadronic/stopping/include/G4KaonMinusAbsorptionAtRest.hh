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
// $Id: G4KaonMinusAbsorptionAtRest.hh,v 1.7 2001/10/04 20:00:40 hpw Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
// -------------------------------------------------------------------
//      GEANT 4 class file --- Copyright CERN 1997
//      CERN Geneva Switzerland
//
//
//      File name:     G4KaonMinusAbsorptionAtRest.hh 
//
//      Author:        Christian V"olcker (Christian.Volcker@cern.ch),
// 
//      Creation date: 10. November 1997
//
//      Modifications: 
// -------------------------------------------------------------------

#ifndef G4KaonMinusAbsorptionAtRest_h
#define G4KaonMinusAbsorptionAtRest_h 1
// Class Description
// Process for nuclear absorption of K- at rest; 
// to be used in your physics list in case you need this physics.
// Class Description - End

#include "globals.hh"
#include "Randomize.hh"
#include "G4VRestProcess.hh"
#include "G4ParticleTypes.hh"
#include "G4Nucleus.hh"
#include "G4DynamicParticle.hh"
#include "G4DynamicParticleVector.hh"
#include "G4NucleiPropertiesTable.hh"
//#include "G4String.hh"


// *********************************************************
class G4KaonMinusAbsorptionAtRest : public G4VRestProcess
// *********************************************************
{  
private:
  // hide assignment operator as private 
      G4KaonMinusAbsorptionAtRest& operator=(const G4KaonMinusAbsorptionAtRest &right);
      G4KaonMinusAbsorptionAtRest(const G4KaonMinusAbsorptionAtRest& );
public:
      G4KaonMinusAbsorptionAtRest(const G4String& processName ="KaonMinusAbsorptionAtRest");
     ~G4KaonMinusAbsorptionAtRest();

  //override methods...
public: 
  G4bool IsApplicable(const G4ParticleDefinition& particle) {
               return( particle == *(G4KaonMinus::KaonMinus()) );
  }

  // the main method ...
     G4VParticleChange* AtRestDoIt(const G4Track& aTrack, const G4Step& aStep); 

protected:                         // why?? might be private....
  // zero mean lifetime
     G4double GetMeanLifeTime(const G4Track& aTrack,
			      G4ForceCondition* condition) 
     {
     G4double result = 0;
     if(aTrack.GetMaterial()->GetNumberOfElements() == 1)
        if(aTrack.GetMaterial()->GetZ()<1.5) result = DBL_MAX;
     return result;
     }

private:
  // returns proton or neutron with fermi-momentum 
     G4DynamicParticle GetAbsorbingNucleon();

  // returns proton or neutron particle definition; 
     G4ParticleDefinition* SelectAbsorbingNucleon();
    
  // provides the neutron halo factor for absorption on nucleus surface. 
  // in the G4Nucleus
     G4double NeutronHaloFactor(G4double Z, G4double N);

  //  creates the reaction products
     G4DynamicParticleVector* KaonNucleonReaction();

  // secondary pion absorption in parent nucleus
  // if TRUE, then add excitation energy to the Nucleus
     G4bool AbsorbPionByNucleus(G4DynamicParticle* aPion);
     
  //  secondary Sigma-Lambda conversion
  // if conversion Done, then add excitation energy to the Nucleus
     G4DynamicParticle *SigmaLambdaConversion(G4DynamicParticle* aSigma);

  // instance variables ...
private:
  // pointer to current stopped hadron
     const G4DynamicParticle *stoppedHadron;

  // pointer to current target nucleus
     G4Nucleus* nucleus;

  // some constant parameters

     G4double pionAbsorptionRate;
     
  // primary production rates ( for absorption on Carbon)

     G4double rateLambdaZeroPiZero;
     G4double rateSigmaMinusPiPlus;
     G4double rateSigmaPlusPiMinus;
     G4double rateSigmaZeroPiZero;

     G4double rateLambdaZeroPiMinus;
     G4double rateSigmaZeroPiMinus;
     G4double rateSigmaMinusPiZero;


  // Sigma Lambda Conversion rates
  // for sigma- p -> lambda n
  //     sigma+ n -> lambda p
  //     sigma- n -> lambda 
  
     G4double sigmaPlusLambdaConversionRate; 
     G4double sigmaMinusLambdaConversionRate;
     G4double sigmaZeroLambdaConversionRate;
     
};

#endif


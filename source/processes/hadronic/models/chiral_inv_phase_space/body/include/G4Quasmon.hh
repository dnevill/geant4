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
// $Id: G4Quasmon.hh,v 1.19 2001/11/26 14:11:45 hpw Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
//      ---------------- G4Quasmon ----------------
//             by Mikhail Kossov, July 1999.
//      class for a Quasmon used by the CHIPS Model
// ------------------------------------------------------------

#ifndef G4Quasmon_h
#define G4Quasmon_h 1

// Standard G4-headers
#include "G4ios.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"
#include "G4LorentzRotation.hh"
//CHIPS-headers
#include "G4QCHIPSWorld.hh"
#include "G4QChipolino.hh"
#include "G4QHadronVector.hh"
#include "G4QNucleus.hh"

class G4Quasmon 
{
public:
  G4Quasmon(G4QContent qQCont    = G4QContent(0,0,0,0,0,0),
            G4LorentzVector q4M  = G4LorentzVector(0.,0.,0.,0.),
            G4LorentzVector ph4M = G4LorentzVector(0.,0.,0.,0.));// Direct Constructor
  G4Quasmon(const G4Quasmon& right);                             // Copy Quasmon by object
  G4Quasmon(G4Quasmon* right);                                   // Copy Quasmon by pointer

  ~G4Quasmon();

  // Overloaded Operators
  const G4Quasmon& operator=(const G4Quasmon& right);
  int operator==(const G4Quasmon &right) const;
  int operator!=(const G4Quasmon &right) const;

  // Static functions
  static void SetParameters(G4double temperature, G4double ssin2g, G4double etaetap);
  static void SetTemper(G4double temperature);
  static void SetSOverU(G4double ssin2g);
  static void SetEtaSup(G4double etaetap);

  //Selectors
  G4double          GetTemper()    const;
  G4double          GetSOverU()    const;
  G4double          GetEtaSup()    const;
  G4LorentzVector   Get4Momentum() const;
  G4QContent        GetQC()        const;
  G4QPDGCode        GetQPDG()      const;
  G4int             GetStatus()    const;

  //Modifiers
  G4QHadronVector*  Fragment(G4QNucleus& nucEnviron, G4int nQ); // Pub-wrapper for "HadronizeQuasmon(,)"
  void              ClearOutput();                    // Clear but not destroy the output
  void              InitQuasmon(const G4QContent& qQCont, const G4LorentzVector& q4M);
  void              IncreaseBy(const G4Quasmon* pQuasm); // as operator+= but by pointer
  void              KillQuasmon();                    // Kill Quasmon (status=0)

private:  
  G4QHadronVector  HadronizeQuasmon(G4QNucleus& qEnv, G4int nQ); // Return new neuclear environment
  G4double         GetRandomMass(G4int PDGCode, G4double maxM);
  void             ModifyInMatterCandidates();
  void             InitCandidateVector(G4int maxMes, G4int maxBar, G4int maxClust);
  void             CalculateNumberOfQPartons(G4double qMass);
  void             CalculateHadronizationProbabilities(G4double excE, G4double kQ, G4double kLS,
                                                       G4bool piF, G4bool gaF);
  void             FillHadronVector(G4QHadron* qHadron);
  G4int            RandomPoisson(G4double meanValue);
  G4double         GetQPartonMomentum(G4double mMinResidual2, G4double mCandidate2);
  G4bool           DecayOutHadron(G4QHadron* qHadron, G4int DFlag=0);
  G4bool           CheckGroundState(G4bool corFlag = false); // Forbid correction by default
  void             KillEnvironment(); // Kill Environment (Z,N,S=0,LV=0)

// Body
private:
  // Static Parameters
  static G4double    Temperature;     // Quasmon Temperature
  static G4double    SSin2Gluons;     // Percent of ssbar sea in a constituen gluon
  static G4double    EtaEtaprime;     // Part of eta-prime in all etas
  // Hadronic input
  G4LorentzVector    q4Mom;           // 4-momentum of the Quasmon +++++
  G4QContent         valQ;            // Quark Content of the Quasmon  +++++
  G4QNucleus         theEnvironment;  // Nuclear (or Vacuum) Environment around the Quasmon
  // Output
  G4int status; // -1-Panic,0-Done,1-FilledSomething,2-DidNothing,3-StopedByCB,4-JustBorn
  G4QHadronVector    theQHadrons;     // Vector of generated secondary hadrons +++++
  // Internal working objects (@@ it is possible to sacrifice some of them in future)
  G4QCHIPSWorld      theWorld;        // Pointer to the CHIPS World
  G4LorentzVector    phot4M;          // Gamma 4-momentum for interaction with a quark-parton
  G4int              nBarClust;       // Maximum barion number of clusters in the Environment @@ ??
  G4int              nOfQ;            // number of quark-partons in the Quasmon (just to accelerate)
  G4QCandidateVector theQCandidates;  // Vector of possible secondary hadrons/clusters (**delete!**)
  G4double           f2all;           // Ratio of free nucleons to free+freeInDense nucleons @@ ??
  G4double           rEP;             // E+p for the Residual Coloured Quasmon im LS +++++
  G4double           rMo;             // p for the Residual Coloured Quasmon im LS +++++
  G4double           totMass;         // Mass of total compound system curQuasmon+curEnvironment
  G4int              bEn;             // BaryoNumber of the Limit Active Nuclear Environment
  G4double           mbEn;            // Mass of the LimActNucEnv
  G4LorentzVector    bEn4M;           // 4-momentum of the LimitActiveNuclearEnviron
  G4QContent         bEnQC;           // QuarkContent of the LimitActiveNuclEnv
};

inline int G4Quasmon::operator==(const G4Quasmon &right) const {return this == &right;}
inline int G4Quasmon::operator!=(const G4Quasmon &right) const {return this != &right;}
inline G4double        G4Quasmon::GetTemper()    const {return Temperature;}
inline G4double        G4Quasmon::GetSOverU()    const {return SSin2Gluons;}
inline G4double        G4Quasmon::GetEtaSup()    const {return EtaEtaprime;}
inline G4LorentzVector G4Quasmon::Get4Momentum() const {return q4Mom;}
inline G4QContent      G4Quasmon::GetQC()        const {return valQ;}
inline G4QPDGCode      G4Quasmon::GetQPDG()      const {return G4QPDGCode(valQ);}
inline G4int           G4Quasmon::GetStatus()    const {return status;}
inline void            G4Quasmon::ClearOutput()        
      {G4std::for_each(theQHadrons.begin(), theQHadrons.end(), DeleteQHadron());
       theQHadrons.clear();
      }
inline void            G4Quasmon::KillEnvironment()
                                    {theEnvironment=G4QNucleus(0,0,0,G4LorentzVector(0.,0.,0.,0.));}
inline G4double        G4Quasmon::GetRandomMass(G4int PDG, G4double maxM)
{
  G4QParticle* part = theWorld.GetQParticle(PDG);
  return G4QHadron(part, maxM).GetMass();
}

inline void G4Quasmon::IncreaseBy(const G4Quasmon* pQuasm)
{
  valQ  += pQuasm->GetQC();
  q4Mom += pQuasm->Get4Momentum();
  status= 3;
}

inline void G4Quasmon::InitQuasmon(const G4QContent& qQCont, const G4LorentzVector& q4M)
{
  valQ  = qQCont;
  q4Mom = q4M;
  status= 3;
}

inline void G4Quasmon::KillQuasmon()
{
  static const G4QContent zeroQC(0,0,0,0,0,0);
  static const G4LorentzVector nothing(0.,0.,0.,0.);
  phot4M= nothing;
  valQ  = zeroQC;
  q4Mom = nothing;
  status= 0;
}

#endif






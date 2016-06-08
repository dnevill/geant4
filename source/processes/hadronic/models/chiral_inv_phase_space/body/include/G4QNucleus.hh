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
// $Id: G4QNucleus.hh,v 1.12 2001/11/26 14:11:45 hpw Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
//      ---------------- G4QNucleus ----------------
//             by Mikhail Kossov, Sept 1999.
//  class header for Quasmon initiated Candidates used by the CHIPS Model
// ----------------------------------------------------------------------

#ifndef G4QNucleus_h
#define G4QNucleus_h 1

#include "G4QCandidateVector.hh"

class G4QNucleus : public G4QHadron
{
public:
  G4QNucleus();                                            // Default Constructor
  G4QNucleus(G4int nucPDG);                                // At Rest PDG-Constructor
  G4QNucleus(G4LorentzVector p, G4int nucPDG);             // Full PDG-Constructor
  G4QNucleus(G4QContent nucQC);                            // At Rest QuarkCont-Constructor
  G4QNucleus(G4QContent nucQC, G4LorentzVector p);         // Full QuarkCont-Constructor
  G4QNucleus(G4int z, G4int n, G4int s);                   // At Rest ZNS-Constructor
  G4QNucleus(G4int z, G4int n, G4int s, G4LorentzVector p);// Full ZNS-Constructor
  G4QNucleus(const G4QNucleus& right);                     // Copy Constructor by value
  G4QNucleus(G4QNucleus* right);                           // Copy Constructor by pointer
  ~G4QNucleus();                                           // Destructor
  // Overloaded Operators
  const G4QNucleus & operator=(const G4QNucleus &right);
  G4int operator==(const G4QNucleus &right) const;
  G4int operator!=(const G4QNucleus &right) const;
  // Specific Selectors
  G4int      GetPDG()      const;                          // Get a PDG Code of the nucleus
  G4int      GetZ()        const;                          // Get a#of protons
  G4int      GetN()        const;                          // Get a#of neutrons
  G4int      GetS()        const;                          // Get a#of lambdas
  G4int      GetA()        const;                          // Get A of the nucleus
  G4int      GetDZ()       const;                          // Get a#of protons in dense region
  G4int      GetDN()       const;                          // Get a#of neutrons in dense region
  G4int      GetDS()       const;                          // Get a#of lambdas in dense region
  G4int      GetDA()       const;                          // Get A of the dense part of nucleus
  G4int      GetMaxClust() const;                          // Get Max BarNum of Clusters
  G4double   GetProbability(G4int bn=0) const;             // probab. for the cluster with BarN
  G4double   GetMZNS()     const;                          // Get GS mass of Nucleus(not H || Q)
  G4double   GetGSMass()   const;                          // Get GS mass of Nucleus(not Hadron)
  G4QContent GetQCZNS()    const;                          // Get ZNS quark content of Nucleus

  // Specific Modifiers
  G4bool     EvaporateBaryon(G4QHadron* h1,G4QHadron* h2); // Evaporate one Baryon from Nucleus
  G4bool     SplitBaryon();                                // Is it possible to split a baryon/alpha
  G4bool     Split2Baryons();                              // Is it possible to split two baryons?
  void       InitByPDG(G4int newPDG);                      // Init existing nucleus by new PDG
  void       InitByQC(G4QContent newQC);                   // Init existing nucleus by new QCont
  void       IncProbability(G4int bn);                     // Add one cluster to probability
  void       Increase(G4int PDG, G4LorentzVector LV = G4LorentzVector(0.,0.,0.,0.));
  void       Increase(G4QContent QC, G4LorentzVector LV = G4LorentzVector(0.,0.,0.,0.));
  void       Reduce(G4int PDG);                            // Reduce Nucleus by PDG fragment
  void       CalculateMass();                              // Recalculate (calculate) the mass
  void       SetMaxClust(G4int maxC);                      // Set Max BarNum of Clusters
  void       PrepareCandidates(G4QCandidateVector& theQCandidates, G4bool piF, G4bool gaF);
  G4int      UpdateClusters(G4bool din);                   // Return a#of clusters & calc. probab's
  G4QNucleus operator+=(const G4QNucleus& rhs);            // Add a cluster to the  nucleus
  G4QNucleus operator-=(const G4QNucleus& rhs);            // Subtract a cluster from a nucleus
  G4QNucleus operator*=(const G4int& rhs);                 // Multiplication of the Nucleus
  // Static functions
  static void SetParameters(G4double fN, G4double fD, G4double cP, G4double mR=1.);
  // Specific General Functions
  G4int RandomizeBinom(G4double p,G4int N);                // Randomize according to Binomial Law
  G4double CoulombBarrier(const G4double& cZ, const G4double& cA, G4double dZ=0., G4double dA=0.);
  G4double BindingEnergy(const G4double& cZ, const G4double& cA, G4double dZ=0., G4double dA=0.);
  G4double CoulBarPenProb(const G4double& CB, const G4double& E, const G4int& C, const G4int& B);

private:  
  // Specific Encapsulated Functions
  void       SetZNSQC(G4int z, G4int n, G4int s);          // Set QC, using Z,N,S
  G4QNucleus GetThis() const;                              // @@ Check for memory leak

// Body
private:
  // Static Parameters
  static G4double freeNuc;      // probability of the quasi-free baryon on surface
  static G4double freeDib;      // probability of the quasi-free dibaryon on surface
  static G4double clustProb;    // clusterization probability in dense region
  static G4double mediRatio;    // relative vacuum hadronization probability
  // The basic  
  G4int Z;                      // Z of the Nucleus
  G4int N;                      // N of the Nucleus
  G4int S;                      // S of the Nucleus
  // The secondaries
  G4int dZ;                     // Z of the dense region of the nucleus
  G4int dN;                     // N of the dense region of the nucleus
  G4int dS;                     // S of the dense region of the nucleus
  G4int maxClust;               // Baryon Number of the last calculated cluster
  G4double probVect[256];       // Cluster probability ("a#of issues" can be real) Vector
};

G4std::ostream& operator<<(G4std::ostream& lhs, G4QNucleus& rhs);
G4std::ostream& operator<<(G4std::ostream& lhs, const G4QNucleus& rhs);

inline G4int G4QNucleus::operator==(const G4QNucleus &right) const  {return this==&right;}
inline G4int G4QNucleus::operator!=(const G4QNucleus &right) const  {return this!=&right;}

inline G4int    G4QNucleus::GetPDG()const {return 90000000+1000*(1000*S+Z)+N;}
inline G4int    G4QNucleus::GetZ()  const {return Z;}
inline G4int    G4QNucleus::GetN()  const {return N;}
inline G4int    G4QNucleus::GetS()  const {return S;}
inline G4int    G4QNucleus::GetA()  const {return Z+N+S;}
inline G4int    G4QNucleus::GetDZ() const {return dZ;}
inline G4int    G4QNucleus::GetDN() const {return dN;}
inline G4int    G4QNucleus::GetDS() const {return dS;}
inline G4int    G4QNucleus::GetDA() const {return dZ+dN+dS;}
inline G4int    G4QNucleus::GetMaxClust() const {return maxClust;}
inline G4double G4QNucleus::GetProbability(G4int bn) const {return probVect[bn];}

// Init existing nucleus by new Quark Content
inline void G4QNucleus::InitByQC(G4QContent newQC)
{//  =============================================
  G4int PDG=G4QPDGCode(newQC).GetPDGCode();
  InitByPDG(PDG);
}

inline G4double   G4QNucleus::GetMZNS()   const {return GetQPDG().GetNuclMass(Z,N,S);}
inline G4double   G4QNucleus::GetGSMass() const {return GetQPDG().GetMass();}
inline G4QContent G4QNucleus::GetQCZNS()  const
{
  if(S>=0) return G4QContent(Z+N+N+S,Z+Z+N+S,S,0,0,0);
  else     return G4QContent(Z+N+N+S,Z+Z+N+S,0,0,0,-S);
}
inline void       G4QNucleus::SetMaxClust(G4int maxC) {maxClust=maxC;}
inline void       G4QNucleus::CalculateMass()
                    {Set4Momentum(G4LorentzVector(0.,0.,0.,GetGSMass()));}
// Add Cluster
inline G4QNucleus G4QNucleus::operator+=(const G4QNucleus& rhs)
//     =======================================================
{
  Z+=rhs.Z;
  N+=rhs.N;
  S+=rhs.S;
  // Atributes of aHadron
  G4int           newPDG= GetPDGCode()   + rhs.GetPDGCode() - 90000000;
  SetQPDG        (newPDG);
  G4QContent      newQC = GetQC()        + rhs.GetQC();
  SetQC          (newQC);
  G4LorentzVector newLV = Get4Momentum() + rhs.Get4Momentum();
  Set4Momentum   (newLV);
  return *this;
} 

// Subtract Cluster
inline G4QNucleus G4QNucleus::operator-=(const G4QNucleus& rhs)
//     =======================================================
{
  Z-=rhs.Z;
  N-=rhs.N;
  S-=rhs.S;
  // Atributes of aHadron
  G4int           newPDG= GetPDGCode()   - rhs.GetPDGCode() + 90000000;
  SetQPDG        (newPDG);
  G4QContent      newQC = GetQC()        - rhs.GetQC();
  SetQC          (newQC);
  G4LorentzVector newLV = Get4Momentum() - rhs.Get4Momentum();
  Set4Momentum   (newLV);
  return *this;
} 

// Multiply Nucleus by integer value
inline G4QNucleus G4QNucleus::operator*=(const G4int& rhs)
//     ===================================================
{
  Z*=rhs;
  N*=rhs;
  S*=rhs;
  // Atributes of aHadron
  G4int           newPDG= rhs*(GetPDGCode() - 90000000) + 90000000;
  SetQPDG        (newPDG);
  G4QContent      newQC = rhs*GetQC();
  SetQC          (newQC);
  G4LorentzVector newLV = rhs*Get4Momentum();
  Set4Momentum   (newLV);
  return *this;
} 

// Private member functions
inline G4QNucleus G4QNucleus::GetThis()const{return G4QNucleus(Z,N,S);}

#endif





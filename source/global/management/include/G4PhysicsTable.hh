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
// $Id: G4PhysicsTable.hh,v 1.11 2001/07/11 10:00:50 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
// 
// ------------------------------------------------------------
//      GEANT 4 class header file
//
// Class description:
//
// G4PhysicsTable is an utility class for storage of pointers
// to G4PhysicsVector containers. It derives all functionalities
// of STL vector containers with the addition of few methods for
// compatibility with previous implementation based on Rogue-Wave
// pointer collections.
// The constructor given the 'capacity' of the table, pre-allocates
// memory for the specified value by invoking the STL's reserve()
// function, in order to avoid reallocation during insertions.
// ------------------------------------------------------------
//
// History:
// -------
// - First implementation, based on object model of
//   2nd December 1995. G.Cosmo
// - 1st March 1996, modified. K.Amako
// - 24th February 2001, migration to STL vectors. H.Kurashige
// - 9th March 2001, added Store/RetrievePhysicsTable. H.Kurashige
//-------------------------------------

#ifndef G4PhysicsTable_h
#define G4PhysicsTable_h 1

#include "g4std/vector"
#include "globals.hh"
#include "G4ios.hh"

class G4PhysicsVector;

class G4PhysicsTable : public G4std::vector<G4PhysicsVector*> 
{

  typedef G4std::vector<G4PhysicsVector*> G4PhysCollection;

 public: // with description

  G4PhysicsTable();
    // Default constructor.

  G4PhysicsTable(size_t capacity);
    // Constructor with capacity. Reserves memory for the
    // specified capacity.

  virtual ~G4PhysicsTable();
    // Destructor.
    // Does not invoke deletion of contained pointed collections.

  G4PhysicsVector*& operator()(size_t);
  G4PhysicsVector* const& operator()(size_t) const;
    // Access operators.

  void clearAndDestroy();
    // Removes all items and deletes them at the same time.

  void   insert (G4PhysicsVector*);
    // Pushes new element to collection.

  void   insertAt (size_t, G4PhysicsVector*); 
    // Inserts element at the specified position in the collection.

  size_t entries() const;
  size_t length() const;
    // Return collection's size.

  G4bool isEmpty() const;
    // Flags if collection is empty or not.

  G4bool StorePhysicsTable(const G4String& filename, G4bool ascii=false);
    // Stores PhysicsTable in a file (returns false in case of failure).
  
  G4bool RetrievePhysicsTable(const G4String& filename, G4bool ascii=false);
    // Retrieves Physics from a file (returns false in case of failure).

  friend G4std::ostream& operator<<(G4std::ostream& out, G4PhysicsTable& table);

 protected:

  G4PhysicsVector* CreatePhysicsVector(G4int type);  

 private:

  G4PhysicsTable(const G4PhysicsTable&);
  G4PhysicsTable& operator=(const G4PhysicsTable&);
    // Private copy constructor and assignment operator.

};

typedef G4PhysicsTable::iterator G4PhysicsTableIterator;

#include "G4PhysicsVector.hh"
#include "G4PhysicsTable.icc"

#endif

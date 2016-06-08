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
// $Id: G4TrackStack.cc,v 1.4 2001/07/13 15:01:55 gcosmo Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
//
//  Last Modification : 09/Dec/96 M.Asai
//

#include "G4TrackStack.hh"

G4TrackStack::G4TrackStack()
:n_stackedTrack(0),firstStackedTrack(0),lastStackedTrack(0)
{;}

G4TrackStack::~G4TrackStack()
{;}

const G4TrackStack & G4TrackStack::operator=(const G4TrackStack &right) 
{
  n_stackedTrack = right.n_stackedTrack;
  firstStackedTrack = right.firstStackedTrack;
  lastStackedTrack = right.lastStackedTrack;
  return *this; 
}

int G4TrackStack::operator==(const G4TrackStack &right) const
{ return (firstStackedTrack==right.firstStackedTrack); }
int G4TrackStack::operator!=(const G4TrackStack &right) const
{ return (firstStackedTrack!=right.firstStackedTrack); }

void G4TrackStack::TransferTo(G4TrackStack * aStack)
{
  if(n_stackedTrack==0) return;

  if(aStack->n_stackedTrack == 0)
  {
    *aStack = *this;
  }
  else
  {
    aStack->lastStackedTrack->SetNext( firstStackedTrack );
    firstStackedTrack->SetPrevious( aStack->lastStackedTrack );
    aStack->lastStackedTrack = lastStackedTrack;
    aStack->n_stackedTrack += n_stackedTrack;
  }

  n_stackedTrack = 0;
  firstStackedTrack = 0;
  lastStackedTrack = 0;
}

G4StackedTrack * G4TrackStack::PopFromStack()
{
  if( n_stackedTrack == 0 ) return 0;
  G4StackedTrack * aStackedTrack = lastStackedTrack;
  GrabFromStack( aStackedTrack );
  return aStackedTrack;
}

void G4TrackStack::PushToStack( G4StackedTrack * aStackedTrack )
{
  if( n_stackedTrack == 0 )
  {
    aStackedTrack->SetPrevious( 0 );
    firstStackedTrack = aStackedTrack;
  }
  else
  {
    lastStackedTrack->SetNext( aStackedTrack );
    aStackedTrack->SetPrevious( lastStackedTrack );
  }
  lastStackedTrack = aStackedTrack;
  n_stackedTrack++;
}

void G4TrackStack::GrabFromStack( G4StackedTrack * aStackedTrack )
{
  if( n_stackedTrack == 1 )
  {
    firstStackedTrack = 0;
    lastStackedTrack = 0;
  }
  else
  {
    if( aStackedTrack == firstStackedTrack )
    {
      firstStackedTrack = aStackedTrack->GetNext();
      firstStackedTrack->SetPrevious( 0 );
    }
    else
    {
      if( aStackedTrack == lastStackedTrack )
      {
        lastStackedTrack = aStackedTrack->GetPrevious();
        lastStackedTrack->SetNext( 0 );
      }
      else
      {
        aStackedTrack->GetPrevious()
          ->SetNext( aStackedTrack->GetNext() );
        aStackedTrack->GetNext()
          ->SetPrevious( aStackedTrack->GetPrevious() );
      }
    }
  }
  n_stackedTrack--;
}

void G4TrackStack::clear()
{
  G4StackedTrack * aStackedTrack = firstStackedTrack;
  G4StackedTrack * nextStackedTrack;

  if ( n_stackedTrack == 0 ) return;

  // delete tracks in the stack
  while( aStackedTrack != 0 )
  {
    nextStackedTrack = aStackedTrack->GetNext();
    delete aStackedTrack->GetTrack();
    delete aStackedTrack;
    aStackedTrack = nextStackedTrack;
  }
  n_stackedTrack = 0;
  firstStackedTrack = 0;
  lastStackedTrack = 0;
}



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
// $Id: G4ViewerList.cc,v 1.3 2001/07/11 10:09:18 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $

#include "G4ViewerList.hh"

void G4ViewerList::remove(G4VViewer* viewer) {
  G4ViewerListIterator iViewer;
  for (iViewer = begin(); iViewer != end(); ++iViewer) {
    if (*iViewer == viewer) break;
  }
  if (iViewer != end()) erase(iViewer);
}

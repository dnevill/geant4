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
// $Id: G4OpenGLXmFourArrowButtons.cc,v 1.4 2001/07/11 10:08:57 gunter Exp $
// GEANT4 tag $Name: geant4-04-00 $
//
//Four arrow buttons class. Inherits from G4OpenGLXmVWidgetComponent

#ifdef G4VIS_BUILD_OPENGLXM_DRIVER

#include "G4OpenGLXmVWidgetComponent.hh"
#include "G4OpenGLXmVWidgetContainer.hh"
#include "G4OpenGLXmFourArrowButtons.hh"
#include <X11/Intrinsic.h>
#include "globals.hh"

G4OpenGLXmFourArrowButtons::G4OpenGLXmFourArrowButtons (XtCallbackRec** c)
{
  callback = c;
}

G4OpenGLXmFourArrowButtons::~G4OpenGLXmFourArrowButtons ()
{}

void G4OpenGLXmFourArrowButtons::AddYourselfTo (G4OpenGLXmVWidgetContainer* container)
{

  pView = container->GetView ();
  ProcesspView ();

  parent = container->GetPointerToWidget ();

  arrow_form = XtVaCreateManagedWidget 
    ("arrow_form",
     xmFormWidgetClass,
     *parent,
     XmNfractionBase, 3,

     XtNvisual, visual, 
     XtNdepth, depth, 
     XtNcolormap, cmap, 
     XtNborderColor, borcol,
     XtNbackground, bgnd,

     NULL);


///////////////`up' arrow///////////////  
  arrow = XtVaCreateManagedWidget 
    ("up_arrow",
     xmArrowButtonGadgetClass, 
     arrow_form,
     
     XmNtopAttachment, XmATTACH_POSITION,
     XmNtopPosition, 0,
     
     XmNbottomAttachment, XmATTACH_POSITION,
     XmNbottomPosition, 1,
     
     XmNleftAttachment, XmATTACH_POSITION,
     XmNleftPosition, 1,

     XmNrightAttachment, XmATTACH_POSITION,
     XmNrightPosition, 2,

     XmNarrowDirection, XmARROW_UP,
     XmNuserData, True,
     NULL);
  
  XtAddCallbacks (arrow, 
		  XmNactivateCallback, 
		  callback[0]);
  
  XtAddCallbacks (arrow, 
		  XmNarmCallback, 
		  callback[0]);
  
  XtAddCallbacks (arrow, 
		  XmNdisarmCallback, 
		  callback[0]);
  
///////////////`down' arrow///////////////  
  arrow = XtVaCreateManagedWidget 
    ("down_arrow",
     xmArrowButtonGadgetClass, 
     arrow_form,
     
     XmNtopAttachment, XmATTACH_POSITION,
     XmNtopPosition, 2,

     XmNbottomAttachment, XmATTACH_POSITION,
     XmNbottomPosition, 3,

     XmNleftAttachment, XmATTACH_POSITION,
     XmNleftPosition, 1,

     XmNrightAttachment, XmATTACH_POSITION,
     XmNrightPosition, 2,

     XmNarrowDirection, XmARROW_DOWN,
     XmNuserData, False,
     NULL);
  
  XtAddCallbacks (arrow, 
		  XmNactivateCallback, 
		  callback[1]);
  
  XtAddCallbacks (arrow, 
		  XmNarmCallback, 
		  callback[1]);
  
  XtAddCallbacks (arrow, 
		  XmNdisarmCallback, 
		  callback[1]);
  
///////////////`left' arrow///////////////  
  arrow = XtVaCreateManagedWidget 
    ("left_arrow",
     xmArrowButtonGadgetClass, 
     arrow_form,
     
     XmNtopAttachment, XmATTACH_POSITION,
     XmNtopPosition, 1,
     
     XmNbottomAttachment, XmATTACH_POSITION,
     XmNbottomPosition, 2,
     
     XmNleftAttachment, XmATTACH_POSITION,
     XmNleftPosition, 0,
     
     XmNrightAttachment, XmATTACH_POSITION,
     XmNrightPosition, 1,
     
     XmNarrowDirection, XmARROW_LEFT,
     XmNuserData, False,
     NULL);
  
  XtAddCallbacks (arrow, 
		  XmNactivateCallback, 
		  callback[2]);
  
  XtAddCallbacks (arrow, 
		  XmNarmCallback, 
		  callback[2]);
  
  XtAddCallbacks (arrow, 
		  XmNdisarmCallback, 
		  callback[2]);
  
///////////////`right' arrow///////////////  
  arrow = XtVaCreateManagedWidget 
    ("right_arrow",
     xmArrowButtonGadgetClass, 
     arrow_form,
     
     XmNtopAttachment, XmATTACH_POSITION,
     XmNtopPosition, 1,
     
     XmNbottomAttachment, XmATTACH_POSITION,
     XmNbottomPosition, 2,

     XmNleftAttachment, XmATTACH_POSITION,
     XmNleftPosition, 2,

     XmNrightAttachment, XmATTACH_POSITION,
     XmNrightPosition, 3,

     XmNarrowDirection, XmARROW_RIGHT,
     XmNuserData, True,
     NULL);
  
  XtAddCallbacks (arrow, 
		  XmNactivateCallback, 
		  callback[3]);
  
  XtAddCallbacks (arrow, 
		  XmNarmCallback, 
		  callback[3]);
  
  XtAddCallbacks (arrow, 
		  XmNdisarmCallback, 
		  callback[3]);

}

Widget* G4OpenGLXmFourArrowButtons::GetPointerToParent ()
{
  return parent;
}

Widget* G4OpenGLXmFourArrowButtons::GetPointerToWidget () 
{
  return &arrow_form;
}

#endif

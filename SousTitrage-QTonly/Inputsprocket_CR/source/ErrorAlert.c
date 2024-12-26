/*	File:		ErrorAlert.c	Contains:	xxx put contents here xxx	Version:	xxx put version here xxx	Copyright:	© 1999 by Apple Computer, Inc., all rights reserved.	File Ownership:		DRI:				xxx put dri here xxx		Other Contact:		xxx put other contact here xxx		Technology:			xxx put technology here xxx	Writers:		(BWS)	Brent Schorsch	Change History (most recent first):	   <SP1>	  7/1/99	BWS		first checked in*///₯	ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ	Includes#include <Dialogs.h>#include <Processes.h>#include <NumberFormatting.h>#include <TextUtils.h>#include "ErrorAlert.h"//#include "AppShellResources.h"//₯	ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ	Private Definitions//₯	ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ	Private Types//₯	ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ	Private Variablesunsigned char gFatalErrOccuredStr[] = "\pA fatal error has occured (";unsigned char gErrOccuredStr[] = "\pAn error has occured (";unsigned char gEndParenStr[] = "\p)";//₯	ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ	Private Functions//₯	ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ	Public Variables//₯	ΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡΡ	AboutBoxvoidErrorAlert(StringPtr errorStr, OSStatus errNum, Boolean shouldQuit){Str255					titleStr;Str31					errorNumAsStr;SInt32					length = 0;SInt16					itemHit;AlertStdAlertParamRec	pb;		//₯Κset up the error string with the error number	NumToString (errNum, errorNumAsStr);		if (shouldQuit)	{		BlockMoveData (&gFatalErrOccuredStr[1], &titleStr[1], gFatalErrOccuredStr[0]);		length = gFatalErrOccuredStr[0];	}	else	{		BlockMoveData (&gErrOccuredStr[1], &titleStr[1], gErrOccuredStr[0]);		length = gErrOccuredStr[0];	}		BlockMoveData (&errorNumAsStr[1], &titleStr[1+length], errorNumAsStr[0]);	length += errorNumAsStr[0];	BlockMoveData (&gEndParenStr[1], &titleStr[1+length], gEndParenStr[0]);	length += gEndParenStr[0];		titleStr[0] = length;		//₯Κset up the pb for StandardAlert	pb.movable = false;	pb.helpButton = false;	pb.filterProc = nil;	pb.defaultText = (StringPtr) kAlertDefaultOKText;	pb.cancelText = nil;	pb.otherText = nil;	pb.defaultButton = kStdOkItemIndex;	pb.cancelButton = kStdCancelItemIndex;	pb.position = kWindowAlertPositionParentWindowScreen;	StandardAlert(kAlertStopAlert, titleStr, errorStr, &pb, &itemHit);		if (shouldQuit)		ExitToShell();}
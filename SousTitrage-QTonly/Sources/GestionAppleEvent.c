#include "BB.Globals_C.h"#include "E3DEMO.H"#include <SegLoad.h>#include <Slots.h>#include <Menus.h>#include <Devices.h>#include <Events.h>#include <Menus.h>#include <Devices.h>#include <Events.h>#include <Files.h>#include <AppleEvents.h>// protos pour le dialog de quitpascal Boolean QuitModalFilter(DialogPtr theDialog ,EventRecord *event,short *itemhit);// les globals extern MyQDGlobals QD;extern AppGlobals G;extern Boolean	gDone;							/* Set to true if user selects Quit */#define   SFGsignature 'SFGr'/* Ce fichier regroupe les routines qui permettent l'acc�s aux autres applications	Le lancement d'autre application et l'envoie r�ception d'apple event*//* Routine to launch the MoniteurVideo application in the background     based on the desktop database and the process manager	 La signature est 'hktv'*/pascal OSErr launchSFG(){   ProcessSerialNumber process;   ProcessInfoRec InfoRec;   DTPBRec DeskTopPB;   HVolumeParam volPB;   Boolean SFGFound;   FSSpec SFGFSSpec;   OSErr err;   LaunchParamBlockRec theLaunchParams;  	process.highLongOfPSN = 0;  	process.lowLongOfPSN = kNoProcess;  	InfoRec.processInfoLength = sizeof(ProcessInfoRec);  	InfoRec.processName = NULL;  	InfoRec.processAppSpec = NULL;  	SFGFound = false;  	while ((!SFGFound) && (GetNextProcess(&process) == noErr))   		if (GetProcessInformation(&process, &InfoRec) == noErr)     		if ((InfoRec.processType == 'APPL') && (InfoRec.processSignature == SFGsignature))       			SFGFound = true;  	if (SFGFound) return noErr;		volPB.ioNamePtr = NULL;  	volPB.ioVolIndex = 1;  	SFGFound = false;  	while ((!SFGFound) && (PBHGetVInfo((HParmBlkPtr)&volPB, false) == noErr))  	{     	DeskTopPB.ioNamePtr = NULL;     	DeskTopPB.ioVRefNum = volPB.ioVRefNum;	    if (PBDTGetPath(&DeskTopPB) == noErr)	    {	       DeskTopPB.ioNamePtr = (StringPtr)&SFGFSSpec.name;	       DeskTopPB.ioIndex = 0;	       DeskTopPB.ioFileCreator = SFGsignature;	       if (PBDTGetAPPL(&DeskTopPB, false) == noErr) 	       {	       		SFGFSSpec.vRefNum = volPB.ioVRefNum;	       		SFGFSSpec.parID = DeskTopPB.ioAPPLParID;	       		SFGFound = true;	    	}	    }	    volPB.ioVolIndex ++;    }	if (!SFGFound) return fnfErr;     theLaunchParams.launchBlockID = extendedBlock;    theLaunchParams.launchEPBLength = extendedBlockLen;    theLaunchParams.launchFileFlags = 0;    theLaunchParams.launchControlFlags = launchContinue + launchNoFileFlags;    theLaunchParams.launchAppSpec = &SFGFSSpec;    theLaunchParams.launchAppParameters = NULL;  	err = LaunchApplication(&theLaunchParams);	return err; } 	 /* Routine to launch the MoniteurVideo application     based on the desktop database and the process manager	 La signature est 'hktv'	 	 */	 pascal OSErr	launchMoniteurVideo(void){ProcessSerialNumber			process;ProcessInfoRec						InfoRec;DTPBRec								DeskTopPB;HVolumeParam						volPB;Boolean									SFGFound;FSSpec									SFGFSSpec;LaunchParamBlockRec			theLaunchParams;OSErr									err;		process.highLongOfPSN = 0;		process.lowLongOfPSN = kNoProcess;		InfoRec.processInfoLength = sizeof(ProcessInfoRec);		InfoRec.processName = nil;		InfoRec.processAppSpec = nil;		SFGFound = false;				while (  (!SFGFound)  &&  (!GetNextProcess(&process) ) ) {				if  (!GetProcessInformation(&process, &InfoRec) )					if(  (InfoRec.processType == 'APPL' ) && (InfoRec.processSignature == 'hktv')  )SFGFound= true;				}						if (SFGFound ) return (noErr);		volPB.ioNamePtr = nil;		volPB.ioVolIndex = 1;		SFGFound = false;		while ( !SFGFound && ( PBHGetVInfo((HParmBlkPtr)&volPB, false) ==noErr) ) {					DeskTopPB.ioNamePtr =(StringPtr) nil;					DeskTopPB.ioVRefNum = volPB.ioVRefNum;										if (PBDTGetPath(&DeskTopPB)  ==noErr){							DeskTopPB.ioNamePtr = &SFGFSSpec.name;							DeskTopPB.ioIndex = 0;							DeskTopPB.ioFileCreator = 'hktv';							if ( PBDTGetAPPL(&DeskTopPB, false) ==noErr ){									SFGFSSpec.vRefNum = volPB.ioVRefNum;									SFGFSSpec.parID =DeskTopPB.ioAPPLParID;									SFGFound = true;								}						}					volPB.ioVolIndex ++;		}						if (!SFGFound) return  fnfErr;		theLaunchParams.launchBlockID = extendedBlock;		theLaunchParams.launchEPBLength = extendedBlockLen;		theLaunchParams.launchFileFlags = 0;		theLaunchParams.launchControlFlags = launchContinue + launchNoFileFlags+launchDontSwitch;		theLaunchParams.launchAppSpec = &SFGFSSpec;		theLaunchParams.launchAppParameters = nil;		err = LaunchApplication(&theLaunchParams);		return(err);}	 pascal void QuitMoniteurVideo(void){ProcessSerialNumber			process;ProcessInfoRec						InfoRec;Boolean									SFGFound;OSErr									err;AppleEvent							AE;AEDesc									target;		process.highLongOfPSN = 0;		process.lowLongOfPSN = kNoProcess;		InfoRec.processInfoLength = sizeof(ProcessInfoRec);		InfoRec.processName = nil;		InfoRec.processAppSpec = nil;		SFGFound = false;				while (  (!SFGFound)  &&  (!GetNextProcess(&process) ) ) {				if  (!GetProcessInformation(&process, &InfoRec) )					if(  (InfoRec.processType == 'APPL' ) && (InfoRec.processSignature == 'hktv')  ) {						            err = AECreateDesc(typeProcessSerialNumber, (Ptr)&process, sizeof(process), &target);																		if (!err)	err = AECreateAppleEvent(kCoreEventClass, kAEQuitApplication, &target, kAutoGenerateReturnID,																				kAnyTransactionID, &AE);									if (!err) 	AEDisposeDesc(&target);																		/* Again, the Finder will convert the AppleEvent to puppetstrings if */									/* the application is a System 6 or non-AE aware app.  This ONLY  */									/* happens for the 4 required (oapp,odoc,pdoc, and quit) AppleEvents  */									/* and ONLY if you use the PSN for the address */									if (!err)	AESend(&AE, nil, kAENoReply + kAEAlwaysInteract + kAECanSwitchLayer, kAENormalPriority, 																	kAEDefaultTimeout,	nil, nil);									AEDisposeDesc(&AE);									SFGFound=true;									}//(InfoRec.processType == 'APPL' ) && (InfoRec.processSignature == 'hktv')				}				} //// ----------pascal void QuitSansFauteGrammaire(void){ProcessSerialNumber		process;ProcessInfoRec			InfoRec;Boolean					SFGFound;OSErr					err;AppleEvent				AE;AEDesc					target;		process.highLongOfPSN = 0;		process.lowLongOfPSN = kNoProcess;		InfoRec.processInfoLength = sizeof(ProcessInfoRec);		InfoRec.processName = nil;		InfoRec.processAppSpec = nil;		SFGFound = false;				while (  (!SFGFound)  &&  (!GetNextProcess(&process) ) ) {				if  (!GetProcessInformation(&process, &InfoRec) )					if(  (InfoRec.processType == 'APPL' ) && (InfoRec.processSignature == 'SFGr')  ) {						            err = AECreateDesc(typeProcessSerialNumber, (Ptr)&process, sizeof(process), &target);																		if (!err)	err = AECreateAppleEvent(kCoreEventClass, kAEQuitApplication, &target, kAutoGenerateReturnID,																				kAnyTransactionID, &AE);									if (!err) 	AEDisposeDesc(&target);																		/* Again, the Finder will convert the AppleEvent to puppetstrings if */									/* the application is a System 6 or non-AE aware app.  This ONLY  */									/* happens for the 4 required (oapp,odoc,pdoc, and quit) AppleEvents  */									/* and ONLY if you use the PSN for the address */									if (!err)	AESend(&AE, nil, kAENoReply + kAEAlwaysInteract + kAECanSwitchLayer, kAENormalPriority, 																	kAEDefaultTimeout,	nil, nil);									AEDisposeDesc(&AE);									SFGFound=true;									}//(InfoRec.processType == 'APPL' ) && (InfoRec.processSignature == 'SFGr')				}				} //pascal void ActiveSansFauteGrammaire(void){ProcessSerialNumber			process;ProcessInfoRec						InfoRec;Boolean									SFGFound;		process.highLongOfPSN = 0;		process.lowLongOfPSN = kNoProcess;		InfoRec.processInfoLength = sizeof(ProcessInfoRec);		InfoRec.processName = nil;		InfoRec.processAppSpec = nil;		SFGFound = false;				while (  (!SFGFound)  &&  (!GetNextProcess(&process) ) ) {				if  (!GetProcessInformation(&process, &InfoRec) )					if(  (InfoRec.processType == 'APPL' ) && (InfoRec.processSignature == 'SFGr')  ) {						         	SetFrontProcess(&process);	SFGFound=true;					}//(InfoRec.processType == 'APPL' ) && (InfoRec.processSignature == 'SFGr')				}// while (!...				} ///*	Handle the �oapp� AppleEvent.	*/pascal OSErr	OAPPHandler(AppleEvent theAppleEvent, AppleEvent reply, long handlerRefCon){#pragma unused (reply, handlerRefCon)	OSErr		oappErr;	AEKeyword	missedKeyWord;	DescType	actualType;	Size		actualSize;		oappErr = AEGetAttributePtr(&theAppleEvent, keyMissedKeywordAttr, typeWildCard, &actualType, (Ptr) &missedKeyWord, sizeof(missedKeyWord), &actualSize);	if (!oappErr)					/* If no error, then a missing parameter was found */		return errAEParamMissed;		/*	Do whatever needs to be done when starting up and return noErr */	// on ouvre la derni�re police d'affichage utilis�e	// et le dernier fichier s'il existe. 	 	if (G.Ve_GDHandle )OpenLastDisplayFontUsed(); 	 	if (G.AutoOpenLastFile) OpenLastFileUsed();	return	noErr;}/*	Handle the �odoc� AppleEvent.	*/pascal OSErr	ODOCHandler(AppleEvent theAppleEvent, AppleEvent reply, long handlerRefCon){#pragma unused (reply, handlerRefCon)	OSErr			odocErr;	AEKeyword		missedKeyWord;	DescType		actualType;	Size			actualSize;	AEDescList		documentList;	long			itemsInList;	long			i;	AEKeyword		keyWord;	DescType		typeCode;	FSSpec			documentFileSpec;	TargetID		senderType;	OSType			senderCreator;	ProcessSerialNumber	thePSN;		odocErr = AEGetParamDesc(&theAppleEvent, keyDirectObject, typeAEList, &documentList);	/* Get list of documents to open */	if (odocErr)		return odocErr;			odocErr = AEGetAttributePtr(&theAppleEvent, keyMissedKeywordAttr, typeWildCard, &actualType, (Ptr) &missedKeyWord, sizeof(missedKeyWord), &actualSize);	if (!odocErr)					/* If no error, then a missing parameter was found */		return errAEParamMissed;		/* 		If we�re in the background, see if the event was sent from the Finder.  If so,		switch to the front.	*/		if (G.InBackground) {		odocErr = AEGetAttributePtr(&theAppleEvent, keyAddressAttr, typeTargetID, &actualType, (Ptr) &senderType, sizeof(senderType), &actualSize);		BlockMove((Ptr) (&(senderType.name.u.portTypeStr)+1), (Ptr) &(senderCreator), 4);		if (senderCreator == 'MACS') {			thePSN.highLongOfPSN = 0;			thePSN.lowLongOfPSN = kCurrentProcess;			SetFrontProcess(&thePSN);		}	}	/* Open all the documents in documentList */		odocErr = AECountItems(&documentList, &itemsInList);		/* Get number of documents */		for (i = 1; i <= itemsInList; i++) {		odocErr = AEGetNthPtr(&documentList, i, typeFSS, &keyWord, &typeCode, (Ptr) &documentFileSpec, sizeof(documentFileSpec), &actualSize);		C_DoFileOpen(&documentFileSpec);	}		 	if (G.Ve_GDHandle)OpenLastDisplayFontUsed();		odocErr = AEDisposeDesc(&documentList);			/* Dispose of AE structure created by AEGetParamDesc */	return	noErr;}/*	Handle the �pdoc� AppleEvent.	*/pascal OSErr	PDOCHandler(AppleEvent theAppleEvent, AppleEvent reply, long handlerRefCon){#pragma unused (reply, handlerRefCon)	OSErr		pdocErr;	AEKeyword	missedKeyWord;	DescType	actualType;	Size		actualSize;	AEDescList	documentList;	long		itemsInList;	long		i;	AEKeyword	keyWord;	DescType	typeCode;	FSSpec		documentFileSpec;		pdocErr = AEGetParamDesc(&theAppleEvent, keyDirectObject, typeAEList, &documentList);	/* Get list of documents to open */	pdocErr = AEGetAttributePtr(&theAppleEvent, keyMissedKeywordAttr, typeWildCard, &actualType, (Ptr) &missedKeyWord, sizeof(missedKeyWord), &actualSize);	if (!pdocErr)					/* If no error, then a missing parameter was found */		return errAEParamMissed;		/* Print all the documents in documentList */		pdocErr = AECountItems(&documentList, &itemsInList);		/* Get number of documents */		for (i = 1; i <= itemsInList; i++) {		pdocErr = AEGetNthPtr(&documentList, i, typeFSS, &keyWord, &typeCode, (Ptr) &documentFileSpec, sizeof(documentFileSpec), &actualSize);		C_DoFileOpen(&documentFileSpec);	}			pdocErr = AEDisposeDesc(&documentList);					/* Dispose of AE structure created by AEGetParamDesc */	return	noErr;}/*	Handle the �quit� AppleEvent.	*/pascal OSErr	QUITHandler(AppleEvent theAppleEvent, AppleEvent reply, long handlerRefCon){#pragma unused (reply, handlerRefCon)	OSErr		quitErr;	AEKeyword	missedKeyWord;	DescType	actualType;	Size		actualSize;	short 		itemhit;	quitErr = AEGetAttributePtr(&theAppleEvent, keyMissedKeywordAttr, typeWildCard, &actualType, (Ptr) &missedKeyWord, sizeof(missedKeyWord), &actualSize);	if (!quitErr)					/* If no error, then a missing parameter was found */		return errAEParamMissed;	/*	ON FERME LE LOGICIEL, ON VERIFIE QU'IL NE FAUT PAS SAUVEGARDER LE FICHIER EN COURS */	if (G.ListingTE) {			SetPort((WindowPtr)&G.ListingWindow);			TransfertTE_Memoire(G.ListingTE,G.ListingTEStNum,G.ListingTEStItem);			TEDispose(G.ListingTE);			G.ListingTE=nil;			InvalRect((Rect*)&((GrafPtr)&G.ListingWindow)->portRect);			DoUpdate((WindowPtr)&G.ListingWindow);	}	TransfertSaisieMemoire();	DrawSt_enCourDansListing();	/* on regarde s'il faut faire une sauvegarde du fichier actuel avant de quitter	*/  	if (G.ChangeSinceLastSave&0x7fff) { 	  // on demande son choix � l'utilisateur (sauvegarder, ne pas sauv., annuler)				  itemhit=Alert(152,(ModalFilterProcPtr)QuitModalFilter);		  if (itemhit==1)	{ C_SaveData(nil);  gDone=true; }		  if (itemhit!=3)	gDone=true;   	} else gDone=true;   	return	noErr;}/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*//* les  routines qui suivent ne sont pas utilis�es pour l'intant *//*	Handle high level events */pascal void	DoHighLevelEvent(EventRecord *event){	OSErr	AEProcessResult;		switch	(event->message) {		case kCoreEventClass:	AEProcessResult = AEProcessAppleEvent(event);	/*	Handle core AppleEvents */								break;		//case rSectionType:	break;											/*	Handle Edition Manager AppleEvents */				//default:				HandleGenericHighLevelEvent(event);				/*	Other high level events */		//						break;		}}pascal void	HandleGenericHighLevelEvent(EventRecord *event){	TargetID	eventSenderInfo;	unsigned	long eventIdentifier;	Ptr			dataBuffer;	unsigned	long dataSize;	OSErr	HLEventError;		dataSize = 0;	dataBuffer = nil;	HLEventError = AcceptHighLevelEvent(&eventSenderInfo, &eventIdentifier, dataBuffer, &dataSize);		/*		Since we don�t know how much data is coming in, call AcceptHighLevelEvent once to		find out how much data was sent, then use create a new buffer large enough to hold		all the data, then call AcceptHighLevelEvent again to get the data.	*/		if (HLEventError == bufferIsSmall) {		dataBuffer = NewPtr(dataSize);		HLEventError = AcceptHighLevelEvent(&eventSenderInfo, &eventIdentifier, dataBuffer, &dataSize);	}			/*	Dispatch the high level event to the proper routine depending on the message class */		switch	(event->message) {	}		if (dataBuffer)		DisposePtr(dataBuffer);}
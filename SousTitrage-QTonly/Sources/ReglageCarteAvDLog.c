/* *	Dialog Module, created by Resorcerer		light Modified by Eric Tiquet  */#include "BB.Globals_C.h"#include <Menus.h>#include <Devices.h>#include <Events.h>#include <DiskInit.h>#include <Dialogs.h>#include <Files.h>#include <Fonts.h>#include <Lists.h>#include <Menus.h>#include <Resources.h>#include <Memory.h>#include <OSUtils.h>#include <Events.h>#include <Packages.h>#include <Scrap.h>#include <Script.h>#include <SegLoad.h>#include <StdArg.h>#include <stdio.h>#include <ToolUtils.h>#include <QuickTimeComponents.h>#include <ImageCompression.h>#define thisDialogID 264/* Symbolic Dialog Item Numbers */static enum {	BUT1_OK = 1,	BUT2_Cancel,	BUT3_r,	CTRL4,	CTRL5,	CTRL6,	CTRL7,	CTRL8,	CTRL9,	CTRL10,	CTRL11,	CTRL12,	CTRL13,	STXT14_R,	STXT15_R,	STXT16_Lumi,	STXT17_Contraste,	STXT18_Couleur,	STXT19_Contour,	STXT20_Hue,	USER21,	USER22,	LASTITEM	};#define OK_ITEM 	BUT1_OK#define CANCEL_ITEM 	BUT2_Cancel/* Useful constants */#ifndef ENTERkey#define ENTERkey	0x3#endif#ifndef DELETEkey#define DELETEkey	0x8#endif#ifndef NIL#define NIL ((void *)0)#endif#ifndef TRUE#define TRUE 1#endif#ifndef FALSE#define FALSE 0#endif#ifndef FRONT_WINDOW#define FRONT_WINDOW  ((WindowPtr) (-1L))#endif/* Prototypes */int				ReglageCarteAV(void);static  DialogPtr 	OpenThisDialog(void);static  void	CloseThisDialog(DialogPtr dlog);static void		DoDialogUpdate(DialogPtr dlog);static void		DoDialogActivate(DialogPtr dlog, int activ);static void		DoDialogContent(DialogPtr dlog, EventRecord *evt);static int		DoDialogItem(DialogPtr dlog, short itemHit);static  pascal  Boolean MyFilter(DialogPtr dlog, EventRecord *evt, short *itemHit);static  Boolean CheckUserItems(Point where, short *itemHit);static int     AnyBadValues(DialogPtr dlog);static long    strlen(char *);static char   *strcpy(char *dst, char *src);static char   *PascalToC(char *pstr);static char   *CToPascal(char *cstr);static  void    PutDlgString(DialogPtr dlog, int item, char *str, int sel);static void    PutDlgWord(DialogPtr dlog, int item, int val, int sel);static void    PutDlgLong(DialogPtr dlog, int item, long val, int sel);static void    PutDlgChkRadio(DialogPtr dlog, int item, int val);static int     GetDlgString(DialogPtr dlog, int item, char *str);static int     GetDlgWord(DialogPtr dlog, int item, short *val);static int     GetDlgLong(DialogPtr dlog, int item, long *val);static int     GetDlgChkRadio(DialogPtr dlog, int item);static int     TextSelected(DialogPtr dlog);OSType  CanPaste(int n, ...);void    FrameDefault(DialogPtr dlog, int item, int frame);static void    GetDlgPanel(DialogPtr dlog, int item, Rect *panel);static void GetCurrentReglage(AvPrefPtr pref);static void SetCurrentReglage(AvPrefPtr pref);static void DoReglageParDefault(void);static void SetDialogReglage(AvPrefPtr  pref);void RAZReglageAV(void);// les globalsextern AppGlobals G;extern MyQDGlobals QD;extern SGChannel 	gVideoChannel;extern ComponentInstance gComponentInstance;static Point where;static int modifiers;static AvPref	thepref;static DialogPtr the_dlog;extern SeqGrabComponent 	gSeqGrabber;extern Boolean gMaskingVitc;extern WindowPtr gMonitor;/* *	Display this modal dialog.  Return TRUE if OK, FALSE if CANCEL or error. *	If the dialog displays values from outside this module, you should either *	import them from globals, or change the argument list of this routine to *	bring them in and pass them to OpenThisDialog(), DoDialogItem(), etc. */void RAZReglageAV(void){AvPref pref;			GetCurrentReglage(&pref);			VDGetVideoDefaults(gComponentInstance,							&pref.black,							&pref.white,							&pref.lumiere,							&pref.hue,							&pref.couleur,							&pref.contraste,							&pref.contour);			SetCurrentReglage(&pref);			} //RAZReglageAVint ReglageCarteAV()	{		short itemHit,okay,keepGoing=TRUE; GrafPtr oldPort;		/* Build dialog window and install its item values */				GetPort(&oldPort);		the_dlog = OpenThisDialog();		if (the_dlog == NIL) return(FALSE);		/* Entertain filtered user events until dialog is dismissed */				while (keepGoing) {			ModalDialog(MyFilter,&itemHit);			keepGoing = DoDialogItem(the_dlog,itemHit);			}				/*		 *	Do final processing of item values, such as exporting them to caller.		 *	DoDialogItem() has already called AnyBadValues().		 */				if (okay = (itemHit==OK_ITEM)) {		/* Or whatever is equivalent */			}		/* That's all, folks! */				CloseThisDialog(the_dlog);		SetPort(oldPort);		SetDialogFont(0);		return(okay);	}/* *	We have to have a filter function, at the very least so that we can outline *	any default button, entertain keyboard editing commands, cmd-period canceling, etc. *	Note that you do not need to have a special user item covering the default button *	in your dialog item list. */static pascal Boolean MyFilter(DialogPtr dlog, EventRecord *evt, short *itemHit)	{		Boolean ans=FALSE,doHilite=FALSE; WindowPtr w,window;		short type,ch,part; Handle hndl; Rect box;		static long then; static Point clickPt;				w = (WindowPtr)(evt->message);		switch(evt->what) {			case updateEvt:				if (w == dlog) {					/* Update our dialog contents */					DoDialogUpdate(dlog);					ans = TRUE; *itemHit = 0;					}				 else {					/*					 *	Call your main event loop DoUpdate(w) routine here if you					 *	don't want unsightly holes in background windows caused					 *	by nested alerts, balloon help, or screen savers (see					 *	Tech Note #304).					 */					DoUpdate(w);					}				break;			case activateEvt:				if (w == dlog) {					DoDialogActivate(dlog,(evt->modifiers & activeFlag)!=0);					*itemHit = 0;					}				 else {					/*					 *	Call your main event loop DoActivate(w) routine here if					 *	you want to deactivate the former frontmost window, in order					 *	to unhighlight any selection, scroll bars, etc.					 */					}				break;			case mouseDown:					where = evt->where;		/* Make info available to DoDialog() */					part = FindWindow(evt->where, &window);				if ( part==inDrag)               /* pass screenBits.bounds to get all gDevices */						if	(window==(WindowPtr)BB_FrontNonFloatingWindow()) {							 DragWindow(window, evt->where,&QD.screenBits.bounds); //&QD.screenbit bounds); //							 ans=true;							*itemHit = 0;						 } 			case mouseUp:				where = evt->where;		/* Make info available to DoDialog() */				GlobalToLocal(&where);				modifiers = evt->modifiers;				break;			case keyDown:				if ((ch=(unsigned char)evt->message)=='\r' || ch==ENTERkey) {					*itemHit = OK_ITEM /* Default Item Number here */;					doHilite = ans = TRUE;					}				 else if (evt->modifiers & cmdKey) {					ch = (unsigned char)evt->message;					switch(ch) {						case 'x':						case 'X':							if (TextSelected(dlog))								{ SystemEdit(3); ZeroScrap(); DialogCut(dlog); TEToScrap(); }							 else {								/* Cut from anything else cuttable, like a list */								}							break;						case 'c':						case 'C':							if (TextSelected(dlog))								{ SystemEdit(3); ZeroScrap(); DialogCopy(dlog); TEToScrap(); }							 else {								/* Copy from anything else copyable, like a list */								}							break;						case 'v':						case 'V':							if (CanPaste(1,'TEXT'))								{ TEFromScrap(); DialogPaste(dlog); }							 else {							 	/* Deal with any other pasteable scraps here */								}							break;						case 'a':						case 'A':							if (((DialogPeek)dlog)->editField >= 0) {								/* Dialog has text edit item: select all */								SelectDialogItemText(dlog,((DialogPeek)dlog)->editField+1,0,32767);								}							 else {								}							*itemHit = 0;							break;						case '.':							*itemHit = CANCEL_ITEM;							doHilite = TRUE;							break;						}					ans = TRUE;		/* Other cmd-chars ignored */					}				break;			}		if (doHilite) {			GetDialogItem(dlog,*itemHit,&type,&hndl,&box);			/* Reality check */			if (type == (btnCtrl+ctrlItem)) {				long soon = TickCount() + 7;		/* Or whatever feels right */				HiliteControl((ControlHandle)hndl,1);				while (TickCount() < soon) ;		/* Leave hilited for a bit */				}			}		return(ans);	}/* * Mouse down event: * Check if it's in some user item, and convert to itemHit if appropriate. */static Boolean CheckUserItems(Point where, short *itemHit)	{		return(FALSE);	}/* * Redraw the contents of this dialog due to update event. * If you have not installed UserItem draw routines, you should redraw * them explicitly here; otherwise, UpdateDialog() will call your routines. */static void DoDialogUpdate(DialogPtr dlog)	{		GrafPtr oldPort;		short type; Handle hndl; Rect box,rect;		PixPatHandle the_pixpat;		RgnHandle	rgn,rgn1;				GetPort(&oldPort);		SetPort(dlog);		BeginUpdate(dlog);				the_pixpat=GetPixPat(129);		TextFont(kFontIDGeneva);		TextSize(9);						if (the_pixpat!=nil){			rgn=NewRgn();			rgn1=NewRgn();			RectRgn(rgn,&dlog->portRect);						GetDialogItem(dlog,22,&type,&hndl,&rect);			RectRgn(rgn1,&rect);			DiffRgn(rgn,rgn1,rgn);			GetDialogItem(dlog,21,&type,&hndl,&rect);			RectRgn(rgn1,&rect);			DiffRgn(rgn,rgn1,rgn);						FillCRgn(rgn,the_pixpat);			DisposePixPat(the_pixpat);			DisposeRgn(rgn);			DisposeRgn(rgn1);		}			Draw_Icon_Text_Ditl(dlog);		DrawControls(dlog);				GetDialogItem(dlog,14,&type,&hndl,&rect);		MoveTo(rect.left,rect.bottom); LineTo(rect.right,rect.bottom);		GetDialogItem(dlog,15,&type,&hndl,&rect);		MoveTo(rect.left,rect.bottom); LineTo(rect.right,rect.bottom);				GetDialogItem(dlog,21,&type,&hndl,&rect);		FrameRectOneLine(&rect,true);		GetDialogItem(dlog,22,&type,&hndl,&rect);		FrameRectOneLine(&rect,true);		FrameDefault(dlog,BUT1_OK,TRUE);				EndUpdate(dlog);		SetPort(oldPort);	}/* * Activate event: Activate or deactivate this dialog and any items in it */static void DoDialogActivate(DialogPtr dlog, int activ)	{		SetPort(dlog);	}/* * Build this dialog's window on desktop, and install initial item values. * Return the dlog opened, or NIL if error (no resource, no memory). */static DialogPtr OpenThisDialog()	{		short type; Handle hndl; Rect box; GrafPtr oldPort;		DialogPtr dlog; unsigned char *p,str[256];		unsigned short	value;		long	inputF,outputF;		unsigned long a,b;		GetPort(&oldPort);		SetDialogFont(kFontIDGeneva); 		the_dlog = GetNewDialog(thisDialogID,NIL,FRONT_WINDOW);		if (the_dlog == NIL) { SysBeep(1); return(NIL); }	/* Poor man's error message */		SetPort(the_dlog);		TextFont(kFontIDGeneva); 		TextSize(9);		/* Fill in dialog's values here */		/* les pop-up menu */		gComponentInstance=SGGetVideoDigitizerComponent(gVideoChannel);		GetCurrentReglage(&thepref);		SetDialogReglage(&thepref);		ShowWindow(the_dlog);		return(the_dlog);	}/* * Clean up any allocated stuff, and return dialog to primordial mists */static void CloseThisDialog(DialogPtr dlog)	{		DisposeDialog(dlog);	/* Call CloseDialog if you provide storage to GetNewDialog */	}/* * Deal with user clicking on an item in this dialog, either modal or non-modal. * The local point is in where; modifiers in modifiers. * Returns whether or not the dialog should be closed (keepGoing). */static int DoDialogItem(DialogPtr dlog, short itemHit)	{		short type,okay=FALSE,keepGoing=TRUE,val;		Handle hndl; Rect box; Point pt;		unsigned char *p,str[256]; unsigned short value,a;		unsigned long b; OSErr result;		if (itemHit<1 || itemHit>=LASTITEM)			return(keepGoing);				/* Only legal items, please */		GetDialogItem(dlog,itemHit,&type,&hndl,&box);		switch(type) {			case ctrlItem+btnCtrl:				switch(itemHit) {					case BUT1_OK:						keepGoing = FALSE; okay = TRUE;						break;					case BUT2_Cancel:						SetCurrentReglage(&thepref);						keepGoing = FALSE;						break;					case BUT3_r:						result = SGPause(gSeqGrabber, true);						DoReglageParDefault();						result = SGPause(gSeqGrabber, false);						break;					}				break;			case ctrlItem+chkCtrl:				value=GetControlValue((ControlHandle)hndl);				if ( itemHit==20){					if (value) 		{	SetControlValue((ControlHandle)hndl,0);	 gMaskingVitc=0;}					else 			{	SetControlValue((ControlHandle)hndl,1);	 gMaskingVitc=1;}					SetPort(gMonitor);					InvalRect(&gMonitor->portRect);					SetPort(dlog);				};				break;			case ctrlItem+radCtrl:				break;			case ctrlItem+resCtrl:					value=GetControlValue((ControlHandle)hndl);					b=(((unsigned long)value)*65535)/100;					a=b;				switch(itemHit) {					case CTRL4:					result = SGPause(gSeqGrabber, true);						VDSetInput(gComponentInstance,value-1);					result = SGPause(gSeqGrabber, false);						break;					case CTRL5:					result = SGPause(gSeqGrabber, true);						VDSetInputStandard(gComponentInstance,(short)value-1);					result = SGPause(gSeqGrabber, false);						break;					case CTRL6:					result = SGPause(gSeqGrabber, true);						VDSetPLLFilterType(gComponentInstance,(unsigned short)value-1);					result = SGPause(gSeqGrabber, false);						break;					case CTRL7:						VDSetBrightness(gComponentInstance,&a);						break;					case CTRL8:						VDSetContrast(gComponentInstance,&a);						break;					case CTRL9:						VDSetSaturation(gComponentInstance,&a);						break;					case CTRL10:						VDSetSharpness(gComponentInstance,&a);						break;					case CTRL11:		/* NOT Enabled */						VDSetHue(gComponentInstance,&a);						break;					case CTRL12:						break;					case CTRL13:						break;					}				break;			case statText:				switch(itemHit) {					case STXT14_R:		/* NOT Enabled */						break;					case STXT15_R:		/* NOT Enabled */						break;					case STXT16_Lumi:		/* NOT Enabled */						break;					case STXT17_Contraste:		/* NOT Enabled */						break;					case STXT18_Couleur:		/* NOT Enabled */						break;					case STXT19_Contour:		/* NOT Enabled */						break;					}				break;			case editText:				break;			case iconItem:				break;			case picItem:				break;			case userItem:				switch(itemHit) {					case USER21:						break;					case USER22:						break;					}				break;			}		if (okay) keepGoing = AnyBadValues(dlog);		return(keepGoing);	}/* * Pull values out of dialog items and deliver TRUE if any of them are * illegal or inconsistent; otherwise deliver FALSE.  If any values are bad, * you should inform your user about the problem here before delivering TRUE. * If any items are missing values, this is the place to assign any defaults. */static int AnyBadValues(DialogPtr dlog)	{		char str[256]; short val,len;		return(FALSE);	}void DoReglageParDefault(void){AvPref pref;			pref=thepref;			VDGetVideoDefaults(gComponentInstance,							&pref.black,							&pref.white,							&pref.lumiere,							&pref.hue,							&pref.couleur,							&pref.contraste,							&pref.contour);			SetCurrentReglage(&pref);			SetDialogReglage(&pref);}static void GetCurrentReglage(AvPrefPtr  pref){long inputF,outputF;				pref->MaskingVitc=gMaskingVitc;		//VDGetInput(gComponentInstance,&pref->entree);		VDGetCurrentFlags(gComponentInstance,&inputF,&outputF);		if (inputF&digiInDoesNTSC) 		pref->standart=0;		if (inputF&digiInDoesPAL) 		pref->standart=1;		if (inputF&digiInDoesSECAM) 	pref->standart=2;				if (inputF&digiInDoesComposite)	pref->entree=0;		if (inputF&digiInDoesSVideo)	pref->entree=1;				VDGetPLLFilterType(gComponentInstance,&pref->type);		VDGetBrightness(gComponentInstance,&pref->lumiere);		VDGetContrast(gComponentInstance,&pref->contraste);		VDGetSaturation(gComponentInstance,&pref->couleur);		VDGetSharpness(gComponentInstance,&pref->contour);		VDGetHue(gComponentInstance,&pref->hue);}static void SetCurrentReglage(AvPrefPtr  pref){		VDSetInput(gComponentInstance,pref->entree);		VDSetInputStandard(gComponentInstance,pref->standart);		VDSetPLLFilterType(gComponentInstance,pref->type);		VDSetBrightness(gComponentInstance,&pref->lumiere);		VDSetContrast(gComponentInstance,&pref->contraste);		VDSetSaturation(gComponentInstance,&pref->couleur);		VDSetSharpness(gComponentInstance,&pref->contour);		VDSetHue(gComponentInstance,&pref->hue);}/* ------ */static void SetDialogReglage(AvPrefPtr  pref){short type; Handle hndl; Rect box;unsigned long a;		GetDialogItem(the_dlog,20,&type,&hndl,&box);		SetControlValue((ControlHandle)hndl,pref->MaskingVitc);/* le type de l'entr�e Vid�o ou SVHS*/				GetDialogItem(the_dlog,3,&type,&hndl,&box);		SetControlValue((ControlHandle)hndl,pref->entree+1);/* le standart de couleur */				GetDialogItem(the_dlog,4,&type,&hndl,&box);		SetControlValue((ControlHandle)hndl,pref->standart+1);/* Broadcast ou VTR */				GetDialogItem(the_dlog,5,&type,&hndl,&box);		SetControlValue((ControlHandle)hndl,pref->type+1);/* les r�glettes *//* brightness*/		GetDialogItem(the_dlog,7,&type,&hndl,&box);		SetControlMinimum((ControlHandle)hndl,0);		SetControlMaximum((ControlHandle)hndl,100);		a=(((unsigned long)pref->lumiere)*100);		a=a/65535;		SetControlValue((ControlHandle)hndl,a);/* contrast*/		GetDialogItem(the_dlog,8,&type,&hndl,&box);		SetControlMinimum((ControlHandle)hndl,0);		SetControlMaximum((ControlHandle)hndl,100);		a=(((unsigned long)pref->contraste)*100);		a=a/65535;		SetControlValue((ControlHandle)hndl,a);		/* couleur*/		GetDialogItem(the_dlog,9,&type,&hndl,&box);		SetControlMinimum((ControlHandle)hndl,0);		SetControlMaximum((ControlHandle)hndl,100);		a=(((unsigned long)pref->couleur)*100);		a=a/65535;		SetControlValue((ControlHandle)hndl,a);		/* contour*/		GetDialogItem(the_dlog,10,&type,&hndl,&box);		SetControlMinimum((ControlHandle)hndl,0);		SetControlMaximum((ControlHandle)hndl,100);		a=(((unsigned long)pref->contour)*100);		a=a/65535;		SetControlValue((ControlHandle)hndl,a);/* hue*/		GetDialogItem(the_dlog,11,&type,&hndl,&box);		SetControlMinimum((ControlHandle)hndl,0);		SetControlMaximum((ControlHandle)hndl,100);		a=(((unsigned long)pref->hue)*100);		a=a/65535;		SetControlValue((ControlHandle)hndl,a);}/*��������������������������������������������������������������������������������������*//* *  The following are various utility routines for general dialog management. *  Typically, you'll want to keep them in a library that is available to all *  your dialog modules; however, they are included here (and declared static) *  as a private library so that you can quickly compile this file for testing. */#define _PrivateLibraries_#ifdef  _PrivateLibraries_/* Local C string length routine */static long strlen(register char *str)	{		register char *p;		p = str;		while (*p++) ;		return((long)(--p - str));	}/* Convert in place a Pascal string to C string, and deliver its address */static char *PascalToC(char *str)	{		register char *p,*q,*end;		end = str + *(unsigned char *)str;		q = (p=str) + 1;		while (p < end) *p++ = *q++;		*p = '\0';		return(str);	}/* *	Convert in place a C string to Pascal string, and deliver its address. *	The C string should not be greater than 255 chars in length, or the *	resulting Pascal string will be truncated to 255 chars. */static char *CToPascal(char *str)	{		register char *p,*q;		register long len;		len = strlen(str);		if (len > 255) len = 255;		p = str + len;		q = p-1;		while (p != str) *p-- = *q--;		*str = len;		return(str);	}/* Dialog Item Stuffers *//* *	Install a given Pascal string, str, into the given static or edit text item *	in the dialog, dlog.  If the item is an edit text item, leave the installed *	text selected or not according to the value of sel (TRUE or FALSE). */static void PutDlgString(DialogPtr dlog, int item, char *str, int sel)	{		short type; Handle hndl; Rect box;		GetDialogItem(dlog,item,&type,&hndl,&box);		SetDialogItemText(hndl,str);		if (type == editText)			SelectDialogItemText(dlog,item,sel?0:32767,32767);		InvalRect(&box);	}/* *	Install a given decimal long value into the static or edit text item of the *	given dialog, dlog.  If the item is an edit text item, leave the installed *	text for the number selected or not according to sel (TRUE or FALSE). */static void PutDlgLong(DialogPtr dlog, int item, long val, int sel)	{		char str[32];		NumToString(val,str);		PutDlgString(dlog,item,str,sel);	}/* *	Same as above, only for an int (word) decimal number. */static void PutDlgWord(DialogPtr dlog, int item, int val, int sel)	{		PutDlgLong(dlog,item,(long)val,sel);	}/* *	Set the given check box or radio button item of the given dialog, dlog, to *	on or off, according to val. */static void PutDlgChkRadio(DialogPtr dlog, int item, int val)	{		short type; Handle hndl; Rect box;		GetDialogItem(dlog,item,&type,&hndl,&box);		SetControlValue((ControlHandle)hndl,val!=0);	}/* *	Deliver the value of the checkbox or radio button item of the given dialog. */static int GetDlgChkRadio(DialogPtr dlog, int item)	{		short type; Handle hndl; Rect box;				GetDialogItem(dlog,item,&type,&hndl,&box);		return(GetControlValue((ControlHandle)hndl) != 0);	}/* Dialog Item Unstuffers *//* *	Retrieve the value of an edit text item in a given dialog, placing the *	resulting Pascal string in the buffer, str, which is assumed large enough *	to hold the text (256 bytes max).  If item is the number of a static text *	item, the empty string is delivered.  Delivers TRUE or FALSE according to *	whether or not the text so delivered was empty.   */static int GetDlgString(DialogPtr dlog, int item, char *str)	{		short type; Handle hndl; Rect box;		GetDialogItem(dlog,item,&type,&hndl,&box);		if (type == editText) GetDialogItemText(hndl,str);		 else                 *str = 0;		return(*str != 0);	}/* *	Retrieve the value of an edit text item in a given dialog, converting the *	Pascal string to a long and setting *val to it.  Delivers TRUE or FALSE *	according to whether or not the text so delivered was empty.  If FALSE, *	*val is set to 0; if TRUE, *val is set to whatever StringToNum() says the *	value is, even if the text contains non-numerical characters. */static int GetDlgLong(DialogPtr dlog, int item, long *val)	{		int ans; char str[256];		*val = 0;		if (ans = GetDlgString(dlog,item,str))			StringToNum(str,val);		return(ans);		}/* Same as above, only delivers the value of a word */static int GetDlgWord(DialogPtr dlog, int item, short *val)	{		int ans; long num;		*val = 0;		if (ans = GetDlgLong(dlog,item,&num))			*val = num;		return(ans);	}/* *	Deliver the number of the current editText item in given dialog if any text *	is selected in it, or 0 if none selected. */static int TextSelected(DialogPtr dlog)	{		register TEHandle textH; int item = 0;				textH = ((DialogPeek)dlog)->textH;		if (*textH)			if ( (*textH)->selStart != (*textH)->selEnd )				item = ((DialogPeek)dlog)->editField+1;		return(item);	}/* *  If any of the variable argument scrap types are available for pasting from *  the scrap, deliver the first one.  Otherwise, deliver 0.  For example, *	 *      if (whichType = CanPaste(3,'TEXT','PICT','STUF')) ... * *  There can be any number of types in the list, as long as the preceding count, n, *  is correct. */static OSType CanPaste(int n, ...)	{		register OSType nextType,ans = 0L;		long err,offset;		va_list nextArg;				va_start(nextArg,n);		nextType = va_arg(nextArg, OSType);				while (n-- > 0) {			err = GetScrap(NIL, nextType, &offset);			if (err >= -1) {				ans = nextType;				break;				}			nextType = va_arg(nextArg, OSType);			}				va_end(nextArg);		return(ans);	}/* *	Get rectangle, *panel, for a given item (usually a user or picture item) *	and then hide the item so that it doesn't interfere with mouse clicking. *	This lets you stop worrying about the item order any user or pict items that *	obscure other items in the item list, which can affect how the DialogMgr *	returns itemHits. */static void GetDlgPanel(DialogPtr dlog, int item, Rect *panel)	{		short type; Handle hndl;				GetDialogItem(dlog,item,&type,&hndl,panel);		HideDialogItem(dlog,item);	}#endif
#include "BB.Globals_C.h"#include <Devices.h>// les globals 	extern MyQDGlobals QD;	extern AppGlobals G;/* *	Dialog Module, created by Resorcerer		light Modified by Eric Tiquet  */#include <StdArg.h>#include <stdio.h>#define thisDialogID 273/* Symbolic Dialog Item Numbers */extern short gAppResFileNumber;static enum {	CTRL1 = 1,	CTRL2,	CTRL3,	CTRL4,	CTRL5,	CTRL6,	CTRL7,	CTRL8,	CTRL9,	CTRL10,	CTRL11,	CTRL12,	CTRL13,	CTRL14,	CTRL15,	STXT16_F1,	STXT17_F2,	STXT18_F3,	STXT19_F4,	STXT20_F5,	STXT21_F6,	STXT22_F7,	STXT23_F8,	STXT24_F9,	STXT25_F10,	STXT26_F11,	STXT27_F12,	STXT28_F13,	STXT29_F14,	STXT30_F15,	BUT31_OK,	BUT32_Par,	BUT33_Annuler,	USER34,	LASTITEM	};#define OK_ITEM 	BUT31_OK#define CANCEL_ITEM 	33 /* Define this to be item that cancels dialog *//* Useful constants */#ifndef ENTERkey#define ENTERkey	0x3#endif#ifndef DELETEkey#define DELETEkey	0x8#endif#ifndef NIL#define NIL ((void *)0)#endif#ifndef TRUE#define TRUE 1#endif#ifndef FALSE#define FALSE 0#endif#ifndef FRONT_WINDOW#define FRONT_WINDOW  ((WindowPtr) (-1L))#endif/* Prototypes */int					C_ConfigureToucheFonctions(void);static 		DialogPtr OpenThisDialog(void);static void			CloseThisDialog(DialogPtr dlog);static void			DoDialogUpdate(DialogPtr dlog);static void			DoDialogActivate(DialogPtr dlog, int activ);static void			DoDialogContent(DialogPtr dlog, EventRecord *evt);static int			DoDialogItem(DialogPtr dlog, short itemHit);pascal  Boolean MyFilter(DialogPtr dlog, EventRecord *evt, short *itemHit);Boolean CheckUserItems(Point where, short *itemHit);int     AnyBadValues(DialogPtr dlog);static long    strlen(char *);char   *strcpy(char *dst, char *src);char   *PascalToC(char *pstr);char   *CToPascal(char *cstr);void    PutDlgString(DialogPtr dlog, int item, char *str, int sel);void    PutDlgWord(DialogPtr dlog, int item, int val, int sel);void    PutDlgLong(DialogPtr dlog, int item, long val, int sel);void    PutDlgChkRadio(DialogPtr dlog, int item, int val);static int     GetDlgString(DialogPtr dlog, int item, char *str);static int     GetDlgWord(DialogPtr dlog, int item, short *val);static int     GetDlgLong(DialogPtr dlog, int item, long *val);static int     GetDlgChkRadio(DialogPtr dlog, int item);static int     TextSelected(DialogPtr dlog);OSType  CanPaste(int n, ...);void    FrameDefault(DialogPtr dlog, int item, int frame);static void    GetDlgPanel(DialogPtr dlog, int item, Rect *panel);static Point where;static int modifiers;/* *	Display this modal dialog.  Return TRUE if OK, FALSE if CANCEL or error. *	If the dialog displays values from outside this module, you should either *	import them from globals, or change the argument list of this routine to *	bring them in and pass them to OpenThisDialog(), DoDialogItem(), etc. */int C_ConfigureToucheFonctions(void)	{		short itemHit,i,okay,keepGoing=TRUE;		register DialogPtr dlog; GrafPtr oldPort;		Handle hndl; short type; Rect box;		/* Build dialog window and install its item values */				GetPort(&oldPort);		dlog = OpenThisDialog();		if (dlog == NIL) return(FALSE);		/* Entertain filtered user events until dialog is dismissed */				while (keepGoing) {			ModalDialog(MyFilter,&itemHit);			keepGoing = DoDialogItem(dlog,itemHit);			}				/*		 *	Do final processing of item values, such as exporting them to caller.		 *	DoDialogItem() has already called AnyBadValues().		 */				if (okay = (itemHit==OK_ITEM)) {		/* Or whatever is equivalent */						for (i=1;i<16;i++) {				GetDItem(dlog,i,&type,&hndl,&box);				G.TableFonctionKeys[i]=GetControlValue((ControlHandle)hndl);			}									}		/* That's all, folks! */				CloseThisDialog(dlog);		SetPort(oldPort);		SetDAFont(0); 		return(okay);	}/* *	We have to have a filter function, at the very least so that we can outline *	any default button, entertain keyboard editing commands, cmd-period canceling, etc. *	Note that you do not need to have a special user item covering the default button *	in your dialog item list. */static pascal Boolean MyFilter(DialogPtr dlog, EventRecord *evt, short *itemHit)	{		Boolean ans=FALSE,doHilite=FALSE; WindowPtr w,window;		short type,ch,part; Handle hndl; Rect box;		static long then; static Point clickPt;				w = (WindowPtr)(evt->message);		switch(evt->what) {			case updateEvt:				if (w == dlog) {					/* Update our dialog contents */					DoDialogUpdate(dlog);					ans = TRUE; *itemHit = 0;					}				 else {					/*					 *	Call your main event loop DoUpdate(w) routine here if you					 *	don't want unsightly holes in background windows caused					 *	by nested alerts, balloon help, or screen savers (see					 *	Tech Note #304).					 */					DoUpdate(w);					}				break;			case activateEvt:				if (w == dlog) {					DoDialogActivate(dlog,(evt->modifiers & activeFlag)!=0);					*itemHit = 0;					}				 else {					/*					 *	Call your main event loop DoActivate(w) routine here if					 *	you want to deactivate the former frontmost window, in order					 *	to unhighlight any selection, scroll bars, etc.					 */					}				break;			case mouseDown:					where = evt->where;		/* Make info available to DoDialog() */					part = FindWindow(evt->where, &window);				if ( part==inDrag)               /* pass screenBits.bounds to get all gDevices */						if	(window==(WindowPtr)FrontNonFloatingWindow()) {							 DragWindow(window, evt->where,&QD.screenBits.bounds); //&QD.screenbit bounds); //							 ans=true;							*itemHit = 0;						 } 			case mouseUp:				where = evt->where;		/* Make info available to DoDialog() */				GlobalToLocal(&where);				modifiers = evt->modifiers;				ans = CheckUserItems(where,itemHit);				break;			case keyDown:				if ((ch=(unsigned char)evt->message)=='\r' || ch==ENTERkey) {					*itemHit = OK_ITEM /* Default Item Number here */;					doHilite = ans = TRUE;				}				if ((ch=(unsigned char)evt->message)==27 ) {					*itemHit = 2 /* Default Item Number here */;					doHilite = ans = TRUE;				  }				if (evt->modifiers & cmdKey) {					ch = (unsigned char)evt->message;					switch(ch) {						case 'x':						case 'X':							if (TextSelected(dlog))								{ SystemEdit(3); ZeroScrap(); DlgCut(dlog); TEToScrap(); }							 else {								/* Cut from anything else cuttable, like a list */								}							break;						case 'c':						case 'C':							if (TextSelected(dlog))								{ SystemEdit(3); ZeroScrap(); DlgCopy(dlog); TEToScrap(); }							 else {								/* Copy from anything else copyable, like a list */								}							break;						case 'v':						case 'V':							if (CanPaste(1,'TEXT'))								{ TEFromScrap(); DlgPaste(dlog); }							 else {							 	/* Deal with any other pasteable scraps here */								}							break;						case 'a':						case 'A':							if (((DialogPeek)dlog)->editField >= 0) {								/* Dialog has text edit item: select all */								SelIText(dlog,((DialogPeek)dlog)->editField+1,0,32767);								}							 else {								}							*itemHit = 0;							break;						case '.':							*itemHit = CANCEL_ITEM;							doHilite = TRUE;							break;						}					ans = TRUE;		/* Other cmd-chars ignored */					}				break;			}		if (doHilite) {			GetDItem(dlog,*itemHit,&type,&hndl,&box);			/* Reality check */			if (type == (btnCtrl+ctrlItem)) {				long soon = TickCount() + 7;		/* Or whatever feels right */				HiliteControl((ControlHandle)hndl,1);				while (TickCount() < soon) ;		/* Leave hilited for a bit */				}			}		return(ans);	}/* * Mouse down event: * Check if it's in some user item, and convert to itemHit if appropriate. */static Boolean CheckUserItems(Point where, short *itemHit)	{		return(FALSE);	}/* * Redraw the contents of this dialog due to update event. * If you have not installed UserItem draw routines, you should redraw * them explicitly here; otherwise, UpdtDialog() will call your routines. */static void DoDialogUpdate(DialogPtr dlog){short type,IconId,i; Handle hndl; Rect box;Str255 str; PixPatHandle	the_pixpat;RgnHandle		r1=NewRgn(),r2=NewRgn();Handle						LaListeH;DitlelementPtr			LaListe;Ditl_MasterlistPtr	LaListe1;				SetPort(dlog);		TextMode(srcOr);		BeginUpdate(dlog);		if (!EmptyRgn(dlog->visRgn)){			 RectRgn(r1,&dlog->portRect);			 			 GetDItem(dlog,34,&type,&hndl,&box);			 RectRgn(r2,&box);			 DiffRgn(r1,r2,r1);			 					 the_pixpat=GetPixPat(129);			  			  if (the_pixpat!=nil){			 	 FillCRgn(r1,the_pixpat);			 	 DisposePixPat(the_pixpat);			  }			  			  TextMode(srcOr);			  			 		LaListeH=((DialogPeek)dlog)->items;		HLock(LaListeH);		LaListe=(DitlelementPtr)*LaListeH;		LaListe1=(Ditl_MasterlistPtr)*LaListeH;					 for (i=1;i<=(LaListe1->dml_NumberOfItem+1);i++) {				 GetDItem(dlog,i,&type,&hndl,&box);				 if ((type&0x7f) == iconItem ) {					 IconId=C_findIconResourceDitl(dlog,i);					 hndl=(Handle)GetCIcon(IconId);					 PlotCIcon(&box,(CIconHandle) hndl);					 }				 				if ( ((type&0x7f) == statText )  && i!=3) {					 GetIText(hndl,&str);					 MoveTo(box.left,box.bottom);					 DrawString(&str);				 }				 			 }			  			 			 		} // vis region empty ?					GetDItem(dlog,34,&type,&hndl,&box);		FrameRectOneLine(&box,true);					DrawControls(dlog);		FrameDefault(dlog,OK_ITEM,true);					EndUpdate(dlog);		DisposeRgn(r1);		DisposeRgn(r2);}/* * Activate event: Activate or deactivate this dialog and any items in it */static void DoDialogActivate(DialogPtr dlog, int activ)	{		SetPort(dlog);	}/* * Build this dialog's window on desktop, and install initial item values. * Return the dlog opened, or NIL if error (no resource, no memory). */static DialogPtr OpenThisDialog()	{		short type,i; Handle hndl; Rect box; GrafPtr oldPort;		DialogPtr dlog; unsigned char *p,str[256];		GetPort(&oldPort);		SetDAFont(geneva); 		dlog = GetNewDialog(thisDialogID,NIL,FRONT_WINDOW);		if (dlog == NIL) { SysBeep(1); return(NIL); }	/* Poor man's error message */		SetPort(dlog);				TextFont(geneva); 		TextSize(9);				/* Fill in dialog's values here */		for (i=1;i<16;i++) {			GetDItem(dlog,i,&type,&hndl,&box);			SetControlValue((ControlHandle)hndl,(short)G.TableFonctionKeys[i]);			}		ShowWindow(dlog);		return(dlog);	}/* * Clean up any allocated stuff, and return dialog to primordial mists */static void CloseThisDialog(DialogPtr dlog)	{		DisposDialog(dlog);	/* Call CloseDialog if you provide storage to GetNewDialog */	}/* * Deal with user clicking on an item in this dialog, either modal or non-modal. * The local point is in where; modifiers in modifiers. * Returns whether or not the dialog should be closed (keepGoing). */static int DoDialogItem(DialogPtr dlog, short itemHit)	{		short type,i,okay=FALSE,saveResFileNumber,keepGoing=TRUE,val;		Handle hndl,pref; Rect box; Point pt;		unsigned char *p,str[256];		unsigned char table[32];		if (itemHit<1 || itemHit>=LASTITEM)			return(keepGoing);				/* Only legal items, please */		GetDItem(dlog,itemHit,&type,&hndl,&box);		switch(type) {			case ctrlItem+btnCtrl:				switch(itemHit) {					case BUT31_OK:						keepGoing = FALSE; okay = TRUE;						break;											case BUT32_Par: // valeur par d�fauts					// on regarde la pr�f�rence dans le logiciel						saveResFileNumber=CurResFile();						UseResFile(gAppResFileNumber);						pref=Get1Resource('FreP',129);						if (pref){ // si elle existe on la lit et on la place dans les pop-ups							HLock(pref);							BlockMove(*pref,&table,18);							HUnlock(pref);							ReleaseResource(pref);														for (i=1;i<16;i++) {								GetDItem(dlog,i,&type,&hndl,&box);								SetControlValue((ControlHandle)hndl,table[i]);							}						}						UseResFile(saveResFileNumber);						break;											case BUT33_Annuler:							keepGoing = FALSE; okay = false;						break;					}				break;			case ctrlItem+chkCtrl:				break;			case ctrlItem+radCtrl:				break;			case ctrlItem+resCtrl:				switch(itemHit) {					case CTRL1:						break;					case CTRL2:						break;					case CTRL3:						break;					case CTRL4:						break;					case CTRL5:						break;					case CTRL6:						break;					case CTRL7:						break;					case CTRL8:						break;					case CTRL9:						break;					case CTRL10:						break;					case CTRL11:						break;					case CTRL12:						break;					case CTRL13:						break;					case CTRL14:						break;					case CTRL15:						break;					}				break;			case statText:				switch(itemHit) {					case STXT16_F1:		/* NOT Enabled */						break;					case STXT17_F2:		/* NOT Enabled */						break;					case STXT18_F3:		/* NOT Enabled */						break;					case STXT19_F4:		/* NOT Enabled */						break;					case STXT20_F5:		/* NOT Enabled */						break;					case STXT21_F6:		/* NOT Enabled */						break;					case STXT22_F7:						break;					case STXT23_F8:		/* NOT Enabled */						break;					case STXT24_F9:		/* NOT Enabled */						break;					case STXT25_F10:		/* NOT Enabled */						break;					case STXT26_F11:		/* NOT Enabled */						break;					case STXT27_F12:		/* NOT Enabled */						break;					case STXT28_F13:		/* NOT Enabled */						break;					case STXT29_F14:		/* NOT Enabled */						break;					case STXT30_F15:		/* NOT Enabled */						break;					}				break;			case editText:				break;			case iconItem:				break;			case picItem:				break;			case userItem:				switch(itemHit) {					case USER34:						break;					}				break;			}		if (okay) keepGoing = AnyBadValues(dlog);		return(keepGoing);	}/* * Pull values out of dialog items and deliver TRUE if any of them are * illegal or inconsistent; otherwise deliver FALSE.  If any values are bad, * you should inform your user about the problem here before delivering TRUE. * If any items are missing values, this is the place to assign any defaults. */static int AnyBadValues(DialogPtr dlog)	{		char str[256]; short val,len;		return(FALSE);	}/*��������������������������������������������������������������������������������������*//* *  The following are various utility routines for general dialog management. *  Typically, you'll want to keep them in a library that is available to all *  your dialog modules; however, they are included here (and declared static) *  as a private library so that you can quickly compile this file for testing. */#define _PrivateLibraries_#ifdef  _PrivateLibraries_/* Local C string length routine */static long strlen(register char *str)	{		register char *p;		p = str;		while (*p++) ;		return((long)(--p - str));	}/* Convert in place a Pascal string to C string, and deliver its address */static char *PascalToC(char *str)	{		register char *p,*q,*end;		end = str + *(unsigned char *)str;		q = (p=str) + 1;		while (p < end) *p++ = *q++;		*p = '\0';		return(str);	}/* *	Convert in place a C string to Pascal string, and deliver its address. *	The C string should not be greater than 255 chars in length, or the *	resulting Pascal string will be truncated to 255 chars. */static char *CToPascal(char *str)	{		register char *p,*q;		register long len;		len = strlen(str);		if (len > 255) len = 255;		p = str + len;		q = p-1;		while (p != str) *p-- = *q--;		*str = len;		return(str);	}/* Dialog Item Stuffers *//* *	Install a given Pascal string, str, into the given static or edit text item *	in the dialog, dlog.  If the item is an edit text item, leave the installed *	text selected or not according to the value of sel (TRUE or FALSE). */static void PutDlgString(DialogPtr dlog, int item, char *str, int sel)	{		short type; Handle hndl; Rect box;		GetDItem(dlog,item,&type,&hndl,&box);		SetIText(hndl,str);		if (type == editText)			SelIText(dlog,item,sel?0:32767,32767);		InvalRect(&box);	}/* *	Install a given decimal long value into the static or edit text item of the *	given dialog, dlog.  If the item is an edit text item, leave the installed *	text for the number selected or not according to sel (TRUE or FALSE). */static void PutDlgLong(DialogPtr dlog, int item, long val, int sel)	{		char str[32];		NumToString(val,str);		PutDlgString(dlog,item,str,sel);	}/* *	Same as above, only for an int (word) decimal number. */static void PutDlgWord(DialogPtr dlog, int item, int val, int sel)	{		PutDlgLong(dlog,item,(long)val,sel);	}/* *	Set the given check box or radio button item of the given dialog, dlog, to *	on or off, according to val. */static void PutDlgChkRadio(DialogPtr dlog, int item, int val)	{		short type; Handle hndl; Rect box;		GetDItem(dlog,item,&type,&hndl,&box);		SetCtlValue((ControlHandle)hndl,val!=0);	}/* *	Deliver the value of the checkbox or radio button item of the given dialog. */static int GetDlgChkRadio(DialogPtr dlog, int item)	{		short type; Handle hndl; Rect box;				GetDItem(dlog,item,&type,&hndl,&box);		return(GetCtlValue((ControlHandle)hndl) != 0);	}/* Dialog Item Unstuffers *//* *	Retrieve the value of an edit text item in a given dialog, placing the *	resulting Pascal string in the buffer, str, which is assumed large enough *	to hold the text (256 bytes max).  If item is the number of a static text *	item, the empty string is delivered.  Delivers TRUE or FALSE according to *	whether or not the text so delivered was empty.   */static int GetDlgString(DialogPtr dlog, int item, char *str)	{		short type; Handle hndl; Rect box;		GetDItem(dlog,item,&type,&hndl,&box);		if (type == editText) GetIText(hndl,str);		 else                 *str = 0;		return(*str != 0);	}/* *	Retrieve the value of an edit text item in a given dialog, converting the *	Pascal string to a long and setting *val to it.  Delivers TRUE or FALSE *	according to whether or not the text so delivered was empty.  If FALSE, *	*val is set to 0; if TRUE, *val is set to whatever StringToNum() says the *	value is, even if the text contains non-numerical characters. */static int GetDlgLong(DialogPtr dlog, int item, long *val)	{		int ans; char str[256];		*val = 0;		if (ans = GetDlgString(dlog,item,str))			StringToNum(str,val);		return(ans);		}/* Same as above, only delivers the value of a word */static int GetDlgWord(DialogPtr dlog, int item, short *val)	{		int ans; long num;		*val = 0;		if (ans = GetDlgLong(dlog,item,&num))			*val = num;		return(ans);	}/* *	Deliver the number of the current editText item in given dialog if any text *	is selected in it, or 0 if none selected. */static int TextSelected(DialogPtr dlog)	{		register TEHandle textH; int item = 0;				textH = ((DialogPeek)dlog)->textH;		if (*textH)			if ( (*textH)->selStart != (*textH)->selEnd )				item = ((DialogPeek)dlog)->editField+1;		return(item);	}/* *  If any of the variable argument scrap types are available for pasting from *  the scrap, deliver the first one.  Otherwise, deliver 0.  For example, *	 *      if (whichType = CanPaste(3,'TEXT','PICT','STUF')) ... * *  There can be any number of types in the list, as long as the preceding count, n, *  is correct. */static OSType CanPaste(int n, ...)	{		register OSType nextType,ans = 0L;		long err,offset;		va_list nextArg;				va_start(nextArg,n);		nextType = va_arg(nextArg, OSType);				while (n-- > 0) {			err = GetScrap(NIL, nextType, &offset);			if (err >= -1) {				ans = nextType;				break;				}			nextType = va_arg(nextArg, OSType);			}				va_end(nextArg);		return(ans);	}/* *	Get rectangle, *panel, for a given item (usually a user or picture item) *	and then hide the item so that it doesn't interfere with mouse clicking. *	This lets you stop worrying about the item order any user or pict items that *	obscure other items in the item list, which can affect how the DialogMgr *	returns itemHits. */static void GetDlgPanel(DialogPtr dlog, int item, Rect *panel)	{		short type; Handle hndl;				GetDItem(dlog,item,&type,&hndl,panel);		HideDItem(dlog,item);	}#endif
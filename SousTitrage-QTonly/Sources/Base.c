#include "BB.Globals_C.h"#include <Devices.h>// les globalsextern MyQDGlobals QD;extern AppGlobals G;extern WindowPtr 	gPaletteKaraoke;extern Boolean			gMaskingSousTitre;extern short gAntiAlias;	extern void VBL_STARTCODE(void);extern void SERIAL(void);//#pragma segment FonctionsDeBaseListelong labs(long val);short abs(short val);pascal void UpdateGeneralValue(void);pascal void 	EcritPreferenceTravail(void);pascal void	CloseErrorWindow(DialogPtr dlog);pascal void 	UpdateTheErrorList(DialogPtr dlog);pascal void 	QuitMoniteurVideo();pascal void QuitSansFauteGrammaire(void);void DoDisposeAV(void);pascal void ManageUndoRedoListeForInsert(long AbsNum);pascal void ManageUndoRedoListeForDelete(long AbsNum);static long  gStartSecond;pascal long TestSiDansST(SousTitreRecordPtr ST_Ptr:__A0,unsigned long TC:__D0):__D0;pascal void C_FaitOffset(SousTitreRecordPtr start, SousTitreRecordPtr end	, long offset);Boolean  AskUserDelete(SousTitreRecordPtr  ST_Ptr ,DialogPtr dlog);void EndAskfDelete( DialogPtr dlog);short DoAskifDeleteST(DialogPtr dlog,Point pt) ;DialogPtr StartConfirmDialogST(short DialogId);void adjustPtToBeVisible(Point  *pt);pascal void UpdateErrorWindow(void);void RemplacePartout(long start,long end);pascal void RPDispose(Handle theRpd);pascal Boolean RPIdle(Handle theRpd,long value,pascal void(*UpdateFct)(WindowPtr window),Boolean Multifinder);void  C_TransfertStyleTE_Memoire(TEHandle te,SousTitreRecordPtr ST_Ptr);pascal Boolean myStandartfilterproc(DialogPtr theDialog ,EventRecord *event,short *itemhit);pascal Boolean RPIsFrontProcess(Handle theRpd);void  CopieTexte(SousTitreRecordPtr source,SousTitreRecordPtr destination);void SauvegardeAutomatique_Idle(short type);void FermeLEsTE(void);void DochangeStylFontSurZone( long DebutZone,long FinZone,short flag, short style, short fontid);void DochangeJustifSurZone( long DebutZone,long FinZone,short justif);short QT_UpdateQTCaption(long AbsStNum);pascal void  PageSetup(void){THPrint	hPrint;Boolean	result;		PrOpen();		hPrint=(THPrint)NewHandleClear(sizeof(TPrint));		PrintDefault(hPrint); 		result=PrStlDialog(hPrint);/*l'utilisateur a valider la configuration,	on recopie le nouveau THPrint dans les parram�tres g�n�raux */		DisposeHandle((Handle)hPrint);		PrClose();}	pascal void C_PrepositionneTCInterne(void){DialogPtr		dialog;Boolean			outboucle;Str255			st0;short			itemhit,itemType;Handle			item;Rect				box;unsigned long		l,m;DateTimeRec date;					dialog=GetNewDialog(161,nil,(WindowPtr)-1);					SetPort(dialog);										BeginUpdate(dialog);					DrawDialog(dialog);					EndUpdate(dialog);					GetDialogItem(dialog,1,&itemType,&item,&box);					InsetRect(&box,-4,-4);					PenSize(3,3);					FrameRoundRect(&box,16,16);					PenNormal();					C_ConversionTCstASCII(G.General_PseudoTimeCode,&st0);					GetDialogItem(dialog,3,&itemType,&item,&box);					SetDialogItemText(item,&st0);					 SelectDialogItemText(dialog,3,0,32766);					do {						ModalDialog((ModalFilterProcPtr) &Special_C_ModalDialogFilter,&itemhit);						if (itemhit ==1 ){								GetDialogItem(dialog,3,&itemType,&item,&box);								GetDialogItemText(item,&st0);								G.General_PseudoTimeCode=C_ConversionChaineASCIITc(&st0);								outboucle=true;								}												if (itemhit ==2 )outboucle=true;												if (itemhit ==4 ){								outboucle=true;								l=LMGetTime();								SecondsToDate(l+1,&date);																m=(((long)date.hour/10)<<28);								m+= ( ((long)date.hour-((long)date.hour/10)*10  ) <<24 ) ;								m+= (((long)date.minute/10)<<20);								m+= ( ( (long)date.minute-((long)date.minute/10)*10 )<<16) ;								m+= (((long)date.second/10)<<12);								m+= ( ( (long)date.second-((long)date.second/10)*10  )<<8);																								// on synchronise l'horloge								while (l==LMGetTime()) ;								G.General_PseudoTimeCode=m;															}					}while (outboucle!=true );										DisposeDialog(dialog);					}void DrawThePopUp(DialogPtr dialog,short item,short menuID,short menuItem,MenuHandle MH ){RGBColor		color,bcolor;MCEntryPtr	mcPtr;Handle			handle;Rect 			rect;short			itemtype,a;Str255			string;		GetDialogItem(dialog,item,&itemtype,&handle,&rect);		color.red=0;		color.green=0;		color.blue=0;		bcolor.red=-1;		bcolor.green=-1;		bcolor.blue=-1;		// on r�cup�re la couleur du fond du menu		mcPtr= GetMCEntry(menuID,menuItem);		if (mcPtr) {			if (mcPtr->mctID==0 && mcPtr->mctItem==0){					color=mcPtr->mctRGB2;					RGBForeColor(&bcolor);					color=mcPtr->mctRGB3;					RGBForeColor(&color);			}						if (mcPtr->mctID!=0 && mcPtr->mctItem==0){					color=mcPtr->mctRGB4;					RGBForeColor(&bcolor);					color=mcPtr->mctRGB3;					RGBForeColor(&color);			}						if (mcPtr->mctID!=0 && mcPtr->mctItem!=0){					color=mcPtr->mctRGB4;					RGBForeColor(&bcolor);					color=mcPtr->mctRGB2;					RGBForeColor(&color);			}					} // if (mcPtr)			rect.left+=14;			EraseRect(&rect);// on recup�re la chaine de caract�re �quivalente � la valeur stock�e		GetMenuItemText(MH,menuItem,&string); 		TextMode(srcOr);// actif ou non ?		if (itemtype&0x80) PenPat(&QD.gray);		MoveTo(rect.left,rect.top+12);		DrawString(&string);				//on rend la couleur noire pour le dessin du reste du popUp		color.red=0;		color.green=0;		color.blue=0;		RGBForeColor(&color);		rect.left-=14;// on dessine le triangle en fin de texte		a=rect.bottom-rect.top-8;		MoveTo(rect.right-6,rect.top+3);		PenSize(2,2);		Line(-a*2,0);		Line(a,a);		Line(a,-a);		// on dessine le rectangle autour du texte				PenSize(1,1);		FrameRect(&rect);				MoveTo(rect.left+1,rect.bottom);		LineTo(rect.right,rect.bottom);		LineTo(rect.right,rect.top+1);		PenNormal();}/* Cette routine retourne le N� d'item de la police d�sign�e par le fontid dans le menu police	on trouve ce n� par le  G.PopUp_FontNumberList*/short GiveFontItemNumber(short fontID){SPtr	P;short val,count,result=0,itemnum=1;			HLock((Handle)G.PopUp_FontNumberList);	P=(SPtr)*G.PopUp_FontNumberList;	count=*P;	do {		P++;		val=*P;			if (val==fontID)				result=itemnum;		itemnum++;			if (itemnum>(count+1))  result=kFontIDGeneva;	} while ( result==0  );	HUnlock((Handle)G.PopUp_FontNumberList);	return result;}///* Cette routine retourne le N� d'item de la police d�sign�e par le fontid dans le menu police	on trouve ce n� par le  G.PopUp_FontNumberList*/short GiveFontID(short fontItemNumber){SPtr	P;short result=0;			HLock((Handle)G.PopUp_FontNumberList);	P=(SPtr)*G.PopUp_FontNumberList;	P=P+fontItemNumber;	result=*P;						HUnlock((Handle)G.PopUp_FontNumberList);	return result;}//						pascal void C_FaitOffset(SousTitreRecordPtr start, SousTitreRecordPtr end	, long offset){SousTitreRecordPtr ST_Ptr;long	tc;	ST_Ptr=start;	do {		C_SpinCursor(32);		if (ST_Ptr->st_TimeCodeIn!=-1) {			tc=C_AdditionTimeCode(ST_Ptr->st_TimeCodeIn,offset);			ST_Ptr->st_TimeCodeIn=tc;		}		if (ST_Ptr->st_TimeCodeOut!=-1) {			tc=C_AdditionTimeCode(ST_Ptr->st_TimeCodeOut,offset);			ST_Ptr->st_TimeCodeOut=tc;		}	ST_Ptr=(SousTitreRecordPtr)ST_Ptr->st_NextST;	} while (ST_Ptr<=end && ST_Ptr!=nil);		SetCursor(&QD.arrow);	UpdateGeneralValue();	UpdateSaisie();				DrawListingWindow();			}					pascal void  C_RenumerotationListeSousTitre(SousTitreRecordPtr ST_Ptr){long Numero;	if (ST_Ptr==G.General_DernierSTPtr) return;// si premier sous-titre on s'assure que c'est bien le n�1	if (ST_Ptr==G.General_PremierSTPtr){			ST_Ptr->st_NumeroST=1;			ST_Ptr->st_OldNumeroST=1;			Numero=1;	}		Numero=ST_Ptr->st_NumeroST&0x00ffffff;	do{		C_SpinCursor(32);		ST_Ptr->st_OldNumeroST=ST_Ptr->st_NumeroST;		ST_Ptr->st_NumeroST=Numero;		Numero++;		ST_Ptr=(SousTitreRecordPtr)ST_Ptr->st_NextST;	}while( (ST_Ptr!=nil)  && (ST_Ptr<=G.General_DernierSTPtr) && (ST_Ptr>=G.General_PremierSTPtr)  );	SetCursor(&QD.arrow);}unsigned long C_CHERCHESTPARnumero(char* string){Str255 			Principal,Secondaire;short 			i,j;Boolean 			outboucle,flag;unsigned char 		c;long				a,b,d,e,f;SousTitreRecordPtr 	ST_Ptr;unsigned long 		resultat;	Principal[0]=0;	Secondaire[0]=0;	resultat=1;	outboucle=false;				/* on s�pare le num�ro principal du num�ro secondaire */		i=1;	j=1;	flag=false;		do{		c=string[i];		if ( c>='0' && c<='9') {				if   (!flag) {					 Principal[j]=c;					 Principal[0]=j; 					 }				else  if (flag)  { 					Secondaire[j]=c;					Secondaire[0]=j; 					}				j++;			} 						if (c==',' || c=='-') { flag=true; j=1;}		i++;					} while (i<=string[0] &&outboucle==false) ;/* on recherche le n� principal */	a=b=0;	StringToNum(&Principal,&a);	if (Secondaire[0]) StringToNum(&Secondaire,&b);/* on recherche dans la liste le st avec le n� pr�par� */	ST_Ptr=G.General_PremierSTPtr;	outboucle=false;	resultat=ST_Ptr->st_AbsNUMST;	f=a+(b<<24);		do{		d=ST_Ptr->st_NumeroST;		e=d&0xff000000; 				// on regarde si le n� de st est �quivalent		if (d==f) {			outboucle=true; //oui on sort			resultat=ST_Ptr->st_AbsNUMST;			}		// non on regarde si l'on est a dessus		if ((d&0x00ffffff)>a) outboucle=true;		if (e && b) { // num�ro secondaire			e=(e>>24);			if (e>b) outboucle=true;			}					if (! outboucle) resultat=ST_Ptr->st_AbsNUMST;				ST_Ptr=(SousTitreRecordPtr) ST_Ptr->st_NextST;			} while(ST_Ptr && ST_Ptr<=G.General_DernierSTPtr && outboucle==false);		return resultat;}void DoEffaceGroupSousTitre(short condition,long start,long end,short askUser);							void DoEffaceGroupSousTitre(short condition,long start,long end,short askUser){SousTitreRecordPtr ST_Ptr,ST_Ptr1;Str255			st0,st1,st2;short		Doefface,result;long i,total;DialogPtr			dlog=nil;	total=end-start;		if(askUser)		dlog=StartConfirmDialogST(182);	else {		ST_Ptr=C_ConversionNumeroSTPointeur((long)start);		ST_Ptr1=C_ConversionNumeroSTPointeur((long)end);		C_ConvertiNumST_String(ST_Ptr->st_NumeroST,&st0);		C_ConvertiNumST_String(ST_Ptr1->st_NumeroST,&st1);		GetIndString(&st2,129,42+condition);		ParamText(&st0,&st1,&st2,nil);		result=Alert(280,(ModalFilterProcPtr)myStandartfilterproc);		if (result==2) return;	}			i=0;	do{		ST_Ptr=C_ConversionNumeroSTPointeur(start+i);		Doefface=0;		Doefface=false;		switch(condition){			case 0:				Doefface=2;			break;					case 1:				if( ST_Ptr->st_TexteLenth==0) Doefface=2;			break;							case 2:				if( (ST_Ptr->st_TimeCodeIn==-1) &&  (ST_Ptr->st_TimeCodeOut==-1) )Doefface=2;			break;						case 3:				if( 	(ST_Ptr->st_TimeCodeIn==-1) &&					(ST_Ptr->st_TimeCodeOut==-1) &&					( ST_Ptr->st_TexteLenth==0) )	Doefface=2;			break;		} // condition		if (Doefface && dlog  && askUser)			Doefface=AskUserDelete(ST_Ptr,dlog);		if (Doefface==1) { 		if(dlog) DisposeDialog(dlog); 		return; 		}	if (Doefface==2) {			C_DeleteST(ST_Ptr); // on efface			total--; i--;		}			i++;	} while( i<= total);		QT_UpdateQTCaption(start); // on actualise la liste		if(dlog)		DisposeDialog(dlog);	// on update les fen�tre	UpdateSaisie();	DrawListingWindow();}// cette routine demande s'il fzut effacer le st (ST_Ptr) en pla�ant une petite fen�tre � cot� du sous-titreBoolean  AskUserDelete(SousTitreRecordPtr  ST_Ptr,DialogPtr	dlog ){long 		stnum,max,value;Point		pt;	stnum=ST_Ptr->st_AbsNUMST;	TransfertSaisieMemoire();// On centre listing	if (G.ListingTE) {		SetPort((WindowPtr)&G.ListingWindow);		TransfertTE_Memoire(G.ListingTE,G.ListingTEStNum,G.ListingTEStItem);		TEDispose(G.ListingTE);		G.ListingTE=nil;		InvalRect((Rect*)&((GrafPtr)&G.ListingWindow)->portRect);	}		G.General_SousTitreEncour=stnum;	UpdateSaisie();	// on regarde si le sous-titre est visible	max=GetControlMaximum(G.ListingVScroll);	value=stnum-G.ListingMaxDisplay/2+1;	if (value<1) value=1;	if (value<(G.ListingMaxDisplay-1)) value=1;	if (value>(max-(G.ListingMaxDisplay/2)) ) value=max-(G.ListingMaxDisplay/2);	SetControlValue(G.ListingVScroll,value);	DrawListingWindow();	SetPort((WindowPtr)&G.ListingWindow);			pt.v= (stnum-value)*G.HauteurST-12;	pt.h=14+ajout_largeur_ST_Listing+417;	if (pt.v<5) pt.v=5;	LocalToGlobal(&pt);	adjustPtToBeVisible(&pt);		return  DoAskifDeleteST(dlog,pt);	}void adjustPtToBeVisible(Point  *pt){GDHandle			gdh;GDHandle			NextDevice=NULL;PixMapHandle		pmh;Point				point=*pt;Rect				rect;Boolean 			visible=false;	NextDevice =GetDeviceList();	do{		// regarde si offscreendevice ?		if ((TestDeviceAttribute(NextDevice,screenDevice) == 0)||			(TestDeviceAttribute(NextDevice,screenActive) == 0)) {} 		else {		// un vrai ecran		rect=(**NextDevice).gdRect;			// on recup�re les informations sur la carte			visible=visible| (PtInRect(*pt,&rect) );	 	}// reel device		NextDevice =GetNextDevice(NextDevice);	 } while (NextDevice);	 	 NextDevice =GetMainDevice();	rect=(**NextDevice).gdRect;	if (!visible) (*pt).h=rect.right-50;} // adjustPtToBeVisible/* Cette routine v�rifie la liste de sous-titre par rapport au valeur par d�faut */void VerifListWithDefaultValue(void){PrefVerifListeHandle PrefVerif;DialogPtr	D=G.ErrorsWindow;GrafPtr	oldport;		GetPort(&oldport);		PrefVerif=nil;		PrefVerif=(PrefVerifListeHandle)NewHandleClear(sizeof(PrefVerifListe));		(**PrefVerif).Preference_CoherenceTimeCode=true;		(**PrefVerif).Preference_RespectIntervalMinimum=true;		(**PrefVerif).Preference_RespectLisibilite=true;		(**PrefVerif).Preference_TolerenceLisibilite=60;		(**PrefVerif).Preference_RespectNombreCaractereLigne=true;		(**PrefVerif).Preference_NombreCaractereLigne=32;		(**PrefVerif).Preference_RespectNombreLigne=true;		(**PrefVerif).Preference_NombreLigne=3;		(**PrefVerif).Preference_DecalageVerticale=false;					if (PrefVerif) {				UpdateGeneralValue();				G.Sous_titre_dessined=nil;				G.General_DernierNumConvertiPtr=nil;				G.Sous_titreInOffscreen=nil;									ShowReferencedWindow((WindowReference)G.ErrorsWindow);				SelectReferencedWindow((WindowReference)G.ErrorsWindow);				SetPort(D);				UpdateErrorWindow();				VerifieLaListe(G.General_PremierSTPtr,G.General_DernierSTPtr,PrefVerif);				InvalRect(&D->portRect);				DisposeHandle((Handle)PrefVerif);				SetCursor(&QD.arrow);				}						SetPort(oldport);}void ChercheRemplaceTexte(short flag){SousTitreRecordPtr ST_Ptr;short			whattodo;long 				num;DialogPtr			dlog=nil;Boolean			reboucle=false,found,done=false,trouvequelquechose=false;EventRecord		event;// on prepare le dialog de confirmation	if (flag)  dlog=StartConfirmDialogST(271);	else 	      dlog=StartConfirmDialogST(272);		if (!dlog) { SysBeep(1);    return; }/* on initi	alise la recherche */	G.Rechercher_StartOffset=0; 	// position du premier caract�re trouv�	G.Rechercher_EndOffset=0; 		//position du dernier caract�re trouv�	G.Rechercher_InCommentaire=0; 	//flags pour indiquer si la chaine a �t� trouver dans un commentaire	G.Rechercher_STNum=G.Rechercher_DebutZone; 			//num�ro du dernier sous titre trouve	num=G.Rechercher_DebutZone;	do{		C_SpinCursor(32);		ST_Ptr=C_ConversionNumeroSTPointeur(num);		// on recherche le texte		found=ChercheTexte(ST_Ptr);				if (!found) {			G.Rechercher_EndOffset=0;			G.Rechercher_StartOffset=0;			num++;		} else {		// on a trouv� on place listing � la bonne place		// on demande son avis � l'utilisateur			G.Rechercher_STNum=num;			SetCursor(&QD.arrow);			trouvequelquechose=true;			whattodo=AskUserChoiceRechercheRemplace(num,dlog);						switch(whattodo){				case 0:	// continuer recherche				break;								case 1: 	// annuler					done=true;				break;								case 2:	// remplacer					RemplaceTexte(G.ListingTE);					// on place le resultat dans le sous-titre					C_TransfertStyleTE_Memoire(G.ListingTE,ST_Ptr);				break;								case 4:	// tout remplacer					if(dlog) DisposeDialog(dlog);					dlog=nil;					RemplacePartout(num,G.Rechercher_FinZone);					done=true;				break;									}		}				// on d�termine s'il faut sortir de la boucle			if (G.Rechercher_RevenirDebut  && (!reboucle) )			if (num> G.Rechercher_FinZone) {				num=1; 	// on revient au d�but du fichier				reboucle=true;			}					if (reboucle) {				if (num>G.Rechercher_DebutZone)					done=true;		} else 	{					if (num>G.Rechercher_FinZone)					done=true;			}				// on regarde s'il faut arr�ter la recherche		if (EventAvail (8, &event) ) {				if ( ( (event.message&0xff)=='.') && 					(event.modifiers&cmdKey) ) done=true;				}	} while( !done);	if (!trouvequelquechose) SysBeep(1);	SetCursor(&QD.arrow);	// on ferme si ouvert le te dans listing	if(dlog) DisposeDialog(dlog);		if (G.ListingTE)  {		SetPort((WindowPtr)&G.ListingWindow);		TransfertTE_Memoire(G.ListingTE,G.ListingTEStNum,G.ListingTEStItem);		TEDispose(G.ListingTE);		G.ListingTE=nil;	}		// on update les fen�tre	UpdateSaisie();	DrawListingWindow();}/* CEtte routine demande son choix � l'utilisateur:	 annuler , continuer recherche, remplacer, tout remplacer */	 short AskUserChoiceRechercheRemplace(long stnum,DialogPtr dlog){short max,value;Point		pt,pt1;SousTitreRecordPtr ST_Ptr;	/* on ouvre la fen�tre listing*/	ShowReferencedWindow((WindowReference)&G.ListingWindow);	TransfertSaisieMemoire();	G.General_SousTitreEncour=G.Rechercher_STNum;	UpdateSaisie();// on ferme le te  en cours s'il y en a un	if (G.ListingTE)  {		SetPort((WindowPtr)&G.ListingWindow);		TransfertTE_Memoire(G.ListingTE,G.ListingTEStNum,G.ListingTEStItem);		TEDispose(G.ListingTE);		G.ListingTE=nil;	}// On centre listing sur le sous-titre	max=GetControlMaximum(G.ListingVScroll);	value=stnum-G.ListingMaxDisplay/2+1;	if (value<1) value=1;	if (value<(G.ListingMaxDisplay-1)) value=1;	if (value>(max-(G.ListingMaxDisplay/2)) ) value=max-(G.ListingMaxDisplay/2);	SetControlValue(G.ListingVScroll,value);	DrawListingWindow();	SetPort((WindowPtr)&G.ListingWindow);		// on ouvre le te		// on d�termine le sous-titre et ses coordon�es	ST_Ptr=C_ConversionNumeroSTPointeur((long)value);// on calcule les coordonn�es de la case listing	pt1.h=156;	pt1.v=(stnum-value)*G.HauteurST+20+7; //7 pix sion on tape dans le commentaire	OpenTheTEListing(pt1);		if (G.ListingTE){		TESetSelect(G.Rechercher_StartOffset,G.Rechercher_EndOffset,G.ListingTE);		}		// on place la petite fen�tre de confirmation	pt.v= (stnum-value)*G.HauteurST-12;	pt.h=14+ajout_largeur_ST_Listing+417;	if (pt.v<5) pt.v=5;	LocalToGlobal(&pt);	adjustPtToBeVisible(&pt);	return DoAskifDeleteST(dlog,pt);		DrawListingWindow();	}/* Cette routine permet de rechercher une chaine de caract�res dans la liste de sous-titre*/Boolean ChercheTexte(SousTitreRecordPtr ST_Ptr){Handle	h=nil;Ptr		P;short	script,anErr;Str255	st0;// on fait une copie de la cha�ne de recherche	BlockMove(&G.Rechercher_STR[0],&st0[0],256); 		anErr = PtrToHand((Ptr)ST_Ptr+sizeof(SousTitreRecord),&h, ST_Ptr->st_TexteLenth);	if (anErr) return false;	HLock(h);	// on effectue la conversion lower->upper case	if (!G.Rechercher_Majuscule) {		UppercaseText(&st0[1],st0[0], FontScript());		UppercaseText(*h, ST_Ptr->st_TexteLenth, FontScript());	}	// on effectuela recherche du texte	G.Rechercher_StartOffset = Munger(h, G.Rechercher_EndOffset, &st0[1], (long) st0[0], nil, 0);	G.Rechercher_EndOffset=G.Rechercher_StartOffset+(long)st0[0];	HUnlock(h);	DisposeHandle(h);		if (G.Rechercher_StartOffset<0) 	return false ;	else return true;}/* Cette routine remplace la s�lection courante par la cha�ne remplacer*/void RemplaceTexte(TEHandle te){		if (te) {			TEDelete(te);	// on efface la s�lection			TEInsert(&G.Remplacer_STR[1], G.Remplacer_STR[0],te); // on remplace le texte			G.ChangeSinceLastSave=true;  //on indique qu'il y a eu modif			}}/* Cette routine remplace toute les occurences de la cha�ne recherche 	par la cha�ne remplace, dans l'interval d�fini */void RemplacePartout(long start,long end){short	result,visBlockNote;Str255	st0,st1;SousTitreRecordPtr	ST_Ptr,ST_Ptr1,ST_Ptr2;	TEHandle	te;Rect		rect;Boolean	trouvequelquechose=false,found=false,done=false;Handle	progression;long		num;	//on force la sauvegarde au cas o�	if (G.ChangeSinceLastSave&0x7fff) { 		C_SaveData(true);		}			//on masque la fen�tre block note		visBlockNote=( (WindowRecord*)(G.BlockNoteWindow) )->visible;	( (WindowRecord*)(G.BlockNoteWindow) )->visible=nil;	// on ferme le te ouvert	FermeLEsTE(); // la methode rapide & sure		/* l'ancienne methode		if (G.ListingTE) {		SetPort((WindowPtr)&G.ListingWindow);		TransfertTE_Memoire(G.ListingTE,G.ListingTEStNum,G.ListingTEStItem);		TEDispose(G.ListingTE);		G.ListingTE=nil;		InvalRect((Rect*)&((GrafPtr)&G.ListingWindow)->portRect);	}*/		// on update saisie		ST_Ptr1=C_ConversionNumeroSTPointeur((long)start);	ST_Ptr2=C_ConversionNumeroSTPointeur((long)end);	C_ConvertiNumST_String(ST_Ptr1->st_NumeroST,&st0);	C_ConvertiNumST_String(ST_Ptr2->st_NumeroST,&st1);	ParamText(&G.Rechercher_STR,&G.Remplacer_STR,&st0,&st1);	result=Alert(274,(ModalFilterProcPtr)myStandartfilterproc);	if (result==2) return;			GetIndString(&st0,129,36);		GetIndString(&st1,129,37);						progression=RPInitReglette(&st0,&st1,G.Rechercher_DebutZone,G.Rechercher_FinZone,true);	/* on effectue un boucle de changement */		// on demande un te pour faire les modifications	SetRect(&rect,0,100,0,100); //mis ces valeur la, sinon risque de plantage	te=TEStyleNew(&rect,&rect);	if (!te) return;			num=start;	// on initialise la recherche	G.Rechercher_EndOffset=0;	G.Rechercher_StartOffset=0;		do{		ST_Ptr=C_ConversionNumeroSTPointeur(num);				if ( RPIsFrontProcess(progression) ) C_SpinCursor(32);		// on recherche le texte		found=ChercheTexte(ST_Ptr);				if (!found) {			G.Rechercher_EndOffset=0;			G.Rechercher_StartOffset=0;			num++;		} else {		// on a trouv� on place listing � la bonne place		// on demmande son avis � l'utilisateur			G.Rechercher_STNum=num;			// on place le contenu dans le te			TRANSFERTTEXTE_MEMOIRE_STYLETE(te,ST_Ptr,&rect,-1);			// on remplace la s�lection			TESetSelect(G.Rechercher_StartOffset,G.Rechercher_EndOffset,te);			RemplaceTexte(te);			// on place le resultat dans le sous-titre			C_TransfertStyleTE_Memoire(te,ST_Ptr);			}						if (num>G.Rechercher_FinZone)	done=true;				// on regarde s'il faut arr�ter le remplacement		done=done|RPIdle(progression,num,&DoUpdate,true);	} while( !done);		if (!trouvequelquechose) SysBeep(1);	SetCursor(&QD.arrow);				TEDispose(te);	if (progression) RPDispose(progression);	UpdateSaisie();	DrawListingWindow();	( (WindowRecord*)(G.BlockNoteWindow) )->visible=visBlockNote;}//--- Cette routine permet de changer la s�lection en cours en majusculevoid ChangeSelectionEnCoursMajuscule(TEHandle te){Handle aCharsH;	if (!te) return;	if ( (**te).selEnd-(**te).selStart){		aCharsH =(**te).hText; 		HLock(aCharsH);		UppercaseText(*aCharsH+(**te).selStart, (**te).selEnd-(**te).selStart, FontScript());		HUnlock(aCharsH);		TEUpdate(&(**te).viewRect,te);		G.ChangeSinceLastSave=true;  //on indique qu'il y a eu modif	}}//--- CEtte routine permet de changer la s�lection en cours en minusculevoid ChangeSelectionEnCoursMinuscule(TEHandle te){Handle aCharsH;	if (!te) return;	if ( (**te).selEnd-(**te).selStart){		aCharsH =(**te).hText;		HLock(aCharsH);		LowercaseText(*aCharsH+(**te).selStart, (**te).selEnd-(**te).selStart, FontScript());		HUnlock(aCharsH);		TEUpdate(&(**te).viewRect,te);		G.ChangeSinceLastSave=true;  //on indique qu'il y a eu modif	}}DecaleTexte(long start,long end,short versbas);DecaleTexte(long start,long end,short versbas){short	result,visBlockNote;Str255	st0,st1,st2;SousTitreRecordPtr	ST_Ptr,ST_Ptr1,ST_Ptr2;	TEHandle	te;Rect		rect;Boolean	trouvequelquechose=false,found=false,done=false;Handle	progression;long		num;		// on ferme le te ouvert	visBlockNote=( (WindowRecord*)(G.BlockNoteWindow) )->visible;	( (WindowRecord*)(G.BlockNoteWindow) )->visible=nil;	if (G.ListingTE) {		SetPort((WindowPtr)&G.ListingWindow);		TransfertTE_Memoire(G.ListingTE,G.ListingTEStNum,G.ListingTEStItem);		TEDispose(G.ListingTE);		G.ListingTE=nil;		InvalRect((Rect*)&((GrafPtr)&G.ListingWindow)->portRect);	}	TransfertSaisieMemoire();	// on demande confirmation du d�calage		ST_Ptr1=C_ConversionNumeroSTPointeur((long)start);	ST_Ptr2=C_ConversionNumeroSTPointeur((long)end);	C_ConvertiNumST_String(ST_Ptr1->st_NumeroST,&st0);	C_ConvertiNumST_String(ST_Ptr2->st_NumeroST,&st1);	if (versbas)		GetIndString(&st2,129,39);	else 	GetIndString(&st2,129,38);		ParamText(&st2,&st0,&st1,nil);	result=Alert(276,(ModalFilterProcPtr)myStandartfilterproc);	if (result==2) return nil;//	on v�rifie que l'on ne va pas effacer un texte lors du d�calage	if (versbas) 	ST_Ptr2=(SousTitreRecordPtr)ST_Ptr2->st_NextST;	else 			ST_Ptr2=(SousTitreRecordPtr)ST_Ptr1->st_PreviousST;			if (ST_Ptr2){	 	if (ST_Ptr2->st_TexteLenth){ 			// on indique que le texte va �tre effac�			C_ConvertiNumST_String(ST_Ptr2->st_NumeroST,&st0);			ParamText(&st0,nil,nil,nil);			result=Alert(277,(ModalFilterProcPtr)myStandartfilterproc);			if (result==2) return nil;		}	}// maintenant on effectue la boucle de d�calage, on ouvre un incateur de progression	GetIndString(&st0,129,36);		GetIndString(&st1,129,40);	progression=RPInitReglette(&st0,&st1,start,end,true);	if (!versbas){ // vers le haut de la liste (le 1er st)		num=start;		do{			ST_Ptr=C_ConversionNumeroSTPointeur((long)num);		 	ST_Ptr1=(SousTitreRecordPtr)ST_Ptr->st_PreviousST;		 			 	if(!ST_Ptr1) {		 		Insert_Before(); // si le sous-titre pr�c�dent n'existe pas on le cr�er		 		num=2; // on actualise le num st et les pointeurs		 		ST_Ptr=C_ConversionNumeroSTPointeur((long)num);		 		ST_Ptr1=(SousTitreRecordPtr)ST_Ptr->st_PreviousST;		 	}		 			 	// on d�cale les textes		 	CopieTexte(ST_Ptr,ST_Ptr1);		 			 				 			 				 	ST_Ptr=C_ConversionNumeroSTPointeur((long)num);		 	ST_Ptr1=(SousTitreRecordPtr)ST_Ptr->st_PreviousST;		 			 	// on efface le texte du sous-titre d�cal�			ST_Ptr->st_StylePtr=nil;			ST_Ptr->st_StyleLenth=nil;			ST_Ptr->st_TexteLenth=nil;						// on indique que les texte ont �t� d�cal�s			ST_Ptr1->st_Error=ST_Ptr1->st_Error|(1<<14);			ST_Ptr->st_Error=ST_Ptr->st_Error|(1<<14);		 	// on fait rotation du curseur		 	if ( RPIsFrontProcess(progression) ) C_SpinCursor(32);	// on regarde s'il faut arr�ter le d�calage				num++;			if (num>end) done=true;			done=done|RPIdle(progression,num,&DoUpdate,true);		} while(!done);	}	if (versbas){ // vers le bas VERS LE DERNIER DE LA LISTE		num=end;		do{			ST_Ptr=C_ConversionNumeroSTPointeur((long)num);			ST_Ptr1=(SousTitreRecordPtr)ST_Ptr->st_NextST;		 	if(!ST_Ptr1) C_InsertSt(ST_Ptr,32); // si le sous-titre suivant n'existe pas on le cr�er		 			 	// on d�cale les textes		 	CopieTexte(ST_Ptr,ST_Ptr1);		 			 	ST_Ptr=C_ConversionNumeroSTPointeur((long)num);		 	ST_Ptr1=(SousTitreRecordPtr)ST_Ptr->st_PreviousST;		 	// on efface le texte du sous-titre d�cal�			ST_Ptr->st_StylePtr=nil;			ST_Ptr->st_StyleLenth=nil;			ST_Ptr->st_TexteLenth=nil;						// on indique que les texte ont �t� d�cal�s			ST_Ptr1->st_Error=ST_Ptr1->st_Error|(1<<14);			ST_Ptr->st_Error=ST_Ptr->st_Error|(1<<14);								 	if ( RPIsFrontProcess(progression) ) C_SpinCursor(32);			// on regarde s'il faut arr�ter le d�calage				num--;			if (num<start) done=true;			done=done|RPIdle(progression,end-num,&DoUpdate,true);		} while(!done);	}	SetCursor(&QD.arrow);	if (progression) RPDispose(progression);		// on update les fen�tre		UpdateSaisie();		DrawListingWindow();				return nil;}void  CopieTexte(SousTitreRecordPtr  source,SousTitreRecordPtr destination){long		nLigne,i;Ptr		P;Handle	commentaire;StScrpHandle	stScrap;unsigned long L,destinationNum,sourceNum;// on prot�ge la routine			if (source>G.General_DernierSTPtr || source<G.General_PremierSTPtr)  return;			if (destination>G.General_DernierSTPtr || destination<G.General_PremierSTPtr)  return;						// on garde les absnumst			destinationNum=destination->st_AbsNUMST;			sourceNum=source->st_AbsNUMST;//on sauvegarde la chaine de commentaire du sous-titre de destination			commentaire=nil;			if (destination->st_CommentaireLenth){				PtrToHand(destination->st_CommentairePtr,&commentaire,destination->st_CommentaireLenth);			}			/* on �carte maintemant le sous-titre pour que tout rentre	on calcule la longueur de la zone m�moire n�cessaire */						L=((source->st_TexteLenth+3)/4)*4; 	   			// longueur du texte ajust� sur mot long 			L+=((source->st_StyleLenth+3)/4)*4; 			// longueur du style ajust� sur mot long 			L+=((destination->st_CommentaireLenth+3)/4)*4;	// longueur du commentaire ajust� sur mot long 			L+=16;								// en marge de s�curite			C_EcarteSousTitre(destination,L);						// on recalcule les pointeurs car ils ont pu �tre modifi� par "Ecarte sous-titre"			source=C_ConversionNumeroSTPointeur((long)sourceNum);			destination=C_ConversionNumeroSTPointeur((long)destinationNum);// on raz les pointeurs			destination->st_StylePtr=nil;			destination->st_StyleLenth=source->st_StyleLenth;			destination->st_TexteLenth=source->st_TexteLenth;// on recopie le texte dans le st			if (source->st_TexteLenth){				BlockMove(	(Ptr)source+sizeof(SousTitreRecord),							(Ptr)destination+sizeof(SousTitreRecord),							source->st_TexteLenth);			}			// on recopie les style dans le sous-titre				if(source->st_StyleLenth && source->st_StylePtr) {				// on calcule le pointeur du style				L=(long)destination+sizeof(SousTitreRecord);				L+=destination->st_TexteLenth;				L=((L+3)/4)*4;				destination->st_StylePtr=(Ptr)L;				BlockMove(source->st_StylePtr,(Ptr)L,source->st_StyleLenth);			}// on remet la cha�ne de commentaire s'il elle existe			if (commentaire){				HLock(commentaire);				// on calcule le pointeur du commentaire				L=(long)destination+sizeof(SousTitreRecord);				L+=destination->st_TexteLenth;				L=((L+3)/4)*4;				L+=destination->st_StyleLenth;				L=((L+3)/4)*4;				destination->st_CommentairePtr=(Ptr)L;				BlockMove(*commentaire,(Ptr)L,destination->st_CommentaireLenth);				DisposeHandle(commentaire);			}		G.ChangeSinceLastSave=true;  //on indique qu'il y a eu modif}void DochangeStylFontSurZone( long DebutZone,long FinZone,short flag, short style, short fontid){short	result,visBlockNote;Str255	st0,st1;SousTitreRecordPtr	ST_Ptr,ST_Ptr1,ST_Ptr2;	TEHandle	te;Rect		rect;Boolean		done=false;Handle		progression;long		num;TextStyle 	stylenew;	//on force la sauvegarde au cas o�	if (G.ChangeSinceLastSave&0x7fff) { 		C_SaveData(true);		}			//on masque la fen�tre block note ???	/*	visBlockNote=( (WindowRecord*)(G.BlockNoteWindow) )->visible;	( (WindowRecord*)(G.BlockNoteWindow) )->visible=nil;*/	// on ferme le ou les te ouvert	FermeLEsTE(); // la methode rapide & sure	GetIndString(&st0,129,36);		GetIndString(&st1,129,56);		progression=RPInitReglette(&st0,&st1,DebutZone,FinZone,true);	stylenew.tsFont=fontid;	stylenew.tsFace=style;	/* on effectue un boucle de changement */	// on demande un te pour faire les modifications	SetRect(&rect,0,100,0,100); //mis ces valeur la, sinon risque de plantage	te=TEStyleNew(&rect,&rect);	if (!te) return;			num=DebutZone;	// on initialise la recherche	do{		ST_Ptr=C_ConversionNumeroSTPointeur(num);		if ( RPIsFrontProcess(progression) ) C_SpinCursor(32);		TRANSFERTTEXTE_MEMOIRE_STYLETE(te,ST_Ptr,&rect,-1);		// on remplace la s�lection		TESetSelect(0,32767,te);		TESetStyle (flag,&stylenew,false,te);		// on place le resultat dans le sous-titre		C_TransfertStyleTE_Memoire(te,ST_Ptr);		num++;		if (num>FinZone)	done=true;		// on regarde s'il faut arr�ter le remplacement			done=done|RPIdle(progression,num,&DoUpdate,true);	} while( !done);	SetCursor(&QD.arrow);		TEDispose(te);	if (progression) RPDispose(progression);	UpdateSaisie();	DrawListingWindow();	//( (WindowRecord*)(G.BlockNoteWindow) )->visible=visBlockNote;}// cette routine change la justification de sous-titre sur une zonevoid DochangeJustifSurZone( long DebutZone,long FinZone,short justif){short	result,visBlockNote;Str255	st0,st1;SousTitreRecordPtr	ST_Ptr,ST_Ptr1,ST_Ptr2;	TEHandle	te;Rect		rect;Boolean		done=false;Handle		progression;long		num;TextStyle 	stylenew;	//on force la sauvegarde au cas o�	if (G.ChangeSinceLastSave&0x7fff) { 		C_SaveData(true);		}			// on ferme le ou les te ouvert	FermeLEsTE(); // la methode rapide & sure	GetIndString(&st0,129,36);		GetIndString(&st1,129,59);		progression=RPInitReglette(&st0,&st1,DebutZone,FinZone,true);	num=DebutZone;	// on initialise la recherche	do{		if ( RPIsFrontProcess(progression) ) C_SpinCursor(32);		ST_Ptr=C_ConversionNumeroSTPointeur(num);		ST_Ptr->st_Justification=justif;		num++;		if (num>FinZone)	done=true;		// on regarde s'il faut arr�ter le remplacement			done=done|RPIdle(progression,num,&DoUpdate,true);	} while( !done);	SetCursor(&QD.arrow);		if (progression) RPDispose(progression);	UpdateSaisie();	DrawListingWindow();}long labs(long val){	if (val<0) val=-val;	return val;	}short abs(short val){	if (val<0) val=-val;	return val;}void FermeLEsTE(void){long L;	if (G.saisieTE) {		TransfertSaisieMemoire();	}			if (G.ListingTE){		L=G.ListingTEStNum;		TransfertTE_Memoire(G.ListingTE,G.ListingTEStNum,G.ListingTEStItem);		TEDispose(G.ListingTE);		G.ListingTE=nil;		InvalRect((Rect*)&((GrafPtr)&G.ListingWindow)->portRect);				/*  on raz le processeur d'affichage */		if (G.Sous_titre_dessined->st_AbsNUMST==L) {			G.Sous_titre_dessined=nil	;			}				if (G.Sous_titreInOffscreen->st_AbsNUMST==L) {			G.Sous_titreInOffscreen=nil	;			}		}}//FermeLEsTE//permet de deeterminer si un te est ouvertshort IsTeOpen();short IsTeOpen(){short result =false;		if (G.ListingTE)				result=true;				if (G.saisieTE)				result=true;				if (G.BlockNoteTE)				result=true;						return 		result;				}
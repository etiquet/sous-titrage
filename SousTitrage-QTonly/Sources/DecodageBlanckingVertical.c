#include "BB.Globals_C.h"// les globalsextern AppGlobals 	G;extern WindowPtr 	gMonitor;extern GWorldPtr 	gAvOffscreen;extern GDHandle 	gAVDevice;extern Boolean		gDone,gRefreshInfoW,doTrackingInListing,doTrackingOutListing,doTrackingInSaisie,doTrackingOutSaisie;;extern GWorldPtr			gMonitorOffscreen,gMonitorOffscreenFinal;extern DialogPtr			gBlankingVerticalWindow,gtestDecodageWindow;extern unsigned long		gVitcLuParAV;extern	Ptr	 gDecodeBlanckingVerticalBuffer;short	gResultatlectureBlancking,gResultatlectureBlancking;Boolean	gNouveauMessage,gDecodeBlanckingVertical;extern short	gcomp,gcomp1,gcomp2,gdelaybit,gValeurFiltrage;short	gcomp3,gLastNumSTDecode;long	glastCheckSum,gCheckSum;long FiltreTimeCode(long tc,long tcdefault);extern Ptr	gDecodageVerticalST,gBufferEmissionBlancking;long gTCIn,gTCOut;void Affichage_SousTitreDecodeVISTC(void);void DrawFenetreDecodageBlancking(void);void FenetreDecodageBlanckingIdle(void);static OSErr TransitionNoirBlanc(char** P);static OSErr TransitionBlancNoir(char** P);static OSErr litUneligneInformation(char** VramPtr,char** Buffer);static OSErr LitUnOctet(char** VramPtr,char** Buffer);void 		LitCodageVertical(void);void	PlaceNouveauMessageDansSousTitre(SousTitreRecordPtr ST_Ptr,VISTCPtr Vistc_ST);void LitCodageVertical(void){unsigned long i,j,x,y,TC,a,rowb,b;Point		startVitc;Ptr			P,P1,P2,P3,base;GrafPtr 	oldPort;short 		type,itemHit;Boolean		found=false;unsigned char c;unsigned short d[32];PixMapHandle	PM;EventRecord	event;OSErr		err;Handle		hndl;Rect		box;long L;Str255		st0;// l'adresse de la zone m�moire de l'image	i=0xe0200800+768*4;	P=(Ptr)i;		// on recherche le premier point blanc, � partir de la ligne 1	y=0;	do{		x=0;		P1=P;		do{								c=*(P1)+*(P1+2);				if (c>gcomp) { 									startVitc.v=y;									startVitc.h=x;									found=true;									P2=P1;							   }		P1+=2;	// 16 bits			x++;		}while(x<30 &&(!found)); 		y++;		P+=768*2;	} while (!found && (y<40));	G.General_TCCourant=G.General_PseudoTimeCode;	if (!found) { 		gResultatlectureBlancking=0;		return; }	// on a le d�but du vitc // coordonn�e startVitc// adresse P2	// on a le droit � 10 lignes de  12 octets dont 10 utiles (120 chars - 16)	P=gDecodeBlanckingVerticalBuffer;	for (y=0;y<24;y++){		P3=P2;		err=litUneligneInformation(&P3,&P);		P2+=768*2; // la ligne suivante	} 	if (err==noErr){			// on calcule le checksum du buffer		P=gDecodeBlanckingVerticalBuffer+8;		L=0;		for (i=8;i<224;i++){			L+=*(P);			P++;		}					gCheckSum=(*(VISTCPtr)gDecodeBlanckingVerticalBuffer).Checksum;		// on compare les checks-sum		if (L==gCheckSum){				// gestion du tc courant		// on assume si check sum correcte => tous est lu correctement		// y compris le time-code		// si le tc d�cod� courant est diff�rent de la derni�re valeur		// on update le compteur interne					if ( (gVitcLuParAV) !=( (*(VISTCPtr)gDecodeBlanckingVerticalBuffer).TcCourant) ){				// on est d�cal� d'une image // au time code r�el				// on compense d'une image				gVitcLuParAV=C_AdditionTimeCode( (*(VISTCPtr)gDecodeBlanckingVerticalBuffer).TcCourant,1);				G.General_PseudoTimeCode=gVitcLuParAV;			} 						// on regarde si le num�ro de st est diff�rent on recopie le block et on indique 			// que nous avon re�u un nouveau sous-titre						if (gLastNumSTDecode !=  (*(VISTCPtr)gDecodeBlanckingVerticalBuffer).NumST) {				//on recopie le buffer dans le prochain sous-titre				gLastNumSTDecode=(*(VISTCPtr)gDecodeBlanckingVerticalBuffer).NumST;				BlockMove(gDecodeBlanckingVerticalBuffer,gDecodageVerticalST,2048);				gNouveauMessage=true;				}							glastCheckSum=L;			gResultatlectureBlancking=10;// reception OK		} else {			gResultatlectureBlancking=-10; // probl�me reception		}	}}							OSErr litUneligneInformation(char** VramPtr,char** Buffer){OSErr err;	short	i;		// on attend le caract�re "noir"	(*VramPtr)+=6*3; // au milieu de l'octet blanc	err=TransitionBlancNoir(VramPtr); 	if (err) return err;		(*VramPtr)+=6*4; // au milieu de l'octect noir	// on attend le petit blanc � la fin du caract�re "noir"	err=TransitionNoirBlanc(VramPtr); 	if (err) return err;				// maintenant on lit 10 caract�res	for(i=0;i<11;i++){		err=LitUnOctet(VramPtr,Buffer);		if (err) return err;	}		return nil;}OSErr LitUnOctet(char** VramPtr,char** Buffer){unsigned char c,a;long	d[8];short	i;	(*VramPtr)+=14; // au milieu du premier pixel	for (i=0;i<8;i++){		d[i]= *(*VramPtr)+*(*VramPtr+2); // moyenne sur 2 pixels		(*VramPtr)+=12;	}		// on calcule la valeur de l'octet	c=0;	for (i=0;i<8;i++){		c=c<<1;			if (d[7-i]>0x70 ) a=1; else a=0;		c=c|a;	}	**Buffer=c; // on place la valeur dans le buffer	(*Buffer)++;		// on attend le prochain syncbit	(*VramPtr)-=4; // on revient un petit peu en arri�re	return TransitionNoirBlanc(VramPtr); }		//-----------static OSErr TransitionNoirBlanc(char** P){short	Count=0;		unsigned char c;		do{		(*P)+=2;		c=*(*P);		Count++;	}while (Count<=200 && c<0x20);	if (Count>=200) return -1;	return 0;}static OSErr TransitionBlancNoir(char** P){short	Count=0;		unsigned char c;		do{		(*P)+=2;		c=*(*P);		Count++;	}while (Count<=200 && c>0x30);	if (Count>=200) return -1;	return 0;}// ----------------	void DrawFenetreDecodageBlancking(void){GrafPtr	oldport;RGBColor	color;PixPatHandle the_pixpat;DialogPtr 	D=gtestDecodageWindow;Handle	itemH;short	type;Rect		rect;RgnHandle rgn,rgn1;		GetPort(&oldport);	SetPort( gtestDecodageWindow);	TextMode(srcCopy);	TextFont(kFontIDGeneva);	TextFace(0);	TextSize(9);		the_pixpat=GetPixPat(129);	color.red=0; color.green= 0; color.blue=0;	RGBForeColor(&color);			if (  (the_pixpat!=nil) && (GiveMinDepth(&D->portRect)>1)  ) {		// on calcule la rgn pour la pattern			rgn=NewRgn();			rgn1=NewRgn();			RectRgn(rgn,&D->portRect);			GetDialogItem(D,4,&type,&itemH,&rect);			EraseRect(&rect);			InsetRect(&rect,-1,-1);			RectRgn(rgn1,&rect);			DiffRgn(rgn,rgn1,rgn);						GetDialogItem(D,15,&type,&itemH,&rect);			EraseRect(&rect);			InsetRect(&rect,-1,-1);			RectRgn(rgn1,&rect);			DiffRgn(rgn,rgn1,rgn);									GetDialogItem(D,17,&type,&itemH,&rect);			EraseRect(&rect);			InsetRect(&rect,-1,-1);			RectRgn(rgn1,&rect);			DiffRgn(rgn,rgn1,rgn);									FillCRgn(rgn,the_pixpat);			DisposeRgn(rgn);			DisposeRgn(rgn1);									InsetRect(&rect,1,1);			} else { // si pas de pixpat ou Ecran n&B  on efface seulement						EraseRect(&D->portRect); // si pas de pixpat on efface seulement			PenNormal();		}		if (the_pixpat) 	DisposePixPat(the_pixpat);				GetDialogItem(D,4,&type,&itemH,&rect);	InsetRect(&rect,-2,-2);	FrameRectTwoLine(&rect,true);	GetDialogItem(D,15,&type,&itemH,&rect);	InsetRect(&rect,-2,-2);	FrameRectTwoLine(&rect,true);	GetDialogItem(D,17,&type,&itemH,&rect);	InsetRect(&rect,-2,-2);	FrameRectTwoLine(&rect,true);	GetDialogItem(D,12,&type,&itemH,&rect);	InsetRect(&rect,-1,-1);	FrameRectOneLine(&rect,true);	GetDialogItem(D,13,&type,&itemH,&rect);	InsetRect(&rect,-1,-1);	FrameRectOneLine(&rect,true);			color.red=0;	color.blue=0;	color.green=24000;		RGBForeColor(&color); // lettre vertes			Draw_Icon_Text_Ditl(D);		gNouveauMessage=true;	FenetreDecodageBlanckingIdle();		SetPort(oldport);}void FenetreDecodageBlanckingIdle(void){GrafPtr	oldport;RGBColor	color;Ptr		P;short	type,i;Handle	hndl;Rect	box,nulrect;Str255	st0;TEHandle	te;	TextStyle			newStyle;		GetPort(&oldport);	SetPort( gtestDecodageWindow);	TextMode(srcCopy);	TextFont(kFontIDGeneva);	TextFace(0);	TextSize(9);		color.red=0;	color.blue=0;	color.green=24000;		RGBForeColor(&color); // lettre vertes			if (gNouveauMessage) {		// le tc in		C_ConversionTCstASCII( (*(VISTCPtr)gDecodageVerticalST).TcIn,&st0);		GetDialogItem(gtestDecodageWindow,2,&type,&hndl,&box);		MoveTo(box.left,box.top+9);		DrawString(&st0);		// le tc out						C_ConversionTCstASCII( (*(VISTCPtr)gDecodageVerticalST).TcOut,&st0);		GetDialogItem(gtestDecodageWindow,3,&type,&hndl,&box);		MoveTo(box.left,box.top+9);		DrawString(&st0);			// le n� de sous-titre			NumToString(gLastNumSTDecode,&st0);		GetDialogItem(gtestDecodageWindow,19,&type,&hndl,&box);		EraseRect(&box);		MoveTo(box.left,box.top+9);		DrawString(&st0);		// on affiche le texte		GetDialogItem(gtestDecodageWindow,4,&type,&hndl,&box);		/*on dessine le texte � l'aide d'un te */				InsetRect(&box,1,1);		SetRect(&nulrect,0,0,0,0);		te=TEStyleNew(&nulrect,&nulrect);			// la justification du sous-titre				TESetAlignment(C_get_STJustification(G.General_PremierSTPtr),te);			// on y place le texte		TRANSFERTTEXTE_MEMOIRE_STYLETE(te,G.General_PremierSTPtr,&box,-1);	// on place un peu de couleur et on fixe la taille � 9		TESetSelect(0,32767,te);				newStyle.tsSize=9;		newStyle.tsFont=kFontIDGeneva;		newStyle.tsColor.blue=28000;		newStyle.tsColor.green=0;		newStyle.tsColor.red=0;		TESetStyle(doSize+doColor,&newStyle,false,te);				(**te).destRect=box;		(**te).viewRect=box;				TECalText(te);		EraseRect(&box);		TEUpdate(&box,te);	//on place le curseur � la fin du texte				TEDispose(te);		gNouveauMessage=false; // on raz l'indicateur	} 		color.red=0;	color.blue=0;	color.green=24000;		RGBForeColor(&color); // lettre vertes		 {	//tc courant		C_ConversionTCstASCII((*(VISTCPtr)gDecodeBlanckingVerticalBuffer).TcCourant ,&st0);		GetDialogItem(gtestDecodageWindow,1,&type,&hndl,&box);		MoveTo(box.left,box.top+9);		DrawString(&st0);			// checksum lu		NumToString(gCheckSum,&st0);		GetDialogItem(gtestDecodageWindow,6,&type,&hndl,&box);		TETextBox(&st0[1],st0[0],&box,teJustLeft);		// checksum calcul�		NumToString(glastCheckSum,&st0);		GetDialogItem(gtestDecodageWindow,5,&type,&hndl,&box);		TETextBox(&st0[1],st0[0],&box,teJustLeft);				// on affiche les erreurs de lectures		// indicateur rouge		GetDialogItem(gtestDecodageWindow,13,&type,&hndl,&box);		if (gResultatlectureBlancking==-10){			color.red=-1; color.blue=0; color.green=0;		} else {			color.red=18000; color.blue=0; color.green=0;		}		RGBForeColor(&color);		PaintRect(&box);				// indicateur vert		GetDialogItem(gtestDecodageWindow,12,&type,&hndl,&box);		if (gResultatlectureBlancking==10){			color.red=0; color.blue=0; color.green=-1;		} else {			color.red=0; color.blue=0; color.green=18000;		}		RGBForeColor(&color);		PaintRect(&box);			}		SetPort(oldport);}// cette routine g�re l'affichage du sous-titre d�cod� par VISTCvoid 	Affichage_SousTitreDecodeVISTC(void){long 				TC,a;SousTitreRecordPtr 	ST_Ptr;Ptr				P,P1,P2,P3,base;PixMapHandle	PM;Rect			rect;OSErr			result;long			rowb,i,j;		// si nouveau message on dessine dans le buffer offscreen		ST_Ptr=(SousTitreRecordPtr)G.General_PremierSTPtr;		TC=G.General_TCCourant;		if (gNouveauMessage){			PlaceNouveauMessageDansSousTitre(ST_Ptr,(VISTCPtr)gDecodageVerticalST);			DessineAVST(ST_Ptr,true);				//gNouveauMessage=false;						// on place le prochain tcin a attendre			gTCIn=ST_Ptr->st_TimeCodeIn;						// on v�rifie la coh�rence du time-code out						if (gTCOut>=gTCIn) {				gTCOut=ST_Ptr->st_TimeCodeOut;				EffaceFenetreSimulation();				G.DrawState=0;				}		}// on regarde o� nous en sommes		G.General_SousTitreCourantPtr=0;		G.General_SousTitrecourant=0;		// on affiche seulement si la fen�tre simulation est ouverte		if( !((WindowPeek)gMonitor)->visible) return;		// on agit en fonction du time-code				if (TC>=gTCIn){	// nous entrons dans le tc in			if(G.DrawState&0x0f) return; // rien � faire il a d�j� �t� affich�			transfertAVOffscreenInScreen();			G.DrawState=1;			gTCOut=ST_Ptr->st_TimeCodeOut; // le  prochain tc out � attendre		}		if (TC>=gTCOut){			if(G.DrawState&0x0f){	// on sort d'un sous-titre				EffaceFenetreSimulation();			}				G.DrawState=0;	 		}}//void PlaceNouveauMessageDansSousTitre(SousTitreRecordPtr ST_Ptr,VISTCPtr Vistc_ST){Ptr	P,P1,P2;long L,L1,L2;short	i,a;	ST_Ptr->st_NextST=nil;	// pas de sous-titre suivant	ST_Ptr->st_PreviousST=nil;// pas de sous-titre devant	ST_Ptr->st_CommentairePtr=nil;	ST_Ptr->st_CommentaireLenth=0; // pas de commentaire	ST_Ptr->st_Error=0;	ST_Ptr->st_PosOffsetTable=nil;	// nu pour l'instant ""KARAOKE"" momentan�ement	ST_Ptr->st_spare[0]=0;	ST_Ptr->st_spare[1]=0;	ST_Ptr->st_spare[2]=0;	ST_Ptr->st_spare[3]=0;	ST_Ptr->st_spare[4]=0;	ST_Ptr->st_spare[5]=0;	// ----------------------------------------------// on place les valeurs d�tect�e/* le n� de sous-titre */	ST_Ptr->st_AbsNUMST=Vistc_ST->NumST; 	// sous-titre n� 1	ST_Ptr->st_NumeroST=Vistc_ST->NumST;			ST_Ptr->st_OldNumeroST=Vistc_ST->NumST;/* time-code*/	ST_Ptr->st_TimeCodeIn=Vistc_ST->TcIn;	ST_Ptr->st_TimeCodeOut=Vistc_ST->TcOut;/* position verticale */	ST_Ptr->st_XOffset=Vistc_ST->Xpos; 	ST_Ptr->st_YOffset=Vistc_ST->Ypos; /*mask, justification*/	a=Vistc_ST->Flags;	ST_Ptr->st_Justification=a&0x03; 		//justification du texte 0 centr�e,1 gauche, 2 droite 	a=a>>2;	ST_Ptr->st_MasKType=a&0x03; 			//type de mask box, line, rectangle; = rien	/* le texte */	L=Vistc_ST->TexteLenth&0xffff; // longueur du texte	if (L>128) L=128; // on sait que sup 128 pas possible		ST_Ptr->st_TexteLenth=L;	P=(Ptr) ST_Ptr+sizeof(SousTitreRecord);	P1=(Ptr) Vistc_ST+sizeof(VISTC); // adresse du premier octets de data	BlockMove(P1,P,ST_Ptr->st_TexteLenth);	P1+=L; // pointeur des styles d�cod�s		// on calcule le nombre de ligne	P2=P;	ST_Ptr->st_Nlines=1;		for (i=0;i<L;i++){		if (*P==0x0d) ST_Ptr->st_Nlines++;		P++;	}	/* on place les styles */	ST_Ptr->st_StyleLenth=Vistc_ST->StyleLenth&0xffff;	if (ST_Ptr->st_StyleLenth>128) ST_Ptr->st_StyleLenth=0; // il y a s�rement erreur		ST_Ptr->st_StylePtr=nil;	if (ST_Ptr->st_StyleLenth){		// on calcule le pointeur des styles		L1=(long)P;		L1+=L;		L1=((L1+3)/4)*4;		ST_Ptr->st_StylePtr=(Ptr)L1;		// on recopie les styles		BlockMove(P1,ST_Ptr->st_StylePtr,ST_Ptr->st_StyleLenth);				// on calcule la longueur du sous-titre		L=((L+3)/4)*4;		L+=ST_Ptr->st_StyleLenth;	}		L=((L+3)/4)*4; // ajustement sur mots long	ST_Ptr->st_LenthST=L+16;}
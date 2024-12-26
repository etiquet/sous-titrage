pascal void ReadBonBougreFormat(ParamBlkPtr pb,char *name,long filelenth){ReadBonBougreFormat	 	PROC	EXPORT			; any source file can use this routineStackFrame	RECORD	{A6Link},DECR		; build a stack frame recordParamBegin	EQU	*			; start parameters after this pointParamblock			ds.l	1	; adresse du block de param�trereply				ds.l	1FileLenth			ds.l	1	; longueur du fichier luParamSize	EQU	ParamBegin-*	; size of all the passed parametersRetAddr 			DS.L	1	; place holder for return addressA6Link				DS.L	1	; place holder for A6 linkBuffer				ds.l	1	; adresse du bufferMaxBuffer			ds.l	1	; adresse haute du bufferPointeur			ds.l	1	; pointeur en coursbuff1				ds.b	256	; buffer temporaire	n�1buff2				ds.b	48	; buffer temporaire n�2NumST				ds.w	1	;Num�ro du sous-titre en coursItemType			ds.w	1ItemHandle 			ds.l	1itemRect 			ds		rectLargeurReglette		ds.w	1NombreSTLusRect		ds		rectrectangle			ds		rectLastXpos			ds.w	1DateTime			ds		DateTimeRecCourantSTPtr		ds.l	1			; Pointeur du d�but du sous-titre en coursCaracteresLus		ds.l	1			; nombres de cract�res lusStPtr				ds.l	1			; variable du st en m�moireNombreST			ds.l	1			; nombre de sous-titre dans le fichier en m�moireRGB_Color			ds.w	3TheDialogPtr		ds.l	1oldport				ds.l	1ST_Ptr; on recherche une zone de travail			move.l	G.BufferTransfert,d0			move.l	d0,Buffer(a6)			add.l	G.SIZEBufferTransfert,d0			move.l	D0,MaxBuffer(a6)			long	NombreST;Ptr		P;SousTitreRecordPtr ST_Ptr;GrafPtr	oldport;// ok on peut bosser; on ouvre un dialog		GetPort(&oldport);		dlog = GetNewDialog(154,nil,(WindowPtr)-1);		SetPort(dlog);		DrawDialog(dlog);// affichage 'Lecture du fichier : Nom de Fichier'				GetDItem(dlog,1,&type,&hndl,&box);		EraseRect(&box);		MoveTo(box.left,box.top+12);		DrawString("\pLecture du fichier: ");		DrawString(&name);// on dessine la r�glette		GetDItem(dlog,1,&type,&hndl,&box);		FrameRect(&box);			ST_Ptr=G.General_PremierSTPtr;		NumST=0;		/* ------------------------------------------------; on lit le fichier de la longueur du buffer*/		pb->ioCompletion=nil;		pb->ioBuffer=G.BufferTransfert;		pb->ioReqCount=G.SIZEBufferTransfert;		pb->ioPosMode=fsFromStart;		pb->ioPosOffset=0;		PBRead(pb,false);		CaracteresLus=G.SIZEBufferTransfert;		// on v�rifie que la version du fichier est compatible avec le logiciel en cour		h=GetResource('vers',1);		if (h) {			version=(short*)**h;			ReleaseResource(h);			}		/*				G.BufferTransfert,a0		move.w	(a0),d0		cmp.w	d7,d0		bge.s	PasDeProbleme	; version sup�rieur � cette version de logicielle; donc alerte	*/	// on efface le fichier en cours		EffaceTouslesSousTitres((char*)(G.BufferTransfert+2));		// on lit le header dans le fichier			P=&G.Preference_Header_SizeOf-&G.preference;		BlockMove(G.BufferTransfert,&G.preference,(long)P);		NombreST=G.General_NombreST;//on met de cote le nombre de sous-titre		G.General_NombreST=1;		/* -------------------------------------------------		*/		Buffer=G.BufferTransfert;		// on pr�pare la lecture du fichier		St_Ptr=Buffer+P;		move.l	Buffer(a6),a3	; d�but de la zone de travail				lea.l	G.Preference_Header_SizeOf,a0	; fin du header		move.l	a0,d0		lea.l	G.preference,a1		sub.l	a1,d0				; longueur du header		add.l	d0,a3				; adresse du premier sous-titre		move.l	a3,pointeur(a6)			move.l	G.general_PremierSTPtr,StPtr(a6); ----		lectureFichierLoop		move.l	pointeur(a6),a3				; nouveau sous-titre � lire dans le fichier		move.l	(a3),d0						; d0 longueur du sous-titre		move.l	a3,d1								add.l	d0,d1						; d1 ptr fin du sous-titre; on teste si le sous-titre est entier		move.l	MaxBuffer(a6),d0		cmp.l	d0,d1				       ;// max buffer		ble.s	LeSousTitreEstEntier		; comme son nom l'indique; on regarde si nous sommes � la fin du fichier; si non on lit a partir du d�but de sous-titre en cour j'usqu'a la fin; calcul de la longueur	� lire; longueur d�j� lue du fichier+(pointeurbuffer-pointeurd�butsous-titre)		move.l	CaracteresLus(a6),d1		add.l	pointeur(a6),d1		sub.l	Buffer(a6),d1		; d1 = position dans le fichier pour le contenu de a3; longueur � lire		move.l	G.SIZEBufferTransfert,d2		move.l	FileLenth(a6),d0		sub.l	d1,d0		sub.l	d2,d0		bpl.s	PasSupBuffer	; ok cela rentre	; cela ne rentre pas dans le buffer, il y aura un autre passage !		move.l	d2,d0			; taille du bufferPasSupBuffer		add.l	d0,CaracteresLus(a6)				move.l	paramBlock(a6),a0		clr.l	ioCompletion(a0)		move.w	sfsvRefNum(a6),ioVrefNum(a0)		move.l	G.BufferTransfert,ioBuffer(a0)		move.l	d0,ioReqCount(a0)		move.w	#fsFromStart,ioPosMode(a0)			; r�f�rence //au d�but		move.l	d1,ioPosOffset(a0)					; � partir du sous-titre		_Read		jsr		TraitementErreurFichier	; on raz les pointeurs 				move.l	G.BufferTransfert,pointeur(a6)LeSousTitreEstEntier; on insert un soustitre		move.l	STPtr(a6),a0		move.l	pointeur(a6),a3	; on transfert le header dans la m�moire				move.l	file_TimeCodeIn(a3),st_TimeCodeIn(a0) 		move.l	file_TimeCodeOut(a3),st_TimeCodeOut(a0)		move.l	file_NumeroST(a3),st_NumeroST(a0)		move.l	file_TexteLenth(a3),st_TexteLenth(a0)		move.l	file_StyleLenth(a3),st_StyleLenth(a0)		move.w	file_XOffset(a3),st_XOffset(a0) 		move.w	file_YOffset(a3),st_YOffset(a0) 		move.w	file_Error(a3),st_Error(a0) 		move.w	file_Flags(a3),st_Flags(a0) 		move.w	file_Nlines(a3),st_Nlines(a0) 		move.l	file_PosOffsetTable(a3),st_PosOffsetTable(a0)		move.b	file_Justification(a3),d0				cmp.b	#4,d0		blo.s	PasSupJustif		moveq	#0,d0		; par d�fault centr�ePasSupJustif				move.b	d0,st_Justification(a0)    		move.b	file_MasKType(a3),d0		cmp.b	#4,d0		blo.s	PasSupMask		moveq	#0,d0		; par d�fault centr�ePasSupMask		move.b	d0,st_MasKType(a0)   		move.l	file_spare(a3),st_spare(a0)		move.w	4+file_spare(a3),4+file_spare(a0)		move.l	file_LenthST(a3),d0		sub.l	#file_sizeOf,d0		clr.l	st_LenthST(a0)		move.l	a3,a4			 	; sauvegarde du ptr		add.l	#file_sizeOf,a3	;   start offset pointer pour les data		move.l	#st_sizeOf,d7; -------; on recopie le texte		tst.l	file_TexteLenth(a4)		beq.s	RecopieCommentaire		; la chaine est vide donc pas de style										move.l	STPtr(a6),a1		move.l	st_NumeroST(a1),d0		cmp.l	#2003,d0		blo.s	@12231		;break@12231	add.l	d7,a1 					; a1 pointe sur le d�but du texte dans le sous-titre		move.l	a3,a0					; d�but du texte dans le fichier		move.l	file_TexteLenth(a4),d0	; longueur du texte				_blockMove; on calcule l'adresse du prochain block � recopier, alignement sur ds.l 		move.l	file_TexteLenth(a4),d0	; longueur du texte		import	AligneD0		jsr		AligneD0; longueur ajust�e sur ds.l		move.l	STPtr(a6),a0			; d�but du sous-titre		add.l	d0,st_LenthST(a0)		; on ajoute la longueur du texte � la taille du sous-titre 		add.l	d0,a3					; pointeur de la prochaine zone		add.l	d0,d7					; start offset du suivant en m�moire; ----------		; on recopie les styles		tst.l	file_StyleLenth(a4)		beq.s	RecopieCommentaire		; il n'y a pas de style; on  calcule le pointeur des styles				move.l	STPtr(a6),a0		move.l	a0,a1		add.l	d7,a1					; longueur du texte ajust�e en .l		move.l	a1,st_StylePtr(a0)		; a1 pointe sur le d�but du style dans le sous-titre		move.l	file_StyleLenth(a4),d0	; longueur des styles		move.l	a3,a0 					; a0 d�but style dans le fichier		_BlockMove; on calcule l'adresse du prochain block � recopier, alignement sur ds.l 		move.l	file_StyleLenth(a4),d0	; longueur du texte		import	AligneD0		jsr		AligneD0; longueur ajust�e sur ds.l		move.l	STPtr(a6),a0			; d�but du sous-titre		add.l	d0,st_LenthST(a0)		; on ajoute la longueur du style � la taille du sous-titre 		add.l	d0,a3					; pointeur de la prochaine zone				add.l	d0,d7; -------RecopieCommentaire				clr.l	st_CommentairePtr(a0)		clr.l	st_Commentairelenth(a0)				tst.l	file_CommentaireLenth(a4)		beq.s	DessinCurseur		; il n'y a pas de commentaire; on  calcule le pointeur du commentaire				move.l	STPtr(a6),a0		move.l	a0,a1		add.l	d7,a1						; a1 pointe d�but commentaire ajust� .l		move.l	a1,st_CommentairePtr(a0)				move.l	file_CommentaireLenth(a4),d0	; longueur des commentaires		move.l	d0,st_Commentairelenth(a0)		move.l	a3,a0 							_BlockMove; on calcule l'adresse du prochain block � recopier, alignement sur ds.l 		move.l	file_CommentaireLenth(a4),d0	; longueur du texte		import	AligneD0		jsr		AligneD0; longueur ajust�e sur ds.l		move.l	STPtr(a6),a0			; d�but du sous-titre		add.l	d0,st_LenthST(a0)		; on ajoute la longueur du commentaire � la taille du sous-titre 		add.l	d0,a3					; pointeur de la prochaine zone				; ---	; on rafraichie la reglette, et le curseurDessinCurseur		move.l	a3,pointeur(a6)			; on sauvegarde ce pointeur car c'est le d�but du prochain		move.l	stPtr(a6),a0		move.l	st_AbsNumSt(a0),d0		move.w	LargeurReglette(a6),d1		and.l	#$fff,d1			mulu.w	d1,d0; resultat sur 32 bits dans d0		move.l	NombreST(a6),d1		divu	d1,d0; resultat dans d0		cmp.w	LastXpos(a6),d0		beq.s	onnedessinepas		move.w	d0,LastXpos(a6) 		bsr		Draw_Reglette				move.w	#16,-(sp) 		JSR	SpinCursor	; spin the ball				_PenNormal		onnedessinepas:				; --------------------------------------------------------	; on teste si la lecture est termin�e; on regarde si le num�ro absolu est >= nombre de st				move.l	stPtr(a6),a0		move.l	st_AbsNumST(a0),d0		move.l	NombreST(a6),d1		cmp.l	d1,d0		bge.s	finLecture		; le fichier entier a �t� lu; non on continue, on insert un sous-titre				move.l	G.General_DernierSTPtr,a0		move.l	#0,d0			; longueur par d�faut		jsr		InsertST		move.l	G.General_DernierSTPtr,a0		move.l	a0,stPtr(a6)			; adresse d�but prochain sous-titre		bra 	lectureFichierLoop		; non on continu		; oui, on se casse de l�			finLecture		move.l	NombreST(a6),G.General_NombreST		move.l	TheDialogPtr(a6),-(sp)		_DisposDialog		Exit	move.l	d1,d7		move.w	#$0505,-(sp)			jsr		Show_cursor		move.l	oldport(a6),-(sp)		_SetPort				UNLK	A6			; destroy the link		MOVEA.L	(SP)+,A0		; pull off the return address		ADDA.L	#ParamSize,SP		; strip all of the caller's parameters		JMP	(A0)			; return to the caller		string	PASCALGroundColor		dc.w	30962,20192,16402	Draw_Reglette; cette routine rafraichie la reglette				movem.l	d0-d7/a0-a5,-(sp)				move.l	TheDialogPtr(a6),-(sp)		move.w	#3,-(sp)		pea		ItemType(a6)		pea		ItemHandle(a6)		pea		itemRect(a6)		_GetDItem				pea		itemRect(a6)		move.w	#2,-(sp)		move.w	#2,-(sp)		_insetRect				sub.w	#1,bottom+itemRect(a6)				move.w	LastXpos(a6),d0		cmp.w	left+itemRect(a6),d0		bhi.s	@123		move.w	left+itemRect(a6),d0@123				move.w	d0,right+itemRect(a6)						move.w	right+itemRect(a6),d0		sub.w	left+itemRect(a6),d0		cmp.w	#2,d0		bhi.s	Do_Reflet				move.w	#10000,RGB_Color(a6)		move.w	#50000,2+RGB_Color(a6)		move.w	#10000,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor						pea		itemRect(a6)		_PaintRect		move.w	#0,RGB_Color(a6)		move.w	#0,2+RGB_Color(a6)		move.w	#0,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor		movem.l	(sp)+,d0-d7/a0-a5		rtsDo_Reflet		move.w	#0,RGB_Color(a6)		move.w	#20000,2+RGB_Color(a6)		move.w	#0,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor		move.w	left+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_MoveTo		move.w	right+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_LineTo				move.w	right+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_MoveTo		move.w	right+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_LineTo		move.w	#15535,RGB_Color(a6)		move.w	#55535,2+RGB_Color(a6)		move.w	#15535,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor				move.w	left+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_MoveTo		move.w	right+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_LineTo				move.w	left+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_MoveTo		move.w	left+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_LineTo		pea		itemRect(a6)		move.w	#1,-(sp)		move.w	#1,-(sp)		_insetRect						move.w	#5535,RGB_Color(a6)		move.w	#20535,2+RGB_Color(a6)		move.w	#5535,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor		move.w	left+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_MoveTo		move.w	right+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_LineTo				move.w	right+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_MoveTo		move.w	right+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_LineTo		move.w	#15535,RGB_Color(a6)		move.w	#55535,2+RGB_Color(a6)		move.w	#15535,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor				move.w	left+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_MoveTo		move.w	right+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_LineTo				move.w	left+itemRect(a6),-(sp)		move.w	top+itemRect(a6),-(sp)		_MoveTo		move.w	left+itemRect(a6),-(sp)		move.w	bottom+itemRect(a6),-(sp)		_LineTo; on dessine l'int�rieur du rectangle		pea		itemRect(a6)		move.w	#1,-(sp)		move.w	#1,-(sp)		_insetRect				add.W	#1,right+itemRect(a6)		add.W	#1,bottom+itemRect(a6)		move.w	#10000,RGB_Color(a6)		move.w	#45000,2+RGB_Color(a6)		move.w	#10000,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor				pea		itemRect(a6)		_PaintRect				move.w	#0,RGB_Color(a6)		move.w	#0,2+RGB_Color(a6)		move.w	#0,4+RGB_Color(a6)		pea		RGB_Color(a6)		_RGBForecolor				_PenNormal				movem.l	(sp)+,d0-d7/a0-a5		rts				DbgInfo.new		ReadBonBougreFormat	; this name will appear in the debugger		align 4			ENDP		
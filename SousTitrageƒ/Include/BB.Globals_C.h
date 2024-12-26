/*********************************	BB.Globals.h		Fichier de d�finition des globals pour le logiciel PoWer Subtitling**********************************/#include "MyInclude.h"#include "SousTitreRecord.h"#include "DisplayFont.h"#ifndef	 __BBGlobals__#define	 __BBGlobals__// ------------- D�finition #define	ListingHauteurCarreST 64	#define 	ajout_largeur_ST_Listing 25#define	st_FramePerSeconds 25// pour le funtypedef long 	*LPtr;typedef short	*SPtr;/*	kMaxDocWidth is an arbitrary number used to specify the width of the TERec's	destination rectangle so that word wrap and horizontal scrolling can be	demonstrated. */#define	kMaxDocWidth			576	/* kMinDocDim is used to limit the minimum dimension of a window when GrowWindow	is called. */#define	kMinDocDim				64/*	kControlInvisible is used to 'turn off' controls (i.e., cause the control not	to be redrawn as a result of some Control Manager call such as SetCtlValue)	by being put into the contrlVis field of the record. kControlVisible is used	the same way to 'turn on' the control. */#define kControlInvisible		0#define kControlVisible			0xFF/*	kScrollbarAdjust and kScrollbarWidth are used in calculating	values for control positioning and sizing. */#define kScrollbarWidth			16#define kScrollbarAdjust		(kScrollbarWidth - 1)/* largeur de la barre en bas des fen�tres (d�termine largeur Hscroll) */#define kBoutFenetreBasLargeur	150/*	kScrollTweek compensates for off-by-one requirements of the scrollbars to have borders coincide with the growbox. */#define kScrollTweek			2	/*	kCrChar is used to match with a carriage return when calculating the	number of lines in the TextEdit record. kDelChar is used to check for	delete in keyDowns. */#define kCrChar					13#define kDelChar				8	/*	kButtonScroll is how many pixels to scroll horizontally when the button part	of the horizontal scrollbar is pressed. */#define kButtonScroll			4	#define kMinSize	23				/* application's minimum size (in K) *//*	We made the preferred size bigger than the minimum size by 12K, so that	there would be even more room for the scrap, FKEYs, etc. */#define kPrefSize	35				/* application's preferred size (in K) */#define	rMenuBar	128				/* application's menu bar */#define	rAboutAlert	128				/* about alert */#define	rUserAlert	129				/* error user alert */#define	rWindow		128				/* application's window */#define rStopRect	128				/* rectangle for Stop light */#define rGoRect		129				/* rectangle for Go light *//* kSysEnvironsVersion is passed to SysEnvirons to tell it which version of the   SysEnvRec we understand. */#define	kSysEnvironsVersion		1/* kOSEvent is the event number of the suspend/resume and mouse-moved events sent   by MultiFinder. Once we determine that an event is an osEvent, we look at the   high byte of the message sent to determine which kind it is. To differentiate   suspend and resume events we check the resumeMask bit. */#define	kOSEvent				app4Evt	/* event used by MultiFinder */#define	kSuspendResumeMessage	1		/* high byte of suspend/resume event message */#define	kResumeMask				1		/* bit of message field for resume vs. suspend */#define	kMouseMovedMessage		0xFA	/* high byte of mouse-moved event message */#define	kNoEvents				0		/* no events mask *//* The following constants are used to identify menus and their items. The menu IDs   have an "m" prefix and the item numbers within each menu have an "i" prefix. */#define	mApple					128		/* Apple menu */#define	iAbout					1#define	mFile					129		/* File menu */#define	iNew					1#define	iClose					4#define	iQuit					12#define	mEdit					130		/* Edit menu */#define	iUndo					1#define	iCut					3#define	iCopy					4#define	iPaste					5#define	iClear					6#define	mLight					131		/* Light menu */#define	iStop					1#define	iGo						2/*	1.01 - kTopLeft - This is for positioning the Disk Initialization dialogs. */#define kDITop					0x0050#define kDILeft					0x0070/*	1.01 - kMinHeap - This is the minimum result from the following	equation:				ORD(GetApplLimit) - ORD(ApplicZone)			for the application to run. It will insure that enough memory will	be around for reasonable-sized scraps, FKEYs, etc. to exist with the	application, and still give the application some 'breathing room'.	To derive this number, we ran under a MultiFinder partition that was	our requested minimum size, as given in the 'SIZE' resource. */	 #define kMinHeap				21 * 1024	/*	1.01 - kMinSpace - This is the minimum result from PurgeSpace, when called	at initialization time, for the application to run. This number acts	as a double-check to insure that there really is enough memory for the	application to run, including what has been taken up already by	pre-loaded resources, the scrap, code, and other sundry memory blocks. */	 #define kMinSpace				8 * 1024/* kExtremeNeg and kExtremePos are used to set up wide open rectangles and regions. */#define kExtremeNeg				-32768#define kExtremePos				32767 - 1 /* required to address an old region bug */typedef struct TMXTask {   	QElemPtr					qLink;	short					qType;	ProcPtr					tmAddr;	long						tmCount;	long						tmWakeUp;	long						tmReserved;	long						tmRefCon; // pour stocker A5} TMXTask ,*TMXTaskPtr;/* 	structure qui permet d'acc�der � A5 en interruption	 /!\ il faut initialiser A5 avant	 	note: on peut d�clarer dans une structure:		IOParam 	pb;		long		A5World;	cela revient au m�me, sauf qu'il n'est pas n�cessaire d'�crire ex: 	IOWG->pb.ioPosMode=0;*/typedef 	struct IOParamPtrWithGlobal{	IOParam 	thepb;	long		A5World;} IOParamPtrWithGlobal,*IOParamPtrWithGlobalPtr;typedef struct VtrStatusRecord	{						short				vtr_error		; //error	long					vtr_Ticks		; //temps ou info s�rie re�ue	short				vtr_Type		; //vtr id	unsigned char	vtr_status[10]	; //grille de bit status data 	long					vtr_data	; //speed	long					vtr_LTC	; //ltc courant	long					vtr_VITC	; //vitc courant	long					vtr_TTM1 	; //tape timer 1	long					vtr_TTM2	; //tape timer 2	long					vtr_LTC_UB	; //user bits du ltc	long					vtr_VITC_UB; //user bits du vitc	short				vtr_recInhibit	;	long					vtr_DoSomethingTC;	// timecode pour effectue qque chose	long					vtr_DoSomethingOrder; //l'ordre � effectuer	long					vtr_DoSomethingParam; //les parram�tres � effectuer	short				vtr_DoNotSendRequest; // si � 0 la routine d'iterruption ne fait pas d'interrogation	long	spare	;} VtrStatusRecord,*VtrStatusRecordPtr,**VtrStatusRecordhandle ;				struct	MtcSearch{	long FoundElement;	Handle TheHandle;};typedef	struct MtcSearch MtcSearch,*MtcSearchPtr,**MtcSearchHandle;/*-------------------------------------------------------*/typedef struct MyQDGlobals{char privates[76];long randSeed;BitMap screenBits;Cursor arrow;Pattern dkGray;Pattern ltGray;Pattern gray;Pattern black;Pattern white;GrafPtr thePort;} MyQDGlobals;/*	Variable Globales*//* structure commune a l'assembleur et au C*/typedef struct AppGlobals { // pour le mac short			HasWNEvent; 		//boolean for WaitNextEvent trap, see ForceEnvironsshort			InBackground; 		//boolean for if in background, see OSEventSysEnvRec		Mac; 			//the system environment record, see ForceEnvirons/* --------------- le stockage des fen�tres --------------------*/WindowRecord  		BackDropWindow;WindowRecord  		DisplayWindow;WindowRecord 		ListingWindow;GWorldPtr	 		OffscreenDisplay;GWorldPtr	 		OffscreenListing;GWorldPtr	 		OffscreenSaisie;GWorldPtr 		OffscreenRendering;GWorldPtr 		OffscreenChenille;GWorldPtr 		DuplicateOffscreenRendering;WindowRecord		RenderingWindow;DialogPtr 			ServiceWindow;DialogPtr 			LogoWindow;DialogPtr			SpareWindow;DialogPtr			SpareWindow1;DialogPtr			SpareWindow2;/* --------------- le stockage des dialogs --------------------*/DialogPtr 			BlockNoteWindow;DialogRecord 		DialogAlertStorage;DialogRecord 		DialogSaisie;DialogRecord 		DialogStorage;DialogPtr 			TELECOMMANDEWindow; 		// la palette flotanteDialogPtr 			ChenilleWindow;			// la palette ChenillardDialogPtr 			ErrorsWindow;				// la palette ChenillardDialogPtr 			PerformanceWindow;		//la fen�tre pour afficher les performances/*	pour clef de protectionsoftware :fichier pr�f		*/short 			SoftProtect;long				StartTicks; 				//pour temps  max demolong 				democount;				//pour max affichage sous-titre/*	pointeur ou handle de resource		*/Handle 			ResourceDATA128; 			//HANDLE 	conversion MsDos<=> MacHandle 			ResourceDATA129; 			//HANDLE	conversion Majuscule<=> MinusculeHandle 			ResourceDATA130; 			//HANDLE	conversion Accentu� <=> MajusculeHandle			ResourceDATA1000; 		//HANDLE	conversion Accentu� <=> MajusculeCIconHandle		IconHandle1; 				//icon vitc onCIconHandle 		IconHandle2; 				//icon vitc off	CIconHandle		IconSauvegardeOn; 			//sauvegarde onCIconHandle 		IconSauvegardeOff; 			//sauvegarde offshort TheRes_number; 						//Le refnum  des resources/*	Handle de resource pr�f�rence       */Handle 			Preference_PourAffichage; 			//data 201Handle			Preference_PourTravail; 				//data 202AliasHandle 		Preference_PourDernierePoliceAlias; 	//data 202AliasHandle 		Preference_PourDernierFilmAlias; 		//data 203// pattern pour les fen�tresshort			BackDrop_PatNum	;short			Listing_PatNum	;short			Saisie_PatNum	;// fonction  automatique � la lecture d'un fichier Bbofshort			AutoOpenBlockNote;short			AutoOpenCheckList;short			AutoOpenLastFont;short			Preference_MultiFinder;short			AutoOpenLastFile;/* ------------ le control handle de listing */ControlHandle      ListingVScroll;/* ------------ le control handle de la fen�tre errors */ControlHandle     ErrorWindowScroll;/* Handle pour la liste des erreurs trouv�es */SousTitreErrorListeHandle		ListeError;/*	handle pour le quick open	*/Handle 			QuickOpenHandle;MenuHandle 	QuickOpenMenuHandle;/*	handle de color cursor	*/CCrsrHandle CurseurDessineST;CCrsrHandle CurseurClearBuffer;CCrsrHandle CurseurTransfert;// --------  Buffers Offscreen  Ptr 						OffscreenDisplayBase; //base bufferTEHandle 					BlockNoteTE; //handle du te pour le block noteshort 					BlockNoteTE_Item; //item correspondant au te/* plan m�moire suppl�mentaire pour la fabrication des bordures*/Ptr 						DuplicateOffscreenBuffer;Handle 					DuplicateOffscreenBuffer_handle;Handle 					RenderingFont_handle	;PixMapHandle 				AltPixMapHandle;TEHandle 					ListingTE;unsigned long 				ListingTEStNum; 		//abs num du te en cour 	short 					ListingTEStItem; 		//item en courshort 					ListingMaxDisplay;unsigned long 				CaseATickCountListing;unsigned short 				General_futurSousTitreEncour	;long 						CaseALastPointListing	;TEHandle 					saisieTE;unsigned long 				saisieTEStNum; 	//abs num du te en cour 	short 					saisieTEStItem;				//item en courshort 					General_OffsetSurListing; //pour d�tection click listingshort 					General_ClickOnce; //pour d�tection double Click/*Alias du fichier en cours */AliasHandle 				aliashandle; //handle pour le alias du fichier en cour/*	Handle du menu font		*/MenuHandle 				PopUp_Source_Font_List;unsigned char 				bufferTimecodeCourant[64];  //pour la conversion tc => ascii (pr�s � l'emplois)/* ADRESSE DU BUFFERTRANSFERT	*/Ptr 						BufferTransfert;long 						SIZEBufferTransfert;                              /*	PARAMETRES POUR LE FICHIER EN COUR	*/short					CurrentvRefNum;long						CurrentFileType;//TEXT Bbof ETC pas actifunsigned char				CurrentVersionNumber;unsigned char				unused;unsigned char				CurrentFileName[256];    long 						CurrentDirID;/*	attention les adresses de ces variables sont utilis�s par la routine d'interuptionne pas changer les longueurs sans v�rifier la routine d'interuption "SERIAL" *//* ---- �tat du lecteur s�rie */short 		SerialError;	long			VitcFilter; 			//filtre pour le lecteur vitclong			Serial_WatchDog; 		//chien de garde pour le lecteur s�rieshort		SendVtrTime_state; 	//derni�re demande de tc completed si =0/* ---- patch pour la configuration du lecteur de timecode */short 		LecteurTimeCode_Type;			//type de l'interface timecodeshort 		Player_TC_src;						//choix du tc playershort 		Mode_Commutateur;					//choix du tc player/*	tc pour le logiciel	*/unsigned long 	Vitc_Readen;unsigned long 	General_TCCourant;unsigned long 	General_LastTCCourant;unsigned long 	General_PseudoTimeCode;unsigned long 	LastRecevied422TC;	 			// pour mode auto Ltc/vitc/* Les IOParams pour E/S s�rie */IOParam 			Main_Rx_PB;	// pour la routine principale s�rielong 				General_A5register_1;Ptr  				Main_Rx_PB_Buffer;IOParam 			Sony_Rx_PB;	// pour la reception protocole Sonylong 				General_A5register_2;Ptr		 		Sony_Rx_Buffer;IOParam 			Vitc_Rx_PB; // pour la reception protocooe Lecteur Vitclong 				General_A5register_3;Ptr		 		Vitc_Rx_PB_Buffer;IOParam 			Tx1_PB;		//pour l'interogation du time codelong 				General_A5register_4;Ptr 				Tx1_PB_Buffer;IOParam 			Spare_PB;		// spare pour transmissionlong 				General_A5register_5;Ptr 				Spare_PB_Buffer;IOParam 			Spare1_PB;	// spare2 pour transmissionlong 				General_A5register_6;Ptr 				Spare1_PB_Buffer;/* Divers Compteurs pour mesurer les  performances Logiciel/Machine  */long				EventLoop_Speed;long				EventLoop_Counteur;long				Serial_Main_Count;long				Serial_Main_rate;long				Serial_Vitc_Count;long				Serial_Vitc_rate;long				Serial_Sony_Count;long				Serial_Sony_rate;/* record pour le time manager de la routine d'interrogation du times code et statusdes vtrs */TMXTask 			performanceTask;TMXTask 			AskTcTask;TMXTask 			GenerateurTask;	short 			VtrTask_flag_1;  //flag pour la routine status/time/*	indicateur si AppleTalk a �t� ferm� par nos soin */short 			AppleTalkClosed;unsigned long		General_OffsetTimeCode;  //offset sur tc Lu (trames sign�)/* m�moire pour le dernier sous-titre trouv� */unsigned short General_SousTitretrouve;  //sous- titre trouv� lors d'une recherche/*	sauvegarde des RefNums des des s�rials  drivers */short ModemOutRefNum;short ModemInRefNum;/* m�moire pour le sous-titre en cour */unsigned short 				General_SousTitreEncour; //sous-titre en cour de traitement dans saisie (/!\ attention ds.w mais  dans recorsd.a c'est un ds.l )unsigned short 				General_SousTitreEncour_spare; //spare pour avoir la m�me longueurunsigned long 				General_LastSousTitrecourant; //dernier sous-titre en cour de traitementunsigned long 				General_SousTitrecourant; //sous-titre en cour de traitementSousTitreRecordPtr		General_SousTitreCourantPtr; //son pointeur/* flags de transfert entre routine interruptionet routine principale */unsigned long 		TcInaAttendre;unsigned long 		TcOutaAttendre;short					TravailAFaire_Affichage;/* m�moire pour le dessin du sous-titre � l'�cran */unsigned long 					General_SousTitreHasChange; //true si le st courant a chang�unsigned long 					General_DrawState; 		 //�tat du rendererunsigned long 					General_STCourantOnScreen; //le st courant est-il a l'�cranSousTitreRecordPtr			Sous_titre_dessined; 	//cache du st dans la ramSousTitreRecordPtr			Sous_titreInOffscreen; 	//cache du st dans le buffer offscreenunsigned short					DrawState; //flag pour dialoguer avec la vbl task				GDHandle							graphDevForRenderFont;  //le gdevice pour les rendu de charRect									OffscreenRenderedRect;Rect									ScreenRenderedRect;short								OffscreenRendered;short								ScreenRendered;unsigned short					General_SousTitreDisplayed; 	//absNumdu st � l'�cran/*	structure contenant le status des VTRs	*/VtrStatusRecord 		RecorderStruct;VtrStatusRecord 		PlayerStruct;/* chaine de caract�res pour rechercher/remplacer */unsigned char 			Rechercher_STR[256];unsigned char 			Remplacer_STR[256];short 				Rechercher_Majuscule; 		//si true case sensitiveshort 				Rechercher_RevenirDebut; 	//wrap around searchunsigned short 			Rechercher_Commentaire; 	//flag pour indiquer si la rechehche doit se faire dans la chaine commentaireunsigned short 			Rechercher_DansZoneFlag; 	//flag si zone de rechercheunsigned long 			Rechercher_DebutZone;		// ptr du premier st de rechercheunsigned long 			Rechercher_FinZone; 		//ptr du dernier st de rechercheunsigned long			Rechercher_STNum; 			//pointeur du dernier sous titre trouveshort				Rechercher_StartOffset; 		// position du premier caract�re trouv�short				Rechercher_EndOffset ; 		//position du dernier caract�re trouv�unsigned short			Rechercher_InCommentaire; 	//flags pour indiquer si la chaine a �t� trouver dans un commentaire/*	variable pour le chien de garde	*/unsigned long 			WatchDogSerial;  	//variable pour le port s�rieunsigned long 			WatchDogSave; 	//variable pour sauvegarde automatiqueshort 						ChangeSinceLastSave;  	//true si liste mofifi�e depuis derni�re sauvegarde/* flags pour tracking de la fen�tre listing */short 						Preference_HardTracking;short 						Preference_Tracking;/* cache pour la routine conversion num => ptr 	*/SousTitreRecordPtr General_DernierNumConvertiPtr;/* sauvegarde pour le dialog changer sytle et police */short 					ChangeStyleDialog_Mode;short 					ChangeStyleDialog_style;short 					ChangeStyleDialog_font;unsigned long 		ChangeStyleDialog_debut;unsigned long 		ChangeStyleDialog_fin;/* variables pour l'exportation vers d'autres logiciels	*/short 					Preference_TypeExport;short					Preference_ConvertMsDos;short					Preference_InclureCommentaire;short					Preference_InclureSousNumero;short					Preference_N19_TypeTeletexte;short					Preference_DoubleHauteur;short					Preference_DoubleLargeur;short					Preference_Couleur; /*m�moire pour l'affichage de la fen�tre time codec.f. d�claration de variables*/short 					Preference_DisplayTimeCode;unsigned  long 		Bandeau_LastTC;short 					Echelle_Bandeau;short 					last_BarGraph;unsigned long		General_HIMEMST;/* debut de la liste des sous-titre */SousTitreRecordPtr		General_PremierSTPtr;SousTitreRecordPtr		General_DernierSTPtr;/* tc correspondant au 1er tc valide */unsigned long 				General_PremierTC;SousTitreRecordPtr		General_PremierTCPtr;/* 	offset et tc correspondant au tc valide dans la liste sous-titre */unsigned long 				General_DernierTC;SousTitreRecordPtr		General_DernierTCPtr;unsigned char PrStatus[26];  //status pour l'impression/* coordonn�es pour la carte d'affichage */Ptr				Base_Adresse;long				Row_Bytes;long 				sparebyte[3];short			Ve_Slot;				// n� du slot de la vid�o explorershort			Ve_RefNum; 			//le ref num du driver de la vid�o explorerGDHandle 			Ve_GDHandle; 		//gd handle de la video explorershort			VE_pixelDeph; 		//Nb de bits par pixelshort			VE_BoardID; 		//board idlong				VE_HATCHECK; 	//pour le blend mode VX		short			VE_Mode; 		//upstream keyer /downstream keyer/* structure pour le driver nu vista  */FontRenderRecord		Display_Font;  //parram�tre de la police d'affichagelong					Spare;				//MenuHandle			PopUp_Font; 			//POUR LE MENU POLICE (POP-UP)Handle				PopUp_FontNumberList;  //handle pour la table de correspondance 					long	NuvistaHardware[4];short nuvistaHphase;/* structure pour les hardware nu vista+ */NuVistaMixerCtlRegs 		nuvistaMixer;NuVistaAnalogCtlRegs 		nuvistaAnalog;NuVistaVideoCtlRegs 		nuvistaCltReg;/* zone m�moire pour les variables de la EVE3 key */Handle						EveHandle; 				//handle des routines apiunsigned long		 	Eve_SerialNumber; 	//n� de s�rie de la clef (n� Rainbow Tech)short						FindFirstKey_error; 	//erreur du premier appel de la clef/*Cette variables est plac�e dans plus loin dans de record	mais elle est indiqu�e ici pour m�moire	Appl_SerialNumber_InKey		*/unsigned long 			GFR0_inKey; 				//n� de serie �crit dans la clef pour le logiciel (GFR 0_1) unsigned short 			Options_dansLaClef;  		//(GFR 2_3) Options du logiciel validesunsigned short 			Options_dansLaClefspare;  	//(GFR 2_3) Options du logiciel validesunsigned long 			GFR2_inKey;/* le reste des GFRs */unsigned short 			Gfr4_inkey;unsigned short 			Gfr5_inkey;unsigned short 			Gfr6_inkey;unsigned short 			Gfr7_inkey;unsigned short 			Gfr8_inkey;unsigned short 			Gfr9_inkey;unsigned short 			GfrA_inkey;unsigned short 			GfrB_inkey;unsigned short 			GfrC_inkey;unsigned short 			GfrD_inkey;unsigned short 			GfrE_inkey;unsigned short 			GfrF_inkey;/*---------------------------------------------------------------	item <=> n� de font	Stockage de la routine de saut � la vbl task			Pour pouvoir acc�der aux variables globales pendant une int�ruption	on place la valeur de a5 juste devant la routine			*/VBLTask					VBL_Structure; 							//	VBLtask 		ds.b	16		Ptr							VBL_A5; 								//the a5 wordunsigned char			VBL_StartRoutinePtr[32]	; 		//start of VBLtask 32 octects pour le code (suffisant)/*   Movem.l	a5,-(sp)	sauvegarde des registres 		move.l	-8(pc),a5			; r�cup�ration de a5 		jmp		VBL_MainRoutine		; saut � la routine sous int�ruptions*/ /***   STOCKAGE DES VARIABLES DE PREFERENCE DE FONCTIONNEMENT ***   Stock�e en t�te de fichier 	*//* 	la version du logiciel	*/unsigned short 				versionLogiciel;/* pr�f�rence pour le film en cours */unsigned char				Preference_TitreOriginal[256];unsigned char				Preference_TitreFrancais[256];unsigned char				Preference_TitreEpisodeOriginal[256];unsigned char				Preference_TitreEpisodeTraduit[256];unsigned char				Preference_NomAdaptateur[256];unsigned char				Preference_CoordonneesAdaptateur[256];unsigned char				Preference_commentaire[256];unsigned char				CodeDeReference[256];unsigned short				PaysOrigine;unsigned short				CodeLangue;unsigned short				CodeCaractere;unsigned long				TcDebutFilm;unsigned long				DateDeCreation;unsigned long				ModifieLe;unsigned short				Revision;unsigned short				Preference_NombreSauv;unsigned short				Preference_AutoCheck;unsigned short				Preference_UtilCheck;unsigned short				Preference_KernCheck;unsigned short				Preference_Interval;unsigned short				Preference_LisiValue;unsigned short				Preference_Renumerotation;unsigned short				Preference_Enchaine;unsigned short				affiche_CR_Flag;							// ex pr�f�rence_multifinder unsigned short				Preference_SaisieLock;/*	table de correspondance pour les touches de fonctions	*/unsigned char 				TableFonctionKeys[32];/* flag true/false pour le dessin gris (listing)	*/unsigned short 				General_Preference_DessinGris;/*	divers 	*/unsigned long 				General_NombreST;unsigned long				General_StartNumberForST;		//$1 (par defaut)unsigned long				General_IncrementPourST;		//$1 (par defaut)unsigned short				General_Preference_flag_1; 	//pour le dialog recherche STunsigned short 				General_Preference_flag_2; 		//######non utilis�	/* 	Police et taille choisies pour l'affichage	*/short							General_TextSize; 		//courant size for saisieshort							General_FontNumber; 	//courant number for saisieshort							SaisieModePreferenciel; //mode de saisie  /* ---- Structure de donn�es li�e � l'impression du document */TPrStatus 					T_Print; //unsigned char	Byte								spareprint[94];/*  ---- liste de font en m�moire */Handle		Unused1;						//Display_Font_List_Handle;  //0 si pas de police disponible/* ---- parram�tres d'affichageformat 8 alpha, 8 red, 8 green, 8 blue => 32 bits	*/unsigned long			RGB_FaceColor; unsigned long			RGB_BorderColor;unsigned long			RGB_OutlineBoxColor;unsigned long			RGB_ShadowColor;short						X_Offset;short						Y_Offset;short						Outline_Box;short						Overriding_All_Attribute;/* m�moire pour le block note */unsigned long			BlockNote_tc[16]; //espace pour 16 time code unsigned char			BlockNote_texte[256]; //256 caract�res/*	dernier offset effectu� sur le film	*/unsigned long 			offsetTC;unsigned char 			EditeurListe[34];			//Editeur liste sous-titreunsigned char 			NomDuMonteur[34]; 		//Nom du monteur de la liste de sous-titreunsigned char 			CoordonneeMonteur[34]; short						Justification; 		//justification d'affichageshort						Offset_JustifRL;	//offset bord �cran pour justif right et leftshort						Display_interligne;short						Boxing_Size;short						Boxing_SizeV;/*	espace pour la protection du logiciel  case pour le n�de s�rie (comme cela on peut conna�tre la provenance d'un fichier)*/unsigned long			Appl_SerialNumber_InKey	;  //n� de serie de la clef pour le logiciel (GFR 0_1) unsigned long			offsetTCIn;unsigned long			offsetTCOut;/* nom de la deni�re police d'affichage utilis�e */char							LastFontUsed[32];// pr�f�rence pour l'effet de transitionshort						EffectMode;short						FadeFactor;short						FadeTime;//Hauteur des sous-titre dans la fen�tre listingshort						HauteurST;// positionnement de d�part N19short						N19_VPStart;/* espace supl�mentaire pour des versions futurs du logiciel*//* /!\  attention,	 si vous modifier cette structure,	 il faut penser a modifier la structure entetefichier */// offset lecture TClong 							OffsetLectureTCPlay;long							OffsetLectureTCStop;short						ModeSaisieTC;/* espace supl�mentaire pour des versions futurs du logiciel*/unsigned char			spareForFutur[570];  //espace pour d'autre parram�tres//  ---------------------------// nouvelle variable V 1,5,8b7 , permet la justification de l	'espace d'affichageshort						safearea;// largeur safe area} AppGlobals,*AppGlobalsPtr,**AppGlobalsHandle;/* Structure pour les pr�f�rences d'affichage en resources */typedef  struct PREF_AFF_REC {short Pref_Baseline; 	//baselineshort Pref_XOffset; 		//Xoffsetshort Pref_MaskSize;	//SizeOf maskshort Pref_VeMode;  	//upstream keyer /Downstream keyershort Pref_Reserved[28];} PREF_AFF_REC,*PREF_AFF_RECPtr,**PREF_AFF_RECHandle;typedef  struct  PreferenceAffichage_Resource{short Pa_Baseline;short Pa_Xpos;short Pa_Kerning;short Pa_Espace;short Pa_Interligne;short Pa_MasqueBordure;} PreferenceAffichage_Resource, *PreferenceAffichage_ResourcePtr,**PreferenceAffichage_ResourceHandle;/* pr�f�rence pour l'exportation de fichier */// modifi� depuis V 1,5,1typedef	  struct PrefExportFichier{short 	Preference_TypeExport;short	Preference_ConvertMsDos;short	Preference_InclureCommentaire;short	Preference_InclureSousNumero;short	Preference_N19_TypeTeletexte;short	Preference_DoubleHauteur;short	Preference_DoubleLargeur;short	Preference_Couleur;short	Preference_VP;short	Spare[16];}PrefExportFichier, *PrefExportFichierPtr,**PrefExportFichierHandle;/* pr�f�rence pour v�rification de la liste */typedef	  struct  PrefVerifListe{short 	Preference_CoherenceTimeCode;short	Preference_RespectIntervalMinimum;short	Preference_RespectLisibilite;short	Preference_TolerenceLisibilite;short	Preference_RespectNombreCaractereLigne;short	Preference_NombreCaractereLigne;short	Preference_RespectNombreLigne;short	Preference_NombreLigne;short	Preference_DecalageVerticale;short	Spare[16];} PrefVerifListe, * PrefVerifListePtr,** PrefVerifListeHandle;/* Structure pour les pr�f�rences de travail stock�es en resources*/typedef  struct  PreferenceTravail_Resource {short	Pt_BackDropFlag;			// fen�tre back drop pr�sente ou nonshort	Pt_PatNum; 					//n� de la pattern �ppat� du fond de l'�cranshort	Pt_Enchaine	;				// mode d'encha�n�short	Pt_SauvegardeAuto;		// sauvegarde automatiqueshort	Pt_SauvegardeDuree;	// interval de sauveagrde (minutes)short	Pt_RenumerotationAuto;	// renum�rotation automatiqueshort	Pt_Preference_LisiValue;	// facteur de lisibilit�short	Pt_TypeVerification;		// mode de v�rifshort	Pt_Default_ListingSize;	// taille listingshort	Pt_Default_ListingFont;	// font listingshort	Pt_ModeDeTravail;			// mode de travailshort	Pt_OpenBlockNote;			// ouverture automatique Block-noteshort	Pt_Interval;						// interval minimumshort	Pt_GrayInListing;				// trac� gris dans listingshort	Pt_FadeTime;					// dur�e de fondushort	Pt_EffectMode;					// mode de transitionRect		Pt_PaletteTelecommandeRect;			// position palette t�l�commandeshort	Pt_PaletteTelecommandeVis;			// palette telecommande visible ou nonRect		Pt_BlockNoteRect;							// m�me chose pour block note ....short	Pt_BlockNoteVis;short	Pt_Listing_PatNum	;				// ppat pour listingshort	Pt_Saisie_PatNum;					// ppat pour saisieshort	Pt_AutoOpenBlockNote;				// ouverture automatique block noteshort	Pt_AutoOpenCheckList;				// v�rification automatique de la liste � l'ouvertureshort	Pt_AutoOpenLastFont;				// ouvrir si bbof la police utilis�e pour le filmRect		Pt_PaletteChenilleRect;			// position palette chenille ....short	Pt_PaletteChenilleVis;				// palette chenille visible ou nonshort	Pt_Echelle_Bandeau;					// echelle de la chenille en pixel/imageshort	Pt_affiche_CR_Flag	;			// affichage des caract�res � dans listingRect		Pt_PaletteSimuRect;			// position palette chenille ....short	Pt_PaletteSimuVis;			// palette chenille visible ou nonshort	Pt_OuvreDernierFilm_Flag;	// chargement du dernier film � l'ouvertureRect		Pt_ListingWindowRect;		// position fen�tre listingshort	Pt_ModeSaisieTC;short	Pt_offsetlecturestop;short	Pt_offsetlectureplay;short	Pt_spare[113];		 } PreferenceTravail_Resource,*PreferenceTravail_ResourcePtr,**PreferenceTravail_ResourceHandle;typedef struct sliderstruct{short	min;short	max;short	value;short	increment;Rect	bounds;}sliderstruct,*sliderstructPtr,**sliderstructHandle;typedef struct AvFlagsPref{Boolean 			FullSize;Boolean 			HalfSize;Boolean 			QuarterSize;Boolean			MaskingVitc;Boolean			MaskingSousTitre;Boolean			ForcerPolice;Boolean			ForcerBold;RGBColor			SimuColor;short			TextSize;short			SimuFont;short			AntiAlias;}AvFlagsPref,*AvFlagsPrefPtr,**AvFlagsPrefHandle;typedef struct AvPref{short		entree;short		standart;short		type;unsigned short lumiere;unsigned short contraste;unsigned short couleur;unsigned short contour;unsigned short hue;unsigned short black;unsigned short white;unsigned short MaskingVitc;unsigned short PositionFenetre;unsigned short spare[7];} AvPref,*AvPrefPtr,**AvPrefHandle;// structure pour d�termination des cartes graphiques pr�sentestypedef struct CarteGraphElement{GDHandle	GDH;short 	boardID;short	RefNum;short	slot;short	spare;}CarteGraphElement,*CarteGraphElementPtr,**CarteGraphElementHandle;typedef struct {	ListHandle hndl;	Rect bounds,scroll,content,dataBounds;	Point cSize,cell;	short nCells;	} UserList,*UserListPtr,**UserListHandle;// structure pour le stockage de sous-titrage dans l'interval vertical// Vertical Interleave Sub Titling Codingtypedef struct VISTC{	long		TcCourant;	long		Checksum;	long		TcIn;	long		TcOut;	short	NumST;	//	short	Xpos;	//	short	Ypos;	//	short	TexteLenth;	short	StyleLenth;	short	Flags;	// code langue, justif, masking, type t�l�texte} VISTC,*VISTCPtr, **VISTCHandle;#endif	// defined ?BBGlobals#include "Protos.h"
#include "BB.Globals_C.h"#include "CreateFastFont.h"#include "PPCDispatch.h"// les globals 	extern MyQDGlobals QD;	extern AppGlobals G;pascal void Terminate(void);//#pragma segment Renderingpascal 	void GetMinCharRect(Rect *rect,GWorldPtr OffscreenRendering);pascal 	CTabHandle MakeNBCTAB(void);void 	DoBlur(GWorldPtr OffscreenRendering,short 	blur,Rect *rect);CharHeaderPtr C_GiveDisplayFont_CharInfo(FontRenderRecordPtr theFont,short thechar,short theStyle);CharHeaderPtr C_GiveDisplayFont_FastCharInfo(FontRenderRecordPtr theFont,short thechar,short theStyle);pascal void C_makeDisplayFontName (FontRenderRecordPtr  FontRender );pascal short C_Draw_A_Char(FontRenderRecordPtr  FontRender,short  TheChar,short TheStyle, long  Face_Color,					long Border_Color,long Shadow_Color,long bgd_Color,					long  drapeau,short  Xpos ,short Ypos ,char* DisplayRamPtr,long RowBytes);					unsigned long MultiplyPixel(unsigned long bgd,unsigned long fgd,short shwfact);pascal Boolean RPIdleWText(Handle theRpd,long value,Str255 string,pascal void(*UpdateFct)(WindowPtr window),Boolean Multifinder );	void C_TestDrawFastChar(void);void C_TestDrawChar(long face, long border,long shadow, long mask);short ValidST(SousTitreRecordPtr ST_Ptr);short CC_Draw_SousTitre(SousTitreRecordPtr Str,short X,short Y,Ptr ScreenBase,long RowBytes,Rect *rect);typedef struct Pixarray{long	pix;}Pixarray,*PixarrayPtr,**PixarrayHandle;// routine de test de la police en m�moire: "fast font"void		CC_TestCDrawST(void);void 		C_TestCDrawST(void);// routine de test de cc_draw_a_STvoid		CC_TestCDrawST(void){long a;			SousTitreRecordPtr		ST_Ptr;WindowPtr	window=(WindowPtr)&G.ListingWindow;GrafPtr		oldport;RGBColor	color;									if(G.Base_Adresse) {					GetPort(&oldport); // pour les test					SetPort((WindowPtr)&G.DisplayWindow);  // pour les test															PenNormal();					PenSize(2,2);					color.red=0xcFFF;					color.green=0xcFFF;					color.blue=0xcFFF;					RGBForeColor(&color);					PenNormal();			/* on force le mode overriding attributs off */					a=G.Overriding_All_Attribute;					G.Overriding_All_Attribute=0; 						/* on affiche le resultat sur l'�cran */					G.DrawState=0x8001;					do{}while(G.DrawState&0xff00);			/* on raz la carte d'affichage */			/* on dessine le sous-titre */					ST_Ptr=C_ConversionNumeroSTPointeur((long)G.General_SousTitreEncour);			//		G.Sous_titre_dessined=ST_Ptr;				if (ValidST(ST_Ptr)==0)					//pour test				CC_Draw_SousTitre(ST_Ptr,G.X_Offset,G.Y_Offset,	G.Base_Adresse,G.Row_Bytes,&G.ScreenRenderedRect);					G.Overriding_All_Attribute=a;					SetPort(oldport);				} // existe t-il une carte d'affichage 							}void C_TestDrawChar(long face, long border,long shadow, long mask){Rect	rect;short	thechar,style,theStyle;long		a,Xpos,Ypos,b,x,y;PixMapHandle	Pmh;CharHeaderPtr	cp;FontRenderRecordPtr	FontRender;// on efface les buffers ecrans				Pmh=(**G.Ve_GDHandle).gdPMap;		rect=(**Pmh).bounds;		// changement de coordonn�e				rect.right=rect.right-rect.left;		rect.bottom=rect.bottom-rect.top;		rect.left=0;		rect.top=0;		b=rect.right-40;		C_paintRect(&rect,mask,G.Base_Adresse,G.Row_Bytes);// on efface la carte		Xpos=10;		Ypos=50;		FontRender=&G.Display_Font;	for (theStyle=0;theStyle<(G.Display_Font.Face_Number);theStyle++){		for (thechar=35;thechar<256;thechar++){		x=Xpos;		y=Ypos;				a=PPCDispatch_Call_C_Draw_A_Char(FontRender,thechar,theStyle,face,border,shadow,mask,1,Xpos,Ypos,G.Base_Adresse,G.Row_Bytes);		if (a<0) a=0;		Xpos+=a;		if (Xpos>b) {			Xpos=10;			Ypos+=G.Display_Font.interligne-6; 			if (Ypos>rect.bottom) Ypos=50;			}	   } // boucle char     } // boucle style}	pascal void Test_Draw_String (void);// cette routine dessine une chaine de caract�re// pour effectuer un test dans l'ecran d'affichage ...pascal void Test_Draw_String (void){Rect	rect;short	thechar,style,theStyle;long		a,X,Y,b,x,y;PixMapHandle	Pmh;CharHeaderPtr	cp;FontRenderRecordPtr	FontRender;Str255		str="\pCeci est une cha�ne de test";// on efface les buffers ecrans				Pmh=(**G.Ve_GDHandle).gdPMap;		rect=(**Pmh).bounds;		// changement de coordonn�e				rect.right=rect.right-rect.left;		rect.bottom=rect.bottom-rect.top;		rect.left=0;		rect.top=0;		b=rect.right-40;// on efface la carte		C_paintRect(&rect,0x0,G.Base_Adresse,G.Row_Bytes);		FontRender=&G.Display_Font;// on efface la carte		Y=G.Y_Offset-(G.Display_interligne+FontRender->interligne )*2;		for (theStyle=0;theStyle<3;theStyle++) {			X=120+G.X_Offset;			for (thechar=1;thechar<=str[0];thechar++){				if( (str[thechar]!=' ')&& (str[thechar]!=0xca)   ) {					a=PPCDispatch_Call_C_Draw_A_Char(FontRender,str[thechar],theStyle,G.RGB_FaceColor,G.RGB_BorderColor,0x00,0x00,2,X,Y,G.Base_Adresse,G.Row_Bytes);					X=X+G.Display_Font.NormalKerning+a;					} else {					X=X+G.Display_Font.NormalKerning+FontRender->spaceWidth;					}			}			Y+=G.Display_interligne+FontRender->interligne ;		}// for style}
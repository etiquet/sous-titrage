#include "All.h"#include "Rendering.h"pascal void GetMinCharRect(Rect *rect,GWorldPtr OffscreenRendering);pascal CTabHandle MakeNBCTAB(void);void DoBlur(GWorldPtr OffscreenRendering,short 	blur,Rect *rect);typedef struct Pixarray{long	pix;}Pixarray,*PixarrayPtr,**PixarrayHandle;void RenderAntiAliasChar(RenderInfoPtr render){	CGrafPtr		oldport;Boolean			preserv=GetPreserveGlyph();GDHandle		gdh;short			a,b,c,savearea;Rect			rect,rect1;FontInfo		finfo;PixMapHandle	pmh;	GetGWorld(&oldport,&gdh);	SetGWorld(render->OffscreenRendering,nil);	RGBForeColor(&render->noir);	RGBBackColor(&render->blanc);	EraseRect(&render->OffscreenRendering->portRect);		TextFont(render->font);	TextSize(render->size*render->Quality);	TextFace(render->style&0xf); 	GetFontInfo(&finfo);/* 	On positionne l'�criture du caract�re	on le d�cale du bord gauche et du bord haut,	cela pour �viter que le caract�re ne soit tronqu� lors d'op�ration	comme blur ou �paississement */		savearea=20+(render->size*render->Quality)/10+10*render->Quality+10*render->blur;	MoveTo(savearea,finfo.ascent+savearea);	SetPreserveGlyph (true);	DrawChar(render->thechar);/* on fait le calcul de la bordure */	BitMapToRegion(render->region,&(((GrafPtr)render->OffscreenRendering)->portBits)); 	a=(long)((render->border*render->Quality)*2)/4;	InsetRgn(render->region,-a,-a);	EraseRect(&render->OffscreenRendering->portRect);	PaintRgn(render->region);	/* on pr�pare le bitmap de destination */		SetGWorld(render->OffscreenRendering2,nil);		RGBForeColor(&render->noir);	RGBBackColor(&render->blanc);		EraseRect(&render->OffscreenRendering2->portRect);	SetRect(&rect1,20,20,					((finfo.widMax+render->border*render->Quality)*2)/2+savearea,					((finfo.ascent+finfo.descent+render->border*render->Quality)*2)/2 +savearea);	//InsetRect(&rect1,-render->border/2,-render->border/2);	/* on calcule les � bords du caract�res */	render->baseline=(finfo.ascent+savearea)/render->Quality;	render->rect.left=0;	render->rect.top=0;	a=(rect1.bottom-rect1.top)/render->Quality;	render->rect.bottom=render->rect.top+a;		a=(rect1.right-rect1.left)/render->Quality;	render->rect.right=(render->rect.left+a);	if (render->ratio==0x1609){		a=(rect1.right-rect1.left)/render->Quality;		render->rect.right=((render->rect.left+a)*3)/4;	}		if (render->ratio==0x0503){		a=(rect1.right-rect1.left)/render->Quality;		render->rect.right=((render->rect.left+a)*15)/16;	}		render->rect.right=(((render->rect.right)*2)/2);	render->rect.bottom=(((render->rect.bottom)*2)/2);	/* on effectue l'anti-aliasing	*/		CopyBits(&((GrafPtr)render->OffscreenRendering)->portBits,				&((GrafPtr)render->OffscreenRendering2)->portBits,				&rect1,&render->rect,srcCopy+ditherCopy,nil);/* on d�termine le rectangle correspondant au caract�re */	GetMinCharRect(&render->rect,render->OffscreenRendering2);/* on effectue le blue si n�cessaire */	if (render->blur){		InsetRect(&render->rect,-render->blur*2,-render->blur*2);		//DoBlur(render->OffscreenRendering2,render->blur,&render->rect);		GetMinCharRect(&render->rect,render->OffscreenRendering2);	}	SetGWorld(oldport,gdh);	SetPreserveGlyph (preserv);}pascal void GetMinCharRect(Rect *rect,GWorldPtr OffscreenRendering){Ptr	P;Ptr	P1,P2,P3;PixMapHandle	pmh;long rowbyte,l;short	a,b,i,j;unsigned char c;Boolean	exit;	pmh=GetGWorldPixMap(OffscreenRendering);	P=GetPixBaseAddr(pmh);	rowbyte=(long)0x1fff&(**pmh).rowBytes;		//on d�termine le bord haut	exit=false;	a=(*rect).bottom;	b=(*rect).right;	i=(*rect).top,	P2=P+i*rowbyte;	i--;	do {		i++;		j=0;		P1=P2+3; // on regarde le canal vert		do {			c=*P1;			if (c!=255) exit=true;			j++;			P1=P1+4; // pixel suivant		} while (exit==false && j<b);		P2=P2+rowbyte; //ligne suivante	} while (exit==false && i<a);	(*rect).top=i;		//on d�termine le bord bas 	exit=false;	i=(*rect).bottom+1;	P2=P+(*rect).bottom*rowbyte;	l=(long)((*rect).right)*4;	do {		i--;		j=(*rect).right;		P1=P2+l+2;		do {			c=*P1;			if (c!=255) exit=true;			P1=P1-4;			j--;		} while (exit==false && j>0);		P2=P2-rowbyte;	} while (exit==false && i>0);	(*rect).bottom=i+1;			//on d�termine le bord gauche	exit=false;	a=(*rect).bottom-(*rect).top;	b=(*rect).right;	P2=P+(*rect).top*rowbyte;	i=-1;	do {		i++;		j=0;		P1=P2+3; // on regarde le canal vert		do {			c=*P1;			if (c!=255) exit=true;			j++;			P1=P1+rowbyte; // ligne suivante		} while (exit==false && j<b);				P2=P2+4; //pixel suivant			} while (exit==false && i<a);	(*rect).left=i;		//on d�termine le bord droit	exit=false;	a=(*rect).bottom-(*rect).top;	b=(*rect).left;	l=(*rect).right*4;	P2=P+(*rect).top*rowbyte;	i=(*rect).right+1;	do {		j=0;		i--;		P1=P2+l+3; // on regarde le canal vert		do {			c=*P1;			if (c!=255) exit=true;			j++;			P1=P1+rowbyte; // ligne suivante		} while (exit==false && j<a);				P2=P2-4; //pixel precedent	} while (exit==false && i>b);	(*rect).right=i+1;		}pascal CTabHandle MakeNBCTAB(void){CTabHandle	tab;short		i;	tab=(CTabHandle)NewHandleClear(sizeof(ColorTable)+256*sizeof(CSpecArray));	HLock((Handle)tab);	(**tab).ctSeed=GetCTSeed();	(**tab).ctFlags=0;	(**tab).ctSize=255;	for(i=0;i<256;i++){		(**tab).ctTable[i].value=i;		(**tab).ctTable[i].rgb.red=i;		(**tab).ctTable[i].rgb.green=i;		(**tab).ctTable[i].rgb.blue=i;	}		HUnlock((Handle)tab);	return tab;}		/* cette routine prepare le rendering */	void PrepareRendering(RenderInfoPtr render){	Rect rect;	render->region=NewRgn();	render->rgn=NewRgn();	SetRect(&rect,0,0,800,800);	NewGWorld(&render->OffscreenRendering,1,&rect,nil,nil,0);	SetRect(&rect,0,0,200,200);	NewGWorld(&render->OffscreenRendering2,32,&rect,nil,nil,0);		if (render->OffscreenRendering)		LockPixels(GetGWorldPixMap(render->OffscreenRendering));	if (render->OffscreenRendering2)		LockPixels(GetGWorldPixMap(render->OffscreenRendering2));		/* on beep si probl�me */		if (! render->OffscreenRendering || !render->OffscreenRendering2){		SysBeep(10);		SysBeep(10);		}	render->blanc.red=-1;	render->blanc.green=-1;	render->blanc.blue=-1;	render->noir.red=0;	render->noir.green=0;	render->noir.blue=0;}/* cette routine dispose le rendering */	void FiniRendering(RenderInfoPtr render){		if (render->OffscreenRendering) {		UnlockPixels(GetGWorldPixMap(render->OffscreenRendering));		DisposeGWorld(render->OffscreenRendering);		}	if (render->OffscreenRendering2){		UnlockPixels(GetGWorldPixMap(render->OffscreenRendering2));		DisposeGWorld(render->OffscreenRendering2);		}	if (render->region) DisposeRgn(render->region);	if (render->rgn) DisposeRgn(render->rgn);}void DoBlur(GWorldPtr Offscreen,short	blur,Rect *rect){long	a,rowbyte,b,l;Handle	h;short	x,y,dx,dy;long		P1,P,P4;Ptr	P2=0; // sourcePtr	P3=0; // destinationlong	blur2;register PixarrayPtr	P5;PixMapHandle	pmh;		pmh=GetGWorldPixMap(Offscreen);	if (LockPixels(pmh)){		P3=(Ptr)GetPixBaseAddr(pmh);		rowbyte=(long)(**pmh).rowBytes&0x1fff;		a=(long)((**pmh).bounds.bottom-(**pmh).bounds.top)*rowbyte;		blur2=(long)(1+2*blur);		blur2=blur2*blur2;				h=NewHandleClear(a);				if (h){		// on copie le fichier image			HLock(h);			P2=*h;			BlockMove(P3,P2,a);					// on fait le blur		P4=0;		P4=(*rect).top*rowbyte+(*rect).left*4; // point de d�part			for (y=(*rect).top;y<=(*rect).bottom;y++){				P=P4;				for (x=(*rect).left;x<=(*rect).right;x++){	// boucles de moyenne								a=0;						for (dy=-blur;dy<=blur;dy++){					// on d�marre des coordonn�es -blur,-blur							P1=P-blur*rowbyte-4*blur+3;							for (dx=-blur;dx=blur;dx++){								b=0;								a=a+(long)*((P2+P1));								P1=P1+4;							}//dx							P1=P1+rowbyte;						}// dy												a=a/blur2; //on moyenne ce nouveauPixel						// on converti 8bits vers 32 bits						b=a+a<<8+a<<16+a<<24;						((PixarrayPtr)(P3+P))->pix=b;						P=P+4;// pixel suivant				}// horizontale				// on inscrit le pixel				P4=P4+rowbyte;// ligne suivante			}// boucle verticale						HUnlock(h);			DisposeHandle(h);		} //h !=nil					}//lock pixels	}
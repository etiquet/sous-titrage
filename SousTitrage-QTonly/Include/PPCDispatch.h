/**************************** 		fichier include du     "PPCDispatch.c"******************************/#include "DrawSousTitre.h"#include "CreateFastFont.h"#include  "MyCopyBits.h"void PPCDispatch_init(void);		//initialisationvoid PPCDispatch_Dispose(void);	//disposeshort  PPCDispatch_AcceleratedExist(void);	//sommes nous sur un PPC ?short PPCDispatch_Call_DrawSousTitreEng(FontRenderRecordPtr FontRender,	SousTitreRecordPtr STPtr,short X,short Y,Ptr ScreenPtr, long RowBytes,	DrawStParamPtr DP,Rect*  rect);pascal short PPCDispatch_Call_C_Draw_A_Char(FontRenderRecordPtr  FontRender,short  TheChar,short TheStyle, 	long  FaceColor, long BorderColor, long ShadowColor, long bgdColor,long  flags, short Xpos,short Ypos, char* DisplayRamPtr, long RowBytes);pascal void PPCDispatch_MyCopyBits (char* source ,char* destination,long rowbytes,Rect* rect);		// draw a char PPC	------------------------------------------------typedef	pascal   short	(*DrawAchar_ProcPtr)(FontRenderRecordPtr  FontRender,short  TheChar,short TheStyle, 	long  FaceColor, long BorderColor, long ShadowColor,long bgdColor,long  flags, short Xpos,short Ypos, char* DisplayRamPtr, long RowBytes);enum {	uppDrawAcharResInfo =  kPascalStackBased     		 | RESULT_SIZE(SIZE_CODE(sizeof(short))) 		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(FontRenderRecordPtr)))		 | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(short)))		 | STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(short)))		 | STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(long)))		 | STACK_ROUTINE_PARAMETER(5, SIZE_CODE(sizeof(long)))		 | STACK_ROUTINE_PARAMETER(6, SIZE_CODE(sizeof(long)))		 | STACK_ROUTINE_PARAMETER(7, SIZE_CODE(sizeof(long))) 		 | STACK_ROUTINE_PARAMETER(8, SIZE_CODE(sizeof(long))) 		 | STACK_ROUTINE_PARAMETER(9, SIZE_CODE(sizeof(short))) 		 | STACK_ROUTINE_PARAMETER(10, SIZE_CODE(sizeof(short))) 		 | STACK_ROUTINE_PARAMETER(11, SIZE_CODE(sizeof(char*))) 		 | STACK_ROUTINE_PARAMETER(12, SIZE_CODE(sizeof(long)))};		//Using these macros lets us use the same calls for 68K and PPC#if powerctypedef UniversalProcPtr DrawAcharUPP;#define CallDrawAchar_Proc(userRoutine, FontRender,TheChar,TheStyle,FaceColor,BorderColor,ShadowColor,bgdColor,flags,Xpos,Ypos,DisplayRamPtr,RowBytes)		\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppDrawAcharResInfo, (FontRender,TheChar,TheStyle,FaceColor,BorderColor,ShadowColor,bgdColor,flags,Xpos,Ypos,DisplayRamPtr,RowBytes))#elsetypedef DrawAchar_ProcPtr DrawAcharUPP;#define CallDrawAchar_Proc(userRoutine,FontRender,TheChar,TheStyle,FaceColor,BorderColor,ShadowColor,bgdColor,flags,Xpos,Ypos,DisplayRamPtr,RowBytes)		\		(*(userRoutine))(FontRender,TheChar,TheStyle,FaceColor,BorderColor,ShadowColor,bgdColor,flags,Xpos,Ypos,DisplayRamPtr,RowBytes)#endif		// draw a sous-titre PPC	----------------------------------------		typedef	pascal   short	(*Draw_SousTitreEng_ProcPtr)(FontRenderRecordPtr FontRender, SousTitreRecordPtr STPtr,short X,short Y,Ptr ScreenPtr,long RowBytes,	DrawStParamPtr DP,Rect* rect);enum {	uppDraw_SousTitreEngInfo =  kPascalStackBased     		 | RESULT_SIZE(SIZE_CODE(sizeof(short))) 		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(FontRenderRecordPtr)))		 | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(SousTitreRecordPtr)))		 | STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(short)))		 | STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(short)))		 | STACK_ROUTINE_PARAMETER(5, SIZE_CODE(sizeof(char*)))		 | STACK_ROUTINE_PARAMETER(6, SIZE_CODE(sizeof(long)))		 | STACK_ROUTINE_PARAMETER(7, SIZE_CODE(sizeof(DrawStParamPtr))) 		 | STACK_ROUTINE_PARAMETER(8, SIZE_CODE(sizeof(Rect*)))};		//Using these macros lets us use the same calls for 68K and PPC#if powerctypedef UniversalProcPtr DrawsSTEngUPP;#define CallDrawSTEng_Proc(userRoutine, FontRender, STPtr,X,Y,ScreenPtr,RowBytes,DP,rect)			\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppDraw_SousTitreEngInfo, ( FontRender,	STPtr,X,Y,ScreenPtr,RowBytes,DP,rect))#elsetypedef Draw_SousTitreEng_ProcPtr Draw_SousTitreEng_UPP;#define CallDrawSTEng_Proc(userRoutine, FontRender, STPtr,X,Y,ScreenPtr,RowBytes,DP,rect)		\		(*(userRoutine))( FontRender,STPtr,X,Y,ScreenPtr,RowBytes,DP,rect)#endif//  MyCopyBits routine	-------------------------------------		typedef	pascal   void	(*MyCopyBits_ProcPtr) (char* source ,char* destination,long rowbytes,Rect* rect);enum {	uppMyCopyBitsProcInfo =  kPascalStackBased		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(char*)))		 | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(char*)))		 | STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(long))) 		 | STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(Rect*)))};		//Using these macros lets us use the same calls for 68K and PPC#if powerctypedef UniversalProcPtr MyCopyBitsUPP;#define CallMyCopyBitsProc(userRoutine,source ,destination, rowbytes,rect)			\		CallUniversalProc((UniversalProcPtr)(userRoutine), uppMyCopyBitsProcInfo, ( source ,destination, rowbytes,rect))#elsetypedef MyCopyBits_ProcPtr MyCopyBitsUPP;#define CallMyCopyBitsProc(userRoutine,source ,destination, rowbytes,rect)		\		(*(userRoutine))(source ,destination, rowbytes,rect)#endif			//  C_Render_A_font_Eng routine	---------------------------------------pascal short	C_Render_A_font(FontRenderRecordPtr FontRender,GDHandle  GraphicDeviceH,long RowBytes,Ptr BaseAdresse);pascal short	C_Render_A_font_Eng(FontRenderRecordPtr FontRender,GDHandle  GraphicDeviceH,long RowBytes,Ptr BaseAdresse);typedef pascal   short	(*C_Render_A_font_Eng_ProcPtr) (FontRenderRecordPtr FontRender,GDHandle  GraphicDeviceH,long RowBytes,Ptr BaseAdresse);enum {	C_Render_A_font_EngProcInfo =   kPascalStackBased     		 | RESULT_SIZE(SIZE_CODE(sizeof(short))) 		 | STACK_ROUTINE_PARAMETER(1, SIZE_CODE(sizeof(FontRenderRecordPtr)))		 | STACK_ROUTINE_PARAMETER(2, SIZE_CODE(sizeof(GDHandle)))		 | STACK_ROUTINE_PARAMETER(3, SIZE_CODE(sizeof(long)))		 | STACK_ROUTINE_PARAMETER(4, SIZE_CODE(sizeof(char*)))};		//Using these macros lets us use the same calls for 68K and PPC#if powerctypedef UniversalProcPtr C_Render_A_font_EngUPP;#define C_Render_A_font_EngProc(Proc,FontRender,GraphicDeviceH, RowBytes,BaseAdresse)			\		CallUniversalProc((UniversalProcPtr)(Proc), C_Render_A_font_EngProcInfo,( FontRender,GraphicDeviceH, RowBytes,BaseAdresse))#elsetypedef C_Render_A_font_Eng_ProcPtr C_Render_A_font_EngUPP;#define C_Render_A_font_EngProc(userRoutine,FontRender ,GraphicDeviceH, RowBytes,BaseAdresse)		\		(*(userRoutine))(FontRender ,GraphicDeviceH, RowBytes,BaseAdresse)#endif						
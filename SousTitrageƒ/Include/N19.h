/*      ---------------------------------------			 Structure de donn�es pour la norme n19	 		 ----------------------------------------		 		 N19.h*/#ifndef	__N19H__#define	__N19H__// structure pour le block GSItypedef struct N19_GSI{Byte			CPN[3];				//num�ro page de codeByte			DFC[8];				//Code du format de disquetteByte			DSC;						//norme d'affichageByte			CCT[2];				//Tableau code de caract�resByte			LC[2];					//;Code de langueByte			OPT[32];				//titre original de programmeByte			OET[32];				//titre original de l'�pisodeByte			TPT[32];				//Nom du traducteurByte			TET[32];				//Traduction du titre de l'�pisodeByte			TN[32];				//Nom du traducteurByte			TCD[32];				//D�tails des coordonn�es du traducteurByte			SLR[16];				//Code de r�f�rence de la liste des sous-titresByte			CD[6];					//Date de cr�ationByte			RD[6];					//Date de r�visionByte			RN[2];					//Num�ro de r�visionByte			TNB[5];				//Nombre total de Block TTIByte			TNS[5];				//Nombre total de sous-titreByte			TNG[3];				//Nombre total de groupe de sous-titreByte			MNC[2];				//Nombre maximal de caract�res par ligneByte			MNR[2];				//Nombre maximum de lignes Byte			TCS;						//Status du Time codeByte			TCP[8];				//Tc d�but du filmByte			TCF[8];				//Tc Premier sous-titreByte			TND;						//Nombre total de disquetteByte			DSN	;					//Num�ro de la disquetteByte			CO[3];					//Pays d'origineByte			PUB[32];				//EditeurByte			EN[32];				//Nom du monteurByte			ECD[32];				//D�tails coordonn�es du monteurByte			SPARE_GSI[75];	// n.u.Byte			UDA[576];			//pour l'utilisateur} N19_GSI,*N19_GSIPtr,**N19_GSIHandle;typedef  struct	N19_TTI {	Byte 			SGN; 		//Num�ro de groupe de sous-titre	Byte				SN[2];		//num�ro du sous-titre	Byte				EBN;			//Num�ro du block d'extension	Byte				CS;			//Etat cumulatif	Byte				TCI[4];		//time code in	Byte				TCO[4];	//time code out	Byte				VP;			//Emplacement vertical	Byte				JC;			//Code de justification	Byte				CF;			//Drapeau de remarque	Byte				TF[112];	//Champ de texte} N19_TTI,*N19_TTIPtr,**N19_TTIHandle;#endif	//	__N19H__
/***********************************	Ce fichier inclus les d�finitions de header	n�cessaire � la compilation du bon bougre	fichier historique, on pourrais faire mieux aujourd'hui		note: il y a des definition pour le preprocesseur	qui permette de compiler differents type de version	prot�g� , non prot�g�, demo.	attention: les definitions doivent �tre unique.		Il ya �galement une definition pour un mode qui facilite le d�buggage	note: voir dans chaque fichier l'utilit�e de __Debug__			************************************/#ifndef __MyInclude__#define	__MyInclude__#include <Slots.h> #include <Serial.h>#include <Retrace.h>#include <Timer.h>#include <TextEdit.h>#include <Menus.h> #include "nuvista+.h"#include "VEDriver.h"#include "VEDriverAccess.h"#include "BB.FloatWindow.h"#include "AdditionnalDlog.h"#include "StdPrefsLib.h"//#define __Demo__			// pour compiler une version de d�monstration#define __NoProtect__ 	// pour compiler une version sans protection//#define __Debug__			// pour permettre un d�buggage plus ais� de certaine partie du logiciel#endif //defined ? __MyInclude__
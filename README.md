# sous-titrage

Partage open source du code du logiciel Power-subtitling écrit pour MacOS OS9 dans les années 2001 par mes soins.
Initié en assembleur pour la vitesse et progressivement réécrit en C/CC+ avec déjà un changement de processeur à la clé en passant de 680xx à PowerPC.

Ce logiciel était décliné en plusieurs versions :
- une pour commander des cartes vidéo professionnelles (digitales dites "D1") sur port "nubus" [lien](https://fr.wikipedia.org/wiki/NuBus)
- pour quicktime (la librairie d'apple qui faisait le rendu des sous-titre )
- une pour simplement faire le marquage / découpage des sous-titres avec 2 touches.

- Un boitier à base de 6305 [lien](ressources/HD6305X0.pdf)  a été développé pour collecter le VITC ( le time code vertical ) à partir d'un signal vidéo
- une version du logiciel savait s'interfacer en "RS 422" avec les magnétos professionnels Sony ou équivalent pour récupérer le time code. [lien](https://fr.wikipedia.org/wiki/Betacam)

Quelques belles astuce de programmation, de l'assembleur, un peu de temps réel sous interuption de processeur ultra précis pour synchroniser les sous-titre à l'image prêt. 

Pour le fun une tentative de portage sous winNT a été tentée, mais a échouée car dans le user space NT... le schéduleur préemptif multitache de windows... a un un incrément d'une miliseconde non modifiable à l'époque... c'était quasiment impossible à refaire... je remercie la communauté windows qui m'avait accompagnée.

(Une image vidéo c'est toutes les 20 ms... avec un délai de 2 à 3 ms cela ne fonctionnait tout simplement pas...)

Vintage un peu quand même tout ça...
https://www.devx.com/terms/nubus/
Et pour ceux qui ont écrit sous mac... ils étaient beau les livres que l'on avait à disposition... et la couleur est arrivée avec le Macintosh 2. J'ai découvert à l'époque la typographie.

[lien vers les livres ](https://knight.sc/software/2020/04/19/classic-macos-development.html)

Si vous êtes curieux ou simplement bricoleur et capable de lancer tourner un émulateur OS X, il y a un petit risque ce que cela fonctionne...
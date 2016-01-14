---------------------------------------------------------------------------------------------------------------------------
------------------------------------------- STREET FIGHTER 2 TRIBUTE ------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------
Autor: Jordi Simon Urbano

Repositori Git:
https://github.com/jordisimon/StreetFighter2_Tribute

Vídeo Youtube al joc original:
https://www.youtube.com/watch?v=GPP_RcMdqW4


INTRODUCCIÓ:

Aquest es un tribut a “Street Fighter 2 The world champion” (edició Super Nintendo).

L'abast d'aquesta pràctica consisteix en la implementació del combat de 2 jugadors.
Per tal fi s'han implementat dos personatges amb els seus moviments complets, Ryu i Ken.
De la mateixa manera també es proporcionen 3 escenaris diferents per desenvolupar el combat, el de Honda, el de Ken i el de Guile.

CONTROLS:

El joc es pot jugar amb teclat o amb comandament (s'ha provat amb el de XBox 360 per a Windows).
En cas de jugar amb teclat, les tecles per defecte son les següents:

Jugador 1:

Esquerra = A
Amunt-Esquerra = Q
Amunt = W
Amunt-Dreta = E
Dreta = D
Avall-Dreta = X
Avall = S
Avall-Esquerra = Z
Puny fluix = T
Puny mig = Y
Puny fort = U
Puntada fluixa = G
Puntada mitja = H
Puntada forta = J
Acceptar/Pausa = Espai

Jugador 2:

Esquerra = Teclat numèric 4
Amunt-Esquerra = Teclat numèric 7
Amunt = Teclat numèric 8
Amunt-Dreta = Teclat numèric 9
Dreta = Teclat numèric 6
Avall-Dreta = Teclat numèric 3
Avall = Teclat numèric 2
Avall-Esquerra = Teclat numèric 1
Puny fluix = Insert
Puny mig = Inici
Puny fort = RePag
Puntada fluixa = Suprimir
Puntada mitja = Fi
Puntada forta = AvPag
Acceptar/Pausa = Intro teclat numèric

En cas de jugar amb comandament de XBox 360 (per ambdos jugadors):

Moviment: Amb la creueta o amb l'stick esquerra
Puny fluix = X
Puny mig = Y
Puny fort = Left Shoulder
Puntada fluixa = A
Puntada mitja = B
Puntada forta = Right Shoulder
Acceptar/Pausa = Start

De totes formes aquest es el mapeig per defecte i es pot canviar per qualsevol altre des de l'arxiu Config.ini, secció [Match_Command_Context].
Les "action" son pulsacions que nomes es rebran en el moment de produirse.
Els "state" son pulsacions que es reben continuament mentre el botó corresponent es manté premut.
El mapeig es realitza de la següent manera:
actionOrState#=controllerId,controllerButton,keyboardButton,actionOrStateId
on
actionOrState# -> és l'identificador d'acció o estat per aquell context concret
controllerId -> és l'identificador de controlador (1 per jugador 1, 2 per jugador 2)
controllerButton -> és l'identificador del botó del controlador que es vol assignar a l'acció o estat (es pot consultar la llista de botons disponibles amb el seu identificador a GameControllerButton de l'arxiu SDLMapping.txt)
keyboardButton -> és l'identificador del botó del teclat que es vol assignar a l'acció o estat (es pot consultar la llista de botons disponibles amb el seu identificador a SDL_Scancode de l'arxiu SDLMapping.txt)
actionOrStateId -> és l'acció o estat al qual es vol assignar els botons anteriors (es pot consultar la llista d'accions o estats disponibles a CommandAction o CommandState respectivament de l'arxiu SDLMapping.txt) 
Exemple:
action2=1,11,26,0 
L'acció 2, mapeja pel controlador 1, el botó DPAD_UP, i la tecla W del teclat a l'acció MOVE_UP

GAMEPLAY:

La seqüència de joc es la mateixa que en el joc original.
Pantalla d'inici -> Menú principal -> Menú de selecció de personatge -> Menú de selecció de handicap i escenari -> Combat -> Resultat combat i acumulats -> Menú de selecció de personatge...

A la pantalla de menú principal només podrém escollir V.S. Battle. Un cop seleccionada aquesta opció, el joc ens porta a la pantalla de selecció de personatges.

La pantalla de selecció de personatges ens permet escollir quin personatge vol utilitzar cada jugador i ens mostra les estadistiques d'aquell personatge per cada jugador i les globals de cada jugador. En aquest tribut només estan disponibles per escollir Ryu i Ken. Quan cada jugador ha triat el personatge que desitja i ha confirmat amb Start es passa a la pantalla de selecció de Handicap i Stage.

La pantalla de selecció de Handicap i Stage permet que cada jugador ajusti el Handicap segons les seves preferencies o habilitats. Es pot escollir un numero de 0 a 7, on 0 provoca que els cops facin menys mal i 7 més. El valor per defecte es 3.
El jugador 1 a mes pot escollir l'escenari on es jugarà el combat. Per realitzar això, seleccionarà la secció de Stage (prement Avall (i comprobant que el titol Stage queda resaltat en vermell)) i podrà seleccionar l'escenari amb Esquerra o Dreta. En aquest tribut només hi ha disponibles tres escenaris, Honda, Guile i Ken.
Un cop escollit Handicap i Stage, el jugador 1 pot començar el combat prement Start.

Els combats poden tenir o no un temps límit, aquest ajustament també es pot realitzar des del mateix arxiu a la secció [Options], clau timeLimit (0 no hi ha limit, 1 hi ha limit).

L'objectiu de cada combat es guanyar dos rondes, o be deixant fora de combat a l'adversari o be tinguent mes vida que el rival al finalitzar el temps límit. Hi ha un màxim de 4 rondes per combat i si cap dels dos jugadors guanya dues rondes, el combat es considera empatat.

Al final de cada ronda es donen punts al jugador vencedor. 200 punts per punt de vida restant (30000 si el jugador ha acabat amb tota la vida) i, només en cas que la partida tingues límit de temps, 100 punts per cada segon que hagi sobrat al finalitzar la ronda.

Els jugadors poden realitzar una sèrie de moviments bàsics, comuns a tots els personatges, i uns moviments especials específics.
Els moviments bàsics són els següents:

Moviments:

Caminar endavant o endarrere: Esquerra o Dreta
Saltar vertical: Amunt
Saltar en diagonal: Amunt-Esquerra o Amunt-Dreta
Ajupir-se: Avall
Defensar-se dempeus: Endarrera mentre el rival efectua un atac. (La defensa dempeus no serveix contra les puntades que fa el rival ajupit)
Defensar-se ajupit: Avall-Enrera. (La defensa ajupida no serveix contra els atacs que fa el rival des de l'aire)

Atacs dempeus, saltant o ajupit:

Puny fluix
Puny mig
Puny fort
Puntada fluixa
Puntada mitja
Puntada forta

Llançaments:

Estant a prop de l'adversari, mentre el jugador es mou endavant, puny mig, puny fort, puntada mitja o puntada forta.

Els atacs especials es porten a terme realitzant una combinació de botons en un espai de temps limitat.
Els atacs especials de Ryu i Ken son els següents:

Hadoken (bola d'energia): Avall -> Avall-Endavant -> Endavant -> Puny fluix (o Puny mig o Puny fort)
Shoryuken (salt amb puny): Endavant -> Avall -> Avall-Endavant -> Puny fluix (o Puny mig o Puny fort)
Kyaku (puntada giratòria): Avall -> Avall-Endarrera -> Endarrera -> Puntada fluixa (o Puntada mitja o Puntada forta)

Els atacs especials es poden blocar defensant-se, però en aquest cas infligeixen igualment una fracció del dany normal.

De la mateixa forma, si un dels jugadors aconsegueix infligir certa quantitat de dany en un temps limitat al rival, aquest sortirà llençat pels aires i al posar-se dret quedarà atordit i indefens per uns instants. Aquest atordiment pot durar mes o menys segons la quantitat de dany rebuda, però el jugador atordit pot reduir el temps prement repetidament els diferents botons d'atac o Dreta - Esquerra.

Un cop finalitzat el combat es mostra una pantalla amb el resum d'estadístiques per a cada jugador, i finalment es torna a la pantalla de selecció de personatge.

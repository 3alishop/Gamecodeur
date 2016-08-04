/*
 *  TaskList.h
 *  enigma
 *
 *  Created by Rockford on 11/01/11.
 *  Copyright 2011 Casual Games France. All rights reserved.
 *
 */

#ifndef ETASKLIST_H
#define ETASKLIST_H

#include "KPTK.h"
#include "ESmartImage.h"
#include <vector>
#include <string>

#include "GraphicalStringTrad.h"

class ESequenceTextFade;
class EFancyString;

typedef enum {
   TASKLIST_MODE_NORMAL,
   TASKLIST_MODE_HINT
} eTaskListMode;

// question -> r�ponse
struct QuestionAnswer {
   GraphicalStringTrad graphSzQuestion;
   GraphicalStringTrad graphSzAnswer;
};

// un objectifs est d�finis par un objectif, une liste de question et leur r�ponses associ�s
struct Objective {
   GraphicalStringTrad graphSzObjective;
   std::vector<QuestionAnswer> vectQuestionAnswer;
};

class ETaskList {

public:
   ETaskList();
   ~ETaskList();

   void Check();
   void Logic();
   void Render();

   bool isVisible() const;

   // affiche la sequence "nouveau objectif" si en cours
   void renderSequence();

   void SetMode(eTaskListMode mode);
   eTaskListMode getMode() const;
   void SetUniverse(const char *szUniverseName);

   //ajoute un objectif � la liste et l'affiche � l'�cran
   void addObjective(const char* objective);
   
   // met � jour les objectifs, � appel� en cas de nouveau objectif ou r�solu
   void maj();

   float yOffset;

private:
   
   // renvoit la version traduite de la chaine ou la chaine si la version traduite n'existe pas
   const char* getTrad(const char* chaine);

   // ajoute l'objectif � la liste, vrai s'il faut v�rifier que l'objectif n'est pas deja pr�sent
   // renvoie vrai s'il a bien �t� rajout�, faux sinon
   bool addObjectiveToList(const char* objective, bool checkExist = false);
   
   // remplie le vecteur d'objectifs
   void fillListObjective();
   // assigne une question � un objectifs
   void assignQuestionToObjective(const std::string & question);
   // calcul les positions de texte des objectifs et leurs indices
   void calcPosition(KTextFace *lpFont);
   // cache toute les r�ponses
   void hideAllAnswer();

   // appel� en cas de clic pour tester sur quel objectif/indice a cliqu� la souris
   void clicOnTaskList(int x, int y, int containerX, int containerY, KTextFace *lpFont);

  // ESmartImage *_lpsimgMainTaskBg;
   char _szUniverseName[256];
   eTaskListMode _eMode;
   float _fYPos;
   bool _bVisible;

   KTextFace *_lpFont28;
   KTextFace *_lpFont16;
   KTextFace *_lpFontBold28;
   KTextFace *_lpFontBold20;
   KTextFace *_lpFont20;

   // vector qui contient la liste des objectifs
   std::vector<Objective> *_pVectListObjectiv;
   bool m_hasClicked;

   bool m_needCalcPosition;
  
   ESequenceTextFade *m_pSequenceTextFade;
};

#endif
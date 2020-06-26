/*!
   \file AI.hh
   \brief Plik modelujący klasę przeciwnika sztucznej inteligencji opartego na algorytmie MinMax
   \author Patryk Szydlik
   \date 25.05.20
 */

#pragma once
#include "Judge.hh"
#include "heap.hh"


/*!
\brief Klasa sztucznej inteligencji decydujacej o optymalnym ruchu na podstawie strategii MinMax
*/
class AI{
  gameJudge * current_game=nullptr;
  gameField * fieldToAnalise=nullptr;

  int checkOutcomeScore(savedMove move, sign AIplayer){
    //DODATNIE SA ZLE
    sign oponnent;
    if(AIplayer==circle){
      oponnent=cross;
    }else{
      oponnent=circle;
    };
    int max_score=1;
    int dx=0;
    int dy=0;
    sign reference=AIplayer;
    for(int direction=0;direction<4;direction++){
      switch(direction){
          case 1:
              dx=1;
              dy=0;
          break;
          case 2:
              dx=1;
              dy=1;
          break;
          case 3:
              dx=0;
              dy=1;
          break;
          case 0:
              dx=-1;
              dy=1;
          break;
      };
      
      int sum=1;
      for(int i=0;i<2;i++){
          int stopped=0;
          int current_x=move.pos_x;
          int current_y=move.pos_y;
          if(i==1){
              dx=-dx;
              dy=-dy;
          };     
          while(!stopped){
              current_x=current_x+dx;
              current_y=current_y+dy;
              if(current_x>=0 && current_x<current_game->getSize() && current_y>=0 && current_y<current_game->getSize()){
                  sign testedField=fieldToAnalise->getField(current_x,current_y);
                  if(testedField!=reference ){
                      if(testedField==oponnent){stopped=1;};
                  }else{
                      sum++;
                  };
              }else{
                  stopped=1;
              };
          };
      };
      if(sum>=current_game->getWinLength()){
        max_score=100;
      }else if(sum>max_score){
        max_score=sum;
      };  
    };
    return -1*max_score;
  }

  

  void symulateGame(int &best_x, int &best_y, int &depth, sign player){
    sign oponnent; //minimazing player
    if(player==circle){
      oponnent=cross;
    }else{
      oponnent=circle;
    };

    savedMove bestMove;
    int bestScore=-100;
    int score;

    for(int i=0;i<fieldToAnalise->size;i++){
      for(int j=0;j<fieldToAnalise->size;j++){
        if(fieldToAnalise->getField(i,j)==blank){
          current_game->putSign(i,j);
          score=minimax(player, depth, oponnent);
          current_game->undo();
          if(score>=bestScore){
            bestScore=score;
            bestMove.set(i,j);
          };
        };
      };
    };
    best_x=bestMove.pos_x;
    best_y=bestMove.pos_y;
  }
  
  int minimax(sign maxplayer, int depth, sign minplayer){
    if(fieldToAnalise->isFull()){
      return 0;
    }else if(current_game->isWinner()){
      if(current_game->player()!=maxplayer){ // oznacza to ze poprzednia zwycieska tura byla maxplayer
        return 1;
      }else if(current_game->player()!=minplayer){  // oznacza to ze poprzednia zwycieska tura byla minplayer
        return -1;
      };
    };

    if(depth<=0){
      return 0;
    }

    int bestScore;
    int score;
    if(current_game->player()==maxplayer){  //maximazing outcome
      bestScore=-100;
      for(int i=0;i<fieldToAnalise->size;i++){
        for(int j=0;j<fieldToAnalise->size;j++){
          if(fieldToAnalise->getField(i,j)==blank){
            current_game->putSign(i,j);
            score=minimax(maxplayer, depth-1, minplayer);
            current_game->undo();
            if(score>bestScore){
              bestScore=score;
            };
          };
        };
      };
    }else if(current_game->player()==minplayer){ //minimazing outcome
      bestScore=100;
      for(int i=0;i<fieldToAnalise->size;i++){
        for(int j=0;j<fieldToAnalise->size;j++){
          if(fieldToAnalise->getField(i,j)==blank){
            current_game->putSign(i,j);
            score=minimax(maxplayer, depth-1, minplayer);
            current_game->undo();
            if(score<bestScore){
              bestScore=score;
            };
          };
        };
      };
    };

    return bestScore;
  }
  public:

  AI(gameJudge * load_game){
    current_game=load_game;
    fieldToAnalise=current_game->shareField();
  }

  void makeMove(sign player){
    int x,y;
    int depth=1;
    int size=fieldToAnalise->size;
    if(size==3){
      depth=6;
    }else if(size>3 && size<6){
      depth=4;
    }else if(size > 5 && size<8){
      depth=3;
    }else if(size > 7 && size<20){
      depth=2;
    };

    depth=findOptimalDepth();

    
    symulateGame(x,y,depth,player);
    current_game->makeMove(x,y);
  }

  int findOptimalDepth(){
    float recursionLimit=20000;
    int freeSpaces=fieldToAnalise->freeFields();
    int new_depth=0;
    do{
      new_depth++;
      recursionLimit=recursionLimit/freeSpaces;
      freeSpaces--;
    }while(recursionLimit>freeSpaces);
    if(new_depth>fieldToAnalise->freeFields()){
      new_depth=fieldToAnalise->freeFields();
    };
    return new_depth;
  }


};
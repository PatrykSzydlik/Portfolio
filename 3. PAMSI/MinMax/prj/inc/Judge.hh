/*!
   \file Judge.hh
   \brief Plik modelujący funkcję sędziowską decydującą o tym czy gracz wygrał
   \author Patryk Szydlik
   \date 25.05.20
 */

#pragma once

#include <Field.hh>
#include <list.hh>

/*!
\brief Klasa zapamietujaca wykonane ruchy
*/
struct savedMove{
    int pos_x;
    int pos_y;


    savedMove(){
        pos_x=0;
        pos_y=0;
    }

    savedMove(int x, int y){
        pos_x=x;
        pos_y=y;
    }

    savedMove(const savedMove & ruch){
        pos_x=ruch.pos_x;
        pos_y=ruch.pos_y;
    }

    void set(int x,int y){
        pos_x=x;
        pos_y=y;
    }
};

class gameJudge;

/*!
\brief Klasa przechoujaca informacje o ustalonych zasadach gry
*/
class gameRule{
    private:
        int fieldSize=3;
        int winLength=3;
        sign winner=blank;
        int draw=0;
        int isAI[2]={0,0};

    protected:
        friend class gameJudge;
        void setWinner(sign winningPlayer){
            winner=winningPlayer;
        }
    public:

        gameRule(int new_size, int new_length){
            if(new_size>=3){fieldSize=new_size;};
            if(new_length<=fieldSize && new_length>2){
                winLength=new_length;
            };
        }


        int getSize(){
            return fieldSize;
        }

        int getWinLength(){
            return winLength;
        }

        sign get_winner(){
            return winner;
        }

        void toggleAI(sign player){
            if(player-1>=0 && player-1 <2){
                if(isAI[player-1]==1){
                    isAI[player-1]=0;
                }else{ 
                    isAI[player-1]=1;
                };
            };
        }

        int * playersAI(){
            return isAI;
        }

        void setDraw(){
            draw=1;
        }

        int isDraw(){
            return draw;
        }
};

/*!
\brief Klasa sędziego gry, kontrolująca postęp rozgrywki
*/
class gameJudge{
    private:
        gameField * field=nullptr;
        gameRule * rules=nullptr;
        int whichTurn=1;
        sign currentPlayer=circle;
        list<savedMove> lastMoves;

    public:
        gameJudge(gameRule * new_rules){
            if(new_rules!=nullptr){
                rules=new_rules;
                field=new gameField(rules->getSize());
            };
        }

        ~gameJudge(){
            if(field!=nullptr){
                delete field;
            };
        }



        int isWinner(){
            savedMove move;
            if(lastMoves.Size()>0){
                move=lastMoves[0]->value();
            }else{
                return 0;
            };
            int dx=0;
            int dy=0;
            sign reference=field->getField(move.pos_x,move.pos_y);
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
                        if(current_x>=0 && current_x<rules->getSize() && current_y>=0 && current_y<rules->getSize()){
                            if(field->getField(current_x,current_y)!=reference){
                                stopped=1;
                            }else{
                                sum++;
                            };
                        }else{
                            stopped=1;
                        };
                    };
                };
                if(sum>=rules->getWinLength()){
                    return 1;
                }
                
            };
            return 0;
        }

        int putSign(int pos_x, int pos_y){
            savedMove new_move(pos_x,pos_y);
            if(pos_x<rules->getSize() && pos_y<rules->getSize()){
                field->putSign(currentPlayer,pos_x,pos_y);
                lastMoves.insertFirst(new_move);
                whichTurn++;
                if(currentPlayer==circle){
                    currentPlayer=cross;
                }else if(currentPlayer==cross){
                    currentPlayer=circle;
                };
                return 0;
            }else{
                return 1;
            }
        }

        int makeMove(int pos_x, int pos_y){
            savedMove new_move(pos_x,pos_y);
            if(putSign(pos_x,pos_y)==0){
                if(isWinner()){
                     if(currentPlayer==circle){
                        currentPlayer=cross;
                    }else if(currentPlayer==cross){
                        currentPlayer=circle;
                    };
                    rules->setWinner(currentPlayer);
                };
                if(field->isFull()){
                    rules->setDraw();
                }
                return 0;
            }else{
                return 1;
            };

        }

        void undo(){
            if(whichTurn>1){
            savedMove toUndo=lastMoves[0]->value();
            lastMoves.removeFirst();
            field->putSign(blank,toUndo.pos_x,toUndo.pos_y);
            if(currentPlayer==circle){
                currentPlayer=cross;
            }else if(currentPlayer==cross){
                currentPlayer=circle;
            };
            whichTurn--;
            };
        }

        void displayField(){
            if(field!=nullptr){
            field->displayTerminal();
            };
        }

        sign player(){
            return currentPlayer;
        }

        gameField * shareField(){
            return field;
        }

        int * playersAI(){
            return rules->playersAI();
        }

        void toggleAI(sign player){
            rules->toggleAI(player);
        }

        sign get_winner(){
            return rules->get_winner();
        }

        int getWinLength(){
            return rules->getWinLength();
        }

        int turnNumber(){
            return whichTurn;
        }

        int isDraw(){
            return rules->isDraw();
        }

        int getSize(){
            return rules->getSize();
        }



};
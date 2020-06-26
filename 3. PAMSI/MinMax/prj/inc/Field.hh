/*!
   \file Field.hh
   \brief Plik modelujący klasę pola gry oraz zapamiętujący ruchy
   \author Patryk Szydlik
   \date 25.05.20
 */

#pragma once

#include <iostream>
using namespace std;
/*!
\brief Ponumerowanie wartości danego znaku w polu 
*/
enum sign {blank, circle, cross};

/*!
\brief Klasa przechoujaca stan pola gry
*/
class gameField{
    private:
        int usedSpace=0;
        sign ** fields=nullptr;
    public:
        int size=0;

        gameField(int new_size){
            usedSpace=0;
            if(new_size >= 3){
                size=new_size;
            }else{
                size=3;
            };
            fields=new sign * [size];
            for(int i=0;i<size;i++){
                fields[i]=new sign [size];
                for(int j=0;j<size;j++){
                    fields[i][j]=blank;
                };
            };
        }

        ~gameField(){
            if(fields!=nullptr){
                for(int i=0;i<size;i++){
                    if(fields[i]!=nullptr){
                        delete[] fields[i];
                    };
                };
                delete[] fields;
            };
        }

        int putSign(sign new_sign, int pos_x, int pos_y){
            
            if(pos_x<size && pos_y<size){
                if(fields[pos_x][pos_y]!=blank){
                    usedSpace--;
                    fields[pos_x][pos_y]=new_sign;
                }else{
                    fields[pos_x][pos_y]=new_sign;
                    usedSpace++;        
                };
            }else{
                return 1;
            };

            
            return 0;
        }

        sign getField(int x, int y){
            return fields[x][y];
        }

        void displayTerminal(){
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    cout<<" ";
                    if(fields[i][j]==blank){
                        cout<<" ";
                    }else if(fields[i][j]==circle){
                        cout<<"o";
                    }else if(fields[i][j]==cross){
                        cout<<"x";
                    };
                    if(j<size-1){
                    cout<<" |";
                    };
                }
                cout<<"\n";
                if(i<size-1){
                    for(int j=0; j<size; j++){ 
                        cout<<"---";
                        if(j<size-1){
                            cout<<"|";
                        }
                    };
                    cout<<"\n";
                };
            };
        }

        int isFull(){
            if(usedSpace>=size*size){
                return 1;
            }else{
                return 0;
            }
        }

        int freeFields(){
            return size*size-usedSpace;
        }

};
/*!
   \file GUI.hh
   \brief Plik modelujący wygląd oraz funkcję obsługujące User Interface
   \author Patryk Szydlik
   \date 25.05.20
 */

#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Judge.hh>
#include <sstream>
#include <string>

using namespace sf;

Color backgroundColor(112,75,129,170);
Color fieldColor(234, 235, 198,255);
Color borderColor(77, 49, 77,255);
Color winningTrophyColor(219, 191, 31,250);


/*!
\brief Klasa interfejsu graficznego, wyswietlajaca zawartosc i kontrolujaca
*/
class graphicalUserInterface{
 
  gameField * fieldToDraw=nullptr;
  gameJudge * current_game=nullptr;
  float map_size;

  ContextSettings settings;
  RectangleShape gameWindow;
  Font font;
  Text tittle;
  RectangleShape titleFrame;
  Text signature;
  Text gameData;

  int koniec=0;

  public:
   RenderWindow window;
  private:



  void drawCircle(int x, int y){
    float radius=(map_size-10.0)*4.0/(10.0*fieldToDraw->size);
    CircleShape circle;
    circle.setRadius(radius);
    circle.setFillColor(fieldColor);
    if(fieldToDraw->size>10){
      circle.setOutlineThickness(2.f);
    }else{
    circle.setOutlineThickness(5.f);
    }
    circle.setOutlineColor(borderColor);
    circle.setOrigin(radius,radius);
    circle.setPosition(x,y);

    window.draw(circle);
  }

  void drawCross(int x, int y){
    float width=(map_size-10.0)*4.0/(5.0*fieldToDraw->size);
    float crossLength = (7.0*width)/5.0;
    float depth;

    if(fieldToDraw->size>10){
      depth=2;
    }else{
      depth=5;
    }

    RectangleShape line(sf::Vector2f(crossLength, depth));
    line.setFillColor(borderColor);
    line.setOrigin(crossLength/2, depth/2);
    line.rotate(45.f);
    line.setPosition(x,y);
    window.draw(line);
    line.rotate(90.f);
    window.draw(line);

    
  }

  void drawEmptySpace(int x, int y, int hover){
    float size=map_size;
    float width=(size)/(fieldToDraw->size)-4.0;
    RectangleShape box(sf::Vector2f(width, width));

    if(hover==1){
      box.setFillColor(winningTrophyColor);
    }else{
      box.setFillColor(fieldColor);
    }

    if(fieldToDraw->size>19){
      box.setOutlineThickness(0.5);
    }else{
      box.setOutlineThickness(2.f);
    };
    
    box.setOutlineColor(borderColor);
    box.setOrigin(width/2, width/2);
    box.setPosition(x,y);
    window.draw(box);
  }

  void drawField(int mouse_x, int mouse_y){
    float x_offset=10.0;
    float y_offset=10.0;
    float diff=(map_size)/(fieldToDraw->size);
    float current_x;
    float current_y;

    float cellWidth=(map_size)/(fieldToDraw->size);
    int offset=15;
    int chosen_j=-1;
    int chosen_i=-1;
    if(mouse_x>15 && mouse_x < map_size+15 && mouse_y>15 && mouse_y < map_size+15 ){
      chosen_j = (mouse_x-offset)/cellWidth;
      chosen_i = (mouse_y-offset)/cellWidth;
    };


    sign temp;
    for(int i=0; i<fieldToDraw->size;i++){
      current_y=y_offset+i*diff+diff/2;
      for(int j=0; j<fieldToDraw->size;j++){
        current_x=x_offset+j*diff+diff/2;
        temp=fieldToDraw->getField(i,j);
        if(i==chosen_i && j==chosen_j && temp==blank && !koniec){
          drawEmptySpace(current_x,current_y,1);
        }else{
          drawEmptySpace(current_x,current_y,0);
        };
        if(temp==circle){
          drawCircle(current_x,current_y);
        }else if(temp==cross){
          drawCross(current_x,current_y);
        }
      };
    };
  }

  void showPlayerData(int mouse_x,int mouse_y){
    Text playerData;
    float x_pos=window.getSize().x-(window.getSize().y/2)-map_size/10;
    float y_pos=window.getSize().y/4+map_size/5;
    float font_size=map_size/20;


    playerData.setFont(font);
    playerData.setCharacterSize(font_size);
    playerData.setFillColor(fieldColor);
    playerData.setStyle( Text::Bold);
    playerData.setOrigin(0,0);
    

    CircleShape player_1;
    player_1.setRadius(font_size/2);
    player_1.setFillColor(backgroundColor);
    player_1.setOutlineThickness(4.f);
    player_1.setOutlineColor(borderColor);
    player_1.setOrigin(font_size/2,font_size/2);
    player_1.setPosition(x_pos+(font_size*5),y_pos+2*font_size/3);

    if(current_game->player()==circle){
      playerData.setFillColor(winningTrophyColor);
      playerData.setStyle( Text::Bold | Text::Underlined);
      player_1.setOutlineColor(winningTrophyColor);
    }else{
      playerData.setFillColor(fieldColor);
      player_1.setOutlineColor(fieldColor);
      playerData.setStyle( Text::Bold);
    }
    playerData.setString("Player 1");
    playerData.setPosition(x_pos,y_pos);
    window.draw(playerData);
    window.draw(player_1);



    float width=font_size;
    float crossLength = (7.0*width)/5.0;

    RectangleShape player_2(sf::Vector2f(crossLength, 5.f));
    player_2.setFillColor(fieldColor);
    player_2.setOrigin(crossLength/2, 2.5);
    player_2.rotate(45.f);
    player_2.setPosition(x_pos+(5*font_size),y_pos+2*font_size/3+font_size*2);
    if(current_game->player()==cross){
      playerData.setFillColor(winningTrophyColor);
      playerData.setStyle( Text::Bold | Text::Underlined);
      player_2.setFillColor(winningTrophyColor);
    }else{
      playerData.setFillColor(fieldColor);
      playerData.setStyle( Text::Bold);
      player_2.setFillColor(fieldColor);
    }
    playerData.setString("Player 2");
    playerData.setPosition(x_pos,y_pos+2*font_size);
    window.draw(playerData);
    window.draw(player_2);
    player_2.rotate(90.f);
    window.draw(player_2);


    playerData.setString("AI");

    float textAI_x=x_pos-2*font_size;
    float textAI_y=y_pos;
    float boxSize=font_size*3/2;
    
    if(mouse_x > textAI_x && mouse_x < textAI_x+boxSize && mouse_y > textAI_y && mouse_y < textAI_y+boxSize ){
      playerData.setFillColor(winningTrophyColor);
    }else if(current_game->playersAI()[circle-1]==1){
      playerData.setFillColor(Color::Red);
      playerData.setStyle( Text::Bold | Text::Underlined);
    }else{
      playerData.setFillColor(borderColor);
      playerData.setStyle( Text::Bold);
    }

    
    playerData.setPosition(textAI_x,textAI_y);
    window.draw(playerData);

    textAI_x=x_pos-2*font_size;
    textAI_y=y_pos+2*font_size;

    if(mouse_x > textAI_x && mouse_x < textAI_x+boxSize && mouse_y > textAI_y && mouse_y < textAI_y+boxSize){
      playerData.setFillColor(winningTrophyColor);
    }else if(current_game->playersAI()[cross-1]==1){
      playerData.setFillColor(Color::Red);
      playerData.setStyle( Text::Bold | Text::Underlined);
    }else{
      playerData.setFillColor(borderColor);
      playerData.setStyle( Text::Bold);
    }

    playerData.setPosition(textAI_x,textAI_y);
    window.draw(playerData);


   


  }

  void showGameData(int mouse_x,int mouse_y){
    stringstream ss;
    ss << "Map size "<< fieldToDraw->size <<"x"<< fieldToDraw->size <<"\n"<<current_game->getWinLength()<<" to win\nTurn : "<<current_game->turnNumber();
    string tekst = ss.str();

    gameData.setString(tekst);
    window.draw(gameData);

    RectangleShape undoButton;
    Text undoText;

    undoText.setString("Undo");
    undoText.setFont(font);
    undoText.setCharacterSize(map_size/20);
    undoText.setStyle(Text::Style::Bold);

    float width=map_size/10;
    float height=map_size/20;
    undoText.setOrigin(width/2,height*3/4);

    undoButton.setSize(Vector2f(width*2,height*3/2));
    undoButton.setOrigin(width,height*3/4);
   

    float x_pos=window.getSize().x-(window.getSize().y/2)-map_size/10+map_size/12;
    float y_pos=window.getSize().y*4/5;

    if(mouse_x>x_pos-width && mouse_x<x_pos+width && mouse_y>y_pos-height && mouse_y<y_pos+height){
      undoText.setFillColor(fieldColor);
      undoButton.setFillColor(winningTrophyColor);
    }else{
      undoText.setFillColor(borderColor);
      undoButton.setFillColor(fieldColor);
    }
   

    undoText.setPosition(x_pos,y_pos);
    undoButton.setPosition(x_pos,y_pos);
    window.draw(undoButton);
    window.draw(undoText);
  }

  void drawEndGame(sign winner){
   
    RectangleShape final_window;
    final_window.setSize(sf::Vector2f(window.getSize().x*2/3,window.getSize().y/3));
    final_window.setFillColor(borderColor);
    final_window.setOutlineThickness(5.f);
    final_window.setOutlineColor(winningTrophyColor);
    final_window.setOrigin(window.getSize().x/3,window.getSize().y/6);
    final_window.setPosition(window.getSize().x/2 , window.getSize().y/2);

    window.draw(final_window);

    Text game_over;
    game_over.setFont(font);
    game_over.setCharacterSize(map_size/10);
    game_over.setFillColor(winningTrophyColor);
    game_over.setStyle(sf::Text::Bold | Text::Underlined);
    game_over.setPosition(window.getSize().x/2 , window.getSize().y/2);


    if(winner==blank){
      game_over.setString("IT'S A DRAW");
      game_over.setOrigin(map_size*2.5/10,map_size/10);
    }else if(winner==circle){
      game_over.setString("PLAYER 1 HAVE WON");
      game_over.setOrigin(map_size*4.5/10,map_size/10);
    }else if(winner==cross){
      game_over.setString("PLAYER 2 HAVE WON");
      game_over.setOrigin(map_size*4.5/10,map_size/10);
    }

    window.draw(game_over);

  }


  public:

 


  graphicalUserInterface(int screenWidth, int screenHeight, int antialiasing, gameJudge * game){
    fieldToDraw=game->shareField();
    current_game=game;

    settings.antialiasingLevel = antialiasing;
    font.loadFromFile("./graphics/DancingScript-Regular.otf");
    
    window.create(VideoMode(screenWidth, screenHeight), "TIK TAK TOE by Patryk Szydlik", sf::Style::Titlebar | sf::Style::Close , settings);
    window.setFramerateLimit(60);
    
    gameWindow.setSize(sf::Vector2f(screenHeight, screenHeight));
    gameWindow.setFillColor(borderColor);
    gameWindow.setOrigin(0,0);
    gameWindow.setPosition(0,0);
    map_size=screenHeight-20;
   

    tittle.setFont(font);
    tittle.setString("TIK TAK TOE");
    tittle.setCharacterSize(screenHeight/10);
    tittle.setFillColor(fieldColor);
    tittle.setStyle(sf::Text::Bold);
    tittle.setOrigin(screenHeight*5/20,screenHeight/20);
    tittle.setPosition(screenWidth*3/4+20,screenHeight/20+15);

    titleFrame.setSize(sf::Vector2f(screenHeight*5/10+60, screenHeight/10+20));
    titleFrame.setFillColor(backgroundColor);
    titleFrame.setOutlineThickness(5.f);
    titleFrame.setOutlineColor(borderColor);
    titleFrame.setOrigin(screenHeight*5/20+30,screenHeight/20+10);
    titleFrame.setPosition(screenWidth*3/4+20, screenHeight/20+25);

    signature.setFont(font);
    signature.setString("PAMSI Projekt 3 by Patryk Szydlik ind 248949");
    signature.setCharacterSize(screenHeight/40);
    signature.setFillColor(fieldColor);
    signature.setStyle( Text::Italic);
    signature.setOrigin(0,screenHeight/30);
    signature.setPosition(screenWidth-44*screenHeight/80,screenHeight-10);


    std::string napis;
    gameData.setFont(font);
    gameData.setCharacterSize(screenHeight/20);
    gameData.setFillColor(fieldColor);
    gameData.setStyle(sf::Text::Bold);
    gameData.setOrigin(screenHeight*5/20,screenHeight/20);
    gameData.setPosition(window.getSize().x-(window.getSize().y/2)-(map_size/10)+(5*map_size/20),screenHeight/4);
  }

  


  void refresh(int mouse_x, int mouse_y){
    window.clear(backgroundColor);
    window.draw(gameWindow);
    window.draw(titleFrame);
    window.draw(tittle);
    window.draw(signature);
    drawField(mouse_x, mouse_y);
    showPlayerData(mouse_x, mouse_y);
    showGameData(mouse_x, mouse_y);

    if(current_game->get_winner()!=blank){
      koniec=1;
      drawEndGame(current_game->get_winner());

    }else if(fieldToDraw->isFull()){
      drawEndGame(blank);
    }
    

    window.display();
  }

  void click(int x, int y){
    if(koniec){

    }else{
      int min_x,max_x,min_y,max_y;

      // player 1 toggle AI

      min_y=window.getSize().y/4+map_size/5;
      max_y=min_y+map_size/20+10;

      min_x=window.getSize().x-(window.getSize().y/2)-map_size/10-map_size/10;
      max_x=min_x+map_size/20+10;

      if(x>min_x && x<max_x && y<max_y && y>min_y){
        current_game->toggleAI(circle);
      }



      // player 2 toggle AI

      min_y=window.getSize().y/4+map_size/5+map_size/10;
      max_y=min_y+map_size/20+map_size/10+10;

      min_x=window.getSize().x-(window.getSize().y/2)-map_size/10-map_size/10;
      max_x=min_x+map_size/20+10;

      if(x>min_x && x<max_x && y<max_y && y>min_y){
        current_game->toggleAI(cross);
      }

      // choosing where to put sign
      if(current_game->playersAI()[current_game->player()-1]==0){
        float cellWidth=(map_size)/(fieldToDraw->size);
        int offset=15;
        if(x>15 && x < map_size+15 && y>15 && y < map_size+15 ){
          int j = (x-offset)/cellWidth;
          int i = (y-offset)/cellWidth;
          if(fieldToDraw->getField(i,j)==blank){
            current_game->makeMove(i,j);
          };
        };
      };

      // undo
      
      if(current_game->playersAI()[current_game->player()-1]==0){
        float x_pos=window.getSize().x-(window.getSize().y/2)-map_size/10+map_size/12;
        float y_pos=window.getSize().y*4/5;
        float width=map_size/10;
        float height=map_size/20;
        if(x>x_pos-width && x<x_pos+width && y>y_pos-height && y<y_pos+height){
          current_game->undo();
          if(current_game->playersAI()[current_game->player()-1]==1){
            current_game->undo();
          };
        };
      };
    };
  };
};
/*!
   \file main.cpp
   \brief Glowny plik zawierajacy wywolanie menu i funkcji zewnetrznych
   \author Patryk Szydlik
   \date 25.05.20
 */
#include <iostream>
#include <Field.hh>
#include <Judge.hh>
#include <AI.hh>
#include <GUI.hh>


using namespace sf;
using namespace std;

int main()
{
    int size;
    int length;
    int zla_wartosc=0;
    do{
        zla_wartosc=0;
        if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n' );
        };
        cout<<"\n Podaj rozmiar planszy z przedzialu 3-50:\n";
        cin>>size;
        if(cin.fail() || size>50 || size<3){
            cout<<" Niepoprawna wartość.\n";
            zla_wartosc=1;
        };
    }while(cin.fail() || zla_wartosc );

    do{
        zla_wartosc=0;
         if(cin.fail()){
            cin.clear();
            cin.ignore(1000, '\n' );
        };
        //cin.ignore();
        cout<<"\n Podaj długość wygrywającą z przedzialu 3-"<<size<<":\n";
        cin>>length;
        if(cin.fail() || length>size || length<3){
            cout<<" Niepoprawna wartość.\n";
            zla_wartosc=1;
        };
    }while(cin.fail() || zla_wartosc);

    gameRule used_rules(size,length);
    gameJudge new_game(&used_rules);
    graphicalUserInterface game(960,540,8,&new_game);
    AI artificialOpponent(& new_game);

    bool exit=0;
    int mouse_pos_x;
    int mouse_pos_y;

    int mouse_click_x;
    int mouse_click_y;

    while(!exit){
        while (game.window.isOpen())
        {
            Event event;
            while (game.window.pollEvent(event)){
                if (event.type == Event::Closed){
                    game.window.close();
                    exit=1;
                };

                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        mouse_click_x=event.mouseButton.x;
                        mouse_click_y=event.mouseButton.y;
                        game.click(mouse_click_x,mouse_click_y);
                    };
                };

                if (event.type == sf::Event::MouseMoved){
                    mouse_pos_x=event.mouseMove.x;
                    mouse_pos_y=event.mouseMove.y;
                }


            };
            if(new_game.get_winner()!=blank || new_game.isDraw()){

            }else if(new_game.playersAI()[new_game.player()-1]==1){
                artificialOpponent.makeMove(new_game.player());
            };
            game.refresh(mouse_pos_x,mouse_pos_y);
        };
    };
    
    return 0;
}
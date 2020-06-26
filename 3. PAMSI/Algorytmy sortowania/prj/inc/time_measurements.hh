/*!
   \file time_measurements.hh
   \brief Zawiera klase służącą do przechowywania danych o czasie trwania
   \author Patryk Szydlik
   \date 22.03.2020
 */
#pragma once


/*!
\brief Klasa time_measure przechowująca wartości mierzonego czasu

Obsługuje zakres w godzinach, minutach, sekundach, milisekundach i mikrosekundach.
*/
class time_measure{
    private:
    int hours;      /*!< ilość godzin */
    int minutes;    /*!< ilość minut*/
    int seconds;    /*!< ilość sekund*/
    int mseconds;   /*!< ilość milisekund*/
    int useconds;   /*!< ilość mikrosekund*/
    public:

/*!
\brief Konstruktor domyślny z zerowymi wartościami poczatkowymi
*/
    time_measure(){
        hours=0;
        minutes=0;
        seconds=0;
        mseconds=0;
        useconds=0;
    }

/*!
\brief Konstruktor z zadanymi wartościami początkowymi
\param[in] new_hours - początkowa liczba godzin
\param[in] new_minutes - początkowa liczba minut
\param[in] new_seconds - początkowa liczba sekund
\param[in] new_mseconds - początkowa liczba milisekund
\param[in] new_useconds - początkowa liczba mikrosekund
*/
  
    time_measure(int new_hours,int new_minutes,int new_seconds,int new_mseconds, int new_useconds){
        hours=new_hours;
        minutes=new_minutes;
        seconds=new_seconds;
        mseconds=new_mseconds;
        useconds=new_useconds;
        update_time();
    }

/*!
\brief Konstruktor kopiujący
\param[in] copied_time - dane do skopiowania
*/
    time_measure(const time_measure &copied_time){
        hours=copied_time.hours;
        minutes=copied_time.minutes;
        seconds=copied_time.seconds;
        mseconds=copied_time.mseconds;
        useconds=copied_time.useconds;
    }

/*!
\brief Funkcja sprawdza przepełnienie zmiennych

W przypadku gdy wartości niższego rzędu są przepełnione to funkcja przypisuje wartość do wyższej zmiennej.
Np. gdy jest ponad 60 sekund to dopisuje 1 minutę więcej i zmienia wartość sekund do zakreso 0-60
*/
    void update_time(){
        if(useconds>=1000){
            mseconds+=useconds/1000;
            useconds=useconds%1000;
        };
        if(mseconds>=1000){
            seconds+=mseconds/1000;
            mseconds=mseconds%1000;
        };
        if(seconds>=60){
            minutes+=seconds/60;
            seconds=seconds%60;
        };
        if(minutes>=60){
            hours+=minutes/60;
            minutes=minutes%60;
        };
    }
/*!
\brief Funkcja dodawania mikrosekund do mierzonego czasu

\param[in] new_useconds - ilość mikrosekund do dodania

*/
    void add_useconds(int new_useconds){
        useconds+=new_useconds;
        update_time();
    }
/*!
\brief Funkcja dodawania milisekund do mierzonego czasu

\param[in] new_mseconds - ilość milisekund do dodania

*/
    void add_mseconds(int new_mseconds){
        mseconds+=new_mseconds;
        update_time();
    }
/*!
\brief Funkcja dodawania sekund do mierzonego czasu

\param[in] new_seconds - ilość sekund do dodania

*/
    void add_seconds(int new_seconds){
        seconds+=new_seconds;
        update_time();
    }

/*!
\brief Funkcja do wyświetlania zmierzonego czasu
*/
    void display(){
        if(hours){std::cout<<hours<<" h ";};
        if(minutes){std::cout<<minutes<<" min ";};
        if(seconds){std::cout<<seconds<<" sec ";};
        if(mseconds){std::cout<<mseconds<<" msec ";};
        std::cout<<useconds<<" usec ";
    }

/*!
\brief Funkcja do wyświetlania zmierzonego czasu w ms
*/
    void display_ms(){
        float time_in_ms=useconds/1000 + mseconds + seconds*1000 + minutes*60000 + hours*3600000;
       std::cout<<time_in_ms<<"\n";
    }
/*!
\brief Funkcja zeruje zapisaną wartość czasu
*/
    void reset(){
        hours=0;
        minutes=0;
        seconds=0;
        mseconds=0;
        useconds=0;
    }
};
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>

#ifdef __GNUG__
#pragma implementation
#endif

#include "gnuplot_link.hh"

using namespace std;

const int STDIN = 0;
const int STDOUT = 1;

namespace PzG {


 std::list<FileInfo>  GnuplotLink::files_information_;



 void GnuplotLink::ShowErrorMessages( bool mode )
 {
  display_error_messages_ = mode;
 }


  GnuplotLink::~GnuplotLink() 
  {}


 bool GnuplotLink::SendToGnuplot(const char *command)
 {
  int string_length = strlen(command);
  int characters_sent;
  
  while (((characters_sent = write(gnuplot_input_,command,string_length)) != -1)
          && string_length > 0) {
    command += characters_sent;
    string_length -= characters_sent;
  }
  if (string_length > 0) {
    ErrorMessage("!!! Przeslanie polecenia do GNUPlota nie powiodlo sie.");
    return false;
  }
  return true;
 }




 GnuplotLink::GnuplotLink() 
 { 
   show_OX_axis_ = show_OY_axis_ = show_OZ_axis_ = true;

   drawing_mode_ = DM_2D;
   ShowErrorMessages();
   gnuplot_output_ = gnuplot_input_ = -1; 
   SetRangeX(-350,350);
   SetRangeY(-350,350);
   SetRangeZ(-200,200);
   SetRotationXZ(60,30);
   SetScaleXZ(1,1);
 }




 bool FileExists(char const *filename)
 {
  struct stat buf;

  if (stat(filename,&buf)) return false;
  if (!(S_ISREG(buf.st_mode))) return false;
  if (!(buf.st_mode & S_IRUSR)) return false;
  return true;
 }




 //-------------------------------------------------------------------------
 // Powoduje dodanie do listy plikow zawierajacych dane dla gnuplota,
 // nowej nazwy pliku.
 //
 // PRE:  filename  - nazwa pliku z danymi dla gnuplota.
 // POST:
 //  Zwraca wartosc:
 //     true - jezeli istnieje plik o nazwie zawartej w zmiennej filename.
 //             Zostaje on ponadto dodany do listy plikow z danymi 
 //             dla gnuplota.
 //    fasle - Jezeli nie istnieje plik o nazwie zawartej w zmiennej
 //            filename. Zadne dodatkowe dzialanie nie jest realizowane.
 //
 bool GnuplotLink::AddFilename( const char      * filename,
                                        LineStyle   style,
                                        int               width
                                      )
 {
  bool result = true;

  if (!FileExists(filename)) {
    string command = "!!! Ostrzezenie: Brak pliku ";
    command += filename;
    //TMP    ErrorMessage(command.c_str());
    result = false;
  }

  files_information_.push_back(FileInfo(filename,style,width));
  return result;
 }


 //-------------------------------------------------------------------------
 // Informuje, czy połączenie z programem gnuplot zostało zainicjowane.
 // 
 bool GnuplotLink::IsConnectionInitialized() const
 {
  return gnuplot_input_ > -1 && gnuplot_output_ > -1;
 }


 void GnuplotLink::ErrorMessage(const char *command) const
 {
  if (!AreErrorMessagesDisplayed()) return;
  cerr << command << endl;
 }


const int LINE_LENGTH  = 120;



 bool GnuplotLink::Init()
 {
  if (IsConnectionInitialized()) return true;
  if (!CreateChildProcess()) return false;

  return SendToGnuplot("\n");
 }


/*!
 *  Inicjalizuje połączenie z programem \e gnuplot. Realizowane jest to
 *  poprzez rozwidlenie procesu i uruchomienie jako procesu potomnego
 *  programu \e gnuplot. Komunikacja z programem \e gnuplot realizowana jest
 *  poprzez przejęcie jego wejścia i wyjścia standardowego.
 *
 *  \retval true - gdy połączenie z programem \e gnuplot zostało poprawnie
 *               zainicjalizowane lub gdy już wcześniej było 
 *               zainicjalizowane.
 *  \retval false - gdy proces inicjalizacji połączenia zakończył się
 *               niepowodzeniem.
 */
 bool GnuplotLink::CreateChildProcess()
 {
  int input_descriptor[2],output_descriptor[2];

  if (pipe(input_descriptor) == -1 || pipe(output_descriptor) == -1) {
    ErrorMessage(
      "### Niemozliwe utworzenie kanalow komunikacyjnych do podprocesow.");
    exit(1);
  }

  switch (fork()) {
    case -1: ErrorMessage("### Niemozliwe rozwidlenie procesu.");
             exit(1);
    case  0: 
       /* Start potomka */

       if (close(STDIN) == -1) { 
         ErrorMessage("### Blad przy zamykaniu strumienia wejsciowego.");
         exit(1);
       }
       if (dup(output_descriptor[STDIN]) == -1) {
         ErrorMessage("### Blad duplikacji kanalu wejsciowego.");  
         exit(1);
       }
       
       if (close(STDOUT) == -1) { 
         ErrorMessage(
            "### Blad zamkniecia kanalu standardowego kanalu wyjsciowego."); 
         exit(1);
       }
       if (dup(input_descriptor[STDOUT]) == -1) {
         ErrorMessage("### Blad duplikacji kanalu wyjsciowego.");  
         exit(1);
       }       
       if (close(output_descriptor[STDIN]) == -1) {
         ErrorMessage("### Blad zamkniecia kanalu wejsciowego.");
         exit(1);
       }
       if (close(output_descriptor[STDOUT]) == -1) {
         ErrorMessage("### Blad zamkniecia kanalu wyjsciowego.");
         exit(1);
       }
       if (close(input_descriptor[STDIN]) == -1) {
         ErrorMessage("### Blad zamkniecia duplikatu kanalu wejsciowego.");
         exit(1);
       }
       if (close(input_descriptor[STDOUT]) == -1) {
         ErrorMessage("### Blad zamkniecia duplikatu kanalu wyjsciowego.");
         exit(1);
       }
       char buffer[3];
       read(STDIN,buffer,1);
       write(STDOUT,"\n",1); 
       const char *command;

       execlp(command = "gnuplot","gnuplot",NULL);

       ErrorMessage("!!! Blad:"); 
       ErrorMessage("!!! W procesie potomnym nie mogl zostac."); 
       ErrorMessage("!!! uruchomiony program gnuplot."); 
       ErrorMessage("!!! Nastapilo przerwanie dzialania procesu potomnego."); 
       ErrorMessage("!!! Jednym z mozliwych powodow problemu moze byc"); 
       ErrorMessage("!!! Brak programu gnuplot w szukanej sciezce."); 
       ErrorMessage("!!! Do uruchomienia programu gnuplot bylo uzyte polecenie:");
       ErrorMessage(command);
       exit(1);

    default:
       if (close(output_descriptor[STDIN]) == -1 || close(input_descriptor[STDOUT]) == -1) { 
         ErrorMessage(" Blad zamkniecia outpipe[STDIN], inpipe[STDOUT]."); 
       }

       fcntl(input_descriptor[STDIN],F_SETFL,O_NDELAY);
       gnuplot_output_  = input_descriptor[STDIN];
       gnuplot_input_ =  output_descriptor[STDOUT];
  }
  return true;
 }




 bool GnuplotLink::DrawToFile(const char *filename)
 {
  if (!IsConnectionInitialized()) {
    if (!Init()) return false;
  }
  string command = "\n\n\nset output '";
  command += filename;
  command += "\n set term png\n";
  if (!SendToGnuplot(command.c_str())) {
    ErrorMessage("!!! Rysunek nie moze byc utworzony.");
    return false;
  }

  bool result = Draw();
  if (!SendToGnuplot("\n\n\nset output \nset term x11\n")) {
    ErrorMessage("!!! Wyjscie dla gnuplot'a nie zostalo poprawnie\n"
                   "!!! przestawione na STDOUT.\n");
    return false;
  }
  return result;
 }



/*!
 * Tworzy napis będący parametrami dla polecenie \e plot programu,
 * \e gnuplot. Parametry te pozwalają na rysowanie brył, których
 *  współrzędne wierzchołków zawarte są w plikach.
 *  Nazwy tych plików muszą być wcześniej dołączone do kolejki 
 *  plików poprzez zastosowanie polecenia
 *   \link GnuplotLink::DodajNazwe DodajNazwe\endlink.
 *  
 * \param command - dopisywana jest do niego sekwencja znaków
 *                  tworzących parametry dla polecenia \e plot.
 * \param separator - zawiera znak separatora między poszczególnymi
 *              parametrami. Jeżeli parametry listy nazw plików
 *              są generowane jako pierwsze, to zmienna ta musi 
 *              być wskaźnikiem do wskaźnika na łańcuch: " ".
 * \retval true - jeśli lista nazw plików nie jest pusta.
 * \retval false - w przypadku przeciwnym.
 * \post Jeżeli  lista nazw plików nie jest pusta, to poprzez
 *              parametr \e separator zostaje udostępniony łańcuch: ", ".
 */
 bool GnuplotLink::AddDrawingFromFiles( std::string  &command, 
                                                char const **separator 
                                             )
 {
  if (files_information_.empty()) return false;
  list<FileInfo>::const_iterator names = files_information_.begin();

  for (; names != files_information_.end(); ++names ) {
    //       OSStrm.empty();
       ostringstream OSStrm;
       command += *separator;
       command += " \'";
       command += names->GetFilename();
       ((command += '\'') += " notitle ") += 
       (names->GetStyle() == LS_CONTINUOUS ? " w l" : " w p pt 5");
       if  (names->GetStyle() == LS_CONTINUOUS) OSStrm << " lw " << names->GetWidth();
                                         else OSStrm << " ps " << names->GetWidth();
       command += OSStrm.str();
       *separator = ", ";
  }
  return true;
 }



 //-------------------------------------------------------------------------
 //  Jezeli lista plikow nie jest pusta, to generuje sekwencje polecen
 //  dla programu gnuplot majaca na celu narysowanie plaszczyzn na
 //  na podstawie danych zawartych w plikach z listy. 
 //
 //  PRE:  Na liscie plikow nie powinna byc pusta. Nazwy plikow na niej
 //        mozna umiescic za pomoca metody 'DodajNazwe'.
 //        Metoda nie wymaga wcześniejszego zainicjowania połączenia
 //        z gnuplotem.
 //  POST: true   - gdy zostaja poprawnie wyslane polecenia dla gnuplota.
 //                 Nie oznacza to jednak, ze proces rysowania zakończył
 //                 się pomyślnie.
 //       false   - gdy połączenie z gnuplotem nie moze zostac poprawnie
 //                 zainicjalizowane lub gdy lista plikow jest pusta.
 //
 bool GnuplotLink::Draw()
 {
  if (!IsConnectionInitialized()) {
    if (!Init()) return false;
  }

  string command;

  CreateCommandPreamble(command);

  char const *separator = "";
  bool is_drawing_recommended = AddFilesToDrawCommand(command,&separator);
  /*

  */
  is_drawing_recommended = AddDrawingFromFiles(command,&separator) || is_drawing_recommended;

  if (!is_drawing_recommended) return false;
  command += "\npause -1\n";
  string command2 = "/usr/bin/echo \"";
  command2 += command;
  command2 += "\" | gnuplot&";

  return SendToGnuplot(command.c_str());
 }



 void  GnuplotLink::CreateCommandPreamble(std::string &Preamble) const
 {
  switch (drawing_mode_) {
   case DM_2D: Create2DPreamble(Preamble); break;
   case DM_3D: Create3DPreamble(Preamble); break;
  }
 }



 void  GnuplotLink::Create2DPreamble(std::string &Preamble) const
 {
  Preamble.clear();
  Preamble.reserve(1000);
  Preamble = "\n\n";

  if (show_OX_axis_) Preamble += "set xzeroaxis lt 0 lw 1\n";
  if (show_OY_axis_) Preamble += "set yzeroaxis lt 0 lw 1\n";

  Preamble += SaveRangeSettings('x');
  Preamble += SaveRangeSettings('y');
  Preamble += "\nplot ";
 }



 void  GnuplotLink::Create3DPreamble(std::string &Preamble) const
 {
  Preamble.clear();
  Preamble.reserve(1000);
  Preamble = "\n\n"
                       "set parametric\n"
                       "set isosamples 9\n"
                       "set urange [-180:180]\n"
                       "set vrange [-90:90]\n";  

  if (show_OX_axis_) Preamble += "set xzeroaxis lt 0 lw 1\n";
  if (show_OY_axis_) Preamble += "set yzeroaxis lt 0 lw 1\n";
  if (show_OZ_axis_) Preamble += "set zzeroaxis lt 0 lw 1\n";

  Preamble += SaveRangeSettings('x');
  Preamble += SaveRangeSettings('y');
  Preamble += SaveRangeSettings('z');
  Preamble += SaveScaleRotationSettings();
  Preamble += "set hidden3d\nsplot ";
 }



std::string GnuplotLink::SaveRangeSettings(char axis) const
{
  ostringstream strm;
  float Min, Max;

  switch (axis) {
   case 'x':  Min = Xmin();  Max = Xmax();  break;
   case 'y':  Min = Ymin();  Max = Ymax();  break;
   case 'z':  Min = Zmin();  Max = Zmax();  break;
   default: cerr << "!!! Blad w 'SaveRangeSettings' niedozwolony"
                    " znak: " << axis << endl;
            return "";
  }
  strm << "set " << axis << "range [" <<  Min << ":" << Max << "]\n";
  return strm.str();
}



std::string GnuplotLink::SaveScaleRotationSettings() const
{
  ostringstream strm;
  strm << "set view " << RotationX() << "," << RotationZ() 
       << "," << ScaleX() << "," << ScaleZ() << endl;
  return strm.str();
}







 //-------------------------------------------------------------------------
 //  Metda usuwa ostatnia nazwe z listy nazw plikow.
 //
 void GnuplotLink::DeleteLastName()
 {
   list<FileInfo>::iterator names = files_information_.end();
   files_information_.erase(--names,files_information_.end());
 }



 //-------------------------------------------------------------------------
 //  Metda calkowicie kasuje zawartosc listy nazw plikow.
 //
 void GnuplotLink::DeleteAllNames()
 {
  files_information_.clear();
 }




} //___ Koniec przestrzeni nazw: PzG ____________________________________________

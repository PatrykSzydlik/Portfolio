#pragma once

#include <string>
#include <list>
#include <vector>

#ifdef __GNUG__
#pragma interface
#endif

/*!
 * \file  gnuplot_link.hh
 *  
 *  Plik zawiera definicję klasy realizującej interfejs
 *  komunikacyjny do programu gnuplot.
 */


/*!
 * \brief Moduł narzędzi umożliwiających połącznie z GNUPlotem
 *
 * Niniejsza przestrzeń nazw stanowi moduł logiczny zawierający
 * narzędzia umożliwiające realizację połączenia z programem \p gnuplot.
 */
namespace PzG {

  /*!
   * \brief Określa tryb rysowania realizowanego przez program \p gnuplot
   *
   *  Typ wyliczeniowy określające dopuszczalne tryby rysowania
   *  realizowanego przez program \p gnuplot. Wybór trybu wiąże się
   *  ze zmianą sposobu interpretacji danych zawartych pliku. Jeśli 
   *  np. wybrany zostanie tryb 2D, to zakłada się, że w każdej linii
   *  pliku z danymi znajdują się wartości współrzędnych \e x, \e y.
   *  Wartości typu:
   *   \li \p DM_2D - rysowanie w trybie 2D, co sprowadza się do 
   *                  rysowania wykresów funkcji jednej zmiennej.
   *   \li \p DM_3D - rysowanie w trybie 3D. Oznacza to możliwość
   *                  rysowania wykresów funkcji dwóch zmiennych.
   *                 
   */
  enum DrawingMode { DM_2D,  DM_3D };
  /*!
   * \brief Sposób rysowania linii
   * 
   * Określa sposób rysowania linii.
   */
  enum LineStyle { LS_CONTINUOUS, LS_SCATTERED }; 

  /*!
   * \brief Zestaw informacji dotyczący pliku i sposobu rysowania
   *
   * Klasa modeluje zestaw informacji dotyczący pliku i sposobu
   * w jaki mają być wizualizowane zawarte w nim dane.
   */
  class FileInfo {
    public:
     /*!
      * Inicjalizuje obiekt.
      *  \param filename - nazwa pliku, z którego pobierane będą dane,
      *  \param style - rodzaj rysowania linii,
      *  \param width - szerokosc linii.
      */
      FileInfo(std::string filename, LineStyle  style, int width)
      {
        filename_ = filename;
        style_ = style;
        width_ = width;
      }
     /*!
      * \brief Udostępia nazwę pliku do rysowania
      *
      * Udostępnia nazwę pliku z danymi do rysowania.
      */
      const std::string GetFilename() const { return filename_; }
     /*!
      * \brief Zmienia nazwę pliku do rysowania
      *
      * Zmienia nazwę pliku z danymi do rysowania.
      */
      void SetFilename(const std::string& filename) { filename_ = filename; }
     /*!
      * \brief Udostępnia sposób rysowanej linii
      *
      * Udostępnia informację o sposóbie rysowania linii.
      */
      LineStyle GetStyle() const { return style_; }
     /*!
      * \brief  Udostępnia informację o szerokości linii.
      *
      *  Udostępnia informację o szerokości rysowanej linii.
      */
      int GetWidth() const { return width_; }

    private:
    /*!
     * \brief Nazwa pliku z danymi do rysowania
     *
     * Nazwa pliku z danymi do rysowania.
     */
      std::string  filename_;
    /*!
     * \brief Szerokość użytego piórka
     *
     * Określa szerokość piórka, jakie ma być użyte
     * do rysowania obiektów graficznych.
     */
      int  width_;
    /*!
     * \brief Sposób rysowania danej linii
     *
     * Przechowuje informacje o sposobie rysowania linii.
     */
      LineStyle  style_;
  };


/*!
 * \brief  Klasa realizuje interfejs do programu GNUPlot.
 *
 * Klasa realizuje interfejs do programu GNUPlot. Pozwala ona na wskazanie
 * zbioru punktów płaszczyzn umieszczonych w pliku lub plikach.
 * Każdy taki zbiór może być następnie wizualizowany przez program 
 * gnuplot w postaci oddzielnych płaszczyzn z wycinaniem części zasłanianych.
 */
class GnuplotLink {
 protected:
  /*!
   * \brief Lista nazw plików z danymi dla \e gnuplota.
   *
   * Pole jest zarządcą listy nazw plików, z których są wczytywane
   * dane dotyczące rysowania obrysu brył przez program \e gnuplot.
   * Operacja ta wykonywana jest po wywołaniu polecenia.
   * \link GnuplotLink::Draw Draw\endlink.
   */
  static std::list<FileInfo>  files_information_;

   /*!
    *  Pole przechowuje deskryptor do wejścia standardowego uruchomionego
    *  programu gnuplot.
    */
  int gnuplot_input_;
   /*!
    *  Pole przechowuje deskryptor do weyjścia standardowego uruchomionego
    *  programu gnuplot.
    */
  int gnuplot_output_;
   /*!
    *  \brief Decyduje czy mają być wyświetlane komunikaty o błędach,
    *         czy też nie.
    *
    *  Wartość tego pola decyduje o tym czy komunikaty o błędach będą 
    *  wyświetlane na wyjście standardowe błędów (\b cerr), czy też nie.
    *   \li \p true - komunikaty będę wyświetlane,
    *   \li \p false -  komunikaty nie będę wyświetlane.
    */
  bool display_error_messages_;

  /*!
   * \brief Określa aktualny tryb rysowania
   *
   * Zawartość pola determinuje sposób rysowania, jaki zostanie 
   * wymuszony na programie \p gnuplot poprzez wysłanie do niego
   * odpowiednich poleceń. Wspomniane wymuszenie jest realizowane
   * poprzez wywołanie polecenia 
   * \link GnuplotLink::Draw Draw()\endlink
   */
  DrawingMode drawing_mode_;
   /*!
    *  \brief Dolny zakres wyświetlanej skali skali dla osi \e OX.
    *
    *  Określa dolny zakres wyświetlanej skali dla osi \e OX.
    */
  float  x_min_;
   /*!
    *  \brief Górny zakres wyświetlanej skali skali dla osi \e OX.
    *
    *  Określa górny zakres wyświetlanej skali dla osi \e OX.
    */
  float  x_max_;
   /*!
    *  \brief Dolny zakres wyświetlanej skali skali dla osi \e OY.
    *
    *  Określa dolny zakres wyświetlanej skali dla osi \e OY.
    */
  float  y_min_;
   /*!
    *  \brief Górny zakres wyświetlanej skali skali dla osi \e OY.
    *
    *  Określa górny zakres wyświetlanej skali dla osi \e OY.
    */
  float  y_max_;
   /*!
    *  \brief Dolny zakres wyświetlanej skali skali dla osi \e OZ.
    *
    *  Określa dolny zakres wyświetlanej skali dla osi \e OZ.
    */
  float  z_min_;
   /*!
    *  \brief Górny zakres wyświetlanej skali skali dla osi \e OZ.
    *
    *  Określa górny zakres wyświetlanej skali dla osi \e OZ.
    */
  float  z_max_;
   /*!
    *  Wartość tego pola definiuje skalowanie rysunku wzdłuż osi 
    *  \e OX (oś horyzontalna ekranu).
    */
  float  x_scale_;
   /*!
    *  Wartość tego pola definiuje skalowanie rysunku wzdłuż osi 
    *  \e OZ (oś wertykalna ekranu).
    */
  float  z_scale_;
   /*!
    *  Wartość tego pola definiuje rotację rysunku (zmiane punktu patrzenia)
    *  względem osi \e OX.
    */
  float  x_rotation_;
   /*!
    *  Wartość tego pola definiuje rotację rysunku (zmiane punktu patrzenia)
    *  względem osi \e OZ.
    */
  float  z_rotation_;

  /*!
   * \brief Czy oś OX ma być widoczna
   *
   * Przechowuje informację decydującą o tym czy oś OX będzie
   * widoczna na rysunku (\p true), czy też nie (\p false).
   */
  bool show_OX_axis_;

  /*!
   * \brief Czy oś OY ma być widoczna
   *
   * Przechowuje informację decydującą o tym czy oś OY będzie
   * widoczna na rysunku (\p true), czy też nie (\p false).
   */
  bool show_OY_axis_;

  /*!
   * \brief Czy oś OZ ma być widoczna
   *
   * Przechowuje informację decydującą o tym czy oś OZ będzie
   * widoczna na rysunku (\p true), czy też nie (\p false).
   */
  bool show_OZ_axis_;




  /*!
   * \brief Tworzy listę parametrów umożliwiających rysowanie dodatkowych elementów
   *
   * Metoda ta przewidziana jest jako element rozszerzenia pozwalającego
   * w klasach pochodnych powiększyć listę rysowanych elementów.
   * \pre Parametr \e command powinien zawierać polecenie \e plot lub \e splot,
   *      do którego będzie możliwe dopisanie dalszego ciągu.
   * \param command - polecenie rysowania, do którego mają być dopisane 
   *                    nazwy plików i odpowiednie parametry dla polecenia plot.
   * \param separator - zawiera znak separatora między poszczególnymi
   *              parametrami. Jeżeli parametry listy przeszkód
   *              są generowane jako pierwsze, to zmienna ta musi 
   *              być wskaźnikiem do wskaźnika na łańcuch: " ".
   */
  virtual bool AddFilesToDrawCommand( std::string &command, char const **separator );

  /*!
   *  \brief Tworzy polecenie ustawiające zakres dla danej współrzędnej.
   *
   *  Tworzy polecenie dla programu \e gnuplot ustawiające zakres 
   *  współrzędnych wybranej współrzędnej \e x, \e y lub \e z, 
   *  dla której ma być tworzony dany rysunek.
   *  \param axis - zawiera znak określający współrzędną, dla której
   *             ma zostać wygenerowane polecenie ustawienia zakresu.
   *  \return łańcuch znaków polecenia ustawiającego żądany zakres
   *          dla wybranej współrzędnej.
   */
  std::string SaveRangeSettings(char axis) const;
  /*!
   *  \brief Tworzy polecenie ustawiające punkt obserwacji.
   *
   *  Tworzy polecenie dla programu \e gnuplot ustawiajające punkt obserwacji
   *  poprzez zadanie rotacji i skali dla poszczególnych osi.
   */
  std::string SaveScaleRotationSettings() const;
   /*!
    * Przesyła na wejście programu \e gnuplot zadany ciąg znaków.
    *  \param command - komunikat przeznaczony do przeslania.
    *
    * \pre  Musi być zainicjowane połączenie z programem gnuplot.
    *
    * \retval true  - jesli przeslanie polecenia zakończyło się powodzeniem,
    * \retval false - w przypadku przeciwnym.
    *
    */
  bool SendToGnuplot(const char *command);
  /*!
   * \brief  Udostępnia informację czy mają być wyświetlane informacje o błędach.
   *
   *  Udostępnia wartość pola
   *  \link GnuplotLink::display_error_messages_
   *            display_error_messages_\endlink.
   *  Określa ono, czy mają być wyświetlane komunikaty o błędach na wyjście
   *  standardowe, czy też nie.
   */
  bool AreErrorMessagesDisplayed() const { return display_error_messages_;}
  /*!
   * \brief Uruchamia program \e gnuplot jako proces potomny.
   */
  bool CreateChildProcess();
  /*!
   * Wyświetla na wyjście "standard error" komunikat (przekazany jako
   * parametr), o ile pole 
   *   \link GnuplotLink::display_error_messages_
   *          display_error_messages_\endlink  ma wartość
   * \p true. W przypadku przeciwnym komunikat nie jest wyświetlany.
   */
  void ErrorMessage(const char *message) const;

  /*!
   * \brief Tworzy preambułę poprzedzającą polecenie rysowania
   *
   *  Tworzy zbiór poleceń, które ustawiają właściwy tryb rysowania
   *  oraz zakresy współrzędnych, jak też wszystkie inne parametry
   *  wynikające z przyjętego trybu rysowania.
   */
  void CreateCommandPreamble(std::string &preamble) const;

  /*!
   * \brief Tworzy preambułę poprzedzającą polecenie rysowania w trybie 2D
   *
   *  Tworzy zbiór poleceń, które ustawiają właściwy tryb rysowania
   *  oraz zakresy współrzędnych, jak też wszystkie inne parametry
   *  wynikające z trybu rysowania 2D.
   */
  void Create2DPreamble(std::string &preamble) const;


  /*!
   * \brief Tworzy preambułę poprzedzającą polecenie rysowania w trybie 3D
   *
   *  Tworzy zbiór poleceń, które ustawiają właściwy tryb rysowania
   *  oraz zakresy współrzędnych, jak też wszystkie inne parametry
   *  wynikające z trybu rysowania 3D.
   */
  void Create3DPreamble(std::string &preamble) const;


 public:

  /*!
   * \brief Umożliwia lub zabrania rysowania osi OX
   *
   * Umożliwia lub zabrania rysowania osi \e OX na rysunku wykresu.
   * \param show - decyduje o tym czy oś \e OX będzie rysowana (\p true),
   *                czy też nie (\p false).
   */
  void show_OX_axis(bool show) { show_OX_axis_ = show; }

  /*!
   * \brief Czy oś OX ma być rysowana
   *
   * Udostępnia informację czy oś \e OX ma być rysowana,
   * czy też nie.
   * \retval true - gdy oś \e OX ma być rysowana,
   * \retval false - w przypadku przeciwnym.
   */
  bool show_OX_axis() const { return show_OX_axis_; }


  /*!
   * \brief Umożliwia lub zabrania rysowania osi OY
   *
   * Umożliwia lub zabrania rysowania osi \e OY na rysunku wykresu.
   * \param show - decyduje o tym czy oś \e OY będzie rysowana (\p true),
   *                czy też nie (\p false).
   */
  void show_OY_axis(bool show) { show_OY_axis_ = show; }

  /*!
   * \brief Czy oś OY ma być rysowana
   *
   * Udostępnia informację czy oś \e OY ma być rysowana,
   * czy też nie.
   * \retval true - gdy oś \e OY ma być rysowana,
   * \retval false - w przypadku przeciwnym.
   */
  bool show_OY_axis() const { return show_OY_axis_; }


  /*!
   * \brief Umożliwia lub zabrania rysowania osi OZ
   *
   * Umożliwia lub zabrania rysowania osi \e OZ na rysunku wykresu.
   * \param show - decyduje o tym czy oś \e OZ będzie rysowana (\p true),
   *                czy też nie (\p false).
   */
  void show_OZ_axis(bool show) { show_OZ_axis_ = show; }

  /*!
   * \brief Czy oś OZ ma być rysowana
   *
   * Udostępnia informację czy oś \e OZ ma być rysowana,
   * czy też nie.
   * \retval true - gdy oś \e OZ ma być rysowana,
   * \retval false - w przypadku przeciwnym.
   */
  bool show_OZ_axis() const { return show_OZ_axis_; }


  /*!
   *  Udostępnia dolną wartość zakresu skali wzdłuż osi \e OX.
   */
  float Xmin() const { return x_min_; }
  /*!
   *  Udostępnia górną wartość zakresu skali wzdłuż osi \e OX.
   */
  float Xmax() const { return x_max_; }
  /*!
   *  Udostępnia dolną wartość zakresu skali wzdłuż osi \e OY.
   */
  float Ymin() const { return y_min_; }
  /*!
   *  Udostępnia górną wartość zakresu skali wzdłuż osi \e OY.
   */
  float Ymax() const { return y_max_; }
  /*!
   *  Udostępnia dolną wartość zakresu skali wzdłuż osi \e OZ.
   */
  float Zmin() const { return z_min_; }
  /*!
   *  Udostępnia górną wartość zakresu skali wzdłuż osi \e OZ.
   */
  float Zmax() const { return z_max_; }

  /*!
   * \brief Zmienia tryb rysowania
   *
   * Zmienia tryb rysowania jaki zostanie wymuszony na programie
   * \p gnuplot.
   * \param mode - wartość parametru określa nowy tryb rysowania.
   */
  void SetDrawingMode(DrawingMode  mode) { drawing_mode_ = mode; }

  /*!
   * \brief Udostępnia aktualny tryb rysowania
   *
   * Udostępnia informację o aktualnym trybie rysowania.
   */
  DrawingMode GetDrawingMode() const { return drawing_mode_; }

  /*!
   *  \brief Ustawia zakres osi \e OX
   *
   * Ustawia zakres osi \e OX. Ogranicza to obszar, który będzie
   * zwizualizowany przez programa \e gnuplot.
   * \param Xo - dolna granica obszaru rysowania dla osi \e OX.
   * \param Xn - górna granica obszaru rysowania dla osi \e OX.
   */
  void SetRangeX(float Xo, float Xn) { x_min_ = Xo;  x_max_ = Xn; }
  /*!
   *  \brief Ustawia zakres osi \e OY
   *
   * Ustawia zakres osi \e OY. Ogranicza to obszar, który będzie
   * zwizualizowany przez programa \e gnuplot.
   * \param Yo - dolna granica obszaru rysowania dla osi \e OY.
   * \param Yn - górna granica obszaru rysowania dla osi \e OY.
   */
  void SetRangeY(float Yo, float Yn) { y_min_ = Yo;  y_max_ = Yn; }
  /*!
   *  \brief Ustawia zakres osi \e OZ. 
   *
   * Ustawia zakres osi \e OZ. Ogranicza to obszar, który będzie
   * zwizualizowany przez programa \e gnuplot.
   * \param Zo - dolna granica obszaru rysowania dla osi \e OZ.
   * \param Zn - górna granica obszaru rysowania dla osi \e OZ.
   */
  void SetRangeZ(float Zo, float Zn) { z_min_ = Zo;  z_max_ = Zn; }


  /*!
   *  \brief Udostępnia skalę dla osi \e OX.
   *
   *  Udostępnia skalę dla osi \e OX dla tworzonego rysunku.
   */
  float ScaleX() const { return x_scale_; }
  /*!
   *  \brief Udostępnia skalę dla osi \e OZ.
   *
   *  Udostępnia skalę dla osi \e OZ dla tworzonego rysunku.
   */
  float ScaleZ() const { return z_scale_; }
  /*!
   *  \brief Zadaje skalę wzdłuż osi \e OZ.
   *
   *  Zadaje skalę wzdłuż osi \e OX dla tworzonego rysunku.
   *  \param x_scale - skala wzdłuż osi \e OX.
   */
  void SetScaleX( float x_scale ) { x_scale_ = x_scale; }
  /*!
   *  \brief Zadaje skalę wzdłuż osi \e OZ.
   *
   *  Zadaje skalę wzdłuż osi \e OZ dla tworzonego rysunku.
   *  \param z_scale - skala wzdłuż osi \e OZ.
   */
  void SetScaleZ( float z_scale ) { z_scale_ = z_scale; }
  /*!
   *  \brief Zadaje skalę wzdłuż osi \e OX i \e OZ.
   *
   *  Zadaje skalę wzdłuż osi \e OX i \e OZ dla tworzonego rysunku.
   *  \param x_scale - skala wzdłuż osi \e OX.
   *  \param z_scale - skala wzdłuż osi \e OZ.
   */
  void SetScaleXZ( float x_scale, float z_scale ) 
          { SetScaleX(x_scale);  SetScaleZ(z_scale); }

  /*!
   *  Udostępnia wartość kąta rotacji renderowanego rysunku wokół
   *  osi \e OX. Zwracana wartość wyrażona jest w stopiniach.
   */
  float RotationX() const { return x_rotation_; }
  /*!
   *  Udostępnia wartość kąta rotacji renderowanego rysunku wokół
   *  osi \e OZ. Zwracana wartość wyrażona jest w stopiniach.
   */
  float RotationZ() const { return z_rotation_; }
  /*!
   * \brief Ustawia rotację wokół osi \e OX.
   *
   * Zadaje kąt rotacji wokół osi \e OX. Umożliwia to zmianę
   * punktu obserwacji renderowanego rysunku.
   * \param  x_angle - wartość kąta rotacji. Jego wartość podawana 
   *                 jest w stopniach.
   */
  void SetRotationX( float x_angle ) { x_rotation_ = x_angle; }
  /*!
   * \brief Ustawia rotację wokół osi \e OZ.
   *
   * Zadaje kąt rotacji wokół osi \e OZ. Umożliwia to zmianę
   * punktu obserwacji renderowanego rysunku.
   * \param  z_angle - wartość kąta rotacji. Jego wartość podawana 
   *                 jest w stopniach.
   */
  void SetRotationZ( float z_angle ) { z_rotation_ = z_angle; }
  /*!
   * \brief Ustawia rotację wokół osi \e OX i \e OZ.
   *
   * Zadaje jednocześnie kąt rotacji wokół osi \e OX i \e OZ. 
   * Umożliwia to zmianę
   * punktu obserwacji renderowanego rysunku.
   * \param  x_angle - wartość kąta rotacji względem osi \e OX. 
   *                 Jego wartość podawana 
   *                 jest w stopniach.
   * \param  z_angle - wartość kąta rotacji względem osi \e OZ. 
   *                 Jego wartość podawana 
   *                 jest w stopniach.
   */
  void SetRotationXZ( float x_angle, float z_angle ) 
    { SetRotationX(x_angle);  SetRotationZ(z_angle); }  

  /*!
   *  \brief Zezwala lub zabrania wyświetlania komunikatów.
   *
   *  Metoda pozwala, albo też zabrania wyświetlania komunikatów o blędach.
   *  Jeżeli jakaś z operacji nie powiedzie się, to jako wynik zwracana
   *  jest wartość \p false. Oprócz tego metody takie moga wyświetlać
   *  komunikaty, które kierowane są na wyjście "standard error"
   *  Domyślnie przymuje się, że programista nie chce dodatkwego wyświetlania
   *  komunikatów.
   */
  void ShowErrorMessages( bool mode = true );
   /*!
    * \brief  Dodaje nazwę pliku.
    *
    * Powoduje dodanie do listy plików zawierajacych dane dla \e gnuplota,
    * nowej nazwy pliku.
    *
    * \param[in]  filename  - nazwa pliku z danymi dla gnuplota.
    * \param[in]  style - tryb rysowania danego zbioru punktow.
    *                      Może być ciągły lub jako zbiór osobnych punktów.
    * \param[in]  width - szerokość rysowanego obiektu. W przypadku
    *                     punktów parametr ten jest połową szerokości
    *                     kwadratu reprezentującego dany punkt.
    *
    * \retval true - jeżeli istnieje plik o nazwie udostępnionej poprzez
    *            parametr
    *            \e filename oraz jest zezwolenie na jego czytanie.
    *            Nazwa pliku zostaje dodana do listy plików z danymi 
    *            dla \e gnuplota.
    * \retval false - Jeżeli nie istnieje plik o nazwie przekazanej poprzez
    *            parametr \e filename. 
    *            Nazwa pliku zostaje dodana do listy plików z danymi 
    *            dla \e gnuplota.
    */
   bool AddFilename( const char       * filename, 
                         LineStyle    style = LS_CONTINUOUS, 
                         int                width = 1
                       );

    /*!
     * \brief Tworzy listę parametrów umożliwiających rysowanie brył z plików.
     */
    bool AddDrawingFromFiles( std::string &command, char const **separator );

   /*!
    * \brief Informuje, czy połączenie z \e gnuplot'em jest zainicjalizowane.
    *
    * Informuje, czy połączenie z programem \e gnuplot jest zainicjowane.
    * \retval true - jeśli tak,
    * \retval false - w przypadku przeciwnym.
    */ 
    bool IsConnectionInitialized() const;

  /*!
   *  Jeżeli lista plików nie jest pusta, to generuje sekwencje poleceń
   *  dla programu \e gnuplot mająca na celu narysowanie płaszczyzn na
   *  na podstawie danych zawartych w plikach z listy. 
   *
   *  \pre  Lista plików nie powinna być pusta. Nazwy plików na niej
   *        można umieścić za pomoca metody 
   *        \link GnuplotLink::AddName AddName\endlink.
   *        Metoda nie wymaga wcześniejszego zainicjowania połączenia
   *        z \e gnuplotem.
   *  \retval true   - gdy zostają poprawnie wysłane polecenia dla gnuplota.
   *                 Nie oznacza to jednak, że proces rysowania zakończył
   *                 się pomyślnie.
   *  \retval false   - gdy połączenie z gnuplotem nie może zostać poprawnie
   *                 zainicjalizowane lub gdy lista plików jest pusta.
   */
  bool Draw();
  /*!
   *  Działa analogicznie jak metoda 
   *  \link GnuplotLink::Draw Draw\endlink, z tą różnicą, że 
   *  rysunek robota
   *  składowany jest w pliku o nazwie przekazanej przez parametr 
   *  \e filename.
   *  Rysunek jest zapisywany w formacie \e PNG.
   *
   *  \post Lista plików nie powinna być pusta ponadto powinno być
   *        możliwe otwarcie do zapisu pliku o nazwie przekazanej przez
   *        parametr \e filename, do której dołączane jest rozszerzenie
   *        .ps .
   *        Metoda nie wymaga wcześniejszego zainicjowania połączenia
   *        z programem \e gnuplot. 
   *
   *  \retval true   - gdy zostają poprawnie wysłane polecenia dla 
   *                 \e gnuplota.
   *                 Nie oznacza to jednak, że proces rysowania zakończył
   *                 się pomyślnie.
   *  \retval false   - gdy połączenie z gnuplotem nie może zostać poprawnie
   *                 zainicjalizowane lub gdy lista plików jest pusta lub
   *                 też gdy nie można otworzyć pliku do zapisu.
   */
  bool DrawToFile(const char *filename);
  /*!
   *  \brief  Inicjalizuje połączenie z programem \e gnuplot.
   *
   *  Inicjalizuje połączenie z programem \e gnuplot. Realizowane jest to
   *  poprzez rozwidlenie procesu i uruchomienie jako procesu potomnego
   *  programu \e gnuplot. Komunikacja z programem \e gnuplot realizowana jest
   *  poprzez przejęcie jego wejścia i wyjścia standardowego.
   *
   *  \retval true - gdy połączenie z programem \e 0gnuplot zostało poprawnie
   *               zainicjalizowane lub gdy już wcześniej było 
   *               zainicjalizowane.
   *  \retval false - gdy proces inicjalizacji połączenia zakończył się
   *               niepowodzeniem.
   */
  bool Init();
  /*!
   *  \brief Usuwa ostatnią nazwę pliku.
   * 
   *  Usuwa ostatnią nazwę z listy nazw plików.
   */
  void DeleteLastName();
  /*!
   *  \brief Kasuje zawartość listy nazw plików.
   * 
   *  Calkowicie kasuje zawartość listy nazw plików.
   */
  void DeleteAllNames();

  GnuplotLink();
  virtual ~GnuplotLink();
};

  inline
  bool GnuplotLink::AddFilesToDrawCommand( std::string &,
                                                         char const  **
                                                       )
  { return true; }



}


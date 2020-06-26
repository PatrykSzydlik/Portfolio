/*!
   \file arg.hh
   \brief Plik z klasą i funkcją pozwalającą zinterpretować argomenty podane przy wywołaniu programu
   \author Patryk Szydlik
   \date 03.05.20
 */

#include <string>
#include <sstream> 

/*!
\brief Klasa zawierająca komplet parametrów wykonania się programu
*/
class inputArguments{
    public:
    int generateInput=1;
    int loadInput=0;
    int nVertices=500;
    int startingVertex=0;
    int percentFull=100;
    std::string InputFilename = "gData.txt";
    int repetitions=1;
    std::string OutputFilename = "results.txt";
    int isRaw=1;
    int graphType=0; // 0 - Matrix  1 - List  2 - Matrix and List
};

/*!
\brief Funkcja interpretująca ciąg argumentów podanych przy wywołaniu programu

\param[in] args - komplet ustawień wywołania programu 
\param[in] argc - zmienna przechowująca ilość argumentów wywołania
\param[in] argv - wskaźniki na tablice przechowujące podane przy wywołaniu argumenty

\param[out] - zwraca 0 jeśli interpretacja się powiodła lub 1 jesli nie
*/

int interpretArguments(inputArguments & args,int argc, char* argv[]){
    int generation=0, loading=0;
    for (int i=1; i<argc; i++) {
        if (argv[i][0] != '-'){  /* blad: to nie jest opcja - brak znaku "-" */
        std::cerr<<"Niepoprawny argument "<<argv[i]<<" wymagane jest podanie opcji ze znakiem '-'  \n";
        return 1;
        };
        std::stringstream readingStream;
        switch (argv[i][1]) {
            case 'g':
                generation=1;
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i];
                readingStream>>args.nVertices;
                }else{
                    std::cerr<<"Niepoprawny pierwszy argument w opcji G \n";
                    return 1;
                };
                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argumentu 1 w opcji G\n";
                    return 1;
                };
                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.startingVertex;
                }else{
                    std::cerr<<"Niepoprawny drugi argument w opcji G\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argumentu 2 w opcji G\n";
                    return 1;
                };
                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.percentFull;
                }else{
                    std::cerr<<"Niepoprawny trzeci argument w opcji G\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argumentu 3 w opcji G\n";
                    return 1;
                };
                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.InputFilename;
                }else{
                    std::cerr<<"Niepoprawny czwarty argument w opcji G\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argumentu 4 w opcji G\n";
                    return 1;
                };

            break;

            case 'i':
                loading=1;
                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.InputFilename;
                }else{
                    std::cerr<<"Niepoprawny argument w opcji I\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argument w opcji I\n";
                    return 1;
                };
            break;

            case 'r':
                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.repetitions;
                }else{
                    std::cerr<<"Niepoprawny argument w opcji R\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argument w opcji R\n";
                    return 1;
                };
            break;

            case 'o':
                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.OutputFilename;
                }else{
                    std::cerr<<"Niepoprawny argument w opcji O\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argument w opcji O\n";
                    return 1;
                };

                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.isRaw;
                }else{
                    std::cerr<<"Niepoprawny drugi argument w opcji O\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argumentu 2 w opcji O\n";
                    return 1;
                };
            break;

            case 't':
                readingStream.clear();
                readingStream.str("");
                i++;
                if (argv[i][0] != '-'){
                readingStream<<argv[i]; 
                readingStream>>args.graphType;
                }else{
                    std::cerr<<"Niepoprawny argument w opcji T\n";
                    return 1;
                };

                if(readingStream.fail()){
                    std::cerr<<"Błąd przy wczytywaniu argument w opcji T\n";
                    return 1;
                };
            break;

            default:
            std::cerr<<"Niepoprawny argument "<<argv[i]<<" opcja nierozpoznana \n";
            return 1;
            break;
        };
    };
    if(generation==1 && loading==1 ){
        std::cerr<<"Nie można uruchomić opcji generowania i wczytywania grafu jednocześnie. \nOpcja generowania automatycznie wyszukuje ścieżki do wszystkich wierzchołków w nowym grafie.\n";
        return 1;
    }else if(generation==0 && loading==1){
        args.loadInput=1;
        args.generateInput=0;
    };
    return 0;
 }
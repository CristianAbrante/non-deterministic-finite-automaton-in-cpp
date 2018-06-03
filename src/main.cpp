
    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta

    // Implementación del main.

#include "./NFA/NFA.hpp"
#include "./State/State.hpp"
#include "./Transition/Transition.hpp"

#include <cstdio>
#include <cstdlib>

void menu (NFA& userNFA);

int main (int argc, char* argv[])
{
    
    bool fileFault = false;
    
    system ("clear");
    cout << "-------------------------------------------------------------------" << endl;
    cout << "\tPráctica 4 : Simulación de Autómatas finitos no deterministas." << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    if (argc == 1)
    {
        
        char fileName[100];
        cout << "Introduzca un fichero que contenga los datos del NFA (.nfa) > ";
        cin >> fileName;
        
        NFA userNFA(fileName, fileFault);
        
        if (!fileFault)
        {
            cout << "Fichero cargado correctamente ✓" << endl;
            menu(userNFA);
        }
        else
        {
            cout << "Error de apertura del fichero: Nombre o formato incorrecto" << endl;
            cerr << "Fin del programa" << endl;
            cout << endl;
        }
    }
    
    if (argc == 2)
    {
        NFA userNFA(argv[1], fileFault);
        
        if (!fileFault)
        {
            cout << "Fichero cargado correctamente ✓" << endl;
            menu(userNFA);
        }
        else
        {
            cout << "Error de apertura del fichero: Nombre o formato incorrecto" << endl;
            cerr << "Fin del programa" << endl;
            cout << endl;
        }
    }
    
    if (argc >2)
    {
        cout << "Número incorrecto de argumentos" << endl;
        cerr << "Fin del programa" << endl;
        cout << endl;
    }
    
    
    cout << "\nHecho por: Cristian Abrante Dorta." << endl;
    cout << endl;
    
}

void menu (NFA& userNFA)
{
    char option;
    cout << endl;
    
    do
    {
        
        cout << endl;
        
        cout << "\t\t---- MENÚ ----"                    << endl;
        cout << " a. Leer NFA desde un fichero."        << endl;
        cout << " b. Mostrar el NFA."                   << endl;
        cout << " c. Identificar estados de muerte."    << endl;
        cout << " d. Identificar si el NFA es un DFA."  << endl;
        cout << " e. Analizar una cadena."              << endl;
        cout << " f. Finalizar programa."               << endl;
        
        cout << endl;
        cout << "Introduzca la letra de la opción a ejecutar > ";
        cin  >> option;
        
        switch (option)
        {
            case 'a': 
            {
                system ("clear");
                cout << " a. Leer NFA desde un fichero."    << endl;
                char fileName[100]; bool fileFault;
                
                cout << "Introduzca un fichero que contenga los datos del NFA (.nfa) > ";
                cin >> fileName;
                
                userNFA.refresh(fileName,fileFault);
                
                if (!fileFault)
                {
                    cout << "Fichero cargado correctamente ✓" << endl;
                }
                else
                {
                    cout << "Error de apertura del fichero: Nombre o formato incorrecto" << endl;
                    cerr << "Fin del programa" << endl;
                    option = 'e';
                    cout << endl;
                }
                
                break;
            }
            case 'b': 
            {
                system ("clear");
                cout << " b. Mostrar el DFA."               << endl;
                cout << "El DFA cargado desde el fichero es el siguiente: " << endl;
                cout << endl;
                
                cout << userNFA << endl;
                
                break;
            }
            case 'c': 
            {
                system ("clear");
                cout << " c. Identificar estados de muerte."<< endl;
                
                userNFA.determinateDeadStates(cout);
                
                cout << endl;
                break;
            }
            case 'd': 
            {
                system ("clear");
                cout << " d. Identificar si el NFA es un DFA."  << endl;
                cout << endl;
                
                if (userNFA.isADFA())
                {
                    cout << "El NFA es un DFA pues tiene una transición por cada símbolo de estado. " << endl;
                }
                else
                {
                    cout << "El NFA no es un DFA." << endl;
                }
                
                cout << endl;
                break;
            }
            case 'e': 
            {
                system ("clear");
                string userLanguageString;
                
                cout << " d. Analizar una cadena."          << endl;
                
                cout << "Introduzca una cadena perteneciente al alfabeto Σ = ";
                userNFA.writeAlphabet(cout);
                cout << " > ";
                cin >> userLanguageString;
                
                if (userNFA.stringIsCorrect(userLanguageString))
                {
                    bool test = userNFA.evaluateString(cout, userLanguageString);
                }
                else
                {
                    do
                    {
                        
                        cout << "La cadena contiene símbolos que no pertenecen al alfabeto, introdúzcala de nuevo > ";
                        cin >> userLanguageString;
                        
                    }while(!userNFA.stringIsCorrect(userLanguageString));
                    
                     bool test = userNFA.evaluateString(cout, userLanguageString);
                }
                
                break;
            }
            case 'f': 
            {
                system ("clear");
                cerr << "Fin del Programa." << endl;
                
                break;
            }
            default:
            {
                do
                {
                    cout << "Opción incorrecta, introduzca de nuevo la opción que desea > ";
                    cin >> option;
                } while (!((option>='a')&&(option<='f')));
            }
        }
    } while(option != 'f');
}
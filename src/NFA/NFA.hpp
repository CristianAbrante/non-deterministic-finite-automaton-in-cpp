    
    // Prática 4: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta
    
    // Definición de la clase NFA
    
#pragma once

#include "../State/State.hpp"
#include "../Transition/Transition.hpp"
#include "../Alphabet/Alphabet.hpp"

#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <vector>

using namespace std;

class NFA
{
    private:
        
        // Método que representa al alfabeto que utiliza el NFA.
        Alphabet        sigma;
        
        // Método que representa a un conjunto de estados.
        set<State>      setOfStates;
        
        // Método que representa al estado inicial 
        State           initialState;
        
        // Método que representa al conjunto de estados aceptados.
        set<State>      acceptedStates;
        
    public:
        
        // Constructor por defecto de la clase.
        NFA (void);
        
        // Constructor al que se le pasa un string y un parámetro que mira si hay fallos.
        NFA (string fileName, bool& openingFault);
        
        // Constructor de copia al que le pasamos como parámetro el propio objeto.
        NFA (const NFA& newNFA);
        
        // Destructor de la clase.
        ~NFA (void);
        
        // Método que carga desde un fichero un nuevo NFA.
        void refresh (string fileName, bool& openingFault);
        
        // Sobrecarga del operador >> que muestra el autómata por pantalla.
        friend ostream& operator<< (ostream& os, NFA& rhsNFA);
        
        // Método que evalua si una string es aceptada por el NFA.
        bool evaluateString(ostream& os, string userString);
        
        // Método que imprime el alfabeto por pantalla.
        ostream& writeAlphabet(ostream& os) const;
        
        // Método que muestra por pantalla los estados de muerte.
        ostream& determinateDeadStates(ostream& os);
        
        // Método que determina si el NFA leido se trata de un DFA o no.
        bool isADFA (void);
        
        bool stringIsCorrect (string languageString);
        
    private:
        
        // Método que crea el NFA a partir de un fichero.
        ifstream& createNFA (ifstream& newNFA);
        
        // Método que limpia el NFA.
        void clear (void);
        
        // Método que devuelve el estado dado un identificador.
        State getState (int ID) const;
        
        void deepSearch (string w, int currentID, vector<string>& paths, int& currentPath, vector<int>& pathStack);
        
        // Método que calcula si el estado es de muerte o no.
        bool isADeadState(const State& possibleState);
        
        // Método que muestra el conjunto de transiciones.
        ostream& writeTransitions (ostream& os, const set<int>& result) const;
        
        // Método que devuelve si un estado es aceptado o no.
        bool isAnAcceptedState (const State& userState) const;
        
        // Método que muestra por pantalla los caminos.
        ostream& writePaths (ostream& os, vector<string>& paths) const;
        
        //Método que devuelve si un estado es aceptado o no.
        bool isAnAcceptedState(const State& userState);
        
        void eraseAPathID (vector<int>& pathStack, int ID);
};

    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta

    // Definición de la clase Transition.

#pragma once

#include <cstdio>
#include <iostream>
#include <set>

class Transition
{
    public: 
        
        // Atributo que especifica la transción para dicho símbolo.
        char symbol;
        
        // Método que especifica el siguiente nodo de la transición.
        int nextStateID;
        
        // Constructor por defecto de la clase.
        Transition (void);
        
        // Constructor al que se le pasa como parámetro el ID del siguiente estado, y el símbolo.
        Transition (int nextState, char userSymbol);
        
        // Constructor de copia al que se le pasa la nueva transiición.
        Transition (const Transition& newTransition);
        
        // Destructor de la clase.
        ~Transition (void);
        
        // Sobrecarga del operador =.
        Transition& operator= (const Transition& rhs);
        
        // Sobrecarga del operador ==.
        bool operator== (const Transition& rhs) const;
        
        // Sobrecarga del operador <.
        bool operator< (const Transition& rhs) const;
};
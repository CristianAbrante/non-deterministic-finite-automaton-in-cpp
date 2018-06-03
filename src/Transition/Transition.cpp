
    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta

    // Implementación de la clase Transition.
    
#include "Transition.hpp"
    
    Transition:: Transition (void):
    symbol(),
    nextStateID(){}
    
    Transition:: Transition (int nextState, char userSymbol):
    symbol(userSymbol),
    nextStateID(nextState){}
    
    Transition:: ~Transition (void)
    {
        symbol = '0';
        nextStateID = -1;
    }
    
    Transition:: Transition (const Transition& newTransition)
    {
        symbol = newTransition.symbol;
        nextStateID = newTransition.nextStateID;
    }
    
    Transition& Transition:: operator= (const Transition& rhs)
    {
        this->symbol = rhs.symbol;
        this->nextStateID = rhs.nextStateID;
    }
        
    bool Transition:: operator== (const Transition& rhs) const
    {
        if ((this->symbol == rhs.symbol) && (this->nextStateID == rhs.nextStateID)) return true;
        return false;
    }
        
    bool Transition:: operator< (const Transition& rhs) const
    {
        if ((this->symbol <= rhs.symbol)) return true;
        return false;
    }
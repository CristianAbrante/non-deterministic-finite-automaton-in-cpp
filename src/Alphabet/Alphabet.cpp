
    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta

    // Definición de la clase Alphabet

#include "Alphabet.hpp"

    Alphabet:: Alphabet (void):
    symbols(){}
    
    Alphabet:: Alphabet (string userAlphabet, bool& creatingFault)
    {
        createAlphabet(userAlphabet, creatingFault);
    }
    
    Alphabet:: Alphabet (const Alphabet& newAlphabet)
    {
        symbols = newAlphabet.symbols;
    }
    
    void Alphabet:: insert (char& token)
    {
        symbols.insert(token);
    }
    
    int Alphabet:: size (void) const
    {
        return symbols.size();
    }
    
    char Alphabet:: getSymbol (int pos) const
    {
        if (pos < size())
        {
            int i = 0; 
            char result;
            bool found = false;
            set<char>:: iterator it = symbols.begin();
            
            while ((it!=symbols.end()) && !found)
            {
                if (pos == i) {result = *it; found = true;}
                else { it++; i++; }
            }
            
            return result;
        }
        else
        {
            return -1;
        }
    }
    
    bool  Alphabet:: stringIsCorrect(string& languageString)
    {
        
        bool correct = true; int i=0;
        
        while ((i<languageString.size())&&correct)
        {
            if (!symbolIsInTheAlphabet(languageString[i])) correct = false;
            else i++;
        }
        
        return correct;
    }
    
    void Alphabet:: clear(void)
    {
        symbols.clear();
    }
    
    ostream& operator<< (ostream& os, const Alphabet& rhs)
    {
        os << "{ ";
        
        for (int i=0; i<rhs.size(); i++)
        {
            if (rhs.getSymbol(i)!= '&')
            {
                os << rhs.getSymbol(i);
                if (i!=(rhs.size()-1)) os << ", ";
            }
            
        }
        
        os << "}";
        
        return os;
    }
    
    Alphabet& Alphabet:: operator= (const Alphabet& rhs)
    {
        this->symbols = rhs.symbols;
    }
    
    // MÉTODOS PRIVADOS.
    
    bool Alphabet:: symbolIsInTheAlphabet(char token) const
    {
        
        if (token == '&') return true;
        
        bool found = false; int i=0;
        while ((i<size())&&!found)
        {
            if (getSymbol(i) == token) found = true;
            else i++;
        }
        
        return found;
        
    }
    
    void Alphabet:: createAlphabet(string userAlphabet, bool& creatingFault)
    {
        clear();
        
        creatingFault = false;
        int i = 0;
        
        while ((i<userAlphabet.size())&&!creatingFault)
        {
            if (legal(userAlphabet[i])) { symbols.insert(userAlphabet[i]); i++; }
            else creatingFault = true;
        }
    }
    
    bool Alphabet:: legal (char& token)
    {
        return ((token!='~')&&(token!='&')&&(token!='{')&&(token!='}')&&(token!=' ')&&(token!=','));
    }

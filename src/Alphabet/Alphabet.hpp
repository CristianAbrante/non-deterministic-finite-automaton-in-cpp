
    // Prática 3: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta

    // Definición de la clase Alphabet

#pragma once

#include <cstdio>
#include <set>
#include <iostream>

using namespace std;

class Alphabet
{
    public:
        
        // Atributo que representa a un conjunto de símbolos.
        set<char>   symbols;
        
        // Constructor por defecto de la clase.
        Alphabet (void);
        
        // Constructor al que se le pasa una string de símbolos.
        Alphabet (string userAlphabet, bool& creatingFault);
        
        // Constructor de copia de la clase.
        Alphabet (const Alphabet& newAlphabet);
        
        // Método que devuelve el número de elementos del alfabeto.
        int size (void) const;
        
        // Método que inserta un caracter al alfabeto.
        void insert (char& token);
        
        // Método que devuelve el símbolo que se encuentra en una posción determinada.
        char getSymbol (int pos) const;
        
        // Método que determina si una cadena tiene todos los símbolos en el alfabeto.
        bool stringIsCorrect(string& languageString);
        
        // Método que limpia el alfabeto.
        void clear (void);
        
        // Sobrecarga del operador que muestra el alfabeto por pantalla.
        friend ostream& operator<< (ostream& os, const Alphabet& rhs);
        
        // Sobrecarga del operador = que iguala 2 alfabetos.
        Alphabet& operator= (const Alphabet& rhs);
        
    private:
        
        // Método que crea el alfabeto.
        void createAlphabet(string userAlphabet, bool& creatingFault);
        
        // Método que determina si un símbolo está en le alfabeto.
        bool symbolIsInTheAlphabet(char token) const;
        
        // Método que devuelve si un token es un símbolo legal.
        bool legal (char& token);
};
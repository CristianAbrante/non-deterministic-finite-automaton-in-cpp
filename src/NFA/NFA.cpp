    
    // Prática 4: Computabilidad y algoritmia
    // Curso: Segundo
    // Alumno: Cristian Abrante Dorta
    
    // Implementación de la clase NFA
    
#include "NFA.hpp"
    
    NFA:: NFA (void):
    sigma(),
    setOfStates(),
    initialState(),
    acceptedStates(){}
    
    NFA:: NFA (string fileName, bool& openingFault):
    sigma(),
    setOfStates(),
    initialState(),
    acceptedStates()
    {
        ifstream    NFADefinition;
        NFADefinition.open(fileName.c_str());
        
        if (NFADefinition.is_open())
        {
            openingFault = false;
            
            createNFA(NFADefinition);
        }
        else
        {
            openingFault = true;
        }
    }
    
    NFA:: NFA (const NFA& newNFA)
    {
        sigma = newNFA.sigma;
        setOfStates = newNFA.setOfStates;
        initialState = newNFA.initialState;
        acceptedStates = newNFA.acceptedStates;
    }
    
    NFA:: ~NFA (void)
    {
        clear();
    }
    
    void NFA:: refresh (string fileName, bool& openingFault)
    {
        clear();
        
        ifstream    NFADefinition;
        NFADefinition.open(fileName.c_str());
        
        if (NFADefinition.is_open())
        {
            openingFault = false;
            
            createNFA(NFADefinition);
        }
        else
        {
            openingFault = true;
        }
    }
    
    ostream& operator<< (ostream& os, NFA& rhsNFA)
    {
        int numberOfSymbols = 0;
        
        os << " ➝ Alfabeto: "<<  rhsNFA.sigma << endl;
        os << " ➝ Número de nodos: " <<  rhsNFA.setOfStates.size() << endl;
        os << " ➝ Estado de partida: q" << rhsNFA.initialState << endl;
        os << endl;
        
        os << " Estado:   σ → Estado siguiente" << endl;
        cout << endl;
        
        for (int i=0; i<rhsNFA.setOfStates.size(); i++)
        {
            os << " q" << rhsNFA.getState(i) << " : "; 
            numberOfSymbols = 0;
            for (int j=0; j<rhsNFA.sigma.size(); j++)
            {
                if (rhsNFA.getState(i).symbolIsUsed(rhsNFA.sigma.getSymbol(j)))
                {
                    if (rhsNFA.sigma.getSymbol(j)!='&')
                        os << rhsNFA.sigma.getSymbol(j) << " → ";
                    else
                        os << "ε" << " → ";
                    rhsNFA.writeTransitions(os, rhsNFA.getState(i).getNextStateID(rhsNFA.sigma.getSymbol(j)));
                    os << " | ";
                }
                else
                {
                    numberOfSymbols++;
                }
            }
            
            if (numberOfSymbols == rhsNFA.sigma.size()) os << "∀σ∈∑ → ∅";
            os << endl;
        }
        
        return os;
    }
    
    bool NFA:: evaluateString (ostream& os, string userString)
    {
        vector<string> paths;
        vector<int> pathStack;
        paths.resize(1);
        pathStack.push_back(0);
        
        int currentPath =0;
        int count =0;
        deepSearch(userString, initialState.identifier, paths, currentPath, pathStack);
        
        writePaths(os, paths);
        
        return true;
    }
    
    ostream& NFA:: writeAlphabet(ostream& os) const
    {
        os << sigma;
        return os;
    }
    
    ostream& NFA:: determinateDeadStates (ostream& os)
    {
        bool hasDeadStates = false;
        
        for (int i=0; i<setOfStates.size(); i++)
        {
            if (isADeadState(getState(i)))
            {
                hasDeadStates = true;
            }
        }
        
        if (hasDeadStates)
        {
            os << "Los estados de muerte son los siguientes:" << endl;
            cout << endl;
            
            for (int i=0; i<setOfStates.size(); i++)
            {
                if (isADeadState(getState(i)))
                {
                    os << "q" << getState(i) << " :  ";
                    
                    for (int j=0; j<sigma.size(); j++)
                    {
                        if (sigma.getSymbol(j)!='&') os << sigma.getSymbol(j) << " → ";
                        else os << "ε" << " → ";
                        
                        writeTransitions(os, getState(i).getNextStateID(sigma.getSymbol(j)));
                        
                        os << "  ";
                    }
                    
                    os << endl;
                }
            }
        }
        else
        {
            os << endl;
            os << "El NFA no tiene estados de muerte." << endl;
        }
        
        return os;
    }
    
    bool NFA:: isADFA (void)
    {
        bool isDFA = true;
        set<State>::iterator it = setOfStates.begin();
        
        while ((it!=setOfStates.end())&&isDFA)
        {
            if ((*it).transitions.size() != sigma.size()) isDFA = false;
            else it++;
        }
        
        return isDFA;
    }
    
    bool NFA:: stringIsCorrect(string languageString)
    {
        return sigma.stringIsCorrect(languageString);
    }
    
    // MÉTODOS PRIVADOS.
    
    ifstream& NFA:: createNFA (ifstream& newNFA)
    {
        int numberOfStates, initialStateID;
        
        newNFA >> numberOfStates;
        newNFA >> initialStateID;
        
        int currentStateID, numberOfTransitions; 
        bool isAnAcceptedState;
        char symbol; int nextStateID;
        
        State tmpState;
        
        for (int i=0; i<numberOfStates; i++)
        {
            newNFA >> currentStateID;
            newNFA >> isAnAcceptedState; 
            newNFA >> numberOfTransitions;
            
            if (currentStateID == initialStateID) initialState.identifier = currentStateID;
            else tmpState.identifier = currentStateID;
            
            for (int j=0; j<numberOfTransitions; j++)
            {
                
                newNFA >> symbol; 
                sigma.insert(symbol);
                
                newNFA >> nextStateID;
                
                if (currentStateID == initialStateID) initialState.setNextState(nextStateID, symbol);
                else tmpState.setNextState(nextStateID, symbol);
            }
            
            if (currentStateID == initialStateID) setOfStates.insert(initialState);
            else setOfStates.insert(tmpState);
            
            if(isAnAcceptedState&&(currentStateID == initialStateID)) acceptedStates.insert(initialState);
            if(isAnAcceptedState&&!(currentStateID == initialStateID)) acceptedStates.insert(tmpState);
            
            tmpState.clear();
        }
        
        return newNFA;
    }
    
    void NFA:: clear (void)
    {
        sigma.clear();
        setOfStates.clear();
        initialState.clear();
        acceptedStates.clear();
    }
    
    State NFA:: getState(int ID) const
    {
        State resultState;
        
        bool found = false;
        set<State>::iterator it = setOfStates.begin();
        
        while ((it!=setOfStates.end())&&!found)
        {
            if ((*it).identifier == ID) 
            {
                found = true; resultState = *it;
            }
            else it++;
        }
        
        return resultState;
    }
    
    ostream& NFA:: writeTransitions (ostream& os, const set<int>& result) const
    {
        if (result.empty())
        {
            os << "∅"; return os;
        }
        else
        {
            os << "{";
            set<int>:: iterator it = result.begin();
            int i = 0;
            
            for (; it!=result.end(); it++)
            {
                os << "q" << (*it);
                if (i!=result.size() - 1) { os << ", "; i++; }
            }
            os << "}";
            
            return os;
        }
    }
    
    void NFA:: deepSearch (string w, int currentID, vector<string>& paths, int& currentPath, vector<int>& pathStack)
    {
        if (w.size()>=1)
        {
            if ((getState(currentID).hasEpsTransitions())&&getState(currentID).numberOfTransitions())
            {
                vector<int> nextEpsID = getState(currentID).getEpsTransitions();
                
                string newPath; int tmpID;
                for(int i=0; i<nextEpsID.size(); i++)
                {
                    newPath = ""; paths.push_back(newPath);
                    paths.back() = paths[currentPath];
                    newPath.clear();
                    tmpID = paths.size() - 1;
                    pathStack.push_back(tmpID);
                }
                
                if (!nextEpsID.empty())
                {
                    
                    for(int i=0; i<nextEpsID.size();i++) 
                    {
                        paths[currentPath] += "q" + to_string(currentID) + " " + "ε" + " " + "q" + to_string(nextEpsID[i]) +"|";
                        deepSearch(w,nextEpsID[i],paths,currentPath, pathStack);
                    } 
                    
                    nextEpsID.clear();
                }
                
            }
            
            char symbol = w.front();
            w = w.substr(1,w.size() - 1);
            
            if (symbol == '&')
            {
                paths[currentPath] += "q" +to_string(currentID) + " " + "ε" + " " + "q" +to_string(currentID)+"|";
                paths[currentPath]+=to_string(currentID);
            }
            else
            {
                set<int> nextID = getState(currentID).getNextStateID(symbol);
                 
                
                if (nextID.size()>1)
                {
                    string newPath; int tmpID;
                    for(int i=1; i<nextID.size(); i++)
                    {
                        newPath = ""; paths.push_back(newPath);
                        paths.back() = paths[currentPath];
                        newPath.clear();
                        tmpID = paths.size() - 1;
                        pathStack.push_back(tmpID);
                    }
                    
                }
                
                if (nextID.empty())
                {
                    paths[currentPath] += "q" + to_string(currentID) + " " + symbol + " o"+"|";
                    eraseAPathID(pathStack, currentPath);
                    currentPath = pathStack.back();
                }
                else
                {
                    set<int>::iterator it = nextID.begin();
                    
                    for (; it!=nextID.end(); it++)
                    {
                        paths[currentPath] +="q" + to_string(currentID) + " " + symbol + " " + "q" + to_string(*it)+"|";
                        deepSearch(w,(*it),paths,currentPath, pathStack);
                    }
                }
            }
            
        }
        else
        {
            paths[currentPath]+=to_string(currentID);
            eraseAPathID(pathStack, currentPath);
            if(!pathStack.empty()) currentPath = pathStack.back();
        }
    }
    
    bool NFA:: isADeadState(const State& possibleState)
    {
        if(!isAnAcceptedState(possibleState))
        {
            if (possibleState.numberOfTransitions())
            {
                int currentID = possibleState.identifier;
                set<int> nextID;
                bool deadState = true;
                
                for (int i=0; i<sigma.size(); i++)
                {
                    nextID = possibleState.getNextStateID(sigma.getSymbol(i));
                    if (!nextID.empty())
                    {
                        set<int>:: iterator it = nextID.begin();
                        while ((it!=nextID.end())&&deadState)
                        {
                            if (currentID != (*it)) deadState = false;
                            else it++;
                        }
                        
                    }
                    
                }
                
                return deadState;
            }
            else
            {
                return true;
            }
        }
        else return false;
    }
    
    bool NFA:: isAnAcceptedState (const State& userState) const
    {
        set<State>::iterator it = acceptedStates.find(userState);
        
        if (it == acceptedStates.end())
        {
            if ((*it) == userState) return true;
            else return false;
        }
        else return true;
    }
    
    ostream& NFA:: writePaths (ostream& os, vector<string>& paths) const
    {
        bool accepted = false;
        for (int i=0; i<paths.size(); i++)
        {
            os << endl;
            os << "Camino " << i+1 << endl;
            
            int j=0;
            while(j<paths[i].size()-1)
            {
                if (paths[i][j]!='|')
                   { os << paths[i][j]; j++;}
                else
                   { os << endl; j++;}
                
            }
            
            if (paths[i][j]=='o')
            {
                os << endl;
                os << "La cadena está no ACEPTADA.";
            }
            else
            {
                int lastStateID = paths[i][j]-'0';
                
                if (isAnAcceptedState(getState(lastStateID)))
                {
                    os << endl;
                    os << "La cadena está ACEPTADA." << endl;
                    accepted = true;
                }
                else
                {
                    os << endl;
                    os << "La cadena está no ACEPTADA." << endl;
                }
            }
        }
        
        if (accepted)
        {
            os << endl;
            os << "DECISIÓN FINAL: la cadena está ACEPTADA." << endl;
        }
        else
        {
            os << endl;
            os << "DECISIÓN FINAL: la cadena está NO ACEPTADA." << endl;
        }
    }
    
    bool NFA:: isAnAcceptedState(const State& userState)
    {
        bool found = false;
        set<State>:: iterator it = acceptedStates.begin();
        
        while ((it!=acceptedStates.end())&&!found)
        {
            if ((*it).identifier==userState.identifier) found = true;
            else it++;
        }
        
        return found;
    }
    
    void NFA:: eraseAPathID (vector<int>& pathStack, int ID)
    {
        vector<int>::iterator it = pathStack.begin();
        bool found = false;
        
        while((it!=pathStack.end())&&!found)
        {
            if ((*it)==ID) found = true;
            else it++;
        }
        
        pathStack.erase(it);
    }
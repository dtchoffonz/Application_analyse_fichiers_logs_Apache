#include <iostream>
#include "Stats.h"
#include "Iflog.h"

using namespace std;

// Manipulateur pour simplement afficher la syntaxe de la commande
ostream& manuelUtilisation(ostream& os)
{
    os << "Synthaxe de la commande :" << endl;
    os << "./analog [-t <heure>] [-e] [-g <nomFichier.dot>] nomFichier.log" << endl;
    return os;
}

int main(int argc,char** argv)
{
    string log_file;
    string dot_file;
    bool grapheViz=false;
    bool exclude = false;
    int hour = -1;

    for (int i = 1; i < argc; ++i) 
    {
        string arg = argv[i];

        if (arg == "-g") 
        {
            if (i + 1 < argc) 
            {
                arg=argv[i+1];
                if (arg.find(".dot")==string::npos)
                {
                    cerr << "Erreur: l'option -g doit avoir un nom de fichier .dot comme argument." << endl;
                    cout << manuelUtilisation << endl;
                    return 1;
                }
                dot_file = argv[i + 1];
                grapheViz=true;
                ++i;
            } 
            else 
            {
                cerr << "Erreur: l'option -g doit avoir un nom de fichier comme argument." << endl;
                cout << manuelUtilisation << endl;
                return 1;
            }

        } 

        else if (arg == "-e") 
        {
            exclude = true;
        }

        else if (arg == "-t") 
        {
            if (i + 1 < argc) 
            {
                try 
                {
                    hour = stoi(argv[i + 1]);
                    if (hour<0 || hour>=24)
                    {
                        cerr << "Erreur: dans l'option -t, l'heure doit être comprise entre 0 et 23 heures." << endl;
                        return 1;
                    }
                    ++i;
                } 
                catch (const exception& e) 
                {
                    cerr << "Erreur: l'option -t doit avoir un entier comme argument."  << endl;
                    cout << manuelUtilisation << endl;
                    return 1;
                }
            } 
            else 
            {
                cerr << "Erreur: l'option -t doit avoir un entier comme argument." << endl;
                cout << manuelUtilisation << endl;
                return 1;
            }
        } 

        else if(i==argc-1)
        {
            log_file=argv[i];
        } 
        
        else 
        {
            cerr << "Erreur: option inconnue : " << arg << endl;
            cout << manuelUtilisation << endl;
            return 1;
        }
    }

    // Si on est arrivé ici, les options sont bonnes

    if(log_file=="")
    {
        cerr << "Erreur: Il faut mettre le nom du fichier dans la commande" << endl;
        cout << manuelUtilisation << endl;
        return 1;
    }

    Stats st(log_file);

    if (!st.FichierOuvert())
    {
        cerr << "Erreur: Nom de fichier non valide" << endl;
        cout << manuelUtilisation << endl;
        return 1;
    }

    st.GenererDico(exclude,hour);
    if(grapheViz)
    {
        cout << "Dot-file " << dot_file << " generated\n";
        st.GenererGraphe(dot_file);
    }
    if (hour != -1)
    {
        cout << "Warning : only hits between " << hour << "h and " << hour+1 << "h have been taken into account\n";
    }

    if (exclude)
    {
        cout << "Warning : documents with extension .css/.jpg/.js have been ignored\n";
    }
    st.AfficherTop10();
    
    return 0;
}
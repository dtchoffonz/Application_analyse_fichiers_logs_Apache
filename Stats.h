//---------- Interface de la classe <Stats> (fichier Stats.h) ----------------
#if ! defined ( STATS_H )
#define STATS_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include "Iflog.h"
#include <map>
#include <string>
#include <fstream>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef map<string,map<string,int> > dico;
typedef map<string,int> ssDico;
//------------------------------------------------------------------------
// Rôle de la classe <Stats>
// Cette classe permet de faire des statistiques d'un fichier log
//
//------------------------------------------------------------------------

class Stats
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    void GenererGraphe( const string& nomFichier ) const;
    // Permet de générer un fichier GraphViz du nom de nomFichier

    void AfficherTop10() const;

    void GenererDico( bool exclude, int time );
    
    // Permet de lire l'entièreté du fichier et de stocker les informations
    // exclude : vrai si on souhaite ne pas prendre en compte les images
    // time : ne prend en compte que les lignes dont l'horaire est entre
    //        time et time+1 (prend tout en compte si time=-1)

    bool FichierOuvert() const;
    // Permet de savoir si on n'a pas eu de problème lors de l'ouverture
    // du fichier de log


//------------------------------------------------- Surcharge d'opérateurs
    Stats & operator = ( const Stats & unStats );


//-------------------------------------------- Constructeurs - destructeur
    Stats ( const Stats & unStats );

    Stats ( const string& nomFic="test.txt",const string& nomConfig="config.txt" );

    virtual ~Stats ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

dico graphe;
map<string,int> top10;
Iflog log;
};

//-------------------------------- Autres définitions dépendantes de <Stats>

#endif // STATS_H


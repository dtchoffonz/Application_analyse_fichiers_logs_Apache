//---------- Interface de la classe <Iflog> (fichier Iflog.h) ----------------
#if ! defined ( IFLOG_H )
#define IFLOG_H

//--------------------------------------------------- Interfaces utilisées
using namespace std;
#include <fstream>

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Iflog>
// Cette classe permet de lire facilement un fichier log ligne par ligne
// afin d'en extraire ses informations
//------------------------------------------------------------------------

class Iflog
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques

    bool LireLigne();
    // Lit une ligne et "retient" les informations qu'elle contient
    // renvoie true si c'est la fin du fichier

    bool IsOpen() const;
    // renvoie true si le fichier fic est ouvert

    // GETERS
    string GetIp() const;

    string GetLogName() const;

    string GetAuthenticated() const;
    
    string GetDate() const;

    int GetStatus() const;

    long int GetTaille() const;

    string GetReferer() const;

    string GetNavigateur() const;

    string GetTypeAction() const;

    string GetUrlDemandee() const;


//------------------------------------------------- Surcharge d'opérateurs
    Iflog & operator = ( const Iflog & unIflog );


//-------------------------------------------- Constructeurs - destructeur
    Iflog ( const Iflog & unIflog );

    Iflog ( const string& nomFichier,const string& nomFicConfig );

    virtual ~Iflog ( );

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés
ifstream fic;
ifstream config;
string urlBase;
string ip;
string logName;
string authenticated;
string date;
int status;
long int taille;
string referer;
string navigateur;
string typeAction;
string urlDemandee;


};

//-------------------------------- Autres définitions dépendantes de <Iflog>

#endif // IFLOG_H


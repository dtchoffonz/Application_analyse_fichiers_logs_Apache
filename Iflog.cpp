//---------- Réalisation de la classe <Iflog> (fichier Iflog.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <fstream>
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Iflog.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Iflog::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

bool Iflog::LireLigne()
{
    if (fic.get()==EOF)
    {
        return false;
    }
    fic.unget();
    getline(fic, ip,' ');
    getline(fic, logName,' ');
    getline(fic, authenticated,' ');
    fic.ignore();
    getline(fic, date,']');
    fic.ignore(2);
    getline(fic, typeAction,' ');
    getline(fic, urlDemandee,' ');
    string temp;
    getline(fic,temp,'"');
    fic.ignore();

    string str_status;
    getline(fic, str_status,' ');
    status=stoi(str_status);

    string str_taille;
    getline(fic, str_taille,' ');
    if(str_taille.compare("-")!=0)
    {
        taille=stoi(str_taille);
    }
    else
        taille=0;

    fic.ignore();
    getline(fic, referer,'"');
    fic.ignore(2);
    getline(fic, navigateur,'"');
    fic.ignore();


    if(referer.find(urlBase)==0)
    {
        referer=referer.substr(urlBase.length());
    }
    
    return true;
}

bool Iflog::IsOpen() const
{
    return fic.is_open();
}

string Iflog::GetIp() const
{
    return ip;
}

string Iflog::GetLogName() const
{
    return logName;
}

string Iflog::GetAuthenticated() const
{
    return authenticated;
}

string Iflog::GetDate() const
{
    return date;
}

int Iflog::GetStatus() const
{
    return status;
}

long int Iflog::GetTaille() const
{
    return taille;
}

string Iflog::GetReferer() const
{
    return referer;
}

string Iflog::GetNavigateur() const
{
    return navigateur;
}

string Iflog::GetTypeAction() const
{
    return typeAction;
}

string Iflog::GetUrlDemandee() const
{
    return urlDemandee;
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur

Iflog::Iflog ( const string& nomFichier ,const string& nomFicConfig ):fic(nomFichier),config(nomFicConfig)
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Iflog>" << endl;
#endif
    if(!config)
    {
        urlBase="";
    }
    else
    {
        getline(config,urlBase);
    }

} //----- Fin de Iflog


Iflog::~Iflog ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Iflog>" << endl;
#endif
    fic.close();
    config.close();
} //----- Fin de ~Iflog


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


//---------- Réalisation de la classe <Stats> (fichier Stats.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <string>
#include <map>
#include <set>
#include <utility>
#include <iostream>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Iflog.h"
#include "Stats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Stats::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

bool Stats::FichierOuvert() const
{
    return log.IsOpen();
}


void Stats::GenererDico(bool exclude,int time)
// On lit chaque ligne en ajoutant les informations dans le dictionnaire
{
    while(log.LireLigne())
    {
        if (exclude && (log.GetUrlDemandee().find(".jpg")!= string::npos || log.GetUrlDemandee().find(".css")!= string::npos || log.GetUrlDemandee().find(".js") != string::npos))
        // On enlève les images, css et javascript
        {
            continue;
        }
        if (time!=-1 && stoi(log.GetDate().substr(12,2))!=time)
        // On enlève quand l'heure n'est pas dans la bonne plage horaire
        {
            continue;
        }
        if (log.GetStatus()>=200 && log.GetStatus()<300)
        {
            ssDico ssDicoVide;
            pair <dico::iterator, bool> controle1=graphe.insert(make_pair(log.GetUrlDemandee(),ssDicoVide));
            if(!controle1.second)
            {
                pair<map<string,int>::iterator,bool>controle2 = controle1.first->second.insert(make_pair(log.GetReferer(),1));
                if(!controle2.second)
                {
                    ++controle2.first->second;
                }
            }
            else
            {
                controle1.first->second.insert(make_pair(log.GetReferer(),1));
            }
            pair <ssDico::iterator, bool> controle = top10.insert(make_pair(log.GetUrlDemandee(),1));
            if (!controle.second)
            {
                ++controle.first->second;
            }
        }
        
    }
}

void Stats::GenererGraphe( const string& nomFichier ) const
// On crée un dictionnaire pour associer un index unique à chaque url
// et on crée ensuite un fichier .dot
{
    ofstream outfic(nomFichier);
    outfic << "digraph {\n";
    ssDico indexes;
    pair<ssDico::iterator,bool> controle;
    int i=0;

    // Parcours du graphe pour construire le dictionnaire des index 
    for(dico::const_iterator it=graphe.begin();it!=graphe.end();++it)
    {
        controle=indexes.insert(make_pair(it->first,i));
        if (controle.second)
        {
            ++i;
        }
        for(ssDico::const_iterator it2=it->second.begin();it2!=it->second.end();++it2)
        {
            controle=indexes.insert(make_pair(it2->first,i));
            if (controle.second)
            {
                ++i;
            }
        }
    }
    

    for(ssDico::const_iterator it=indexes.begin();it!=indexes.end();++it)
    {
        outfic << "node" << it->second << " [label=\"" << it->first << "\"];\n";
    }
    for(dico::const_iterator it=graphe.begin();it!=graphe.end();++it)
    {
        for(ssDico::const_iterator ssit=it->second.begin();ssit!=it->second.end();++ssit)
        {
            outfic << "node" << indexes[ssit->first] << " -> node" << indexes[it->first] << "[label=\"" << ssit->second << "\"];\n";
        }
    }
    outfic << "}";
    outfic.close();
}

void Stats::AfficherTop10() const
// On inverse la map top10 pour pouvoir avoir les nombres d'itération comme clé
// Puis on affiche les 10 premiers du plus grand au plus petit
{
    multimap<int,string> premiers;
    for(map<string,int>::const_iterator it=top10.begin();it!=top10.end();++it)
    {
        premiers.insert(make_pair(it->second,it->first));
    }
    multimap<int,string>::reverse_iterator it=premiers.rbegin();
    for(int i;i<10;++i)
    {
        if(it==premiers.rend())
        {
            break;
        }
        cout << it->second << " (" << it->first << "hits)" << endl;
        ++it;
    }
}

//------------------------------------------------- Surcharge d'opérateurs


//-------------------------------------------- Constructeurs - destructeur


Stats::Stats (const string& nomFic,const string& nomConfig):log(nomFic,nomConfig)
{
#ifdef MAP
    cout << "Appel au constructeur de <Stats>" << endl;
#endif

} //----- Fin de Stats


Stats::~Stats ( )
{
#ifdef MAP
    cout << "Appel au destructeur de <Stats>" << endl;
#endif
} //----- Fin de ~Stats


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées


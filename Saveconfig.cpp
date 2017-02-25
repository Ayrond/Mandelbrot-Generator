#include "Saveconfig.h"
//#include "Function.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>

#define TRACE_INPUT() std::cout << "Call: " << __PRETTY_FUNCTION__ << std::endl;
#define TRACE_OUTPUT() std::cout << "Exit: " << __PRETTY_FUNCTION__ << std::endl;


Saveconfig::Saveconfig(){}

//void Saveconfig::set_default(par){
//    m_pmconfig.m_MyParams["Height"]="1000";
//    m_pmconfig.m_MyParams["Width"]="1900";
//    m_pmconfig.m_MyParams["Itera"]="300";
//    m_pmconfig.m_MyParams["Mod"]="200";
//    m_pmconfig.m_MyParams["Largeur"]="4";
//    m_pmconfig.m_MyParams["x"]="0";
//    m_pmconfig.m_MyParams["y"]="0";
//    m_pmconfig.m_MyParams["Filename"]="Mandelbrot";
//}
void Saveconfig::init(std::string filename)
{
    m_pmconfig.m_MyParams.clear();
    m_filename=filename;
}
void Saveconfig::add_data(std::string name, std::string value)
{
    //TRACE_INPUT()
    m_pmconfig.m_MyParams[name]=value;
    //TRACE_OUTPUT()
}

void Saveconfig::write()
{
//    TRACE_INPUT()
    m_flux.open(m_filename, std::ios::out | std::ios::trunc);
    if(!m_flux)
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier \"" << m_filename << "\" en écriture." << std::endl;
    }

    for(std::map<std::string, std::string>::iterator it = m_pmconfig.m_MyParams.begin(); it!=m_pmconfig.m_MyParams.end(); ++it){
        m_flux << it->first << ": " << it->second << std::endl;
        //std::cout << it->first << ": " << it->second << std::endl;
    }
//    m_flux << std::flush ;
    m_flux.close();
//    TRACE_OUTPUT()
}
void Saveconfig::read()
{
//    TRACE_INPUT()
    m_flux.open(m_filename, std::ios::in);
    if(!m_flux.is_open())
    {
        std::cerr << "ERREUR: Impossible d'ouvrir le fichier \"" << m_filename << "\" en lecture." << std::endl;
    }
    std::string x;
    std::string y;
    m_flux >> x;
    m_flux.seekg(0,std::ios::beg);
    if(x.size() == 0){
        std::cerr << "WARNING: Le fichier \"" << m_filename << "\" est vide, utilisation de la conf par défault." << std::endl;
        m_flux.close();
//        set_default();
//            set_on_case();
    }
    else{
        while(!m_flux.eof()){
            m_flux >> x >> y;
            if (x.size() >= 1)
            {
                x.pop_back();// Suppression des deux points ou sinon  : maChaine.resize (maChaine.size () - 1);
                m_pmconfig.m_MyParams[x]=y;
            }
            else
            {
               std::cerr << "ERREUR: Fichier de configuration erroné : x.size()=" << x.size() << std::endl;
            }
        }
    }

    m_flux.close();
}
std::string Saveconfig::value_of(std::string what, std::string default_value)
{
//    TRACE_INPUT()
//    std::cout << what << std::endl << std::flush();
    std::map<std::string, std::string>::iterator it=m_pmconfig.m_MyParams.find(what);
    if(it == m_pmconfig.m_MyParams.end())
    {
        std::cerr << "In" << __PRETTY_FUNCTION__ << ": no return for value:" << what << std::endl;
        return default_value;
    }
    else
    {
        return it->second;
    }
}

#ifndef SAVECONFIG_H_INCLUDED
#define SAVECONFIG_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

//#include "Function.h"
class params
{
    public:
        std::map<std::string, std::string> m_MyParams;

};

class Saveconfig
{
    public :
        Saveconfig();
        void init(std::string filename="SaveConfig.conf");
        void add_data(std::string name, std::string value);
        void write();

//        void set_pm(params pm);
        void read();
        //void closefile();
        std::string value_of(std::string what, std::string default_value="");
//        int nb_de_ligne();

    private :

        std::string m_filename;
        std::vector<std::string> m_vx;
        std::vector<std::string> m_vy;
        std::fstream m_flux;
        params m_pmconfig;
};




#endif // SAVECONFIG_H_INCLUDED

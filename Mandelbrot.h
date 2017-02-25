#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED
#include <iostream>
#include <fstream>


//class params
//{
//    public:
//        params();
//        std::map<std::string, std::string> m_MyParams;
//
//};
class Mandelbrot
{
    public :

        Mandelbrot();
        Mandelbrot(int widthImage, int heightImage, double largeurArea, double xcentre, double ycentre, std::string filename, int IteractionMax, double ModuleMax, bool Axes);
//        Mandelbrot(const Mandelbrot&);

        void set_param(int widthImage, int heightImage, double largeurArea, double xcentre, double ycentre, std::string filename, int IteractionMax, double ModuleMax, bool Axes);
        /*void add_widthImage(int widthImage);
        void add_heightImage(int heightImage);
        void add_largeurArea(double largeurArea);
        void add_xcentre(double xcentre);
        void add_ycentre(double ycentre);
        void add_filename(std::string filename);
        void add_IteractionMax(int IteractionMax);
        void add_ModuleMax(double ModuleMax);*/

        void calc();


    private :
        int m_widthImage;
        int m_heightImage;
        double m_largeurArea;
        double m_xcentre;
        double m_ycentre;
        std::string m_filename;
        int m_IteractionMax;
        double m_ModuleMax;
        bool m_axes;

        std::fstream m_flux;
};
int rcalc(int iter);
int bcalc(int iter);
int gcalc(int iter);
#endif // MANDELBROT_H_INCLUDED

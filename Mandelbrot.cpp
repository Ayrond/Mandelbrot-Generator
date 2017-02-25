#include "Mandelbrot.h"
#include "Function.h"

#include <fstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

#define TRACE_INPUT() std::cout << "Call: " << __PRETTY_FUNCTION__ << std::endl;
#define TRACE_OUTPUT() std::cout << "Exit: " << __PRETTY_FUNCTION__ << std::endl;

int rcalc(int iter){
    iter=iter % 1530;
    if(iter<=765){
        if(iter<255){
            return 255;
        }
        else{
            if(iter<510){
                return 510-iter;
//                return 255+127-(iter/2);
            }
            else{
                return 0;
//                return 127;
            }
        }
    }
    else{
        return rcalc(1530-iter);
    }
}

int bcalc(int iter){
//    return rcalc(iter+1020);
    return rcalc(iter+1020+64);
}
int gcalc(int iter){
//    return rcalc(iter+510);
    return rcalc(iter+510-64);
}

Mandelbrot::Mandelbrot(){
        m_widthImage=0;
        m_heightImage=0;
        m_largeurArea=0;
        m_xcentre=0;
        m_ycentre=0;
        m_filename="Test";
        m_IteractionMax=0;
        m_ModuleMax=0;
        m_axes=0;
}
Mandelbrot::Mandelbrot(int widthImage, int heightImage, double largeurArea, double xcentre, double ycentre, std::string filename, int IteractionMax, double ModuleMax, bool Axes):
    m_widthImage(widthImage),
    m_heightImage(heightImage),
    m_largeurArea(largeurArea),
    m_xcentre(xcentre),
    m_ycentre(ycentre),
    m_filename(filename),
    m_IteractionMax(IteractionMax),
    m_ModuleMax(ModuleMax),
    m_axes(Axes)
{}

void Mandelbrot::set_param(int widthImage, int heightImage, double largeurArea, double xcentre, double ycentre, std::string filename, int IteractionMax, double ModuleMax, bool Axes)
{
    m_widthImage=widthImage;
    m_heightImage=heightImage;
    m_largeurArea=largeurArea;
    m_xcentre=xcentre;
    m_ycentre=ycentre;
    m_filename=filename;
    m_IteractionMax=IteractionMax;
    m_ModuleMax=ModuleMax;
    m_axes=Axes;
}
void Mandelbrot::calc(){
    TRACE_INPUT()

    std::time_t t0(std::time_t(0));
    t0=chrono(t0);

    double x =0;
    double y =0;

    // Variables de traçage
    long rColor = 0 ;
    long gColor = 0 ;
    long bColor = 0 ;

    m_flux.open(m_filename, std::ios::out | std::ios::trunc);;


//    FILE *out =fopen(m_filename.data(),"w" );
//    fprintf(out,"P6\n%i %i\n255\n", m_widthImage, m_heightImage);
//    m_flux << "P3" << std::endl << m_widthImage << " " << m_heightImage << std::endl << "255" << std::endl;
    m_flux << "P6" << std::endl << m_widthImage << " " << m_heightImage << std::endl << "255" << std::endl;
    double coef = m_largeurArea / m_widthImage;
    int axe = m_widthImage / 4;

    int decalyorigine=-m_heightImage/2+1;
    int decalxorigine=-m_widthImage/2+1;
//    int pyfin = m_heightImage/2;
//    int pxfin = m_widthImage/2;

//    int cx = 0;
//    int cy = 0;

    long buffersize = m_heightImage*m_widthImage*3*sizeof(char);
    char *buffer = (char *) malloc(buffersize);
    memset(buffer, 0, buffersize);//initialisation inutile ?
//    const int nbthreads=15;


    #pragma omp parallel for private(x,y,rColor,gColor,bColor)

    for(int cy = 0; cy < m_heightImage ; ++cy)
//    for(int py = -m_heightImage/2+1; py <= pyfin ; ++py)
    {
        int py=cy+decalyorigine;
        y = -py*coef+m_ycentre;
//        if ( py % 200 == intTest ) std::cout << py << ": " ;//<< std::endl;
        for(int cx = 0; cx <= m_widthImage ; ++cx)
        {
            int px=cx+decalxorigine;
            x = px*coef+m_xcentre;
            if(m_axes && (px == 0 || px == axe || px == -axe || py == 0 || py == axe || py == -axe)){
                    rColor = 255;
                    bColor = 255;
                    gColor = 255;
            }
            else{
//                bool test = Calcul(x,y, IteractionMax);

                double z_r = 0;
                double z_i = 0;
                int i = 0;
                double z_r2;
                double z_i2;
//#define rapide
#ifdef rapide
                do
                {
                    double tmp= z_r;
                    z_r = z_r * z_r - z_i * z_i + x;
                    z_i = 2 * tmp * z_i + y;
                    ++i;
                } while (z_r * z_r + z_i * z_i < m_ModuleMax && i < m_IteractionMax);
#else
                do
                {

                    z_r2 = z_r*z_r;
                    z_i2 = z_i*z_i;
                    z_i = 2 * z_i * z_r + y;
                    z_r = z_r2 - z_i2 + x;
                    ++i;
                } while (z_r2 + z_i2 < m_ModuleMax && i < m_IteractionMax);
#endif // rapide
//                i=px;
                if ( i == m_IteractionMax)
                {
                    gColor = 0;
                    bColor = 0;
                    rColor = 0;
                }
//                else
//                {
//
//                    gColor = (double(i) / m_IteractionMax)*255;
//                    bColor = 255*(double(i) / m_IteractionMax/3);
//                    if(gColor<0)gColor=0;
//                    if(bColor<0)bColor=0;
//                }
                else
                {

//                    gColor = gcalc(1-(double(i)/m_IteractionMax)*1530);
//                    bColor = bcalc(1-(double(i)/m_IteractionMax)*1530);
//                    rColor = rcalc(1-(double(i)/m_IteractionMax)*1530);
                    gColor = gcalc(i);
                    bColor = bcalc(i*110);
                    rColor = rcalc(i);
                }
//                if(py==0){
//                    std::cout << "Rouge :" << rColor << "\t" ;
//                    std::cout << "Bleu :" << bColor << "\t" ;
//                    std::cout << "Vert :" << gColor << std::endl ;
//                }
            }

//            cptchar+=sprintf(buffer+cptchar,"%c%c%c", char(rColor), char(gColor), char(bColor));
            long cptchar=(m_widthImage*cy+cx)*3;

            buffer[cptchar]=char(rColor);
            buffer[++cptchar]=char(gColor);
            buffer[++cptchar]=char(bColor);
//            sprintf(buffer+cptchar,"%c%c%c", char(rColor), char(gColor), char(bColor));


//            fprintf(out,"%c%c%c", char(rColor), char(gColor), char(bColor));
//            buffer << char(rColor) << char(gColor) << char(bColor);
//            m_flux << char(rColor) << char(gColor) << char(bColor);
//            m_flux << rColor << " " << gColor << " " << bColor << std::endl;
        }
    }
    m_flux.write(buffer, buffersize);
    m_flux.flush();
    free(buffer);
    m_flux.close();
    std::cout << "Chrono :" << chrono(t0) << std::endl;
    TRACE_OUTPUT()
}

#include <gtkmm.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <X11/Xlib.h>
#include <cmath>

#include "Mandelbrot.h"
#include "Saveconfig.h"
#include "Function.h"
#include "DerivedWindow.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

std::thread* pt;

Saveconfig MySave;
Mandelbrot MyMan;

DerivedWindow* pWindow = NULL;
Gtk::Entry* pWidth_Height = NULL;
Gtk::Entry* pWidth_Width = NULL;
Gtk::Entry* pItera_Itera = NULL;
Gtk::Entry* pItera_Mod = NULL;
Gtk::Entry* pWhere_x = NULL;
Gtk::Entry* pWhere_y = NULL;
Gtk::Entry* pWhere_Largeur = NULL;
Gtk::Entry* pFile_name = NULL;
Gtk::Button* pGenerate = NULL;
Gtk::Button* pCalc = NULL;
Gtk::Spinner* pSpinner = NULL;
Gtk::LevelBar* pLevelBar = NULL;
Gtk::Switch* pAxes = NULL;
Gtk::Switch* pFilm = NULL;
Gtk::Label* pExtention = NULL;

void reset_params(string filename="Mandelbrot.conf")
{
    MySave.init(filename);
    MySave.add_data("Height","1200");
    MySave.add_data("Width","1920");
    MySave.add_data("Itera","300");
    MySave.add_data("Mod","200");
    MySave.add_data("Largeur","4");
    MySave.add_data("x","0");
    MySave.add_data("y","0");
    MySave.add_data("Filename","Mandelbrot");
    MySave.add_data("Axes","0");
    MySave.add_data("Film","0");
}

void get_from_box(Saveconfig& save)
{

    if(!pWidth_Height || !pWidth_Width || !pItera_Itera|| !pItera_Mod
           || !pWhere_Largeur || !pWhere_x || !pWhere_y || !pFile_name || !pGenerate|| !pCalc){
            cerr << "ERREUR : Un des Widgets n'a pus être chargés." << endl;
            exit(EXIT_FAILURE);
    }
    save.add_data("Height",pWidth_Height->get_text());
    save.add_data("Width",pWidth_Width->get_text());
    save.add_data("Itera",pItera_Itera->get_text());
    save.add_data("Mod",pItera_Mod->get_text());
    save.add_data("Largeur",pWhere_Largeur->get_text());
    save.add_data("x",pWhere_x->get_text());
    save.add_data("y", pWhere_y->get_text());
    save.add_data("Filename",pFile_name->get_text());
    save.add_data("Axes", pAxes->get_active()?"1":"0");
    save.add_data("Film", pFilm->get_active()?"1":"0");
//    for(auto it = pm.m_MyParams.cbegin(); it != pm.m_MyParams.cend(); ++it)
//    {
//     std::cout << it->first << ":" << it->second << "\n";
//    }
}
void set_on_case(Saveconfig& save)
{

    if(!pWidth_Height || !pWidth_Width || !pItera_Itera|| !pItera_Mod
           || !pWhere_Largeur || !pWhere_x || !pWhere_y || !pFile_name || !pGenerate|| !pCalc){
            cerr << "ERREUR : Un des Widgets n'a pus être chargés." << endl;
            exit(EXIT_FAILURE);
    }
    pWidth_Height->set_text(save.value_of("Height"));
    pWidth_Width->set_text(save.value_of("Width"));
    pItera_Itera->set_text(save.value_of("Itera"));
    pItera_Mod->set_text(save.value_of("Mod"));
    pWhere_Largeur->set_text(save.value_of("Largeur"));
    pWhere_x->set_text(save.value_of("x"));
    pWhere_y->set_text(save.value_of("y"));
    pAxes->set_active(stobool(save.value_of("Axes")));
    pFilm->set_active(stobool(save.value_of("Film")));
    std::string str = save.value_of("Filename") + ".ppm";
    str.resize(str.size () - 4);
    pFile_name->set_text(str);
    /*for(auto it = pm.m_MyParams.cbegin(); it != pm.m_MyParams.cend(); ++it)
    {
     std::cout << it->first << ":" << it->second << "\n";
    }*/
}
void thread_function()
{
    get_from_box(MySave);

    if(stobool(MySave.value_of("Film"))){
        pLevelBar->set_min_value(0);
        double tmp = stodou(MySave.value_of("Largeur")) - floor(stodou(MySave.value_of("Largeur")));
        int i =0;
        for(i=1;tmp<1;i++){
            cout << "i :" << i << "\ttmp :" << tmp << endl;
            tmp*=10;
        }
        pLevelBar->set_max_value(i);
        for(int j=1;tmp>stodou(MySave.value_of("Largeur")) - floor(stodou(MySave.value_of("Largeur")));j++){
            MyMan.set_param(stoint(MySave.value_of("Width")),
                   stoint(MySave.value_of("Height")),
                   tmp,
                   stodou(MySave.value_of("x")),
                   stodou(MySave.value_of("y")),
                   MySave.value_of("Filename")+std::to_string(j)+".ppm",
                   stoint(MySave.value_of("Itera")),
                   stodou(MySave.value_of("Mod")),
                   stobool(MySave.value_of("Axes")) );

            MyMan.calc();
            pLevelBar->set_value(j);
            cout << "j :" << j << "\ttmp :" << tmp << endl;
            tmp/=5;
        }
    }
    else{
        MyMan.set_param(stoint(MySave.value_of("Width")),
                   stoint(MySave.value_of("Height")),
                   stodou(MySave.value_of("Largeur")),
                   stodou(MySave.value_of("x")),
                   stodou(MySave.value_of("y")),
                   MySave.value_of("Filename")+".ppm",
                   stoint(MySave.value_of("Itera")),
                   stodou(MySave.value_of("Mod")),
                   stobool(MySave.value_of("Axes")) );

        MyMan.calc();
    }

    pSpinner->stop();
    pGenerate->set_sensitive(true);
}
/*
string get_data_pWidth_Height(){
    return pWidth_Height->get_text();
}
string get_data_pWidth_Width(){
    return pWidth_Width->get_text();
}
string get_data_pItera_Itera(){
    return pItera_Itera->get_text();
}
string get_data_pItera_Mod(){
    return pItera_Mod->get_text();
}
string get_data_pWhere_x(){
    return pWhere_x->get_text();
}
string get_data_pWhere_y(){
    return pWhere_y->get_text();
}
string get_data_pWhere_Largeur(){
    return pWhere_Largeur->get_text();
}
string get_data_pFile_name(){
    return pFile_name->get_text();
}*/

static void on_button_generate_clicked()
{
//    TRACE_INPUT()
    pGenerate->set_sensitive(false);
	if(pWindow){
        if(pSpinner){
            pSpinner->start();
            pSpinner->show_now();
//            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//            while(Gtk::Main::events_pending()) Gtk::Main::iteration();
        }
        //cout <<pt << endl;
        if(pt){
            if (pt->joinable()){
                pt->join();
            }
            delete pt;

        }
        pt= new std::thread(thread_function);
        //cout <<pt << endl;
//        while(!pt->joinable()){
//            while(Gtk::Main::events_pending()) Gtk::Main::iteration();
//            //std::this_thread::sleep_for(std::chrono::milliseconds(500));
//            cout << "*";
//        }
//        pWindow->Save_conf("Mandelbrot.conf");
        MySave.write();
	}
//	TRACE_OUTPUT()
}
static void on_button_calc_clicked()
{
    //cout << pWindow->conf_value("Height") << endl ;
}
int main (int argc, char **argv)
{
    TRACE_INPUT()
    XInitThreads();
    MySave.init("Mandelbrot.conf");
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    //Load the GtkBuilder file and instantiate its widgets:
    auto refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("Mandelbrot.glade");
    }
    catch(const Glib::FileError& ex)
    {
        cerr << "FileError: " << ex.what() << endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        cerr << "MarkupError: " << ex.what() << endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        cerr << "BuilderError: " << ex.what() << endl;
        return 1;
    }

    //Get the GtkBuilder-instantiated Dialog:
    refBuilder->get_widget_derived("MyWindow", pWindow);
    if(pWindow){

    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
        refBuilder->get_widget("Width_Height", pWidth_Height);
        refBuilder->get_widget("Width_Width", pWidth_Width);
        refBuilder->get_widget("Itera_Itera", pItera_Itera);
        refBuilder->get_widget("Itera_Mod", pItera_Mod);
        refBuilder->get_widget("Where_x", pWhere_x);
        refBuilder->get_widget("Where_y", pWhere_y);
        refBuilder->get_widget("Where_Largeur", pWhere_Largeur);
        refBuilder->get_widget("File_name", pFile_name);
        refBuilder->get_widget("Exec_button", pGenerate);
        refBuilder->get_widget("Calc", pCalc);
        refBuilder->get_widget("MySpinner", pSpinner);
        refBuilder->get_widget("MyLevelbar", pLevelBar);
        refBuilder->get_widget("Axes", pAxes);
        refBuilder->get_widget("Film", pFilm);
        refBuilder->get_widget("Debug", pExtention);

        if(!pWidth_Height || !pWidth_Width || !pItera_Itera|| !pItera_Mod || !pWhere_Largeur ||
           !pWhere_x || !pWhere_y || !pFile_name || !pGenerate|| !pCalc || !pAxes || !pFilm || !pLevelBar || !pSpinner || !pExtention){
            cerr << "ERREUR : Un des Widgets n'a pus être chargés." << endl;
            exit(EXIT_FAILURE);
        }
        pGenerate->signal_clicked().connect(sigc::ptr_fun(on_button_generate_clicked));
        pCalc->signal_clicked().connect(sigc::ptr_fun(on_button_calc_clicked));
        reset_params("Mandelbrot.conf");
//        MySave.write();
        MySave.read();
        set_on_case(MySave);
        app->run(*pWindow);
    }
    if(pt){
        if(pt->joinable()){
                pt->join();
        }
        delete pt;
    }
    get_from_box(MySave);
    MySave.write();
    delete pWindow;

    TRACE_OUTPUT()
    return 0;

}

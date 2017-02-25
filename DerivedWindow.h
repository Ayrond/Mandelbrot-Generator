#ifndef DERIVEDWINDOW_H_INCLUDED
#define DERIVEDWINDOW_H_INCLUDED

#include <iostream>
#include <thread>
#include <gtkmm.h>

#include "Function.h"

class DerivedWindow : public Gtk::Window
{
    public:
        DerivedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
        virtual ~DerivedWindow();

//        void Save_conf(std::string filename="Mandelbrot.conf");
//        void Read_conf(std::string filename="Mandelbrot.conf");
//        void Load_conf();
//        std::string conf_value(std::string what, std::string default_value="");

    protected:
        //Signal handlers:
        Glib::RefPtr<Gtk::Builder> m_refGlade;

    private:
        bool on_key_press_event(GdkEventKey* event);
//        Saveconfig m_Save;
//        params m_pm;

};

#endif // DERIVEDWINDOW_H_INCLUDED

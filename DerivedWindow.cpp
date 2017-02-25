#include "DerivedWindow.h"
#include <iostream>
#include <thread>
#include <string>
#include <stdio.h>

#define TRACE_INPUT() std::cout << "Call: " << __PRETTY_FUNCTION__ << std::endl;
#define TRACE_OUTPUT() std::cout << "Exit: " << __PRETTY_FUNCTION__ << std::endl;

DerivedWindow::DerivedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
: Gtk::Window(cobject),
  m_refGlade(refGlade)
{
//    Read_conf();
//    Load_conf();
}

DerivedWindow::~DerivedWindow()
{
//    Save_conf();
}

//void DerivedWindow::Save_conf(std::string filename)
//{
//    m_Save.init(filename);
//    /*m_Save.add_data("Height", get_data_pWidth_Height());
//    m_Save.add_data("Width", get_data_pWidth_Width());
//    m_Save.add_data("Itera", get_data_pItera_Itera());
//    m_Save.add_data("Mod", get_data_pItera_Mod());
//    m_Save.add_data("Largeur", get_data_pWhere_Largeur());
//    m_Save.add_data("x", get_data_pWhere_x());
//    m_Save.add_data("y", get_data_pWhere_y());
//    m_Save.add_data("Filename", get_data_pFile_name());*/
//    m_Save.write();
//}
//void DerivedWindow::Read_conf(std::string filename)
//{
//    m_Save.init(filename);
//    m_Save.read();
//    Load_conf();
//}
//void DerivedWindow::Load_conf()
//{
//
//
//    set_on_case(m_Save.m_pmconfig);/*
//    pWidth_Height->set_text(conf_value("Height", m_Save.m_config["Height"]));
//    pWidth_Width->set_text(conf_value("Width", "1900"));
//    pItera_Itera->set_text(conf_value("Itera", "300"));
//    pItera_Mod->set_text(conf_value("Mod", "200"));
//    pWhere_Largeur->set_text(conf_value("Largeur", "4"));
//    pWhere_x->set_text(conf_value("x", "0"));
//    pWhere_y->set_text(conf_value("y", "0"));
//    pFile_name->set_text(conf_value("Filename", "Mandelbrot"));*/
//}
//std::string DerivedWindow::conf_value(std::string what, std::string default_value)
//{
//    return m_Save.value_of(what, default_value);
//}
bool DerivedWindow::on_key_press_event(GdkEventKey* key_event)
{
    //GDK_MOD1_MASK -> the 'alt' key(mask)
    //GDK_KEY_1 -> the '1' key
    //GDK_KEY_2 -> the '2' key

    if(key_event->keyval == GDK_KEY_Escape)
    {
        //close the window, when the 'esc' key is pressed
//        std::cout << "Test" << std::endl;
//        std::flush(std::cout);
        hide();
        return true;
    }
//    if(key_event->keyval == GDK_KEY_Return)
//    {
//        //close the window, when the 'esc' key is pressed
////        pGenerate->clicked();
//        return true;
//    }

    //if the event has not been handled, call the base class
    return Gtk::Window::on_key_press_event(key_event);
}

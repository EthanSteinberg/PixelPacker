/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#ifndef PIXEL_GUI_H_INCLUDED
#define PIXEL_GUI_H_INCLUDED

#include <boost/scoped_ptr.hpp>

#include <boost/utility.hpp>
#include <gtkmm.h>


class t_pixelGui : boost::noncopyable
{
public:
   t_pixelGui();
   void run();

private:
   void addFilesButtonPressed();
   void removeFilesButtonPressed();
   void selectedCallback(std::vector<std::string>  &files,const Gtk::TreeModel::iterator &);
   void removeWait();
   void processButtonPressed();
   void saveButtonPressed();
   bool pulseTheBar();

   std::string savename;

   Glib::RefPtr<Gtk::Builder> builder;
   Glib::RefPtr<Gtk::ListStore> list;

   boost::scoped_ptr<Gtk::Window> mainWindow;
   boost::scoped_ptr<Gtk::Dialog> waitingDialog;
   boost::scoped_ptr<Gtk::FileChooserDialog> chooseDialog;
   boost::scoped_ptr<Gtk::FileChooserDialog> saveDialog;

   Gtk::TreeView *view;
   Gtk::Button *addFilesButton;
   Gtk::Button *removeFilesButton;
   Gtk::Button *processButton;
   Gtk::Button *saveButton;

   Gtk::CheckButton *readableButton;
   Gtk::RadioButton *maxRectsButton;
   Gtk::RadioButton *shelfButton;
   Gtk::RadioButton *gilButton;

   Gtk::ProgressBar *theBar;

   class FileColumns : public Gtk::TreeModelColumnRecord
   {
   public:
      FileColumns()
      {
         add(m_Name);
         add(m_Picture);
         add(m_Size);
         add(m_Location);
         add(m_Area);
      }

      Gtk::TreeModelColumn<Glib::ustring> m_Name;
      Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > m_Picture;
      Gtk::TreeModelColumn<Glib::ustring> m_Size;
      Gtk::TreeModelColumn<Glib::ustring> m_Location;
      Gtk::TreeModelColumn<int> m_Area;
   } fileColumns;
};

#endif

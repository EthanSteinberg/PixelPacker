/*
-------------------------------------------------------------------------
This file is part of PixelPacker, tools to pack textures into as small as space as possible.

PixelPacker version 1 of 6 March 2011
Copyright (C) 2011 Ethan Steinberg <ethan.steinberg@gmail.com>

This program is released under the terms of the license contained
in the file COPYING.
---------------------------------------------------------------------------
*/


#include "pixelGui.h"
#include <gtk/gtk.h>
#include <iostream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include "../pak/pixelPak.h"
#include "../pak/algoShelfSimple.h"
#include "../pak/algoGil.h"
#include "../pak/algoMaxRects.h"

void startProcess(std::vector<std::string> filenames, bool readable, int algorithm, std::string outputName, sigc::slot<void> finished);

t_pixelGui::t_pixelGui()
{}

void t_pixelGui::run()
{
   savename = "pixelPack";
   builder = Gtk::Builder::create_from_file("../res/gui.glade"); 
   list = Gtk::ListStore::create(fileColumns);


   builder->get_widget("treeview1",view);
   view->set_model(list);
   view->append_column("Name",fileColumns.m_Name);
   view->append_column("Image",fileColumns.m_Picture);
   view->append_column("Size",fileColumns.m_Size);

   auto column  = view->get_column(0);
   column->set_resizable(true);
   column->set_sort_column(fileColumns.m_Name);

   column  = view->get_column(1);
   column->set_resizable(true);
   //column->set_sort_column(fileColumns.m_Area);

   column  = view->get_column(2);
   column->set_resizable(true);
   column->set_sort_column(fileColumns.m_Area);

   Glib::RefPtr<Gtk::TreeSelection> selection = view->get_selection();
   selection->set_mode(Gtk::SelectionMode::SELECTION_MULTIPLE);

   Gtk::Window *winPtr;
   builder->get_widget("window1",winPtr);
   mainWindow.reset(winPtr);

   Gtk::Dialog *diaPtr;
   builder->get_widget("dialog1",diaPtr);
   waitingDialog.reset(diaPtr);

   Gtk::FileChooserDialog *dia2Ptr;
   builder->get_widget("filechooserdialog1",dia2Ptr);
   chooseDialog.reset(dia2Ptr);


   builder->get_widget("button1",addFilesButton);
   addFilesButton->signal_clicked().connect(sigc::mem_fun(*this, &t_pixelGui::addFilesButtonPressed));

   builder->get_widget("button2",removeFilesButton);
   removeFilesButton->signal_clicked().connect(sigc::mem_fun(*this, &t_pixelGui::removeFilesButtonPressed));

   builder->get_widget("button3",processButton);
   processButton->signal_clicked().connect(sigc::mem_fun(*this, &t_pixelGui::processButtonPressed));

   builder->get_widget("button7",saveButton);
   saveButton->signal_clicked().connect(sigc::mem_fun(*this, &t_pixelGui::saveButtonPressed));

   builder->get_widget("progressbar1",theBar);

   builder->get_widget("checkbutton1",readableButton);
   builder->get_widget("radiobutton1",maxRectsButton);
   builder->get_widget("radiobutton2",shelfButton);
   builder->get_widget("radiobutton3",gilButton);

   Gtk::FileChooserDialog *lol = Glib::wrap(GTK_FILE_CHOOSER_DIALOG(gtk_file_chooser_dialog_new("save a file",mainWindow->gobj(),GTK_FILE_CHOOSER_ACTION_SAVE,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE,GTK_RESPONSE_ACCEPT,NULL)));
   saveDialog.reset(lol);

   Gtk::Main::run(*mainWindow);
}

bool t_pixelGui::pulseTheBar()
{
   if (!waitingDialog->get_visible())
      return false;

   theBar->pulse();
   return true;
}

void t_pixelGui::addFilesButtonPressed()
{
   
   int id =chooseDialog->run();
   chooseDialog->hide();

   if (id != 1)
      return;

   std::vector<std::string> files = chooseDialog->get_filenames();

   char buffer[100];

   BOOST_FOREACH(std::string &name, files)
   {
      auto iter = list->append();
      Glib::RefPtr<Gdk::Pixbuf>  image = Gdk::Pixbuf::create_from_file(name);
      boost::filesystem::path imagePath(name);

      snprintf(buffer,sizeof(buffer),"%d by %d",image->get_width(), image->get_height());
      int area = image->get_width() * image->get_height();
      image = image->scale_simple(25,25,Gdk::InterpType::INTERP_BILINEAR);

      iter->set_value(fileColumns.m_Name, Glib::ustring(imagePath.stem().native()));
      iter->set_value(fileColumns.m_Picture,image);
      iter->set_value(fileColumns.m_Size, Glib::ustring(buffer));
      iter->set_value(fileColumns.m_Location, Glib::ustring(name));
      iter->set_value(fileColumns.m_Area, area);
   
   }

}

void t_pixelGui::removeFilesButtonPressed()
{
   auto selected = view->get_selection();

   //selected->selected_foreach_iter(sigc::mem_fun(*this,&t_pixelGui::selectedCallback));
   std::vector<Gtk::TreeModel::Path> paths = selected->get_selected_rows();
   std::vector<Gtk::TreeRowReference> iters;

   BOOST_FOREACH(Gtk::TreeModel::Path aPath, paths)
   {
      iters.push_back(Gtk::TreeRowReference(list,aPath));
   }

   BOOST_FOREACH(Gtk::TreeRowReference iter, iters)
   {
      Gtk::TreeModel::Path aPath = iter.get_path();
      auto treeIter = list->get_iter(aPath);
      list->erase(treeIter);
   }

}


void t_pixelGui::selectedCallback(std::vector<std::string> &filenames,const Gtk::TreeModel::iterator &iter)
{
   auto blah = *iter;
   filenames.push_back(blah->get_value(fileColumns.m_Location));

   //return false;
}

void t_pixelGui::processButtonPressed()
{
   if (waitingDialog->get_visible())
   {
      Gtk::MessageDialog message("Sorry, you already have a task running");
      message.run();
      message.hide();
      return;
   }

   std::vector<std::string> filenames;

   sigc::slot<void> finished = sigc::mem_fun(*this, &t_pixelGui::removeWait);
   
   list->foreach_iter(sigc::bind_return(sigc::bind<0>(sigc::mem_fun(*this, &t_pixelGui::selectedCallback),sigc::ref(filenames)),false));

   int state = maxRectsButton->get_active() * 0 +
              shelfButton->get_active() * 2 +
             gilButton->get_active() * 1; 

   Glib::Thread::create(sigc::bind(&startProcess,filenames,readableButton->get_active(),state,savename,finished),false);
   waitingDialog->show();
   Glib::signal_timeout().connect(sigc::mem_fun(*this, &t_pixelGui::pulseTheBar),50);
}

void startProcess(std::vector<std::string> filenames, bool readable, int algorithm, std::string outputName, sigc::slot<void> finished)
{
      t_pixelPak packer;
      switch(algorithm)
      {
         case 0:
            packer = t_pixelPak(new t_algoMaxRects   ,readable);
            break;

         case 1:
            packer = t_pixelPak(new t_algoGil        ,readable);
            break;

         case 2:
            packer = t_pixelPak(new t_algoShelfSimple,readable);
            break;
      }

      std::pair<Magick::Image, std::string> output = packer.process(filenames);
      Magick::Image myPic = output.first;
      std::string jsonData = output.second;

      myPic.write(outputName + ".png");
      
      std::ofstream out(outputName + ".json");
      out<<jsonData;

      Glib::signal_idle().connect_once(finished);
}


void t_pixelGui::removeWait()
{
   waitingDialog->hide();
}

void t_pixelGui::saveButtonPressed()
{
   int result = saveDialog->run(); 
   saveDialog->hide();

   if (result == GTK_RESPONSE_ACCEPT)
   {
      savename = saveDialog->get_filename();


      boost::filesystem::path savePath(savename);
      saveButton->set_label(savePath.stem().native());
   }
}


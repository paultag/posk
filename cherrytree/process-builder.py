#!/usr/bin/env python

import sys
import gtk
  
class TutorialTextEditor:
    def on_Interface_destroy(self, widget, data=None):
        gtk.main_quit()
    def on_imagemenuitem5_activate_item( self, widget, data=None):
        gtk.main_quit()

    def on_imagemenuitem10_activate_item( self, widget, data=None):
        self.about = self.builder.get_object("About")
        self.about.show()
    def on_About_close( self, widget, data=None ):
        self.about.close()
    def on_Write_activate( self, widget, data=None ):
        runtime  = self.builder.get_object("ProcessRuntime")
        priority = self.builder.get_object("ProcessPriority")
        start    = self.builder.get_object("ProcessStart")

        print runtime.get_value()
        print priority.get_value()
        print start.get_value()

    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file("./resources/Interface.glade") 
        
        self.window = self.builder.get_object("Interface")
        self.builder.connect_signals(self)       

if __name__ == "__main__":
    editor = TutorialTextEditor()
    editor.window.show()
    gtk.main()


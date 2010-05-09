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
    def on_ProcessRuntime_value_changed( self, widget, data=None ):
        print "Kickass"
    def on_Write_activate( self, widget, data=None ):
        print self.runtime.get_value()
        print self.priority.get_value()
        print self.start.get_value()

    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file("./resources/Interface.glade") 
        
        self.window = self.builder.get_object("Interface")
        self.start    = self.builder.get_object("ProcessStart")
        self.priority = self.builder.get_object("ProcessPriority")
        self.runtime  = self.builder.get_object("ProcessRuntime")
        self.builder.connect_signals(self)       

if __name__ == "__main__":
    editor = TutorialTextEditor()
    editor.window.show()
    gtk.main()


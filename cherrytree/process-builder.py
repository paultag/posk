#!/usr/bin/env python

import sys
import gtk
import json
  
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
        start    = self.builder.get_object("ProcessStart")
        priority = self.builder.get_object("ProcessPriority")
        runtime  = self.builder.get_object("ProcessRuntime")

        resourceHD1 = self.builder.get_object("Resource")
        resourceHD2 = self.builder.get_object("Resource1")
        resourceNIC = self.builder.get_object("Resource2")
        resource1 = self.builder.get_object("Resource3")
        resource2 = self.builder.get_object("Resource4")
        resource3 = self.builder.get_object("Resource5")
        resource4 = self.builder.get_object("Resource6")
        resource5 = self.builder.get_object("Resource7")
        resource6 = self.builder.get_object("Resource8")
        resource7 = self.builder.get_object("Resource9")
        resource8 = self.builder.get_object("Resource10")
        resource9 = self.builder.get_object("Resource11")
        resourceA = self.builder.get_object("Resource12")
        resourceB = self.builder.get_object("Resource13")
        resourceC = self.builder.get_object("Resource14")

        output = {}
        output["time"]      = runtime.get_value_as_int()
        output["priority"]  = priority.get_value_as_int()
        output["start"]     = start.get_value_as_int()
        output["resources"] = {}
        resources = output["resources"]
        resources["nic"] = resourceNIC.get_active()
        resources["hd1"] = resourceHD1.get_active()
        resources["hd2"] = resourceHD2.get_active()
        resources["re1"] = resource1.get_active()
        resources["re2"] = resource2.get_active()
        resources["re3"] = resource3.get_active()
        resources["re4"] = resource4.get_active()
        resources["re5"] = resource5.get_active()
        resources["re6"] = resource6.get_active()
        resources["re7"] = resource7.get_active()
        resources["re8"] = resource8.get_active()
        resources["re9"] = resource9.get_active()
        resources["reA"] = resourceA.get_active()
        resources["reB"] = resourceB.get_active()
        resources["reC"] = resourceC.get_active()


        print json.dumps(output, sort_keys=True, indent=4)

    def __init__(self):
        self.builder = gtk.Builder()
        self.builder.add_from_file("./resources/Interface.glade") 
        self.window = self.builder.get_object("Interface")
        self.builder.connect_signals(self)       

if __name__ == "__main__":
    editor = TutorialTextEditor()
    editor.window.show()
    gtk.main()


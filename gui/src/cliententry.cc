#include "cliententry.h"
#include "glibmm/ustring.h"
#include "gtkmm/box.h"
#include "gtkmm/builder.h"

#include <string>
#include <iostream>

// For creating a dummy object in main.cc.
ClientEntry::ClientEntry(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder) {
    ClientEntry(cobject, builder, true, "127.0.0.1", 7000);
}

ClientEntry::ClientEntry(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder,
        bool active, Glib::ustring ip, int port)
: Gtk::Box(cobject), refBuilder(builder), client_switch(nullptr), ip_entry(nullptr), port_entry(nullptr) {
    client_switch = builder->get_widget<Gtk::Switch>("client_switch");
    if (client_switch) {
        client_switch->set_active(active);
    }
    ip_entry = builder->get_widget<Gtk::Entry>("ip_entry");
    if (ip_entry) {
        ip_entry->set_text(ip);
    }
    port_entry = builder->get_widget<Gtk::Entry>("port_entry");
    if (port_entry) {
        port_entry->set_text(std::to_string(port));
    }

    // connect signal handlers here
}

ClientEntry::~ClientEntry() {}

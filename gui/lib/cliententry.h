#ifndef CLIENT_ENTRY_H
#define CLIENT_ENTRY_H

#include <gtkmm/switch.h>
#include <gtkmm/entry.h>
#include <glibmm/refptr.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>

class ClientEntry : public Gtk::Box {
    public:
        ClientEntry(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
        ClientEntry(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder,
                bool active, Glib::ustring ip, int port);
        ~ClientEntry() override;

    private:
        Glib::RefPtr<Gtk::Builder> refBuilder;

        Gtk::Switch* client_switch;
        Gtk::Entry* ip_entry;
        Gtk::Entry* port_entry;
};

#endif /* ifndef CLIENT_ENTRY_H */

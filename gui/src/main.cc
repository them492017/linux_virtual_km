#include "cliententry.h"

#include <iostream>
#include "glibmm/fileutils.h"
#include "glibmm/markup.h"
#include "glibmm/refptr.h"
#include "gtkmm/box.h"
#include "gtkmm/button.h"
#include "gtkmm/enums.h"
#include "gtkmm/window.h"
#include <gtkmm/application.h>

void add_client(Gtk::Box* client_list) {
    auto refBuilder = Gtk::Builder::create_from_file("ui/cliententry.ui");
    ClientEntry* entry = Gtk::Builder::get_widget_derived<ClientEntry>(refBuilder, "entry", true, "127.0.0.1", 7000);
    if (entry) {
        client_list->append(*entry);
        // for (auto child: entry->get_children()) {
        //     client_list->append(*child);
        // }
        std::cout << "Appending entry" << std::endl;
    }
}

void on_app_activate(Glib::RefPtr<Gtk::Application> app) {
    auto refBuilder = Gtk::Builder::create();
    try {
        refBuilder->add_from_file("ui/mainwindow.ui");
    }
    catch (const Glib::FileError& err) {
        std::cerr << "FileError: " << err.what() << std::endl;
        return;
    }
    catch (const Glib::MarkupError& err) {
        std::cerr << "MarkupError: " << err.what() << std::endl;
        return;
    }
    catch (const Gtk::BuilderError& err) {
        std::cerr << "BuilderError: " << err.what() << std::endl;
        return;
    }

    auto win = refBuilder->get_widget<Gtk::Window>("win");

    if (!win) {
        std::cerr << "Couldn't get the window" << std::endl;
        return;
    }

    app->add_window(*win);
    win->set_visible(true);

    // set signal handler to add clients
    auto add_button = refBuilder->get_widget<Gtk::Button>("add_client_button");
    auto client_list = refBuilder->get_widget<Gtk::Box>("client_box");

    add_button->signal_clicked().connect([client_list] () { add_client(client_list); });

    // auto bTest = Gtk::Builder::create_from_file("ui/cliententry.ui");
    // ClientEntry* entry = Gtk::Builder::get_widget_derived<ClientEntry>(bTest, "entry");
    // win->set_child(*entry);
}

int main(int argc, char** argv) {
    auto app = Gtk::Application::create("com.github.them492017.linuxkm");

    app->signal_activate().connect([app] () { on_app_activate(app); });

    return app->run(argc, argv);
}

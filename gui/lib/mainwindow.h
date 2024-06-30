#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "glibmm/refptr.h"
#include "gtkmm/builder.h"
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
    public:
        MainWindow();
        ~MainWindow() override;

    private:
        Glib::RefPtr<Gtk::Builder> builder;
};

#endif /* ifndef MAIN_WINDOW_H */

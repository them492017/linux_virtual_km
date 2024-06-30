#include "mainwindow.h"
#include "gtkmm/builder.h"
#include <iostream>

MainWindow::MainWindow()
: builder(Gtk::Builder::create_from_file("mainwindow.ui")) {
    auto win = builder->get_widget<Gtk::Window>("win");
}

MainWindow::~MainWindow() {}

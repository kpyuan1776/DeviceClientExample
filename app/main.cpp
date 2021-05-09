#include <iostream>
#include <thread>

/*#include <boost/python.hpp>
#include <pygtk/pygtk.h>
#include <gtkmm.h>

using namespace boost::python;
*/

#include "mainwindow.h"
#include <QApplication>

#include "my_lib.h"

/*
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
*/
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
//namespace http = boost::beast::http;    // from <boost/beast/http.hpp>



using namespace std;



void processingTasks(string msg)
{
    cout << "start processing tasks:" << msg << endl;
    print_boost_version();
}


int main(int argc, char *argv[])
{
    
    
    thread thread_proc(processingTasks,"stuff");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    thread_proc.join();

    return a.exec();
}
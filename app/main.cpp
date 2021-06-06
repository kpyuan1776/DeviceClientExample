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
#include "messagehandling.h"
#include "devicestate.h"



#include <iostream>
#include <thread>


#include <boost/log/trivial.hpp>



using namespace std;

namespace logging = boost::log;



void initLogging()
{
    /*logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
    */
}






int main(int argc, char *argv[])
{
    initLogging();


    unique_ptr<DeviceBackendWorker> backendWorker = make_unique<DeviceBackendWorker>();
    BOOST_LOG_TRIVIAL(debug) << "start thread for background tasks";
    std::thread backendWorkerThread = backendWorker->go();


    QApplication app(argc, argv);
    MainWindow w{"test"};
    w.show();

    int res = app.exec();

    BOOST_LOG_TRIVIAL(info) << "join threads, main thread: id = " << this_thread::get_id();
    backendWorkerThread.join();

    return res;
}

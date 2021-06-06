#include "devicestate.h"


DeviceBackendWorker::DeviceBackendWorker()
{}

DeviceBackendWorker::~DeviceBackendWorker()
{}


void DeviceBackendWorker::backendLoop()
{
    info();

    
    //example "loop" for a specific state-flow
    for(int i=0; i<50; i++)
    {    
        device.process_event(MeasurementStarted{});
        info();
        device.process_event(MeasurementFinished{});
        info();
        device.process_event(VerifiedOnLatestVersion{});
        info();
    }
    
    info();
    device.process_event(MeasurementStarted{});
    info();
    device.process_event(MeasurementFinished{});
    info();
    device.process_event(NewVersionAvailable{});
    info();
    device.process_event(UpdateDownloadFinished{});
    info();
    
    device.process_event(NewVersionAvailable{});
}


std::thread DeviceBackendWorker::go()
{
    return thread([=] {backendLoop(); });
}


void DeviceBackendWorker::info()
{
    auto i = device.current_state()[0];
    BOOST_LOG_TRIVIAL(trace) << "The device is currently: " << device.state_names[i];
    //cout << "The device is currently: " << device.state_names[i] << "\n";
}
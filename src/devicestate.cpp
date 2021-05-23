#include "devicestate.h"


DeviceBackendWorker::DeviceBackendWorker()
{}

DeviceBackendWorker::~DeviceBackendWorker()
{}


void DeviceBackendWorker::loop()
{
    info();
    
    //example "game-loop" for a specific state-flow
    for(int i=0; i<5; i++)
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

void DeviceBackendWorker::info()
{
    auto i = device.current_state()[0];
    cout << "The device is currently: " << device.state_names[i] << "\n";
}
#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <boost/msm/back/state_machine.hpp>

#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;




//transition or events
struct MeasurementStarted {};
struct MeasurementFinished {};
struct VerifiedOnLatestVersion {};
struct NewVersionAvailable {};
struct UpdateDownloadFinished {};
struct SwitchOff {};


struct DeviceStateMachine : state_machine_def<DeviceStateMachine>
{

    vector<string> state_names  = {
        "default"s,
        "measuring"s,
        "checkversion"s,
        "download_update"s,
        "shutdown"s
    };

    struct Default : state<> {};

    struct Measuring : state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const& evt, FSM&)
        {
            cout << "do measurement..." << endl;
        }

    };

    struct CheckVersion: state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const& evt, FSM&)
        {
            cout << "check version..." << endl;
        }
    };


    struct DownloadUpdate: state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const& evt, FSM&)
        {
            cout << "download update..." << endl;
        }
    };


    struct Shutdown: state<>
    {
        template <class Event, class FSM>
        void on_entry(Event const& evt, FSM&)
        {
            cout << "shutdown..." << endl;
        }
    };

    //transition table
    //mpl::vector<Row<start_state, event, target_state>,...>
    struct transition_table : mpl::vector<
        Row<Default,MeasurementStarted,Measuring>,
        Row<Measuring,MeasurementFinished,CheckVersion>,
        Row<CheckVersion,VerifiedOnLatestVersion,Default>,
        Row<CheckVersion,NewVersionAvailable,DownloadUpdate>,
        Row<DownloadUpdate,UpdateDownloadFinished,Shutdown>,
        Row<Default,SwitchOff,Shutdown>
    > {};

    typedef Default initial_state;


    template <class FSM, class Event>
    void no_transition(Event const& e, FSM&, int state)
    {
        cout << "No transition from state " << state_names[state]
            << " on event " << typeid(e).name() << endl;
    }

};



class DeviceBackendWorker
{
  public:
    DeviceBackendWorker();
    ~DeviceBackendWorker();
    void loop();
    void info();

  private:
    msm::back::state_machine<DeviceStateMachine> device;

};


#endif //end DEVICE_STATE_H
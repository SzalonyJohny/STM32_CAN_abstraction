#include <array>
#include <cstdint>
#include <stdio.h>

#include "hal_can.hpp"
#include "message_abstraction.hpp"

//CanHeaders
#include "CanHeaders/PM08-CANBUS-APPS.hpp"
#include "CanHeaders/PM08-CANBUS-AQ_CARD.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_LV.hpp"
#include "CanHeaders/PM08-CANBUS-BMS_HV.hpp"
#include "CanHeaders/PM08-CANBUS-DASH.hpp"
#include "CanHeaders/PM08-CANBUS-LAP_TIMER.hpp"
#include "CanHeaders/PM08-CANBUS-SF.hpp"
#include "CanHeaders/PM08-CANBUS-STEERING_WHEEL.hpp"
#include "CanHeaders/PM08-CANBUS-TC.hpp"
#include "CanHeaders/PM08-CANBUS-TELEMETRY.hpp"

namespace new_can
{

  class Can_interface
  {

      Device<Apps_main> apps{ APPS_MAIN_CAN_ID };
      Device<AQ_main> aq_main{ AQ_MAIN_CAN_ID };
      Device<AQ_air_flow> aq_air_flow{ AQ_AIR_FLOW_CAN_ID };
      Device<BMS_HV_main> bms_hv_main{ BMS_HV_MAIN_CAN_ID };
      Device<BMS_LV_main> bms_lv_main{ BMS_LV_MAIN_CAN_ID };
      Device<BMS_LV_temperature> bms_lv_temperature{ BMS_LV_TEMPERATURE_CAN_ID };
      Device<Dash_Main> dash_main{ DASH_MAIN_CAN_ID };
      Device<Dash_StateChange> dash_statechange{ DASH_STATECHANGE_CAN_ID };
      Device<Lap_timer_Main> laptimer_main{ LAP_TIMER_MAIN_CAN_ID };
      Device<Lap_timer_StateChange> laptimer_statechange{ LAP_TIMER_STATECHANGE_CAN_ID };
      Device<SF_main> sf_main{ SF_MAIN_CAN_ID };
      Device<SF_data_frame_0> sf_data_0{ SF_DATA_FRAME_0_CAN_ID };
      Device<SF_data_frame_1> sf_data_1{ SF_DATA_FRAME_1_CAN_ID };
      Device<SF_data_frame_2> sf_data_2{ SF_DATA_FRAME_2_CAN_ID };
      Device<SF_data_frame_3> sf_data_3{ SF_DATA_FRAME_3_CAN_ID };
      Device<SF_data_frame_4> sf_data_4{ SF_DATA_FRAME_4_CAN_ID };
      Device<SF_data_frame_5> sf_data_5{ SF_DATA_FRAME_5_CAN_ID };
      Device<Steering_Wheel_main> steering_wheel_main{ STEERING_WHEEL_MAIN_CAN_ID };
      Device<Steering_Wheel_event> steering_wheel_event{ STEERING_WHEEL_EVENT_CAN_ID };
      Device<TS_main> ts_main{ TS_MAIN_CAN_ID };
      Device<TS_rear_suspension> ts_rear_suspension{ TS_REAR_SUSPENSION_CAN_ID };
      Device<Telemetry_Main> telemetry_main{ TELEMETRY_MAIN_CAN_ID };

      std::array<Device_base*, 23> device_array = { &apps, &aq_main, &aq_air_flow, &bms_hv_main,
                                          &bms_lv_main, &bms_lv_temperature, &dash_main, &dash_statechange,
                                          &laptimer_main, &laptimer_statechange, &sf_main, &sf_data_0, &sf_data_1,
                                          &sf_data_2, &sf_data_2, &sf_data_3, &sf_data_4, &sf_data_5, &steering_wheel_main,
                                          &steering_wheel_event, &ts_main, &ts_rear_suspension, &telemetry_main };

  public:
    Can_interface() {}
    
    void get_message(Can_rx_message &m)
    {
      for (auto &dev : device_array)
      {
        if (dev->IDE == m.header.IDE)
        {
          dev->set_data(m);
          return; // to exit void
        }
      }
    }

    const Apps_main& get_apps_main() { return apps.data; }
    const AQ_main& get_aq_main() { return aq_main.data; }
    const AQ_air_flow& get_aq_air_flow() { return aq_air_flow.data; }
    const BMS_HV_main& get_bms_hv_main() { return bms_hv_main.data; }
    const BMS_LV_main& get_bms_lv_main() { return bms_lv_main.data; }
    const BMS_LV_temperature& get_bms_lv_temperature() { return bms_lv_temperature.data; }
    const Dash_Main& get_dash_main() { return dash_main.data; }
    const Dash_StateChange& get_dash_state_change() { return dash_statechange.data; }
    const Lap_timer_Main& get_laptimer_main() { return laptimer_main.data; };
    const Lap_timer_StateChange& get_laptimer_statechange() { return laptimer_statechange.data };
    const SF_main& get_sf_main() { return sf_main.data; }
    const SF_data_frame_0& get_sf_dataframe_0() { return sf_data_0.data; }
    const SF_data_frame_1& get_sf_dataframe_1() { return sf_data_1.data; }
    const SF_data_frame_2& get_sf_dataframe_2() { return sf_data_2.data; }
    const SF_data_frame_3& get_sf_dataframe_3() { return sf_data_3.data; }
    const SF_data_frame_4& get_sf_dataframe_4() { return sf_data_4.data; }
    const SF_data_frame_5& get_sf_dataframe_5() { return sf_data_5.data; }
    const Steering_Wheel_main& get_steering_wheel_main() { return steering_wheel_main.data; }
    const Steering_Wheel_event& get_steering_wheel_event() { return steering_wheel_event.data; }
    const TS_main& get_tc_main() { return ts_main.data; }
    const TS_rear_suspension& get_tc_rear() { return ts_rear_suspension.data; }
    const Telemetry_Main& get_telemetry_main() { return telemetry_main.data; }


  };
} // namespace new_can
#include <array>
#include <cstdint>
#include <stdio.h>

#include "hal_can.hpp"
#include "acquisition_card_def.hpp"
#include "apps_def.hpp"
#include "message_abstraction.hpp"

namespace new_can
{

  class can_interface
  {

    device<apps_data> apps{APPS_CAN_ID};
    device<acquisition_card_data> ac{AC_CAN_ID};
    
    std::array<device_base *, 2> device_array = {&apps, &ac /*all devices */};

  public:
    void disp()
    {
      printf("Apps IDE: %d \n", (int)apps.IDE);
      printf("Apps status: %d \n", (int)apps.data.apps_status);
      printf("Apps value: %d \n", apps.data.apps_value);
      printf("Apps d_dt: %d \n\n", apps.data.d_apps_dt);
    }

    void get_message(can_rx_message &m)
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

    apps_data get_apps_data() const { return apps.data; }

    acquisition_card_data get_acquisition_card_data() const { return ac.data; }
  };

} // namespace new_can
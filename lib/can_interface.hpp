#include <array>
#include <cstdint>
#include <stdio.h>

#include "hal_can.hpp"
#include "acquisition_card_def.hpp"
#include "apps_def.hpp"
#include "message_abstraction.hpp"

namespace new_can
{

  class Can_interface
  {

    Device<Apps_data> apps{APPS_CAN_ID};
    Device<Acquisition_card_data> ac{AC_CAN_ID};

    std::array<Device_base *, 2> device_array = {&apps, &ac /*all devices */};

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

    const Apps_data & get_apps_data() const { return apps.data; }
    const Acquisition_card_data & get_acquisition_card_data() const { return ac.data; }
  };
} // namespace new_can
#include <array>
#include <cstdint>
#include <stdio.h>

#include "hal_can.hpp"
#include "acquisition_card_def.hpp"
#include "apps_def.hpp"
#include "message_abstraction.hpp"

namespace new_can
{

  typedef void (*ErrorHandlerFunction)(void);

  class Can_interface
  {
    ErrorHandlerFunction error_func;

    bool unhandled_error;

    Device<Apps_data> apps{APPS_CAN_ID};
    Device<Acquisition_card_data> ac{AC_CAN_ID};
    
    Device<Apps_error> apps_error{APPS_CAN_ERROR_ID};

    std::array<Device_base *, 2> device_array = {&apps, &ac /*all devices */};
    std::array<Device_base *, 2> errors_array = {&apps_error};

  public:
    Can_interface(ErrorHandlerFunction func = nullptr): error_func(func), unhandled_error(false) { }
    
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

      for (auto &dev: errors_array) {
        if (dev->IDE == m.header.IDE) {
          dev->set_data(m);
          if (error_func not_eq nullptr)
            error_func();
          
          unhandled_error = true;
          return;
        }
      }
    }

    void set_error_function(ErrorHandlerFunction error_handler) { error_func = error_handler; }
    void clear_error_function() { error_func = nullptr; }

    bool is_unhandled() const { return unhandled_error; }
    void set_unhandled(bool error_state) { unhandled_error = error_state; }

    const Apps_data & get_apps_data() const { return apps.data; }
    const struct Apps_error & get_apps_error() const { return apps_error.data; }

    const Acquisition_card_data & get_acquisition_card_data() const { return ac.data; }
  };
} // namespace new_can
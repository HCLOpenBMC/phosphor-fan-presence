/**
 * Copyright © 2021 IBM Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "shutdown_alarm_monitor.hpp"
#include "threshold_alarm_logger.hpp"
#include <sdbusplus/bus.hpp>
#include <sdeventplus/event.hpp>
#include <phosphor-logging/log.hpp>
#include "power_state.hpp"
#include <iostream>
#include "nlohmann/json.hpp"
#include <fstream>
#include <iomanip>


using namespace sensor::monitor;

int main(int argc, char* argv[])
{
 
    phosphor::logging::log<phosphor::logging::level::ERR>(
                        "main is started ");
  
    auto event = sdeventplus::Event::get_default();
    auto bus = sdbusplus::bus::new_default();
    bus.attach_event(event.get(), SD_EVENT_PRIORITY_NORMAL);

 
    std::shared_ptr<phosphor::fan::PowerState> powerState =
        std::make_shared<phosphor::fan::PGoodState>();
                               
   phosphor::logging::log<phosphor::logging::level::ERR>(
                        "started the  shuutdownalarm monitor");
          
     ShutdownAlarmMonitor shutdownMonitor{bus, event, powerState};
    

     phosphor::logging::log<phosphor::logging::level::ERR>(
                        "Threshold alarm logger  is started ");
  
    ThresholdAlarmLogger logger{bus, event, powerState};
 

    return event.loop();
}

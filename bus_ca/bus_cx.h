#ifndef _BUS_H_
#define _BUS_H_

#include "bus_if.h"
#include <iostream>

class Bus_cx : public sc_module, public bus_if
{
public:
  sc_port<bus_if,0> bus_port;
  sc_export<bus_if> bus_export;
  void write( unsigned addr, unsigned  data );
  void read(  unsigned addr, unsigned &data );
  sc_mutex bus_mutex;
  sc_time delay;
  void end_of_elaboration();
  unsigned decode(unsigned addr);
  unsigned *starts, *ends;
  Bus_cx( sc_module_name mn, double bus_delay, sc_time_unit delay_unit )
  : sc_module(mn), delay(bus_delay, delay_unit)
  {
    bus_export.bind(*this);
  }
};

#endif

#ifndef _BUS_PV_H_
#define _BUS_PV_H_

#include "bus_if.h"
#include <iostream>

class Bus_pv : public sc_module, public bus_if
{
public:
  sc_port<bus_if,0> bus_port;
  sc_export<bus_if> bus_export;
  void write( unsigned addr, unsigned  data );
  void read(  unsigned addr, unsigned &data );
  void end_of_elaboration();
  unsigned decode(unsigned addr);
  unsigned *starts, *ends;
  Bus_pv( sc_module_name mn )
  : sc_module(mn)
  {
    bus_export.bind(*this);
  }
};

#endif

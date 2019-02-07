#ifndef _BUS_CA_H_
#define _BUS_CA_H_

#include "bus_if.h"
#include <iostream>

class Bus_ca : public sc_module, public ext_bus_if
{
public:
  sc_port<bus_if,0> bus_port;
  sc_export<ext_bus_if> bus_export;	//connected to the masters
  sc_in<bool> clock;
  void write( unsigned addr, unsigned  data, unsigned id );
  void read(  unsigned addr, unsigned &data, unsigned id );
  void write( unsigned addr, unsigned  data )
  { write(addr,data,0); }
  void read(  unsigned addr, unsigned &data )
  { read(addr,data,0); }
  void end_of_elaboration();
  unsigned decode(unsigned addr);
  unsigned *starts, *ends;
  bool     *request;
  sc_event *grant;
  sc_event ack;
  unsigned masters;
  void arbitrate();
  SC_HAS_PROCESS(Bus_ca);
  Bus_ca( sc_module_name mn, unsigned num_masters )
  : sc_module(mn)
  {
    bus_export.bind(*this);
    SC_THREAD(arbitrate);
    sensitive << clock.pos();
    masters = num_masters;
    request = new bool[masters];
    grant   = new sc_event[masters];
  }
  ~Bus_ca() {
	  delete[] request;
	  delete[] grant;
	}
};

#endif

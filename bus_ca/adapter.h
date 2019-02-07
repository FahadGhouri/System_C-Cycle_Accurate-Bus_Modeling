#ifndef _ADAPTER_H_
#define _ADAPTER_H_

#include "bus_if.h"

class Adapter : public sc_module, public bus_if
{
public:
  sc_out<int> x;
  sc_out<int> y;
  sc_in<int>  s;

  unsigned start_addr1, start_addr2, start_addr3, block_size;
  
  unsigned addition_status;

  unsigned id;

  sc_export<bus_if> Adapter_export;

  sc_port<ext_bus_if,1> init_port;

  void process();

  sc_event run;

  void write( unsigned addr, unsigned  data );
  void read(  unsigned addr, unsigned &data );

  void write( unsigned addr, unsigned  data, unsigned id); 
  void read(  unsigned addr, unsigned &data, unsigned id);
  
  SC_HAS_PROCESS(Adapter);

  Adapter( sc_module_name mn, unsigned id=0) : sc_module(mn)
  {
    Adapter_export.bind(*this);
    this->id=id;
    SC_THREAD(process);
    sensitive<<run;
    return; // alternative: export the bus_if here
  }

};

#endif

#ifndef _NEW_MASTER_H_
#define _NEW_MASTER_H_

#include "bus_if.h"

SC_MODULE(New_master)
{
  sc_port<ext_bus_if,1> initiator_port;

  void action();
  SC_HAS_PROCESS(New_master);
  New_master( sc_module_name mn, unsigned id )
    : sc_module(mn),
    id(id)
  {
    SC_THREAD(action);
  }

private:
  unsigned id;
};

#endif

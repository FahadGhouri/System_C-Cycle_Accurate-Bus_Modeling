#ifndef _BUS_IF_H_
#define _BUS_IF_H_

#include "systemc.h"

class bus_if : virtual public sc_interface
{
public:
  virtual void write( unsigned addr, unsigned  data ) = 0;
  virtual void read(  unsigned addr, unsigned &data ) = 0;
};

class ext_bus_if : virtual public bus_if
{
public:
  virtual void write( unsigned addr, unsigned  data, unsigned id ) = 0;
  virtual void read(  unsigned addr, unsigned &data, unsigned id ) = 0;
};

#endif

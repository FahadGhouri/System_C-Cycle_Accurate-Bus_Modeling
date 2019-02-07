#include "master.h"

void Master::action()
{
  unsigned data;
  wait(10, SC_NS);
  for( unsigned addr = start; addr <= end; addr++ )
  {
    data = rand() % 256;
    initiator_port->write(addr, data, id);
    cout << name() << " write(" << addr << ", " << data << ")" 
         << " at " << sc_time_stamp() << endl;
    wait(1, SC_NS);
  }
  for( unsigned addr = start; addr <= end; addr++ )
  {
    initiator_port->read(addr, data, id);
    cout << name() << " read(" << addr << ", " << data << ")" 
         << " at " << sc_time_stamp() << endl;
    wait(1, SC_NS);
  }
  wait();
}

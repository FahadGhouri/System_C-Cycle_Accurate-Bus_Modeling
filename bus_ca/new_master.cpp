#include "new_master.h"

void New_master::action()
{
  unsigned data1=0;
  wait(1000, SC_NS); 
  initiator_port->write(1024, 0, id);
  initiator_port->write(1025, 16, id);
  initiator_port->write(1026, 64, id);
  initiator_port->write(1027, 16, id);
  initiator_port->write(1028, 1, id);
  initiator_port->read(1028, data1, id);
  while(data1==1)
    initiator_port->read(1028, data1, id);
  sc_stop();
  wait();
}

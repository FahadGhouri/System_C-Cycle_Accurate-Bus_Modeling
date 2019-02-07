#include "bus_ca.h"

void Bus_ca::arbitrate() // round robin
{
  unsigned next = 0;
  unsigned i;
  for(;;)
  {
    wait();
    i = 0;
    while(i < masters)
      if( request[(next+i)%masters] )
      {
        grant[(next+i)%masters].notify(SC_ZERO_TIME);
        wait(ack);
        next = (next+1)%masters;
	i = masters; // finish while loop
      } 
      else i++;
  }
}

void Bus_ca::write( unsigned addr, unsigned  data, unsigned id )
{
  request[id] = true;
  wait( grant[id] ); // arbitration phase
  bus_port[decode(addr)]->write(addr,data);
  wait(clock.posedge_event()); // address phase
  wait(clock.posedge_event()); // data phase
  request[id] = false;
  ack.notify();
}

void Bus_ca::read(  unsigned addr, unsigned &data, unsigned id )
{
  request[id] = true;
  wait( grant[id] ); // arbitration phase
  bus_port[decode(addr)]->read(addr,data);
  wait(clock.posedge_event()); // address phase
  wait(clock.posedge_event()); // data phase
  request[id] = false;
  ack.notify();
}

void Bus_ca::end_of_elaboration()
{
  unsigned i, slave_start, slave_end;
  ifstream mem_map("mem_map.txt");
  unsigned slaves = bus_port.size();
  starts = new unsigned[slaves];
  ends   = new unsigned[slaves];
  mem_map >> i;
  while( mem_map )
  { 
    mem_map >> slave_start >> slave_end;
    if( i >= slaves )
    {
       cout << "Bus ERROR: slave number does not exist" << endl;
       sc_stop();
    }
    else
    { 
      starts[i] = slave_start;
      ends[i]   = slave_end;
      cout << "Bus slave " << i << " starts " 
           << slave_start << " ends " << slave_end << endl;
    } 
    mem_map >> i;
  }
}

unsigned Bus_ca::decode(unsigned addr)
{
  for( int i = 0; i < bus_port.size(); i++ )
  {
    if( (addr >= starts[i]) && (addr <= ends[i]) ) return i;
  }
  cout << "Bus ERROR: address " << addr << " not found" << endl;
  return 0;
}

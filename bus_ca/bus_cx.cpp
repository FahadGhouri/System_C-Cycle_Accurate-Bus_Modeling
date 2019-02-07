#include "bus_cx.h"

void Bus_cx::write( unsigned addr, unsigned  data )
{
  bus_mutex.lock();
  bus_port[decode(addr)]->write(addr,data);
  wait( delay );
  bus_mutex.unlock();
}

void Bus_cx::read(  unsigned addr, unsigned &data )
{
  bus_mutex.lock();
  bus_port[decode(addr)]->read(addr,data);
  wait( delay );
  bus_mutex.unlock();
}

void Bus_cx::end_of_elaboration()
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

unsigned Bus_cx::decode(unsigned addr)
{
  for( int i = 0; i < bus_port.size(); i++ )
  {
    if( (addr >= starts[i]) && (addr <= ends[i]) ) return i;
  }
  cout << "Bus ERROR: address " << addr << " not found" << endl;
  return 0;
}

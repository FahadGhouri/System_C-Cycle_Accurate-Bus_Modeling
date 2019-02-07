#include "master.h"
#include "ram.h"
#include "bus_cx.h"
#include "bus_ca.h"
#include "adapter.h"
#include "adder.h"
#include "new_master.h"

int sc_main(int argc, char *argv[])
{
  Master master1("master1", 0, 17, 0);
  Ram    ram1("ram1", 0, 16);
  Master master2("master2", 20, 31, 1);
  Ram    ram2("ram2", 16,16);
  New_master master3("master3", 2);
  Ram    ram3("ram3", 64,16);
  Adder  adder("adder");
  Adapter adpt("adpt", 3);

  Bus_ca bus("bus", 4);

  sc_clock clk("clk",5,SC_NS,0.5);

  bus.clock(clk);

  sc_signal<int> ch_x, ch_y, ch_s;
  master1.initiator_port(bus.bus_export);
  master2.initiator_port(bus.bus_export);
  master3.initiator_port(bus.bus_export);
  bus.bus_port(ram1.target_export);
  bus.bus_port(ram2.target_export);
  bus.bus_port(ram3.target_export);
  bus.bus_port(adpt.Adapter_export);
  adpt.init_port(bus.bus_export);  

  adpt.x(ch_x);
  adpt.y(ch_y);
  adpt.s(ch_s);
  adder.x(ch_x);
  adder.y(ch_y);
  adder.s(ch_s);
  sc_start(5000, SC_NS);
  ram1.dump(cout);
  ram2.dump(cout);
  ram3.dump(cout);
  return 0;
}

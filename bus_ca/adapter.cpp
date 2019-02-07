#include "adapter.h"

void Adapter::write(unsigned addr, unsigned  data, unsigned id) {
    init_port->write(addr, data, id);
    cout << name() << " write(" << addr << ", " << data << ")" 
         << " at " << sc_time_stamp() << endl;
    wait(1, SC_NS);
}

void Adapter::read( unsigned addr, unsigned &data, unsigned id) {
    init_port->read(addr, data, id);
    cout << name() << " read(" << addr << ", " << data << ")" 
         << " at " << sc_time_stamp() << endl;
    wait(1, SC_NS);
}

void Adapter::write(unsigned addr, unsigned  data) {
switch(addr) {
  case 1024 :
    start_addr1=data;
    break;
  case 1025 :
    start_addr2=data;
    break;
  case 1026 :
    start_addr3=data;
    break;
  case 1027 :
    block_size=data;
    break;
  case 1028 :
    addition_status=data;
    if(addition_status==1)
        run.notify();
    break;
  default :
    cout << "Adapter: write to invalid address" << endl;
  }
}

void Adapter::read( unsigned addr, unsigned &data){
 switch(addr) {
  case 1024 :
    data=start_addr1;
    break;
  case 1025 :
    data=start_addr2;
    break;
  case 1026 :
    data=start_addr3;
    break;
  case 1027 :
    data=block_size;
    break;
  case 1028 :
    data=addition_status;
    break;
  default :
    cout << "Adapter: read from invalid address" << endl;
  }
}

void Adapter::process(){
    unsigned data1, data2, data3;
    for(;;){
        wait();
        for(unsigned i=0;i<block_size;i++){
            read(start_addr1+i,data1,id);
            x.write(data1);
            read(start_addr2+i,data2,id);
            y.write(data2);
            wait(10, SC_NS);
            data3=s.read();
            write(start_addr3+i,data3,id);
        }
        addition_status=0;
    }
}

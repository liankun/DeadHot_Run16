#include<fstream>

void get_new_key(){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);
  MpcExMapper* mapper = MpcExMapper::instance();
  ofstream o_txt("key_to_new_key.txt");  
  for(int i = 0;i < 24576*2;i++){
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    int index = 6*quadrant+sensor;
    int lx = mapper->get_lx(i);
    int ly = mapper->get_ly(i);
    int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
    o_txt<<i<<" "<<new_key<<endl;
  }
}

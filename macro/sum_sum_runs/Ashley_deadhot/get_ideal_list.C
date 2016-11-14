#include<fstream>
void get_ideal_list(){
  ofstream ashley_ideal_list("ashley_ideal_list.txt");
  gSystem->Load("libMyMpcEx.so");
  MpcExMapper* mapper = MpcExMapper::instance();
  for(int i = 0;i < 24576*2;i++){
    int lx = mapper->get_lx(i);
    if(lx==6) ashley_ideal_list<<i<<endl;
    if(lx==18) ashley_ideal_list<<i<<endl;
  }
}

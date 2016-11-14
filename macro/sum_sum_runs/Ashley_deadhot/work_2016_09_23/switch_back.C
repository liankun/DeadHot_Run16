#include<fstream>
void switch_back(){
  ifstream deadhot_channel("deadhot_channel.txt");
  int key;
  int good_high;
  int good_low;
  gSystem->Load("libMyMpcEx.so");
  MpcExMapper* mapper = MpcExMapper::instance();

  ofstream bad_key("deadhot_channel_switch_back.txt");
  while(deadhot_channel>>key>>good_high>>good_low){
    int arm = mapper->get_arm(key);
    int packet = mapper->get_packet(key);
    int chain = mapper->get_chain(key);

    int key_modi=key;


    if(arm==0 && packet==7 && chain==0){
      key_modi=key+2304;
    }
    
    if(arm==0 && packet==7 && chain==3){
      key_modi=key-2304;
    }

    bad_key<<key_modi<<" "<<good_high<<" "<<good_low<<endl;
  }
}

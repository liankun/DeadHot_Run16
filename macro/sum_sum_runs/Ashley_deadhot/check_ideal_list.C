#include<fstream>
#include<map>
#include<set>
void check_ideal_list(){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);
  MpcExMapper* mapper = MpcExMapper::instance();

  ifstream ideal_list("ashely_idealkeys_north.txt");
  ifstream high_list("high_deadhot_stat_add_discrete.txt");
  ifstream low_list("low_deadhot_stat_add_discrete.txt");
  set<int> ideal_set;
  map<int,int>high_map;
  map<int,int>low_map;
  int key;
  int freq;
  
  
  while(ideal_list>>key){
    int arm = mapper->get_arm(key);
    int packet = mapper->get_packet(key);
    int chain = mapper->get_chain(key);
    int chip = mapper->get_chip(key);
    int key_modi=key;
    int lx = mapper->get_lx(key);
    int ly = mapper->get_ly(key);
    int layer = mapper->get_layer(key);
    int quadrant = mapper->get_quadrant(key);
    int sensor = mapper->get_sensor_in_quadrant(key);


    if(arm==0 && packet==7 && chain==0){
      key_modi=key+2304;
    }
    if(arm==0 && packet==7 && chain==3){
      key_modi=key-2304;
    }

    cout<<key<<" lx "<<lx<<" ly "<<ly<<" "<<layer<<" "<<quadrant<<" "<<sensor<<endl;

   

    ideal_set.insert(key_modi);
  }
  while(high_list>>key>>freq){
    high_map.insert(pair<int,int>(key,freq));
  }
  while(low_list>>key>>freq){
    low_map.insert(pair<int,int>(key,freq));
  }

  cout<<"high gain: "<<endl;
  /*
  for(set<int>::iterator it = ideal_set.begin();it!=ideal_set.end();it++){
    int key = *it;
    if(high_map.find(key)!=high_map.end()){
      if(high_map.find(key)->second < 27)continue;
      cout<<high_map.find(key)->first<<" "<<high_map.find(key)->second<<endl;
    }    
  }

  cout<<"low gain: "<<endl;
  for(set<int>::iterator it = ideal_set.begin();it!=ideal_set.end();it++){
    int key = *it;
    if(low_map.find(key)!=low_map.end()){
      if(low_map.find(key)->second<27)continue;
      cout<<low_map.find(key)->first<<" "<<low_map.find(key)->second<<endl;
    }    
  }
  */
}

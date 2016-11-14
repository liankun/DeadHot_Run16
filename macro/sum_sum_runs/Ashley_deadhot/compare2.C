#include<fstream>
#include<set>
void compare2(){
  gSystem->Load("libMyMpcEx.so");
  MpcExMapper* mapper = MpcExMapper::instance();
  ifstream ashely_deadhot("bad_keys_for_all_runs.txt");
  ifstream liankun_deadhot("list_B_plus_C_plus_E.txt");
  ifstream refer_high("high_real_deadhot_add_discrete.txt");
  ifstream refer_low("low_real_deadhot_add_discrete_final.txt");
  set<int> ashley_high_set;
  set<int> ashley_low_set;
  set<int> ashley_deadhot_set;
  set<int> liankun_deadhot_set;
  set<int> liankun_high_set;
  set<int> liankun_low_set;
  set<int> refer_high_set;
  set<int> refer_low_set;

  int key;
  int high_is_good=0;
  int low_is_good=0;

  while(ashely_deadhot>>key>>high_is_good>>low_is_good){
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
    
    if(high_is_good == 1){
      ashley_high_set.insert(key_modi);
    }
    
    if(low_is_good == 1){
      ashley_low_set.insert(key_modi);
    }
  }

  while(refer_high>>key){
    refer_high_set.insert(key);
  }
 
  while(refer_low>>key){
    refer_low_set.insert(key);
  }

  while(liankun_deadhot>>key){
    if(refer_high_set.find(key)!=refer_high_set.end()){
      liankun_high_set.insert(key);
    }
    if(refer_low_set.find(key)!=refer_low_set.end()){
      liankun_low_set.insert(key);
    }
  }
  
  cout<<"high bad liankun: "<<liankun_high_set.size()<<endl;
  cout<<"high bad Ashley:  "<<ashley_high_set.size()<<endl;
  int count=0;
  ofstream ashley_only_high("ashley_only_high_final.txt");
  
  for(set<int>::iterator it = ashley_high_set.begin();it != ashley_high_set.end();it++){
    int key = *it;
    if(liankun_high_set.find(key)!=liankun_high_set.end()){
      count++;
    }
    else{
      ashley_only_high<<key<<endl;
    }
  }
  cout<<"same: "<<count<<endl;

  cout<<"low bad liankun: "<<liankun_low_set.size()<<endl;
  cout<<"low bad Ashley:  "<<ashley_low_set.size()<<endl;
  count = 0;
  ofstream ashley_only_low("ashley_only_low_final.txt");
  for(set<int>::iterator it = ashley_low_set.begin();it != ashley_low_set.end();it++){
    int key = *it;
    if(liankun_low_set.find(key)!=liankun_low_set.end()){
      count++;
    }
    else{
      ashley_only_low<<key<<endl;
    }
  }
  cout<<"same "<<count<<endl;
}

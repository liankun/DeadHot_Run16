#include<fstream>
#include<set>
void check_bad_key(){
  ifstream high_deadhot("high_real_deadhot_add_discrete.txt");
  ifstream low_deadhot("low_real_deadhot_add_discrete.txt");
  ifstream low_deadhot_large_adc("low_real_deadhot_add_discrete_large_adc.txt");

  set<int> high_deadhot_set;
  set<int> low_deadhot_set;
  set<int> low_deadhot_large_adc_set;

  int key;
  while(high_deadhot>>key){
    high_deadhot_set.insert(key);
  }

  while(low_deadhot>>key){
    low_deadhot_set.insert(key);
  }

  while(low_deadhot_large_adc>>key){
    low_deadhot_large_adc_set.insert(key);
  }

    
//  ifstream deadhot_hot("deadhot_channel.txt");
  ifstream deadhot_hot("deadhot_channel_switch_back.txt");
  int high_good;
  int low_good;
  int number_high = 0;
  int number_low = 0;
  int number_low2 = 0;
  gSystem->Load("libMyMpcEx.so");
  MpcExMapper* mapper = MpcExMapper::instance();
  
  while(deadhot_hot>>key>>high_good>>low_good){
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
 
    
    if(high_good==1){
      if(high_deadhot_set.find(key_modi)==high_deadhot_set.end()){
        cout<<"in deadhot channel not in high_deadhot_set"<<end;
      }
      number_high++;
    }
    else{
      if(high_deadhot_set.find(key_modi)!=high_deadhot_set.end()){
        cout<<"not in deadhot channel in high_deadhot_set"<<end;
      }
    }
    
    if(low_good==1){
      if(low_deadhot_set.find(key_modi)==low_deadhot_set.end()){
        cout<<"in deadhot channel not in low_deadhot_set"<<end;
      }
      number_low++;
    }
    if(low_good==2){
      if(low_deadhot_large_adc_set.find(key_modi)!=low_deadhot_large_adc_set.end()){
        cout<<"in deadhot channel in low_deadhot_large_adc_set"<<end;
      }
      
      if(low_deadhot_set.find(key_modi)==low_deadhot_set.end()){
        cout<<"in deadhot channel not in low_deadhot_set"<<end;
      }
      number_low++;
      
      if(high_good==0)number_low2++;
    }
    if(low_good==0){
      if(low_deadhot_large_adc_set.find(key_modi)!=low_deadhot_large_adc_set.end()){
        cout<<"not in deadhot channel in low_deadhot_large_adc_set"<<end;
      }
      if(low_deadhot_set.find(key_modi)!=low_deadhot_set.end()){
        cout<<"not in deadhot channel in low_deadhot_set"<<end; 
      }
    }
  }
  cout<<"number of high: "<<number_high<<endl;
  cout<<"number of low: "<<number_low<<endl;
  cout<<"number of low large: "<<number_low2<<endl;
}

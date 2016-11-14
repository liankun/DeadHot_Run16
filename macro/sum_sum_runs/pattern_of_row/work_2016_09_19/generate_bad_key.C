#include<fstream>
#include<set>
void generate_bad_key(){
  ifstream high_deadhot("high_bad_list_merge.txt");
  ifstream low_deadhot("low_bad_list_merge.txt");
  ifstream low_deadhot_large_adc("low_bad_up_range_add_discrete_list.txt");

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

  
  ofstream deadhot_hot("deadhot_channel.txt");
  for(int i = 0;i<16*24*128;i++){
    int high_good=0;
    int low_good=0;
    if(high_deadhot_set.find(i)!=high_deadhot_set.end()){
      high_good=1;
    }
    if(low_deadhot_set.find(i)!=low_deadhot_set.end()){
      low_good=1;
    }
    if(low_deadhot_large_adc_set.find(i)==low_deadhot_large_adc_set.end()){
      if(low_deadhot_set.find(i)!=low_deadhot_set.end()){
        low_good=2;
      }
    }
    deadhot_hot<<i<<" "<<high_good<<" "<<low_good<<endl;
  }
}

#include<fstream>
#include<set>
#include<map>
void compare3(){
  ifstream high_deadhot_stat("high_deadhot_stat_add_discrete_new.txt");
  ifstream low_deadhot_stat("low_deadhot_stat_add_discrete_new.txt");
  
  ifstream ashley_only_high("ashley_high_only.txt");
  ifstream ashley_only_low("ashley_low_only.txt");

  map<int,int> high_deadhot_stat_map;
  map<int,int> low_deadhot_stat_map;

  set<int> ashley_high_only_set;
  set<int> ashley_low_only_set;

  int key;
  int freq;
  
  while(high_deadhot_stat>>key>>freq){
    high_deadhot_stat_map.insert(pair<int,int>(key,freq));
  }

  while(low_deadhot_stat>>key>>freq){
    low_deadhot_stat_map.insert(pair<int,int>(key,freq));
  }

  while(ashley_only_high>>key){
    ashley_high_only_set.insert(key);
  }

  while(ashley_only_low>>key){
    ashley_low_only_set.insert(key);
  }

  for(set<int>::iterator it = ashley_high_only_set.begin();it!=ashley_high_only_set.end();it++){
    int key = *it;
    if(high_deadhot_stat_map.find(key)!=high_deadhot_stat_map.end()){
      cout<<"key: "<<high_deadhot_stat_map.find(key)->first<<" "
          <<high_deadhot_stat_map.find(key)->second<<endl;
    }
  }
}

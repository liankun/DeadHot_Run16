#include<fstream>
#include<map>
void pull_c_in_freq(){
  ifstream high_deadhot_stat("high_deadhot_stat.txt");
  ifstream low_deadhot_stat("low_deadhot_stat.txt");
  map<int,int>high_stat_map;
  map<int,int>low_stat_map;
  int key;
  int freq;
  while(high_deadhot_stat>>key>>freq){
//    cout<<key<<" "<<freq<<endl;
    high_stat_map.insert(pair<int,int>(key,freq));
  }
  while(low_deadhot_stat>>key>>freq){
//    cout<<key<<" "<<freq<<endl;
    low_stat_map.insert(pair<int,int>(key,freq));
  }
  
  //high part
  ofstream high_want_deadhot("why_deadhot_in_freq/high_want_deadhot_0_10.txt");
  for(map<int,int>::iterator it=high_stat_map.begin();it!=high_stat_map.end();++it){
    int key = it->first;
    int freq = it->second;
    if(freq >=10 || freq < 0)continue;
    high_want_deadhot<<key<<endl;    
  }

  ofstream low_want_deadhot("why_deadhot_in_freq/low_want_deadhot_0_10.txt");
  for(map<int,int>::iterator it=low_stat_map.begin();it!=low_stat_map.end();++it){
    int key = it->first;
    int freq = it->second;
    if(freq >=10 || freq < 0)continue;
    low_want_deadhot<<key<<endl;    
  }
 
}

#include<fstream>
#include<map>
void classify_stat(){
  ifstream in_high_txt("high_deadhot_stat_no_discrete.txt");
  ifstream in_low_txt("low_deadhot_stat_no_discrete.txt");
  
  map<int,int>high_map;
  map<int,int>low_map;

  int key;
  int freq;

  while(in_high_txt>>key>>freq){
    high_map.insert(pair<int,int>(key,freq));
  }

  while(in_low_txt>>key>>freq){
    low_map.insert(pair<int,int>(key,freq));
  }

  ofstream out_high_txt("high_deadhot_freq_no_discrete_0_44.txt");
  ofstream out_low_txt("low_deadhot_freq_no_discrete_0_44.txt");
  
  for(map<int,int>::iterator it = high_map.begin();it!=high_map.end();it++){
    int key = it->first;
    int freq = it->second;
    if(freq<45 && freq>=0){
      out_high_txt<<key<<endl;
    }
  }
  
  for(map<int,int>::iterator it = low_map.begin();it!=low_map.end();it++){
    int key = it->first;
    int freq = it->second;
    if(freq<45 && freq>=0){
      out_low_txt<<key<<endl;
    }
  }
}

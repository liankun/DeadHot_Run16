#include<fstream>
#include<set>
#include<map>
void find_channel(){
  ifstream reuse_channel("low_reuse_list.txt");
  int num_c;
  int num_line;
  int num_index;
  
  set<int>reuse_set;
  while(reuse_channel>>num_c>>num_line>>num_index){
    int the_ch = num_c*100+num_line*10+num_index;
    reuse_set.insert(the_ch);
  }

  map<int,int> reuse_map;
  int key;
  ifstream reuse_key_txt("low_output_info.txt");
  while(reuse_key_txt>>key>>num_c>>num_index){
    int the_ch = num_c*100+num_index-1;
    reuse_map.insert(pair<int,int>(the_ch,key));
  }

  ofstream reuse_key_out("low_key_reuse.txt");
  for(set<int>::iterator it = reuse_set.begin();it!=reuse_set.end();++it){
    int the_ch = *it;
    if(reuse_map.find(the_ch)!=reuse_map.end()){
      int key = reuse_map[the_ch];
      reuse_key_out<<key<<endl;
    }
    else{
      cout<<"find no key in map"<<endl;
    }
  }
  ofstream bad_key_out("low_bad_key.txt");
  for(map<int,int>::iterator it2 = reuse_map.begin();it2!=reuse_map.end();++it2){
    int the_ch = it2->first;
    if(reuse_set.find(the_ch)==reuse_set.end()){
      bad_key_out<<it2->second<<endl;
    }
  }
}

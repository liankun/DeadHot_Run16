#include<fstream>
#include<set>
#include<map>
void remove_discrete_from_list(){
  ifstream disceret_list("low_discrete.txt");
  ifstream deadhot_list("low_real_deadhot_add_discrete.txt");
  set<int> disceret_set;
  set<int> deadhot_set;
  map<int,int>deadhot_map;
  int key;
  int freq;
  while(disceret_list>>key){
    disceret_set.insert(key);
  }
  while(deadhot_list>>key){
    deadhot_set.insert(key);
//    deadhot_map.insert(pair<int,int>(key,freq));
  }
  ofstream output("low_real_deadhot_no_discrete.txt");
  for(set<int>::iterator it=deadhot_set.begin();it!=deadhot_set.end();++it){
    int key = *it;
    if(disceret_set.find(key)==disceret_set.end()){
      output<<key<<endl;
    }
  }
}

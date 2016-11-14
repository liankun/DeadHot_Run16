#include<fstream>
#include<set>
void make_reuse_deadhot(){
  ifstream high_reuse_txt("high_key_reuse.txt");
  ifstream low_reuse_txt("low_key_reuse.txt");
  ifstream high_deadhot_txt("high_real_deadhot_add_discrete.txt");
  ifstream low_deadhot_txt("low_real_deadhot_add_discrete.txt");
  
  set<int> high_reuse_set;
  set<int> low_reuse_set;
  int key;
  while(high_reuse_txt>>key){
    high_reuse_set.insert(key);
  }
  while(low_reuse_txt>>key){
    low_reuse_set.insert(key);
  }

  ofstream high_deadhot_out("high_real_deadhot_add_discrete_remove_reuse.txt");
  ofstream low_deadhot_out("low_real_deadhot_add_discrete_remove_reuse.txt");
  while(high_deadhot_txt>>key){
    if(high_reuse_set.find(key)==high_reuse_set.end()){
      high_deadhot_out<<key<<endl; 
    }
  }

  while(low_deadhot_txt>>key){
    if(low_reuse_set.find(key)==low_reuse_set.end()){
      low_deadhot_out<<key<<endl; 
    }
  }
}

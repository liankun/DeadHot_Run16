#include<fstream>
#include<set>
//add discrete for low
void add_discrete(){
  ifstream in_low_discrete_txt("low_discrete.txt");
  ifstream in_low_up_range_txt("low_bad_up_range_list.txt");
  set<int> low_discrete_set;
  set<int> low_up_range_set;

  int key;
  int key2;
  while(in_low_discrete_txt>>key>>key2){
    if(key!=key2){
      cout<<"key != key2"<<endl;
    }
    low_discrete_set.insert(key);
    low_up_range_set.insert(key);
  }

  while(in_low_up_range_txt>>key){
    low_up_range_set.insert(key);
  }

  ofstream out_low_up_range_txt("low_bad_up_range_add_discrete_list.txt");
  for(set<int>::iterator it=low_up_range_set.begin();it!=low_up_range_set.end();++it){
    int set_key=(*it);
//    if(low_discrete_set.find(set_key)==low_discrete_set.end()){
      out_low_up_range_txt<<set_key<<endl;
//    }
  }
}

#include<fstream>
#include<set>

void compare(){
  ifstream in_file0("high_bad_list_merge.txt");
  ifstream in_file1("low_bad_list_merge.txt");

  set<int> set0;
  set<int> set1;
  
  int key;
  while(in_file0>>key){
    set0.insert(key);
  }

  while(in_file1>>key){
    set1.insert(key);
  }

  int num=0;
  for(set<int>::iterator it=set0.begin();it!=set0.end();++it){
    int key = (*it);
    if(set1.find(key)!=set1.end()){
      num++;
    }
  }
  cout<<"number of file 0: "<<set0.size()<<endl;
  cout<<"number of file 1: "<<set1.size()<<endl;
  cout<<"same: "<<num<<endl;
}

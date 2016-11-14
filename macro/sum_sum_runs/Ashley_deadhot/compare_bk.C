#include<fstream>
#include<set>
void compare(){
  ifstream a_high_deadhot("high_deadhot_key_3_4cut_new.txt");
  ifstream a_low_deadhot("low_deadhot_key_3_4cut_new.txt");
  ifstream l_high_deadhot("high_real_deadhot_add_discrete.txt");
  ifstream l_low_deadhot("low_real_deadhot_add_discrete.txt");
  ifstream deadhot_db("deadhot_from_db.txt");
  set<int> high_deadhot_db;
  set<int> low_deadhot_db;
  set<int> high_bad_ped_db;
  set<int> low_bad_ped_db;
  set<int> a_high_bad_set;
  set<int> a_low_bad_set;
  set<int> l_high_bad_set;
  set<int> l_low_bad_set;

  int key;
  int high_deadhot;
  int high_bad_ped;
  int low_deadhot;
  int low_bad_ped;
  while(deadhot_db>>key>>high_deadhot>>high_bad_ped>>low_deadhot>>low_bad_ped){
//    if(key<24576)continue;
    if(high_deadhot > 0) high_deadhot_db.insert(key);
    if(low_deadhot > 0) low_deadhot_db.insert(key);
    if(high_deadhot ==0 && high_bad_ped > 0) high_bad_ped_db.insert(key);
    if(low_deadhot ==0 && low_bad_ped > 0) low_bad_ped_db.insert(key);
  }
  
  while(a_high_deadhot>>key){    
    a_high_bad_set.insert(key);
  }

  while(a_low_deadhot>>key){
    a_low_bad_set.insert(key);
  }

  while(l_high_deadhot>>key){
//    if(key<24576)continue;
    l_high_bad_set.insert(key);  
  }

  while(l_low_deadhot>>key){
//    if(key<24576)continue;
    l_low_bad_set.insert(key);
  }

  int count=0;
  for(std::set<int>::iterator it=l_high_bad_set.begin(); it!=l_high_bad_set.end(); ++it){
    int key = *it;
    if(a_high_bad_set.find(key)!=a_high_bad_set.end())count++;
  }
  cout<<"high gain bad key Liankun: "<<l_high_bad_set.size()<<endl;
  cout<<"high gian bad key Ashley: "<<a_high_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;
  
  count=0;
  for(std::set<int>::iterator it=l_low_bad_set.begin(); it!=l_low_bad_set.end(); ++it){
    int key = *it;
    if(a_low_bad_set.find(key)!=a_low_bad_set.end())count++;
  }
  cout<<"low gain bad key Liankun: "<<l_low_bad_set.size()<<endl;
  cout<<"low gain bad key Ashley: "<<a_low_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

  count=0;
  for(std::set<int>::iterator it=high_deadhot_db.begin(); it!=high_deadhot_db.end(); ++it){
    int key = *it;
    if(a_high_bad_set.find(key)!=a_high_bad_set.end())count++;
  }
  cout<<"high gain bad key DB: "<<high_deadhot_db.size()<<endl;
  cout<<"high gain bad key Ashley: "<<a_high_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

  count=0;
  for(std::set<int>::iterator it=low_deadhot_db.begin(); it!=low_deadhot_db.end(); ++it){
    int key = *it;
    if(a_low_bad_set.find(key)!=a_low_bad_set.end())count++;
  }
  cout<<"low gain bad key DB: "<<low_deadhot_db.size()<<endl;
  cout<<"low gain bad key Ashley: "<<a_low_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

  count=0;
  for(std::set<int>::iterator it=high_bad_ped_db.begin(); it!=high_bad_ped_db.end(); ++it){
    int key = *it;
    if(a_high_bad_set.find(key)!=a_high_bad_set.end())count++;
  }
  cout<<"high gain bad ped key DB: "<<high_bad_ped_db.size()<<endl;
  cout<<"high gain bad key Ashley: "<<a_high_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

  count=0;
  for(std::set<int>::iterator it=low_bad_ped_db.begin(); it!=low_bad_ped_db.end(); ++it){
    int key = *it;
    if(a_low_bad_set.find(key)!=a_low_bad_set.end())count++;
  }
  cout<<"low gain bad ped key DB: "<<low_bad_ped_db.size()<<endl;
  cout<<"low gain bad key Ashley: "<<a_low_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

  count=0;
  for(std::set<int>::iterator it=high_deadhot_db.begin(); it!=high_deadhot_db.end(); ++it){
    int key = *it;
    if(l_high_bad_set.find(key)!=l_high_bad_set.end())count++;
  }
  cout<<"high gain deadhot key DB: "<<high_deadhot_db.size()<<endl;
  cout<<"high gain bad key Liankun: "<<l_high_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;
 
  count=0;
  for(std::set<int>::iterator it=low_deadhot_db.begin(); it!=low_deadhot_db.end(); ++it){
    int key = *it;
    if(l_low_bad_set.find(key)!=l_low_bad_set.end())count++;
  }
  cout<<"low gain deadhot key DB: "<<low_deadhot_db.size()<<endl;
  cout<<"low gain bad key Liankun: "<<l_low_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

  count=0;
  for(std::set<int>::iterator it=high_bad_ped_db.begin(); it!=high_bad_ped_db.end(); ++it){
    int key = *it;
    if(l_high_bad_set.find(key)!=l_high_bad_set.end())count++;
  }
  cout<<"high gain bad ped key DB: "<<high_bad_ped_db.size()<<endl;
  cout<<"high gain bad key Liankun: "<<l_high_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

  count=0;
  for(std::set<int>::iterator it=low_bad_ped_db.begin(); it!=low_bad_ped_db.end(); ++it){
    int key = *it;
    if(l_low_bad_set.find(key)!=l_low_bad_set.end())count++;
  }
  cout<<"low gain bad ped key DB: "<<low_bad_ped_db.size()<<endl;
  cout<<"low gain bad key Liankun: "<<l_low_bad_set.size()<<endl;
  cout<<"same key: "<<count<<endl;

// spy channel
  count=0;
  for(int i=0;i<24576*2;i++){
    if(i%128 == 14 ){
      int key = i;
      if(l_high_bad_set.find(key)!=l_high_bad_set.end())count++;
    }
  }
  cout<<"number of spy in Liankun: "<<count<<endl;

  count=0;
  for(int i=0;i<24576*2;i++){
    if(i%128 == 14){
      int key = i;
      if(a_high_bad_set.find(key)!=a_high_bad_set.end())count++;
    }
  }
  cout<<"number of spy in Ashely: "<<count<<endl;

  //print out different keys
  //Ashley only
  ofstream a_high_only("ashley_high_only2.txt");
  for(std::set<int>::iterator it=a_high_bad_set.begin(); it!=a_high_bad_set.end(); ++it){
    int key = *it;
    if(l_high_bad_set.find(key)==l_high_bad_set.end())a_high_only<<key<<endl;
  }
 
  ofstream a_low_only("ashley_low_only2.txt");
  for(std::set<int>::iterator it=a_low_bad_set.begin(); it!=a_low_bad_set.end(); ++it){
    int key = *it;
    if(l_low_bad_set.find(key)==l_low_bad_set.end())a_low_only<<key<<endl;
  }

  ofstream l_high_only("liankun_high_only2.txt");
  for(std::set<int>::iterator it=l_high_bad_set.begin(); it!=l_high_bad_set.end(); ++it){
    int key = *it;
    if(a_high_bad_set.find(key)==a_high_bad_set.end())l_high_only<<key<<endl;
  }

  ofstream l_low_only("liankun_low_only2.txt");
  for(std::set<int>::iterator it=l_low_bad_set.begin(); it!=l_low_bad_set.end(); ++it){
    int key = *it;
    if(a_low_bad_set.find(key)==a_low_bad_set.end())l_low_only<<key<<endl;
  }

  ofstream same_high_only("same_high_only2.txt");
  for(std::set<int>::iterator it=l_high_bad_set.begin(); it!=l_high_bad_set.end(); ++it){
    int key = *it;
    if(a_high_bad_set.find(key)!=a_high_bad_set.end())same_high_only<<key<<endl;
  }

  ofstream same_low_only("same_low_only2.txt");
  for(std::set<int>::iterator it=l_low_bad_set.begin(); it!=l_low_bad_set.end(); ++it){
    int key = *it;
    if(a_low_bad_set.find(key)!=a_low_bad_set.end())same_low_only<<key<<endl;
  }


  ofstream same_high("same_high_ped2.txt");
  for(std::set<int>::iterator it=l_high_bad_set.begin(); it!=l_high_bad_set.end(); ++it){
    int key = *it;
    if(a_high_bad_set.find(key)!=a_high_bad_set.end())same_high<<key<<endl;
  }

  ofstream same_low("same_low_ped2.txt");
  for(std::set<int>::iterator it=l_low_bad_set.begin(); it!=l_low_bad_set.end(); ++it){
    int key = *it;
    if(a_low_bad_set.find(key)!=a_low_bad_set.end())same_low<<key<<endl;
  }

}

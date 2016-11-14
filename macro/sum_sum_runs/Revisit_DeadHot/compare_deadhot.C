#include<fstream>
#include<set>
void compare_deadhot(){
  ifstream deadhot_db("deadhot_from_db.txt");
  int key;
  int high_deadhot;
  int low_deadhot;
  int high_bad_ped;
  int low_bad_ped;
  set<int> high_deadhot_db;
  set<int> low_deadhot_db;
  set<int> high_bad_ped_db;
  set<int> low_bad_ped_db;
  while(deadhot_db>>key>>high_deadhot>>high_bad_ped>>low_deadhot>>low_bad_ped){
    if(high_deadhot > 0) high_deadhot_db.insert(key);
    if(low_deadhot > 0) low_deadhot_db.insert(key);
    if(high_deadhot ==0 && high_bad_ped > 0) high_bad_ped_db.insert(key);
    if(low_deadhot ==0 && low_bad_ped > 0) low_bad_ped_db.insert(key);
  }
 
  
  ifstream high_real_deadhot("out.txt");
  ifstream low_real_deadhot("good_low_deadhot_large_adc.txt");
  set<int> high_deadhot_no_db;
  set<int> low_deadhot_no_db;
  
  while(high_real_deadhot>>key){
    high_deadhot_no_db.insert(key);
  }
  while(low_real_deadhot>>key){
    low_deadhot_no_db.insert(key);
  }

  //statistic part
  int count = 0;
  cout<<"high deadhot from DB: "<<high_deadhot_db.size()<<endl;
  cout<<"high deadhot from No DB: "<<high_deadhot_no_db.size()<<endl;
  for(std::set<int>::iterator it=high_deadhot_db.begin(); it!=high_deadhot_db.end(); ++it){
     int ch = (*it);
     if(high_deadhot_no_db.find(ch)!=high_deadhot_no_db.end()) count++;
  }
  cout<<"Same key: "<<count<<endl;
  
  count=0;
  cout<<"low deadhot from DB: "<<low_deadhot_db.size()<<endl;
  cout<<"low deadhot from No DB: "<<low_deadhot_no_db.size()<<endl;
  for(std::set<int>::iterator it=low_deadhot_db.begin(); it!=low_deadhot_db.end(); ++it){
     int ch = (*it);
     if(low_deadhot_no_db.find(ch)!=low_deadhot_no_db.end()) count++;
   }
   cout<<"Same key: "<<count<<endl;
 
  count = 0;
  cout<<"high bad pedestal: "<<high_bad_ped_db.size()<<endl;
  for(std::set<int>::iterator it=high_bad_ped_db.begin(); it!=high_bad_ped_db.end(); ++it){
    int ch = (*it);
    if(high_deadhot_no_db.find(ch)!=high_deadhot_no_db.end()) count++;
  }
  cout<<"same key: "<<count<<endl;

  count=0;
  cout<<"low bad pedestal: "<<low_bad_ped_db.size()<<endl;
   for(std::set<int>::iterator it=low_bad_ped_db.begin(); it!=low_bad_ped_db.end(); ++it){
    int ch = (*it);
    if(low_deadhot_no_db.find(ch)!=low_deadhot_no_db.end()) count++;
  }
  cout<<"same key: "<<count<<endl; 


  count=0;
  for(std::set<int>::iterator it=low_deadhot_no_db.begin(); it!=low_deadhot_no_db.end(); ++it){
    int ch= (*it);
    if(high_deadhot_no_db.find(ch)!=high_deadhot_no_db.end()) count++;
    
  }
  
  cout<<"both high low deadhot: "<<count<<endl;


   ofstream high_deadhot_db_out("high_deadhot_db.txt");
   for(std::set<int>::iterator it=high_deadhot_db.begin(); it!=high_deadhot_db.end(); ++it){
     high_deadhot_db_out << *it <<endl;
   }

   ofstream low_deadhot_db_out("low_deadhot_db.txt");
   for(std::set<int>::iterator it=low_deadhot_db.begin(); it!=low_deadhot_db.end(); ++it){
     low_deadhot_db_out << *it <<endl;
   }

   ofstream only_low_deadhot("good_low_deadhot_large_adc2.txt");
   for(std::set<int>::iterator it=low_deadhot_no_db.begin(); it!=low_deadhot_no_db.end(); ++it){
    int ch= (*it);
    if(high_deadhot_no_db.find(ch)==high_deadhot_no_db.end()) only_low_deadhot<<ch<<endl;
  }

}

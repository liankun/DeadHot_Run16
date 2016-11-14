#include<fstream>
#include<map>
void statistic(){
  ifstream run_list_north("key_list_from_ashley_north.txt");
  ifstream run_list_south("key_list_from_ashley_south.txt");
  string s;
  map<int,int>high_key_stat;
  map<int,int>low_key_stat;
  for(int i = 0;i < 24576*2;i++){
    high_key_stat.insert(pair<int,int>(i,0));
    low_key_stat.insert(pair<int,int>(i,0));
  }

  TH1D* hhigh_run = new TH1D("hhigh_run","Number of High gain dead hot vs Run Number",50,-0.5,49.5);
  
  TH1D* hlow_run = new TH1D("hlow_run","Number of Low gain dead hot vs Run Number",50,-0.5,49.5);
  
  int run_count=0;
  while(getline(run_list_south,s)){
    cout<<"process "<<s<<endl;
    ifstream bad_key_list(s.c_str());
    int key;
    int high_is_good;
    int low_is_good;
    int high_num=0;
    int low_num=0;
    while(bad_key_list>>key>>high_is_good>>low_is_good){
//      cout<<key<<" "<<high_is_good<<" "<<low_is_good<<endl;
      if(high_is_good == 1){
        high_key_stat[key]++;
        high_num++;  
      }
      if(low_is_good == 1){
        low_key_stat[key]++; 
        low_num++;
      }
    }
    hhigh_run->Fill(run_count,high_num);
    hlow_run->Fill(run_count,low_num);
    run_count++;
  }

  run_count=0;
  while(getline(run_list_north,s)){
    cout<<"process "<<s<<endl;
    ifstream bad_key_list(s.c_str());
    int key;
    int high_is_good;
    int low_is_good;
    int high_num=0;
    int low_num=0;
    while(bad_key_list>>key>>high_is_good>>low_is_good){
//      cout<<key<<" "<<high_is_good<<" "<<low_is_good<<endl;
      if(high_is_good == 1){
        high_key_stat[key]++;
        high_num++;  
      }
      if(low_is_good == 1){
        low_key_stat[key]++; 
        low_num++;
      }
    }
    hhigh_run->Fill(run_count,high_num);
    hlow_run->Fill(run_count,low_num);
    run_count++;
  }



  TH1D* hhigh_freq = new TH1D("hhigh_freq","high gain freqency for north",50,-0.5,49.5);
  hhigh_freq->GetXaxis()->SetTitle("Freqency");

  TH1D* hlow_freq = new TH1D("hlow_freq","low gain freqency for north",50,-0.5,49.5);
  hlow_freq->GetXaxis()->SetTitle("Freqency");


  ofstream high_deadhot_key("high_deadhot_key_3_4cut_new.txt");
  ofstream low_deadhot_key("low_deadhot_key_3_4cut_new.txt");

  for(std::map<int,int>::iterator it=high_key_stat.begin(); it!=high_key_stat.end(); ++it){
    if((it->second) > 0){
      hhigh_freq->Fill(it->second);
    
    }
    if((it->second) > 7){
      high_deadhot_key<<it->first<<endl; 
    }
  }
  
  for(std::map<int,int>::iterator it=low_key_stat.begin(); it!=low_key_stat.end(); ++it){
    if((it->second) > 0){
      hlow_freq->Fill(it->second);    
    }
    if((it->second) > 7){
      low_deadhot_key<<it->first<<endl;
    }
  }

  TFile* ofile = new TFile("stat_new.root","RECREATE");
  hhigh_freq->Write();
  hlow_freq->Write();
  hhigh_run->Write();
  hlow_run->Write();
}

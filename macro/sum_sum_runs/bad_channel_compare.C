#include<set>
#include<fstream>
void bad_channel_compare(int group=0){
  gSystem->Load("libMyMpcEx.so");
  char path[500];
  sprintf(path,"%d/deadhot_adc_row.root",group);
  TFile* file = new TFile(path,"READONLY");
  if(!file){
    cout<<path<<" not exist !"<<endl;
    return;
  }

  sprintf(path,"%d/sum_sum.root",group);
  TFile* file2 = new TFile(path,"READONLY");
  if(!file2){
    cout<<path<<" not exist !"<<endl;
    return;
  }

  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");


  TH2D* hhigh_adc_row = (TH2D*)file->Get("hhigh_adc_row");
  TH2D* hlow_adc_row = (TH2D*)file->Get("hlow_adc_row");
  TH2D* hhigh_adc_r = (TH2D*)file->Get("hhigh_adc_r");
  TH2D* hlow_adc_r = (TH2D*)file->Get("hlow_adc_r");

  MpcExMapper* mapper = MpcExMapper::instance();
  sprintf(path,"%d/high_deadhot.txt",group);
  ifstream bad_high_itg_total(path);
  sprintf(path,"%d/low_deadhot.txt",group);
  ifstream bad_low_itg_total(path);

  std::set<int> bad_high_itg_list;
  std::set<int> bad_low_itg_list;

  int key;
  int new_key;
  while(bad_high_itg_total>>key>>new_key){
    bad_high_itg_list.insert(key);
  }

  while(bad_low_itg_total>>key>>new_key){
    bad_low_itg_list.insert(key);
  }

  for(set<int>::iterator it = bad_high_itg_list.begin();it!=bad_high_itg_list.end();it++){
    int key = *it;

  }
}

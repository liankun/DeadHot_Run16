#include<fstream>
#include<set>
#include<map>
void get_deadhot_ped_all(){
  TH2D* hhigh_deadhot_ped = new TH2D("hhigh_deadhot_ped","high Dead Hot Pedestal",2000,-0.5,1999.5,300,-40-0.5,260-0.5);
  hhigh_deadhot_ped->GetXaxis()->SetTitle("Dead hot Channel");
  hhigh_deadhot_ped->GetYaxis()->SetTitle("Pedestal");

  TH2D* hlow_deadhot_ped = new TH2D("hlow_deadhot_ped","low Dead Hot Pedestal",2000,-0.5,1999.5,300,-40-0.5,260-0.5);
  hlow_deadhot_ped->GetXaxis()->SetTitle("Dead hot Channel");
  hlow_deadhot_ped->GetYaxis()->SetTitle("Pedestal");

  TH1D* hhigh_rms_stat = new TH1D("hhigh_rms_stat","high ped rms",100,0,5);
  TH1D* hlow_rms_stat = new TH1D("hlow_rms_stat","low ped rms",100,0,5);

  ifstream high_deadhot_ped_txt("high_bad_ped.txt");
  ifstream low_deadhot_ped_txt("low_bad_ped.txt");

  set<int> high_deadhot_ped_list;
  set<int> low_deadhot_ped_list;
  map<int,int> high_key_map;
  map<int,int> low_key_map;


  int key;
  double ped;

  while(high_deadhot_ped_txt>>key>>ped){
    high_deadhot_ped_list.insert(key);
  }

  while(low_deadhot_ped_txt>>key>>ped){
    low_deadhot_ped_list.insert(key);
  }

  for(int i = 0;i < 44;i++){
    char path[500];
    sprintf(path,"%d/sum_sum.root",i);
    TFile* ifile = new TFile(path,"READONLY");
    if(!ifile) continue;
    TH2D* hhigh_adc_key = (TH2D*)ifile->Get("hhigh_adc_key");
    TH2D* hlow_adc_key = (TH2D*)ifile->Get("hlow_adc_key");
    
    int the_bad = 0;
    for(std::set<int>::iterator it=high_deadhot_ped_list.begin(); it!=high_deadhot_ped_list.end(); ++it){
      int key = (*it);
      hhigh_adc_key->SetAxisRange(key,key,"x");
      TH1D* htemp = hhigh_adc_key->ProjectionY();
      int max_bin = htemp->GetMaximumBin();
      double bin_center = htemp->GetBinCenter(max_bin);
      hhigh_deadhot_ped->Fill(the_bad,bin_center);
      high_key_map.insert(std::pair<int,int>(the_bad,key));
      the_bad++;
    }
    
    the_bad=0;
    for(std::set<int>::iterator it=low_deadhot_ped_list.begin(); it!=low_deadhot_ped_list.end(); ++it){
      int key = (*it);
      hlow_adc_key->SetAxisRange(key,key,"x");
      TH1D* htemp = hlow_adc_key->ProjectionY();
      int max_bin = htemp->GetMaximumBin();
      double bin_center = htemp->GetBinCenter(max_bin);
      hlow_deadhot_ped->Fill(the_bad,bin_center);
      low_key_map.insert(std::pair<int,int>(the_bad,key));
      the_bad++;
    }
    ifile->Close();
  }

  ofstream high_ped_rms("high_ped_rms.txt");
  ofstream low_ped_rms("low_ped_rms.txt");
  ofstream high_deadhot_ped_final("high_deadhot_ped_final.txt");
  ofstream low_deadhot_ped_final("low_deadhot_ped_final.txt");

  for(int ibin = 0;ibin < 2000;ibin++){
    if(high_key_map.find(ibin)!=high_key_map.end()){
      hhigh_deadhot_ped->SetAxisRange(ibin,ibin,"x"); 
      TH1D* htemp = hhigh_deadhot_ped->ProjectionY();
      double rms = htemp->GetRMS();
      hhigh_rms_stat->Fill(rms);
      high_ped_rms<<high_key_map.find(ibin)->second<<" "<<ibin<<" "<<rms<<endl;
      if(rms < 0.5) high_deadhot_ped_final<<high_key_map.find(ibin)->second<<" "<<htemp->GetMean()<<endl;
    }
    if(low_key_map.find(ibin)!=low_key_map.end()){
      hlow_deadhot_ped->SetAxisRange(ibin,ibin,"x");
      TH1D* htemp = hlow_deadhot_ped->ProjectionY();
      double rms = htemp->GetRMS();
      hlow_rms_stat->Fill(rms);
      low_ped_rms<<low_key_map.find(ibin)->second<<" "<<ibin<<" "<<rms<<endl;
      if(rms < 0.5) low_deadhot_ped_final<<low_key_map.find(ibin)->second<<" "<<htemp->GetMean()<<endl;
    }
  }


  TFile* ofile = new TFile("deadhot_ped_stat.root","RECREATE");
  hhigh_deadhot_ped->Write();
  hlow_deadhot_ped->Write();
  hhigh_rms_stat->Write();
  hlow_rms_stat->Write();
}

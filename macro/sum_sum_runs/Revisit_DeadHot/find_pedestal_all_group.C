#include<fstream>
#include<set>
#include<map>
void find_pedestal_all_group(){
  ifstream high_bad_list("high_deadhot_stat_no_discrete.txt");
  ifstream low_bad_list("low_deadhot_stat_no_discrete.txt");


  set<int> high_bad_set;
  set<int> low_bad_set;


  int key;
  double ped;
  int freq;
  while(high_bad_list>>key>>freq){
    high_bad_set.insert(key);
  }
  
  while(low_bad_list>>key>>freq){
    low_bad_set.insert(key);
  }


  TH2D* hhigh_ped = new TH2D("hhigh_ped","high Pedestal",8000,-0.5,8000-0.5,300,-40-0.5,260-0.5);
  hhigh_ped->GetXaxis()->SetTitle("The bad");
  hhigh_ped->GetYaxis()->SetTitle("ADC");

  TH2D* hlow_ped = new TH2D("hlow_ped","low Pedestal",8000,-0.5,8000-0.5,300,-40-0.5,260-0.5);
  hlow_ped->GetXaxis()->SetTitle("The bad");
  hlow_ped->GetYaxis()->SetTitle("ADC");


  map<int,int> high_bad_to_key;
  map<int,int> low_bad_to_key;

  for(int i = 0;i<44;i++){
    char path[500];
    TH2D* hhigh_adc_key;
    TH2D* hlow_adc_key;
    sprintf(path,"../%d/sum_sum.root",i);
    TFile* ifile = new TFile(path,"READONLY");
    if(!ifile){
//      cout<<"Open "<<<path<<" failed !!!"<<endl;
      continue;
    }
    hhigh_adc_key = (TH2D*)ifile->Get("hhigh_adc_key");
    hlow_adc_key = (TH2D*)ifile->Get("hlow_adc_key");
   
    int the_bad=0;
    for(set<int>::iterator it = high_bad_set.begin();it!=high_bad_set.end();++it){
      int key = *it;
      hhigh_adc_key->SetAxisRange(key,key,"x");
      TH1D* htemp = (TH1D*)hhigh_adc_key->ProjectionY();
      int max_bin = htemp->GetMaximumBin();
      double max_center = htemp->GetBinCenter(max_bin);
      hhigh_ped->Fill(the_bad,max_center);
      high_bad_to_key.insert(pair<int,int>(the_bad,key));
      the_bad++;
      delete htemp;
    }

    the_bad=0;
    for(set<int>::iterator it = low_bad_set.begin();it!=low_bad_set.end();++it){
      int key = *it;
      hlow_adc_key->SetAxisRange(key,key,"x");
      TH1D* htemp = (TH1D*)hlow_adc_key->ProjectionY();
      int max_bin = htemp->GetMaximumBin();
      double max_center = htemp->GetBinCenter(max_bin);
      hlow_ped->Fill(the_bad,max_center);
      low_bad_to_key.insert(pair<int,int>(the_bad,key));
      the_bad++;
      delete htemp;
    }
    ifile->Close();
  }

  ofstream high_ped_out("high_pedestal_mean_stat_final.txt");
  ofstream low_ped_out("low_pedestal_mean_stat_final.txt");


  for(int i = 0;i < 8000;i++){
    hhigh_ped->SetAxisRange(i,i,"x");
    TH1D* htemp = hhigh_ped->ProjectionY();
    double entries = htemp->GetEntries();
    if(entries < 1) continue;
    double rms = htemp->GetRMS();
    double mean = htemp->GetMean();
    if(fabs(mean) > 3 || rms > 1.5){
      high_ped_out<<high_bad_to_key[i]
//                  <<" "<<mean
//		  <<" "<<rms
//		  <<" "<<
		  endl;
    }
  }

  for(int i = 0;i < 8000;i++){
    hlow_ped->SetAxisRange(i,i,"x");
    TH1D* htemp = hlow_ped->ProjectionY();
    double entries = htemp->GetEntries();
    if(entries < 1) continue;
    double rms = htemp->GetRMS();
    double mean = htemp->GetMean();
    if(fabs(mean) > 3 || rms > 1.5){
      low_ped_out<<low_bad_to_key[i]
//                 <<" "<<mean
//		 <<" "<<rms
//		 <<" "
		 <<endl;
    }
  }



  TFile* ofile = new TFile("deadhot_ped_stat.root","RECREATE"); 

  hhigh_ped->Write();
  hlow_ped->Write();

}

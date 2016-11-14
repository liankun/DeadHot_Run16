#include<fstream>
#include<map>
#include<set>
void draw_ped_adc(){
  ifstream high_ped_txt("high_pedestal_mean_final.txt");
  ifstream low_ped_txt("low_pedestal_mean_final.txt");

  TH2D* hhigh_bad_adc = new TH2D("hhigh_bad_adc","Bad High ADC",2500,-0.5,2499.5,300,-40-0.5,260-0.5);
  hhigh_bad_adc->GetXaxis()->SetTitle("dead hot Number");
  hhigh_bad_adc->GetYaxis()->SetTitle("ADC");
  
  TH2D* hlow_bad_adc = new TH2D("hlow_bad_adc","Bad Low ADC",2500,-0.5,2499.5,300,-40-0.5,260-0.5);
  hlow_bad_adc->GetXaxis()->SetTitle("dead hot Number");
  hlow_bad_adc->GetYaxis()->SetTitle("ADC");

  TH1D* hhigh_bad_ped = new TH1D("hhigh_bad_ped","High Bad Pedestal",2500,-0.5,2499.5);

  TH1D* hlow_bad_ped = new TH1D("hlow_bad_ped","Low Bad Pedestal",2500,-0.5,2499.5);

  map<int,double> high_ped_map;
  map<int,double> low_ped_map;

  int key;
  double ped;
  double rms;
  while(high_ped_txt>>key>>ped>>rms){
//    cout<<key<<" "<<ped<<" "<<rms<<endl;
    high_ped_map.insert(pair<int,double>(key,ped));
  }

  while(low_ped_txt>>key>>ped>>rms){
//    cout<<key<<" "<<ped<<" "<<rms<<endl;
    low_ped_map.insert(pair<int,double>(key,ped));
  }

  TFile* ifile = new TFile("../all_runs.root","READONLY");
  TH2D* hhigh_adc_key = (TH2D*)ifile->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)ifile->Get("hlow_adc_key");

  int the_bad=0;
  for(map<int,double>::iterator it = high_ped_map.begin();it!=high_ped_map.end();++it){
    int key = it->first;
    double ped = it->second;
    hhigh_bad_ped->Fill(the_bad,ped);
    for(int i = 0;i < 300;i++){
      double content = hhigh_adc_key->GetBinContent(key+1,i+1);
      double center = hhigh_adc_key->GetYaxis()->GetBinCenter(i+1);
      hhigh_bad_adc->Fill(the_bad,center,content);
    }
    the_bad++;
  }

  the_bad=0;
  for(map<int,double>::iterator it = low_ped_map.begin();it!=low_ped_map.end();++it){
    int key = it->first;
    double ped = it->second;
    hlow_bad_ped->Fill(the_bad,ped);
    for(int i = 0;i < 300;i++){
      double content = hlow_adc_key->GetBinContent(key+1,i+1);
      double center = hlow_adc_key->GetYaxis()->GetBinCenter(i+1);
      hlow_bad_adc->Fill(the_bad,center,content);
    }
    the_bad++;
  }

  TFile* ofile = new TFile("bad_channel_adc_ped_no_discrete.root","RECREATE");
  TCanvas* c0 = new TCanvas("c_high","high adc",1200,800);
  hhigh_bad_adc->Draw("colz");
  hhigh_bad_ped->SetLineColor(kBlack);
  hhigh_bad_ped->Draw("same");
  c0->Write();

  TCanvas* c1 = new TCanvas("c_low","low adc",1200,800);
  hlow_bad_adc->Draw("colz");
  hlow_bad_ped->SetLineColor(kBlack);
  hlow_bad_ped->Draw("same");
  c1->Write();
}

#include<fstream>
void draw_deadhot_adc(){
  ifstream high_deadhot_txt("high_deadhot_remove_discrete.txt");
  ifstream low_deadhot_txt("low_deadhot_remove_discrete.txt");
  set<int> high_deadhot_list;
  set<int> low_deadhot_list;
  int key;
  while(high_deadhot_txt>>key){
//    cout<<key<<endl; 
    high_deadhot_list.insert(key);
  }
  while(low_deadhot_txt>>key){
//    cout<<key<<endl;
    low_deadhot_list.insert(key);
  }
  
  TFile* ifile = new TFile("../all_runs.root","READONLY");
  if(!ifile){
    cout<<"open all runs file failed !!!"<<endl;
    return;
  }
  TH2D* hhigh_adc_key;
  TH2D* hhigh_rawadc_key;
  TH2D* hlow_adc_key;
  TH2D* hlow_rawadc_key;
  hhigh_adc_key = (TH2D*)ifile->Get("hhigh_adc_key");
  hhigh_rawadc_key = (TH2D*)ifile->Get("hhigh_rawadc_key");
  hlow_adc_key = (TH2D*)ifile->Get("hlow_adc_key");
  hlow_rawadc_key = (TH2D*)ifile->Get("hlow_rawadc_key");
  
  TH2D* hhigh_bad_adc = new TH2D("hhigh_bad_adc","Bad High ADC",2500,-0.5,2499.5,300,-40-0.5,260-0.5);
  hhigh_bad_adc->GetXaxis()->SetTitle("dead hot Number");
  hhigh_bad_adc->GetYaxis()->SetTitle("ADC");
  
  TH1D* hhigh_bad_ped = new TH1D("hhigh_bad_ped","High Bad Pedestal",2500,-0.5,2499.5);
  TH1D* hlow_bad_ped = new TH1D("hlow_bad_ped","Low Bad Pedestal",2500,-0.5,2499.5);

  TH2D* hhigh_bad_rawadc = new TH2D("hhigh_bad_rawadc","Bad High Raw ADC",2500,-0.5,2499.5,300,-40-0.5,260-0.5);
  hhigh_bad_rawadc->GetXaxis()->SetTitle("dead hot Number");
  hhigh_bad_rawadc->GetYaxis()->SetTitle("ADC");

  TH2D* hlow_bad_adc = new TH2D("hlow_bad_adc","Bad Low ADC",2500,-0.5,2499.5,300,-40-0.5,260-0.5);
  hlow_bad_adc->GetXaxis()->SetTitle("dead hot Number");
  hlow_bad_adc->GetYaxis()->SetTitle("ADC");
  
  TH2D* hlow_bad_rawadc = new TH2D("hlow_bad_rawadc","Bad Low Raw ADC",2500,-0.5,2499.5,300,-40-0.5,260-0.5);
  hlow_bad_rawadc->GetXaxis()->SetTitle("dead hot Number");
  hlow_bad_rawadc->GetYaxis()->SetTitle("ADC");

  ofstream high_bad_ped("high_bad_ped.txt");
  ofstream low_bad_ped("low_bad_ped.txt");


  int the_bad=0;  
  for (std::set<int>::iterator it=high_deadhot_list.begin(); it!=high_deadhot_list.end(); ++it){
    int key = (*it);
    hhigh_adc_key->SetAxisRange(key,key,"x");
    TH1D* htemp = hhigh_adc_key->ProjectionY();
    int max_bin = htemp->GetMaximumBin();
    double max_center = htemp->GetBinCenter(max_bin);
    double rms = htemp->GetRMS();
    double entries = htemp->GetEntries();
    if(rms < 5) continue;
    if(entries < 10) continue;
    hhigh_bad_ped->Fill(the_bad,max_center);
    high_bad_ped<<key<<" "<<max_center<<endl;
    for(int i = 0;i < 300;i++){
      double content = hhigh_adc_key->GetBinContent(key+1,i+1);
      double center = hhigh_adc_key->GetYaxis()->GetBinCenter(i+1);
      hhigh_bad_adc->Fill(the_bad,center,content);


      content = hhigh_rawadc_key->GetBinContent(key+1,i+1);
      center =  hhigh_rawadc_key->GetYaxis()->GetBinCenter(i+1);
      hhigh_bad_rawadc->Fill(the_bad,center,content);
    }
    the_bad++;
  }

  the_bad=0;
  for (std::set<int>::iterator it=low_deadhot_list.begin(); it!=low_deadhot_list.end(); ++it){
    int key = (*it);
    hlow_adc_key->SetAxisRange(key,key,"x");
    TH1D* htemp = hlow_adc_key->ProjectionY();
    int max_bin = htemp->GetMaximumBin();
    double max_center = htemp->GetBinCenter(max_bin);
    double rms = htemp->GetRMS();
    double entries = htemp->GetEntries();
    if(rms < 5) continue;
    if(entries < 10) continue;
    hlow_bad_ped->Fill(the_bad,max_center);
    low_bad_ped<<key<<" "<<max_center<<endl;
    for(int i = 0;i < 300;i++){
      double content = hlow_adc_key->GetBinContent(key+1,i+1);
      double center = hlow_adc_key->GetYaxis()->GetBinCenter(i+1);
      hlow_bad_adc->Fill(the_bad,center,content);

      content = hlow_rawadc_key->GetBinContent(key+1,i+1);
      center =  hlow_rawadc_key->GetYaxis()->GetBinCenter(i+1);
      hlow_bad_rawadc->Fill(the_bad,center,content);
    }
    the_bad++;
  }

  TFile* ofile = new TFile("bad_channel_adc_no_discrete.root","RECREATE");
  hhigh_bad_adc->Write();
  hhigh_bad_rawadc->Write();
  hlow_bad_adc->Write();
  hlow_bad_rawadc->Write();
  hhigh_bad_ped->Write();
  hlow_bad_ped->Write();

/*
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
*/
}

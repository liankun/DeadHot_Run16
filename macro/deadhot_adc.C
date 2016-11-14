#include<fstream>
#include<map>

void deadhot_adc(){
  ifstream high_deadhot("high_deadhot_stat.txt");
  ifstream low_deadhot("low_deadhot_stat.txt");
  
  TFile* ifile = new TFile("sum_sum0.root","READONLY");

  TH2D* hhigh_rawadc_key = (TH2D*)ifile->Get("hhigh_rawadc_key");
  TH2D* hlow_rawadc_key = (TH2D*)ifile->Get("hlow_rawadc_key");

  TH2D* hhigh_adc_key = (TH2D*)ifile->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)ifile->Get("hlow_adc_key");

  const int Nbins=20000;

  TH2D* hhigh_deadhot_rawadc = new TH2D("hhigh_deadhot_rawadc","High Raw dead hot ADC",Nbins,-0.5,Nbins-0.5,300,-40-0.5,260-0.5); 
  hhigh_deadhot_rawadc->GetYaxis()->SetTitle("Raw ADC");

  TH2D* hlow_deadhot_rawadc = new TH2D("hlow_deadhot_rawadc","Low Raw dead hot ADC",Nbins,-0.5,Nbins-0.5,300,-40-0.5,260-0.5); 
  hlow_deadhot_rawadc->GetYaxis()->SetTitle("Raw ADC");

  TH2D* hhigh_deadhot_adc = new TH2D("hhigh_deadhot_adc","High dead hot ADC",Nbins,-0.5,Nbins-0.5,300,-40-0.5,260-0.5); 
  hhigh_deadhot_adc->GetYaxis()->SetTitle("ADC");

  TH2D* hlow_deadhot_adc = new TH2D("hlow_deadhot_adc","Low dead hot ADC",Nbins,-0.5,Nbins-0.5,300,-40-0.5,260-0.5); 
  hlow_deadhot_adc->GetYaxis()->SetTitle("ADC");



  std::multimap<int,int> map_high;
  std::multimap<int,int> map_low;
  int key;
  int frq;

  while(high_deadhot>>key>>frq){
//cout<<key<<" "<<frq<<endl;
    map_high.insert(pair<int,int>(frq,key));
  }

  while(low_deadhot>>key>>frq){
//cout<<key<<" "<<frq<<endl;
    map_low.insert(pair<int,int>(frq,key));
  }

  int count=0;
  for(multimap<int,int>::iterator it=map_high.begin();it!=map_high.end();it++){
//      cout<<it->first<<" "<<it->second<<endl;     
    int key = it->second;
    if(it->first < 90) continue;
    for(int ibin = 0;ibin < 300;ibin++){
      double content = hhigh_rawadc_key->GetBinContent(key+1,ibin+1);
      hhigh_deadhot_rawadc->SetBinContent(count+1,ibin+1,content);
      content = hhigh_adc_key->GetBinContent(key+1,ibin+1);
      hhigh_deadhot_adc->SetBinContent(count+1,ibin+1,content);
    }
    count++;
  }
  cout<<"Number of bad channels for high: "<<count<<endl;
  
  count=0;
  for(multimap<int,int>::iterator it=map_low.begin();it!=map_low.end();it++){
//      cout<<it->first<<" "<<it->second<<endl;     
    int key = it->second;
    if(it->first < 90) continue;
    for(int ibin = 0;ibin < 300;ibin++){
      double content = hlow_rawadc_key->GetBinContent(key+1,ibin+1);
      hlow_deadhot_rawadc->SetBinContent(count+1,ibin+1,content);
      content = hlow_adc_key->GetBinContent(key+1,ibin+1);
      hlow_deadhot_adc->SetBinContent(count+1,ibin+1,content);
    }
    count++;
  }
  cout<<"Number of bad channels for low: "<<count<<endl;


  TFile* ofile = new TFile("deadhot_adc.root","RECREATE");
  hhigh_deadhot_rawadc->Write();
  hhigh_deadhot_adc->Write();
  hlow_deadhot_rawadc->Write();
  hlow_deadhot_adc->Write();
}

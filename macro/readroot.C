#include <set>
void readroot(){
  gSystem->Load("libMyMpcEx.so");
  TFile* file = new TFile("sum_sum0.root","READONLY");
  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");

  TH1D* hhigh_adc_layer[2][8];
  TH1D* hlow_adc_layer[2][8];
  TH1D* hhigh_adc_sensor[2][8][24];
  TH1D* hlow_adc_sensor[2][8][24];
  TH1D* hhigh_peak_pos[2];
  TH1D* hlow_peak_pos[2];
  TH1D* hhigh_peak_pos_key[2];
  TH1D* hlow_peak_pos_key[2];
  
  TH1D* hhigh_mean[2];
  TH1D* hlow_mean[2];

  TH1D* hhigh_rms[2];
  TH1D* hlow_rms[2];

  TH1D* hhigh_mean_key[2];
  TH1D* hlow_mean_key[2];

  TH1D* hhigh_rms_key[2];
  TH1D* hlow_rms_key[2];

  TH2D* hhigh_mean_vs_rms[2];
  TH2D* hlow_mean_vs_rms[2];
 
  hhigh_mean_vs_rms[0] = new TH2D("hhigh_mean_vs_rms0","High ADC Mean vs RMS Arm 0",300,-40-0.5,260-0.5,300,-40-0.5,260-0.5);
  hhigh_mean_vs_rms[0]->GetXaxis()->SetTitle("RMS");
  hhigh_mean_vs_rms[0]->GetYaxis()->SetTitle("Mean");

  hhigh_mean_vs_rms[1] = new TH2D("hhigh_mean_vs_rms1","High ADC Mean vs RMS Arm 1",300,-40-0.5,260-0.5,300,-40-0.5,260-0.5);
  hhigh_mean_vs_rms[1]->GetXaxis()->SetTitle("RMS");
  hhigh_mean_vs_rms[1]->GetYaxis()->SetTitle("Mean");

  hlow_mean_vs_rms[0] = new TH2D("hlow_mean_vs_rms0","Low ADC Mean vs RMS Arm 0",300,-40-0.5,260-0.5,300,-40-0.5,260-0.5);
  hlow_mean_vs_rms[0]->GetXaxis()->SetTitle("RMS");
  hlow_mean_vs_rms[0]->GetYaxis()->SetTitle("Mean");

  hlow_mean_vs_rms[1] = new TH2D("hlow_mean_vs_rms1","Low ADC Mean vs RMS Arm 1",300,-40-0.5,260-0.5,300,-40-0.5,260-0.5);
  hlow_mean_vs_rms[1]->GetXaxis()->SetTitle("RMS");
  hlow_mean_vs_rms[1]->GetYaxis()->SetTitle("Mean");



  hhigh_peak_pos[0] = new TH1D("hhigh_peak_pos0","Biggest Peak Arm 0",300,-40-0.5,260-0.5);
  hhigh_peak_pos[1] = new TH1D("hhigh_peak_pos1","Biggest Peak Arm 1",300,-40-0.5,260-0.5);

  hlow_peak_pos[0] = new TH1D("hlow_peak_pos0","Biggest Peak Arm 0",300,-40-0.5,260-0.5);
  hlow_peak_pos[1] = new TH1D("hlow_peak_pos1","Biggest Peak Arm 1",300,-40-0.5,260-0.5);

  hhigh_mean[0] = new TH1D("hhigh_mean0","Mean Arm 0",300,-40-0.5,260-0.5);
  hhigh_mean[1] = new TH1D("hhigh_mean1","Mean Arm 1",300,-40-0.5,260-0.5);

  hlow_mean[0] = new TH1D("hlow_mean0","Mean Arm 0",300,-40-0.5,260-0.5);
  hlow_mean[1] = new TH1D("hlow_mean1","Mean Arm 1",300,-40-0.5,260-0.5);

  hhigh_rms[0] = new TH1D("hhigh_rms0","RMS Arm 0",300,-40-0.5,260-0.5);
  hhigh_rms[1] = new TH1D("hhigh_rms1","RMS Arm 1",300,-40-0.5,260-0.5);

  hlow_rms[0] = new TH1D("hlow_rms0","RMS Arm 0",300,-40-0.5,260-0.5);
  hlow_rms[1] = new TH1D("hlow_rms1","RMS Arm 1",300,-40-0.5,260-0.5);



  hhigh_peak_pos_key[0] = new TH1D("hhigh_peak_pos_key0","Biggest Peak Arm 0",24576,-0.5,24576-0.5);
  hhigh_peak_pos_key[1] = new TH1D("hhigh_peak_pos_key1","Biggest Peak Arm 1",24576,24576-0.5,49152-0.5);

  hlow_peak_pos_key[0] = new TH1D("hlow_peak_pos_key0","Biggest Peak Arm 0",24576,-0.5,24576-0.5);
  hlow_peak_pos_key[1] = new TH1D("hlow_peak_pos_key1","Biggest Peak Arm 1",24576,24576-0.5,49152-0.5);

  hhigh_mean_key[0] = new TH1D("hhigh_mean_key0","Mean Arm 0",24576,-0.5,24576-0.5);
  hhigh_mean_key[1] = new TH1D("hhigh_mean_key1","Mean Arm 1",24576,24576-0.5,49152-0.5);

  hlow_mean_key[0] = new TH1D("hlow_mean_key0","Mean Arm 0",24576,-0.5,24576-0.5);
  hlow_mean_key[1] = new TH1D("hlow_mean_key1","Mean Arm 1",24576,24576-0.5,49152-0.5);

  hhigh_rms_key[0] = new TH1D("hhigh_rms_key0","RMS Arm 0",24576,-0.5,24576-0.5);
  hhigh_rms_key[1] = new TH1D("hhigh_rms_key1","RMS Arm 1",24576,24576-0.5,49152-0.5);

  hlow_rms_key[0] = new TH1D("hlow_rms_key0","RMS Arm 0",24576,-0.5,24576-0.5);
  hlow_rms_key[1] = new TH1D("hlow_rms_key1","RMS Arm 1",24576,24576-0.5,49152-0.5);

  for(int iarm = 0;iarm < 2;iarm++){
    for(int ilayer = 0;ilayer < 8;ilayer++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_layer%d",iarm,ilayer);
      hhigh_adc_layer[iarm][ilayer] = new TH1D(hname,hname,251,-30-0.5,221-0.5);
      hhigh_adc_layer[iarm][ilayer]->GetXaxis()->SetTitle("ADC");

      sprintf(hname,"hlow_adc_arm%d_layer%d",iarm,ilayer);
      hlow_adc_layer[iarm][ilayer] = new TH1D(hname,hname,251,-30-0.5,221-0.5);
      hlow_adc_layer[iarm][ilayer]->GetXaxis()->SetTitle("ADC");
    }
  }

  
  MpcExMapper* mapper = MpcExMapper::instance();
  //one layer : 3072 minipad
//  ofstream high_bad_rms("high_bad_rms.txt");
//  ofstream low_bad_rms("low_bad_rms.txt");
//  ofstream high_bad_mean("high_bad_mean.txt");
//  ofstream low_bad_mean("low_bad_mean.txt");
  
  ifstream high_bad_rms("high_bad_rms.txt");
  ifstream low_bad_rms("low_bad_rms.txt");
  ifstream high_bad_mean("high_bad_mean.txt");
  ifstream low_bad_mean("low_bad_mean.txt");


  std::set<int> bad_rms_list_h;
  std::set<int> bad_rms_list_l;
  std::set<int> bad_mean_list_h;
  std::set<int> bad_mean_list_l;

  int key;
  double rms;
  double mean;
  
  while(high_bad_rms>>key>>rms){
//    cout<<key<<" "<<rms<<endl;
    bad_rms_list_h.insert(key);
  }
  while(low_bad_rms>>key>>rms){
//    cout<<key<<" "<<rms<<endl;
    bad_rms_list_l.insert(key);
  }

  while(high_bad_mean>>key>>mean){
//    cout<<key<<" "<<mean<<endl;
    bad_mean_list_h.insert(key);
  }

  while(low_bad_mean>>key>>mean){
//    cout<<key<<" "<<mean<<endl;
    bad_mean_list_l.insert(key);
  }

  for(int i = 0;i < 49152;i++){
    hhigh_adc_key->SetAxisRange(i,i,"X");
    hlow_adc_key->SetAxisRange(i,i,"X");
    hhigh_adc_key->SetAxisRange(-30,220,"Y");
    hlow_adc_key->SetAxisRange(-30,220,"Y");

    TH1D* htemp0 = hhigh_adc_key->ProjectionY();
    TH1D* htemp1 = hlow_adc_key->ProjectionY();
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    if(htemp0->GetEntries() < 10) continue;
    int max_bin0 = htemp0->GetMaximumBin();
    double max_center0 = htemp0->GetBinCenter(max_bin0);
    int max_bin1 = htemp1->GetMaximumBin();
    double max_center1 = htemp1->GetBinCenter(max_bin1);
    
  
    double mean0 = htemp0->GetMean();
    double mean1 = htemp1->GetMean();


    double rms0 = htemp0->GetRMS();
    double rms1 = htemp1->GetRMS();

    if(bad_rms_list_h.find(i) == bad_rms_list_h.end()){
      if(bad_mean_list_h.find(i) == bad_mean_list_h.end()){
        hhigh_peak_pos[arm]->Fill(max_center0);
        hhigh_peak_pos_key[arm]->Fill(i,max_center0);
        hhigh_mean[arm]->Fill(mean0);
        hhigh_mean_key[arm]->Fill(i,mean0);
        hhigh_rms[arm]->Fill(rms0);
        hhigh_rms_key[arm]->Fill(i,rms0);
        hhigh_adc_layer[arm][layer]->Add(htemp0);
        hhigh_mean_vs_rms[arm]->Fill(rms0,mean0);
//      if(arm == 0 && (mean0 <=-9 || mean0 >=46 )) high_bad_mean<<i<<" "<<mean0<<endl;
//      if(arm == 1 && (mean0 <=-9 || mean0 >=38 )) high_bad_mean<<i<<" "<<mean0<<endl;

      }
    }

    if(bad_rms_list_l.find(i) == bad_rms_list_l.end()){
      if(bad_mean_list_l.find(i) == bad_mean_list_l.end()){
        hlow_peak_pos[arm]->Fill(max_center1);
        hlow_peak_pos_key[arm]->Fill(i,max_center1);
        hlow_mean[arm]->Fill(mean1);
        hlow_mean_key[arm]->Fill(i,mean1);
        hlow_rms[arm]->Fill(rms1);
        hlow_rms_key[arm]->Fill(i,rms1);
        hlow_adc_layer[arm][layer]->Add(htemp1);
        hlow_mean_vs_rms[arm]->Fill(rms1,mean1);
//      if(arm == 0 && (mean1 <=-5 || mean1 >=15 )) low_bad_mean<<i<<" "<<mean1<<endl;
//      if(arm == 1 && (mean1 <=-7 || mean1 >=12 )) low_bad_mean<<i<<" "<<mean1<<endl;
      }
    }

    
//    if(arm == 0 && (rms0 <=4 || rms0 >=46 )) high_bad_rms<<i<<" "<<rms0<<endl;
//    if(arm == 1 && (rms0 <=2 || rms0 >=46 )) high_bad_rms<<i<<" "<<rms0<<endl;
//    if(arm == 0 && (rms1 <=2 || rms1 >=20 )) low_bad_rms<<i<<" "<<rms1<<endl;
//    if(arm == 1 && (rms1 <=1 || rms1 >=17 )) low_bad_rms<<i<<" "<<rms1<<endl;
  }

  TFile* ofile = new TFile("layer_adc.root","RECREATE");
   for(int iarm = 0;iarm < 2;iarm++){
    hhigh_mean_vs_rms[iarm]->Write();
    hlow_mean_vs_rms[iarm]->Write();
    hhigh_peak_pos[iarm]->Write();
    hlow_peak_pos[iarm]->Write();
    hhigh_peak_pos_key[iarm]->Write();
    hlow_peak_pos_key[iarm]->Write();
    hhigh_mean[iarm]->Write();
    hlow_mean[iarm]->Write();
    hhigh_mean_key[iarm]->Write();
    hlow_mean_key[iarm]->Write();
    hhigh_rms[iarm]->Write();
    hlow_rms[iarm]->Write();
    hhigh_rms_key[iarm]->Write();
    hlow_rms_key[iarm]->Write();

    for(int ilayer = 0;ilayer < 8;ilayer++){
      hhigh_adc_layer[iarm][ilayer]->Write();
      hlow_adc_layer[iarm][ilayer]->Write();
    }
  }
}

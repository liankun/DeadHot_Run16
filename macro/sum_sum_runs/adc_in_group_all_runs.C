#include<set>
#include<fstream>
#include<map>

void adc_in_group_all_runs(int group=0){
  gSystem->Load("libMyMpcEx.so");
  char path[500];
  TFile* file = new TFile("all_runs.root","READONLY");
  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");

  MpcExMapper* mapper = MpcExMapper::instance();
  ifstream bad_high_itg_total("Revisit_DeadHot/high_pedestal_mean_stat_final.txt");
  ifstream bad_low_itg_total("Revisit_DeadHot/low_pedestal_mean_stat_final.txt");
  
  std::set<int> bad_high_itg_list;
  std::set<int> bad_low_itg_list;




  double high_itg_begin_type0[2][6]={{0,15,45,80,120,200},{0,15,30,50,80,150}};
  double high_itg_end_type0[2][5]={{15,45,80,120,200},{15,30,50,80,150}};
  double high_itg_begin_type1[2][6]={{0,10,40,75,115,195},{0,10,25,45,75,145}};
  double high_itg_end_type1[2][5]={{10,40,75,115,195},{10,25,45,75,145}};
  double low_itg_begin[6] = {0,5,15,25,40,100};
  double low_itg_end[5] = {5,15,25,40,100};
  
  double high_itg_region_type0[2][8]={{-40.5,0,15,45,80,120,200,259.5},
                                      {-40.5,0,15,30,50,80,150,259.5}};

  double high_itg_region_type1[2][8]={{-40.5,0,10,40,75,115,195,259.5},
                                      {-40.5,0,10,25,45,75,145,259.5}};

  
  double low_itg_region[8]={-40.5,0,5,15,25,40,100,259.5};


  int key;
  int new_key;
  double mean;
  double rms;
  while(bad_high_itg_total>>key>>mean>>rms){
    bad_high_itg_list.insert(key);
  }

  while(bad_low_itg_total>>key>>mean>>rms){
    bad_low_itg_list.insert(key);
  }
  
  TProfile* phigh_adc_row[1536];
  TProfile* plow_adc_row[1536];
  TProfile* phigh_adc_r[144];
  TProfile* plow_adc_r[144];

  TProfile* phigh_itg_row[1536];
  TProfile* plow_itg_row[1536];
  TProfile* phigh_itg_r[144];
  TProfile* plow_itg_r[144];

  for(int i = 0;i<1536;i++){
    char pname[500];
    int arm = i/768;
    int layer = i/96;
    if(layer>=8) layer = layer - 8;
    sprintf(pname,"phigh_itg_row%d",i);
   
    if(layer>1){
      phigh_itg_row[i] = new TProfile(pname,pname,7,high_itg_region_type1[arm],"s");
    }
    else{
      phigh_itg_row[i] = new TProfile(pname,pname,7,high_itg_region_type0[arm],"s");
    }
    phigh_itg_row[i]->GetXaxis()->SetTitle("region");
    sprintf(pname,"plow_itg_row%d",i);
    plow_itg_row[i] = new TProfile(pname,pname,7,low_itg_region,"s");
    plow_itg_row[i]->GetXaxis()->SetTitle("region");
    
    sprintf(pname,"phigh_adc_row%d",i);
    phigh_adc_row[i] = new TProfile(pname,pname,300,-40-0.5,260-0.5);
    phigh_adc_row[i]->GetXaxis()->SetTitle("ADC");
    sprintf(pname,"plow_adc_row%d",i);
    plow_adc_row[i] = new TProfile(pname,pname,300,-40-0.5,260-0.5);
    plow_adc_row[i]->GetXaxis()->SetTitle("ADC");
  }

  for(int i=0;i<144;i++){
    int arm = i/72;
    int layer = i/9;
    if(layer >= 8) layer = layer - 8;
    char pname[500];
    sprintf(pname,"phigh_itg_r%d",i);
    if(layer>1){
      phigh_itg_r[i] = new TProfile(pname,pname,7,high_itg_region_type1[arm],"s");
    }
    else{
      phigh_itg_r[i] = new TProfile(pname,pname,7,high_itg_region_type0[arm],"s");
    }
    phigh_itg_r[i]->GetXaxis()->SetTitle("region");
    sprintf(pname,"plow_itg_r%d",i);
    plow_itg_r[i] = new TProfile(pname,pname,7,low_itg_region,"s");
    plow_itg_r[i]->GetXaxis()->SetTitle("region");
    sprintf(pname,"phigh_adc_r%d",i);
    phigh_adc_r[i] = new TProfile(pname,pname,300,-40-0.5,260-0.5);
    phigh_adc_r[i]->GetXaxis()->SetTitle("ADC");
    sprintf(pname,"plow_adc_r%d",i);
    plow_adc_r[i] = new TProfile(pname,pname,300,-40-0.5,260-0.5);
    plow_adc_r[i]->GetXaxis()->SetTitle("ADC");
  }


  const int ndiv = 9;
  double rbins[ndiv+1] ={6.5,9,10.5,12.1,13.5,14.4,15.6,16.8,18.1,21.5};

  for(int i=0;i<24576*2;i++){
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    int index = 6*quadrant+sensor;
    int ly = mapper->get_ly(i);
    int row_num=192*4*arm+24*4*layer+index*4+ly;
    double pos_x = mapper->get_x(i);
    double pos_y = mapper->get_y(i);
    double r = sqrt(pos_x*pos_x+pos_y*pos_y);
    int n = -1;
    
    for(int ibin=0;ibin<ndiv;ibin++){
      if(r >=rbins[ibin] && r <rbins[ibin+1]){
        n = ibin;
	break;
      }
    }

    if(n < 0){
      cout<<"bad r "<<r<<endl;
      return;
    }

    int r_index=9*8*arm+9*layer+n;

    hhigh_adc_key->SetAxisRange(i,i,"X");
    hlow_adc_key->SetAxisRange(i,i,"X");
    TH1D* htemp0 = hhigh_adc_key->ProjectionY();
    TH1D* htemp1 = hlow_adc_key->ProjectionY();

    if(bad_high_itg_list.find(i) == bad_high_itg_list.end()){
      for(int j = 0;j < 300;j++){
        double content = hhigh_adc_key->GetBinContent(i+1,j+1);
	double center = hhigh_adc_key->GetYaxis()->GetBinCenter(j+1);
        phigh_adc_row[row_num]->Fill(center,content,1);
	phigh_adc_r[r_index]->Fill(center,content,1);
      }
      
      for(int iitg = 1;iitg<5;iitg++){
        double high_begin = high_itg_begin_type0[arm][iitg];
	double high_end = high_itg_end_type0[arm][iitg];
        if(layer > 1){
          high_begin = high_itg_begin_type1[arm][iitg];
	  high_end = high_itg_end_type1[arm][iitg];
	}
	int high_begin_bin = htemp0->FindBin(high_begin);
	int high_end_bin = htemp0->FindBin(high_end);
	double itegral0 = htemp0->Integral(high_begin_bin,high_end_bin);
	double mean=(high_begin+high_end)/2.;
	phigh_itg_row[row_num]->Fill(mean,itegral0,1);
	phigh_itg_r[r_index]->Fill(mean,itegral0,1);
      }
    }
    
    if(bad_low_itg_list.find(i) == bad_low_itg_list.end()){
      for(int j = 0;j < 300;j++){
        double content = hlow_adc_key->GetBinContent(i+1,j+1);
	double center = hlow_adc_key->GetYaxis()->GetBinCenter(j+1);
        plow_adc_row[row_num]->Fill(center,content);
	plow_adc_r[r_index]->Fill(center,content);
      }
      
      for(int iitg = 1;iitg<5;iitg++){
        double low_begin = low_itg_begin[iitg];
	double low_end = low_itg_end[iitg];
	double mean = (low_begin+low_end)/2.;
	int low_begin_bin = htemp1->FindBin(low_begin);
	int low_end_bin = htemp1->FindBin(low_end);
	double itegral1 = htemp1->Integral(low_begin_bin,low_end_bin);
	plow_itg_row[row_num]->Fill(mean,itegral1,1);
	plow_itg_r[r_index]->Fill(mean,itegral1,1);
      }
      delete htemp0;
      delete htemp1;
    }
  }


  TFile* ofile = new TFile("Revisit_DeadHot/deadhot_adc_shift_ped.root","RECREATE");

  for(set<int>::iterator it = bad_high_itg_list.begin();it!=bad_high_itg_list.end();++it){
    int key = *it;
    int arm = mapper->get_arm(key);
    int layer = mapper->get_layer(key);
    int quadrant = mapper->get_quadrant(key);
    int sensor = mapper->get_sensor_in_quadrant(key);
    int index = 6*quadrant+sensor;
    int ly = mapper->get_ly(key);
    int row_num=192*4*arm+24*4*layer+index*4+ly;
    double pos_x = mapper->get_x(key);
    double pos_y = mapper->get_y(key);
    double r = sqrt(pos_x*pos_x+pos_y*pos_y);
    int n = -1;
  



    for(int ibin=0;ibin<ndiv;ibin++){
      if(r >=rbins[ibin] && r <rbins[ibin+1]){
        n = ibin;
	break;
      }
    }

    if(n < 0){
      cout<<"bad r "<<r<<endl;
      return;
    }

    int r_index=9*8*arm+9*layer+n;
    hhigh_adc_key->SetAxisRange(key,key,"x");
    TH1D* htemp0 = hhigh_adc_key->ProjectionY();
    double entries= htemp0->GetEntries();
    if(entries<1){
      delete htemp0;
      continue;
    }

    TProfile* ptemp;
    if(layer>1){
      ptemp= new TProfile("ptemp","ptemp",7,high_itg_region_type1[arm]);
    }
    else{
      ptemp= new TProfile("ptemp","ptemp",7,high_itg_region_type0[arm]);
    }
    ptemp->SetLineColor(kRed);
    for(int iitg = 1;iitg<5;iitg++){
      double high_begin = high_itg_begin_type0[arm][iitg];
      double high_end = high_itg_end_type0[arm][iitg];
      if(layer > 1){
        high_begin = high_itg_begin_type1[arm][iitg];
	high_end = high_itg_end_type1[arm][iitg];
      }
      int high_begin_bin = htemp0->FindBin(high_begin);
      int high_end_bin = htemp0->FindBin(high_end);
      double itegral0 = htemp0->Integral(high_begin_bin,high_end_bin);
      double mean = (high_begin+high_end)/2.;
      ptemp->Fill(mean,itegral0,1);
    }

    

    char hname[500];
    sprintf(hname,"c_high_key%d",key);
    TCanvas* c = new TCanvas(hname,hname,800,1200);
    c->Divide(2,2);
    c->cd(1);
    gPad->SetLogy();
    htemp0->SetLineColor(kRed);
    phigh_adc_row[row_num]->Draw("");
    htemp0->Draw("same");

    c->cd(2);
    gPad->SetLogy();
    phigh_adc_r[r_index]->Draw("");
    htemp0->Draw("same");

    c->cd(3);
    gPad->SetLogy();
    phigh_itg_row[row_num]->Draw("");
    ptemp->Draw("same");
    
    c->cd(4);
    gPad->SetLogy();
    phigh_itg_r[r_index]->Draw("");
    ptemp->Draw("same");

    c->Write();
    delete ptemp;
    delete htemp0;
  }

  for(set<int>::iterator it = bad_low_itg_list.begin();it!=bad_low_itg_list.end();++it){
    int key = *it;
    int arm = mapper->get_arm(key);
    int layer = mapper->get_layer(key);
    int quadrant = mapper->get_quadrant(key);
    int sensor = mapper->get_sensor_in_quadrant(key);
    int index = 6*quadrant+sensor;
    int ly = mapper->get_ly(key);
    int row_num=192*4*arm+24*4*layer+index*4+ly;
    double pos_x = mapper->get_x(key);
    double pos_y = mapper->get_y(key);
    double r = sqrt(pos_x*pos_x+pos_y*pos_y);
    int n = -1;
    
    for(int ibin=0;ibin<ndiv;ibin++){
      if(r >=rbins[ibin] && r <rbins[ibin+1]){
        n = ibin;
	break;
      }
    }

    if(n < 0){
      cout<<"bad r "<<r<<endl;
      return;
    }

    int r_index=9*8*arm+9*layer+n;
    hlow_adc_key->SetAxisRange(key,key,"x");
    TH1D* htemp0 = hlow_adc_key->ProjectionY();
    double entries= htemp0->GetEntries();
    if(entries<1){
      delete htemp0;
      continue;
    }


    TProfile* ptemp = new TProfile("ptemp","ptemp",7,low_itg_region);
    ptemp->SetLineColor(kRed);
    for(int iitg = 1;iitg<5;iitg++){
      double low_begin = low_itg_begin[iitg];
      double low_end = low_itg_end[iitg];
      int low_begin_bin = htemp0->FindBin(low_begin);
      int low_end_bin = htemp0->FindBin(low_end);
      double itegral1 = htemp0->Integral(low_begin_bin,low_end_bin);
      double mean = (low_begin+low_end)/2;
      ptemp->Fill(mean,itegral1);
    }


    char hname[500];
    sprintf(hname,"c_low_key%d",key);
    TCanvas* c = new TCanvas(hname,hname,800,1200);
    c->Divide(2,2);
    c->cd(1);
    gPad->SetLogy();
    htemp0->SetLineColor(kRed);
    plow_adc_row[row_num]->Draw("");
    htemp0->Draw("same");

    c->cd(2);
    gPad->SetLogy();
    plow_adc_r[r_index]->Draw("");
    htemp0->Draw("same");
    
    
    c->cd(3);
    gPad->SetLogy();
    plow_itg_row[row_num]->Draw("");
    ptemp->Draw("same");
    
    c->cd(4);
    gPad->SetLogy();
    plow_itg_r[r_index]->Draw("");
    ptemp->Draw("same");

    c->Write();
    delete ptemp; 
    delete htemp0;
  }
}

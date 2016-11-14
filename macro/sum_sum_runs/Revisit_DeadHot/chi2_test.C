#include<set>
#include<fstream>
#include<map>
#include<vector>

void chi2_test(int step=20){
  gSystem->Load("libMyMpcEx.so");
  char path[500];
  TFile* file = new TFile("../all_runs.root","READONLY");
  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");

  MpcExMapper* mapper = MpcExMapper::instance();
  ifstream bad_high_itg_total("high_real_deadhot_add_discrete.txt");
  ifstream bad_low_itg_total("low_real_deadhot_add_discrete.txt");

  ifstream bad_high_ped("high_pedestal_mean_final.txt");
  ifstream bad_low_ped("low_pedestal_mean_final.txt");

//  ifstream high_deadhot_output("high_deadhot_freq_no_discrete_0_44.txt");
//  ifstream low_deadhot_output("low_deadhot_freq_no_discrete_0_44.txt");

  ifstream high_deadhot_output("high_real_deadhot_no_discrete.txt");
  ifstream low_deadhot_output("low_real_deadhot_no_discrete.txt");

  std::set<int> bad_high_itg_list;
  std::set<int> bad_low_itg_list;
  std::set<int> bad_high_output_set;
  std::set<int> bad_low_output_set;

  std::map<int,int> bad_high_ped_map;
  std::map<int,int> bad_low_ped_map;

  TH2D* hchi2_high = new TH2D("hchi2_high","hchi2_high",100,0,5,200,0,10);
  hchi2_high->GetXaxis()->SetTitle("Mean");
  hchi2_high->GetYaxis()->SetTitle("RMS");
  TH2D* hchi2_low = new TH2D("hchi2_low","hchi2_low",100,0,5,200,0,10);
  hchi2_low->GetXaxis()->SetTitle("Mean");
  hchi2_low->GetYaxis()->SetTitle("RMS");

  int key;
  int new_key;
  double mean;
  double rms;
  while(bad_high_itg_total>>key){
    bad_high_itg_list.insert(key);
  }

  while(bad_low_itg_total>>key){
    bad_low_itg_list.insert(key);
  }
 
  while(high_deadhot_output>>key){
    bad_high_output_set.insert(key);
  }

  while(low_deadhot_output>>key){
    bad_low_output_set.insert(key);
  }

  while(bad_high_ped>>key>>mean>>rms){
    if(rms<1)bad_high_ped_map.insert(pair<int,int>(key,mean));
  }

  while(bad_low_ped>>key>>mean>>rms){
    if(rms<1)bad_low_ped_map.insert(pair<int,int>(key,mean));
  }


  TProfile* phigh_adc_row[1536];
  TProfile* plow_adc_row[1536];
  TProfile* phigh_adc_r[144];
  TProfile* plow_adc_r[144];


  for(int i = 0;i<1536;i++){
    char pname[500];
    int arm = i/768;
    int layer = i/96;
    if(layer>=8) layer = layer - 8;
    
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
    }
    
    if(bad_low_itg_list.find(i) == bad_low_itg_list.end()){
      for(int j = 0;j < 300;j++){
        double content = hlow_adc_key->GetBinContent(i+1,j+1);
	double center = hlow_adc_key->GetYaxis()->GetBinCenter(j+1);
        plow_adc_row[row_num]->Fill(center,content);
	plow_adc_r[r_index]->Fill(center,content);
      }
      
      delete htemp0;
      delete htemp1;
    }
  }
 
  ofstream out_high_txt("high_chi2_0_0_5.txt");
  ofstream out_low_txt("low_chi2_0_0_2.txt");

  for(set<int>::iterator it = bad_high_output_set.begin();it!=bad_high_output_set.end();++it){
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
    double ped=0;
//    if(bad_high_ped_map.find(key)!=bad_high_ped_map.end()){
//      cout<<"find the high ped "<<bad_high_ped_map[key]<<endl;
//      ped = bad_high_ped_map[key];
//    }
  

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
    char hname[300];
    double entries= htemp0->GetEntries();
    if(entries<1){
      delete htemp0;
      continue;
    }
    
    int bin0 = htemp0->FindBin(15+ped);
    int bin1 = htemp0->FindBin(200+ped);

    if(layer <= 1){
        bin0 = htemp0->FindBin(10+ped);
	bin1 = htemp0->FindBin(200+ped);
    }
    int total_bin=0;
    double mean_ratio=0;
    double mean_ratio2=0;

    for(int i = bin0;i<=bin1;i++){
      double content0=htemp0->GetBinContent(i);
      double bin_center=htemp0->GetBinCenter(i);
      int bin_r = phigh_adc_r[r_index]->FindBin(bin_center);
      double content1=phigh_adc_r[r_index]->GetBinContent(bin_r);
      if(content1 < 10)continue;
      mean_ratio += content0/content1;
      mean_ratio2 += content0*content0/(content1*content1);
      total_bin++;
    }


    mean_ratio = mean_ratio/total_bin;
    mean_ratio2 = mean_ratio2/total_bin;
    
//cout<<" "<<total_bin
//    <<" "<<mean_ratio
//    <<" "<<mean_ratio2
//    <<" "<<sqrt(mean_ratio2-mean_ratio*mean_ratio)
//    <<endl;
 

    hchi2_high->Fill(mean_ratio,sqrt(mean_ratio2-mean_ratio*mean_ratio));
    if(sqrt(mean_ratio2-mean_ratio*mean_ratio) < 0.2 && mean_ratio<=(step+1)*0.1 && mean_ratio>(step+0)*0.1){
      out_high_txt<<key<<endl;
    }
//    else{
//      hchi2_high->Fill(mean_ratio,sqrt(mean_ratio2-mean_ratio*mean_ratio));
//    }
    delete htemp0;
  }


  for(set<int>::iterator it = bad_low_output_set.begin();it!=bad_low_output_set.end();++it){
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
    double ped = 0; 
//    if(bad_low_ped_map.find(key)!=bad_low_ped_map.end()){
//      cout<<"find the low ped "<<bad_low_ped_map[key]<<endl;
//      ped = bad_low_ped_map[key];
//    }
   
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
//    hlow_adc_key->SetAxisRange(5,100,"x");
    TH1D* htemp0 = hlow_adc_key->ProjectionY();
//    plow_adc_r[r_index]->SetAxisRange(5,100,"x");
    double entries= htemp0->GetEntries();
    if(entries<1){
      delete htemp0;
      continue;
    }
    
    int bin0 = htemp0->FindBin(6+ped);
    int bin1 = htemp0->FindBin(100+ped);
    int total_bin=0;
    double mean_ratio=0;
    double mean_ratio2=0;
    for(int i = bin0;i<=bin1;i++){
      double content0=htemp0->GetBinContent(i);
      double bin_center = htemp0->GetBinCenter(i);
      int bin_r = plow_adc_r[r_index]->FindBin(bin_center);
      double content1=plow_adc_r[r_index]->GetBinContent(bin_r);
      if(content1 < 10)continue;
//      cout<<content0<<" "<<content1<<endl;
      mean_ratio += content0/content1;
      mean_ratio2 += content0*content0/(content1*content1);
      total_bin++;
    }

    mean_ratio = mean_ratio/total_bin;
    mean_ratio2 = mean_ratio2/total_bin;

//cout<<total_bin
//    <<" "<<mean_ratio
//    <<" "<<mean_ratio2
//    <<" "<<sqrt(mean_ratio2-mean_ratio*mean_ratio)
//    <<endl;
    
    hchi2_low->Fill(mean_ratio,sqrt(mean_ratio2-mean_ratio*mean_ratio));
    if(sqrt(mean_ratio2-mean_ratio*mean_ratio) < 0.2 && mean_ratio<=(step+1)*0.1 && mean_ratio>(step+0)*0.1){
      out_low_txt<<key<<endl;
    }
//    else{
//      hchi2_low->Fill(mean_ratio,sqrt(mean_ratio2-mean_ratio*mean_ratio));
//    }
    delete htemp0;
  }
  
  TFile* ofile = new TFile("chi2_output.root","RECREATE");
  hchi2_high->Write();
  hchi2_low->Write();

}

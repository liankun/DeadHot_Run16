void find_deadhot_by_slope(int runNumber=44){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);

  TH1D* hhigh_itg[2][5];
  TH1D* hlow_itg[2][5];

  char path[500];
  sprintf(path,"%d/Integral.root",runNumber);
  TFile* file = new TFile(path,"READONLY");
  
  map<int,int>key_to_key;
  MpcExMapper* mapper = MpcExMapper::instance();
  for(int i = 0;i < 49152;i++){
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    int index = 6*quadrant+sensor;
    int lx = mapper->get_lx(i);
    int ly = mapper->get_ly(i);
    int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
    key_to_key.insert(pair<int,int>(new_key,i));
  }

  
  for(int iarm = 0;iarm < 2;iarm++){
    for(int iitg=0;iitg<5;iitg++){
      char hname[500];
      sprintf(hname,"hhigh_adc_arm%d_integral%d",iarm,iitg);
      hhigh_itg[iarm][iitg] = (TH1D*)file->Get(hname);
      sprintf(hname,"hlow_adc_arm%d_integral%d",iarm,iitg);
      hlow_itg[iarm][iitg] = (TH1D*)file->Get(hname);
    }
  }

  for(int iitg=0;iitg<5;iitg++){
    char txt_name[500];
    sprintf(txt_name,"%d/bad_high_itg%d.txt",runNumber,iitg);
    ofstream bad_high_itg(txt_name);
    sprintf(txt_name,"%d/bad_low_itg%d.txt",runNumber,iitg);
    ofstream bad_low_itg(txt_name);
    for(int iarm = 0;iarm < 2;iarm++){
      for(int i = 0;i < 192*4;i++){
        double mean0 = 0;
        double mean1 = 0;
        double sq_mean0 = 0;
        double sq_mean1 = 1;
        int count0 = 0;
        int count1 = 0;
        for(int j = 32*i;j<32*(i+1);j++){
           
        }
      }
    }
  } 
}

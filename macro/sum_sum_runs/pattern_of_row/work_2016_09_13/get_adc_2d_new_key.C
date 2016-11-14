void get_adc_2d_new_key(){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);
  
  TFile* file = new TFile("../all_runs.root","READONLY");
  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");

  MpcExMapper* mapper = MpcExMapper::instance();

  TH2D* hhigh_adc_new_key = new TH2D("hhigh_adc_new_key","High ADC new key(Pedestal Subtracted) vs Key",49152,-0.5,49152-0.5,300,-40-0.5,260-0.5);

  TH2D* hlow_adc_new_key = new TH2D("hlow_adc_new_key","low ADC new key(Pedestal Subtracted) vs Key",49152,-0.5,49152-0.5,300,-40-0.5,260-0.5);

  for(int i = 0;i < 24576*2;i++){
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    int index = 6*quadrant+sensor;
    int lx = mapper->get_lx(i);
    int ly = mapper->get_ly(i);
    int new_key = 24576*arm+3072*layer+128*index+32*ly+lx;
    for(int j =0;j<300;j++){
      double content=hhigh_adc_key->GetBinContent(i+1,j+1);
      hhigh_adc_new_key->SetBinContent(new_key+1,j+1,content);
      content=hlow_adc_key->GetBinContent(i+1,j+1);
      hlow_adc_new_key->SetBinContent(new_key+1,j+1,content);
    }
  }

  TFile* ofile = new TFile("output_newkey.root","RECREATE");
  hhigh_adc_new_key->Write();
  hlow_adc_new_key->Write();

}

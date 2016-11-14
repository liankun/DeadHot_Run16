void new_key(){
  gSystem->Load("libMyMpcEx.so");
  TFile* file = new TFile("sum_sum0.root","READONLY");
  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");
  TH2D* hhigh_rawadc_key = (TH2D*)file->Get("hhigh_rawadc_key");
  TH2D* hlow_rawadc_key = (TH2D*)file->Get("hlow_rawadc_key");


  TH2D* hhigh_adc_new_key = new TH2D("hhigh_adc_new_key","High ADC vs New Key",49152,-0.5,49152-0.5,300,-40-0.5,260-0.5);
  hhigh_adc_new_key->GetXaxis()->SetTitle("new Key");
  hhigh_adc_new_key->GetYaxis()->SetTitle("ADC");
  
  TH2D* hlow_adc_new_key = new TH2D("hlow_adc_new_key","Low ADC vs New Key",49152,-0.5,49152-0.5,300,-40-0.5,260-0.5);
  hlow_adc_new_key->GetXaxis()->SetTitle("new Key");
  hlow_adc_new_key->GetYaxis()->SetTitle("ADC");

  TH2D* hhigh_rawadc_new_key = new TH2D("hhigh_rawadc_new_key","High Raw ADC vs New Key",49152,-0.5,49152-0.5,300,-40-0.5,260-0.5);
  hhigh_rawadc_new_key->GetXaxis()->SetTitle("new Key");
  hhigh_rawadc_new_key->GetYaxis()->SetTitle("ADC");
  
  TH2D* hlow_rawadc_new_key = new TH2D("hlow_rawadc_new_key","Low Raw ADC vs New Key",49152,-0.5,49152-0.5,300,-40-0.5,260-0.5);
  hlow_rawadc_new_key->GetXaxis()->SetTitle("new Key");
  hlow_rawadc_new_key->GetYaxis()->SetTitle("ADC");

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
    for(int j = 0;j<300;j++){
      double content = hhigh_adc_key->GetBinContent(i+1,j+1);
      double bin_center = hhigh_adc_key->GetYaxis()->GetBinCenter(j+1);
      hhigh_adc_new_key->Fill(new_key,bin_center,content);

      content = hlow_adc_key->GetBinContent(i+1,j+1);
      bin_center = hlow_adc_key->GetYaxis()->GetBinCenter(j+1);
      hlow_adc_new_key->Fill(new_key,bin_center,content);

      content = hhigh_rawadc_key->GetBinContent(i+1,j+1);
      bin_center = hhigh_rawadc_key->GetYaxis()->GetBinCenter(j+1);
      hhigh_rawadc_new_key->Fill(new_key,bin_center,content);

      content = hlow_rawadc_key->GetBinContent(i+1,j+1);
      bin_center = hlow_rawadc_key->GetYaxis()->GetBinCenter(j+1);
      hlow_rawadc_new_key->Fill(new_key,bin_center,content);
    }
  }
  TFile* ofile = new TFile("new_key.root","RECREATE");
  hhigh_adc_new_key->Write();
  hlow_adc_new_key->Write();
  hhigh_rawadc_new_key->Write();
  hlow_rawadc_new_key->Write();
}

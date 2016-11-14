void find_pedestal(){
  TFile* ifile = new TFile("bad_channel_adc.root","READONLY");
  if(!ifile){
    cout<<"open file failed !"<<endl;
    return;
  }
  TH2D* hhigh_bad_adc = (TH2D*)ifile->Get("hhigh_bad_adc");
  TH2D* hlow_bad_adc = (TH2D*)ifile->Get("hlow_bad_adc");
}

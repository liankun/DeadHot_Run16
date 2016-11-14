void draw_ped_sigma(){
  ifstream ped("ped_from_db.txt");
  int key;
  double mean_high;
  double mean_low;
  double sigma_high;
  double sigma_low;
  TH2D* hped_high = new TH2D("hped_high","High Pedestal",50,0,50,100,0,10);
  hped_high->GetXaxis()->SetTitle("Pedestal");
  hped_high->GetYaxis()->SetTitle("Sigma");
  TH2D* hped_low = new TH2D("hped_low","Low Pedestal",50,0,50,100,0,10);
  hped_low->GetXaxis()->SetTitle("Pedestal");
  hped_low->GetYaxis()->SetTitle("Sigma");
  while(ped>>key>>mean_high>>sigma_high>>mean_low>>sigma_low){
//    cout <<key<<" "<<mean_high<<" "<<sigma_high<<" "<<mean_low<<" "<<sigma_low<<endl;
    hped_high->Fill(mean_high,sigma_high);
    hped_low->Fill(mean_low,sigma_low);
  }
}

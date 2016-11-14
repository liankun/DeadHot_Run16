void get_discrete_channel(int group = 0){
  char path[500];
//  sprintf(path,"%d/sum_sum.root",group);
  TFile* file = new TFile("all_runs.root","READONLY");
  TH2D* hhigh_adc_key = (TH2D*)file->Get("hhigh_adc_key");
  TH2D* hlow_adc_key = (TH2D*)file->Get("hlow_adc_key");

//  sprintf(path,"%d/high_discrete.txt",group);
  ofstream high_discrete("high_discrete.txt");
//  sprintf(path,"%d/low_discrete.txt",group);
  ofstream low_discrete("low_discrete.txt");

  for(int i = 0;i < 24576*2;i++){
    hhigh_adc_key->SetAxisRange(i,i,"X");
    hlow_adc_key->SetAxisRange(i,i,"X");
    TH1D* htemp0 = hhigh_adc_key->ProjectionY();
    TH1D* htemp1 = hlow_adc_key->ProjectionY();
    double entries0 = htemp0->GetEntries();
    double entries1 = htemp1->GetEntries();
    int high_bin0=htemp0->FindBin(15);
    int high_bin1=htemp0->FindBin(110);
    int low_bin0=htemp1->FindBin(5);
    int low_bin1=htemp1->FindBin(40);
    int freq=0;
    if(entries0>1){
      for(int ibin=high_bin0;ibin<high_bin1;ibin++){
        double content0=htemp0->GetBinContent(ibin);
        double content1=htemp0->GetBinContent(ibin-1);
        double content2=htemp0->GetBinContent(ibin+1);
        double mean01=(content0+content1)/2.;
	double mean02=(content0+content2)/2.;
        if((mean01>0.0001) && (fabs(content0-content1) > mean01)){
//cout<<content0<<" "<<content1<<" "<<content2<<" "<<10*sqrt(mean01)<<" "<<10*sqrt(mean02)<<endl;          	  
	  freq++;
	  if(freq>8){
            high_discrete<<i<<" "<<i<<endl;
	    break;
	  }
	}
        if((mean02>0.0001) && (fabs(content0-content2) > mean02)){
//cout<<content0<<" "<<content1<<" "<<content2<<" "<<10*sqrt(mean01)<<" "<<10*sqrt(mean02)<<endl;
	  freq++;
          if(freq>8){
            high_discrete<<i<<" "<<i<<endl;
	    break;
	  }
	}
      }
    }
    freq=0;
    if(entries1>1){
      for(int ibin=low_bin0;ibin<low_bin1;ibin++){
        double content0=htemp1->GetBinContent(ibin);
        double content1=htemp1->GetBinContent(ibin-1);
        double content2=htemp1->GetBinContent(ibin+1);
        double mean01=(content0+content1)/2.;
	double mean02=(content0+content2)/2.;
        if((mean01>0.0001) && (fabs(content0-content1) > mean01)){
//cout<<content0<<" "<<content1<<" "<<content2<<" "<<10*sqrt(mean01)<<" "<<10*sqrt(mean02)<<endl;
	  freq++;
	  if(freq>8){
	    low_discrete<<i<<" "<<i<<endl;
	    break;
	  }
	}
        if((mean02>0.0001) && (fabs(content0-content2) > mean02)){
//cout<<content0<<" "<<content1<<" "<<content2<<" "<<10*sqrt(mean01)<<" "<<10*sqrt(mean02)<<endl;
	  freq++;
	  if(freq>8){
	    low_discrete<<i<<" "<<i<<endl;
	    break;
	  }
	}
      }
    }
  }
}

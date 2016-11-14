#include<fstream>
void read_mip(){
  ifstream in_mip_txt("ofs_run_log.txt");
  int runNumber=0;
  int sensor=0;
  double mip=0;
  
  TH2D* hsensor_mip = new TH2D("hsensor_mip","MIP vs Sensor",384,-0.5,384-0.5,200,-0.5,200-0.5);
  
  while(in_mip_txt>>runNumber>>sensor>>mip){
    hsensor_mip->Fill(sensor,mip);
    if(sensor==4){
      cout<<runNumber<<" "<<mip<<endl;
    }
  }

  TFile* ofile = new TFile("sensor_mip.root","RECREATE");
  hsensor_mip->Write();
}

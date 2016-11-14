void draw_group_geom(){
  gSystem->Load("libMyMpcEx.so");
  recoConsts* rc = recoConsts::instance();
  rc->set_IntFlag("RUNNUMBER",430013);
  MpcExMapper* mapper = MpcExMapper::instance();
  Exogram* hgrammy[2];
  Exogram* hgrammy[0] = new Exogram("hgrammy0","Exogram Arm 0",900,-24,24,900,-24,24,8,-0.5,7.5);
  Exogram* hgrammy[1] = new Exogram("hgrammy1","Exogram Arm 1",900,-24,24,900,-24,24,8,-0.5,7.5);
 
  int group_south[4][6]={
                   {0,1,2,3,4,5},
		   {6,0,2,3,4,5},
		   {0,1,2,3,4,5},
		   {6,0,2,3,4,5}
		  };  
  int group_north[4][6]={
                   {6,0,2,3,4,5},
		   {0,1,2,3,4,5},
		   {6,0,2,3,4,5},
		   {0,1,2,3,4,5}
		  };  
  
  for(int i=0;i<49152;i++){
    int arm = mapper->get_arm(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    if(arm==0){
      hgrammy[arm]->FillEx(i,group_south[quadrant][sensor]+1);
    }
    else{
      hgrammy[arm]->FillEx(i,group_north[quadrant][sensor]+1);
    }
  }

  TFile* ofile = new TFile("work_2016_09_11/group_gemo.root","RECREATE");
  hgrammy[0]->Write();
  hgrammy[1]->Write();
  for(int iarm=0;iarm<2;iarm++){
    for(int ilayer=0;ilayer<8;ilayer++){
      hgrammy[iarm]->SetAxisRange(ilayer,ilayer,"z");
      TH2D* htemp=hgrammy[iarm]->Project3D("yx");
      char hname[500];
      sprintf(hname,"harm%d_layer%d",iarm,ilayer);
      htemp->SetName(hname);
      htemp->Write();
    }
  }
}

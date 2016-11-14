void draw_mpcex_r(){
  TH1D* hr[2][8];
  TH2D* hmpcex_nxy[2][8];
  for(int iarm = 0;iarm < 2;iarm++){
    for(int ilayer = 0;ilayer<8;ilayer++){
      char hname[500];
      char name[100];
      sprintf(hname,"hr_arm%d_layer%d",iarm,ilayer);
      hr[iarm][ilayer] = new TH1D(hname,hname,5000,6,25);
      sprintf(name,"hmpcex_nxy_layer%d_arm%d",ilayer,iarm);
      int Nx = 198*2;
      float ScaleX = 1;
      int Ny = 24*2;
      float ScaleY = 8;
      if(ilayer%2 == 1){
        Nx = 24*2;
        ScaleX = 8;
        Ny = 198*2;
        ScaleY = 1;
      }
      hmpcex_nxy[iarm][ilayer] = new TH2D(name,name,Nx,-0.5*ScaleX,(Nx-0.5)*ScaleX,Ny,-0.5*ScaleY,(Ny-0.5)*ScaleY);

    }
  }
  gSystem->Load("libMyMpcEx.so");
  MpcExMapper* mapper = MpcExMapper::instance();

  Exogram* grammy = new Exogram("hgrammy","Exogram arm 0",900,-24,24,900,-24,24,8,-0.5,7.5);
  
  double r_odd[10] = {6.5,9,10.5,12.1,13.5,14.4,15.6,16.8,18.1,21.5};
  double r_even[10] = {6.5,9,10.5,12.1,13.5,14.4,15.6,16.8,18.1,21.5};
  int count_odd[9] = {0};
  int count_even[9] = {0};


  for(int i = 0;i < 49152;i++){
    int arm = mapper->get_arm(i);
    int layer = mapper->get_layer(i);
    double pos_x = mapper->get_x(i);
    double pos_y = mapper->get_y(i);
    double r = sqrt(pos_x*pos_x+pos_y*pos_y);
    hr[arm][layer]->Fill(r);
    double scale = 0;
    int nx = mapper->get_nx(i);
    int ny = mapper->get_ny(i);
    int quadrant = mapper->get_quadrant(i);
    int sensor = mapper->get_sensor_in_quadrant(i);
    int packet = mapper->get_packet(i);
    int chain = mapper->get_chain(i);
    int chipmap = mapper->get_chipmap(i);
    
    if(arm==0 && layer==2 && quadrant==1){
      cout <<layer<<" "<<quadrant<<" "<<packet<<" "<<chain<<" "<<chipmap<<" "<<i<<endl;
    }
    if(arm==0 && layer==3 && quadrant==2){
      cout <<layer<<" "<<quadrant<<" "<<packet<<" "<<chain<<" "<<chipmap<<" "<<i<<endl;
    }

    if(layer%2 == 0){
      for(int j = 0;j<9;j++){
        if(r >= r_even[j] && r < r_even[j+1]){
          scale = j+1;
	  count_even[j]++;
	}
      }
    }

    if(layer%2 == 1){
      for(int j = 0;j<9;j++){
        if(r >= r_odd[j] && r < r_odd[j+1]){
	    scale = j+1;
	    count_odd[j]++;
	}
      }
    }
//    scale = sensor+0.5;
    grammy->FillEx(i,nx+198*ny);
    hmpcex_nxy[arm][layer]->SetBinContent(2*nx+1+1,2*ny+1+1,scale);
  
  }
  

  for(int j = 0;j < 9;j++){
    cout<<j<<" odd "<<count_odd[j]<<" "<<count_odd[j]/8<<endl;
    cout<<j<<" event "<<count_even[j]<<" "<<count_odd[j]/8<<endl;
  }

  TFile* ofile = new TFile("mpcex_sensor.root","RECREATE");
  grammy->Write();
  for(int iarm = 0;iarm < 2;iarm++){
    for(int ilayer = 0;ilayer < 8;ilayer++){
      hr[iarm][ilayer]->Write();
      hmpcex_nxy[iarm][ilayer]->Write();
    }
  }
}

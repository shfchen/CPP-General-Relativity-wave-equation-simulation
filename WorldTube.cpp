#include "WorldTube.h"

WorldTube::WorldTube(Grid& thegrid, Coordinates &coords){}

void WorldTube::init_world_tube(Grid & thegrid, Coordinates &coords)
{
  addSingFieldToLeftElemExt.resize(params.grid.numelems-1,false);
  addSingFieldToRightElemExt.resize(params.grid.numelems-1,false);
  subSingFieldFromLeftElemExt.resize(params.grid.numelems-1,false);
  subSingFieldFromRightElemExt.resize(params.grid.numelems-1,false);
  inWorldTube.resize(params.grid.numelems-1,false);
  //boolean flags represent boundaries excluding scri+ and scri-

  
  for (int j=1; j<params.grid.numelems-1; j++){
    double rho = thegrid.gridNodeLocations().get(j+1,0);
    if((abs(rho-Rminus)<1.e-10)||(abs(rho-Rplus)<1.e-10))
      {
	coords.timeDepTrans.at(j)=true;
      }
    if((rho>Wminus)&&(rho<Wplus)){
      inWorldTube.at(j)=true;
    }else if(abs(rho-Wminus)<1.e-10){
      addSingFieldToLeftElemExt.at(j)=true;
      subSingFieldFromRightElemExt.at(j)=true;
    }else if(abs(rho-Wplus)<1.e-10){
      addSingFieldToLeftElemExt.at(j)=true;
      subSingFieldFromRightElemExt.at(j)=true;
    }
  }
      
}


void WorldTube::set_world_tube_window(Grid &thegrid, Coordinates &coords){

  double wind, dwind, d2wind;
  for(int j=0; j<params.grid.numelems; j++){
    for(int i=0; i<=params.grid.elemorder; i++){
    
      if((j==0)&&(i!=params.grid.elemorder)){
	thegrid.window.set(j,i,0.);
	thegrid.dwindow.set(j,i,0.);
	thegrid.d2window.set(j,i,0.);
      }
      else if((j==params.grid.numelems-1)&&(i==0)&&inWorldTube.at(j-1)){
 	thegrid.window.set(j,i,1.);
	thegrid.dwindow.set(j,i,1.);
	thegrid.d2window.set(j,i,1.);
      }
      else if(j==params.grid.numelems-1){
 	thegrid.window.set(j,i,0.);
	thegrid.dwindow.set(j,i,0.);
	thegrid.d2window.set(j,i,0.);
      }else if 
	  ((j==0)&&(inWorldTube.at(j))&&(i==params.grid.elemorder)){
	thegrid.window.set(j,i,1.);
	thegrid.dwindow.set(j,i,1.);
       thegrid.d2window.set(j,i,1.);
      }else if
       	  ((j==0)&&(!inWorldTube.at(j))&&(i=params.grid.elemorder)){
	thegrid.window.set(j,i,0.);
	thegrid.dwindow.set(j,i,0.);
       thegrid.d2window.set(j,i,0.);
      }else if((!inWorldTube.at(j-1))&&(inWorldTube.at(j))&&(i==params.grid.elemorder)){
	thegrid.window.set(j,i,1.);
	thegrid.dwindow.set(j,i,1.);
	thegrid.d2window.set(j,i,1.);
      } else if ((inWorldTube.at(j-1))&&(!inWorldTube.at(j))&&(i==0)){
  	thegrid.window.set(j,i,1.);
	thegrid.dwindow.set(j,i,1.);
	thegrid.d2window.set(j,i,1.);
      } else if (inWorldTube.at(j-1)&&(inWorldTube.at(j))){
	thegrid.window.set(j,i,1.);
	thegrid.dwindow.set(j,i,1.);
	thegrid.d2window.set(j,i,1.);
      } else {
	thegrid.window.set(j,i,0.);
	thegrid.dwindow.set(j,i,0.);
	thegrid.d2window.set(j,i,0.);
      }
    }
  }
}
 

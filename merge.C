
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <iomanip>

#include "TStyle.h"
#include "TFile.h"
#include "dataMCplotMaker.h"

int merge()
{

//information about the histogram files
char* date = "Mar9";
//file name
//char* suffix2 ="v4_met100_inv20_ge2j";
char* suffix2 = "v4_signal_M20-70";

//plot names
//title for the plots
//char* suffix = "E^{miss}_{T} > 100, M_{ll} > 20, >=2 Jets";
//char* suffix = " M_{ll} > 20, >=2 Jets";
char* suffix = "signal_region_20 < M_{ll} < 70";

TFile* data =   new TFile(Form("/home/users/sanil/dilepton/full_set/%s/data_%s.root"	,date,suffix2));
TFile* tt =     new TFile(Form("/home/users/sanil/dilepton/full_set/%s/tt_%s.root"	,date,suffix2));
TFile* dy =     new TFile(Form("/home/users/sanil/dilepton/full_set/%s/dy_%s.root"	,date,suffix2)); 
TFile* wz =     new TFile(Form("/home/users/sanil/dilepton/full_set/%s/wz_%s.root"	,date,suffix2)); 





 /* Data */
  TH1F* of_invmass     	= (TH1F*) data->Get("of_invmass"); 
  TH1F* sf_invmass    	= (TH1F*) data->Get("sf_invmass"); 

  TH1F* of_met		= (TH1F*) data->Get("of_met"); 
  TH1F* sf_met 		= (TH1F*) data->Get("sf_met"); 

  TH1F* sf_njets        = (TH1F*) data->Get("sf_njets"); 
  TH1F* of_njets        = (TH1F*) data->Get("of_njets"); 

  TH1F* sf_jetspt       = (TH1F*) data->Get("sf_jetspt"); 
  TH1F* of_jetspt       = (TH1F*) data->Get("of_jetspt"); 

  TH1F* sf_mt2       	= (TH1F*) data->Get("sf_mt2"); 
  TH1F* of_mt2		= (TH1F*) data->Get("of_mt2"); 

  TH1F* of_metphi	= (TH1F*) data->Get("of_metphi"); 
  TH1F* sf_metphi       = (TH1F*) data->Get("sf_metphi"); 

  TH1F* cesf_invmass	= (TH1F*) data->Get("cesf_invmass"); 
  TH1F* ceof_invmass  	= (TH1F*) data->Get("ceof_invmass"); 

  TH1F* fosf_invmass  	= (TH1F*) data->Get("fosf_invmass"); 
  TH1F* foof_invmass   	= (TH1F*) data->Get("foof_invmass"); 

  TH1F* cesf_mt2       	= (TH1F*) data->Get("cesf_mt2"); 
  TH1F* ceof_mt2       	= (TH1F*) data->Get("ceof_mt2"); 

  TH1F* fosf_mt2       	= (TH1F*) data->Get("fosf_mt2"); 
  TH1F* foof_mt2       	= (TH1F*) data->Get("foof_mt2"); 




  /* WZ*/ 
  TH1F* wz_of_invmass       	= (TH1F*) wz->Get("of_invmass"); 
  TH1F* wz_sf_invmass       	= (TH1F*) wz->Get("sf_invmass"); 

  TH1F* wz_of_met 	    	= (TH1F*) wz->Get("of_met"); 
  TH1F* wz_sf_met           	= (TH1F*) wz->Get("sf_met"); 

  TH1F* wz_sf_njets       	= (TH1F*) wz->Get("sf_njets"); 
  TH1F* wz_of_njets       	= (TH1F*) wz->Get("of_njets"); 

  TH1F* wz_sf_jetspt       	= (TH1F*) wz->Get("sf_jetspt"); 
  TH1F* wz_of_jetspt       	= (TH1F*) wz->Get("of_jetspt"); 

  TH1F* wz_sf_mt2       	= (TH1F*) wz->Get("sf_mt2"); 
  TH1F* wz_of_mt2		= (TH1F*) wz->Get("of_mt2"); 

  TH1F* wz_of_metphi		= (TH1F*) wz->Get("of_metphi"); 
  TH1F* wz_sf_metphi       	= (TH1F*) wz->Get("sf_metphi"); 

  TH1F* wz_cesf_invmass		= (TH1F*) wz->Get("cesf_invmass"); 
  TH1F* wz_ceof_invmass  	= (TH1F*) wz->Get("ceof_invmass"); 

  TH1F* wz_fosf_invmass  	= (TH1F*) wz->Get("fosf_invmass"); 
  TH1F* wz_foof_invmass   	= (TH1F*) wz->Get("foof_invmass"); 

  TH1F* wz_cesf_mt2       	= (TH1F*) wz->Get("cesf_mt2"); 
  TH1F* wz_ceof_mt2       	= (TH1F*) wz->Get("ceof_mt2"); 

  TH1F* wz_fosf_mt2       	= (TH1F*) wz->Get("fosf_mt2"); 
  TH1F* wz_foof_mt2       	= (TH1F*) wz->Get("foof_mt2"); 

 	/*tt-bar*/ 
  TH1F* tt_of_invmass       	= (TH1F*) tt->Get("of_invmass"); 
  TH1F* tt_sf_invmass       	= (TH1F*) tt->Get("sf_invmass"); 

  TH1F* tt_of_met 	    	= (TH1F*) tt->Get("of_met"); 
  TH1F* tt_sf_met           	= (TH1F*) tt->Get("sf_met"); 

  TH1F* tt_sf_njets       	= (TH1F*) tt->Get("sf_njets"); 
  TH1F* tt_of_njets       	= (TH1F*) tt->Get("of_njets"); 

  TH1F* tt_sf_jetspt       	= (TH1F*) tt->Get("sf_jetspt"); 
  TH1F* tt_of_jetspt       	= (TH1F*) tt->Get("of_jetspt"); 

  TH1F* tt_sf_mt2       	= (TH1F*) tt->Get("sf_mt2"); 
  TH1F* tt_of_mt2		= (TH1F*) tt->Get("of_mt2"); 

  TH1F* tt_of_metphi		= (TH1F*) tt->Get("of_metphi"); 
  TH1F* tt_sf_metphi       	= (TH1F*) tt->Get("sf_metphi"); 

  TH1F* tt_cesf_invmass		= (TH1F*) tt->Get("cesf_invmass"); 
  TH1F* tt_ceof_invmass  	= (TH1F*) tt->Get("ceof_invmass"); 

  TH1F* tt_fosf_invmass  	= (TH1F*) tt->Get("fosf_invmass"); 
  TH1F* tt_foof_invmass   	= (TH1F*) tt->Get("foof_invmass"); 

  TH1F* tt_cesf_mt2       	= (TH1F*) tt->Get("cesf_mt2"); 
  TH1F* tt_ceof_mt2       	= (TH1F*) tt->Get("ceof_mt2"); 

  TH1F* tt_fosf_mt2       	= (TH1F*) tt->Get("fosf_mt2"); 
  TH1F* tt_foof_mt2       	= (TH1F*) tt->Get("foof_mt2"); 

 	/*DY*/ 
  TH1F* dy_of_invmass       	= (TH1F*) dy->Get("of_invmass"); 
  TH1F* dy_sf_invmass       	= (TH1F*) dy->Get("sf_invmass"); 

  TH1F* dy_of_met 	    	= (TH1F*) dy->Get("of_met"); 
  TH1F* dy_sf_met           	= (TH1F*) dy->Get("sf_met"); 

  TH1F* dy_sf_njets       	= (TH1F*) dy->Get("sf_njets"); 
  TH1F* dy_of_njets       	= (TH1F*) dy->Get("of_njets"); 

  TH1F* dy_sf_jetspt       	= (TH1F*) dy->Get("sf_jetspt"); 
  TH1F* dy_of_jetspt       	= (TH1F*) dy->Get("of_jetspt"); 

  TH1F* dy_sf_mt2       	= (TH1F*) dy->Get("sf_mt2"); 
  TH1F* dy_of_mt2		= (TH1F*) dy->Get("of_mt2"); 

  TH1F* dy_of_metphi		= (TH1F*) dy->Get("of_metphi"); 
  TH1F* dy_sf_metphi       	= (TH1F*) dy->Get("sf_metphi"); 

  TH1F* dy_cesf_invmass		= (TH1F*) dy->Get("cesf_invmass"); 
  TH1F* dy_ceof_invmass  	= (TH1F*) dy->Get("ceof_invmass"); 

  TH1F* dy_fosf_invmass  	= (TH1F*) dy->Get("fosf_invmass"); 
  TH1F* dy_foof_invmass   	= (TH1F*) dy->Get("foof_invmass"); 

  TH1F* dy_cesf_mt2       	= (TH1F*) dy->Get("cesf_mt2"); 
  TH1F* dy_ceof_mt2       	= (TH1F*) dy->Get("ceof_mt2"); 

  TH1F* dy_fosf_mt2       	= (TH1F*) dy->Get("fosf_mt2"); 
  TH1F* dy_foof_mt2       	= (TH1F*) dy->Get("foof_mt2"); 

		/*background*/

 std::vector<TH1F*>	 of_invmass_b;
 std::vector<TH1F*>	 sf_invmass_b;

 std::vector<TH1F*>	 of_met_b;
 std::vector<TH1F*>	 sf_met_b;

 std::vector<TH1F*>	 of_njets_b;
 std::vector<TH1F*>	 sf_njets_b;

 std::vector<TH1F*>	 of_jetspt_b;
 std::vector<TH1F*>	 sf_jetspt_b;

 std::vector<TH1F*>	 of_mt2_b;
 std::vector<TH1F*>	 sf_mt2_b;

 std::vector<TH1F*>	 of_metphi_b;
 std::vector<TH1F*>	 sf_metphi_b;

 std::vector<TH1F*>	 ceof_invmass_b;
 std::vector<TH1F*>	 cesf_invmass_b;

 std::vector<TH1F*>	 foof_invmass_b;
 std::vector<TH1F*>	 fosf_invmass_b;

 std::vector<TH1F*>	 ceof_mt2_b;
 std::vector<TH1F*>	 cesf_mt2_b;

 std::vector<TH1F*>	 foof_mt2_b;
 std::vector<TH1F*>	 fosf_mt2_b;


std::vector<char*>	 titles;
std::vector <Color_t> colors;

titles.push_back("tt"); 
colors.push_back(kGreen+2);

titles.push_back("dy"); 
colors.push_back(kCyan+2);

titles.push_back("wz"); 
colors.push_back(kRed+1);


/*tt-bar*/
of_invmass_b.push_back(tt_of_invmass);
sf_invmass_b.push_back(tt_sf_invmass);

of_met_b.push_back(tt_of_met);
sf_met_b.push_back(tt_sf_met);

of_njets_b.push_back(tt_of_njets);
sf_njets_b.push_back(tt_sf_njets);


of_jetspt_b.push_back(tt_of_jetspt);
sf_jetspt_b.push_back(tt_sf_jetspt);
            
of_mt2_b.push_back(tt_of_mt2);
sf_mt2_b.push_back(tt_sf_mt2);
            
of_metphi_b.push_back(tt_of_metphi);
sf_metphi_b.push_back(tt_sf_metphi);
            
ceof_invmass_b.push_back(tt_ceof_invmass);
cesf_invmass_b.push_back(tt_cesf_invmass);
            
foof_invmass_b.push_back(tt_foof_invmass);
fosf_invmass_b.push_back(tt_fosf_invmass);
            
ceof_mt2_b.push_back(tt_ceof_mt2);
cesf_mt2_b.push_back(tt_cesf_mt2);
            
foof_mt2_b.push_back(tt_foof_mt2);
fosf_mt2_b.push_back(tt_fosf_mt2);

/*DY*/
of_invmass_b.push_back(dy_of_invmass);
sf_invmass_b.push_back(dy_sf_invmass);

of_met_b.push_back(dy_of_met);
sf_met_b.push_back(dy_sf_met);

of_njets_b.push_back(dy_of_njets);
sf_njets_b.push_back(dy_sf_njets);


of_jetspt_b.push_back(dy_of_jetspt);
sf_jetspt_b.push_back(dy_sf_jetspt);
            
of_mt2_b.push_back(dy_of_mt2);
sf_mt2_b.push_back(dy_sf_mt2);
            
of_metphi_b.push_back(dy_of_metphi);
sf_metphi_b.push_back(dy_sf_metphi);
            
ceof_invmass_b.push_back(dy_ceof_invmass);
cesf_invmass_b.push_back(dy_cesf_invmass);
            
foof_invmass_b.push_back(dy_foof_invmass);
fosf_invmass_b.push_back(dy_fosf_invmass);
            
ceof_mt2_b.push_back(dy_ceof_mt2);
cesf_mt2_b.push_back(dy_cesf_mt2);
            
foof_mt2_b.push_back(dy_foof_mt2);
fosf_mt2_b.push_back(dy_fosf_mt2);

/*WZ*/
of_invmass_b.push_back(wz_of_invmass);
sf_invmass_b.push_back(wz_sf_invmass);

of_met_b.push_back(wz_of_met);
sf_met_b.push_back(wz_sf_met);

of_njets_b.push_back(wz_of_njets);
sf_njets_b.push_back(wz_sf_njets);


of_jetspt_b.push_back(wz_of_jetspt);
sf_jetspt_b.push_back(wz_sf_jetspt);
            
of_mt2_b.push_back(wz_of_mt2);
sf_mt2_b.push_back(wz_sf_mt2);
            
of_metphi_b.push_back(wz_of_metphi);
sf_metphi_b.push_back(wz_sf_metphi);
            
ceof_invmass_b.push_back(wz_ceof_invmass);
cesf_invmass_b.push_back(wz_cesf_invmass);
            
foof_invmass_b.push_back(wz_foof_invmass);
fosf_invmass_b.push_back(wz_fosf_invmass);
            
ceof_mt2_b.push_back(wz_ceof_mt2);
cesf_mt2_b.push_back(wz_cesf_mt2);
            
foof_mt2_b.push_back(wz_foof_mt2);
fosf_mt2_b.push_back(wz_fosf_mt2);






/*signal */
vector<TH1F*> empty;
vector<char*> empty_title;
TH1F* null = new TH1F("","",1,0,1);
empty.push_back(null);
empty_title.push_back(" ");

//1
dataMCplotMaker(sf_met,sf_met_b, titles, 	
Form("SF met_%s",suffix),"",	Form("--noFill  --xAxisLabel E_{T}^{miss} 			  --legendRight 0.1 --outputName met_SF_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(of_met,of_met_b, titles,	
Form("OF met_%s",suffix),"",	Form("--noFill  --xAxisLabel E_{T}^{miss} 			  --legendRight 0.1 --outputName met_OF_%s"	,suffix),empty,empty_title,colors); 

//2
dataMCplotMaker(sf_njets,sf_njets_b, titles,  	
Form("SF njets_%s",suffix),"",	Form("--noFill  --xAxisLabel Jet Multiplicity --xAxisUnit --legendRight 0.1 --outputName njets_SF_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(of_njets,of_njets_b, titles,  	
Form("OF njets_%s",suffix),"",	Form("--noFill  --xAxisLabel Jet Multiplicity --xAxisUnit --legendRight 0.1 --outputName njets_OF_%s"	,suffix),empty,empty_title,colors); 

//3
dataMCplotMaker(sf_invmass,sf_invmass_b, titles,
Form("SF invmass_%s",suffix),"",Form("--noFill  --vLine 75 --vLine 105  	--isLinear	  --legendRight 0.1 --outputName invmass_SF_%s " ,suffix),empty,empty_title,colors); 

dataMCplotMaker(of_invmass,of_invmass_b, titles,
Form("OF invmass_%s",suffix),"",Form("--noFill  --vLine 75 --vLine 105 	  	--isLinear	  --legendRight 0.1 --outputName invmass_OF_%s " ,suffix),empty,empty_title,colors); 

//4
/*
dataMCplotMaker(sf_jetspt,sf_jetspt_b, titles,
Form("SF jetspt_%s",suffix),"",	Form("--noFill  --xAxisLabel \\sum Jet p$_{T}$ --xAxisUnit --legendRight 0.1 --outputName jetspt_SF_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(of_jetspt,of_jetspt_b, titles,
Form("OF jetspt_%s",suffix),"",	Form("--noFill  --xAxisLabel \\sum Jet p$_{T}$ --xAxisUnit --legendRight 0.1 --outputName jetspt_OF_%s"	,suffix),empty,empty_title,colors); 
*/
//5
dataMCplotMaker(sf_mt2,sf_mt2_b, titles,
Form("SF mt2_%s",suffix),"",	Form("--noFill  --xAxisLabel M_{T2} --xAxisUnit --legendRight 0.1 --outputName mt2_SF_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(of_mt2,of_mt2_b, titles,
Form("OF mt2_%s",suffix),"",	Form("--noFill  --xAxisLabel M_{T2} --xAxisUnit --legendRight 0.1 --outputName mt2_OF_%s"	,suffix),empty,empty_title,colors); 

//6
dataMCplotMaker(sf_metphi,sf_metphi_b, titles,
Form("SF metphi_%s",suffix),"",	Form("--noFill  --xAxisLabel Met\\Phi --xAxisUnit --legendRight 0.1 --outputName metphi_SF_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(of_metphi,of_metphi_b, titles,
Form("OF metphi_%s",suffix),"",	Form("--noFill  --xAxisLabel Met\\Phi --xAxisUnit --legendRight 0.1 --outputName metphi_OF_%s"	,suffix),empty,empty_title,colors); 

//7
dataMCplotMaker(cesf_invmass,cesf_invmass_b, titles,
Form("SF cesf_invmass_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Central_SF_invamss_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(ceof_invmass,ceof_invmass_b, titles,
Form("OF ceof_invmass_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Central_OF_invamss_%s"	,suffix),empty,empty_title,colors); 

//8
dataMCplotMaker(fosf_invmass,fosf_invmass_b, titles,
Form("SF fosf_invmass_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Forward_SF_invamss_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(foof_invmass,foof_invmass_b, titles,
Form("OF foof_invmass_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Forward_OF_invamss_%s"	,suffix),empty,empty_title,colors); 

//9
dataMCplotMaker(cesf_mt2,cesf_mt2_b, titles,
Form("SF cesf_mt2_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Central_SF_mt2_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(ceof_mt2,ceof_mt2_b, titles,
Form("OF ceof_mt2_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Central_OF_mt2_%s"	,suffix),empty,empty_title,colors); 

//10
dataMCplotMaker(fosf_mt2,fosf_mt2_b, titles,
Form("SF fosf_mt2_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Forward_SF_mt2_%s"	,suffix),empty,empty_title,colors); 

dataMCplotMaker(foof_mt2,foof_mt2_b, titles,
Form("OF foof_mt2_%s",suffix),"",	Form("--noFill  --xAxisLabel --xAxisUnit --legendRight 0.1 --outputName Forward_OF_mt2_%s"	,suffix),empty,empty_title,colors); 


  return 0;
}

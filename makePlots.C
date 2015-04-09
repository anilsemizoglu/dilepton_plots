// C++
#include <iostream>
#include <stdio.h>  
#include <vector>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <fstream>

// ROOT
#include "TBenchmark.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TLegend.h"
#include "TRandom1.h"
#include "TPad.h"
#include "TCut.h"
#include "TH2F.h"
#include "TH1.h"
#include "THStack.h"
#include "TMath.h"
#include "Math/VectorUtil.h"
#include "Math/Vector4D.h"
#include "Math/LorentzVector.h"
#include "TLorentzVector.h"

// CMS2
#include "CMS2.h"
#include "muonSelections.h"
#include "susySelections.h"
#include "/home/users/sanil/CORE/ssSelections.h"
#include "eventSelections.h"
#include "MT2/MT2.h"
#include "MT2/MT2Utility.h"

#include "electronSelections.h"
#include "trackSelections.h"


// Good run list

#include "/home/users/sanil/CMSSW_5_3_2_patch4_V05-03-23/src/CMS2/NtupleMacros/Tools/goodrun.cc"

// My includes
#include "/home/users/sanil/myheaders/myheader.h"
//#include "/home/users/sanil/myheaders/triggerWeights.h"
#include "DL.h"
typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVec;

using namespace std;
using namespace ROOT::Math;
using namespace dl;


int ScanChain( TChain* chain, char* sampleType = "", bool ismc = true, bool fast = true, int nEvents = -1, string skimFilePrefix = "test") {

  // Benchmark
  TBenchmark *bmark = new TBenchmark();
  bmark->Start("benchmark");
//counters
int 	file_count = 0, trkProblem=0, event_count = 0;

float   ee_central = 0, mm_central = 0, em_central = 0,
	ee_forward = 0, mm_forward = 0, em_forward = 0,

   	sf_forward = 0, of_forward = 0,
    	sf_central = 0, of_central = 0,
    	sf_count   = 0, of_count   = 0,
/*
    	sf_mt2Tail_central = 0,of_mt2Tail_central = 0,
    	sf_mt2Zero_central = 0,of_mt2Zero_central = 0,

    	sf_mt2Tail_forward = 0,of_mt2Tail_forward = 0,
    	sf_mt2Zero_forward = 0,of_mt2Zero_forward = 0,
*/
    	ce_in_sf = 0, ce_out_sf = 0, fo_in_sf = 0, fo_out_sf = 0,  
    	ce_in_of = 0, ce_out_of = 0, fo_in_of = 0, fo_out_of = 0;




	TH1F   *of_invmass 	= new TH1F("of_invmass","of_invmass_",60,0,300);
	TH1F   *sf_invmass 	= new TH1F("sf_invmass","sf_invmass_",60,0,300);

	TH1F   *of_mt2 		= new TH1F("of_mt2","of_mt2_",70,0,350);
	TH1F   *sf_mt2 		= new TH1F("sf_mt2","sf_mt2_",70,0,350);

	TH1F   *of_njets 	= new TH1F("of_njets","of_njets_",10,0,10);
	TH1F   *sf_njets 	= new TH1F("sf_njets","sf_njets_",10,0,10);

	TH1F   *of_nbtag 	= new TH1F("of_nbtag","of_btag_",10,0,10);
	TH1F   *sf_nbtag 	= new TH1F("sf_nbtag","sf_btag_",10,0,10);

	TH1F   *of_met 		= new TH1F("of_met","of_met_",60,0,300);
	TH1F   *sf_met 		= new TH1F("sf_met","sf_met_",60,0,300);

	TH1F   *of_metphi 	= new TH1F("of_metphi","of_metphi_",80,-4,4);
	TH1F   *sf_metphi 	= new TH1F("sf_metphi","sf_metphi_",80,-4,4);

	TH1F   *of_jetspt 	= new TH1F("of_jetspt","of_jetspt_",80,0,400);
	TH1F   *sf_jetspt 	= new TH1F("sf_jetspt","sf_jetspt_",80,0,400);


	/*central and forward plots*/

	TH1F   *cesf_invmass 	= new TH1F("cesf_invmass","cesf_invmass_",60,0,300);
	TH1F   *ceof_invmass 	= new TH1F("ceof_invmass","ceof_invmass_",60,0,300);

	TH1F   *fosf_invmass 	= new TH1F("fosf_invmass","fosf_invmass_",60,0,300);
	TH1F   *foof_invmass 	= new TH1F("foof_invmass","foof_invmass_",60,0,300);

	TH1F   *ceof_mt2 	= new TH1F("ceof_mt2","ceof_mt2_",70,0,350);
	TH1F   *cesf_mt2 	= new TH1F("cesf_mt2","cesf_mt2_",70,0,350);

	TH1F   *foof_mt2 	= new TH1F("foof_mt2","foof_mt2_",70,0,350);
	TH1F   *fosf_mt2 	= new TH1F("fosf_mt2","fosf_mt2_",70,0,350);

	// 2D histograms

 	TH2F	*btag_jet = new TH2F("btag_jet","btag_jet_",10,0,10,10,0,10);
 	TH2F	*mt2_jet = new TH2F("mt2_jet","mt2_jet_",25,100,125,5,0,5);



//Sumw2()->post_invmass_mc;
//Sumw2->post_invmass_da;
// Loop over events to Analyze
  unsigned int nEventsTotal = 0;
  unsigned int nEventsChain = chain->GetEntries();
  if( nEvents >= 0 ) nEventsChain = nEvents;
  TObjArray *listOfFiles = chain->GetListOfFiles();
  TIter fileIter(listOfFiles);
  TFile *currentFile = 0;

  unsigned int nDuplicates = 0;
  // File Loop
  while ( (currentFile = (TFile*)fileIter.Next()) ) {
    // Get File Content
    TFile *file = new TFile( currentFile->GetTitle() );
    TTree *tree = (TTree*)file->Get("tree");
    if(fast) TTreeCache::SetLearnEntries(10);
    if(fast) tree->SetCacheSize(128*1024*1024);
    // cms2.Init(tree);
    dilep.Init(tree);  
    // Loop over Events in current file
    if( nEventsTotal >= nEventsChain ) continue;
    unsigned int nEventsTree = tree->GetEntriesFast();
    for( unsigned int event = 0; event < nEventsTree; ++event) {
    
      // Get Event Content
      if( nEventsTotal >= nEventsChain ) continue;
      if(fast) tree->LoadTree(event);
      // cms2.GetEntry(event);
      dilep.GetEntry(event);  
      ++nEventsTotal;


	/* 	checking for duplicates as elmu, elel and mumu babies 
		are created separately without checking duplicates	*/
      if(isRealData()){
        DorkyEventIdentifier id = {runNumber(), eventNumber(), lumiBlock()};
        if (is_duplicate(id)){
          continue;
        }
      }
    
      CMS2::progress( nEventsTotal, nEventsChain );

	float 	flavour = abs(lt_id()*ll_id()),
		invmass = (ll_p4()+lt_p4()).M(),  	ll_eta  = abs(ll_p4().eta()), 
							lt_eta  = abs(lt_p4().eta());


	/* Event Clean Up */
	if( trackingProblemVeto()) continue;
	if( tauVeto() )	     	   continue;
	if( isoTrackVeto() )       continue;
	/* Event Clean Up */



	/* Scaling of the MC */
 float scale = 0;
	if(isRealData()){
		scale = 1;
	}else if (!isRealData()){

	/* check the flavour scale up to 19.4   account for the trigger efficiencies */
	if 	(flavour == 169) scale  = 0.88*scale_1fb()*19.4;
	else if (flavour == 143) scale 	= 0.88*scale_1fb()*19.4;
	else if (flavour == 121) scale 	= 0.88*scale_1fb()*19.4;
		}

	/* Scaling of the MC */



 	      /* Do the MetPhi correction */
      float metx = met() * cos( metPhi() );
      float mety = met() * sin( metPhi() );

      float shiftx = 0.;
      float shifty = 0.;

      shiftx = (! isRealData()) ?  (0.1166 + 0.0200*nvtxs()) : (0.2661 + 0.3217*nvtxs());
      shifty = (! isRealData()) ?  (0.2764 - 0.1280*nvtxs()) : (-0.2251 - 0.1747*nvtxs());
      
      metx -= shiftx;
      mety -= shifty;

      float cmet = sqrt( metx*metx + mety*mety );  
      float cmetphi = atan2( mety , metx );
      float metu = cmet;	// use metu 			 
      float metphiu = cmetphi; // use metphiu
		/* end correction */




	
		/* Jet loop */
float jetspt =0;
/*
	int n_bTag =0, n_jets = 0;
bool trkProbVeto = false;

	for(unsigned int c = 0; c < jets_p4().size(); c++) {

	float _jetPt = jets_p4().at(c).pt()* jets_p4Correction().at(c) ;
	
	if(_jetPt <= 40) continue;  
	if(fabs(jets_p4().at(c).eta()) > 3) continue;

	float dr_ll = ROOT::Math::VectorUtil::DeltaR(jets_p4().at(c), ll_p4());
	float dr_lt = ROOT::Math::VectorUtil::DeltaR(jets_p4().at(c), lt_p4());

	if(dr_ll < 0.4) continue;      
	if(dr_lt < 0.4) continue;      
	jetspt += _jetPt;

	n_jets++;
	//n Tagging
	float _bTag = btagDiscriminant().at(c);
      	if ( _bTag > 0.244) n_bTag++ ;

	if (( abs(jets_p4().at(c).eta()) > 0.9 && abs(jets_p4().at(c).Eta()) < 1.9 && (jets_chargedMulti().at(c) - jets_neutralMulti().at(c)) > 40) ) {
	trkProbVeto = true;	       

	}
}
if(trkProbVeto) continue;
*/
		/* Jet loop */

	/*Skip the jet loop since njets() is saved with;
		-pt > 40 GeV, 
		-eta < 3, 
		-L1correction, 
		-trkProbVetoed
	Uncomment the looper to make changes and 
	comment the following line to stop filling n_jets with njets(),
	njets() is filled in the baby, n_jets is filled in the looper */

int n_jets = njets();
int n_btag = nbtag();
float mt2 = MT2(metu,metphiu,ll_p4(),lt_p4());

for(unsigned int i=0;jets_pt().size();i++){
jetspt+=jets_pt().at(i);
cout << jets_pt().at(i) << endl;
}


	/* Check if the triggers are passed*/

	if(isRealData()){
      	if(flavour == 169 && !mu17_mu8()  ) 			continue;
      	if(flavour == 143 && (!mu17_ele8() && !mu8_ele17())) 	continue;
      	if(flavour == 121 && !ele17_ele8() ) 			continue;
	}


	/* 
	checking the mother of the selected lepton	
	2 = from W/Z incorrect charge
	1 = from W/Z   correct charge
	0 = not matched to a lepton (= fake)
	1 = lepton from b decay
	2 = lepton from c decay
	3 = lepton from some other source

	checks for fakes
	*/

	bool isTau = 0;
	if(!isRealData()){
	
	if (ll_isFromW() != 1 && ll_isFromW() !=2) continue;
	if (lt_isFromW() != 1 && lt_isFromW() !=2) continue;

	// check for taus
	for(unsigned int i=0;i<gen_p4().size();i++)
	if(abs(gen_id().at(i)) == 15) isTau = 1 ;
	}

	if (isTau) continue;


	/* define variables for the cuts */

	bool 	jet2_met150 = 0, jet3_met100 = 0,
		central = 0, z_window =0,signal_region=0;

	if (ll_eta <= 1.4  && lt_eta <= 1.4) 		central 	= 1; // only central if both leptons are in the center
	if (abs(invmass - 91) < 15) 			z_window	= 1; // in the z-window
	if (abs(invmass - 45) < 25) 			signal_region	= 1; //  signal region 20-70
	if (n_jets >= 2 && metu >= 150) 		jet2_met150 	= 1; // >=2 jets and met > 150
	if (n_jets >= 3 && metu >= 100)  		jet3_met100 	= 1; // >=3 jets and met > 100

			/* CUTS asdf*/
		//if(n_jets < 2) 		continue;
		//if(metu < 50 ) 	continue;
		//if(invmass < 20 ) 	continue;

	if(invmass < 20 || invmass > 70 ) continue;
	if(!jet2_met150  && !jet3_met100) continue;

			/* CUTS */ 


			/* Histogram Filling*/
btag_jet->Fill(n_btag,n_jets,scale);
 mt2_jet->Fill(mt2,n_jets,scale);

	if(flavour == 143){
		of_invmass->	Fill(invmass	,scale);
		of_njets->	Fill(n_jets	,scale);
		of_nbtag->	Fill(n_btag	,scale);
		of_met->	Fill(metu	,scale);
		of_jetspt->	Fill(jetspt	,scale);		
		of_metphi->	Fill(metphiu	,scale);
		of_mt2->	Fill(mt2	,scale);
	
	if(central){ 	
		ceof_invmass->	Fill(invmass	,scale);
		ceof_mt2->	Fill(mt2	,scale);

	}else if(!central){
		foof_invmass->		Fill(invmass	,scale);
		foof_mt2->		Fill(mt2	,scale);
			}

	}else if (flavour == 121 || flavour == 169){
		sf_invmass->	Fill(invmass	,scale);
		sf_njets->	Fill(n_jets	,scale);
		sf_nbtag->	Fill(n_btag	,scale);
		sf_met->	Fill(metu	,scale);
		sf_jetspt->	Fill(jetspt	,scale);		
		sf_metphi->	Fill(metphiu	,scale);
		sf_mt2->	Fill(mt2	,scale);

	if(central){ 	
		cesf_invmass->	Fill(invmass	,scale);
		cesf_mt2->	Fill(mt2	,scale);
	}else if(!central){
		fosf_invmass->	Fill(invmass	,scale);
		fosf_mt2->	Fill(mt2	,scale);
			}

		} 

			/* Counting */
//SF
if(flavour == 143 &&  central &&  z_window) 	 ce_in_of+=scale;
if(flavour == 143 && !central &&  z_window) 	 fo_in_of+=scale;
if(flavour == 143 &&  central &&  signal_region) ce_out_of+=scale;
if(flavour == 143 && !central &&  signal_region) fo_out_of+=scale;
//OF
if(flavour != 143 &&  central &&  z_window) 	 ce_in_sf+=scale;
if(flavour != 143 && !central &&  z_window) 	 fo_in_sf+=scale;
if(flavour != 143 &&  central &&  signal_region) ce_out_sf+=scale;
if(flavour != 143 && !central &&  signal_region) fo_out_sf+=scale;

    } //loop over events in the current file

    file_count++;

    // Clean Up
    delete tree;
    file->Close();
    delete file;
  } //file loop




    if ( nEventsChain != nEventsTotal ) {
    cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
  }


mt2_jet->Draw("COLZ");
	/* write the histograms to files*/

/*leave date blank to not write the histograms
* still writes the counts
*/
bool write_hist = 1;
char* date = "Mar31";

//char* suffix ="met150_inv20";
//char* suffix ="v4_inv20_ge1j";
//char* suffix ="v4_ge2";
//char* suffix = "dataDrive_DY";
//char* suffix ="v2_met40_jetEta_2_4";
//char* suffix ="v4_signal_inv20";
//char* suffix ="v4_signal_M20-70";
//char* suffix = "b-veto";
//char* suffix = "counting";




//asdf
//char* suffix ="v4_met100_inv20_ge2j";	//
//char* suffix ="v4_met50_inv20_ge2j"; //
//char* suffix ="v4_inv20_ge2j";

//char* suffix ="v4_met100_inv20_ge1j"; //
//char* suffix ="v4_met50_inv20_ge1j"; //
//char* suffix ="v4_inv20_ge1j"; //

char* suffix ="v4_signal_inv20";  //
//char* suffix ="v4_signal_M20-70"; //
if(write_hist){
  TFile* fout = new TFile(Form("/home/users/sanil/dilepton/full_set/%s/%s%s.root",date,sampleType,suffix),"RECREATE");
of_invmass 	->Write();
sf_invmass 	->Write();	

of_met 		->Write();
sf_met 		->Write();		

of_njets 	->Write();
sf_njets 	->Write();	

of_jetspt	->Write();
sf_jetspt	->Write();

of_mt2 		->Write();
sf_mt2 		->Write();	

of_metphi	->Write();
sf_metphi	->Write();

ceof_invmass 	->Write();
cesf_invmass 	->Write();

foof_invmass 	->Write();
fosf_invmass 	->Write();

ceof_mt2	->Write();
cesf_mt2	->Write();

foof_mt2	->Write();
fosf_mt2	->Write();

fout->Close();
}

	/* write the counts to file*/
  ofstream myfile;
  myfile.open(Form("/home/users/sanil/dilepton/full_set/dy_estimate/vetoTau/%s%s_%s.txt",sampleType,suffix,date));
  if(myfile.is_open())
  {
myfile << "Same Flavour: " 	<< ce_in_sf+ce_out_sf+fo_in_sf+fo_out_sf << endl;
myfile << "central: " 		<< ce_in_sf + ce_out_sf << endl;
myfile << "forward: " 	 	<< fo_in_sf + fo_out_sf << endl;
myfile << "in: " 	 	<< ce_in_sf + fo_in_sf << endl;
myfile << "out: " 	 	<< ce_out_sf + fo_out_sf << endl;
myfile << "central in: " 		<< ce_in_sf  << endl;
myfile << "central out: " 		<< ce_out_sf << endl;
myfile << "forward in: " 		<< fo_in_sf << endl;
myfile << "forward out: " 		<< fo_out_sf << endl;
myfile << "______________" << endl; 
myfile << "______________" << endl; 
myfile << "______________" << endl; 
myfile << "Opposite Flavour: " 	<< ce_in_of+ce_out_of+fo_in_of+fo_out_of << endl;
myfile << "central: " 	 	<< ce_in_of + ce_out_of << endl;
myfile << "forward: " 	 	<< fo_in_of + fo_out_of << endl;
myfile << "in: " 	 	<< ce_in_of + fo_in_of << endl;
myfile << "out: " 	 	<< ce_out_of + fo_out_of << endl;
myfile << "central in: " 		<< ce_in_of  << endl;
myfile << "central out: " 		<< ce_out_of << endl;
myfile << "forward in: " 		<< fo_in_of << endl;
myfile << "forward out: " 		<< fo_out_of << endl;
myfile << "______________" << endl; 
myfile << "DY ESTIMATES" << endl; 
myfile << "	Only for MC:" << endl;
myfile << "		R central out/in: " << (ce_out_of + ce_out_sf) / (ce_in_of + ce_in_sf) << endl;
myfile << "		R forward out/in: " << (fo_out_of + fo_out_sf) / (fo_in_of + fo_in_sf) << endl;
myfile << "		R total out/in:   " << (ce_out_of + ce_out_sf + fo_out_of + fo_out_sf) / (ce_in_of + ce_in_sf + fo_in_of + fo_in_sf) << endl;
myfile << "	Only for data:" << endl;
myfile << "		central_in_SF - central_in_OF: " << ce_in_sf-ce_in_of << endl;
myfile << "		forward_in_SF - forward_in_OF: " << fo_in_sf-fo_in_of << endl;
myfile << "		total_in_SF - total_in_OF:    " << ce_in_sf - ce_in_of + fo_in_sf - fo_in_of << endl;




}

  bmark->Stop("benchmark");
  cout << endl;
  cout << nEventsTotal << "Events Processed" << endl;
  cout << "------------------------------" << endl;
  cout << "CPU  Time:   " << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
  cout << "Real Time:   " << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
  cout << endl;
  delete bmark;

  return 0;
 }


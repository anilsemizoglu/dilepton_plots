{
  gSystem->AddIncludePath(Form("-I%s/CORE", gSystem->Getenv("HOME")));
  gSystem->AddIncludePath(Form("-I%s/CORE/MT2", gSystem->Getenv("HOME")));
  gSystem->Load(Form("%s/CORE/libCMS2NtupleMacrosCORE.so", gSystem->Getenv("HOME")));  
  gROOT->ProcessLine(".L DL.cc+");
  gROOT->ProcessLine(".L makePlots.C+");
  //gROOT->ProcessLine(".L makeRcoeff.C+");

  gROOT->ProcessLine(".L /home/users/sanil/CMSSW_5_3_2_patch4_V05-03-23/src/CMS2/NtupleMacros/Tools/goodrun.cc");

  TChain *ch = new TChain("tree"); 
  ch->Add("/home/users/sanil/makebaby/babies/ttbar_v4.root");



  ScanChain(ch, "tt_");

}

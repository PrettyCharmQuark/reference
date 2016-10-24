void world_tree() {
  ifstream in;
  in.open("world_range.dat");
  Float_t x;
  Float_t px;
  Int_t nlines = 0;
  Float_t a = 0;
  Float_t b = 2;
  TFile *f = new TFile("world.root","RECREATE");
  TTree *mytree = new TTree("tree","distrebution");
  mytree->Branch("px",&px,"px/F");
  while (1) {
    in >> x; //从文件中读取一行,分别赋值给x,y,z。
    if (!in.good()) break;
    if (nlines < 5) printf("x=%8f\n",x);
    px = x;
    a=max(a,px);
    b=min(b,px);
    //h1->Fill(px);
    mytree->Fill();//填充TNtuple
    nlines++;
    
  }
  printf("the max number is %f\n",a);
  printf("the min number is %f\n",b );
  printf(" found %d points\n",nlines);

  //TH1F *h1 = new TH1F("h1","x distribution",200,b,a);
  in.close();
  f->Write();
}

void world_hist(){
  //TFile* f = new TFile("world.root");
  //TTree* mytree = (TTree*)f->Get("mytree");
  TChain* chain = new TChain("tree");
  chain->Add("world.root");
  static Float_t px;
  Double_t hx;
  Float_t a = 0;
  Float_t b = 200;
  //TBranch* hx = mytree->GetBranch("px");
  //hx->SetAddress(&px);
  chain->SetBranchAddress("px",&px);
  Long64_t nentries = chain->GetEntries();
  for(Long64_t n =0;n<nentries;n++){
    chain->GetEntry(n);
    hx=px;
    if (n < 5) printf("hx=%8f\n",hx);
    if (a < hx) a=hx;
    if (b > hx) b=hx;
  } 
  TH1F *h1 = new TH1F("h1","The range distribution of the e+",150,b,a);


  for (Long64_t i=0;i<nentries;i++){
    chain->GetEntry(i);
    if (i < 5) printf("hx=%8f\n",hx);
    hx=px;
    h1->Fill(px);
  }
  //f->Write();
  TCanvas *c1 = new TCanvas("c1","hists with different entries",800,600);
  //gPad->SetLogx(1);
  //gPad->SetLogy(1);
  //h1->Draw("E");
  h1->Draw("SAME");
  c1->Print("e+&air_range.eps");
}
void world(){
  world_tree();
  world_hist();
}

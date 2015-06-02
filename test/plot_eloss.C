void plot_eloss()
{
  gStyle -> SetPadTopMargin(0.05);
  gStyle -> SetPadBottomMargin(0.16);
  gStyle -> SetPadLeftMargin(0.18);
  gStyle -> SetPadRightMargin(0.04);
  gStyle -> SetTitleSize(0.06, "x");
  gStyle -> SetTitleSize(0.06, "y");
  gStyle -> SetTitleOffset(1.10, "x");
  gStyle -> SetTitleOffset(1.30, "y");
  gStyle -> SetTitleFont(132, "t");
  gStyle -> SetTitleFont(132, "x");
  gStyle -> SetTitleFont(132, "y");
  gStyle -> SetLabelFont(132, "x");
  gStyle -> SetLabelFont(132, "y");
  gStyle -> SetTitleSize(0.07, "x");
  gStyle -> SetTitleSize(0.07, "y");
  gStyle -> SetLabelSize(0.07, "x");
  gStyle -> SetLabelSize(0.07, "y");
  gStyle -> SetLabelSize(0.07, "z");
  gStyle -> SetLegendFillColor(0);
  gStyle -> SetEndErrorSize(4);

  const Double_t gKE[] = {0.01,  0.011,  0.012, 0.013,  0.014, 0.015,  0.016, 0.017,  0.018,
                          0.02,  0.0225, 0.025, 0.0275, 0.030, 0.0325, 0.035, 0.0375, 0.04,
                          0.045, 0.05,   0.055, 0.06,   0.065, 0.07,   0.08,  0.09,   0.1,
                          0.11,  0.12,   0.13,  0.14,   0.15,  0.16,   0.17,  0.18,   0.2,
                          0.225, 0.25,   0.275, 0.3,    0.325, 0.35,   0.375, 0.4};

  TGraph* graphTRIM = new TGraph();
  graphTRIM -> SetMarkerStyle(20);
  graphTRIM -> SetMarkerSize(0.5);
  graphTRIM -> SetMarkerColor(kBlack);

  TGraph* graph10 = new TGraph();
  graph10 -> SetMarkerStyle(25);
  graph10 -> SetLineColor(kRed);
  graph10 -> SetMarkerColor(kRed);

  TGraph* graph1344 = new TGraph();
  graph1344 -> SetMarkerStyle(4);
  graph1344 -> SetLineColor(kBlue);
  graph1344 -> SetMarkerColor(kBlue);

  Double_t ke, eLoss, dummy;
  Int_t iEntry = 0;

  ifstream fileTRIM("TRIMLISE_proton_dEdx.dat");
  while (fileTRIM >> ke >> eLoss)
    graphTRIM -> SetPoint(iEntry++, ke, eLoss);
  fileTRIM.close();

  iEntry = 0;
  TString line;
  ifstream file10("10mm.dat");
  while(!file10.eof()) {
    line.ReadLine(file10);
    if (line.Contains("-----> Mean dE/dx = ")) {
      ke = gKE[iEntry]*1000.;

      TObjArray *array = line.Tokenize(" ");
      eLoss = ((TObjString *) array -> At(4)) -> String().Atof()*0.1;
      delete array;

      graph10 -> SetPoint(iEntry++, ke, eLoss);
    }
  }
  file10.close();

  iEntry = 0;
  TString line;
  ifstream file1344("1344mm.dat");
  while(!file1344.eof()) {
    line.ReadLine(file1344);
    if (line.Contains("-----> Mean dE/dx = ")) {
      ke = gKE[iEntry]*1000.;

      TObjArray *array = line.Tokenize(" ");
      eLoss = ((TObjString *) array -> At(4)) -> String().Atof()*0.1;
      delete array;

      graph1344 -> SetPoint(iEntry++, ke, eLoss);
    }
  }
  file1344.close();

  TCanvas* cvs = new TCanvas("cvs", "", 800, 600);
  graphTRIM -> Draw("Apl");
  graphTRIM -> GetHistogram() -> GetYaxis() -> SetLimits(0., 0.008);
  graphTRIM -> GetHistogram() -> GetYaxis() -> SetRangeUser(0., 0.008);
  graphTRIM -> GetHistogram() -> GetXaxis() -> SetTitle("KE (MeV)");
  graphTRIM -> GetHistogram() -> GetXaxis() -> CenterTitle();
  graphTRIM -> GetHistogram() -> GetYaxis() -> SetTitle("dE/dx (MeV/mm)");
  graphTRIM -> GetHistogram() -> GetYaxis() -> CenterTitle();
  graph1344 -> Draw("samepl");
  graph10 -> Draw("samepl");

  TLegend *legend = new TLegend(0.4, 0.54, 0.85, 0.78);
  legend -> AddEntry(graphTRIM, "TRIM/LISE++", "pl");
  legend -> AddEntry(graph1344, "TestEm5 - 1344 mm", "pl");
  legend -> AddEntry(graph10, "TestEm5 - 10 mm", "pl");
  legend -> SetBorderSize(0);
  legend -> Draw("same");
}

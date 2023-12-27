void draw()
{
    TString datasetNames[] = {
        "dataset_beardmary.txt",
        "dataset_carydavids.txt",
        "dataset_robertpeele.txt",
        "dataset_masahideharada.txt",
        "dataset_cookkj.txt",
    };

    auto win = LKWindowManager::GetWindowManager();

    //auto cvs = LKWindowManager::GetWindowManager() -> Canvas("cvs");
    //auto cvs = win -> CanvasResize("cvs_upscattering_12C_totx","",800,400);
    //auto cvs = win -> CanvasRatio("cvs_upscattering_12C_totx","",0.5,0.7);
    auto cvs = win -> Canvas("cvs_upscattering_12C_totx");//,1,0.5,0.6);
    cvs -> SetMargin(0.12,0.05,0.14,0.05);

    auto hist = new TH2D("hist",";E_{lab} (MeV);Cross Section (mb);",100,7,27,100,0,95);
    hist -> GetXaxis() -> SetTitleSize(0.055);
    hist -> GetYaxis() -> SetTitleSize(0.055);
    hist -> GetXaxis() -> SetLabelSize(0.045);
    hist -> GetYaxis() -> SetLabelSize(0.045);
    hist -> GetXaxis() -> SetTitleOffset(1.2);
    hist -> SetStats(0);
    hist -> Draw();

    auto legend = new TLegend();
    int countDataset = 0;
    double x, y;
    for (auto datasetName : datasetNames)
    {
        ifstream file(datasetName);
        auto graph = new TGraph();
        while (file >> x >> y)
            graph -> SetPoint(graph->GetN(),x,y);
        graph -> SetMarkerColor(countDataset+1);
        graph -> SetLineColor(countDataset+1);
        graph -> SetMarkerStyle(20+countDataset);
        if (countDataset==0) {
            graph -> Draw("samel");
            graph -> SetLineColor(kOrange-2);
            graph -> SetLineWidth(4);
            //legend -> AddEntry(graph,"B. Mary","l");
            legend -> AddEntry(graph,"Ref. [7]","l");
        }
        else if (countDataset==1) {
            graph -> SetMarkerColor(kBlack);
            graph -> SetMarkerStyle(20);
            graph -> SetMarkerSize(2.0);
            graph -> SetLineColor(kGray);
            graph -> Draw("samepc");
            //legend -> AddEntry(graph,"C. N. David","pl");
            legend -> AddEntry(graph,"Ref. [3]","pl");
        }
        else if (countDataset==4) {
            graph -> SetMarkerColor(kRed);
            graph -> SetMarkerStyle(25);
            graph -> SetMarkerSize(2.0);
            graph -> SetLineColor(kRed);
            graph -> Draw("samepc");
            //legend -> AddEntry(graph,"K. J. Cook","pl");
            legend -> AddEntry(graph,"Ref. [6]","pl");
        }
        else {
            graph -> SetMarkerSize(2.4);
            if (countDataset==3) {
                graph -> SetMarkerStyle(22);
                graph -> SetMarkerColor(8);
                //legend -> AddEntry(graph,"M. Harada","pc");
                legend -> AddEntry(graph,"Ref. [5]","p");
            }
            if (countDataset==2) {
                graph -> SetMarkerStyle(23);
                graph -> SetMarkerColor(9);
                //legend -> AddEntry(graph,"R. Peele","pc");
                legend -> AddEntry(graph,"Ref. [4]","p");
            }
            graph -> Draw("samep");
        }
        ++countDataset;
    }

    auto xIF1 = cvs->GetUxmin() + cvs->GetLeftMargin();
    auto xIF2 = cvs->GetUxmax() - cvs->GetRightMargin();
    auto yIF1 = cvs->GetUymin() + cvs->GetBottomMargin();
    auto yIF2 = cvs->GetUymax() - cvs->GetTopMargin();
    auto dx = xIF2 - xIF1;
    auto dy = yIF2 - yIF1;
    auto x1 = xIF1 + 0.6*dx;
    auto x2 = xIF2 - 0.01;
    auto y1 = yIF1 + 0.5*dy;
    auto y2 = yIF2 - 0.01;
    legend -> SetX1(x1);
    legend -> SetX2(x2);
    legend -> SetY1(y1);
    legend -> SetY2(y2);
    legend -> SetBorderSize(0);
    //legend -> SetTextFont(132);
    legend -> SetTextSize(0.050);
    legend -> SetMargin(0.3);
    legend -> Draw();

    cvs -> SaveAs("figures/cvs_upscattering_12C_totx.png");
    cvs -> SaveAs("figures/cvs_upscattering_12C_totx.pdf");
}

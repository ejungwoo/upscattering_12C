void draw()
{
    TString datasetNames[] = {
        "dataset_carydavids.txt",
        "dataset_beardmary.txt",
        "dataset_masahideharada.txt",
        "dataset_robertpeele.txt",
    };

    auto hist = new TH2D("hist","",100,5,35,100,0,100);
    hist -> Draw();

    int countDataset = 0;
    double x, y;
    for (auto datasetName : datasetNames)
    {
        ifstream file(datasetName);
        auto graph = new TGraph();
        while (file >> x >> y)
            graph -> SetPoint(graph->GetN(),x,y);
        graph -> SetMarkerColor(countDataset+1);
        graph -> SetMarkerSize(0.5);
        graph -> SetMarkerStyle(20+countDataset);
        graph -> Draw("samepl");
        ++countDataset;
    }
}

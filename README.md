# Machine Learning (ML) examples
This directory is for ML examples for typical ATLAS physicists tasks, which could be used in various (self) tutoring opportunities.
Tutorials solve the issue of transferring Python / ROOT code and data between environments:
+ laptop
+ Jupyter
+ SWAN
+ Lxplus  

Tutorials was based the ATLAS Higgs Machine Learning Challenge where was to use the simulated data characterizing the events found in the Atlas to classify the events in the tau-tau as the decay of the Higgs boson as compared to the background. The classical method (TMVA/BDT) was also used on the example of data on the Higgs decay in two muons.
## Installation instructions
Download the tutorials:  

    git clone https://:@gitlab.cern.ch:8443/atlasml/Tutorials_ML.git  
    cd Tutorials_ML/higgsml_opendata/  
 
Download the 63 MB dataset: 

    curl -o atlas-higgs-challenge-2014-v2.csv.gz  
    http://opendata.cern.ch/record/328/files/atlas-higgs-challenge-2014-v2.csv.gz  
    gunzip atlas-higgs-challenge-2014-v2.csv.gz 
    
Detailed instructions on each approach are in sub-directories.

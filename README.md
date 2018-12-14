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
    
# XGBoost and AdaBoost Tutorials
Using the example of the decay H → τ τ, demonstrated the potential of the latest machine learning methods to improve the significance of the discoveries of the Higgs decays. The original example can be found [here](https://github.com/ATLAS-outreach/HiggsML2014/blob/master/scripts/higgsml_opendata_tmva.py). I used the scikit-learn XGBoost library instead of the ROOT TMVA. 

## Install scikit-learn
Scikit-learn requires:
Python >= 2.7 or >= 3.4, cython with a version >= 0.23

    git clone git://github.com/scikit-learn/scikit-learn.git
    cd scikit-learn
    sudo pip install cython
    sudo pip install --editable .
    
More information installing scikit-learn for all supported platform [here](https://scikit-learn.org/stable/install.html).
## Install XGBoost

    sudo pip install xgboost
    sudo pip install xgboost --upgrade
    
An alternate way to install XGBoost if you cannot use pip or you want to run the latest  code from GitHub requires that you make a clone of the XGBoost project and perform a manual build and installation. 
## Execute the XGBoost example
    cd Tutorials_ML/XGBoostTutorial
    vi higgsml_opendata_xgboost.py
Change this path to your directory where your dataset is located.

    python higgsml_opendata_xgboost.py
Expected output: Accuracy: 82.41%
## Conclusion:
 * Prediction accuracy increased.
 * The libraries and methods used in source algorithm (TMVA/BDT) are not supported in the Jupyter environment. Scikit-learn with XGBoost library will do it. 
## Execute the AdaBoost example
    cd Tutorials_ML/AdaBoostTutorial
    vi higgsml_opendata_AdaBoost.py
Change this path to your directory where your dataset is located.

    python higgsml_opendata_AdaBoost.py
Expected output: 

|               | precision          | recall | f1-score | support |
| ------------- |:------------------:| ------:| --------:| -------:|
| background    |       0.83         |   0.88 |   0.85   | 65975   |
|      signal   |       0.73         |   0.64 |   0.68   | 34025   |
| avg / total   |       0.79         |   0.80 |   0.79   | 100000  |

# Implement ML tutorials as Jupyter notebook 
## (higgsml_opendata_simplest.py.ipynb and higgsml_opendata_tmva.ipynb) 

To implement the tasks of ML in different environments, it was decided to use a container docker, which in turn is easy to use and settings.
 1. Install Docker [here](https://www.docker.com/community-edition) 
 2. Configure the container assigned by the docker
 3. Run Docker from the Web Server 
 4. Jupiter notebooks
 ![Screen](https://gitlab.cern.ch/okuchins/Tutorials_ML/blob/master/HiggsML_opendata_Jupyter/images/Screen.png)

Higgsml_opendata_simplest.py re-implemented as a Jupyter notebook. Next, change the threshold = -22 (a somewhat arbitrary value, it should be optimized) and modify the Jupyter notepad to count each label present in the data set. Sourse code [here](https://github.com/ATLAS-outreach/HiggsML2014/blob/master/scripts/higgsml_opendata_simplest.py). 
 
 Expected output (including optimized threshold): 
 1. Loop again to determine the AMS, using threshold: -22
 AMS with recomputed weight: 1.54450974336 (signal=461.228096209 bkg=89012.844986)  
 AMS with kaggle weight : 1.54450974337 (signal=461.228096209 bkg=89012.844986)
 2. Loop again to determine the AMS, using threshold: -30
 AMS with recomputed weight: 1.58480303364 (signal= 558.35671681 bkg=123932.919195)
 AMS with kaggle weight : 1.58480303364 (signal=558.35671681 bkg=123932.919195)  
 Conclusion: AMS increases by ~ 0.04 compared to the initial value, with a slight increase in the amount of signal and large background (1 order higher); script condition - recalculated weight and kaggle weight must be the same not satisfied.
 3. Loop again to determine the AMS, using threshold: -14
 AMS with recomputed weight: 1.34888303313 (signal=318.667627142 bkg=55695.8429448)
 AMS with kaggle weight : 1.34888303313 (signal= 318.667627142 bkg=55695.8429448)  
 Conclusion: AMS decreased; the value of the signal and background decreased.

Higgsml_opendata_TMVA.py is more complex and the libraries and methods used in this algorithm are not supported in the Jupyter environment. To implement the algorithm, we will replace TMVA with the Scikit-learn/AdaBoost and Scikit-learn/XgBoost algorithms (Algorithms are presented in the root of the folder). 

# TMVA Tutorial 

In the framework of scientific efforts to study the properties of the Higgs sector that began after its discovery in 2012, the discovery and accurate measurement of the decays of the Higgs boson into fermions is one of the main scientific priorities for the next few years of data collection at the LHC.
We decided to repeat the results of the [Decay Analysis Group](https://cds.cern.ch/record/2210393/files/ATL-COM-PHYS-2016-1194.pdf?)

## Installation

Install Root [here](https://root.cern.ch/downloading-root)

Install TMVA [here](http://tmva.sourceforge.net) 

## Execute the Hmumu example

    cd Tutorials_ML/higgsml_hmumu
    vi TMVAClassification.C

Change this path to your directory where your dataset is located.

    root TMVAClassification.C

The TMVA algorithm runs for a very long time. Therefore all actions aimed at improving the efficiency of this algorithm and the normalization parameters, I rendered in a separate script - tmva_draw0207c. This allows you not to make train the tree every time. As a result you will get TMVA.root. Write the path of this file in tmva_draw0207.c. 

    root tmva_draw0207.c








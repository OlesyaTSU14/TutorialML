"""
ATLAS Higgs Machine Learning Challenge 2014

#The algorithms higgsml_opendata_tmva.py was changed and adapted to work on a laptop using a package scikit-learn.
"""
#matplotlib inline
from array import array
import numpy as np

from numpy import loadtxt
from xgboost import XGBClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

import csv
import copy
#with open('/Users/okuchins/Olesya_work/HigsML2014/S_learn/atlas-higgs-challenge-2014-v2.csv','rb') as f:
#    reader = csv.reader(f)
#    your_list = map(tuple, reader)

#alldata = list(csv.reader(open('/Users/okuchins/Olesya_work/HigsML2014/S_learn/atlas-higgs-challenge-2014-v2.csv',"rb"), delimiter=','))
#list = map(tuple, reader)

#dataset
datafile="/Users/okuchins/Olesya_work/HigsML2014/S_learn/atlas-higgs-challenge-2014-v2.csv"
# load the CSV file as a numpy matrix
alldata = list(csv.reader(open(datafile,"rb"), delimiter=','))

# first line is the list of variables, put it aside
header        = alldata.pop(0)

# deal with some exception
iid=header.index("EventId")
ilabel=header.index("Label")
ikaggleset=header.index("KaggleSet")
ikaggleweight=header.index("KaggleWeight")
iweight=header.index("Weight") # original weight     
immc=header.index("DER_mass_MMC")
injet=header.index("PRI_jet_num")
exclude_index = [iid, ilabel, ikaggleset, ikaggleweight, iweight, immc, injet]
print ilabel

for entry in alldata:
    for i in range(len(entry)):
        if i in [iid,injet]:
            entry[i]=int(entry[i])
        elif i not in [ilabel,ikaggleset]:
            entry[i]=float(entry[i])

data_train = []
data_test = []

sumselsig=0.
sumselbkg=0.
sumallsig=0.
sumallbkg=0.
sumsubsig=0.
sumsubbkg=0.
t=0
b=0
v=0
u=0

sumselkagglesig=0.
sumselkagglebkg=0.

for entry in alldata:
   
    weight=entry[iweight]
    kaggleweight=entry[ikaggleweight]    

    if entry[ilabel]=="s":
        sumallsig+=weight
    else:
        sumallbkg+=weight    

    if entry[ikaggleset]=="t":
        t+=1 
        data_train.append(entry)
    if entry[ikaggleset]=="b":
        b+=1
        data_test.append(entry)
    if entry[ikaggleset]=="v":
        v+=1
    if entry[ikaggleset]=="u":
        u+=1      

    if entry[ikaggleset]!="b":
        continue

    if entry[ilabel]=="s":
        sumsubsig+=weight
    else:
        sumsubbkg+=weight  


print 'Number of train is %i' % (t)  
print data_train[0:2]
print 'Number of test is %i' % (b)
print data_test[0:2]    


x_train = []
x_test = []
y_train = []
y_test = []

for row in data_train:
    newrow = copy.deepcopy(row)
    for el in sorted(exclude_index, reverse=True):
        del newrow[el]
    x_train.append(newrow)
    y_train.append(row[ilabel])

for row in data_test:
    newrow = copy.deepcopy(row)
    for el in sorted(exclude_index, reverse=True):
        del newrow[el]
    x_test.append(newrow)
    y_test.append(row[ilabel]) 

print 'Length of X train is %i' % (len(x_train))  
print x_train[0:1]
print 'Length of Y train is %i' % (len(y_train))  
print y_train[0:1]
print 'Length of X test is %i' % (len(x_test))
print x_test[0:1]  
print 'Length of Y test is %i' % (len(y_test))
print y_test[0:1]     


# fit model no training data
x_train = np.array(x_train)
x_train =np.array(x_train)

model = XGBClassifier()
model.fit(x_train, y_train)

print(model)


# make predictions for test data
y_pred = model.predict(x_test)

#print (value)
predictions = y_pred

# evaluate predictions
accuracy = accuracy_score(y_test, predictions)
print("Accuracy: %.2f%%" % (accuracy * 100.0))



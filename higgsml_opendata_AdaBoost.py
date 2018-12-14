"""
ATLAS Higgs Machine Learning Challenge 2014

#The algorithms higgsml_opendata_tmva.py was changed and adapted to work on a laptop using a package scikit-learn.
"""
#matplotlib inline
from array import array
import numpy as np
#import matplotlib.pyplot as plt
from sklearn import datasets
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier
from sklearn.metrics import classification_report, roc_auc_score
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

#alldata.head()

    
    # sum event weight passing the selection. Of course in real life the threshold should be optimised

#newlist=[] 
#signal = []
#for row in your_list[1:]:
    #if int(row[32]) == 0 && int(row[33]) == 0:
     #   backgr.append(int(row[23]))
    #else:
    #    signal.append(int(row[23]))

#print len(sinal)
#signal_tr = signal[:len(signal)*0.7]
#signal_ts = signal[len(signal)*0.7:]

    #newlist.append({'EventId':row[0],'Weight':row[31],'Label':row[32],'KaggleSet':row[33],'KaggleWeight':row[34],'Pri_jet_num':row[23]})

# where DecisionTrees, DecisionStumps and AdaBoost are
# compared to each other
#X, y = datasets.make_hastie_10_2(n_samples=12000, random_state=1)

# Train on the first 2000, test on the rest



#t_train, b_train = t[:2000], b[:2000]
#t_test, b_test = t[2000:], b[2000:]


# some shortcuts to select "signal" or "background"
# entries in the feautre vector
#signal = y_train > +0.1
#background = y_train < -0.1

#plt.scatter(X_train[signal,0], X_train[signal,1], c='red')
#plt.scatter(X_train[background,0], X_train[background,1], c='blue')
#plt.xlabel("Feature 0")
#plt.ylabel("Feature 1")

dt = DecisionTreeClassifier(max_depth=3,
                            min_samples_leaf=0.01*len(x_train[0]))
bdt = AdaBoostClassifier(dt,
                         algorithm='SAMME',
                         n_estimators=800,
                         learning_rate=0.5)

bdt.fit(x_train, y_train)
sk_y_predicted = bdt.predict(x_test)
print classification_report(y_test, sk_y_predicted, target_names=["background", "signal"])
print "Area under ROC curve: %.4f"%(roc_auc_score(y_test, sk_y_predicted))

plt.hist(bdt.decision_function(x_train[y_train>0.]).ravel(),
         color='r', alpha=0.5, range=(-0.4,0.4), bins=20)
plt.hist(bdt.decision_function(x_train[y_train<0.]).ravel(),
         color='b', alpha=0.5, range=(-0.4,0.4), bins=20)

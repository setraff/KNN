import numpy as np
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

#creates 2D array of plots for KMeans.fit()
def convertToX(arrX, arrY):
    larrX = len(arrX)
    rArr = []
    for row in range(larrX):
        rArr.append([arrX[row], arrY[row]])
    return rArr
    
def cluster_and_visualise(datafilename, K, featurenames): 
    #create 2D array of data from the file
    rawData = np.genfromtxt(datafilename, delimiter=",")
    
    #making sure it doesnt iterate through the characters if there is only one feature
    if (len(featurenames[0]) == 1):
        featurenames = ([featurenames])

    #initialise global varibles
    l = len(featurenames)
    area = l * l
    #index of subplot, to be incremeted area times
    spIndex = 1

    #initialise figure
    fig = plt.subplots(l, l, figsize=(24, 24))
    
    #create array of rows and reverse it
    rRow = []
    for i in range(l):
        rRow.append(i)
    rRow.reverse()

    #draw on the canvas
    while spIndex <= area:
        for yRow in rRow:
            for xCol in range(l):
                if (yRow == xCol):
                    plt.subplot(l, l, spIndex)
                    plt.hist(x=rawData[:,yRow])
                    plt.xlabel(featurenames[yRow], fontsize= 'xx-large', fontweight='bold')
                    spIndex += 1
                else:
                    plt.subplot(l, l, spIndex)
                    xLabel = featurenames[xCol]
                    yLabel = featurenames[yRow]
                    plt.xlabel(xLabel, fontsize= 'xx-large', fontweight='bold')
                    plt.ylabel(yLabel, fontsize= 'xx-large', fontweight='bold')
                    yVals = rawData[:,yRow]
                    xVals = rawData[:,xCol]
                    X = convertToX(xVals, yVals)
                    kmeaned = KMeans(n_clusters=K, init="k-means++")
                    kmeaned.fit(X)
                    labels = kmeaned.labels_
                    plt.scatter(x=xVals, y=yVals, c=labels, s=5400/area)
                    spIndex += 1

    #save as jpg and return fig, axs
    axs = plt.axes
    plt.suptitle('Data Visualisation by Rafhaan Ahmed Fayaz\n' + 'n_clusters: ' + str(K) + '\n', fontsize = 30)
    plt.tight_layout()
    plt.savefig('myVisualisation.jpg')
    return fig, axs
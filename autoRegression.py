# -*- coding: utf-8 -*-
"""
Created on Sat Dec 12 21:33:40 2015

@author: mrins
"""
import numpy as np
from math import floor
from fileOps import readCritterbotData
from fileOps import readFilteredCritterbotData
from fileOps import writeMatrixToCSVFile
from fileOps import writeVectorToCSVFile


def stochasticAutoRegression(X, span, totTime, signal, featureDimension):

    Original = np.zeros(totTime-1)
    Predicted = np.zeros(totTime-1)
    RMSError = np.zeros(totTime-1)    
    
    weights = np.zeros(span * featureDimension)
    streamingSumofDifferences = 0

    for timeIndex in range(span, totTime-1):
        stepSize = 1.0 / pow(timeIndex+1, 0.5)
        Xhist = X[timeIndex-span:timeIndex,:]
        Xhist = Xhist.reshape(1, span * featureDimension).transpose().flatten()
        originalTargetValue = X[timeIndex][signal]
        weights = weights - stepSize * ((Xhist.dot(weights) - originalTargetValue) * Xhist)
        weights = weights / np.linalg.norm(weights) #Divide by L2 norm
        
        predictedTargetValue = Xhist.transpose().dot(weights)
        Original[timeIndex] = originalTargetValue
        Predicted[timeIndex] = predictedTargetValue
        print(timeIndex,": <",originalTargetValue,",",predictedTargetValue,">")
        streamingSumofDifferences += pow((predictedTargetValue-originalTargetValue), 2)
        RMSError[timeIndex] = pow(streamingSumofDifferences/(timeIndex+1), 0.5)
        
    writeMatrixToCSVFile(Original, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/Original_SGDonlineAR.csv", "Original")
    writeMatrixToCSVFile(Predicted, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/Predicted_SGDonlineAR.csv", "Predicted")        
    writeVectorToCSVFile(RMSError, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/RMSError_SGDonlineAR.csv", "RMSError")    


def normalizeFeatureValuesOfMatrixAsWhole(X):
    Xrows = len(X)
    Xcols = len(X[0])
    minimum = X.min()
    maximum = X.max()
    for i in range(0, Xrows):
        for j in range(0, Xcols):
            X[i][j] = X[i][j] / (maximum - minimum)
    return X
    
def normalizeFeatureValuesOfMatrixColumnWise(X):
    Xrows = len(X)
    Xcols = len(X[0])
    for j in range(0, Xcols):
        col = X[:,[j]]
        minimum = col.min()
        maximum = col.max()
        if maximum != minimum:
            for i in range(0, Xrows):
                X[i][j] = (X[i][j] - minimum) * 1.0 / (maximum - minimum)
                # Debug Code
                if  X[i][j] > 1:
                    print(col)
                    print(X[i][j], maximum, minimum)
                    return None
    return X
    
    
def verifyNormalization(X):
    Xrows = len(X)
    Xcols = len(X[0])
    for i in range(0, Xrows):
        for j in range(0, Xcols):
            if X[i][j] > 1:
                print(i, j, X[i][j])
                return False
    return True
    
def testScaleFeatureValuesOfMatrixColumnWise():
    X = np.arange(9.0).reshape((3,3))
    print(X)
    X = normalizeFeatureValuesOfMatrixColumnWise(X)
    print(X)
    
def discountedPredictedReturn(X, startIndex, totTime, signal, discount):
    discountedSum = 0
    threshold = 0.00001    
    for timeIndex in range(startIndex, totTime):
        oldDiscountedSum = discountedSum
        discountedSum += (pow(discount, (timeIndex-startIndex+1)) * X[timeIndex][signal])
        if (abs(discountedSum - oldDiscountedSum) < threshold):
            break
    return discountedSum
    
######Version 1##########    
### This is an online version of Stochastic Gradient Descent ####
#def stochasticTemporalDifference(X, featureDimension, totTime, signal, discount, traceDecay):
#    
#    Original = np.zeros(totTime-1)
#    Predicted = np.zeros(totTime-1)
#    RMSError = np.zeros(totTime-1)
#        
#    weights = np.zeros(featureDimension)
#    eligibilityTraces = np.zeros(featureDimension)
#    streamingSumofDifferences = 0
#    
#    
#    for timeIndex in range(0, totTime-1):
#        stepSize = 0.1
#        xCur = X[timeIndex]
#        xNext = X[timeIndex+1]
#        delta = xNext[signal]
#        delta = delta + discount * xNext.dot(weights)
#        delta = delta - xCur.dot(weights)
#        eligibilityTraces = traceDecay * discount * eligibilityTraces + xCur
#        weights = weights + stepSize * delta * eligibilityTraces
#        weights = weights / np.linalg.norm(weights) #Divide by L2 norm
#
#
#        originalTargetValue = xNext[signal] 
#        predictedTargetValue = xNext.dot(weights)
#        Original[timeIndex] = originalTargetValue
#        Predicted[timeIndex] = predictedTargetValue
#        print(timeIndex,": <",originalTargetValue,",",predictedTargetValue,">")
#        streamingSumofDifferences += pow((predictedTargetValue-originalTargetValue), 2)
#        RMSError[timeIndex] = pow(streamingSumofDifferences/(timeIndex+1), 0.5)
#    
#    writeMatrixToCSVFile(Original, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/Original_SGDonlineTD_ver1.csv", "Original")
#    writeMatrixToCSVFile(Predicted, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/Predicted_SGDonlineTD_ver1.csv", "Predicted")    
#    writeVectorToCSVFile(RMSError, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/RMSError_SGDonlineTD_ver1.csv", "RMSError")    
#


#####Version 2##########
# Difference with prev version is we are calculating original Target value as dicounted
# sum of future values and step size inversely varies with time index  
def stochasticTemporalDifference(X, featureDimension, totTime, signal, discount, traceDecay):
    
    Original = np.zeros(totTime-1)
    Predicted = np.zeros(totTime-1)
    RMSError = np.zeros(totTime-1)
        
    weights = np.zeros(featureDimension)
    eligibilityTraces = np.zeros(featureDimension)
    streamingSumofDifferences = 0
    
    
    for timeIndex in range(0, totTime-1):
        stepSize = 1.0 / pow(timeIndex+1, 0.5)
        xCur = X[timeIndex]
        xNext = X[timeIndex+1]
        delta = xNext[signal]
        delta = delta + discount * xNext.dot(weights)
        delta = delta - xCur.dot(weights)
        eligibilityTraces = traceDecay * discount * eligibilityTraces + xCur
        weights = weights + stepSize * delta * eligibilityTraces
        weights = weights / np.linalg.norm(weights) #Divide by L2 norm. If we do not normalize weights, its overshooting


        originalTargetValue = discountedPredictedReturn(X, timeIndex, totTime, signal, discount) 
        predictedTargetValue = xNext.dot(weights)
        Original[timeIndex] = originalTargetValue
        Predicted[timeIndex] = predictedTargetValue
        print(timeIndex,": <",originalTargetValue,",",predictedTargetValue,">")
        streamingSumofDifferences += pow((predictedTargetValue-originalTargetValue), 2)
        RMSError[timeIndex] = pow(streamingSumofDifferences/(timeIndex+1), 0.5)

    writeMatrixToCSVFile(Original, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/Original_SGDonlineTD_ver2.csv", "Original")
    writeMatrixToCSVFile(Predicted, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/Predicted_SGDonlineTD_ver2.csv", "Predicted")        
    writeVectorToCSVFile(RMSError, "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/RMSError_SGDonlineTD_ver2.csv", "RMSError")    
            

def testStochasticAutoRegressionOnCritterbotData():
    
    ### Reading Data. Uncomment only one
    #X = readCritterbotData()
    X = readFilteredCritterbotData()
    Xrows = len(X)
    Xcols = len(X[0])
    
    ### Scaling the data. Uncomment only one
    #X = normalizeFeatureValuesOfMatrixAsWhole(X)
    X = normalizeFeatureValuesOfMatrixColumnWise(X)
    if verifyNormalization(X) is False:
        return
    
    
    #np.savetxt("/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/CritterBotFilteredScaled", X, delimiter=' ', fmt='%.5e')
    print("XShape", X.shape)
    
    ### Algorithm to run. Uncomment only one
    stochasticAutoRegression(X, 30, Xrows, 27, Xcols)

        
def main():
    testStochasticAutoRegressionOnCritterbotData()

if __name__ == '__main__':
    main()
        
        
# -*- coding: utf-8 -*-
"""
Created on Sat Dec 12 22:13:05 2015

@author: mrins
"""
import csv
import numpy as np


def writeMatrixToCSVFile(X, outputFileName, header = None):
    np.savetxt(outputFileName, X, delimiter=',', header = header)
    

def writeVectorToCSVFile(V, outputFileName, header = None):
    np.savetxt(outputFileName, V, header=header)
    

def readCritterbotData():   
    inputFileName = "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/CritterBot"
    X = np.genfromtxt(inputFileName, dtype = float, delimiter = ' ', skip_header = 1)
    redundantAttributesIndices = findCritterbotDataredundantAttrIndices(inputFileName)
    Xfiltered = filterCritterbotData(X, redundantAttributesIndices)
    return Xfiltered
    
    

def readFilteredCritterbotData():
    inputFileName = "/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/CritterBotFiltered"
    X = np.genfromtxt(inputFileName, dtype = float, delimiter = ' ')
    return X



def findCritterbotDataredundantAttrIndices(inputFileName): 
    redundantAttributesName = ["unixTime", "Bump0", "Bump1", "Bump2", "Bump3", "Bump4", "Bump5", "Bump6", "Bump7", "Bump8", "Bump9", "Bump10", "Bump11", "Bump12", "Bump13", "Bump14", "Bump15", "Bump16", "Bump17", "Bump18", "Bump19", "Bump20", "Bump21", "Bump22", "Bump23", "Bump24", "Bump25", "Bump26", "Bump27", "Bump28", "Bump29", "Bump30", "Bump31"];
    redundantAttributesIndices = np.zeros(len(redundantAttributesName))    
    with open(inputFileName, 'r') as inputFile:
        attributeNames = inputFile.readline().split()
        redundantAttributesIndex = 0
        for index in range(0, len(attributeNames)):
            if attributeNames[index] in redundantAttributesName:
                redundantAttributesIndices[redundantAttributesIndex] = index
                redundantAttributesIndex = redundantAttributesIndex + 1
    return redundantAttributesIndices



def filterCritterbotData(X, redundantAttributesIndices):
    Xrows = len(X)
    Xcols = len(X[0])
    Xmod = np.zeros(Xrows*(Xcols-len(redundantAttributesIndices)))
    Xmod = Xmod.reshape(Xrows, (Xcols-len(redundantAttributesIndices)))
    for i in range(0, Xrows):
        Xmod_j = 0
        for j in range(0, Xcols):
            if j not in redundantAttributesIndices:
                Xmod[i][Xmod_j] = X[i][j]
                Xmod_j = Xmod_j + 1
    np.savetxt("/Users/mrins/Documents/Python Projects/Time Series Analysis/Data/CritterBotFiltered", Xmod, delimiter=' ', fmt='%.5e')
    return Xmod                
            
def testreadCritterbotData(): 
    readCritterbotData()


def main():
    testreadCritterbotData()


if __name__ == '__main__':
    main()
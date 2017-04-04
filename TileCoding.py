# -*- coding: utf-8 -*-
"""
Created on Thu Jan 28 17:56:47 2016

@author: mrins
"Based on: https://webdocs.cs.ualberta.ca/~sutton/tiles2.html"

"""

import numpy as np
import random

# Input V contains the input vector
# numOfTiles represents number of features
# Output: A 2 dimensional matrix with each rows representing a single instance.
def OneDimensionalTileCoding(V, numOfTiles):
    
    TileCodedFeatureVector = np.zeros((len(V),numOfTiles))
    minVal = np.amin(V) * (1-0.01)
    maxVal = np.amax(V) * (1+0.01)
    intervalWidth = 1.0 * (maxVal-minVal) / numOfTiles
    
#    for i in range(numOfTiles+1):
#        val = minVal + i*intervalWidth
#        print(val)
    
    for valueIndex in range(len(V)):
        tile = np.floor(1.0 * (V[valueIndex] - minVal) / intervalWidth)
        #print(valueIndex, V[valueIndex], tile)
        TileCodedFeatureVector[valueIndex, tile] = 1
    
    #Each value of V represents a row in TileCodedFeatureVector
    #print(TileCodedFeatureVector)
    return TileCodedFeatureVector
    
    
def testOneDimensionalTileCoding():
    V = np.arange(2.1, 16, 0.22)
    print(V)
    OneDimensionalTileCoding(V, 14)
    
# Two features V1 and V2 with corresponding values.
# numOfTiles represents numOfFeatures in a row. So we have numOfFeatures X numOfFeatures 
#    square matrices for generated features
# Output: A 3 dimensional matrix with each primary rows representing a single instance.
def TwoDimensionalTileCodingWithoutOverlaps(V1, V2, numOfTiles):
    if len(V1) != len(V2):
        return
    length = len(V1)
    TileCodedFeatureMatrix = np.zeros((length*numOfTiles*numOfTiles)).reshape(len(V1),numOfTiles,numOfTiles)
    minValV1 = np.amin(V1) * (1-0.01)
    maxValV1 = np.amax(V1) * (1+0.01) 
    minValV2 = np.amin(V2) * (1-0.01)
    maxValV2 = np.amax(V2) * (1+0.01)
    intervalWidthV1 = 1.0 * (maxValV1-minValV1) / numOfTiles
    intervalWidthV2 = 1.0 * (maxValV2-minValV2) / numOfTiles
    
    for valueIndex in range(length):
        rowTileIndex = np.floor(1.0 * (V1[valueIndex] - minValV1) / intervalWidthV1)
        colTileIndex = np.floor(1.0 * (V2[valueIndex] - minValV2) / intervalWidthV2)
        #print(valueIndex, V1[valueIndex], rowTileIndex, V2[valueIndex], colTileIndex)
        TileCodedFeatureMatrix[valueIndex, rowTileIndex, colTileIndex] = 1
        
    #print(TileCodedFeatureMatrix)
    return TileCodedFeatureMatrix
    

def testTwoDimensionalTileCodingWithoutOverlaps():
    V1 = np.arange(1, 16, 0.5)
    random.shuffle(V1)
    V2 = np.arange(3, 18, 0.5)
    random.shuffle(V2)
    print(V1)
    print(V2)
    TwoDimensionalTileCodingWithoutOverlaps(V1, V2, 4)
    
    
def TwoDimensionalTileCodingWithMultipleOverlaps(V1, V2, numOfTiles):
    if len(V1) != len(V2):
        return
    length = len(V1)
    TileCodedFeatureMatrix = np.zeros((length*numOfTiles*numOfTiles)).reshape(len(V1),numOfTiles,numOfTiles)
    minValV1 = np.amin(V1) * (1-0.01)
    maxValV1 = np.amax(V1) * (1+0.01) 
    minValV2 = np.amin(V2) * (1-0.01)
    maxValV2 = np.amax(V2) * (1+0.01)
    intervalWidthV1 = 1.0 * (maxValV1-minValV1) / numOfTiles
    intervalWidthV2 = 1.0 * (maxValV2-minValV2) / numOfTiles
    
    for valueIndex in range(length):
        rowTileIndex = np.floor(1.0 * (V1[valueIndex] - minValV1) / intervalWidthV1)
        colTileIndex = np.floor(1.0 * (V2[valueIndex] - minValV2) / intervalWidthV2)
        #print(valueIndex, V1[valueIndex], rowTileIndex, V2[valueIndex], colTileIndex)
        TileCodedFeatureMatrix[valueIndex, rowTileIndex, colTileIndex] = 1
        
    #print(TileCodedFeatureMatrix)
    return TileCodedFeatureMatrix
    
def main():
    #testOneDimensionalTileCoding()
    testTwoDimensionalTileCodingWithoutOverlaps()
    
main()
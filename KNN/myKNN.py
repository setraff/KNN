import numpy as np
import math

# IMPORTANT: This class should support these attributes: modelX, modelY and labelsPresent:
class simple_KNN:
    # IMPORTANT: the parameter K specifies the number of neighbours to be considered when making a prediction 
    # IMPORTANT: verbose controls whether to print out the details of the training dataset
    def __init__(self, K, verbose = False):
        self.K = K
        self.verbose = verbose

    # IMPORTANT: X is a 2-dimensional numpy arrays with a column for each feature and a row for each different data item
    # IMPORTANT: y is a one-dimensional numpy array of labels encoded as integers, with one entry for each different data item.
    def fit(self, X, y):
        # get the amount of data items (the amount of rows) in the training dataset
        self.numTrainingItems = X.shape[0]
        # get the amount of features (the amount of columns) in the training dataset
        self.numFeatures = X.shape[1]
        # store local copies of the training dataset (X) and label ids (y)
        self.modelX = X
        self.modelY = y
        self.labelsPresent = np.unique(self.modelY)
        if (self.verbose):
            print(f"There are {self.numTrainingItems} data items in the training dataset.")
            print(f"self.modelX has a shape of {self.modelX.shape}.")
            print(f"self.modelY is a list of {len(self.modelY)} label ids, where there are {len(self.labelsPresent)} unique label ids.")
    
    # IMPORTANT: newItems is a two-dimensional numpy array with the same number of columns as the training data X.
    # returns a list of predicted label IDs for newItems
    def predict(self, newItems):
        # if rows of newItems > X, cut newItems to match the length of X
        if (newItems.shape[0] > self.modelX.shape[0]):
            self.newItems = newItems[:self.modelX.shape[0]]
        # else if rows of X > newItems, cut X to match the length of newItems
        elif (self.modelX.shape[0] > newItems.shape[0]):
            self.modelX = self.modelX[:newItems.shape[0]]
        else:
            self.newItems = newItems

        predicted_labels = [self.predict_new_item(i) for i in newItems]
        return predicted_labels

    # get most frequent label id for newItem
    def predict_new_item(self, newItem):
        # calculate the euclidian distance between two data items.
        def euclidean_distance(a, b):
            assert a.shape[0] == b.shape[0]
            distance = 0.0
            for i in range(a.shape[0]):
                difference = a[i] - b[i]
                distance= distance + difference*difference
            return math.sqrt(distance) 
        # stores the distances between newItem and all other items in the training dataset
        distances = [euclidean_distance(newItem, i) for i in self.modelX]
        # stores the indexes of the K nearest data items
        indexes = np.argsort(distances)[:self.K]
        # stores the labels of K nearest data items
        labels = [self.modelY[i] for i in indexes]
        # calculate and return the label with the highest frequency.
        if(len(labels) == 1):
            return (labels)[0]
        else:
            label = labels[np.bincount(labels).argmax()]
            return label
from myKNN import simple_KNN
from sklearn.metrics import accuracy_score
import numpy as np

X = np.genfromtxt('fruit_values.csv', delimiter=",")
_newItems = np.genfromtxt('newItems.csv', delimiter=",")
y = np.genfromtxt('fruit_label_ids.csv')
kval = 1
clf = simple_KNN(K=kval, verbose=True)
clf.fit(X, y)
predicted_labels = clf.predict(newItems=_newItems)
print(f"training labels: {list(y)}")
print(f"predicted_labels: {predicted_labels}")
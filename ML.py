# Linear Regression
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
data = {'StudyHours':[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15], 'Marks':[35,40,50,55,60,65,70,75,80,85,88,90,93,96,99]}
df = pd.DataFrame(data)
print("Dataset: ")
print(df)
X = df[['StudyHours']].values
y = df['Marks'].values
X_mean = np.mean(X)
X_std = np.std(X)
X = (X - X_mean) / X_std
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size = 0.2, random_state = 42)
model = LinearRegression()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
print("\nR2 Score: ", r2_score(y_test, y_pred))
print("\nMean Squared Error: ", mean_squared_error(y_test, y_pred))
print("\nSlope (m): ", model.coef_[0])
print("\nIntercept (c): ", model.intercept_)
plt.scatter(X, y)
plt.plot(X, model.predict(X), color='red')
plt.title("Linear Regresssion with Normalization")
plt.xlabel("Study Hours (Normalized)")
plt.ylabel("Marks")
plt.show()
hours = float(input("\nEnter study hours: "))
hours_normalized = (hours - X_mean) / X_std
predicted_marks = model.predict([[hours_normalized]])
print("\nPredicted Marks: ", predicted_marks[0])

# Logistic Regression
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, confusion_matrix
data = {'StudyHours':[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15], 'Pass':[0,0,0,0,0,0,1,1,1,1,1,1,1,1,1]}
df = pd.DataFrame(data)
print("Dataset:")
print(df)
X = df[['StudyHours']].values
y = df['Pass'].values
X_mean = np.mean(X)
X_std = np.std(X)
X = (X - X_mean) / X_std
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
model = LogisticRegression()
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
print("\nAccuracy:", accuracy_score(y_test, y_pred))
print("\nConfusion Matrix:\n", confusion_matrix(y_test, y_pred))
plt.scatter(X, y)
plt.title("Logistic Regression")
plt.xlabel("Study Hours (Normalized)")
plt.ylabel("Pass / Fail")
plt.show()
hours = float(input("\nEnter study hours: "))
hours_normalized = (hours - X_mean) / X_std
prediction = model.predict([[hours_normalized]])
if prediction[0] == 1:
    print("\nPrediction: Pass")
else:
    print("\nPrediction: Fail")

# SVM Classification + Regression
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.svm import SVC, SVR
from sklearn.metrics import accuracy_score, mean_squared_error
data = {
    'Hours':[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15],
    'Marks':[35,40,50,55,60,65,70,75,80,85,88,90,93,96,99],
    'Pass':[0,0,0,0,0,0,1,1,1,1,1,1,1,1,1]
}
df = pd.DataFrame(data)
print("Dataset:")
print(df)
X = df[['Hours']].values
y_class = df['Pass'].values
y_reg = df['Marks'].values
X_mean = np.mean(X)
X_std = np.std(X)
X = (X - X_mean) / X_std
X_train, X_test, y_train_class, y_test_class = train_test_split(
    X, y_class, test_size=0.2, random_state=42
)
X_train2, X_test2, y_train_reg, y_test_reg = train_test_split(
    X, y_reg, test_size=0.2, random_state=42
)
svc_model = SVC(kernel='linear')
svc_model.fit(X_train, y_train_class)
y_pred_class = svc_model.predict(X_test)
print("\nSVM Classification Accuracy:",
      accuracy_score(y_test_class, y_pred_class))
svr_model = SVR(kernel='linear')
svr_model.fit(X_train2, y_train_reg)
y_pred_reg = svr_model.predict(X_test2)
print("\nSVM Regression MSE:",
      mean_squared_error(y_test_reg, y_pred_reg))
plt.scatter(X, y_reg)
plt.plot(X, svr_model.predict(X), color='red')
plt.title("SVM Regression")
plt.xlabel("Hours (Normalized)")
plt.ylabel("Marks")
plt.show()
hours = float(input("\nEnter study hours: "))
hours_normalized = (hours - X_mean) / X_std
class_prediction = svc_model.predict([[hours_normalized]])
if class_prediction[0] == 1:
    print("\nClassification Prediction: Pass")
else:
    print("\nClassification Prediction: Fail")
reg_prediction = svr_model.predict([[hours_normalized]])
print("\nPredicted Marks:", reg_prediction[0])

# Decision Tree + Random Forest
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
from sklearn import tree
data = {
    'PetalLength':[1,1.2,1.4,1.5,3,3.2,3.5,3.8,5,5.2,5.5,5.8,6,6.2,6.5],
    'Species':[0,0,0,0,1,1,1,1,2,2,2,2,2,2,2]
}
df = pd.DataFrame(data)
print("Dataset:")
print(df)
X = df[['PetalLength']]
y = df['Species']
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)
dt_model = DecisionTreeClassifier()
dt_model.fit(X_train, y_train)
dt_pred = dt_model.predict(X_test)
print("\nDecision Tree Accuracy:",
      accuracy_score(y_test, dt_pred))
rf_model = RandomForestClassifier(n_estimators=10)
rf_model.fit(X_train, y_train)
rf_pred = rf_model.predict(X_test)
print("\nRandom Forest Accuracy:",
      accuracy_score(y_test, rf_pred))
plt.figure(figsize=(8,5))
tree.plot_tree(dt_model, filled=True)
plt.title("Decision Tree")
plt.show()
value = float(input("\nEnter petal length: "))
dt_prediction = dt_model.predict([[value]])
rf_prediction = rf_model.predict([[value]])
print("\nDecision Tree Prediction:", dt_prediction[0])
print("Random Forest Prediction:", rf_prediction[0])

# K-Means Clustering
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
data = {
    'Income':[20,22,25,27,30,35,40,42,45,50,55,60,65,70,75],
    'Spending':[15,18,20,22,25,30,35,38,40,45,50,55,60,65,70]
}
df = pd.DataFrame(data)
print(df)
X = df[['Income','Spending']]
model = KMeans(n_clusters=3, random_state=42)
model.fit(X)
df['Cluster'] = model.labels_
print("\nClustered Data:")
print(df)
plt.scatter(df['Income'], df['Spending'], c=df['Cluster'])
plt.title("K-Means Clustering")
plt.xlabel("Income")
plt.ylabel("Spending")
plt.show()

# DBSCAN Clustering
import pandas as pd
import matplotlib.pyplot as plt
from sklearn.cluster import DBSCAN
data = {
    'X':[1,2,2,3,8,8,9,25,26,27,50,51,52,53,54],
    'Y':[1,1,2,2,8,9,8,25,26,27,50,51,50,52,53]
}
df = pd.DataFrame(data)
print(df)
X = df[['X','Y']]
model = DBSCAN(eps=3, min_samples=2)
df['Cluster'] = model.fit_predict(X)
print("\nClustered Data:")
print(df)
plt.scatter(df['X'], df['Y'], c=df['Cluster'])
plt.title("DBSCAN Clustering")
plt.xlabel("X")
plt.ylabel("Y")
plt.show()

# Neural Network
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.metrics import accuracy_score
data = {
    'Hours':[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15],
    'Pass':[0,0,0,0,0,0,1,1,1,1,1,1,1,1,1]
}
df = pd.DataFrame(data)
print(df)
X = df[['Hours']].values
y = df['Pass'].values
X_mean = np.mean(X)
X_std = np.std(X)
X = (X - X_mean) / X_std
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)
model = MLPClassifier(hidden_layer_sizes=(5,), max_iter=1000)
model.fit(X_train, y_train)
y_pred = model.predict(X_test)
print("\nAccuracy:", accuracy_score(y_test, y_pred))
hours = float(input("\nEnter study hours: "))
hours_normalized = (hours - X_mean) / X_std
prediction = model.predict([[hours_normalized]])
if prediction[0] == 1:
    print("\nPrediction: Pass")
else:
    print("\nPrediction: Fail")
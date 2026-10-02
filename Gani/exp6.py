import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.datasets import fetch_openml
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, classification_report, confusion_matrix
# Load MNIST dataset
mnist = fetch_openml(mnist_784, version=1, as_frame=False)
X = mnist.data

y = mnist.target.astype(int)
print("Dataset Shape:", X.shape)
print("Labels:", np.unique(y))
# Use 15,000 images for faster execution
X = X[:15000]
y = y[:15000]
# Display first image pixel values
print("\nFirst Image Pixels:")
print(X[0].reshape(28, 28))
# Split dataset
X_train, X_test, y_train, y_test = train_test_split(
X,
y,
test_size=0.3,
random_state=42,
stratify=y
)
# Create and train Decision Tree model
model = DecisionTreeClassifier(
criterion=gini,
max_depth=10,
random_state=42
)
model.fit(X_train, y_train)
# Prediction
y_pred = model.predict(X_test)
# Accuracy
print("\nAccuracy:, accuracy_score(y_test, y_pred)")
# Classification Report
print("\nClassification Report:")
print(classification_report(y_test, y_pred))
# Confusion Matrix
cm = confusion_matrix(y_test, y_pred)
plt.figure(figsize=(8, 6))
sns.heatmap(cm, annot=True, fmt=d, cmap=Blues)
plt.title("Confusion Matrix - MNIST")
plt.xlabel(Predicted)
plt.ylabel(Actual)
plt.show()
# Display first 10 predicted images
fig, axes = plt.subplots(2, 5, figsize=(10, 5))

for i, ax in enumerate(axes.flat):
    ax.imshow(X_test[i].reshape(28, 28), cmap=gray)
    ax.set_title(
        fActual: {y_test[i]}\nPredicted: {y_pred[i]}
        )
    ax.axis(off)
plt.tight_layout()
plt.show()
# Display first three levels of Decision Tree
plt.figure(figsize=(20, 10))
plot_tree(
    model,
    max_depth=3,
    filled=True,
    fontsize=7,
    class_names=[str(i) for i in range(10)]
    )
plt.title("Decision Tree - MNIST ")
plt.show()
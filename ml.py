import os
import numpy as np
import pandas as pd
from sklearn.preprocessing import StandardScaler as ss
import sys
from sklearn.svm import SVC
from sklearn.model_selection import train_test_split
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.feature_selection import chi2
from sklearn.metrics import accuracy_score, f1_score


class Model(object):
    def __init__(self, csv_path):
        # read and shuffle the dataset
      
        self.df = pd.read_csv(csv_path)
        self.preprocess()

        self.clf = SVC(kernel='linear', C = 1) #neither too big nor too small margin.
    
    def preprocess(self):
        self.df = self.df.sample(
            frac=1,
            random_state=42
        ).reset_index(drop=True)

        self.X = self.df[['ngrams']].values.reshape(-1).astype('U')
        self.y = self.df[['class']].values.reshape(-1)

        self.X_train, self.X_test, self.y_train, self.y_test = \
            train_test_split(self.X, self.y, test_size=0.25, random_state=42)

    def score_features(self, vocab=None):
        self.vec = TfidfVectorizer(vocabulary=vocab)
        print(f"\nX_train shape: {self.X_train.shape}")

        if vocab:
            self.X_train = self.vec.fit_transform(self.X_train)
            print(f"Transformed X shape: {self.X_train.shape}")
        else:
            self.X_transf_full = self.vec.fit_transform(self.X_train)
            print(f"Inc. Tran. X shape: {self.X_transf_full.shape}")

    def select_features(self, max_features: int = 1000):

        _, pvals = chi2(self.X_transf_full, self.y_train)
        top_indices = np.argsort(pvals)[-max_features:]
        reverse_vocab = self.vec.get_feature_names()
        
        target_vocab = []
        for top_idx in top_indices:
            target_vocab.append(reverse_vocab[top_idx])
        
        print(f"\nLen of Target Vocab: {len(target_vocab)}")
        
        self.score_features(vocab=target_vocab)

    def train(self):
        self.clf.fit(self.X_train, self.y_train)

    def evaluate(self):
        preds = self.clf.predict(self.X_train)
        print(f"Train Acc: {accuracy_score(self.y_train, preds)}")
        print(f"Train F1: {f1_score(self.y_train, preds)}")
        self.X_test = self.vec.transform(self.X_test)
        preds = self.clf.predict(self.X_test)
        print(f"Acc: {accuracy_score(self.y_test, preds)}")
        print(f"F1: {f1_score(self.y_test, preds)}")
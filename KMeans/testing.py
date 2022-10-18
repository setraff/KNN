from myVisualiser import cluster_and_visualise

datafilename = 'fruit_values.csv'
K = 3
featurenames =  ( 'mean_red', 'mean_green', 'mean_blue','width', 'height', 'weight')

cluster_and_visualise(datafilename, K, featurenames)
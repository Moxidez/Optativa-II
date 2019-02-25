datos = read.csv("iris.csv", header = TRUE,sep = ",") # header -> cabeceras , sep = separador de col
View(datos)
library(caTools)
library(NoiseFiltersR)
set.seed(123) # semilla -> randomica
split= sample.split(datos$label, SplitRatio=0.8) #tomar random de la semilla a partir de la etiqueta
training_set = subset(datos, split==TRUE)
test_set=subset(datos,split==FALSE)
training_set$label= factor(training_set$label, levels = c(1,2,3))

cnn_matrix=CNN(training_set,k=1)
training_setcnn = subset(cnn_matrix, split==TRUE)
test_setcnn=subset(cnn_matrix,split==FALSE)
print(cnn_matrix)
cnn_matrix=cnn_matrix$cleanData


rnn_matrix=RNN(training_set,k=1)
print(rnn_matrix)
rnn_matrix=rnn_matrix$cleanData
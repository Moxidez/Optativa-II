datos = read.csv("datos.csv", header = TRUE,sep = ";") # header -> cabeceras , sep = separador de col
#view -> obversar la matriz
View(datos)

####### Instalar librerias caTools y noiseFilterR#######

###Cargar las librerias###
library(caTools)
library(NoiseFiltersR)
set.seed(123) # semilla -> randomica
split= sample.split(datos$label, SplitRatio=0.8) #tomar random de la semilla a partir de la etiqueta
                                                 #0.8 se elije para base de datos entrenamiento
training_set = subset(datos, split==TRUE)
test_set=subset(datos,split==FALSE)

#############FILTROS EN R#####################
###### convertir etiqueta en factor

training_set$label= factor(training_set$label, levels = c(1,2,3))
#CNN
cnn_matrix=CNN(training_set,k=3)
print(cnn_matrix)
#Number of removed instances: 740 (77.48691 %)
cnn_matrix=cnn_matrix$cleanData

# AENN, CNN, ENN, RNN, DROP3

#AENN
aenn_matrix=AENN(training_set,k=3)
print(aenn_matrix)
#Number of removed instances: 89 (9.319372 %)
aenn_matrix=aenn_matrix$cleanData

#RNN
rnn_matrix=RNN(training_set,k=3)
print(rnn_matrix)
#Number of removed instances: 740 (77.48691 %)
rnn_matrix=rnn_matrix$cleanData

#### GUARDAR MATRIZ EN UN ARCHIVO#######
write.csv(rnn_matrix,file = "rnn_matriz.csv", sep = ",")
write.csv(cnn_matrix,file = "cnn_matriz.csv", sep = ",")
write.csv(aenn_matrix,file = "aenn_matriz.csv", sep = ";")


################### BALANCEO DE DATOS###################
# Cada conjunto cuente con el mismo numero de datos.
library(prospectr)
matrix_ks=kenStone(training_set,k=180,metric = "euclid")
matrix_ks=training_set[matrix_ks$model,]
#ordenar
# convertir como factor a la etiqueta

matrix_ks$label= factor(matrix_ks$label, levels = c(1,2,3))
# aplican CNN
cnn_matrix2=CNN(matrix_ks,k=3)
print(cnn_matrix2)
#NNumber of removed instances: 102 (56.66667 %)
cnn_matrix2=cnn_matrix2$cleanData

#aplican kNN
y_pred=knn(train=cnn_matrix2[,-6], test= test_set[,-6], cl= cnn_matrix2[,6], k=3)

cm=table(test_set[,6],y_pred)
cm

#   1  2  3
#1 72 12  2
#2  8 64 18
#3  8 26 29
#72+64+29 = 147/152=0.967

48+45+28
121/152



baseks=datos[modelks$model,]
#ordenar los datos
baseks=baseks[order(baseks$Tipo_Rep),]











###################KNN################

library(class)
y_pred=knn(train=training_set[,-6], test= test_set[,-6], cl= training_set [,6], k=3)

cm=table(test_set[,6],y_pred)
cm
#  1  2  3
#1 80  4  2
#2 10 73  7
#3  3 12 48

#rendimiento= (80+73+48)/152=0.973%


#####CNN##########
y_pred=knn(train=cnn_matrix[,-6], test= test_set[,-6], cl=cnn_matrix [,6], k=3)

cm=table(test_set[,6],y_pred)
cm

#    1   2  3
#1 77  8  1
#2  6 68 16
#3  6 15 42

#77+68+42= 106/152=0.697


####### RNN ########
y_pred=knn(train=rnn_matrix[,-6], test= test_set[,-6], cl=rnn_matrix [,6], k=3)

cm=table(test_set[,6],y_pred)
cm
#    1   2  3
#1 78  7  1
#2  6 70 14
#3  4 17 42
#78+70+42=0.697


############### REDUCCION DE DIMENSIONES###########333
library(caret)
pca=preProcess(x=cnn_matrix2[,-6],method = 'pca',pcaComp = 2)
pca_cnn=predict(pca,cnn_matrix2)
plot(pca_cnn$PC1,pca_cnn$PC2,col=pca_cnn$label, pch= 16, xlab = "PC1", ylab = "pc2")


pca=preProcess(x=cnn_matrix2[,-6],method = 'pca',pcaComp = 2)
pca_cnn=predict(pca,cnn_matrix2)
plot(pca_cnn$PC1,pca_cnn$PC2,col=pca_cnn$label, pch= 16, xlab = "PC1", ylab = "pc2")



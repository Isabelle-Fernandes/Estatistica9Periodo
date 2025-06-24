
// Bloco de declaração de dados

data{
  int<lower=1> n;
  int<lower=1> q;
  int<lower=0> y[n];
  matrix[n,q] x;
  vector[q] m_beta;
  matrix[q,q] S_beta;
}

 // Bloco de declaração de parâmetros

parameters{
  vector[q] beta;
}
 
// Bloco de parâmetros transformados

transformed parameters{
  vector[n] theta;
  for(i in 1:n){
    theta[i] = exp(x[i,] * beta);
  }
}

// Bloco do modelo

model{
  // Verossimilhança
  for(i in 1:n){
    y[i] ~ poisson(theta[i]);
  }
  
  // Priori 1:  Normal Multivariada com vetor de medias e matriz de covariâncias
  beta ~ multi_normal(m_beta, S_beta);
}

//
//
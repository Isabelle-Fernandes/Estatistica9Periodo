
// Bloco de declaração de dados

data{
  int<lower=1> n;
  vector[n] y;
  real m;
  real<lower=0> v;
  real<lower=0> a;
  real<lower=0> b;
}

 // Bloco de declaração de parâmetros

parameters{
  real mu_real;
  real<lower=0> phi_real;
}
 
// Bloco de parâmetros transformados

transformed parameters{
  real sigma2;
  sigma2 = 1/phi_real;
}

// Bloco do modelo.

model{
  // Verossimilhança
  for(i in 1:n){y[i] ~ normal(mu_real, sqrt(1/phi_real));}
  
  // Priori 1: 
  mu_real ~ normal(m,v);
  
  // Priori 2: 
  phi_real ~ gamma(a,b);
}


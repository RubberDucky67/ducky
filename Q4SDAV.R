p <- 0.1
n <- 10
lambda <- 3
mu <- 50
sigma <- 10
binom_prob <- dbinom(2, size = n, prob = p)
cat("Binomial P(X = 2):", binom_prob, "\n")
pois_prob <- dpois(2, lambda = lambda)
cat("Poisson P(X = 2):", pois_prob, "\n")
norm_prob <- pnorm(60, mean = mu, sd = sigma)
cat("Normal P(X < 60):", norm_prob, "\n")
z <- 1.96   # for 95% CI
lower <- mu - z * sigma/sqrt(n)
upper <- mu + z * sigma/sqrt(n)
cat("95% Confidence Interval: [", lower, ",", upper, "]\n")
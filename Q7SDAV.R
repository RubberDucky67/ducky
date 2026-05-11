n <- 100
x <- 65
p_hat <- x / n
cat("=== Proportion Test ===\n")
prop_test <- prop.test(x, n, p = 0.5)
print(prop_test)
cat("\n=== Z-test ===\n")
p0 <- 0.5
z <- (p_hat - p0) / sqrt((p0 * (1 - p0)) / n)
p_value_z <- 2 * (1 - pnorm(abs(z)))
cat("Z value:", z, "\n")
cat("p-value:", p_value_z, "\n")
cat("\n=== t-test ===\n")
sample_data <- c(rep(1, x), rep(0, n - x))
t_test <- t.test(sample_data, mu = 0.5)
print(t_test)
cat("\n=== 95% Confidence Interval ===\n")
z_crit <- 1.96
margin <- z_crit * sqrt((p_hat * (1 - p_hat)) / n)
lower <- p_hat - margin
upper <- p_hat + margin
cat("CI:", lower, "to", upper, "\n")
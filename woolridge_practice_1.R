install.packages("wooldridge")

library(wooldridge)
#mean(x)      # average
#sd(x)        # standard deviation
#var(x)       # variance
#median(x)    # median
#min(x)       # minimum
#max(x)       # maximum
#range(x)     # min and max together
#quantile(x)  # quartiles
#summary(x)   # gives you mean, median, min, max, quartiles all at once

data(wage1)
head(wage1)

avg_education <- mean(wage1$educ, na.rm=TRUE)
min_education <- min(wage1$educ)
max_education <- max(wage1$educ)

# Average education
avg_education

min_education

max_education



avg_wage <- mean(wage1$wage, na.rm=TRUE)

avg_wage

wage1$wage_2026 <- wage1$wage * (334.980 / 56.9)  # This will give us wage adjusted for inflation


head(wage1$wage_2026)


avg_wage_2026 <- mean(wage1$wage_2026, na.rm=TRUE)
avg_wage_2026
avg_wage








# Install once (if you haven't already) -- remove the # to run these the first time
# install.packages("readxl")
# install.packages('ggplot2')


# Load the library (needed every session)
#library(readxl)
#library(ggplot2)
# Read the file
crime <- read_excel("/Users/elper2/Documents/econ424/problemset1.xls")

# Check it worked
head(crime)



# ---- Summary statistics ----
summary(crime)                 # min, max, median, mean, quartiles
sd(crime$Violence)             # standard deviation
sd(crime$Unemployment)


# ---- Boxplot: shows the spread and any outliers ----
ggplot(crime, aes(y = Violence)) +
  geom_boxplot(fill = "orange") +
  labs(title = "Violent Crime Rate", y = "Violence")


# ---- Scatter plot with a best-fit line ----
ggplot(crime, aes(x = Unemployment, y = Violence)) +
  geom_point(color = "steelblue") +
  geom_smooth(method = "lm", se = TRUE, color = "red") +
  labs(title = "Unemployment vs. Violent Crime", x = "Unemployment (%)", y = "Violent crime rate")


# ---- Correlation ----
cor(crime$Unemployment, crime$Violence)



# ---- Simple linear regression ----
model <- lm(Violence ~ Unemployment, data = crime)
summary(model)

# Residuals vs. fitted values: there should be no clear pattern
plot(model, which = 1)


# ---- Outliers ----
crime[order(-crime$Violence), ]   # states sorted from highest to lowest violence

# Scatter plot with state names so the outliers are easy to spot
ggplot(crime, aes(x = Unemployment, y = Violence, label = State)) +
  geom_point() +
  geom_text(size = 2.5, vjust = -0.7) +
  labs(title = "Unemployment vs. Violent Crime (labeled)", x = "Unemployment (%)", y = "Violent crime rate")

# Rerun the regression without DC and compare the slope to the first model
model_noDC <- lm(Violence ~ Unemployment, data = subset(crime, State != "District of Columbia"))
summary(model_noDC)




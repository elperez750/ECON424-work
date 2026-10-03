

library(wooldridge)

data("meap01")



# 0
min(meap01$math4)


# 100
max(meap01$math4)

str(meap01)


perfect_math <- sum(meap01$math4 == 100)
perfect_math

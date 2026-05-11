# Q1-2015
happiness <- read.csv("2015.csv", stringsAsFactors = FALSE)
cat("Columns:", ncol(happiness), "\n")
cat("Rows:", nrow(happiness), "\n\n")
classify_happiness <- function(score) {
  if (score >= 7.0) {
    return("High Happiness Country")
  } else if (score >= 5.0) {
    return("Medium Happiness Country")
  } else {
    return("Low Happiness Country")
  }
}
cat("Example:", classify_happiness(happiness$Happiness.Score[1]), "\n\n")
cat("=== Country Happiness Classification ===\n")
for (i in 1:min(10, nrow(happiness))) {
  score <- happiness$Happiness.Score[i]
  country <- happiness$Country[i]
  cat("Country:", country,
      "| Score:", round(score, 3),
      "|", classify_happiness(score), "\n")
}
summarise_happiness <- function(scores) {
  total   <- sum(scores, na.rm = TRUE)
  avg     <- mean(scores, na.rm = TRUE)
  highest <- max(scores, na.rm = TRUE)
  lowest  <- min(scores, na.rm = TRUE)
  cat("\n=== Happiness Score Summary ===\n")
  cat("Total Score Sum:", round(total, 3), "\n")
  cat("Average Score  :", round(avg, 3), "\n")
  cat("Highest Score  :", round(highest, 3), "\n")
  cat("Lowest Score   :", round(lowest, 3), "\n")
  return(avg)
}
summarise_happiness(happiness$Happiness.Score)
segments <- sapply(happiness$Happiness.Score, classify_happiness)
cat("\n=== Happiness Tier Distribution ===\n")
print(table(segments))
cat("\n=== Top 5 Happiest Countries ===\n")
top5 <- happiness[order(-happiness$Happiness.Score), ][1:5, c("Country", "Happiness.Score", "Region")]
print(top5)

# Q1-Mall_customers
mall <- read.csv("Mall_Customers.csv", stringsAsFactors = FALSE)
cat("Columns:", ncol(mall), "\n")
cat("Rows:", nrow(mall), "\n\n")
classify_spender <- function(spending_score) {
  if (spending_score <= 33) {
    return("Low Spender")
  } else if (spending_score <= 66) {
    return("Moderate Spender")
  } else {
    return("High Spender")
  }
}
cat("Example:", classify_spender(mall$Spending.Score..1.100.[1]), "\n\n")
cat("=== Customer Spending Classification ===\n")
for (i in 1:min(10, nrow(mall))) {
  score  <- mall$Spending.Score..1.100.[i]
  income <- mall$Annual.Income..k..[i]
  cat("Customer", mall$CustomerID[i],
      "| Income:", income, "k$",
      "| Spending Score:", score,
      "|", classify_spender(score), "\n")
}
summarise_mall <- function(incomes, scores) {
  cat("\n=== Mall Customer Summary ===\n")
  cat("Average Annual Income :", round(mean(incomes, na.rm = TRUE), 2), "k$\n")
  cat("Average Spending Score:", round(mean(scores,  na.rm = TRUE), 2), "\n")
  cat("Max Income            :", max(incomes, na.rm = TRUE), "k$\n")
  cat("Min Income            :", min(incomes, na.rm = TRUE), "k$\n")
}
summarise_mall(mall$Annual.Income..k.., mall$Spending.Score..1.100.)
segments <- sapply(mall$Spending.Score..1.100., classify_spender)
cat("\n=== Spending Segment Distribution ===\n")
print(table(segments))
cat("\n=== Gender Breakdown ===\n")
print(table(mall$Gender))

# Q1-Online_Sales_Data
sales <- read.csv("Online_Sales_Data.csv", stringsAsFactors = FALSE)
cat("Columns:", ncol(sales), "\n")
cat("Rows:", nrow(sales), "\n\n")
classify_transaction <- function(revenue) {
  if (revenue < 100) {
    return("Low Revenue Transaction")
  } else if (revenue < 500) {
    return("Medium Revenue Transaction")
  } else {
    return("High Revenue Transaction")
  }
}
cat("Example:", classify_transaction(sales$Total.Revenue[1]), "\n\n")
cat("=== Transaction Revenue Classification ===\n")
for (i in 1:min(10, nrow(sales))) {
  rev      <- sales$Total.Revenue[i]
  product  <- sales$Product.Name[i]
  category <- sales$Product.Category[i]
  cat("Txn", i,
      "| Category:", category,
      "| Product:", product,
      "| Revenue:", rev,
      "|", classify_transaction(rev), "\n")
}
calculate_sales_summary <- function(revenues, units) {
  cat("\n=== Sales Summary ===\n")
  cat("Total Revenue   :", sum(revenues, na.rm = TRUE), "\n")
  cat("Average Revenue :", round(mean(revenues, na.rm = TRUE), 2), "\n")
  cat("Total Units Sold:", sum(units, na.rm = TRUE), "\n")
  cat("Max Single Sale :", max(revenues, na.rm = TRUE), "\n")
  return(invisible(NULL))
}
calculate_sales_summary(sales$Total.Revenue, sales$Units.Sold)
segments <- sapply(sales$Total.Revenue, classify_transaction)
cat("\n=== Transaction Tier Distribution ===\n")
print(table(segments))
cat("\n=== Revenue by Product Category ===\n")
cat_rev <- aggregate(Total.Revenue ~ Product.Category, data = sales, FUN = sum)
cat_rev <- cat_rev[order(-cat_rev$Total.Revenue), ]
print(cat_rev)

# Q1-Salary_Data
salary_df <- read.csv("Salary_Data.csv", stringsAsFactors = FALSE)
salary_df$Salary <- as.numeric(salary_df$Salary)
salary_df <- salary_df[!is.na(salary_df$Salary), ]
cat("Columns:", ncol(salary_df), "\n")
cat("Rows:", nrow(salary_df), "\n\n")
classify_salary_band <- function(salary) {
  if (salary < 50000) {
    return("Entry Level")
  } else if (salary < 100000) {
    return("Mid Level")
  } else {
    return("Senior / Executive Level")
  }
}
cat("Example:", classify_salary_band(salary_df$Salary[1]), "\n\n")
cat("=== Employee Salary Band Classification ===\n")
for (i in 1:min(10, nrow(salary_df))) {
  sal   <- salary_df$Salary[i]
  title <- salary_df$Job.Title[i]
  exp   <- salary_df$Years.of.Experience[i]
  cat("Employee", i,
      "| Job:", title,
      "| Experience:", exp, "yrs",
      "| Salary:", sal,
      "|", classify_salary_band(sal), "\n")
}
salary_stats <- function(salaries) {
  cat("\n=== Salary Statistics ===\n")
  cat("Total Payroll   :", sum(salaries, na.rm = TRUE), "\n")
  cat("Average Salary  :", round(mean(salaries, na.rm = TRUE), 2), "\n")
  cat("Median Salary   :", median(salaries, na.rm = TRUE), "\n")
  cat("Highest Salary  :", max(salaries, na.rm = TRUE), "\n")
  cat("Lowest Salary   :", min(salaries, na.rm = TRUE), "\n")
  return(invisible(NULL))
}
salary_stats(salary_df$Salary)
segments <- sapply(salary_df$Salary, classify_salary_band)
cat("\n=== Salary Band Distribution ===\n")
print(table(segments))
cat("\n=== Average Salary by Education Level ===\n")
edu_avg <- aggregate(Salary ~ Education.Level, data = salary_df, FUN = mean)
edu_avg$Salary <- round(edu_avg$Salary, 2)
print(edu_avg[order(-edu_avg$Salary), ])

# Q1-Titanic-Dataset
titanic <- read.csv("Titanic-Dataset.csv", stringsAsFactors = FALSE)
titanic$Age  <- as.numeric(titanic$Age)
titanic$Fare <- as.numeric(titanic$Fare)
cat("Columns:", ncol(titanic), "\n")
cat("Rows:", nrow(titanic), "\n\n")
classify_survival_risk <- function(pclass, sex, age) {
  if (is.na(age)) age <- 30          # impute median-ish
  if (sex == "female" && pclass == 1) {
    return("High Survival Chance")
  } else if (sex == "female" || (sex == "male" && age < 15)) {
    return("Moderate Survival Chance")
  } else {
    return("Low Survival Chance")
  }
}
cat("Example:", classify_survival_risk(
  titanic$Pclass[1], titanic$Sex[1], titanic$Age[1]), "\n\n")
cat("=== Passenger Survival Risk Classification ===\n")
for (i in 1:min(10, nrow(titanic))) {
  p   <- titanic[i, ]
  cat("Passenger", p$PassengerId,
      "| Name:", p$Name,
      "| Class:", p$Pclass,
      "| Sex:", p$Sex,
      "| Age:", ifelse(is.na(p$Age), "NA", p$Age),
      "| Survived:", p$Survived,
      "|", classify_survival_risk(p$Pclass, p$Sex, p$Age), "\n")
}
summarise_titanic <- function(df) {
  cat("\n=== Titanic Summary ===\n")
  cat("Total Passengers   :", nrow(df), "\n")
  cat("Survivors          :", sum(df$Survived, na.rm = TRUE), "\n")
  cat("Survival Rate      :", round(mean(df$Survived, na.rm = TRUE) * 100, 2), "%\n")
  cat("Average Fare       :", round(mean(df$Fare, na.rm = TRUE), 2), "\n")
  cat("Average Age        :", round(mean(df$Age, na.rm = TRUE), 2), "\n")
  return(invisible(NULL))
}
summarise_titanic(titanic)
segments <- mapply(classify_survival_risk,
                   titanic$Pclass, titanic$Sex, titanic$Age)
cat("\n=== Survival Risk Segment Distribution ===\n")
print(table(segments))
cat("\n=== Survival Rate by Passenger Class ===\n")
class_surv <- aggregate(Survived ~ Pclass, data = titanic, FUN = mean)
class_surv$SurvivalRate <- paste0(round(class_surv$Survived * 100, 1), "%")
print(class_surv[, c("Pclass", "SurvivalRate")])

# Q1-Wholesale_customers_data
wholesale <- read.csv("Wholesale_customers_data.csv", stringsAsFactors = FALSE)
cat("Columns:", ncol(wholesale), "\n")
cat("Rows:", nrow(wholesale), "\n\n")
classify_wholesale_customer <- function(total_spend) {
  if (total_spend < 20000) {
    return("Small Account")
  } else if (total_spend < 60000) {
    return("Medium Account")
  } else {
    return("Large Account")
  }
}
wholesale$Total_Spend <- rowSums(
  wholesale[, c("Fresh", "Milk", "Grocery", "Frozen",
                "Detergents_Paper", "Delicassen")],
  na.rm = TRUE
)
cat("Example:", classify_wholesale_customer(wholesale$Total_Spend[1]), "\n\n")
cat("=== Wholesale Customer Account Classification ===\n")
for (i in 1:min(10, nrow(wholesale))) {
  spend   <- wholesale$Total_Spend[i]
  channel <- ifelse(wholesale$Channel[i] == 1, "Horeca", "Retail")
  region  <- wholesale$Region[i]
  cat("Customer", i,
      "| Channel:", channel,
      "| Region:", region,
      "| Total Spend:", spend,
      "|", classify_wholesale_customer(spend), "\n")
}
summarise_wholesale <- function(df) {
  categories <- c("Fresh", "Milk", "Grocery", "Frozen",
                  "Detergents_Paper", "Delicassen")
  cat("\n=== Category Spend Summary ===\n")
  for (cat_name in categories) {
    cat(sprintf("%-20s Total: %10.0f  |  Avg: %8.2f\n",
        cat_name,
        sum(df[[cat_name]], na.rm = TRUE),
        mean(df[[cat_name]], na.rm = TRUE)))
  }
  return(invisible(NULL))
}
summarise_wholesale(wholesale)
segments <- sapply(wholesale$Total_Spend, classify_wholesale_customer)
cat("\n=== Account Size Distribution ===\n")
print(table(segments))
cat("\n=== Average Total Spend by Channel ===\n")
ch <- aggregate(Total_Spend ~ Channel, data = wholesale, FUN = mean)
ch$Channel <- ifelse(ch$Channel == 1, "Horeca", "Retail")
print(ch)

# Q1-data
diabetes <- read.csv("data.csv", stringsAsFactors = FALSE)
diabetes$BMI     <- as.numeric(diabetes$BMI)
diabetes$Glucose <- as.numeric(diabetes$Glucose)
cat("Columns:", ncol(diabetes), "\n")
cat("Rows:", nrow(diabetes), "\n\n")
classify_bmi_risk <- function(bmi) {
  if (is.na(bmi) || bmi == 0) {
    return("Unknown")
  } else if (bmi < 18.5) {
    return("Underweight")
  } else if (bmi < 25.0) {
    return("Normal Weight")
  } else if (bmi < 30.0) {
    return("Overweight")
  } else {
    return("Obese")
  }
}
cat("Example:", classify_bmi_risk(diabetes$BMI[1]), "\n\n")
cat("=== Patient BMI Risk Classification ===\n")
for (i in 1:min(10, nrow(diabetes))) {
  p <- diabetes[i, ]
  cat("Patient", i,
      "| BMI:", p$BMI,
      "| Glucose:", p$Glucose,
      "| Age:", p$Age,
      "| Diabetic:", ifelse(p$Outcome == 1, "Yes", "No"),
      "|", classify_bmi_risk(p$BMI), "\n")
}
summarise_diabetes <- function(df) {
  cat("\n=== Clinical Summary ===\n")
  cat("Total Patients      :", nrow(df), "\n")
  cat("Diabetic Patients   :", sum(df$Outcome, na.rm = TRUE), "\n")
  cat("Diabetes Rate       :", round(mean(df$Outcome, na.rm = TRUE) * 100, 2), "%\n")
  cat("Average BMI         :", round(mean(df$BMI[df$BMI > 0], na.rm = TRUE), 2), "\n")
  cat("Average Glucose     :", round(mean(df$Glucose[df$Glucose > 0], na.rm = TRUE), 2), "\n")
  cat("Average Age         :", round(mean(df$Age, na.rm = TRUE), 2), "\n")
  return(invisible(NULL))
}
summarise_diabetes(diabetes)
segments <- sapply(diabetes$BMI, classify_bmi_risk)
cat("\n=== BMI Risk Category Distribution ===\n")
print(table(segments))
cat("\n=== Diabetes Rate by BMI Category ===\n")
diabetes$BMI_Category <- sapply(diabetes$BMI, classify_bmi_risk)
rate_by_bmi <- aggregate(Outcome ~ BMI_Category, data = diabetes, FUN = mean)
rate_by_bmi$DiabetesRate <- paste0(round(rate_by_bmi$Outcome * 100, 1), "%")
print(rate_by_bmi[, c("BMI_Category", "DiabetesRate")])

# Q1-ds_salaries
ds <- read.csv("ds_salaries.csv", stringsAsFactors = FALSE)
if ("Unnamed..0" %in% colnames(ds)) {
  ds$Unnamed..0 <- NULL
}
ds$salary_in_usd <- as.numeric(ds$salary_in_usd)
ds <- ds[!is.na(ds$salary_in_usd), ]
cat("Columns:", ncol(ds), "\n")
cat("Rows:", nrow(ds), "\n\n")
classify_ds_salary <- function(salary_usd) {
  if (salary_usd < 70000) {
    return("Junior / Below Market")
  } else if (salary_usd < 130000) {
    return("Market Rate")
  } else {
    return("Senior / Above Market")
  }
}
cat("Example:", classify_ds_salary(ds$salary_in_usd[1]), "\n\n")
cat("=== Data Scientist Salary Classification ===\n")
for (i in 1:min(10, nrow(ds))) {
  d <- ds[i, ]
  exp_label <- switch(d$experience_level,
    "EN" = "Entry",
    "MI" = "Mid",
    "SE" = "Senior",
    "EX" = "Executive",
    d$experience_level)
  cat("Employee", i,
      "| Title:", d$job_title,
      "| Exp:", exp_label,
      "| Remote:", paste0(d$remote_ratio, "%"),
      "| USD Salary:", d$salary_in_usd,
      "|", classify_ds_salary(d$salary_in_usd), "\n")
}
summarise_ds_salaries <- function(salaries) {
  cat("\n=== DS Salary Market Summary ===\n")
  cat("Total Records   :", length(salaries), "\n")
  cat("Average Salary  :", round(mean(salaries, na.rm = TRUE), 2), "USD\n")
  cat("Median Salary   :", median(salaries, na.rm = TRUE), "USD\n")
  cat("Highest Salary  :", max(salaries, na.rm = TRUE), "USD\n")
  cat("Lowest Salary   :", min(salaries, na.rm = TRUE), "USD\n")
  return(invisible(NULL))
}
summarise_ds_salaries(ds$salary_in_usd)
segments <- sapply(ds$salary_in_usd, classify_ds_salary)
cat("\n=== Salary Tier Distribution ===\n")
print(table(segments))
cat("\n=== Average USD Salary by Experience Level ===\n")
exp_avg <- aggregate(salary_in_usd ~ experience_level, data = ds, FUN = mean)
exp_avg$salary_in_usd <- round(exp_avg$salary_in_usd, 2)
exp_avg$experience_level <- factor(
  exp_avg$experience_level,
  levels = c("EN", "MI", "SE", "EX"),
  labels = c("Entry", "Mid", "Senior", "Executive")
)
print(exp_avg[order(exp_avg$experience_level), ])